// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm 0x6F3280
//   len 0x49, 0x6F4A70 len 0x33).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6F3280  TechnoClass::FUN_006F3280  (__thiscall)
//   FUNCTION: GAMEMD 0x6F4A70  TechnoClass::vf_73  (__thiscall)

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"

GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 8 == 0xC94);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->bools_C8C[8]) == 1);
GG_STATIC_ASSERT(offsetof(TechnoClass, IsTether) == 0x418);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->IsTether) == 1);

// FUNCTION: GAMEMD 0x6F3280  (__thiscall)
// A mission gate: true when the object's current mission is none of 0, 6 and
// 0x10, and its type does not carry the byte at +0xC94.
//
// Retail dispatches GetCurrentMission three separate times rather than caching
// it, which is what an ordinary virtual call in three separate conditions
// gives — cl will not common a virtual call either, so the three-test spelling
// is the literal one. The gates are nested so `return false` remains the
// trailing fall-through and cl materialises `MOV AL,0x1`; spelled as early
// returns the last gate folds into a SET and the constant disappears.
bool TechnoClass::FUN_006F3280()
{
    if (vf_97() != 0) {
        if (vf_97() != 6) {
            if (vf_97() != 0x10) {
                if (!vf_33()->bools_C8C[8]) {
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6F4A70  (__thiscall)
// Run the base step; if it declines, decline. If it succeeds and this object is
// tethered to a radio partner, send the partner message 0xD, then report
// success either way.
//
// The argument arrives as `MOV EAX,[ESP+0x4]` and the exit is `RET 4`: a
// stack-passed argument, so a plain __thiscall member rather than __fastcall.
//
// LEVER, the same one as its neighbour: the success path has to be nested with
// `return false` left as the function's trailing fall-through. Written as an
// early `if (!base) return false;` cl inverts the branch and inlines a second
// `POP ESI; RET 4` where retail has one shared `XOR AL,AL; POP ESI; RET 4`
// cold tail (30.0%, multiset off by a jump polarity and the XOR).
bool TechnoClass::vf_73(int mode)
{
    if (ObjectClass::vf_73(mode)) {
        if (this->IsTether) {
            vf_157(0xD);
        }
        return true;
    }
    return false;
}
