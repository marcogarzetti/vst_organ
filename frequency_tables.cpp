
#include "frequency_tables.h"
#include <windows.h>
#include <string>

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
	float c0 = 16.35; //frequency of the C0 note
	float k = 1.059463094359; //frequency multiplier for semitone

	for (int i = 0;i < 128;i++)
	{
		//index frequencies for the 9 harmonics - for 128 notes
		freqTable1[i] = c0;
		freqTable2[i] = c0 * 3;
		freqTable3[i] = c0 * 2;
		freqTable4[i] = c0 * 4;
		freqTable5[i] = c0 * 6;
		freqTable6[i] = c0 * 8;
		freqTable7[i] = c0 * 10;
		freqTable8[i] = c0 * 12;
		freqTable9[i] = c0 * 16;

		c0 *= k; //increase by one semitone
	}
}