// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI, address run 0x557600-0x557F40 (plus the shared vtable read at
//   0x7ED10C). This whole run carried NO worklist row under its true name; the
//   private-reference seed misfiled eleven of these bodies under "ai/ai_functions_
//   batch2.cpp" (cell "ai") because the pool-address heuristic that seeded the
//   cell had no class name to key on. The owning class came out of the
//   destructor's own vtable store instead:
//     0x557609  MOV [ESI],0x7ed10c            -- ListClass's own vtable
//     0x7ed108 -4 -> 0x00805218  (complete object locator)
//     0x00805218 + 0xC -> 0x0081d110  (type descriptor)
//     0x0081d110 + 8 -> ".?AVListClass@@"
//   and the immediately-following type descriptor at 0x0081d128 decodes to
//   ".?AVCheckListClass@@", which cross-checks the already-matched
//   match/ui/check_list_class_methods.h (the two classes' RTTI blocks are
//   laid down back to back in .rdata).
//
//   ListClass is ControlClass's list widget (RTTI ListClass): a text vector plus a live vertical SliderClass with two
//   ShapeButtonClass end buttons, spliced into and out of the same modal
//   gadget chain as the list itself whenever scrolling is active. The full
//   51-slot primary vtable was read as one block (0x7ED10C, 200 bytes) and
//   gives real membership + slot order independent of any worklist entry;
//   several bodies below (the dtor, the Add/AddHead/AddTail/Remove overrides)
//   carry no worklist row at all and were found purely by that read plus the
//   raw-byte sweep between confirmed entries (`objdump -D -b binary -m i386`
//   over 4096-byte `ghidra memory read` chunks) -- the sweep is what turned
//   up 0x557E10/0x557E60/0x557EB0/0x557F00 and the dtor at 0x557600, none of
//   which are auto-detected `decompile` targets (0x557EB0 in particular).
//
//   ListClass's own primary vtable @0x007ED10C, slots reached from this TU
//   (byte offset -> retail address; "(self)" marks a slot on `this`'s own
//   vtable reached again indirectly rather than a foreign object):
//     +0x00 ~ListClass (scalar-deleting thunk)      0x558060  (not matched here)
//     +0x0C Add(LinkClass&)         [was LinkClass::Add]        0x557E10
//     +0x10 AddTail(LinkClass&)     [was LinkClass::AddTail]    0x557EB0
//     +0x14 AddHead(LinkClass&)     [was LinkClass::AddHead]    0x557E60
//     +0x24 Remove()                [was GadgetClass::Remove]   0x557F00
//     +0x48 MarkRedraw (self)                                   0x557FD0 (decl only)
//     +0x88 AddItem(wchar_t const*)                              0x5576A0
//     +0x8C EnableScrollBar()                                    0x557BE0
//     +0x90 Bump(int)                                            0x557A20
//     +0x9C GetCurrentItem()                                     0x557AE0
//     +0xA0 GetItem(int)                                         0x557AC0
//     +0xA4 StepSelectedIndex(int) (self, decl only)             0x557FB0
//     +0xA8 RemoveItem(int)                                      0x557730
//     +0xAC RemoveItem(wchar_t const*)                           0x557800
//     +0xB0 DisableScrollBar()                                   0x557CB0
//     +0xC0 SetViewIndex(int)                                    0x557B70
//     +0xC4 Step(int)                                            0x557A70
//     +0x7C Action(unsigned,unsigned*,int) [ControlClass slot]   0x557830
//   Bump (0x557A20) and Step (0x557A70) disassemble byte-for-byte identical
//   apart from relative addresses -- two vtable slots compiled from the same
//   source shape, not a shared body (each survives independently at its own
//   address; see the byte-identical-siblings rule banked in
//   docs/matching_methodology_and_toolchain.md).
//
// Layout, member by member, confirmed numerically from THIS TU's own
// disassembly only (fields this TU never touches stay `unknown_XX` gaps
// rather than borrowing unconfirmed names from the consult-only re_finding):
//   +0x00  Vfptr           `MOV [ESI],0x7ed10c` in the destructor
//   +0x10  Y               `MOV EDX,[ESI+0x10]` in Action's hit-test
//   +0x14  Width           `param_1[5] +=/-= Scroller.Width` in the
//                          destructor / Enable/DisableScrollBar
//   +0x34  List            TextDynVector; `MOV [ESI+0x34],0x7ed1fc` (its own
//                          dtor-installed vtable) plus +0x38/+0x3C/+0x41/+0x44
//                          (Vector/Capacity/IsAllocated/Count) read
//                          throughout every body here
//   +0x4C  LineHeight      `IDIV [ESI+0x4c]` in Action
//   +0x50  LineCount       `CMP [ESI+0x50]` in AddItem/RemoveItem/SetViewIndex
//   +0x54  IsScrollActive  `MOV AL,[ESI+0x54]` in every body here
//   +0x58  UpButton        `LEA ECX,[ESI+0x58]` (ShapeButtonClass, opaque --
//                          only its vptr and its own +0x14 Width, at +0x6C
//                          absolute via the sibling below, are ever read)
//   +0xB8  DownButton      `LEA ECX,[ESI+0xB8]` (ShapeButtonClass, opaque)
//   +0x118 Scroller        `LEA ECX,[ESI+0x118]` (SliderClass, opaque);
//                          Scroller+0x14 = 0x12C is its own inherited
//                          GadgetClass::Width, read/written by the
//                          destructor and Enable/DisableScrollBar
//   +0x16C SelectedIndex   `MOV [ESI+0x16c],EAX` in Action/RemoveItem
//   +0x170 CurrentTopIndex `MOV [ESI+0x170],EAX` in Action/SetViewIndex/
//                          Bump/Step/RemoveItem
// sizeof(ListClass) == 0x174, matching the already-independently-confirmed
// CheckListClass::IsReadOnly / ColorListClass::Colors start address (both
// derived classes append their own fields starting exactly there).
#ifndef GG_MATCH_UI_LIST_CLASS_BASE_METHODS_H
#define GG_MATCH_UI_LIST_CLASS_BASE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../core/link_class_methods.h"
#include "../core/vector_class_operations.h"

