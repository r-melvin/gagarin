// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x642AD0, 0x642AE0, 0x642DF0 and 0x642B30. All four
//   are `__fastcall`/`__thiscall` one-object methods over a small run of
//   offsets (+0x54, +0x58, +0x60, +0x78, +0x80) that abut the already-
//   confirmed ProgressScreenClass::PlayerSide at +0x80
//   (match/ui/progress_screen_class.h, read not edited -- that header defers
//   the rest of the class's layout to P2, so this TU models only the four
//   offsets its own functions touch, under a local name, rather than editing
//   the shared one).
//     0x642AD0: `MOV byte ptr [ECX+0x60],0; RET` -- clears a flag byte.
//     0x642AE0: `this+0x58` gates a `free(this+0x54)`, then `this+0x54` is
//       unconditionally zeroed -- the ordinary "release an owned buffer"
//       shape already seen elsewhere in this tree.
//     0x642DF0: `MOV EAX,[ESP+4]; MOV [ECX+0x78],EAX; RET 4` -- a plain
//       setter, one stack argument.
//     0x642B30: reads `this+0x80` (`PlayerSide`) and tail-jumps into the
//       gadget-by-name-and-type finder at 0x68CA50 with one of two literal
//       caption strings ("AlliedLoad" at 0x836EC0, "SovietLoad" at
//       0x836EB4) and a literal type `1`.
#ifndef GG_MATCH_UI_LOAD_SCREEN_SIDE_CAPTION_METHODS_H
#define GG_MATCH_UI_LOAD_SCREEN_SIDE_CAPTION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) -- CRT free.
extern "C" void __cdecl gg_free_0642AE0(void* block);

// FUNCTION: GAMEMD 0x68CA50 (decl; reloc) -- find a gadget by caption text
// and type; genuinely __fastcall (ECX=name, EDX=type).
extern "C" void* FindGadgetByCaption_0068CA50(const char* name, int type);

// STRING: GAMEMD 0x836EC0  "AlliedLoad"
extern const char STR_00836EC0[];
// STRING: GAMEMD 0x836EB4  "SovietLoad"
extern const char STR_00836EB4[];

struct LoadScreenClass_00642AD0
{
    char  _pad000[0x54];   // +0x0000 .. not modelled here
    void* Buffer;           // +0x0054
    char  BufferOwned;      // +0x0058
    char  _pad059[0x60 - 0x59];
    char  Flag060;          // +0x0060
    char  _pad061[0x78 - 0x61];
    int   At078;            // +0x0078
    char  _pad07C[0x80 - 0x7C];
    int   PlayerSide;       // +0x0080

    // FUNCTION: GAMEMD 0x642AD0
    void ClearFlag060();
    // FUNCTION: GAMEMD 0x642AE0
    void ReleaseBuffer();
    // FUNCTION: GAMEMD 0x642DF0
    void SetAt078(int value);
    // FUNCTION: GAMEMD 0x642B30
    void* PickSideCaptionGadget();
};
GG_STATIC_ASSERT(offsetof(LoadScreenClass_00642AD0, Buffer)      == 0x54);
GG_STATIC_ASSERT(offsetof(LoadScreenClass_00642AD0, BufferOwned) == 0x58);
GG_STATIC_ASSERT(offsetof(LoadScreenClass_00642AD0, Flag060)     == 0x60);
GG_STATIC_ASSERT(offsetof(LoadScreenClass_00642AD0, At078)       == 0x78);
GG_STATIC_ASSERT(offsetof(LoadScreenClass_00642AD0, PlayerSide)  == 0x80);

#endif  // GG_MATCH_UI_LOAD_SCREEN_SIDE_CAPTION_METHODS_H
