#include "encoders.h"

/*
    encoderSetup
    Initialize the I2C encoders with the custom pins

*/

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

    /* Configure the events */
    RGBEncoder.onChange = encoder_rotated;
    RGBEncoder.onButtonRelease = encoder_click;
    RGBEncoder.onMinMax = encoder_thresholds;
    RGBEncoder.onFadeProcess = encoder_fade;
    RGBEncoder.onButtonDoublePush = encoder_doubleclick;

    /* Enable the I2C Encoder V2 interrupts according to the previus attached callback */
    RGBEncoder.autoconfigInterrupt();

    RGBEncoder.writeCounter((int32_t)ENCODER_DEFAULT);
    RGBEncoder.writeMax((int32_t)ENCODER_MAX);
    RGBEncoder.writeMin((int32_t)ENCODER_MIN);
    RGBEncoder.writeStep((int32_t)ENCODER_STEP);
}

void readEncoders()
{
    uint8_t enc_cnt;

    if (digitalRead(I2C_INT_PIN) == LOW)
    {
        if (digitalRead(I2C_INT_PIN) == HIGH)
        { // If the interrupt pin return high, exit from the encoder scan
            return;
        }
        RGBEncoder.updateStatus();
    }
}

void encoder_rotated(i2cEncoderLibV2 *obj)
{
    encoderColorFeedback(obj, ROTATE);
    if (obj->readStatus(i2cEncoderLibV2::RINC))
        Serial.print("Increment ");
    else
        Serial.print("Decrement ");
    // processRotary(obj->id, obj->readCounterInt());
}

void encoder_click(i2cEncoderLibV2 *obj)
{
    encoderColorFeedback(obj, CLICK);
    // processPush(obj->id, obj->readCounterInt());
    Serial.print("Push: ");
    Serial.println(obj->id);
}

void encoder_doubleclick(i2cEncoderLibV2 *obj)
{
    Serial.print("Double Push: ");
    Serial.println(obj->id);
}

void encoder_thresholds(i2cEncoderLibV2 *obj)
{
    encoderColorFeedback(obj, LIMIT);
    if (obj->readStatus(i2cEncoderLibV2::RMAX))
        Serial.print("Max: ");
    else
        Serial.print("Min: ");
    Serial.println(obj->id);
}

void encoder_fade(i2cEncoderLibV2 *obj)
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