// VTABLE: GAMEMD 0x007ED10C -- ListClass primary vtable (51 slots, read as one
// block; membership/order read from retail).
extern char VT_007ED10C[];

// ---------------------------------------------------------------------------
// TextDynVector -- DynamicVectorClass<wchar_t const*>, the base list's own
// entry vector at ListClass+0x34. Its destructor reseats 0x7ED1FC, which RTTI
// names VectorClass<unsigned short const*> (VC6's wchar_t is unsigned short).
// The canonical template; its own offsets are asserted with it.
// ---------------------------------------------------------------------------
typedef DynamicVectorClass<wchar_t const*> TextDynVector;
GG_STATIC_ASSERT(sizeof(TextDynVector) == 0x18);

struct ListClassVtbl;

// ---------------------------------------------------------------------------
// ListClass. ControlClass's list widget: a text vector, a scroll flag, and
// the two ShapeButtons + SliderClass that get spliced into the same modal
// gadget chain while scrolling is active. Only the members this TU's sixteen
// bodies actually touch are named; every other byte is an `unknown_XX` gap
// (LinkClass's Next/Previous, GadgetClass's X/Height/flags/..., ControlClass's
// ID/SendTo, and ListClass's own TextFlags/Tabs -- all confirmed elsewhere in
// docs/decomp_spec/re_findings/frontend_gadget_system.md but not independently
// re-derived by this TU, so they stay unnamed here per AGENTS.md). `Vfptr` is
// declared against the forward-declared `ListClassVtbl` above -- a pointer to
// an incomplete type is fine here; the pointer-to-member-function trick below
// needs ListClass itself complete first, which this definition provides.
// ---------------------------------------------------------------------------
// CONSOLIDATION NOTE (proposal): this view is non-polymorphic (an explicit
// Vfptr plus hand-built slot tables). The retail classes are polymorphic:
// ListClass : ControlClass : GadgetClass : LinkClass (vtable 0x7ED10C, 51 slots;
// new slots from +0x88 AddItem .. +0xC8 DrawItem, RemoveItem(int) at +0xA8 and
// RemoveItem(text) at +0xAC because VC6 lays overloaded virtuals out in reverse
// declaration order), CheckListClass : ListClass (0x7E4F84, IsReadOnly +0x174)
// and ColorListClass : ListClass (0x7E5054, 53 slots; Colors +0x174, Style
// +0x18C, SelectColor +0x190; new slots +0xCC AddItem(text, color), +0xD0
// SetStyle). A polymorphic model with embedded ShapeButtonClass (+0x58, +0xB8)
// and SliderClass (+0x118) members verifies all 51/53 slots and reproduces the
// compiler-emitted deleting destructors 0x558060 / 0x488F00 byte for byte (no
// /GX, destructor defined inline in its own TU). Moving these headers onto it
// changes the matched destructor TUs here, so it must be re-gated with
// verify_all.py before it lands; the code rewrite is not drafted in this patch.
class ListClass
{
public:
    ListClassVtbl*        Vfptr;               // +0x000
    unsigned char         unknown_004[0x0C - 0x04];  // LinkClass::Next/Previous
    unsigned char         unknown_00C[0x10 - 0x0C];  // GadgetClass::X
    int                   Y;                   // +0x010
    int                   Width;               // +0x014
    unsigned char         unknown_018[0x34 - 0x18];  // Height..Tabs
    TextDynVector         List;                // +0x034
    int                   LineHeight;          // +0x04C
    int                   LineCount;           // +0x050
    bool                  IsScrollActive;      // +0x054
    unsigned char         unknown_055[0x58 - 0x55];
    unsigned char         UpButton[0xB8 - 0x58];    // ShapeButtonClass (opaque)
    unsigned char         DownButton[0x118 - 0xB8]; // ShapeButtonClass (opaque)
    unsigned char         Scroller[0x16C - 0x118];  // SliderClass (opaque)
    int                   SelectedIndex;       // +0x16C
    int                   CurrentTopIndex;     // +0x170

