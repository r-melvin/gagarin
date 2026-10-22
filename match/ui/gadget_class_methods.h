// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and the complete virtual-table layout were derived from the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI: the GadgetClass vtable
//   was read directly from memory at 0x7E92BC (the address the scalar-deleting
//   destructor at 0x4E1A60 stores into [this]), and each slot identified by its
//   target address against the known method entry points. Cross-checked against
//   YRpp (every offset reconfirmed
//   here from the disassembly).
//
// GadgetClass — base of the GUI gadget hierarchy. It is a doubly-linked-list
// node (LinkClass: Next@0x4, Previous@0x8) plus a screen rectangle and flags.
//
// Member names: X/Y/Width/Height/IsSticky/IsDisabled/Flags are YRpp-cross-checked
// against the accesses below. RedrawPending (+0x1C) is descriptive: it is set by
// Enable/Disable/Action/MarkRedraw and consumed by Draw. The slot map below is
// derived from the binary's 0x7E92BC table.
//
// CONFIRMED vtable layout (byte offset -> entry, from the 0x7E92BC dump):
//   0x00 ~dtor(scalar-del)  0x04 GetNext      0x08 GetPrev      0x0C Add
//   0x10 AddTail            0x14 AddHead      0x18 HeadOfList    0x1C TailOfList
//   0x20 Zap                0x24 Remove       0x28 Input         0x2C DrawAll
//   0x30 DeleteList         0x34 ExtractGadget 0x38 MarkListToRedraw 0x3C Disable
//   0x40 Enable             0x44 GetID        0x48 MarkRedraw    0x4C PeerToPeer
//   0x50 SetFocus           0x54 KillFocus    0x58 IsFocused     0x5C IsListToRedraw
//   0x60 IsToRedraw         0x64 SetPosition  0x68 SetDimension  0x6C Draw
//   0x70 OnMouseEnter       0x74 OnMouseLeave 0x78 StickyProcess 0x7C Action
//   0x80 Clicked
#ifndef GG_MATCH_UI_GADGET_CLASS_METHODS_H
#define GG_MATCH_UI_GADGET_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/link_class_methods.h"

// GadgetClass derives from the real LinkClass base (match/core/link_class_methods.h):
// vtable slots 0x00..0x24 and the vptr/Next/Previous prefix come from the base,
// and GadgetClass appends its own slots from 0x28 (Input) onward. Modelling the
// base for real (rather than inlining its prefix) is what lets Remove() below be
// spelled as the base-qualified `LinkClass::Remove()` the retail bytes show — a
// *non-tail* call (`call; pop esi; ret`), which a free-function stand-in would
// have been tail-jumped into instead.
// VTABLE: GAMEMD 0x7E92BC
class GadgetClass : public LinkClass
{
public:
    // FUNCTION: GAMEMD 0x4E12F0 (decl; constructor)
    GadgetClass(int x, int y, int width, int height, unsigned int flags, char sticky);

    // Overrides land in the base's slots regardless of declaration position;
    // NEW slots below are declared in exact vtable order so the compiler emits
    // the right [reg+offset] dispatch for every virtual call the matched code
    // makes. Slots not touched by the matched code are opaque void()s.
    // NOTE: the three list overrides keep the base's LinkClass* return type.
    // MSVC 6.0 has no covariant return types (C2555), so the retail code could
    // not have narrowed them either; callers cast at the use site instead.
    virtual ~GadgetClass();                          // 0x00 slot 0   (override)
    virtual LinkClass* GetNext();                    // 0x04 slot 1   (override) <- matched
    virtual LinkClass* GetPrev();                    // 0x08 slot 2   (override) <- matched
    virtual LinkClass* Remove();                     // 0x24 slot 9   (override) <- matched
    virtual unsigned Input();                        // 0x28 slot 10  (first new slot) 0x4E1640
    virtual void DrawAll(bool forced);               // 0x2C slot 11  <- matched
    virtual void DeleteList();                        // 0x30 slot 12  <- matched
    virtual GadgetClass* ExtractGadget(unsigned id); // 0x34 slot 13  0x4E1920
    virtual void MarkListToRedraw();                 // 0x38 slot 14  0x488690
    virtual void Disable();                          // 0x3C slot 15  <- matched
    virtual void Enable();                           // 0x40 slot 16  <- matched
    virtual unsigned int GetID();                    // 0x44, returns zero at 0x4AEBA0
    virtual void MarkRedraw();                       // 0x48 slot 18  <- matched
    // 0x4C: 0x48E650 returns with RET 0xC; caller 0x48E5A0 passes these arguments.
    virtual void PeerToPeer(unsigned flags, unsigned* key, GadgetClass* source);
    virtual void SetFocus();                          // 0x50 slot 20  <- matched
    virtual void KillFocus();                        // 0x54 slot 21  <- matched
    virtual bool IsFocused();                        // 0x58 slot 22  <- matched
    virtual int  IsListToRedraw();                   // 0x5C slot 23  <- matched
    virtual unsigned char IsToRedraw();              // 0x60 slot 24  0x4886A0
    virtual void SetPosition(int x, int y);          // 0x64 slot 25  <- matched
    virtual void SetDimension(int w, int h);         // 0x68 slot 26  <- matched
    virtual int  Draw(int forced);                   // 0x6C slot 27 (arg widened to int)
    virtual void OnMouseEnter();                     // 0x70 slot 28  0x4E1510
    virtual void OnMouseLeave();                     // 0x74 slot 29  0x4E1520
    virtual void StickyProcess(unsigned flags);      // 0x78 slot 30  <- matched
    virtual int  Action(unsigned flags, unsigned* key, int modifier);  // 0x7C slot 31  <- matched
    // 0x80: 0x4E13F0 masks `flags` with Flags, hit-tests (x, y) and forwards to Action.
    virtual int  Clicked(unsigned* key, unsigned flags, int x, int y, int modifier);  // 0x80 slot 32

