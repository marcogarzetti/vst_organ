//------------------------------------------------------------------------
// Copyright(c) 2025 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace OrganPlugin {
	//------------------------------------------------------------------------
	static const Steinberg::FUID kvst_organProcessorUID(0x071356C8, 0x4B9853A9, 0xABD92440, 0x0912FBFA);
	static const Steinberg::FUID kvst_organControllerUID(0x75F6A637, 0x1C6B5B69, 0xA18830F9, 0xDE8B8EF4);

#define vst_organVST3Category "Instrument"

	//define parameters
	enum GainParams : Steinberg::Vst::ParamID
	{
		kParamGainId = 100, // should be a unique id...

		//oscillators gains
		kParamOsc1Id = 101,
		kParamOsc2Id = 102,
		kParamOsc3Id = 103,
		kParamOsc4Id = 104,
		kParamOsc5Id = 105,
		kParamOsc6Id = 106,
		kParamOsc7Id = 107,
		kParamOsc8Id = 108,
		kParamOsc9Id = 109,

	};
	//------------------------------------------------------------------------
} // namespace OrganPlugin