    // FUNCTION: GAMEMD 0x557600
    void Dtor();
    // FUNCTION: GAMEMD 0x5576A0
    int AddItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x557730
    void RemoveItem(int index);
    // FUNCTION: GAMEMD 0x557800
    void RemoveItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x557830
    unsigned Action(unsigned flags, unsigned* key, int extra);
    // FUNCTION: GAMEMD 0x557A20
    void Bump(int minus);
    // FUNCTION: GAMEMD 0x557A70
    void Step(int minus);
    // FUNCTION: GAMEMD 0x557AC0
    wchar_t const* GetItem(int index);
    // FUNCTION: GAMEMD 0x557AE0
    wchar_t const* GetCurrentItem();
    // FUNCTION: GAMEMD 0x557B70
    int SetViewIndex(int index);
    // FUNCTION: GAMEMD 0x557BE0
    int EnableScrollBar();
    // FUNCTION: GAMEMD 0x557CB0
    int DisableScrollBar();
    // FUNCTION: GAMEMD 0x557E10
    LinkClass* Add(LinkClass& object);
    // FUNCTION: GAMEMD 0x557E60
    LinkClass* AddHead(LinkClass& object);
    // FUNCTION: GAMEMD 0x557EB0
    LinkClass* AddTail(LinkClass& object);
    // FUNCTION: GAMEMD 0x557F00
    LinkClass* Remove();

    // The non-virtual base-class bodies this TU chains to. Declared, never
    // defined here: each is only a relocation target, and the receiver has to
    // arrive in ECX, which VC6 grants only to a member function (see the
    // stand-in rule in docs/matching_methodology_and_toolchain.md).
    void       BaseDtor();                        // GadgetClass::~GadgetClass 0x4E1390
    LinkClass* BaseAdd(LinkClass& object);        // LinkClass::Add            0x5566A0
    LinkClass* BaseAddHead(LinkClass& object);    // LinkClass::AddHead        0x5566D0
    LinkClass* BaseAddTail(LinkClass& object);    // LinkClass::AddTail        0x556700
    LinkClass* BaseRemove();                      // GadgetClass::Remove       0x4E1480
    unsigned   BaseAction(unsigned flags, unsigned* key, int extra); // ControlClass::Action 0x48E5A0
};

