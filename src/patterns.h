#ifndef PATTERNS_H
#define PATTERNS_H

// A couple function prototypes
// void changePalette();
// Task _taskChangePalette(SECONDS_PER_PALETTE *TASK_SECOND, TASK_FOREVER, &changePalette);

// system procedures_____________________________________

#include <Arduino.h>
#include <FastLED.h>

#include "splendidanew.h"

extern SimplePatternList gPatterns;

void SoftTwinkles();
void cylindrical_Pattern();
void FireComets();
void hypnoticWaves();
void testCylinderMapping2();
void DiagonalPattern();
void hypnoticSpiral();
void spiralCylinderWave();
void PlasmaBall(); // F_lying,  // I don't like it enough.
void RGBTunnel();
void Flower();
void Distortion_Waves_cylinder();
void colorwaves();
void Distortion_Waves_planar();
void FireButterfly();
void Spiral2();
void pride();
void RGB_Caleidoscope2();
void RGB_Caleidoscope1();
void Swirl();
void RGB_hiphotic();
void Spiral();
void DigitalRain();
void fire2021();

void balls();
void raininit();
void updaterain();
void changepattern();

#endif