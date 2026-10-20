// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x69BAB0:
//     `MOV AL,[ECX+0x30D8]` / `MOV byte ptr [ECX+0x30D8],1`   (InGameFrameActive)
//     `CMP dword ptr [ECX],0`                                 (GameMode, +0x00)
//     `MOV ECX,[0xA8B230]; MOV AL,[ECX+0x35A2]`               (provider flag)
//     `MOV ECX,[0x887640]; MOV EAX,[ECX]; CALL [EAX+0x1C]`    (mouse slot 7)
//     `MOV ECX,[0x887640]; MOV EDX,[ECX]; CALL [EDX+0x18]`    (mouse slot 6)
//     `MOV ECX,[0x87E758]; MOV EDX,0x4000; JMP 0x407150`      (__fastcall tail)
//   YRpp names only (consult-only): SessionClass::Resume @0x69BAB0,
//   InGameFrameActive @+0x30D8, Unsorted::IsActive @0xA8E9A0,
//   GameOptionsClass::Instance @0xA8EB60, WWMouseClass::Instance @0x887640,
//   Unsorted::CurrentFrame @0xA8ED84.
#ifndef GG_MATCH_NETWORK_SESSION_CLASS_RESUME_METHODS_H
#define GG_MATCH_NETWORK_SESSION_CLASS_RESUME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8E9A0 — Unsorted::IsActive (byte).
extern char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0x83ED20 — the game speed saved across a pause (-1 = none).
extern int DAT_0083ED20;
// GLOBAL: GAMEMD 0xA8EB60 — GameOptionsClass::Instance; first dword is the speed.
extern int DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0xB07784 — a frame deadline re-armed at CurrentFrame + 3.
extern int DAT_00B07784;

// The provider hung off 0xA8B230; only its byte at +0x35A2 is read here.
struct Provider_0069BAB0
{
    char _pad0000[0x35A2];   // +0x0000
    char At_35A2;            // +0x35A2
};
GG_STATIC_ASSERT(offsetof(Provider_0069BAB0, At_35A2) == 0x35A2);
// GLOBAL: GAMEMD 0xA8B230
extern Provider_0069BAB0* DAT_00A8B230;

// FUNCTION: GAMEMD 0x684240 (decl; reloc) — no arguments, no cleanup.
void __cdecl FUN_00684240(void);

// WWMouseClass (YRpp name): two zero-argument __thiscall slots, 6 and 7.
struct MouseVtbl_0069BAB0;
struct Mouse_0069BAB0
{
    MouseVtbl_0069BAB0* Vtbl;   // +0x0000
};
typedef void (Mouse_0069BAB0::*FnMouse18_0069BAB0)();
typedef bool (Mouse_0069BAB0::*FnMouse1C_0069BAB0)();
struct MouseVtbl_0069BAB0
{
    char _pad00[0x18];             // +0x0000
    FnMouse18_0069BAB0 At_18;      // +0x0018  CaptureMouse
    FnMouse1C_0069BAB0 At_1C;      // +0x001C  IsCaptured
};
GG_STATIC_ASSERT(offsetof(MouseVtbl_0069BAB0, At_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MouseVtbl_0069BAB0, At_1C) == 0x1C);
// GLOBAL: GAMEMD 0x887640 — WWMouseClass::Instance.
extern Mouse_0069BAB0* DAT_00887640;

// The object 0x407150 is called on (see match/core/small_misc2_methods.h,
// Obj_00407100); redeclared locally so this TU stands alone.
struct Obj_0087E758
{
    int Flags;   // +0x0000

    // FUNCTION: GAMEMD 0x407150 (decl; reloc) — __fastcall: this=ECX, value=EDX.
    void __fastcall FUN_00407150(int value);
};
// GLOBAL: GAMEMD 0x87E758
extern Obj_0087E758* DAT_0087E758;

struct SessionClass
{
    int  GameMode;              // +0x0000
    char _pad0004[0x30D8 - 4];  // +0x0004
    char InGameFrameActive;     // +0x30D8

    // FUNCTION: GAMEMD 0x69BAB0
    void Resume();
};
GG_STATIC_ASSERT(offsetof(SessionClass, InGameFrameActive) == 0x30D8);

#endif  // GG_MATCH_NETWORK_SESSION_CLASS_RESUME_METHODS_H
