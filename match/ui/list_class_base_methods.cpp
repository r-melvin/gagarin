// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   ListClass's own sixteen-body core (dtor, list mutation, scrolling,
//   Add/AddHead/AddTail/Remove overrides), diffed against the
//   user's retail gamemd.exe v1.001. Bodies ordered ascending by address.
//
//   All sixteen are typed C++; Action (0x557830) is a recorded partial. An
//   earlier revision of this file had TEN naked bodies on the theory
//   that a shared block reached from two call sites, or several foreign
//   vtables dispatched in one body, could not be regenerated from C++. That
//   theory was wrong for nine of the ten and the note is retracted -- see the
//   lever notes on the individual bodies below.
//
//   Hand-assembly screen (docs/matching_methodology_and_toolchain.md, batch
//   thirty-eight): NONE of these sixteen retail bodies carries the inline-`_asm`
//   signature, so all of them were compiled from ordinary C++ and converting
//   our transcriptions was the right call. Evidence, from the retail bytes:
//     * not one of the sixteen opens a `PUSH EBP; MOV EBP,ESP` frame --
//       0x557600 opens `PUSH EBX; PUSH ESI`, 0x5576A0 `PUSH EBX; MOV EBX,
//       [ESP+8]`, 0x557730 `MOV EAX,[ESP+4]; PUSH ESI`, 0x557830 `PUSH EBX;
//       MOV EBX,[ESP+8]`, and the nine others `PUSH ESI`;
//     * every parameter is read ESP-relative (`[ESP+0x8]`, `[ESP+0xC]`,
//       `[ESP+0x10]`, `[ESP+0x14]`), the frame-pointer-omission convention,
//       which an `__asm` block would have suppressed;
//     * 0x557BE0 EnableScrollBar uses EBP as a general-purpose register
//       (`LEA EBP,[ESI+0xB8]` at 0x557C1D) -- conclusive proof that /O2's
//       frame-pointer omission was in force in that function;
//     * no body reserves a stack slot at all (no `SUB ESP,n` anywhere in
//       0x557600-0x557F3A); every local lives in ESI/EDI/EBX/EBP;
//     * the instruction set used is mov/lea/push/pop/call/test/cmp/add/sub/
//       inc/dec/and/xor/idiv/cdq/jcc/ret only. The one arguably exotic pair,
//       `CDQ; IDIV [ESI+0x4C]` at 0x5578E4, is what cl emits for a signed
//       `/` -- there is no segment override, no string instruction, no
//       BSWAP/RDTSC/CPUID/LOOP, no PUSHFD/POPFD and no carry-flag reuse.
#include "list_class_base_methods.h"

// FUNCTION: GAMEMD 0x557600
// ListClass::~ListClass. If scrolling was active, restores the Width the
// scrollbar had borrowed, clears the flag, and unhooks the Scroller and both
// ShapeButtons from the modal gadget chain (Remove, vtbl+0x24 on each) before
// this itself is marked for redraw -- that whole arm is DisableScrollBar's body
// expanded in place, minus its return value. Unconditionally destroys the three
// child widgets, re-stamps the base list's own vtable, frees its block if it
// owned one, and chains to GadgetClass::~GadgetClass.
//
// ListClass's own vtable seat is a plain store: ListClass is not modelled as
// polymorphic here (it carries its vptr as an explicit member). The list
// vector's seat comes from its inline destructor.
// The `XOR EBX,EBX` zero register falls out of the seven zero uses on its own.
void ListClass::Dtor()
{
    Vfptr = (ListClassVtbl*)VT_007ED10C;
    if (IsScrollActive) {
        // The vtable pointer has to be read into its own local BEFORE the Width
        // arithmetic, or cl sinks the load past it and emits the receiver LEA
        // first; retail loads `[ESI+0x118]` at 0x557614, two instructions ahead
        // of the `ADD ECX,EAX`. Same lever as EnableScrollBar below.
        GadgetVtbl* scrollerVt = ((GadgetShim*)&Scroller)->Vfptr;
        Width += ((GadgetShim*)&Scroller)->Width;
        IsScrollActive = false;
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scrollerVt->At_24)();
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*up->Vfptr->At_24)();
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_24)();
        (this->*Vfptr->At_48)();
    }
    ((SliderObj*)&Scroller)->Dtor();
    ((ShapeBtnObj*)&DownButton)->Dtor();
    ((ShapeBtnObj*)&UpButton)->Dtor();
    // The member vector's destructor, inline. DynamicVectorClass has no
    // destructor of its own, so this is ~VectorClass: it reseats the
    // VectorClass<wchar_t const*> vtable 0x7ED1FC and frees the block if it
    // owns it. Calling the DynamicVectorClass destructor instead makes cl call
    // the implicit one out of line (6.2%).
    List.VectorClass<wchar_t const*>::~VectorClass();
    BaseDtor();
}

