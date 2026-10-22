// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x48DBE0 (Ghidra disasm).
//   Names cross-checked against YRpp (each
//   offset/address reconfirmed against the user's binary below).
//
// Translation unit: Theater::FindIndex — linear case-insensitive lookup of a
// theater by ID over the fixed 6-entry Theater::Array.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x48DBE0   Theater::FindIndex   (__fastcall)
//   GLOBAL:   GAMEMD 0x7E1B78   Theater::Array[6]    (0x70 stride; end 0x7E1E18)
//   LIBRARY:  GAMEMD 0x7C8D20   _stricmp             (CRT; reloc-normalised call)

#include "theater_methods.h"

// The fixed global array. Its address (0x7E1B78) and the end sentinel
// (&Array[6] == 0x7E1E18) are emitted as relocations and normalised by the
// differ; confirmed numerically from the 0x48DBE0 disassembly.
extern Theater Theater_Array[6];

// CRT case-insensitive compare @0x7C8D20 — declared (no body) so cl emits a
// reloc-normalised call rather than inlining an intrinsic.
extern "C" int __cdecl _stricmp(const char* s1, const char* s2);

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x48DBE0   Theater::FindIndex   (__fastcall)
//
// pName arrives in ECX (__fastcall). EBX=pName, EDI=index, ESI walks the array
// at 0x70 stride; on the first _stricmp==0 hit returns the index, else -1.
// ---------------------------------------------------------------------------
int __fastcall Theater::FindIndex(const char* pName)
{
    for (int i = 0; i < 6; ++i) {
        if (_stricmp(pName, Theater_Array[i].ID) == 0) {
            return i;
        }
    }
    return -1;
}
