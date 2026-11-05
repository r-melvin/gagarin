// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x770270.
//   PLACEMENT LEAD (inference): in retail this constructor reaches the capacity-0 base
//   constructor of the two +0x37C vectors by a real CALL (0x42DC50), while 0x770E10 in
//   match/tu281_wdtvoice.cpp has that constructor expanded inline. At /Ob2 cl inlines any
//   body it can see, so the retail call implies the base constructor body was not visible
//   where this function was compiled. This file includes only the dynamic-vector
//   constructor (vector_class_dynamic_ctor.h), never the base one, and is a separate
//   object from match/tu281_wdtvoice.cpp; the original file name is not known and is
//   not claimed.
#include "vector_class_dynamic_ctor.h"
#include "wdt_voice_classes.h"

void* __cdecl FUN_00407010();   // FUNCTION: GAMEMD 0x407010 (decl; reloc)

// The element constructor, expanded in the loop below (its out-of-line copy is 0x770E10
// in match/tu281_wdtvoice.cpp, which carries the FUNCTION claim).
inline Obj_00770E10::Obj_00770E10()
{
    unknown_00 = STR_00889F64;
}

// FUNCTION: GAMEMD 0x770270
Obj_00770430::Obj_00770430(int side)
    : unknown_00(side), unknown_3B8(true), unknown_3BC(0), unknown_3D8(0)
{
    FUN_00407010();
    {
        Wstring text("OldCycle");
        unknown_04[0].unknown_00 = text;
    }
    {
        Wstring text("History");
        unknown_04[1].unknown_00 = text;
    }
    {
        Wstring text("Status");
        unknown_04[2].unknown_00 = text;
    }
    {
        Wstring text("Territory");
        unknown_04[3].unknown_00 = text;
    }
    {
        Wstring text("Game");
        unknown_04[4].unknown_00 = text;
    }
    {
        Wstring text("Evacuate");
        unknown_04[5].unknown_00 = text;
    }
}
