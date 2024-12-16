#ifndef SPLENDIDANEW_H
#define SPLENDIDANEW_H

// Splendida 256 NEW demoreel with palletes
// fastled fibonacci 256 leds demo
// Yaroslaw Turbin
// https://vk.com/ldirko
// https://www.reddit.com/user/ldirko/
// https://twitter.com/ldir_ko

// controls: from start automode is enable and patterns change in loop
// one g_patternButton click change pattern to next and automode is OFF
// double click change bright in loop 0..maxbright with 7 steps. not affect to Automode
// long press activate Automode ON

#define M5ATOM

#include <Arduino.h>
#include <FastLED.h>
#include <TaskScheduler.h> // Include TaskScheduler for Task definitions

#include "tables.h"
#include "palettes.h"
// #include "patterns.h"

// Emulator
#ifndef M5ATOM
#define DATA_PIN 26           // set your leds datapin   change to 32 for m5 atom lite
#define ATOMLED_PIN 19        // set your leds datapin   change to 27 for m5 atom lite
#define BUTTON_PIN_INPUT 16   // button pin              change to 39 for m5 atom lite
#define EXTRA_BUTTON_PIN 22   // button pin              change to 39 for m5 atom lite
#define BRIGHTNESS_POT_PIN 12 // Brightness potentiometer pin
#define SPEED_POT_PIN 13      // Speed potentiometer pin
#endif

// Atom Matrix M5
#ifdef M5ATOM
#define DATA_PIN 26    // set your leds datapin   change to 32 for m5 atom lite
#define ATOMLED_PIN 21 // set your leds datapin   change to 27 for m5 atom lite
#endif

#define LED_TYPE WS2812B // leds type
#define COLOR_ORDER GRB  // color order of leds

#define MAX_POWER_MILLIAMPS 800 // write here your power in milliamps. default i set 800 mA for safety
#define MAX_BRIGHTNESS 100      // max brightness of leds - will be limited by max power

#define NUM_COLS_PLANAR 20 // resolution of planar lookup table
#define NUM_ROWS_PLANAR 20 // resolution of planar lookup table
#define NUM_LEDS_PLANAR NUM_COLS_PLANAR *NUM_ROWS_PLANAR

#define NUM_COLS_CYLINDER 45 // resolution of cylindrical lookup table
#define NUM_ROWS_CYLINDER 11 // resolution of cinindrical lookup table
// #define NUM_LEDS_CYLINDER NUM_COLS_CILINDR *NUM_ROWS_CYLINDER

#define NUM_LEDS 256

#define MAX_ANIMATION_SPEED 0.4f
#define MIN_ANIMATION_SPEED -0.4f

// Animation Constants
#define SECONDS_PER_PALETTE 20
#define SECONDS_PER_PATTERN 60
#define BLEND_SPEED 16
#define BLEND_INTERVAL_MS 40

#define NUM_PATTERNS 25

typedef void (*SimplePatternList[])();

// Extern declarations of global variables
extern uint8_t g_targetBrightness;
extern uint8_t g_lastSafeIndex;
extern float g_animationSpeed;
extern CRGBPalette16 gCurrentPalette;
extern CRGBPalette16 gTargetPalette;
extern float g_timeAccumulator;
extern SimplePatternList gPatterns;
extern uint8_t gCurrentPatternNumber;
extern CRGB g_statusLed[];
extern byte g_patternInitNeeded;
extern uint8_t g_currentBrightness;
extern uint8_t g_fadeState;
extern CRGB leds[NUM_LEDS];
extern const char *patternNames[];
extern uint8_t gCurrentPaletteNumber;

extern uint8_t g_fadeStartBrightness;
extern uint8_t g_fadeTargetBrightness;
extern uint8_t g_fadeCurrentBrightness;

float fmap(float x, float a, float b, float c, float d);

enum FadeState
{
    FADE_NONE,
    FADING_OUT,
    FADING_IN
};

extern Scheduler _runner;
extern Task _taskChangeToBrightness;
extern Task _taskRunPattern;
extern Task _taskChangePalette;
extern Task _taskChangePattern;
extern Task _taskBlendPalette;
extern Task _taskFade;
extern Task _taskReadEncoders;

void changeToBrightness();
void runPattern();

void fadeOut();
void fadeIn();
std::string timeToString();

// Function Prototypes
void initializeGPIO();
void initializeSerial();
void initializeLEDs();
void initializeButton();
void printPatternAndPalette();
void readPotentiometers();
void handleButton();
void changePalette();
void blendPalette();
void changePattern();
void startFadeOut();
void startFadeIn();
void fade();

void readEncoders();
void encoderSetup();

#endif // SPLENDIDANEW_H