//------------------------------------------------------------------------
// Copyright(c) 2025 My Plug-in Company.
//------------------------------------------------------------------------

#include "controller.h"
#include "cids.h"
#include "pluginterfaces/base/funknown.h"
#include "processor.h"


using namespace Steinberg;

namespace MyCompanyName {

	//------------------------------------------------------------------------
	// vst_organController Implementation
	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organController::initialize(FUnknown* context)
	{
		// Here the Plug-in will be instantiated

		//---do not forget to call parent ------
		tresult result = EditControllerEx1::initialize(context);
		if (result != kResultOk)
		{
			return result;
		}

		// Here you could register some parameters
			//---Create Parameters------------
		parameters.addParameter(STR16("Gain"), STR16("dB"), 0, .5, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamGainId, 0);

		//parameters for harmonics control
		parameters.addParameter(STR16("16'"), STR16("dB"), 0, 1, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc1Id, 0);
		parameters.addParameter(STR16("5 1/3'"), STR16("dB"), 0, 1, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc2Id, 0);
		parameters.addParameter(STR16("8'"), STR16("dB"), 0, 1, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc3Id, 0);
		parameters.addParameter(STR16("4'"), STR16("dB"), 0, 0, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc4Id, 0);
		parameters.addParameter(STR16("2 2/3'"), STR16("dB"), 0, 0, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc5Id, 0);
		parameters.addParameter(STR16("2'"), STR16("dB"), 0, 0, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc6Id, 0);
		parameters.addParameter(STR16("1 3/5'"), STR16("dB"), 0, 0, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc7Id, 0);
		parameters.addParameter(STR16("1 1/3'"), STR16("dB"), 0, 0, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc8Id, 0);
		parameters.addParameter(STR16("1'"), STR16("dB"), 0, 0, Steinberg::Vst::ParameterInfo::kCanAutomate, GainParams::kParamOsc9Id, 0);

		//read default parameters

		//voices
	//for each voice
		//for (int v = 0; v < MAX_VOICES; v++) {

		//	auto* param = parameters.getParameter(kParamOsc1Id);

		//	voices[v].levels[0] = GainParams::kParamOsc1Id; //set the oscillator level reading the current parameter value
		//}

		return result;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organController::terminate()
	{
		// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

		//---do not forget to call parent ------
		return EditControllerEx1::terminate();
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organController::setComponentState(IBStream* state)
	{
		// Here you get the state of the component (Processor part)
		if (!state)
			return kResultFalse;

		return kResultOk;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organController::setState(IBStream* state)
	{
		// Here you get the state of the controller

		return kResultTrue;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API vst_organController::getState(IBStream* state)
	{
		// Here you are asked to deliver the state of the controller (if needed)
		// Note: the real state of your plug-in is saved in the processor

		return kResultTrue;
	}

	//------------------------------------------------------------------------
	IPlugView* PLUGIN_API vst_organController::createView(FIDString name)
	{
		// Here the Host wants to open your editor (if you have one)
		if (FIDStringsEqual(name, Vst::ViewType::kEditor))
		{
			// create your editor here and return a IPlugView ptr of it
			return nullptr;
		}
		return nullptr;
	}

	//------------------------------------------------------------------------
} // namespace MyCompanyName