// FUNCTION: GAMEMD 0x5576A0
// ListClass::AddItem. DynamicVectorClass<wchar_t const*>::AddItem expanded at
// the call site (vector_class_operations.h): append if there is spare
// capacity, else grow by CapacityIncrement -- only when the vector owns its block, or
// has never allocated one -- and fall into the same append code on success.
// Unconditionally marks for redraw, turns the scrollbar on once the entry count
// exceeds a page, and keeps a live Scroller's range current. Returns the index
// of the entry just added (or of the last entry, given a null pointer, via the
// shared trailing return).
//
// The block the earlier naked transcription described as "reached from two
// different callers" is just the fallthrough after the capacity `if`; an
// ordinary inline vector Add reproduces it, including the EDI/EBX/ESI pinning,
// on the first compile. The only real lever was the append's own shape.
int ListClass::AddItem(wchar_t const* text)
{
    if (text != 0) {
        List.AddItem(text);
        (this->*Vfptr->At_48)();
        if (List.Count > LineCount) {
            (this->*Vfptr->At_8C)();
        }
        if (IsScrollActive) {
            SliderShim* scroller = (SliderShim*)&Scroller;
            (scroller->*scroller->Vfptr->At_88)(List.Count);
        }
    }
    return List.Count - 1;
}

// FUNCTION: GAMEMD 0x557730
// ListClass::RemoveItem(index). Shifts every later entry down one slot, then
// keeps the scrollbar, the selection and the scrolled-to-top index consistent
// with the new (shorter) count. The outer bound check is unsigned (index
// against the pre-removal count, JNC) and the inner one signed (JGE, the
// inlined DynamicVectorClass::Delete's own guard).
//
// The removal is the vector's inline by-index Delete, and every count read
// goes through the inline GetCount() accessor. Retail's repeated `CMP EAX,ECX`
// (0x55773A/0x557742) is the inlined Delete re-testing the bound, and its
// count reload at 0x5577C3 follows from the accessor; reading the field
// directly lets cl reuse flags and registers (8.2%, and 70.5% with Delete
// alone).
void ListClass::RemoveItem(int index)
{
    if ((unsigned)index < (unsigned)List.GetCount()) {
        List.Delete(index);
        if (List.GetCount() <= LineCount) {
            (this->*Vfptr->At_B0)();
        }
        if (IsScrollActive) {
            SliderShim* scroller = (SliderShim*)&Scroller;
            (scroller->*scroller->Vfptr->At_88)(List.GetCount());
        }
        if (SelectedIndex >= List.GetCount()) {
            SelectedIndex--;
            if (SelectedIndex < 0) {
                SelectedIndex = 0;
            }
        }
        if (CurrentTopIndex >= List.GetCount()) {
            CurrentTopIndex--;
            if (CurrentTopIndex < 0) {
                CurrentTopIndex = 0;
            }
            if (IsScrollActive) {
                SliderShim* scroller = (SliderShim*)&Scroller;
                (scroller->*scroller->Vfptr->At_B0)(1);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x557800
// ListClass::RemoveItem(text). Looks the text up in the base list's own
// vector (TextDynVector::ID, vtbl+0x10) and, if found, dispatches to the
// index overload above through this object's own vtable slot +0xA8 (an
// indirect self-call, not a direct one -- the two overloads really are
// separate virtuals in retail).
void ListClass::RemoveItem(wchar_t const* text)
{
    if (text != 0) {
        ListClassVtbl* vt = Vfptr;
        int index = List.FindItemIndex(text);
        (this->*vt->At_A8)(index);
    }
}

// FUNCTION: GAMEMD 0x557830
// ListClass::Action. A left-button-release edge (flags&4) zeroes the caller's
// key, forces the return value to 1 outright and returns -- the only branch
// that never needs the key pointer, so EDI (holding it everywhere else) is
// never pushed on this path. Otherwise: a non-keyboard event (flags&0x100==0)
// resolves the clicked row from the cursor Y (via the global mouse singleton)
// into SelectedIndex; a keyboard PageUp/PageDown (key==0x26/0x28) steps the
// selection by one row each way and eats the key; anything else just clears the
// Keyboard bit. Every path falls through to ControlClass::Action, each with its
// own EDI/ESI/EBX epilogue (four separate `ret 0xc` tails).
//
// PARTIAL, 93.5% (87/93, multiset identical). The residual is load order in
// the hit-test: retail loads Y then CurrentTopIndex ahead of the subtraction
// and re-reads List.Count for the clamp; cl orders those loads differently.
// Other natural spellings: the row computed straight into SelectedIndex
// (80.6%), the key test as a switch with a ternary clamp (53.8%), and the
// summands swapped or the mouse call inlined (both 93.5%).
unsigned ListClass::Action(unsigned flags, unsigned* key, int extra)
{
    if (flags & 4) {
        *key = 0;
        BaseAction(flags & ~4, key, 0);
        return 1;
    }
    if (flags & 0x100) {
        if (*key == 0x26) {
            (this->*Vfptr->At_A4)(-1);
            *key = 0;
        } else if (*key == 0x28) {
            (this->*Vfptr->At_A4)(1);
            *key = 0;
        } else {
            flags &= ~0x100;
        }
    } else {
        MouseShim* mouse = DAT_00887640;
        int mouseY = (mouse->*mouse->Vfptr->At_30)();
        int row = (mouseY - Y - 1) / LineHeight + CurrentTopIndex;
        SelectedIndex = row;
        int last = List.Count - 1;
        if (row >= last) {
            row = last;
        }
        SelectedIndex = row;
        if (row == -1) {
            SelectedIndex = 0;
        }
    }
    return BaseAction(flags, key, 0);
}

// FUNCTION: GAMEMD 0x557A20
// ListClass::Bump. While scrolling is active, steps the live Scroller by one
// page (vtbl+0xB0), and on a real change reads its new position back
// (vtbl+0x90) into CurrentTopIndex and marks for redraw. Byte-identical to
// Step below -- two vtable slots compiled from the same shape, matched
// separately at their own addresses.
void ListClass::Bump(int minus)
{
    if (IsScrollActive) {
        SliderShim* scroller = (SliderShim*)&Scroller;
        if ((scroller->*scroller->Vfptr->At_B0)(minus)) {
            CurrentTopIndex = (scroller->*scroller->Vfptr->At_90)();
            (this->*Vfptr->At_48)();
        }
    }
}

// FUNCTION: GAMEMD 0x557A70
// ListClass::Step. See Bump immediately above -- same body, different slot.
void ListClass::Step(int minus)
{
    if (IsScrollActive) {
        SliderShim* scroller = (SliderShim*)&Scroller;
        if ((scroller->*scroller->Vfptr->At_B0)(minus)) {
            CurrentTopIndex = (scroller->*scroller->Vfptr->At_90)();
            (this->*Vfptr->At_48)();
        }
    }
}

// FUNCTION: GAMEMD 0x557AC0
// ListClass::GetItem. Clamps the index to the last valid entry (empty list
// returns null) and returns the raw vector slot.
wchar_t const* ListClass::GetItem(int index)
{
    if (List.Count == 0) {
        return 0;
    }
    int last = List.Count - 1;
    if (index >= last) {
        index = last;
    }
    return List.Items[index];
}

// FUNCTION: GAMEMD 0x557AE0
// ListClass::GetCurrentItem. The selected row, or null if the selection has
// scrolled past the end of a shrunk list.
wchar_t const* ListClass::GetCurrentItem()
{
    if (List.Count <= SelectedIndex) {
        return 0;
    }
    return List.Items[SelectedIndex];
}

// FUNCTION: GAMEMD 0x557B70
// ListClass::SetViewIndex. Clamps the requested top row to
// [0, Count-LineCount] and, on a real change, marks for redraw and
// pushes the new top row to a live Scroller.
int ListClass::SetViewIndex(int index)
{
    int span = List.Count - LineCount;
    int clamped = (span < 0) - 1;
    clamped &= span;
    if (index < 0) {
        index = 0;
    } else if (index > clamped) {
        index = clamped;
    }
    if (index != CurrentTopIndex) {
        CurrentTopIndex = index;
        (this->*Vfptr->At_48)();
        if (IsScrollActive) {
            SliderShim* scroller = (SliderShim*)&Scroller;
            (scroller->*scroller->Vfptr->At_8C)(CurrentTopIndex);
        }
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x557BE0
// ListClass::EnableScrollBar. A no-op if already active. Otherwise: marks for
// redraw, shrinks Width by the Scroller's own Width, re-peers all three child
// widgets to this list (MakePeer, vtbl+0x84), splices them into the same modal
// gadget chain this itself is on (Add, vtbl+0xC), marks each for redraw, and
// pushes the current count/page/top-row down to the Scroller.
//
// Two levers. The three child pointers must each be a named local, which is
// what pins them into EBX/EBP/EDI across the twelve calls. And UpButton's
// vtable pointer must be read into its OWN local before the Width subtraction:
// retail loads `[ESI+0x58]` at 0x557C03, ahead of the `SUB EBX,ECX`, and
// deriving it at the call site instead costs exactly the four instructions
// between 0x557BFA and 0x557C0B (94.7% vs 100%).
int ListClass::EnableScrollBar()
{
    if (!IsScrollActive) {
        IsScrollActive = true;
        (this->*Vfptr->At_48)();
        GadgetVtbl* upVt = ((GadgetShim*)&UpButton)->Vfptr;
        Width -= ((GadgetShim*)&Scroller)->Width;
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*upVt->At_84)(this);
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_84)(this);
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scroller->Vfptr->At_84)(this);
        (up->*up->Vfptr->At_0C)(*(LinkClass*)this);
        (down->*down->Vfptr->At_0C)(*(LinkClass*)this);
        (scroller->*scroller->Vfptr->At_0C)(*(LinkClass*)this);
        (up->*up->Vfptr->At_48)();
        (down->*down->Vfptr->At_48)();
        (scroller->*scroller->Vfptr->At_48)();
        SliderShim* slider = (SliderShim*)&Scroller;
        (slider->*slider->Vfptr->At_88)(List.Count);
        (slider->*slider->Vfptr->At_A8)(LineCount);
        (slider->*slider->Vfptr->At_8C)(CurrentTopIndex);
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x557CB0
// ListClass::DisableScrollBar. A no-op if not active. Otherwise: restores
// Width, clears the flag, unhooks the Scroller and both ShapeButtons from the
// modal gadget chain (Remove, vtbl+0x24 on each -- the same three calls the
// destructor makes when torn down while scrolling), and marks for redraw.
// Same vtable-pointer-before-the-arithmetic lever as the destructor above;
// without it this stalls at 85.7% on four transposed instructions.
int ListClass::DisableScrollBar()
{
    if (IsScrollActive) {
        GadgetVtbl* scrollerVt = ((GadgetShim*)&Scroller)->Vfptr;
        Width += ((GadgetShim*)&Scroller)->Width;
        IsScrollActive = false;
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scrollerVt->At_24)();
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*up->Vfptr->At_24)();
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_24)();
        (this->*Vfptr->At_48)();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x557E10
// ListClass::Add. While scrolling is active, splices the Scroller and both
// ShapeButtons into the same list `object` is joining (vtbl+0xC on each, in
// Scroller/DownButton/UpButton order), then chains to the non-virtual base
// LinkClass::Add and returns its result (which is itself HeadOfList()).
// Each child pointer is declared where it is first used: hoisting all three
// to the top of the arm instead costs the whole body (0%).
LinkClass* ListClass::Add(LinkClass& object)
{
    if (IsScrollActive) {
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scroller->Vfptr->At_0C)(object);
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_0C)(object);
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*up->Vfptr->At_0C)(object);
    }
    return BaseAdd(object);
}

// FUNCTION: GAMEMD 0x557E60
// ListClass::AddHead. Same shape as Add immediately above, but splices via
// vtbl+0x14 (AddHead) and chains to the non-virtual base LinkClass::AddHead.
LinkClass* ListClass::AddHead(LinkClass& object)
{
    if (IsScrollActive) {
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scroller->Vfptr->At_14)(object);
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_14)(object);
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*up->Vfptr->At_14)(object);
    }
    return BaseAddHead(object);
}