GG_STATIC_ASSERT(offsetof(ListClass, Y)               == 0x010);
GG_STATIC_ASSERT(offsetof(ListClass, Width)           == 0x014);
GG_STATIC_ASSERT(offsetof(ListClass, List)            == 0x034);
GG_STATIC_ASSERT(offsetof(ListClass, LineHeight)      == 0x04C);
GG_STATIC_ASSERT(offsetof(ListClass, LineCount)       == 0x050);
GG_STATIC_ASSERT(offsetof(ListClass, IsScrollActive)  == 0x054);
GG_STATIC_ASSERT(offsetof(ListClass, UpButton)        == 0x058);
GG_STATIC_ASSERT(offsetof(ListClass, DownButton)      == 0x0B8);
GG_STATIC_ASSERT(offsetof(ListClass, Scroller)        == 0x118);
GG_STATIC_ASSERT(offsetof(ListClass, SelectedIndex)   == 0x16C);
GG_STATIC_ASSERT(offsetof(ListClass, CurrentTopIndex) == 0x170);
GG_STATIC_ASSERT(sizeof(ListClass)                    == 0x174);
// The scroller's own inherited GadgetClass::Width sits at Scroller+0x14,
// i.e. ListClass+0x12C -- the destructor/Enable/DisableScrollBar's
// `param_1[0x4b]` (0x4b*4 == 0x12C). Confirmed via the shared GadgetClass
// leading layout (vptr,Next,Previous,X,Y,Width,...); pinned numerically here
// because it is read/written by name in this TU (see the .cpp).
GG_STATIC_ASSERT(offsetof(ListClass, Scroller) + 0x14 == 0x12C);

// ---------------------------------------------------------------------------
// ListClass's own primary vtable, modelled only for the four self-slots this
// TU dispatches through indirectly (AddItem/RemoveItem/EnableScrollBar/
// Action all call sibling ListClass virtuals -- some matched elsewhere in
// this same TU, some (MarkRedraw @0x557FD0, StepSelectedIndex @0x557FB0) not
// yet matched and declared here only as relocation targets). Per
// match/_rt/gg_vslot.h: the owning class must be complete before this
// pointer-to-member-function type is declared, hence ListClass is defined
// above and this typedef comes after.
// ---------------------------------------------------------------------------
typedef void (ListClass::*LC_SelfVoidFn)();
typedef void (ListClass::*LC_SelfIntFn)(int);

typedef LinkClass* (ListClass::*LC_SelfHeadFn)();

