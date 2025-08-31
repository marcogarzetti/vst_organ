//------------------------------------------------------------------------
// Copyright(c) 2025 My Plug-in Company.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h" //for helper functions

#include <windows.h>

#include "frequency_tables.h"
#include "voice.h"



//#include "oscillator.h"

using namespace Steinberg;

namespace MyCompanyName {
	//------------------------------------------------------------------------
	// vst_organProcessor
	//------------------------------------------------------------------------

	//Oscillator osc1;
	//float freqTable[128];
	//float vst_organProcessor::freqTable[128];
	//Oscillator vst_organProcessor::osc1;

	//void vst_organProcessor::CreateFrequencyTable()
	//{
	//	float c0 = 16.35;
	//	float k = 1.059463094359;

	//	for (int i = 0;i < 128;i++)
	//	{
	//		vst_organProcessor::freqTable[i] = c0;
	//		c0 *= k;
	//	}
	//}

	vst_organProcessor::vst_organProcessor()
	{
		//--- set the wanted controller for our processor
		setControllerClass(kvst_organControllerUID);
	}

	//------------------------------------------------------------------------
	vst_organProcessor::~vst_organProcessor()
	{
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::initialize(FUnknown* context)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		std::cout << "Debug message" << std::endl;
		OutputDebugStringA("Debug message\n");

		// Here the Plug-in will be instantiated

		//---always initialize the parent-------
		tresult result = AudioEffect::initialize(context);
		// if everything Ok, continue
		if (result != kResultOk)
		{
			return result;
		}

		//--- create Audio IO ------
		// addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
		addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

		/* If you don't need an event bus, you can remove the next line */
		addEventInput(STR16("Event In"), 1);

		//CreateFrequencyTable(); //old
		CreateFrequencyTables(); //new


		return kResultOk;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::terminate()
	{
		// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

		//---do not forget to call parent ------
		return AudioEffect::terminate();
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::setActive(TBool state)
	{
		//--- called when the Plug-in is enable/disable (On/Off) -----
		return AudioEffect::setActive(state);
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::process(Vst::ProcessData& data)
	{
		//osc1.setFrequency(1000);
		//osc1.setFrequency(500);
		//--- First : Read inputs parameter changes-----------
		if (data.inputParameterChanges)
		{
			// for each parameter defined by its ID
			int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
			for (int32 index = 0; index < numParamsChanged; index++)
			{
				// for this parameter we could iterate the list of value changes (could 1 per audio block or more!)
				// in this example, we get only the last value (getPointCount - 1)
				Vst::IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
				if (paramQueue)
				{
					Vst::ParamValue value;
					int32 sampleOffset;
					int32 numPoints = paramQueue->getPointCount();


					switch (paramQueue->getParameterId())
					{
						//gain
					case GainParams::kParamGainId:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
							mGain = value * 10;

							//master gain
						}
						break;
					case GainParams::kParamOsc1Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 1 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[0] = value;
							}
						}
						break;
					case GainParams::kParamOsc2Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[1] = value;
							}
						}
						break;
					case GainParams::kParamOsc3Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[2] = value;
							}
						}
						break;
					case GainParams::kParamOsc4Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[3] = value;
							}
						}
						break;
					case GainParams::kParamOsc5Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[4] = value;
							}
						}
						break;
					case GainParams::kParamOsc6Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[5] = value;
							}
						}
						break;
					case GainParams::kParamOsc7Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[6] = value;
							}
						}
						break;
					case GainParams::kParamOsc8Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[7] = value;
							}
						}
						break;
					case GainParams::kParamOsc9Id:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {

							//set the level of oscillator 2 for all the voices
							for (int i = 0; i < MAX_VOICES; i++) {
								voices[i].levels[8] = value;
							}
						}
						break;
					}
				}
			}
		}

		// ....

		//---Second: Read input events-------------
		// get the list of all event changes
		Vst::IEventList* eventList = data.inputEvents;
		if (eventList)
		{


			int32 numEvent = eventList->getEventCount();
			for (int32 i = 0; i < numEvent; i++)
			{
				Vst::Event event;
				if (eventList->getEvent(i, event) == kResultOk)
				{
					// here we do not take care of the channel info of the event
					switch (event.type)
					{
						//----------------------
					case Vst::Event::kNoteOnEvent:
						// use the velocity as gain modifier: a velocity max (1) will lead to silent audio
						//mGainReduction = event.noteOn.velocity; // value between 0 and 1
					{
						int32 pitch = event.noteOn.pitch;
						//osc1.setFrequency(freqTable[pitch]); //old

						int freeVoice = GetFirstAvailableVoice();
						OutputDebugStringA(("First available voice: " + std::to_string(freeVoice) + "\n").c_str());

						//assign the free voice to the note
						notes[pitch] = freeVoice;

						//get the voice assigned to the note
						int assignedVoice = notes[pitch];

						//voice on
						voices[assignedVoice].NoteOn(pitch); //new
						OutputDebugStringA(("NoteOn received - noteId = " + std::to_string(pitch) + "\n").c_str());

						break;
					}


					//----------------------
					case Vst::Event::kNoteOffEvent:
					{
						// noteOff reset the gain modifier
	//mGainReduction = 0.f;
	//outputs[0][i] = 0;
						int32 pitch = event.noteOn.pitch;
						//osc1.setFrequency(0); //old

						//get the voice assigned to the note
						int assignedVoice = notes[pitch];

						//voice off
						voices[assignedVoice].NoteOff(); //new
						OutputDebugStringA(("NoteOn received - noteId = " + std::to_string(pitch) + "\n").c_str());
						break;
					}

					}
				}
			}
		}


		//--- Here you have to implement your processing
		//oscillator 1 play
		if (data.numSamples > 0)
		{
			float** outputs = data.outputs[0].channelBuffers32;
			int32 numSamples = data.numSamples;

			//output oscillator samples
			for (int i = 0; i < numSamples; i++) {
				//float sample = osc1.process();
				//outputs[0][i] = sample*0.5;   // left
				////	//outputs[1][i] = sample;   // right
				float sample = 0;

				//sum the samples of the voices
				for (int i = 0; i < MAX_VOICES; i++) {
					sample += voices[i].GetSample();
				}
				outputs[0][i] = sample * 0.2;
			}
		}

		return kResultOk;
	}

	int vst_organProcessor::GetFirstAvailableVoice() {
		for (int i = 0; i < MAX_VOICES; i++) {
			if (!voices[i].active) {
				return i;
			}
		}
		return -1;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::setupProcessing(Vst::ProcessSetup& newSetup)
	{
		//--- called before any processing ----
		return AudioEffect::setupProcessing(newSetup);
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::canProcessSampleSize(int32 symbolicSampleSize)
	{
		// by default kSample32 is supported
		if (symbolicSampleSize == Vst::kSample32)
			return kResultTrue;

		// disable the following comment if your processing support kSample64
		/* if (symbolicSampleSize == Vst::kSample64)
			return kResultTrue; */

		return kResultFalse;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::setState(IBStream* state)
	{
		// called when we load a preset, the model has to be reloaded
		IBStreamer streamer(state, kLittleEndian);

		return kResultOk;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::getState(IBStream* state)
	{
		// here we need to save the model
		IBStreamer streamer(state, kLittleEndian);

		return kResultOk;
	}

	//------------------------------------------------------------------------



} // namespace MyCompanyName
