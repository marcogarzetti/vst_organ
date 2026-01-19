#include "voice.h";
#include "frequency_tables.h"
#include <windows.h>
#include <string>



void Voice::NoteOn(int midiNoteNumber) {
	noteNumber = midiNoteNumber;
	active = true;

	// reset phase
    for (int i = 0; i < 9; i++)
        oscillators[i].reset();

	OutputDebugStringA(("Voice 1 set pitch" + std::to_string(midiNoteNumber) + "\n").c_str());

	//envelope smoothing to avoid click
	env = 0.0f;
	envTarget = 1.0f;
	envStep = 1.0f / (0.005f * 44100); // 5 ms attack

	oscillators[0].setFrequency(freqTable1[midiNoteNumber]);
	oscillators[1].setFrequency(freqTable2[midiNoteNumber]);
	oscillators[2].setFrequency(freqTable3[midiNoteNumber]);
	oscillators[3].setFrequency(freqTable4[midiNoteNumber]);
	oscillators[4].setFrequency(freqTable5[midiNoteNumber]);
	oscillators[5].setFrequency(freqTable6[midiNoteNumber]);
	oscillators[6].setFrequency(freqTable7[midiNoteNumber]);
	oscillators[7].setFrequency(freqTable8[midiNoteNumber]);
	oscillators[8].setFrequency(freqTable9[midiNoteNumber]);
		//osc1.setFrequency(freqTable1[midiNoteNumber]);
		//osc2.setFrequency(freqTable2[midiNoteNumber]);
		//osc3.setFrequency(freqTable3[midiNoteNumber]);
		//osc4.setFrequency(freqTable4[midiNoteNumber]);
		//osc5.setFrequency(freqTable5[midiNoteNumber]);
		//osc6.setFrequency(freqTable6[midiNoteNumber]);
		//osc7.setFrequency(freqTable7[midiNoteNumber]);
		//osc8.setFrequency(freqTable8[midiNoteNumber]);
		//osc9.setFrequency(freqTable9[midiNoteNumber]);
}

void Voice::NoteOff() {
	//active = false;
	noteNumber = -1;

	//envelope smoothing to avoid clicks
	envTarget = 0.0f;
	envStep = 1.0f / (0.02f * 44100); // 20 ms release
}

float Voice::GetSample() {

	//OutputDebugStringA("Voice 1 get sample");

	float sample = 0;
	for (int i = 0; i < 9; i++) {
		sample += (oscillators[i].process() * levels[i]); //each oscillator has a different level
	}
	//call osc.process and compute resulting sample to be returned
	if (!active) return 0.0f; //note off
	//return (
	//	osc1.process() +
	//	osc2.process() +
	//	osc3.process() +
	//	osc4.process() +
	//	osc5.process() +
	//	osc6.process() +
	//	osc7.process() +
	//	osc8.process() +
	//	osc9.process()) * 0.1;

	  // normalize level based on number of oscillators
		sample /= static_cast<float>(9);
	
		// envelope smoothing
		if (env < envTarget)
		{
			env += envStep;
			if (env > envTarget) env = envTarget;
		}
		else if (env > envTarget)
		{
			env -= envStep;
			if (env < envTarget) env = envTarget;
		}

		sample *= env;

		//deactivate voice only when level reached 0
		if (env <= 0.00001f)
		{
			active = false;
			noteNumber = -1;
			return 0.0f;
		}

		return sample;
}