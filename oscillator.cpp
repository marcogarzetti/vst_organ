#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "oscillator.h"

#include <windows.h>
#include <string>

//constexpr double PI = 3.14159265358979323846;


	void Oscillator::setSampleRate(double sr) {
		sampleRate = sr; OutputDebugStringA(("OScillator set sample rate " + std::to_string(sr) + "\n").c_str());
	}
	void Oscillator::setFrequency(double freq) {
		OutputDebugStringA(("OScillator set frequency " + std::to_string(freq) + "\n").c_str());
		frequency = freq; increment = (2.0 * PI * frequency) / sampleRate;
	}

	float Oscillator::process() {
		phase += increment;
		if (phase >= 2.0 * PI) phase -= 2.0 * PI; //at the end of the cycle, reset phase and restart
		return sinf(phase);
	}


	//sampleRate = 44100.0; //todo: get sample rate from host
	//frequency;
	//phase = 0.0;
	//increment = (2.0 * PI * frequency) / sampleRate;
