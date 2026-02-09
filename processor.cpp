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



//| Situation		 | How you receive parameters              |
//| -------------- - | -------------------------------------- -|
//| User moves knob  | `process()` via `inputParameterChanges` |
//| Plugin loads	 | **`setState()`**						   |
//| Preset loads	 | **`setState()`**						   |
//| Project reopens  | **`setState()`**						   |


using namespace Steinberg;

namespace OrganPlugin {
	//------------------------------------------------------------------------
	// vst_organProcessor
	//------------------------------------------------------------------------

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

		//create frequency tables and populate with values
		CreateFrequencyTables();

		//initialize default gain and drawbars

		//master gain
		mGain = 0.5;

		//drawbars
		float drawbars[9];

		drawbars[0] = 1.0;
		drawbars[1] = 1.0;
		drawbars[2] = 1.0;
		drawbars[3] = 0.0;
		drawbars[4] = 0.0;
		drawbars[5] = 0.0;
		drawbars[6] = 0.0;
		drawbars[7] = 0.0;
		drawbars[8] = 0.0;

		// apply to voices
		for (int v = 0; v < MAX_VOICES; ++v)
			for (int o = 0; o < 9; ++o)
				voices[v].levels[o] = drawbars[o];

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

							//master gain				
							mGain = value;
						}
						break;

						//gains for harmonics (oscillators) of the voices
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
						int32 noteNumber = event.noteOn.pitch;

						//get the first available voice (not assigned to a note)
						int freeVoice = GetFirstAvailableVoice();
						OutputDebugStringA(("First available voice: " + std::to_string(freeVoice) + "\n").c_str());

						//voice on
						voices[freeVoice].NoteOn(noteNumber);
						OutputDebugStringA(("NoteOn received - noteId = " + std::to_string(noteNumber) + "assigned voice: " + std::to_string(freeVoice) + "\n").c_str());

						break;
					}

					//----------------------
					case Vst::Event::kNoteOffEvent:
					{
						int32 noteNumber = event.noteOn.pitch;

						OutputDebugStringA(("NoteOff received - noteId = " + std::to_string(noteNumber) + "\n").c_str());

						//get the voice assigned to the note
						int voicesAssignedToNote[MAX_VOICES];
						int count = GetVoicesAssignedToNote(noteNumber, voicesAssignedToNote);

						//send note off to all the voices assigned to the note
						for (int i = 0; i < count; i++) {
							int voiceNumber = voicesAssignedToNote[i];

							//voice off
							if (voiceNumber >= 0) //if a voice is assigned to the note
							{
								voices[voiceNumber].NoteOff();
							}
						}
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
				float sample = 0;

				//sum the samples of the voices
				for (int i = 0; i < MAX_VOICES; i++) {
					sample += voices[i].GetSample();
				}
				outputs[0][i] = sample * mGain; // left
				outputs[1][i] = sample * mGain; // right
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

	int vst_organProcessor::GetVoicesAssignedToNote(int noteNumber, int* outIndices)
	{
		int count = 0;

		for (int i = 0; i < MAX_VOICES && count < MAX_VOICES; i++) {
			if (voices[i].noteNumber == noteNumber) {
				outIndices[count++] = i;
			}
		}

		return count; //number of voices found
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organProcessor::setupProcessing(Vst::ProcessSetup& newSetup)
	{
		//get sample frequency from host and set voices sample rate. If the sample rate is changed in the host this cycle will be executed to set the new sample rate for the voices
		for (int i = 0; i < MAX_VOICES; i++) {
			voices[i].SetSampleRate(newSetup.sampleRate);
		}
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

} // namespace OrganPlugin
