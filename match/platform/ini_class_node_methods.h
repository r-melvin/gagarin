// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | TS++-cross-check
//   Every offset, every call target and every vtable address below was read
//   numerically off the user's own retail gamemd.exe v1.001 through the local
//   Ghidra CLI. EA's GPLv3 Red Alert 1 release (CODE/INI.CPP, CODE/LISTNODE.H)
//   and the GPLv3 TS++ headers (src/lib/ini.h, src/lib/listnode.h,
//   src/lib/wwcrc.h) were read for member NAMES and algorithm shape only;
//   nothing is transcribed from either and every offset is re-derived from the
//   binary. No YRpp header was consulted for this cluster.
//
// The INI node cluster at 0x52AA90-0x52AF41: the two static line-classifier
// helpers INIClass uses while parsing, the INIEntry / INISection node
// destructors and their scalar deleting thunks, the GenericList constructor
// that seeds an empty doubly-linked list, and the CRCEngine constructor that
// sits in the same address run because INIClass hashes every section and entry
// name through it.
//
// CLASS IDENTIFICATION (the word four bytes before each vtable is the complete
// object locator; its field at +0x0C is the type descriptor; the name starts
// eight bytes into that):
//   0x7EB730 -> 0x803668 -> 0x825AF0 -> ".?AUINIEntry@INIClass@@"
//   0x7EB738 -> 0x803708 -> 0x825B40 -> ".?AUINISection@INIClass@@"
//   0x7EB740 -> 0x803600 -> 0x825A90 -> ".?AV?$List@PAUINIEntry@INIClass@@@@"
//   0x7EB748 -> 0x8036A0 -> 0x825B10 -> ".?AV?$Node@PAUINISection@INIClass@@@@"
//   0x7EB750 -> 0x8035B0 -> 0x825A70 -> ".?AVCacheStraw@@"
//   0x7E1B00 -> 0x7FAD18 -> 0x817508 -> ".?AVGenericList@@"
//   0x7E1B08 -> 0x7FACD0 -> 0x8174E8 -> ".?AVGenericNode@@"
// So the vtable itself is the word AFTER each locator: GenericNode's is
// 0x7E1B0C, GenericList's 0x7E1B04, INIEntry's 0x7EB734, INISection's
// 0x7EB73C, Node<INISection*>'s 0x7EB74C, CacheStraw's 0x7EB754. Each of the
// INI vtables is one slot wide - the only virtual any of these classes has is
// its destructor, whose seat holds the scalar deleting thunk.
//
// MODELLING NOTE. Every class here is written as a plain struct carrying its
// vtable pointer as an ordinary `void* Vtable` member at +0x00, and each
// vtable seat is stored through an extern stand-in symbol. Slot zero is
// treated as an ordinary virtual holding the deleting-destructor thunk rather
// than as a C++ virtual destructor: that keeps the seat stores under our
// control (cl never expands an explicit destructor call, and it re-orders the
// compiler-generated vptr store relative to the member initialisers), and it
// keeps every later slot index right for classes with wider vtables.
#ifndef GG_MATCH_PLATFORM_INI_CLASS_NODE_METHODS_H
#define GG_MATCH_PLATFORM_INI_CLASS_NODE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Vtable stand-ins. Only the relocation is emitted, so one extern symbol per
// retail vtable address reproduces the `MOV dword ptr [reg],imm32` seat store.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E1B04  GenericList
extern "C" void* GG_VTABLE_GENERICLIST;
// VTABLE: GAMEMD 0x7E1B0C  GenericNode
extern "C" void* GG_VTABLE_GENERICNODE;
// VTABLE: GAMEMD 0x7EB734  INIClass::INIEntry
extern "C" void* GG_VTABLE_INIENTRY;
// VTABLE: GAMEMD 0x7EB73C  INIClass::INISection
extern "C" void* GG_VTABLE_INISECTION;
// VTABLE: GAMEMD 0x7EB744  List<INIClass::INIEntry*>
extern "C" void* GG_VTABLE_LISTOFINIENTRY;
// These two are never seated by any body in this TU - their classes add
// nothing to GenericNode, so the derived seat store is dead and cl drops it -
// but the slot-zero bodies below belong to them, so the addresses are recorded.
// VTABLE: GAMEMD 0x7EB74C  Node<INIClass::INISection*>
// VTABLE: GAMEMD 0x7EB754  CacheStraw

