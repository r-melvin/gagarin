// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x723EA0 / 0x723EB0),
//   cross-checked against YRpp ToggleClass.h / GadgetClass.h (consult-only;
//   reconfirmed numerically here).
//
// ToggleClass — a two-state GUI gadget (checkbox / radio button). TurnOn /
// TurnOff just set the IsOn flag (byte @ +0x2D) and tail-call the gadget's
// "flag to redraw" virtual at vtable slot 18 (+0x48):
//     mov eax,[ecx]      ; load vptr
//     mov byte [ecx+2d], 0/1
//     jmp [eax+0x48]     ; tail-call slot 18
#ifndef GG_MATCH_UI_TOGGLE_CLASS_METHODS_H
#define GG_MATCH_UI_TOGGLE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Minimal vtable + member view of ToggleClass (ControlClass : GadgetClass : …).
// The full GadgetClass virtual table is reproduced as opaque slots so the only
// virtual the matched code touches — "flag to redraw" — lands at byte offset
// 0x48 (index 18) of the vtable, exactly where the disasm's `jmp [eax+0x48]`
// dispatches. The destructor occupies slot 0 under the MSVC ABI.
struct ToggleClass
{
    virtual ~ToggleClass();          // slot 0  (+0x00)
    virtual void v04();              // slot 1  (+0x04)  GetNext
    virtual void v08();              // slot 2  (+0x08)  GetPrev
    virtual void v0C();              // slot 3  (+0x0C)  Remove
    virtual void v10();              // slot 4  (+0x10)  Input
    virtual void v14();              // slot 5  (+0x14)  DrawAll
    virtual void v18();              // slot 6  (+0x18)  DeleteList
    virtual void v1C();              // slot 7  (+0x1C)  ExtractGadget
    virtual void v20();              // slot 8  (+0x20)  MarkListToRedraw
    virtual void v24();              // slot 9  (+0x24)  Disable
    virtual void v28();              // slot 10 (+0x28)  Enable
    virtual void v2C();              // slot 11 (+0x2C)  GetID
    virtual void v30();              // slot 12 (+0x30)  MarkRedraw
    virtual void v34();              // slot 13 (+0x34)  PeerToPeer
    virtual void v38();              // slot 14 (+0x38)  SetFocus
    virtual void v3C();              // slot 15 (+0x3C)  KillFocus
    virtual void v40();              // slot 16 (+0x40)  IsFocused
    virtual void v44();              // slot 17 (+0x44)  IsListToRedraw
    virtual void FlagToRedraw();     // slot 18 (+0x48)  <- tail-called here

    // Non-virtual gadget control.
    void TurnOn();                   // GAMEMD 0x723EA0 __thiscall
    void TurnOff();                  // GAMEMD 0x723EB0 __thiscall

    // Layout: vptr occupies [0x00..0x03]; the GadgetClass/ControlClass body up
    // to the IsOn flag is opaque. IsOn (the toggle state) is a byte @ +0x2D.
    char          _base[0x2D - 0x04];  // +0x04 .. +0x2C
    unsigned char IsOn;                // +0x2D
};

GG_STATIC_ASSERT(offsetof(ToggleClass, IsOn) == 0x2D);

#endif  // GG_MATCH_UI_TOGGLE_CLASS_METHODS_H