    // Non-virtual public helper (not present in the vtable dump).
    // FUNCTION: GAMEMD 0x4E12D0 (decl) -- the scheme index gadgets draw with (__fastcall, static).
    static int GetColorScheme();
    bool IsEnabled() const;                          // GAMEMD 0x4E1470
    // FUNCTION: GAMEMD 0x4E15A0 — smallest enabled gadget under (x, y).
    GadgetClass* ExtractGadgetAt(int x, int y);

    // Layout: LinkClass supplies vptr@0x00 + Next@0x04 + Previous@0x08
    // (sizeof(LinkClass) == 0x0C); GadgetClass appends the screen rectangle,
    // the redraw/sticky/disabled bytes, and the flag word.
    int          X;          // +0x0C
    int          Y;          // +0x10
    int          Width;      // +0x14
    int          Height;     // +0x18
    unsigned char RedrawPending; // +0x1C
    unsigned char IsSticky;    // +0x1D
    unsigned char IsDisabled;  // +0x1E
    unsigned char _pad1F;      // +0x1F
    int          Flags;      // +0x20
};

GG_STATIC_ASSERT(offsetof(GadgetClass, Next)        == 0x04);  // inherited from LinkClass
GG_STATIC_ASSERT(offsetof(GadgetClass, Previous)    == 0x08);  // inherited from LinkClass
GG_STATIC_ASSERT(offsetof(GadgetClass, X)           == 0x0C);  // SetPosition  [ECX+0x0C]
GG_STATIC_ASSERT(offsetof(GadgetClass, Y)           == 0x10);  // SetPosition  [ECX+0x10]
GG_STATIC_ASSERT(offsetof(GadgetClass, Width)       == 0x14);  // SetDimension [ECX+0x14]
GG_STATIC_ASSERT(offsetof(GadgetClass, Height)      == 0x18);  // SetDimension [ECX+0x18]
GG_STATIC_ASSERT(offsetof(GadgetClass, RedrawPending) == 0x1C);  // MarkRedraw   [ECX+0x1C]
GG_STATIC_ASSERT(offsetof(GadgetClass, IsSticky)    == 0x1D);  // StickyProcess[ECX+0x1D]
GG_STATIC_ASSERT(offsetof(GadgetClass, IsDisabled)  == 0x1E);  // Enable       [ECX+0x1E]
GG_STATIC_ASSERT(offsetof(GadgetClass, Flags)       == 0x20);  // KillFocus    [ECX+0x20]
GG_STATIC_ASSERT(sizeof(GadgetClass) == 0x24);

// The best-so-far rectangle ExtractGadgetAt keeps on its frame. Only Width and
// Height are initialised (from the screen size); X and Y are written on a hit
// and never read, and retail still stores them (0x4E1607/0x4E160B) because they
// are struct members rather than dead scalars.
struct GadgetRect
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(GadgetRect) == 0x10);

// GLOBAL: GAMEMD 0x7F5BE8 — screen width (1024 in the retail image).
extern int DAT_007F5BE8;
// GLOBAL: GAMEMD 0x7F5BF4 — screen height (768 in the retail image).
extern int DAT_007F5BF4;

#endif  // GG_MATCH_UI_GADGET_CLASS_METHODS_H