// ---------------------------------------------------------------------------
// CRT and game-heap primitives, declared so cl emits reloc-normalised calls.
// The two deallocators are genuinely different functions in retail: the string
// members go through the CRT `free` at 0x7C93E8 (it locks heap 9 and calls the
// block walker at 0x7CF7BD), while the heap-allocated nodes and index tables go
// through `operator delete` at 0x7C8B3D.
// ---------------------------------------------------------------------------
// LIBRARY: GAMEMD 0x7C93E8  CRT free
extern "C" void  __cdecl FUN_007C93E8(void* block);
// LIBRARY: GAMEMD 0x7C8B3D  operator delete
extern "C" void  __cdecl FUN_007C8B3D(void* block);
// LIBRARY: GAMEMD 0x7CAF30  CRT strchr
extern "C" char* __cdecl FUN_007CAF30(const char* string, int ch);
// FUNCTION: GAMEMD 0x727CF0  strtrim - trims leading and trailing whitespace
// in place. Takes its buffer in ECX and pops nothing, so it is __fastcall.
void __fastcall FUN_00727CF0(char* buffer);
// FUNCTION: GAMEMD 0x43AE50  the buffer-holder destructor CacheStraw runs on
// its member at +0x0C.
void __fastcall FUN_0043AE50(void* self);
// FUNCTION: GAMEMD 0x6C9850  Straw::~Straw - CacheStraw's base destructor.
void __fastcall FUN_006C9850(void* self);

// Slot zero of every class in this cluster: the scalar deleting destructor.
// `this` in ECX, the flag word pushed, the object returned in EAX. Modelled as
// slot zero of an abstract stand-in so the indirect call keeps retail's shape
// (`MOV EDX,[ECX]` / `PUSH 1` / `CALL [EDX]`); the stand-in is never
// instantiated, so no vtable of its own is emitted.
struct GG_Deletable
{
    virtual void* DeletingDestructor(unsigned int flags) = 0;
};

// ---------------------------------------------------------------------------
// GenericNode - the doubly-linked list node every INI record is threaded on.
// Offsets confirmed from the unlink sequence shared by 0x52AAF0, 0x52AB80,
// 0x52AD50 and 0x52AE20: `MOV ECX,[ESI+4]` then `MOV EAX,[ESI+8]` then
// `MOV [EAX+4],ECX` proves NextNode is at +0x04 and PrevNode at +0x08, because
// the first store is PrevNode->NextNode = NextNode.
// ---------------------------------------------------------------------------
struct GenericNode
{
    void*        Vtable;     // +0x00
    GenericNode* NextNode;   // +0x04
    GenericNode* PrevNode;   // +0x08

    // The guard retail spells out three times per unlink: `CMP ESI,EBX`,
    // `CMP EBX,[ECX+4]`, `CMP EBX,[ECX+8]`, in that order.
    __forceinline bool IsValid() const;
    __forceinline void Unlink();
    __forceinline void Link(GenericNode* node);
    // What the GenericNode destructor collapses to once inlined: seat the base
    // vtable, then unlink.
    __forceinline void DestroyNode();
    // What the GenericNode constructor collapses to. Retail writes the two
    // links before the seat, so they are written in that order here.
    __forceinline void InitNode();
};

GG_STATIC_ASSERT(offsetof(GenericNode, Vtable)   == 0x00 &&
                 offsetof(GenericNode, NextNode) == 0x04 &&
                 offsetof(GenericNode, PrevNode) == 0x08 &&
                 sizeof(GenericNode) == 0x0C);

// ---------------------------------------------------------------------------
// GenericList - a head sentinel and a tail sentinel linked to each other.
// The layout falls straight out of 0x52ACE0: `LEA ESI,[EAX+4]` is FirstNode
// and `LEA EDX,[EAX+0x10]` is LastNode, so the list itself is 0x1C bytes.
// ---------------------------------------------------------------------------
struct GenericList
{
    void*       Vtable;      // +0x00
    GenericNode FirstNode;   // +0x04
    GenericNode LastNode;    // +0x10

