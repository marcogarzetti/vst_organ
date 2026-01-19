#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


constexpr double PI = 3.14159265358979323846;


// Simple oscillator class
class Oscillator {
public:
	void setSampleRate(double sr);
	void setFrequency(double freq);
    void reset(); //reset phase
	float process();

private:
    double sampleRate; // = 44100.0;   // default
    double frequency = 440.0;      // default (A4)
    double phase = 0.0;
    double increment = (2.0 * PI * frequency) / sampleRate;
};