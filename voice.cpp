#include "voice.h";
#include "frequency_tables.h"
#include <windows.h>
#include <string>



void Voice::NoteOn(int midiNoteNumber) {
	noteNumber = midiNoteNumber;
	active = true;
	OutputDebugStringA(("Voice 1 set pitch" + std::to_string(midiNoteNumber) + "\n").c_str());



		osc1.setFrequency(freqTable1[midiNoteNumber]);
		osc2.setFrequency(freqTable2[midiNoteNumber]);
		osc3.setFrequency(freqTable3[midiNoteNumber]);
		osc4.setFrequency(freqTable4[midiNoteNumber]);
		osc5.setFrequency(freqTable5[midiNoteNumber]);
		osc6.setFrequency(freqTable6[midiNoteNumber]);
		osc7.setFrequency(freqTable7[midiNoteNumber]);
		osc8.setFrequency(freqTable8[midiNoteNumber]);
		osc9.setFrequency(freqTable9[midiNoteNumber]);
}

void Voice::NoteOff() {
	active = false;
	noteNumber = -1;

}

float Voice::GetSample() {

	//OutputDebugStringA("Voice 1 get sample");

	//call osc.process and compute resulting sample to be returned
	if (!active) return 0.0f; //note off
	return (
		osc1.process() +
		osc2.process() +
		osc3.process() +
		osc4.process() +
		osc5.process() +
		osc6.process() +
		osc7.process() +
		osc8.process() +
		osc9.process()) * 0.1;
}