//------------------------------------------------------------------------
// Copyright(c) 2025 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "oscillator.h"
#include "voice.h"

static constexpr int MAX_VOICES = 8;

namespace MyCompanyName {

	//------------------------------------------------------------------------
	//  vst_organProcessor
	//------------------------------------------------------------------------
	class vst_organProcessor : public Steinberg::Vst::AudioEffect
	{
	public:
		vst_organProcessor();
		~vst_organProcessor() SMTG_OVERRIDE;

		//declare frequency tables and oscillators
	public:
		static float freqTable[128]; //old
		static Oscillator osc1; //old
		Voice voices[MAX_VOICES];
		float notes[128];

		//declare parameters
	public:
		Steinberg::Vst::ParamValue mGain = 1.;

		int GetFirstAvailableVoice();

		//static void CreateFrequencyTable();

		// Create function
		static Steinberg::FUnknown* createInstance(void* /*context*/)
		{
			return (Steinberg::Vst::IAudioProcessor*)new vst_organProcessor;
		}

		//--- ---------------------------------------------------------------------
		// AudioEffect overrides:
		//--- ---------------------------------------------------------------------
		/** Called at first after constructor */
		Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;

		/** Called at the end before destructor */
		Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;

		/** Switch the Plug-in on/off */
		Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) SMTG_OVERRIDE;

		/** Will be called before any process call */
		Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;

		/** Asks if a given sample size is supported see SymbolicSampleSizes. */
		Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

		/** Here we go...the process call */
		Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;

		/** For persistence */
		Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
		Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

		//------------------------------------------------------------------------

	};

	//------------------------------------------------------------------------
} // namespace MyCompanyName