    // What the GenericList constructor collapses to: build both sentinels,
    // seat the list, and link the head to the tail. It is shared by the plain
    // list at 0x52ACE0 and the List<INIEntry*> instantiation at 0x52AF50,
    // which carries the identical body with one extra seat store, so it is
    // forced inline: cl emits a call rather than an expansion for an ordinary
    // base constructor, and retail has no such call.
    __forceinline void InitList();

    // First() is the head sentinel's forward link, which is why INISection's
    // destructor reads [ESI+0x18] for a list seated at +0x10.
    GenericNode* First() const { return FirstNode.NextNode; }
    __forceinline void DestroyList();
};

// The bare GenericList instantiation. Its constructor is the one class in the
// cluster whose body is shared, so the constructor sits on a derived stand-in
// rather than on GenericList itself: a user-declared base constructor would
// force cl to emit a call to it from List<INIEntry*>'s constructor.
struct GenericListObject : public GenericList
{
    // FUNCTION: GAMEMD 0x52ACE0
    GenericListObject();
};

GG_STATIC_ASSERT(offsetof(GenericList, FirstNode) == 0x04 &&
                 offsetof(GenericList, LastNode)  == 0x10 &&
                 sizeof(GenericList) == 0x1C);

// ---------------------------------------------------------------------------
// IndexClass, as seen from here. The layout is the one already confirmed in
// match/core/index_class.h, and INISection's destructor re-proves it: the
// table is freed from +0x2C and then +0x30, +0x34, +0x3C are zeroed as dwords
// while +0x38 is zeroed as a byte (`MOV [ESI+0x38],BL`).
// ---------------------------------------------------------------------------
struct IndexClassRaw
{
    void* IndexTable;   // +0x00
    int   IndexCount;   // +0x04
    int   IndexSize;    // +0x08
    char  IsSorted;     // +0x0C
    void* Archive;      // +0x10

    __forceinline void Clear();
};

GG_STATIC_ASSERT(offsetof(IndexClassRaw, IndexCount) == 0x04 &&
                 offsetof(IndexClassRaw, IndexSize)  == 0x08 &&
                 offsetof(IndexClassRaw, IsSorted)   == 0x0C &&
                 offsetof(IndexClassRaw, Archive)    == 0x10 &&
                 sizeof(IndexClassRaw) == 0x14);

// ---------------------------------------------------------------------------
// INIComment - one retained comment line. The destructors walk the chain
// reading the text at +0x00 and the successor at +0x04.
// ---------------------------------------------------------------------------
struct INIComment
{
    char*       Comment;   // +0x00
    INIComment* Next;      // +0x04
};

GG_STATIC_ASSERT(offsetof(INIComment, Next) == 0x04 && sizeof(INIComment) == 0x08);

// ---------------------------------------------------------------------------
// INIClass::INIEntry - one `key=value` line. The seven-dword tail is pinned by
// the constructor at 0x52AF00, which takes seven arguments (`RET 0x1C`) and
// lands them at +0x0C, +0x10, +0x14, +0x18, +0x1C, +0x20 and +0x24; the fifth
// argument going to +0x24 while the sixth and seventh go to +0x1C and +0x20 is
// what proves the cursor members are declared in the order below and
// initialised out of order by the member-initialiser list.
// ---------------------------------------------------------------------------
struct INIEntry : public GenericNode
{
    char*       Entry;              // +0x0C
    char*       Value;              // +0x10
    INIComment* Comments;           // +0x14
    char*       CommentString;      // +0x18
    int         PreIndentCursor;    // +0x1C
    int         PostIndentCursor;   // +0x20
    int         CommentCursor;      // +0x24

    // FUNCTION: GAMEMD 0x52AF00
    INIEntry(char* entry, char* value, INIComment* comments, char* commentstring,
             int commentcursor, int preindentcursor, int postindentcursor);

    // FUNCTION: GAMEMD 0x52AAF0
    void DestroyEntry();
    // FUNCTION: GAMEMD 0x52AD50  vtable 0x7EB734 slot 0
    void* DeletingDestructor(unsigned int flags);
};

