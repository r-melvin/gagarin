// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x55AF60).
//   Every global address reconfirmed below from the absolute-load operands;
//   names cross-checked against YRpp.
//
// reccmp annotation:
//   FUNCTION: GAMEMD 0x55AF60  Detail::GetMinFrameRate  (__cdecl)
//   GLOBAL:   GAMEMD 0x829FF4  Detail::MinFrameRate
//   GLOBAL:   GAMEMD 0x829FF8  Detail::BufferZoneWidth
//   GLOBAL:   GAMEMD 0xABCD44  FPSCounter::CurrentFrameRate
//   GLOBAL:   GAMEMD 0xABCD50  FPSCounter::ReducedEffects

#include "fps_counter_methods.h"

// Engine globals (absolute loads in 0x55AF60). The differ normalises the
// relocations on these memory operands.
extern unsigned int MinFrameRate;             // GAMEMD 0x829FF4
extern unsigned int BufferZoneWidth;          // GAMEMD 0x829FF8
extern unsigned int FPSCounter_CurrentFrameRate; // GAMEMD 0xABCD44
extern bool         FPSCounter_ReducedEffects;   // GAMEMD 0xABCD50

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x55AF60  (__cdecl)
// The minimum frame rate with hysteresis. When effects are NOT reduced, the
// threshold is MinFrameRate; dropping below it latches ReducedEffects and
// raises the threshold by BufferZoneWidth. When effects ARE reduced, the
// (higher) threshold MinFrameRate+BufferZoneWidth must be reached to unlatch.
// ---------------------------------------------------------------------------
unsigned int Detail::GetMinFrameRate()
{
	if (FPSCounter_ReducedEffects) {
		unsigned int threshold = BufferZoneWidth + MinFrameRate;
		if (FPSCounter_CurrentFrameRate < threshold)
			return threshold;
		FPSCounter_ReducedEffects = false;
		return MinFrameRate;
	}

	if (FPSCounter_CurrentFrameRate < MinFrameRate) {
		FPSCounter_ReducedEffects = true;
		return MinFrameRate + BufferZoneWidth;
	}
	return MinFrameRate;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABCD44
unsigned int FPSCounter_CurrentFrameRate;
// GLOBAL: GAMEMD 0xABCD50
bool FPSCounter_ReducedEffects;
// GLOBAL: GAMEMD 0x829FF4
unsigned int MinFrameRate = 0xF;
// GLOBAL: GAMEMD 0x829FF8
unsigned int BufferZoneWidth = 5;
// END defined globals