struct ListClassVtbl
{
    char          _pad00[0x18];
    LC_SelfHeadFn At_18;               // HeadOfList            (base slot, decl only)
    char          _pad1C[0x48 - 0x1C];
    LC_SelfVoidFn At_48;               // MarkRedraw            GAMEMD 0x557FD0 (decl only)
    char          _pad4C[0x8C - 0x4C];
    LC_SelfVoidFn At_8C;               // EnableScrollBar       GAMEMD 0x557BE0
    char          _pad90[0xA4 - 0x90];
    LC_SelfIntFn  At_A4;               // StepSelectedIndex     GAMEMD 0x557FB0 (decl only)
    LC_SelfIntFn  At_A8;               // RemoveItem(int)       GAMEMD 0x557730
    char          _padAC[0xB0 - 0xAC];
    LC_SelfVoidFn At_B0;               // DisableScrollBar      GAMEMD 0x557CB0
};
GG_STATIC_ASSERT(offsetof(ListClassVtbl, At_18) == 0x18);
GG_STATIC_ASSERT(offsetof(ListClassVtbl, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(ListClassVtbl, At_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(ListClassVtbl, At_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(ListClassVtbl, At_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(ListClassVtbl, At_B0) == 0xB0);

// ---------------------------------------------------------------------------
// GadgetShim -- the GadgetClass-level view shared by all three child widgets
// (UpButton, DownButton, Scroller). Only the leading vptr and the inherited
// GadgetClass::Width at +0x14 are modelled; the slots below are the ones this
// TU dispatches on a child, and they are the same six for all three because
// they are GadgetClass/LinkClass slots, not derived-class ones. The two
// destructor stand-ins beneath it exist for the same reason the Base* methods
// on ListClass do: the receiver has to reach the callee in ECX.
// ---------------------------------------------------------------------------
struct GadgetVtbl;
struct GadgetShim
{
    GadgetVtbl*   Vfptr;                  // +0x00
    unsigned char unknown_04[0x14 - 0x04];
    int           Width;                  // +0x14 (GadgetClass::Width)
};
typedef LinkClass* (GadgetShim::*GA_LinkFn)(LinkClass&);
typedef LinkClass* (GadgetShim::*GA_RemFn)();
typedef void       (GadgetShim::*GA_VoidFn)();
typedef void       (GadgetShim::*GA_PeerFn)(void*);

struct GadgetVtbl
{
    char      _pad00[0x0C];
    GA_LinkFn At_0C;   // Add(LinkClass&)      -- ListClass::Add / EnableScrollBar
    GA_LinkFn At_10;   // AddTail(LinkClass&)  -- ListClass::AddTail
    GA_LinkFn At_14;   // AddHead(LinkClass&)  -- ListClass::AddHead
    char      _pad18[0x24 - 0x18];
    GA_RemFn  At_24;   // Remove()             -- dtor / DisableScrollBar / Remove
    char      _pad28[0x48 - 0x28];
    GA_VoidFn At_48;   // MarkRedraw()         -- EnableScrollBar
    char      _pad4C[0x84 - 0x4C];
    GA_PeerFn At_84;   // MakePeer(this)       -- EnableScrollBar
};
GG_STATIC_ASSERT(offsetof(GadgetShim, Width)  == 0x14);
GG_STATIC_ASSERT(offsetof(GadgetVtbl, At_0C)  == 0x0C);
GG_STATIC_ASSERT(offsetof(GadgetVtbl, At_10)  == 0x10);
GG_STATIC_ASSERT(offsetof(GadgetVtbl, At_14)  == 0x14);
GG_STATIC_ASSERT(offsetof(GadgetVtbl, At_24)  == 0x24);
GG_STATIC_ASSERT(offsetof(GadgetVtbl, At_48)  == 0x48);
GG_STATIC_ASSERT(offsetof(GadgetVtbl, At_84)  == 0x84);

// The two child destructors the ListClass destructor calls non-virtually,
// SliderClass::~SliderClass @0x6B1D00 and ShapeButtonClass::~ShapeButtonClass
// @0x69DDC0. Declared only; `lea ecx,[esi+N]; call` is the whole contract.
struct SliderObj    { void Dtor(); };
struct ShapeBtnObj  { void Dtor(); };

// ---------------------------------------------------------------------------
// SliderShim -- a minimal stand-in for the embedded SliderClass Scroller,
// carrying only the leading vptr so the vtable slots this TU reaches on it
// can be dispatched with the correct __thiscall register/stack shape (see
// match/_rt/gg_vslot.h). SliderClass's own layout/naming is out of scope for
// this TU; only the four byte offsets below are exercised, and their retail
// addresses are not independently pinned here.
// ---------------------------------------------------------------------------
struct SliderVtbl;
struct SliderShim { SliderVtbl* Vfptr; };
typedef void (SliderShim::*SL_VoidIntFn)(int);
typedef int  (SliderShim::*SL_IntVoidFn)();
typedef int  (SliderShim::*SL_BoolIntFn)(int);

struct SliderVtbl
{
    char         _pad00[0x88];
    SL_VoidIntFn At_88;   // SetXxx(Count)     -- called from AddItem/EnableScrollBar/RemoveItem
    SL_VoidIntFn At_8C;   // SetXxx(CurrentTopIndex) -- called from SetViewIndex/EnableScrollBar
    SL_IntVoidFn At_90;   // GetXxx()                -- called from Bump/Step
    char         _pad94[0xA8 - 0x94];
    SL_VoidIntFn At_A8;   // SetXxx(LineCount)       -- called from EnableScrollBar
    char         _padAC[0xB0 - 0xAC];
    SL_BoolIntFn At_B0;   // Step(minus)             -- called from Bump/Step/RemoveItem
};
GG_STATIC_ASSERT(offsetof(SliderVtbl, At_88) == 0x88);
GG_STATIC_ASSERT(offsetof(SliderVtbl, At_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(SliderVtbl, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(SliderVtbl, At_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(SliderVtbl, At_B0) == 0xB0);

// ---------------------------------------------------------------------------
// MouseShim -- the mouse/cursor object behind the 0x00887640 pointer, modelled
// only for the one slot Action reaches: `MOV ECX,[DAT_00887640]; MOV EAX,[ECX];
// CALL [EAX+0x30]`, whose int result is the cursor Y used for the row hit-test.
// ---------------------------------------------------------------------------
struct MouseVtbl;
struct MouseShim { MouseVtbl* Vfptr; };
typedef int (MouseShim::*MS_IntVoidFn)();
struct MouseVtbl
{
    char         _pad00[0x30];
    MS_IntVoidFn At_30;   // cursor Y -- called from ListClass::Action
};
GG_STATIC_ASSERT(offsetof(MouseVtbl, At_30) == 0x30);

// GLOBAL: GAMEMD 0x00887640 -- the mouse/cursor singleton pointer.
extern "C" MouseShim* DAT_00887640;

#endif  // GG_MATCH_UI_LIST_CLASS_BASE_METHODS_H
