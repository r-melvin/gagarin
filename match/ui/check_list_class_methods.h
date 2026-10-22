// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI at 0x4882D0 / 0x488310 / 0x488380 / 0x4883F0 / 0x4884A0 / 0x4886E0.
//   The run carried no name in any worklist; the owning class came out of the
//   runtime type information behind the vtable the destructors install:
//     0x7E4F84 - 4 -> 0x7FD150 (complete object locator)
//     0x7FD150 + 0xC -> 0x81D128 (type descriptor)
//     0x81D128 + 8 -> ".?AVCheckListClass@@"
//   Every offset and virtual slot below is confirmed numerically from
//   the disassembly.
//
// CheckListClass -- a ListClass whose entries are check boxes. Each entry is a
// small heap node holding the text and the checked flag, so the class owns its
// entries and has to free them itself.
//
// Layout, member by member from the disassembly:
//   +0x000  vptr           `MOV [ESI],0x7E4F84` in both destructor copies
//   +0x034  List           the base list's own entry vector; its Count
//                          at +0x44 is the `MOV EAX,[ESI+0x44]` loop guard
//   +0x16C  SelectedIndex  `MOV EAX,[ESI+0x16C]` twice in Action
//   +0x174  IsReadOnly     `MOV AL,[ESI+0x174]`; a byte, tested and returned
//                          from as the early exit
//
// Virtual slots reached from here (all through the primary vtable):
//   +0x48  Flag_To_Redraw()      no arguments
//   +0x94  Count()               no arguments, int result, the loop bound
//   +0xB8  <select by index>(int)
#ifndef GG_MATCH_UI_CHECK_LIST_CLASS_METHODS_H
#define GG_MATCH_UI_CHECK_LIST_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../core/vector_class.h"

void* __cdecl operator new(size_t);
void  __cdecl operator delete(void*);

// VTABLE: GAMEMD 0x007E4F84 — CheckListClass
extern char VT_007E4F84[];

// FUNCTION: GAMEMD 0x7DD0F8 (decl; reloc) — the wide-string compare the two
// text lookups run; __cdecl, two pushed arguments, `ADD ESP,8` afterwards.
extern "C" int __cdecl wcscmp(wchar_t const* a, wchar_t const* b);

// The heap node one entry becomes. `PUSH 8` sizes it, `MOV [EAX],ECX` writes
// the text and `MOV BYTE PTR [EAX+4],0` the flag, so it is exactly two members
// and eight bytes. The no-throw specification keeps the allocation out of an
// unwind frame that retail has no trace of under /GX, the tree's earlier
// flag set.
struct CheckItemClass
{
    wchar_t const* Text;       // +0x00
    bool           IsTicked;  // +0x04

    CheckItemClass(wchar_t const* text) throw() : Text(text), IsTicked(false) {}
};
GG_STATIC_ASSERT(offsetof(CheckItemClass, IsTicked) == 0x04);
GG_STATIC_ASSERT(sizeof(CheckItemClass) == 8);

// DynamicVectorClass<wchar_t const*> — the base list's entry vector (RTTI
// VectorClass<unsigned short const*> at 0x7ED1FC; VC6's wchar_t is unsigned
// short). Only the active count is reached from this TU, at List+0x10 ==
// this+0x44. Its own offsets are asserted with the canonical template.
typedef DynamicVectorClass<wchar_t const*> TextDynVector;
GG_STATIC_ASSERT(sizeof(TextDynVector) == 0x18);

struct CheckListVtbl;

class CheckListClass
{
public:
    CheckListVtbl* Vfptr;                   // +0x000
    char           _pad004[0x34 - 0x04];    // +0x004
    TextDynVector  List;                    // +0x034
    char           _pad04C[0x16C - 0x4C];   // +0x04C
    int            SelectedIndex;           // +0x16C
    char           _pad170[0x174 - 0x170];  // +0x170
    bool           IsReadOnly;              // +0x174

    // FUNCTION: GAMEMD 0x557600 (decl; reloc) — ListClass::~ListClass
    void ListClass_Dtor();
    // FUNCTION: GAMEMD 0x5576A0 (decl; reloc) — ListClass::Add_Item
    void ListClass_AddItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x557730 (decl; reloc) — ListClass::Remove_Item(index)
    void ListClass_RemoveItem(int index);
    // FUNCTION: GAMEMD 0x557830 (decl; reloc) — ListClass::Action
    int  ListClass_Action(unsigned flags, void* key, int extra);
    // FUNCTION: GAMEMD 0x557AC0 (decl; reloc) — ListClass::Get_Item(index)
    void* ListClass_GetItem(int index);

    // FUNCTION: GAMEMD 0x4882D0
    void Dtor();
    // FUNCTION: GAMEMD 0x488310
    void AddItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x488380
    void RemoveItem(wchar_t const* text);
    // FUNCTION: GAMEMD 0x4883F0
    void FUN_004883F0(wchar_t const* text);
    // FUNCTION: GAMEMD 0x4884A0
    int  Action(unsigned flags, void* key, int extra);
    // FUNCTION: GAMEMD 0x4886E0
    CheckListClass* ScalarDeletingDtor(unsigned char flags);
};

GG_STATIC_ASSERT(offsetof(CheckListClass, List)          == 0x034);
GG_STATIC_ASSERT(offsetof(CheckListClass, SelectedIndex) == 0x16C);
GG_STATIC_ASSERT(offsetof(CheckListClass, IsReadOnly)    == 0x174);
// The loop guard the two destructor copies read is List.Count, and it
// has to land on +0x44 for `MOV EAX,[ESI+0x44]` to be that member.
GG_STATIC_ASSERT(offsetof(CheckListClass, List) +
                 offsetof(TextDynVector, Count) == 0x44);

// The class has to be complete before these, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef void (CheckListClass::*FlagToRedrawFn)();
typedef int  (CheckListClass::*CountFn)();
typedef void (CheckListClass::*SelectFn)(int);

struct CheckListVtbl
{
    char           _pad00[0x48];            // 0x00
    FlagToRedrawFn At_48;                   // 0x48
    char           _pad4C[0x94 - 0x4C];     // 0x4C
    CountFn        At_94;                   // 0x94
    char           _pad98[0xB8 - 0x98];     // 0x98
    SelectFn       At_B8;                   // 0xB8
};
GG_STATIC_ASSERT(offsetof(CheckListVtbl, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(CheckListVtbl, At_94) == 0x94);
GG_STATIC_ASSERT(offsetof(CheckListVtbl, At_B8) == 0xB8);

#endif  // GG_MATCH_UI_CHECK_LIST_CLASS_METHODS_H