// FUNCTION: GAMEMD 0x557EB0
// ListClass::AddTail. Unlike Add/AddHead above, chains to the non-virtual
// base LinkClass::AddTail *first*, unconditionally; only then, while
// scrolling is active, splices the three children in (vtbl+0x10 on each, in
// UpButton/DownButton/Scroller order -- the reverse of Add/AddHead); and
// returns `this->HeadOfList()` (vtbl+0x18) explicitly rather than the base
// call's own result. Not auto-detected by `decompile` (recovered from the
// raw-byte sweep + the vtable read); no worklist row names it.
//
// The trailing self-dispatch must read `Vfptr` at its use site. Caching it
// into a local above the base call -- the inverse lever, and the right one in
// the destructor and Enable/DisableScrollBar -- costs the whole body (0%),
// because retail loads `[ESI]` at 0x557EF1, after every call has returned.
LinkClass* ListClass::AddTail(LinkClass& object)
{
    BaseAddTail(object);
    if (IsScrollActive) {
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*up->Vfptr->At_10)(object);
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_10)(object);
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scroller->Vfptr->At_10)(object);
    }
    return (this->*Vfptr->At_18)();
}

// FUNCTION: GAMEMD 0x557F00
// ListClass::Remove. While scrolling is active, unhooks the Scroller and both
// ShapeButtons (vtbl+0x24 on each, Scroller/DownButton/UpButton order), then
// chains to the non-virtual base GadgetClass::Remove. No worklist row names
// this either; found the same way as AddTail above.
LinkClass* ListClass::Remove()
{
    if (IsScrollActive) {
        GadgetShim* scroller = (GadgetShim*)&Scroller;
        (scroller->*scroller->Vfptr->At_24)();
        GadgetShim* down = (GadgetShim*)&DownButton;
        (down->*down->Vfptr->At_24)();
        GadgetShim* up = (GadgetShim*)&UpButton;
        (up->*up->Vfptr->At_24)();
    }
    return BaseRemove();
}
