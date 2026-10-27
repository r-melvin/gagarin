// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   MapClass lifetime and member-layout facts are read from the retail v1.001
//   entries 0x5652C0 and 0x589BD0, the Map constructor tables at 0x565090 and
//   0x565190, and RTTI address points 0x7ED404, 0x7ED4C0, 0x7ED4A0,
//   0x7E3890, 0x7ED480, 0x7E38D0, and 0x7ED5A0.

#include "../core/pair_vector_ctor_family_methods.h"
#include "../ui/input_controls/ui_display_chain.h"

// These no-argument native helpers are called by MapClass::~MapClass in the
// observed order. The free-function convention is the project default /Gr.
void __fastcall FUN_0074D760();
void __fastcall FUN_0074E880();
void __fastcall FUN_00722390();
void __fastcall FUN_00722E50();

// FUNCTION: GAMEMD 0x5652C0
MapClass::~MapClass()
{
    FUN_0074D760();
    FUN_0074E880();
    FUN_00722390();
    FUN_00722E50();

    if (Words != 0) {
        ::operator delete(Words);
        Words = 0;
    }
    if (BucketsA != 0) {
        if (BucketsA->Items != 0)
            delete[] BucketsA->Items;
        ::operator delete(BucketsA);
        BucketsA = 0;
    }
    if (Records != 0) {
        ::operator delete(Records);
        Records = 0;
    }
    for (int i = 0; i != 3; ++i) {
        if (BucketsB[i] != 0) {
            if (BucketsB[i]->Items != 0)
                delete[] BucketsB[i]->Items;
            ::operator delete(BucketsB[i]);
            BucketsB[i] = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x589BD0
SubzoneTrackingStruct::SubzoneTrackingStruct()
    : unknown_00()
{
    unknown_00.Clear();
    unknown_18 = 0;
    unknown_1C = 0;
    unknown_20 = 0;
}