GG_STATIC_ASSERT(offsetof(INIEntry, Entry)            == 0x0C &&
                 offsetof(INIEntry, Value)            == 0x10 &&
                 offsetof(INIEntry, Comments)         == 0x14 &&
                 offsetof(INIEntry, CommentString)    == 0x18 &&
                 offsetof(INIEntry, PreIndentCursor)  == 0x1C &&
                 offsetof(INIEntry, PostIndentCursor) == 0x20 &&
                 offsetof(INIEntry, CommentCursor)    == 0x24 &&
                 sizeof(INIEntry) == 0x28);

// ---------------------------------------------------------------------------
// INIClass::INISection - one bracketed section. The destructor at 0x52AB80
// pins every offset: the name freed from +0x0C, the entry list worked at
// +0x10 (its head sentinel's forward link at +0x18), the entry index freed and
// zeroed across +0x2C..+0x3C, and the comment chain drained from +0x40.
// ---------------------------------------------------------------------------
struct INISection : public GenericNode
{
    char*         Section;      // +0x0C
    GenericList   EntryList;    // +0x10
    IndexClassRaw EntryIndex;   // +0x2C
    INIComment*   Comments;     // +0x40

    INIEntry* FirstEntry() const { return (INIEntry*)EntryList.First(); }

    // FUNCTION: GAMEMD 0x52AB80
    void DestroySection();
};

GG_STATIC_ASSERT(offsetof(INISection, Section)    == 0x0C &&
                 offsetof(INISection, EntryList)  == 0x10 &&
                 offsetof(INISection, EntryIndex) == 0x2C &&
                 offsetof(INISection, Comments)   == 0x40 &&
                 sizeof(INISection) == 0x44);

// ---------------------------------------------------------------------------
// Node<INISection*> - the bare node instantiation INIClass keeps its section
// list on. Nothing but the inherited destructor is ever emitted for it.
// ---------------------------------------------------------------------------
struct NodeOfINISection : public GenericNode
{
    // FUNCTION: GAMEMD 0x52AE20  vtable 0x7EB74C slot 0
    void* DeletingDestructor(unsigned int flags);
};

// ---------------------------------------------------------------------------
// List<INIClass::INIEntry*> - the list instantiation INISection threads its
// entries on. It adds nothing to GenericList but its own vtable seat, which is
// why its constructor is the base constructor with one extra store and its
// destructor carries no seat of its own at all (the derived store is dead,
// overwritten immediately by the base's).
// ---------------------------------------------------------------------------
struct ListOfINIEntry : public GenericList
{
    // FUNCTION: GAMEMD 0x52AF50
    ListOfINIEntry();
    // FUNCTION: GAMEMD 0x52AFC0  vtable 0x7EB744 slot 0
    void* DeletingDestructor(unsigned int flags);
};

GG_STATIC_ASSERT(sizeof(ListOfINIEntry) == 0x1C);

// ---------------------------------------------------------------------------
// CacheStraw - unrelated to INI, but its deleting destructor is seated inside
// this address run. The class is opaque apart from the sub-object at +0x0C
// whose destructor runs first.
// ---------------------------------------------------------------------------
struct CacheStraw
{
    // FUNCTION: GAMEMD 0x52AE70  vtable 0x7EB754 slot 0
    void* DeletingDestructor(unsigned int flags);
};

// ---------------------------------------------------------------------------
// CRCEngine - the hash INIClass indexes section and entry names with. Three
// dwords: the running value, the staging index and the staging word.
// ---------------------------------------------------------------------------
struct CRCEngine
{
    long CRC;             // +0x00
    int  Index;           // +0x04
    long StagingBuffer;   // +0x08

    // FUNCTION: GAMEMD 0x52AEC0
    CRCEngine(long initial);
};

GG_STATIC_ASSERT(offsetof(CRCEngine, Index)         == 0x04 &&
                 offsetof(CRCEngine, StagingBuffer) == 0x08 &&
                 sizeof(CRCEngine) == 0x0C);

// ---------------------------------------------------------------------------
// The two static line classifiers. Both take their buffer in ECX and pop
// nothing, which for a one-pointer function is __fastcall.
// ---------------------------------------------------------------------------
struct INIClass
{
    // FUNCTION: GAMEMD 0x52AA90
    static void __fastcall Strip_Comments(char* buffer);
    // FUNCTION: GAMEMD 0x52AAC0
    static bool __fastcall Line_Contains_Section(char* buffer);
};

#endif  // GG_MATCH_PLATFORM_INI_CLASS_NODE_METHODS_H
