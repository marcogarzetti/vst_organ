#pragma once
#include "oscillator.h"

class Voice {

public: 
	//Oscillator osc1;
	//Oscillator osc2;
	//Oscillator osc3;
	//Oscillator osc4;
	//Oscillator osc5;
	//Oscillator osc6;
	//Oscillator osc7;
	//Oscillator osc8;
	//Oscillator osc9;
	Oscillator oscillators[9];

public:
	Voice() {
		//default constructor

		for (int i = 0; i < 9; i++) {
			oscillators[i].setSampleRate(44100);
		}
		//osc1.setSampleRate(44100);
		//osc2.setSampleRate(44100);
		//osc3.setSampleRate(44100);
		//osc4.setSampleRate(44100);
		//osc5.setSampleRate(44100);
		//osc6.setSampleRate(44100);
		//osc7.setSampleRate(44100);
		//osc8.setSampleRate(44100);
		//osc9.setSampleRate(44100);
	}

public:
	bool active = false;
	int noteNumber = -1;

public:
	void NoteOn(int noteNumber);
	void NoteOff();
	float GetSample();
};


