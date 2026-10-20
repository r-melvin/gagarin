// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals + control flow derived from the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI (absolute-load disassembly at 0x55AF60), cross-checked
//   against YRpp FPSCounter.h (consult-only, no LICENSE; every global address
//   reconfirmed from the disasm).
//
// FPSCounter / Detail static helpers. Only Detail::GetMinFrameRate is matched;
// it touches four engine globals (no instance state — a free __cdecl routine):
//   GLOBAL: GAMEMD 0x829FF4  Detail::MinFrameRate        (unsigned int)
//   GLOBAL: GAMEMD 0x829FF8  Detail::BufferZoneWidth     (unsigned int)
//   GLOBAL: GAMEMD 0xABCD44  FPSCounter::CurrentFrameRate(unsigned int)
//   GLOBAL: GAMEMD 0xABCD50  FPSCounter::ReducedEffects  (bool)
#ifndef GG_MATCH_CORE_FPS_COUNTER_METHODS_H
#define GG_MATCH_CORE_FPS_COUNTER_METHODS_H

struct Detail
{
	static unsigned int GetMinFrameRate();
};

#endif // GG_MATCH_CORE_FPS_COUNTER_METHODS_H
