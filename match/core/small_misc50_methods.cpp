// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x410960.

#include "small_misc50_methods.h"

#include "../_layout/abstract_type_class.h"
// GLOBAL: GAMEMD 0x887734
extern const wchar_t DAT_00887734[];
// STRING: GAMEMD 0x817830
extern const char STR_00817830[];
// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
wchar_t* __fastcall StringTable_LoadString(const char*, int*, const char*, int);

// FUNCTION: GAMEMD 0x410960
AbstractTypeClass::AbstractTypeClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), ID(noInit), UINameLabel(noInit), Name(noInit)
{
    if (UINameLabel[0])
        UIName = StringTable_LoadString(UINameLabel, 0, STR_00817830, 0x7F);
    else
        UIName = DAT_00887734;
}

// FUNCTION: GAMEMD 0x4253B0
long __stdcall FUN_004253B0(AnimClass_004253B0* subject, void* second, void* third)
{
    void* key = subject->Key;

    // The two index stores are separate blocks but the forward is shared - the
    // found path jumps over the -1 store straight to the call - so this is one
    // `return` reached by a `goto`, not a `return` per branch. Duplicating the
    // call instead emits it twice and scores 61.5%.
    if (key) {
        for (int i = DAT_00B054E0 - 1; i >= 0; i--) {
            if (key == DAT_00B054D4[i]->Key) {
                subject->Index = i;

                goto forward;
            }
        }
    }

    subject->Index = -1;

forward:
    return FUN_00410320(subject, second, third);
}


// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x818CE8
extern const char STR_00818CE8[] = "Structures";
// GLOBAL: GAMEMD 0x818CE8
extern const char STR_00818CE8[];
// GLOBAL: GAMEMD 0x818CE8
extern const char STR_00818CE8[];
// END defined globals
