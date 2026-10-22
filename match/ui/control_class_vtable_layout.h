// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail ControlClass 0x7E528C and ToggleClass 0x7E8118 have 34 slots.
// This layout pins offsets, not unconfirmed parameter types. Slots whose
// signatures remain opaque are not called by the recovered constructor/state methods.
#ifndef GG_MATCH_UI_CONTROL_CLASS_VTABLE_LAYOUT_H
#define GG_MATCH_UI_CONTROL_CLASS_VTABLE_LAYOUT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ControlClassVtableLayout
{
    void* DeletingDestructor; // +0x00: Control 0x48E660, Toggle 0x4B5810
    void* GetNext; // +0x04: Control 0x4E14A0, Toggle 0x4E14A0
    void* GetPrev; // +0x08: Control 0x4E14B0, Toggle 0x4E14B0
    void* Add; // +0x0C: Control 0x5566A0, Toggle 0x5566A0
    void* AddTail; // +0x10: Control 0x556700, Toggle 0x556700
    void* AddHead; // +0x14: Control 0x5566D0, Toggle 0x5566D0
    void* HeadOfList; // +0x18: Control 0x556640, Toggle 0x556640
    void* TailOfList; // +0x1C: Control 0x556670, Toggle 0x556670
    void* Zap; // +0x20: Control 0x5565F0, Toggle 0x5565F0
    void* Remove; // +0x24: Control 0x4E1480, Toggle 0x4E1480
    void* Input; // +0x28: Control 0x4E1640, Toggle 0x4E1640
    void* DrawAll; // +0x2C: Control 0x4E1570, Toggle 0x4E1570
    void* DeleteList; // +0x30: Control 0x4E14C0, Toggle 0x4E14C0
    void* ExtractGadget; // +0x34: Control 0x4E1920, Toggle 0x4E1920
    void* MarkListToRedraw; // +0x38: Control 0x488690, Toggle 0x488690
    void* Disable; // +0x3C: Control 0x4E1460, Toggle 0x4E1460
    void* Enable; // +0x40: Control 0x4E1450, Toggle 0x4E1450
    void* GetID; // +0x44: Control 0x48E610, Toggle 0x48E610
    void* MarkRedraw; // +0x48: Control 0x4E1960, Toggle 0x4E1960
    void* PeerToPeer; // +0x4C: Control 0x48E650, Toggle 0x48E650
    void* SetFocus; // +0x50: Control 0x4E19A0, Toggle 0x4E19A0
    void* KillFocus; // +0x54: Control 0x4E19D0, Toggle 0x4E19D0
    void* IsFocused; // +0x58: Control 0x4E19F0, Toggle 0x4E19F0
    void* IsListToRedraw; // +0x5C: Control 0x4E1A00, Toggle 0x4E1A00
    void* IsToRedraw; // +0x60: Control 0x4886A0, Toggle 0x4886A0
    void* SetPosition; // +0x64: Control 0x4E1A20, Toggle 0x4E1A20
    void* SetDimension; // +0x68: Control 0x4E1A40, Toggle 0x4E1A40
    void* Draw; // +0x6C: Control 0x48E620, Toggle 0x48E620
    void* OnMouseEnter; // +0x70: Control 0x4E1510, Toggle 0x4E1510
    void* OnMouseLeave; // +0x74: Control 0x4E1520, Toggle 0x4E1520
    void* StickyProcess; // +0x78: Control 0x4E1970, Toggle 0x4E1970
    void* Action; // +0x7C: Control 0x48E5A0, Toggle 0x723EC0
    void* Clicked; // +0x80: Control 0x4E13F0, Toggle 0x4E13F0
    void* FUN_0048E600; // +0x84: Control 0x48E600, Toggle 0x48E600
};
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, DeletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, GetNext) == 0x04);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, GetPrev) == 0x08);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Add) == 0x0C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, AddTail) == 0x10);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, AddHead) == 0x14);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, HeadOfList) == 0x18);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, TailOfList) == 0x1C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Zap) == 0x20);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Remove) == 0x24);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Input) == 0x28);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, DrawAll) == 0x2C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, DeleteList) == 0x30);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, ExtractGadget) == 0x34);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, MarkListToRedraw) == 0x38);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Disable) == 0x3C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Enable) == 0x40);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, GetID) == 0x44);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, MarkRedraw) == 0x48);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, PeerToPeer) == 0x4C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, SetFocus) == 0x50);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, KillFocus) == 0x54);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, IsFocused) == 0x58);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, IsListToRedraw) == 0x5C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, IsToRedraw) == 0x60);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, SetPosition) == 0x64);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, SetDimension) == 0x68);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Draw) == 0x6C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, OnMouseEnter) == 0x70);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, OnMouseLeave) == 0x74);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, StickyProcess) == 0x78);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Action) == 0x7C);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, Clicked) == 0x80);
GG_STATIC_ASSERT(offsetof(ControlClassVtableLayout, FUN_0048E600) == 0x84);
GG_STATIC_ASSERT(sizeof(ControlClassVtableLayout) == 0x88);
#endif
