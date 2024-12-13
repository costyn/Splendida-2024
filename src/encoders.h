#ifndef ENCODERS_H
#define ENCODERS_H

#include <Arduino.h>
#include <i2cEncoderLibV2.h>
#include <Wire.h>

typedef enum
{
    ROTATE,
    LIMIT,
    CLICK
} EncoderEvent;

typedef enum
{
    BRIGHTNESS,
    BPM,
    ROTATION,
    PRESET,
} EncoderState;

#define I2C_SDA_PIN 19 // Choose your SDA pin
#define I2C_SCL_PIN 22 // Choose your SCL pin
#define I2C_INT_PIN 23 // Choose your INT pin

#define NUM_ENCODERS 1 // Number of encoders

#define ENC_BRIGHTNESS_ID 0
#define ENC_BRIGHTNESS_ADDRESS 0x20
#define ENC_BRIGHTNESS_NAME "brightness"
#define ENC_BRIGHTNESS_MIN 0
#define ENC_BRIGHTNESS_MAX 254
#define ENC_BRIGHTNESS_STEP 5
#define ENC_BRIGHTNESS_DEFAULT 150
#define ENC_BRIGHTNESS_CONFIRM false
#define ENC_BRIGHTNESS_PUSH "power"

static const String encoderNames[NUM_ENCODERS] PROGMEM = {ENC_BRIGHTNESS_NAME};
static const bool encoderConfirm[NUM_ENCODERS] PROGMEM = {ENC_BRIGHTNESS_CONFIRM};

// Class initialization with the I2C addresses
//  i2cEncoderLibV2 RGBEncoder[ENCODER_N] = { i2cEncoderLibV2(0x40),
//                                            i2cEncoderLibV2(0x20), i2cEncoderLibV2(0x60), i2cEncoderLibV2(0x10),
//                                            i2cEncoderLibV2(0x50), i2cEncoderLibV2(0x30), i2cEncoderLibV2(0x70),
//                                            i2cEncoderLibV2(0x04), i2cEncoderLibV2(0x44),
//  };

static i2cEncoderLibV2 RGBEncoder[NUM_ENCODERS] = {i2cEncoderLibV2(ENC_BRIGHTNESS_ADDRESS)};

void encoderSetup();
void readEncoders();

void encoder_rotated(i2cEncoderLibV2 *obj);
void encoder_click(i2cEncoderLibV2 *obj);
void encoder_thresholds(i2cEncoderLibV2 *obj);
void encoder_fade(i2cEncoderLibV2 *obj);
void encoder_doubleclick(i2cEncoderLibV2 *obj);
void encoderColorFeedback(i2cEncoderLibV2 *obj, EncoderEvent event);

void setPreset(int presetIndex);
void setBrightness(int brightness);

#endif