//------------------------------------------------------------------------
// Copyright(c) 2025 Marco Garzetti.
//------------------------------------------------------------------------

#pragma once
#include "oscillator.h"

namespace OrganPlugin {
	class Voice {

		//voice: each voice has 9 oscillators for the harmonics of the organ
	public:
		Oscillator oscillators[9];
		float levels[9];

	public:
		Voice() {
			//default constructor
			for (int i = 0; i < 9; i++) {
				levels[i] = 0;
			}
		}

	public:
		bool active = false;
		int noteNumber = -1;
		double voiceSampleRate = 0;

	public:
		void NoteOn(int noteNumber); //activate the voice with the specified note
		void NoteOff(); //deactivate the voice
		float GetSample(); //called by the processor to get the current sample of the voice
		void SetSampleRate(double sampleRate); //called when the host sets the sample rate

		//for envelope smoothing (avoid clicks)
		float env = 0.0f;
		float envTarget = 0.0f;
		float envStep = 0.0f;
	};
}


