// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x410960.

#include "small_misc50_methods.h"

// FUNCTION: GAMEMD 0x410960
//
// The flag byte is read and its address taken before the four vtable stores,
// which is why retail's `MOV AL,[ESI+0x3D]` and `LEA ECX,[ESI+0x3D]` sit ahead
// of them even though the branch on that byte comes afterwards.
Obj_00410960* Obj_00410960::FUN_00410960(int value)
{
    FUN_004101C0(value);

    vt0 = &VT_007E2000;
    vt1 = &VT_007E1FE4;
    vt2 = &VT_007E1FDC;
    vt3 = &VT_007E1FD4;

    if (Registered) {
        Block = FUN_00734E60(&Registered, 0, STR_00817830, 0x7F);

        return this;
    }

    Block = &DAT_00887734;

    return this;
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

// FUNCTION: GAMEMD 0x44FE60
void __fastcall FUN_0044FE60(Ini_0044FE60* ini)
{
    ini->FUN_005257C0(DAT_007E3E88, 0);

    for (int i = 0; i < DAT_00A8EB50; i++) {
        Entry_0044FE60* entry = DAT_00A8EB44[i];

        if (!entry->Skip && !entry->Settings->Skip) {
            entry->FUN_0044FEC0(ini);
        }
    }
}

// FUNCTION: GAMEMD 0x45E520
Obj_0045E520* Obj_0045E520::FUN_0045E520(int value)
{
    FUN_00711840(value);

    field_E00  = 0;
    field_1788 = 0;
    field_178C = 0;
    // Pinned: the only store whose value does not come from the shared zero, so
    // plainly written VC6 lifts it ahead of the other four.
    *(volatile char*)&field_1790 = 1;
    field_1791 = 0;

    Secondary = &VT_007E4638;

    vt0 = &VT_007E4570;
    vt1 = &VT_007E4554;
    vt2 = &VT_007E454C;
    vt3 = &VT_007E4544;

    return this;
}
