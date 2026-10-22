// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4F4480: the surface pointers `[0x88731C]` (Composite)
//   saved over `[0x887314]` (Temp, restored from EBP at the end) and
//   `[0x887300]` (Sidebar); the mouse singleton `[0x887640]` dispatched
//   `PUSH 0; PUSH surface; CALL [EDX+0x40]` and `[EDX+0x3C]`; `[ESI+0xC]`
//   read then zeroed with `SETNZ` / `CMP 2; SETZ` bytes spilled to the frame;
//   CALL 0x53BAE0 (no receiver, AL result); the tactical object `[0x887324]`
//   receiving CALL 0x6D3D10 three times with (surface, flag, 0 / 1 / 2);
//   this's own slots `[EDX+0x40]` (one pushed argument) and `[EDX+0x44]`
//   (none); the bytes `[0xB0B519]` (cleared afterwards) and `[0xA8ED6B]`;
//   the optional objects `[0xA8EF54]` (slot +0x2C, one pushed 0) and
//   `[0x887368]` (slot +0xC, one pushed 0); `MOV ECX,0xA8BC60; CALL
//   0x5D49A0` (MessageListClass::Draw on the instance); the byte
//   `[0xA8B8B4]` gating `XOR CL,CL; CALL 0x55F1E0`. Names from YRpp
//   GScreenClass.h / Surface.h / WWMouseClass.h / TacticalClass.h /
//   (names only).
//   FlagToRedraw @0x4F42F0: the byte `[EAX+0xD7D]` on `[0x887324]`, `[ECX+0xC]`
//   compared with 2 and stored, then `MOV ECX,0x87F7E8; CALL 0x578AC0`.
#ifndef GG_MATCH_UI_GSCREEN_CLASS_RENDER_METHODS_H
#define GG_MATCH_UI_GSCREEN_CLASS_RENDER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Surface_004F4480 { char opaque[4]; };

// GLOBAL: GAMEMD 0x887300 — DSurface::Sidebar.
extern Surface_004F4480* DAT_00887300;
// GLOBAL: GAMEMD 0x887314 — DSurface::Temp.
extern Surface_004F4480* DAT_00887314;
// GLOBAL: GAMEMD 0x88731C — DSurface::Composite.
extern Surface_004F4480* DAT_0088731C;

// GLOBAL: GAMEMD 0xA8ED6B — Unsorted::ArmageddonMode (byte).
extern bool DAT_00A8ED6B;
// GLOBAL: GAMEMD 0xB0B519 — a "sidebar needs a full redraw" byte, cleared here.
extern bool DAT_00B0B519;
// GLOBAL: GAMEMD 0xA8B8B4 — Unsorted::EnableMPDebug (byte).
extern bool DAT_00A8B8B4;

// FUNCTION: GAMEMD 0x53BAE0 (decl; reloc) — a global byte test, no receiver.
bool __cdecl FUN_0053BAE0();
// FUNCTION: GAMEMD 0x55F1E0 (decl; reloc) — __fastcall, flag in CL.
void __fastcall FUN_0055F1E0(bool flag);

