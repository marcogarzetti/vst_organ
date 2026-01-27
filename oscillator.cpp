#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "oscillator.h"
#include <windows.h>
#include <string>

//constexpr double PI = 3.14159265358979323846;

namespace OrganPlugin {
	void Oscillator::setSampleRate(double sr) {
		sampleRate = sr; OutputDebugStringA(("OScillator set sample rate " + std::to_string(sr) + "\n").c_str());
	}
	void Oscillator::setFrequency(double freq) {
		OutputDebugStringA(("OScillator set frequency " + std::to_string(freq) + "\n").c_str());
		frequency = freq; increment = (2.0 * PI * frequency) / sampleRate;
	}

	void Oscillator::reset() {
		//reset phase
		phase = 0.0;
	}

	float Oscillator::process() {
		//increment is the increment for each sample, this function is called for every sample, then the result will be the sin of the phase incremented by increment for each sample
		//the increment is calulated in oscillator.h according to frequency and sample rate

		phase += increment;
		if (phase >= 2.0 * PI) phase -= 2.0 * PI; //at the end of the cycle, reset phase and restart
		return sinf(phase); //sin function
	}
}

