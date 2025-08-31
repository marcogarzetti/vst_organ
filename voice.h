#pragma once
#include "oscillator.h"

class Voice {

public: 
	Oscillator oscillators[9];
	float levels[9];

public:
	Voice() {
		//default constructor
		for (int i = 0; i < 9; i++) {
			oscillators[i].setSampleRate(44100);
			levels[i] = 0;
		}
	}

public:
	bool active = false;
	int noteNumber = -1;


public:
	void NoteOn(int noteNumber);
	void NoteOff();
	float GetSample();
};


