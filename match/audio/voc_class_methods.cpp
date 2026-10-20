// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Name cross-checked
//   against YRpp VocClass.h (consult-only; reconfirmed from the disassembly).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x007514D0  VocClass::FindIndex  (__fastcall, static)

#include "voc_class_methods.h"

// Retail _stricmp (0x007C8D20). cdecl; declared (no body) so cl emits a call.
extern "C" int __cdecl gg_voc_stricmp(const char* a, const char* b);

// FUNCTION: GAMEMD 0x007514D0  (__fastcall, static)
// Return the index of the Array entry whose audio-event name matches pName
// (case-insensitive), or -1 when pName is null / no entry matches.
int __fastcall VocClass::FindIndex(const char* pName)
{
    if (pName)
    {
        for (int i = 0; i < VocClass_Array.Count; ++i)
        {
            // Reference item->Event twice (the null test and the call) so cl
            // keeps `item` anchored in EAX and CSE-loads Event once into ECX,
            // matching retail's `mov eax,[eax+esi*4]; mov ecx,[eax]` pairing
            // (verified byte-for-byte; a single anchored event-pointer load).
            VocItem* item = ((VocItem**)VocClass_Array.Items)[i];
            const char* name = item->Event ? item->Event->GetName() : "Invalid Voc";
            if (gg_voc_stricmp(pName, name) == 0)
                return i;
        }
    }
    return -1;
}
