// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x69E010 / 0x6CFCC0 /
//   0x6D09C0), cross-checked against YRpp ShapeButtonClass.h / ToolTipManager.h
//   (consult-only, no LICENSE; every offset reconfirmed against the user's
//   binary below).
//
// ShapeButtonClass — sidebar/UI SHP button. This TU matches the flash-tick AI,
// the static command-name lookup FindIndex, and the static SetToolTip helper.
// The full ShapeButtonClass : ToggleClass layout is P2 work, so the unknown
// base is padded to each touched offset and asserted.
#ifndef GG_MATCH_UI_SHAPE_BUTTON_CLASS_AI_METHODS_H
#define GG_MATCH_UI_SHAPE_BUTTON_CLASS_AI_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// ToolTip — the descriptor SetToolTip builds on the stack (YRpp ToolTip; size
// 0x1C). Plain aggregate: retail does NOT call its ctor, it fills the bytes.
//   GadgetID @0x00 | Bounds{X@0x04,Y@0x08,Width@0x0C,Height@0x10}
//   Text @0x14 | field_18 @0x18
// ---------------------------------------------------------------------------
struct ToolTip
{
    unsigned int GadgetID;  // +0x00
    int          X;         // +0x04
    int          Y;         // +0x08
    int          Width;     // +0x0C
    int          Height;    // +0x10
    const char*  Text;      // +0x14
    bool         field_18;  // +0x18
};

// ---------------------------------------------------------------------------
// ToolTipManager (forward, methods declared no-body so cl emits normalised
// call relocs). The global instance pointer lives at 0x00887368.
// ---------------------------------------------------------------------------
struct ToolTipManager
{
    void Remove(unsigned int id);  // GAMEMD 0x724730 __thiscall (not matched here)
    bool Add(ToolTip& tip);        // GAMEMD 0x724580 __thiscall (not matched here)
};

extern ToolTipManager* ToolTipManager_Instance;  // [0x00887368]

// ---------------------------------------------------------------------------
// Command-name lookup table referenced by FindIndex.
//   CommandNames[11]  @0x008427D0 .. 0x008427FB  (array of const char*)
//   DefaultCommandIndex @0x008427CC              (int, the not-found result)
// ---------------------------------------------------------------------------
extern const char* const CommandNames[11];  // [0x008427D0]
extern int DefaultCommandIndex;              // [0x008427CC]

// ---------------------------------------------------------------------------
// ShapeButtonClass (partial). Offsets confirmed numerically from the targets:
//   X @0x0C, Y @0x10, Width @0x14, Height @0x18  (gadget rect, SetToolTip)
//   field_1e (bool) @0x1E  (AI flash-mode selector)
//   ID (unsigned) @0x24    (SetToolTip GadgetID source)
//   IsToFlash (bool) @0x34 | FlashDelay (int) @0x38 | FlashCounter (int) @0x3C
// ---------------------------------------------------------------------------
struct ShapeButtonClass
{
    // Declared ascending by retail address.
    bool AI();                                                        // GAMEMD 0x69E010 __thiscall
    static int __fastcall FindIndex(const char* name);               // GAMEMD 0x6CFCC0 __fastcall
    static void __fastcall SetToolTip(ShapeButtonClass* pButton,
                                      const char* tip);              // GAMEMD 0x6D09C0 __fastcall

    char         _pad00[0x0C];          // +0x00 : COM vptrs + base
    int          X;                     // +0x0C
    int          Y;                     // +0x10
    int          Width;                 // +0x14
    int          Height;                // +0x18
    char         _pad1c[0x1E - 0x1C];   // +0x1C
    bool         field_1e;              // +0x1E
    char         _pad1f[0x24 - 0x1F];   // +0x1F
    unsigned int ID;                    // +0x24
    char         _pad28[0x34 - 0x28];   // +0x28
    bool         IsToFlash;             // +0x34
    char         _pad35[3];             // +0x35
    int          FlashDelay;            // +0x38
    int          FlashCounter;          // +0x3C
};

GG_STATIC_ASSERT(offsetof(ShapeButtonClass, X) == 0x0C);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Y) == 0x10);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Width) == 0x14);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, Height) == 0x18);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, field_1e) == 0x1E);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, IsToFlash) == 0x34);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashDelay) == 0x38);
GG_STATIC_ASSERT(offsetof(ShapeButtonClass, FlashCounter) == 0x3C);
GG_STATIC_ASSERT(offsetof(ToolTip, Text) == 0x14);
GG_STATIC_ASSERT(offsetof(ToolTip, field_18) == 0x18);

#endif  // GG_MATCH_UI_SHAPE_BUTTON_CLASS_AI_METHODS_H
