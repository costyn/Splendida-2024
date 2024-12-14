#include "encoders.h"

/*
    encoderSetup
    Initialize the I2C encoders with the custom pins

*/

EncoderState g_encoderState = BRIGHTNESS; // default state

void encoderSetup()
{
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN); // Initialize I2C with custom pins

    pinMode(I2C_INT_PIN, INPUT);

    RGBEncoder.reset();

    RGBEncoder.begin(
        i2cEncoderLibV2::INT_DATA |
        i2cEncoderLibV2::WRAP_DISABLE |
        i2cEncoderLibV2::DIRE_RIGHT |
        i2cEncoderLibV2::IPUP_ENABLE |
        i2cEncoderLibV2::RMOD_X1 |
        i2cEncoderLibV2::RGB_ENCODER);
    RGBEncoder.id = 0;                      // do we need this?
    RGBEncoder.writeAntibouncingPeriod(25); // 250ms of debouncing
    RGBEncoder.writeDoublePushPeriod(100);  // Set the double push period to 500ms

    /* Configure the callback events */
    RGBEncoder.onChange = encoder_onChange;
    RGBEncoder.onButtonPush = encoder_onButtonPush;
    RGBEncoder.onMinMax = encoder_onMinMax;
    RGBEncoder.onFadeProcess = encoder_onFadeEnd;
    RGBEncoder.onButtonDoublePush = encoder_doubleClick;

    /* Enable the I2C Encoder V2 interrupts according to the previus attached callback */
    RGBEncoder.autoconfigInterrupt();

    RGBEncoder.writeCounter((int32_t)ENCODER_DEFAULT);
    RGBEncoder.writeMax((int32_t)ENCODER_MAX);
    RGBEncoder.writeMin((int32_t)ENCODER_MIN);
    RGBEncoder.writeStep((int32_t)ENCODER_STEP);
}

void readEncoders()
{
    if (digitalRead(I2C_INT_PIN) == LOW)
    {
        if (digitalRead(I2C_INT_PIN) == HIGH)
        { // If the interrupt pin return high, exit from the encoder scan
            return;
        }
        RGBEncoder.updateStatus();
    }
}

void encoder_onChange(i2cEncoderLibV2 *obj)
{
    constexpr const char *SGN = "encoder_onChange()";
    bool increasing = obj->readStatus(i2cEncoderLibV2::RINC);

    switch (g_encoderState)
    {
    case BRIGHTNESS:
        if (increasing)
        {
            g_targetBrightness = min(255, g_targetBrightness + 5);
        }
        else
        {
            g_targetBrightness = max(0, g_targetBrightness - 5);
        }
        Serial.printf("%s: Brightness target: %d\n", SGN, g_targetBrightness);
        break;

    case SPEED:
        if (increasing)
        {
            g_animationSpeed = min(0.4f, g_animationSpeed + 0.01f);
        }
        else
        {
            g_animationSpeed = max(-0.4f, g_animationSpeed - 0.01f);
        }
        Serial.printf("%s: Animation Speed: %.2f\n", SGN, g_animationSpeed);
        break;

    default:
        break;
    }
}

// a function to that will select the next EncoderState when the button is pressed
void encoder_onButtonPush(i2cEncoderLibV2 *obj)
{
    constexpr const char *SGN = "encoder_onButtonPush()";

    switch (g_encoderState)
    {
    case BRIGHTNESS:
        obj->writeRGBCode(0x00FFFF);
        g_encoderState = SPEED;
        break;
    case SPEED:
        g_encoderState = BRIGHTNESS;
        obj->writeRGBCode(0xFF0000);
        break;
    default:
        obj->writeRGBCode(0x00FFFF);
        g_encoderState = BRIGHTNESS;
        break;
    }
    Serial.printf("%s: %s: EncoderState: %s\n", timeToString().c_str(), SGN, g_encoderState);
}

void encoder_doubleClick(i2cEncoderLibV2 *obj)
{
    constexpr const char *SGN = "encoder_doubleClick()";
    Serial.printf("%s: %s: Initiating change pattern\n", timeToString().c_str(), SGN);
    changePattern();
}

void encoder_onMinMax(i2cEncoderLibV2 *obj)
{
    constexpr const char *SGN = "encoder_onMinMax()";

    obj->writeRGBCode(0xFF0000);

    if (obj->readStatus(i2cEncoderLibV2::RMAX))
        Serial.printf("%s: %s: Max\n", timeToString().c_str(), SGN);
    else
        Serial.printf("%s: %s: Min\n", timeToString().c_str(), SGN);
}

void encoder_onFadeEnd(i2cEncoderLibV2 *obj)
{
    obj->writeRGBCode(0x000000);
}

void encoderColorFeedback(i2cEncoderLibV2 *obj, EncoderEvent event)
{
    if (event == ROTATE)
    {
        obj->writeRGBCode(0xFFFFFF);
    }
    if (event == CLICK)
    {
        obj->writeRGBCode(0x00FFFF);
    }
    if (event == LIMIT)
    {
        obj->writeRGBCode(0xFF0000);
    }
}

void setBrightness(int brightness)
{
    RGBEncoder.writeCounter((int32_t)brightness);
}