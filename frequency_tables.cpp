//------------------------------------------------------------------------
// Copyright(c) 2025 Marco Garzetti.
//------------------------------------------------------------------------

#include "frequency_tables.h"
#include <windows.h>
#include <string>

namespace OrganPlugin {
	float freqTable1[128];
	float freqTable2[128];
	float freqTable3[128];
	float freqTable4[128];
	float freqTable5[128];
	float freqTable6[128];
	float freqTable7[128];
	float freqTable8[128];
	float freqTable9[128];

	void CreateFrequencyTables()
	{
		OutputDebugStringA("Create frequency tables");
		float midiNoteZero = 8.1758; //frequency of the MIDI note 0 note
		float k = 1.059463094359; //frequency multiplier for semitone

		for (int i = 0;i < 128;i++)
		{
			//index frequencies for the 9 harmonics - for 128 notes
			freqTable1[i] = midiNoteZero;
			freqTable2[i] = midiNoteZero * 3;
			freqTable3[i] = midiNoteZero * 2;
			freqTable4[i] = midiNoteZero * 4;
			freqTable5[i] = midiNoteZero * 6;
			freqTable6[i] = midiNoteZero * 8;
			freqTable7[i] = midiNoteZero * 10;
			freqTable8[i] = midiNoteZero * 12;
			freqTable9[i] = midiNoteZero * 16;

			midiNoteZero *= k; //increase by one semitone
		}
	}
}