// WWMouseClass — slots +0x3C / +0x40 take (surface, flag).
struct MouseVtbl_004F4480;
struct Mouse_004F4480
{
    MouseVtbl_004F4480* Vtbl;      // +0x0000
};
typedef void (Mouse_004F4480::*MouseFn_004F4480)(Surface_004F4480* surface, bool flag);
struct MouseVtbl_004F4480
{
    char              _pad000[0x3C];   // +0x0000
    MouseFn_004F4480  At_3C;           // +0x003C
    MouseFn_004F4480  At_40;           // +0x0040
};
GG_STATIC_ASSERT(offsetof(MouseVtbl_004F4480, At_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(MouseVtbl_004F4480, At_40) == 0x40);
// GLOBAL: GAMEMD 0x887640 — WWMouseClass::Instance.
extern Mouse_004F4480* DAT_00887640;

// TacticalClass — Render, and the redraw byte FlagToRedraw sets.
struct Tactical_004F4480
{
    char          _pad000[0xD7D];  // +0x0000
    unsigned char NeedsRedraw;     // +0x0D7D
    // FUNCTION: GAMEMD 0x6D3D10 (decl; reloc) — TacticalClass::Render.
    void Render(Surface_004F4480* surface, bool flag, int mode);
};
GG_STATIC_ASSERT(offsetof(Tactical_004F4480, NeedsRedraw) == 0xD7D);
// GLOBAL: GAMEMD 0x887324 — TacticalClass::Instance.
extern Tactical_004F4480* DAT_00887324;

// An optional object at 0xA8EF54 whose slot +0x2C takes one argument.
struct OptVtbl_004F4480;
struct Opt_004F4480
{
    OptVtbl_004F4480* Vtbl;        // +0x0000
};
typedef void (Opt_004F4480::*OptFn_004F4480)(int arg);
struct OptVtbl_004F4480
{
    char            _pad000[0x2C]; // +0x0000
    OptFn_004F4480  At_2C;         // +0x002C
};
GG_STATIC_ASSERT(offsetof(OptVtbl_004F4480, At_2C) == 0x2C);
// GLOBAL: GAMEMD 0xA8EF54
extern Opt_004F4480* DAT_00A8EF54;

// CCToolTip — slot +0xC takes one argument.
struct TipVtbl_004F4480;
struct Tip_004F4480
{
    TipVtbl_004F4480* Vtbl;        // +0x0000
};
typedef void (Tip_004F4480::*TipFn_004F4480)(int arg);
struct TipVtbl_004F4480
{
    char            _pad000[0x0C]; // +0x0000
    TipFn_004F4480  At_0C;         // +0x000C
};
GG_STATIC_ASSERT(offsetof(TipVtbl_004F4480, At_0C) == 0x0C);
// GLOBAL: GAMEMD 0x887368 — CCToolTip::Instance.
extern Tip_004F4480* DAT_00887368;

// MessageListClass — the instance is the object itself (MOV ECX,0xA8BC60).
struct MessageList_004F4480
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5D49A0 (decl; reloc) — MessageListClass::Draw.
    void Draw();
};
// GLOBAL: GAMEMD 0xA8BC60 — MessageListClass::Instance.
extern MessageList_004F4480 DAT_00A8BC60;

// The map instance at 0x87F7E8; only its redraw-counter bump at 0x578AC0 is
// reached, so the type takes that function's class name and the call binds to
// it.
struct ScreenRedraw_00578AC0
{
    // FUNCTION: GAMEMD 0x578AC0 (decl; reloc) — bump the redraw counter.
    void FUN_00578AC0();
};
// GLOBAL: GAMEMD 0x87F7E8
extern ScreenRedraw_00578AC0 DAT_0087F7E8;

// GScreenClass — the redraw flag and two of its own virtuals.
struct GScreenVtbl_004F4480;
struct GScreen_004F4480
{
    GScreenVtbl_004F4480* Vtbl;    // +0x0000
    char _pad004[0x0C - 0x04];     // +0x0004
    int  RedrawFlag;               // +0x000C

    // FUNCTION: GAMEMD 0x4F42F0 — GScreenClass::FlagToRedraw.
    void FlagToRedraw(int mode);
    // FUNCTION: GAMEMD 0x4F4480 — GScreenClass::Render.
    void Render();
};
GG_STATIC_ASSERT(offsetof(GScreen_004F4480, RedrawFlag) == 0x0C);
typedef void (GScreen_004F4480::*GScreenFn40_004F4480)(bool full);
typedef void (GScreen_004F4480::*GScreenFn44_004F4480)();
struct GScreenVtbl_004F4480
{
    char                  _pad000[0x40]; // +0x0000
    GScreenFn40_004F4480  At_40;         // +0x0040
    GScreenFn44_004F4480  At_44;         // +0x0044
};
GG_STATIC_ASSERT(offsetof(GScreenVtbl_004F4480, At_40) == 0x40);
GG_STATIC_ASSERT(offsetof(GScreenVtbl_004F4480, At_44) == 0x44);

#endif  // GG_MATCH_UI_GSCREEN_CLASS_RENDER_METHODS_H
