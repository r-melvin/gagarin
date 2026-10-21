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
// MODELLING NOTE. The shared intrusive-node layouts expose an explicit
// `void* Vtable` member at +0x00; each
// vtable seat is stored through an extern stand-in symbol. Slot zero is
// treated as an ordinary virtual holding the deleting-destructor thunk rather
// than as a C++ virtual destructor: that keeps the seat stores under our
// control (cl never expands an explicit destructor call, and it re-orders the
// compiler-generated vptr store relative to the member initialisers), and it
// keeps every later slot index right for classes with wider vtables.
#ifndef GG_MATCH_PLATFORM_INI_CLASS_NODE_METHODS_H
#define GG_MATCH_PLATFORM_INI_CLASS_NODE_METHODS_H

#include <stddef.h>
#include "../_layout/generic_list.h"
#include "../_layout/index_class_layout.h"
#include "../_layout/ini_class.h"
#include "../_layout/memory_buffer.h"
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
typedef void* (List<INIClass::INIEntry*>::*INIEntryListDeletingSlot)(unsigned int);
extern "C" INIEntryListDeletingSlot GG_VTABLE_LISTOFINIENTRY;
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
// INIComment - one retained comment line. The destructors walk the chain
// reading the text at +0x00 and the successor at +0x04.
// ---------------------------------------------------------------------------
// Nested node layouts and assertions are shared by INI lookups and lifetime code.
#include "../_layout/ini_nodes.h"
typedef INIClass::INIEntry INIEntry;
typedef INIClass::INISection INISection;

// ---------------------------------------------------------------------------
// Node<INISection*> - the bare node instantiation INIClass keeps its section
// list on. Nothing but the inherited destructor is ever emitted for it.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// List<INIClass::INIEntry*> - the list instantiation INISection threads its
// entries on. It adds nothing to GenericList but its own vtable seat, which is
// why its constructor is the base constructor with one extra store and its
// destructor carries no seat of its own at all (the derived store is dead,
// overwritten immediately by the base's).
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// CacheStraw - unrelated to INI, but its deleting entry is seated inside this
// address run. The binary clears a 0x0C sub-object at +0x0C before calling the
// Straw base routine; original member ownership is not established here.
// ---------------------------------------------------------------------------
struct CacheStraw
{
    char unknown_00[0x0C];
    MemoryBuffer Buffer; // +0x0C, passed to MemoryBuffer::Clear by the deleting entry

    // FUNCTION: GAMEMD 0x52AE70  vtable 0x7EB754 slot 0
    void* DeletingDestructor(unsigned int flags);
};
GG_STATIC_ASSERT(offsetof(CacheStraw, Buffer) == 0x0C);

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
// The shared INIClass declares the two static line classifiers. Both take
// their buffer in ECX and pop nothing (__fastcall).
// ---------------------------------------------------------------------------


#endif  // GG_MATCH_PLATFORM_INI_CLASS_NODE_METHODS_H
