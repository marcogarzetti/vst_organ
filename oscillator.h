//------------------------------------------------------------------------
// Copyright(c) 2025 Marco Garzetti.
//------------------------------------------------------------------------

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

namespace OrganPlugin {
	constexpr double PI = 3.14159265358979323846;

	//base oscillator class
	class Oscillator {
	public:
		void setSampleRate(double sr);
		void setFrequency(double freq);
		void reset(); //reset phase
		float process();

	private:
		double sampleRate = 0;
		double frequency = 440.0; // default
		double phase = 0.0;
		double increment = (2.0 * PI * frequency) / sampleRate; //increment for each sample
	};
}

