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
    SPEED,
    ROTATION,
    PRESET,
} EncoderState;

#define I2C_SDA_PIN 23 // Choose your SDA pin
#define I2C_SCL_PIN 19 // Choose your SCL pin
#define I2C_INT_PIN 22 // Choose your INT pin

#define NUM_ENCODERS 1 // Number of encoders

#define ENC_ID 0
#define ENCODER_ADDRESS 0x28
#define ENCODER_MIN 0
#define ENCODER_MAX 254
#define ENCODER_STEP 1
#define ENCODER_DEFAULT 150

static i2cEncoderLibV2 RGBEncoder[NUM_ENCODERS] = {i2cEncoderLibV2(ENCODER_ADDRESS)};

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