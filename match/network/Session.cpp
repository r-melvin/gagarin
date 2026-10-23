// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// /Ob2 bisection matches 0x69B690; all affected old matches must remain exact.
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name | YRpp-cross-check
//   Original translation unit Session.CPP. The name is the source-file string at 0x83eeb8
//   in retail gamemd.exe v1.001, passed by the assert at 0x6977d5 inside this object's
//   code range (0x696d20-0x69ddbf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// SHA-1 block transform. __thiscall (`ret 8`; callers 0x69D939/0x69D99C/
// 0x69DA61/0x69DAC3 load ECX with the state object and push the 64-byte
// block and the accumulator at state+0x18), but `this` is never read.
// 0x160-byte frame: an 80-word schedule at [esp+0x30] and a five-word
// working copy at [esp+0x1C] taken with `rep movs`.
//
// Partial-block buffering step of the SHA-1 engine whose field offsets are
// pinned in combat/random_straw.h (Acc +0x18, Length +0x2C,
// PartialCount +0x30, Partial[64] +0x34). This TU-local view adds the
// out-of-line helpers called from 0x69D960.
// Pinned here by 0x69D8C0: `LEA EDI,[EDX+EBX+0x34]`, `[EBX+0x30]`,
// `LEA EAX,[EBX+0x18]`, `[EBX+0x2C]`, block size 0x40.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.
//
// Retail RTTI type descriptors name VectorClass<DiskID> and
// DynamicVectorClass<DiskID>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Retail RTTI type descriptors name VectorClass<MultiMission*> and
// DynamicVectorClass<MultiMission*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Retail RTTI type descriptors name VectorClass<PhoneEntryClass*> and
// DynamicVectorClass<PhoneEntryClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// 10 remaining four-byte-element resize bodies retain address-scoped
// views until their actual template classes are integrated. Recovered entries
// are bound in their native specialization implementations.
// Entry-origin spans are 0xB0 bytes. Instructions confirm Items+4, Capacity+8,
// initialization flag+C, ownership flag+D, live count+10 and Clear slot+C.
// Original source ownership and TU grouping are not established by this sweep.
//
// The source keeps the base resize as an inline call and clamps the count only
// on success. The capacity-zero branch dispatches Clear; allocation failure
// returns false. The ownership expression retains the verified short-circuit
// term so VC6 schedules SETZ and the pointer/capacity stores as retail does.
// These views remain verified under /O2 /DNDEBUG /Gy /GX.
//
// Retail RTTI names VectorClass<Wstring> and DynamicVectorClass<Wstring> (4-byte string-handle elements).
// The element copy ctor 0x7B4690 (fastcall), dtor 0x7B46F0, operator== 0x7B4780 and operator!= are out-of-line bodies bound by symbol map.

#include "../_layout/session_class.h"
#include "../platform/ccini_class_methods.h"
#include "../platform/ccfile_class.h"
#include <stdio.h>
// GLOBAL: GAMEMD 0x83EFD0
extern const char STR_0083EFD0[];
// GLOBAL: GAMEMD 0x83EFC4
extern const char STR_0083EFC4[];
// GLOBAL: GAMEMD 0x8332E8
extern const char STR_008332E8[];
// GLOBAL: GAMEMD 0x824E38
extern const char STR_00824E38[];
// GLOBAL: GAMEMD 0x83D06C
extern const char STR_0083D06C[];
// GLOBAL: GAMEMD 0x83CFA8
extern const char STR_0083CFA8[];
// GLOBAL: GAMEMD 0x83CF94
extern const char STR_0083CF94[];
// GLOBAL: GAMEMD 0x83CF84
extern const char STR_0083CF84[];
// GLOBAL: GAMEMD 0x83EFB8
extern const char STR_0083EFB8[];
// GLOBAL: GAMEMD 0x83EFA8
extern const char STR_0083EFA8[];
// GLOBAL: GAMEMD 0x83EF9C
extern const char STR_0083EF9C[];

// GLOBAL: GAMEMD 0x8870C0 (declaration; existing owner)
extern CCINIClass DAT_008870C0;
// STRING declarations by retail address; no new literal storage in this draft.
// GLOBAL: GAMEMD 0x826444
extern const char STR_00826444[]; // RA2MD.INI, raw-string binding pending
// GLOBAL: GAMEMD 0x82642C
extern const char STR_0082642C[]; // MultiPlayer
// GLOBAL: GAMEMD 0x83F13C
extern const char STR_0083F13C[]; // WOLTaunts
// GLOBAL: GAMEMD 0x83F130
extern const char STR_0083F130[]; // LANTaunts
// GLOBAL: GAMEMD 0x83F120
extern const char STR_0083F120[]; // WOLScrollText
// GLOBAL: GAMEMD 0x83F110
extern const char STR_0083F110[]; // LANScrollText

// Native byte loads at 0x699464/47F/49A/4B5 pin these four accesses.
GG_STATIC_ASSERT(sizeof(RawFileClass) == 0x24);


// LIBRARY: GAMEMD 0x7DDE13 -- CRT _wcsdup
extern "C" wchar_t* __cdecl _wcsdup(const wchar_t*);
// GLOBAL: GAMEMD 0x83ED04 -- four label pointers.
extern const char* const DAT_0083ED04[4];
#include "session_entry.h"
#include <wchar.h>
#include <string.h>
// Declaration at 0x734E60; body belongs to the string-table translation unit.
extern wchar_t* __fastcall FUN_00734E60(const char*, int, const char*, int);
// GLOBAL: GAMEMD 0x83F4B8
extern const char STR_0083F4B8[];
// GLOBAL: GAMEMD 0x83EEB8
extern const char STR_0083EEB8[];
// GLOBAL: GAMEMD 0x83F658
extern const char STR_0083F658[];
// GLOBAL: GAMEMD 0x83F3E4
extern const char STR_0083F3E4[];
// GLOBAL: GAMEMD 0x82BC30
extern const char STR_0082BC30[];

#include "../core/empty_function_family_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ShaState_0069DB30
{
    unsigned long Long[5];   // +0x00
};
GG_STATIC_ASSERT(sizeof(ShaState_0069DB30) == 0x14);

// The state forwarded at SHAPipe +0x0C (_layout/sha_pipe_layout.h
// places Acc at pipe+0x24, PartialCount at +0x3C and Partial at +0x40).
class SHAState_0069DB30
{
public:
    char IsCached;               // +0x00
    char unknown_01[3];          // +0x01
    char FinalResult[0x14];      // +0x04
    ShaState_0069DB30 Acc;               // +0x18
    int Length;                  // +0x2C
    int PartialCount;            // +0x30
    char Partial[0x40];          // +0x34

    void FUN_0069DB30(const void* source, ShaState_0069DB30& acc) const;
};
GG_STATIC_ASSERT(offsetof(SHAState_0069DB30, Acc) == 0x18);
GG_STATIC_ASSERT(offsetof(SHAState_0069DB30, PartialCount) == 0x30);
GG_STATIC_ASSERT(offsetof(SHAState_0069DB30, Partial) == 0x34);

inline unsigned long ByteSwap32(unsigned long value)
{
    return (((value << 16) | (value & 0xFF00)) << 8) | (unsigned char)(value >> 24) | ((unsigned short)((value >> 8) & 0xFF00));
}

inline unsigned long Rotl32(unsigned long value, int bits)
{
    return (value << bits) | (value >> (32 - bits));
}

inline unsigned long Function(int index, unsigned long x, unsigned long y, unsigned long z)
{
    if (index < 20) return ((y ^ z) & x) ^ z;
    if (index >= 40 && index < 60) return ((x | y) & z) | (x & y);
    return x ^ y ^ z;
}

inline unsigned long Constant(int index)
{
    if (index < 20) return 0x5A827999UL;
    if (index < 40) return 0x6ED9EBA1UL;
    return (index < 60) ? 0x8F1BBCDCUL : 0xCA62C1D6UL;
}

#include "../_rt/gg_static_assert.h"
#include <stddef.h>
#include <string.h>

struct ShaEngineView_0069D8C0
{
    bool          IsCached;        // +0x00
    unsigned long FinalResult[5];  // +0x04
    unsigned long Acc[5];          // +0x18
    long          Length;          // +0x2C
    int           PartialCount;    // +0x30
    char          Partial[64];     // +0x34

    void FUN_0069D8C0(const void*& data, long& length);
    // FUNCTION: GAMEMD 0x69DB30 -- one 64-byte block into the accumulator.
    void FUN_0069DB30(const void* block, unsigned long* acc) const;
};

GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, Acc) == 0x18);
GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, Length) == 0x2C);
GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, PartialCount) == 0x30);
GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, Partial) == 0x34);

#include "../core/trivial_tu207_methods.h"

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

struct Team_005095D0
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[4];
    void* unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Team_005095D0, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

struct Obj_005095D0
{
    int FUN_005095D0(int kind);
};


struct Obj_0050DA10
{
    char Pad_00[0x5490];
    Cell_0050DEF0 unknown_5490;
    Cell_0050DEF0 unknown_5494;
    char Pad_5498[0x54F0 - 0x5498];
    Cell_0050DEF0 unknown_54F0;
    Cell_0050DEF0 unknown_54F4;
    Cell_0050DEF0 unknown_54F8;
    int unknown_54FC;
    char Pad_5500[0x577C - 0x5500];
    int unknown_577C;

    void FUN_0050DA10();
    void FUN_0050DA50();
    int FUN_0050DA80() const;
    Cell_0050DEF0 FUN_0050DEF0() const;
    void FUN_0050DFF0();
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_5490) == 0x5490);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54FC) == 0x54FC);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_577C) == 0x577C);

struct Obj_0053ECB0
{
    unsigned char unknown_0[10];

    Obj_0053ECB0();
};

struct Triple_0053EDA0
{
    short unknown_0;
    short unknown_2;
    short unknown_4;
};
GG_STATIC_ASSERT(sizeof(Triple_0053EDA0) == 6);

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);

struct Obj_005402B0
{
    void FUN_005402B0(int value);
};

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);

struct Entry_005657A0
{
    char Pad_00[0x24];
    Cell_0050DEF0 unknown_24;
};

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);

struct Obj_005B3700
{
    int unknown_0;
    char unknown_4;
    char unknown_5;
    char unknown_6;
    char unknown_7;
    char unknown_8;
    char unknown_9;
    char Pad_0A[6];
    double unknown_10;
    double unknown_18;

    Obj_005B3700();
};
GG_STATIC_ASSERT(offsetof(Obj_005B3700, unknown_10) == 0x10);

struct Slot_005B3A00
{
    char Bytes[0x20];
};

// GLOBAL: GAMEMD 0x00A8E3A8 (32-byte records)
extern "C" Slot_005B3A00 DAT_00A8E3A8[];

struct Obj_005B3A00
{
    char Pad_00[0xAC];
    int unknown_AC;
};
GG_STATIC_ASSERT(offsetof(Obj_005B3A00, unknown_AC) == 0xAC);

struct Iface_005BF500
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3(int value) = 0;
};

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

struct Vector_005C6120
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;

    void** unknown_4;
    int Pad_08;
    int Pad_0C;
    int unknown_10;

    void FUN_005C6120();
};

struct Obj_005F9710
{
    char unknown_0;
    char unknown_1;
};

struct Quad_00645C30
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_00645C30(int a, int b, int c, int d);
};

struct Record_00656580
{
    char Bytes[0x18];
};

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);

struct Obj_00656580
{
    Record_00656580 unknown_0[1];

    Record_00656580* FUN_00656580(const Key_00656580* key);
};


struct Obj_0065AD30
{
    char Pad_00[0xE4];
    int* unknown_E4;

    int FUN_0065AD30(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD30, unknown_E4) == 0xE4);

struct Pair_0065C890
{
    int unknown_0;
    int unknown_4;

    Pair_0065C890(int a, int b);
};

struct Obj_0068BCB0
{
    char Pad_00[0x214];
    int unknown_214;
};
GG_STATIC_ASSERT(offsetof(Obj_0068BCB0, unknown_214) == 0x214);


struct Obj_0068C030
{
    char Pad_00[0x1180];
    int unknown_1180[16];

    int FUN_0068C030(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0068C030, unknown_1180) == 0x1180);


struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F30() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_53) == 0x53);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_57) == 0x57);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);

struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);

struct Obj_0069BBE0
{
    char Pad_00[0x30D8];
    char unknown_30D8;
};
GG_STATIC_ASSERT(offsetof(Obj_0069BBE0, unknown_30D8) == 0x30D8);

struct Type_006A46D0
{
    char Pad_00[0x24];
    char unknown_24[1];
};

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include "../core/vector_class_operations.h"

enum DiskID { DiskID_placeholder };


// Retail PAUGlobalPacketType RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

struct GlobalPacketType;

// VTABLE: GAMEMD 0x7F1234 -- VectorClass<GlobalPacketType*>.
template class VectorClass<GlobalPacketType*>;
typedef VectorClass<GlobalPacketType*> GgGlobalpackettypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F11D4 -- DynamicVectorClass<GlobalPacketType*>.
template class DynamicVectorClass<GlobalPacketType*>;
typedef DynamicVectorClass<GlobalPacketType*> GgGlobalpackettypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(GlobalPacketType*) == 4);

// FUNCTION: GAMEMD 0x69C4D0
// DynamicVectorClass<DiskID>::Slot5 (also slot 5 of the TypeList<DiskID> table)
// FUNCTION: GAMEMD 0x69C940
// DynamicVectorClass<DiskID>::FindItemIndex
template class DynamicVectorClass<DiskID>;

GG_STATIC_ASSERT(sizeof(DiskID) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<DiskID >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<DiskID >) == 0x18);

#include "../core/vector_class_operations.h"

class MultiMission;

template class DynamicVectorClass<MultiMission*>;

GG_STATIC_ASSERT(sizeof(MultiMission*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<MultiMission* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<MultiMission* >) == 0x18);

#include "../core/vector_class_operations.h"

class PhoneEntryClass;

template class DynamicVectorClass<PhoneEntryClass*>;

GG_STATIC_ASSERT(sizeof(PhoneEntryClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PhoneEntryClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PhoneEntryClass* >) == 0x18);

#include "../core/vector_resize_family_methods.h"

#include "../core/vector_class_operations.h"


struct Obj_00696F90;
struct Obj_00696FC0;
struct Obj_00696FF0;
struct Obj_00697020;
struct Obj_0069B720;

#pragma pack(push, 1)
struct Obj_00696F90
{
    char unknown_00[0x4B];
    int unknown_4B;   // +0x004B
    int unknown_4F;   // +0x004F
    // FUNCTION: GAMEMD 0x696F90
    int FUN_00696F90(int a1);
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F90, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F90, unknown_4F) == 0x4F);

#pragma pack(push, 1)
struct Obj_00696FC0
{
    char unknown_00[0x53];
    int unknown_53;   // +0x0053
    int unknown_57;   // +0x0057
    // FUNCTION: GAMEMD 0x696FC0
    int FUN_00696FC0(int a1);
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696FC0, unknown_53) == 0x53);
GG_STATIC_ASSERT(offsetof(Obj_00696FC0, unknown_57) == 0x57);

#pragma pack(push, 1)
struct Obj_00696FF0
{
    char unknown_00[0x5B];
    int unknown_5B;   // +0x005B
    int unknown_5F;   // +0x005F
    // FUNCTION: GAMEMD 0x696FF0
    int FUN_00696FF0(int a1);
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696FF0, unknown_5B) == 0x5B);
GG_STATIC_ASSERT(offsetof(Obj_00696FF0, unknown_5F) == 0x5F);

#pragma pack(push, 1)
struct Obj_00697020
{
    char unknown_00[0x63];
    int unknown_63;   // +0x0063
    int unknown_67;   // +0x0067
    // FUNCTION: GAMEMD 0x697020
    int FUN_00697020(int a1);
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00697020, unknown_63) == 0x63);
GG_STATIC_ASSERT(offsetof(Obj_00697020, unknown_67) == 0x67);

struct Obj_0069B720
{
    char unknown_00[0x15C];
    int unknown_15C;   // +0x015C
    int unknown_160;   // +0x0160
    // FUNCTION: GAMEMD 0x69B720
    int FUN_0069B720();
};
GG_STATIC_ASSERT(offsetof(Obj_0069B720, unknown_15C) == 0x15C);
GG_STATIC_ASSERT(offsetof(Obj_0069B720, unknown_160) == 0x160);

// FUNCTION: GAMEMD 0x696F90
// Branching.
int Obj_00696F90::FUN_00696F90(int a1)
{
    if (a1 == -2)
    {
        unknown_4B = 0;
        unknown_4F = a1;
        return a1;
    }
    unknown_4B = a1;
    unknown_4F = -1;
    return a1;
}

// FUNCTION: GAMEMD 0x696FC0
// Branching.
int Obj_00696FC0::FUN_00696FC0(int a1)
{
    if (a1 == -2)
    {
        unknown_53 = -1;
        unknown_57 = a1;
        return a1;
    }
    unknown_53 = a1;
    unknown_57 = -1;
    return a1;
}

// FUNCTION: GAMEMD 0x696FF0
// Branching.
int Obj_00696FF0::FUN_00696FF0(int a1)
{
    if (a1 == -2)
    {
        unknown_5B = -1;
        unknown_5F = a1;
        return a1;
    }
    unknown_5B = a1;
    unknown_5F = -1;
    return a1;
}

// FUNCTION: GAMEMD 0x697020
// Branching.
int Obj_00697020::FUN_00697020(int a1)
{
    if (a1 == -2)
    {
        unknown_63 = -1;
        unknown_67 = a1;
        return a1;
    }
    unknown_63 = a1;
    unknown_67 = -1;
    return a1;
}

#include "../_layout/session_class.h"
#include "../_layout/house_class.h"
// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* HouseClass_CurrentPlayer;
// GLOBAL: GAMEMD 0xA8022C
extern HouseClass** HouseClass_ArrayItems;
// GLOBAL: GAMEMD 0xA80238
extern int HouseClass_ArrayCount;
// LIBRARY: GAMEMD 0x7DD0F8
extern "C" int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer) == 0x1EC);
GG_STATIC_ASSERT(offsetof(HouseClass, Defeated) == 0x1F5);
GG_STATIC_ASSERT(offsetof(HouseClass, UIName) == 0x1602A);

#include "transport/connman_class.h"
// GLOBAL: GAMEMD 0xA8E284
extern int DAT_00A8E284[8];
// Declaration: STRING GAMEMD 0x83EF7C
extern const char STR_0083EF7C[];
// Declaration: STRING GAMEMD 0x83EF60
extern const char STR_0083EF60[];
// Declaration: STRING GAMEMD 0x83EF44
extern const char STR_0083EF44[];
// Declaration: STRING GAMEMD 0x83EF24
extern const char STR_0083EF24[];
// Declaration: STRING GAMEMD 0x83EF08
extern const char STR_0083EF08[];
// Declaration: STRING GAMEMD 0x81C5F0
extern const char STR_0081C5F0[];
// Declaration: STRING GAMEMD 0x81C5E8
extern const char STR_0081C5E8[];
GG_STATIC_ASSERT(offsetof(HouseClass, IPAddress) == 0x200);
GG_STATIC_ASSERT(offsetof(HouseClass, TournamentTeamID) == 0x204);
GG_STATIC_ASSERT(offsetof(HouseClass, LostConnection) == 0x208);

// FUNCTION: GAMEMD 0x697050
SessionProfile_00697F10::SessionProfile_00697F10()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 1;
    unknown_0C = 10000;
    unknown_10 = 10;
    unknown_14 = true;
    unknown_15 = true;
    unknown_16 = true;
    unknown_17 = true;
    unknown_18 = true;
    for (int index = 0; index < 8; ++index) {
        unknown_1C[index][0] = 0;
        unknown_1C[index][1] = 0;
        unknown_1C[index][2] = 0;
    }
}

// FUNCTION: GAMEMD 0x6977C0
void SessionClass::FUN_006977C0()
{
    for (int index = 0; index < 4; ++index) {
        const unsigned short* text = _wcsdup(
            FUN_00734E60(DAT_0083ED04[index], 0, STR_0083EEB8, 0x251));
        // Native ignores append failure and does not free a failed append.
        unknown_292C.AddItem(text);
    }
}

// FUNCTION: GAMEMD 0x697B70
int SessionClass::FUN_00697B70()
{
    NetworkNumberType network;
    NodeAddressType node;
    FUN_004068E0(STR_0083EF7C);
    if (Session_00A8B238.GameMode != 3 && Session_00A8B238.GameMode != 4)
        return 0;
    for (int i = 0; i < unknown_283C.Count; ++i) {
        FUN_004068E0(STR_0083EF60, i, unknown_283C.Items[i], unknown_283C.Items[i]->Id);
        // Native name pointer is player+0, UTF16 consumed by _wcsicmp.
        if (_wcsicmp(reinterpret_cast<const wchar_t*>(unknown_283C.Items[i]->Name),
            HouseClass_ArrayItems[unknown_283C.Items[i]->Id]->UIName) != 0)
            return 0;
        if (_wcsicmp(reinterpret_cast<const wchar_t*>(unknown_283C.Items[i]->Name), unknown_3020) == 0) {
            unknown_3074 = unknown_283C.Items[i]->Id;
            Players_00A8DA78[i]->Address.FUN_0053EDA0(network, node);
            Address_00A8DBA4.FUN_0053ED20(network, node, 0);
            Manager_00A8E9C0.FUN_00543050(&Address_00A8DBA4);
        }
        HouseClass_ArrayItems[unknown_283C.Items[i]->Id]->TournamentTeamID = unknown_283C.Items[i]->unknown_7B;
        Players_00A8DA78[i]->Address.FUN_0053EDA0(network, node);
        int address = 0;
        for (int j = 0; j < 4; ++j)
            address = (address << 8) | node.Node[j];
        FUN_004068E0(STR_0083EF44, unknown_283C.Items[i]->Id, address, unknown_283C.Items[i]->unknown_7B);
        HouseClass_ArrayItems[unknown_283C.Items[i]->Id]->IPAddress = address;
        HouseClass_ArrayItems[unknown_283C.Items[i]->Id]->LostConnection = 0;
        if (i > 0) {
            Manager_00A8E9C0.FUN_00540DC0(unknown_283C.Items[i]->Id,
                reinterpret_cast<wchar_t*>(unknown_283C.Items[i]->Name), &unknown_283C.Items[i]->Address);
            unknown_283C.Items[i]->unknown_73 = -1;
        }
    }
    for (int timerIndex = 0; timerIndex < 8; ++timerIndex)
        DAT_00A8E284[timerIndex] = ConnTimer.GetValue();
    if (GameMode == 4 && unknown_3090) {
        NetworkNumberType zeroNetwork = { 0 };
        NodeAddressType zeroNode = { 0, 0, 0, 0, 0, 0 };
        Address_00A8DBB0.FUN_0053ED20(zeroNetwork, zeroNode, 0);
        unknown_2968 = 1;
        unknown_308C = 0;
        unknown_309C = 20;
        unknown_3094 = -1;
        Manager_00A8E9C0.FUN_00540E70();
        IdMap_00B052D0.FUN_00663B40();
        if (Session_00A8B238.FUN_00697E70(0)) {
            if (IdMap_00B052D0.FUN_00663DB0(0)) {
                if (!IdMap_00B052D0.FUN_006639D0())
                    Flag_00A8DBA0 = false;
            } else {
                Flag_00A8DBA0 = false;
            }
        }
    } else {
        Flag_00A8DBA0 = false;
    }
    FUN_004068E0(STR_0083EF24, Flag_00A8DBA0 ? STR_0081C5F0 : STR_0081C5E8);
    FUN_004068E0(STR_0083EF08);
    return 1;
}

// FUNCTION: GAMEMD 0x697E70
bool SessionClass::FUN_00697E70(void* house)
{
    // Existing public declaration accepts opaque House pointers from legacy
    // callers. Native697E99/697EB1/697EE1/697EEB prove this layout boundary.
    if (house == 0)
        house = HouseClass_CurrentPlayer;
    HouseClass* selected = static_cast<HouseClass*>(house);
    if (Session_00A8B238.GameMode == 4 && selected != 0) {
        if (unknown_3074 != -1)
            return selected->ArrayIndex == unknown_3074;
        if (_wcsicmp(selected->UIName, unknown_3020) == 0)
            return true;
    }
    for (int i = 0; i < HouseClass_ArrayCount; ++i) {
        HouseClass* entry = HouseClass_ArrayItems[i];
        if (entry->IsHumanPlayer && !entry->Defeated)
            return selected == entry ? true : false;
    }
    return false;
}

// GLOBAL: GAMEMD 0x83ED14
extern signed char DAT_0083ED14[9];
GG_STATIC_ASSERT(sizeof(DAT_0083ED14) == 9);

#include "../core/rules_class.h"
#include "../platform/ccini_class_methods.h"
#include "multiplayer_game_mode.h"
// Declaration: GAMEMD 0x5D5E10 -- no incoming arguments, pointerEAX, RET.
MultiplayerGameMode* FUN_005D5E10();
// LIBRARY: GAMEMD 0x7C8EF4
extern "C" int __cdecl sprintf(char*, const char*, ...);
// Declaration: STRING GAMEMD 0x83EFD0
extern const char STR_0083EFD0[];
// Declaration: STRING GAMEMD 0x83EFC4
extern const char STR_0083EFC4[];
// Declaration: STRING GAMEMD 0x8332E8
extern const char STR_008332E8[];
// Declaration: STRING GAMEMD 0x824E38
extern const char STR_00824E38[];
// Declaration: STRING GAMEMD 0x83D06C
extern const char STR_0083D06C[];
// Declaration: STRING GAMEMD 0x83CFA8
extern const char STR_0083CFA8[];
// Declaration: STRING GAMEMD 0x83CF94
extern const char STR_0083CF94[];
// Declaration: STRING GAMEMD 0x83CF84
extern const char STR_0083CF84[];
// Declaration: STRING GAMEMD 0x83EFB8
extern const char STR_0083EFB8[];
// Declaration: STRING GAMEMD 0x83EFA8
extern const char STR_0083EFA8[];
// Declaration: STRING GAMEMD 0x83EF9C
extern const char STR_0083EF9C[];

// FUNCTION: GAMEMD 0x697F10
void SessionProfile_00697F10::FUN_00697F10(CCINIClass* ini, const char* section, int fallback, int firstFallback)
{
    ini->Reset();
    unknown_00 = ini->FUN_005276D0(section, STR_0083EFD0, FUN_005D5E10()->unknown_28);
    unknown_04 = ini->FUN_005276D0(section, STR_0083EFC4, 0);
    unknown_08 = ini->FUN_005276D0(section, STR_008332E8, RulesInstance->unknown_14A0);
    unknown_0C = ini->FUN_005276D0(section, STR_00824E38, RulesInstance->unknown_1484);
    unknown_10 = ini->FUN_005276D0(section, STR_0083D06C, RulesInstance->unknown_1494);
    unknown_14 = ini->FUN_005295F0(section, STR_0083CFA8, RulesInstance->unknown_14B6);
    unknown_15 = ini->FUN_005295F0(section, STR_0083CF94, RulesInstance->unknown_14B9);
    unknown_16 = ini->FUN_005295F0(section, STR_0083CF84, RulesInstance->unknown_14BA);
    unknown_17 = ini->FUN_005295F0(section, STR_0083EFB8, RulesInstance->unknown_14B8);
    unknown_18 = ini->FUN_005295F0(section, STR_0083EFA8, RulesInstance->unknown_14B1);
    for (int slot = 1; slot < 8; ++slot) {
        char key[16];
        sprintf(key, STR_0083EF9C, slot);
        int first = slot == 1 ? firstFallback : fallback;
        int second = -2;
        int third = -2;
        ini->FUN_00477440(section, key, &first, &second, &third);
        unknown_1C[slot][0] = first;
        unknown_1C[slot][1] = second;
        unknown_1C[slot][2] = third;
    }
}

// FUNCTION: GAMEMD 0x698F90
void SessionProfile_00697F10::FUN_00698F90(CCINIClass* ini, const char* section)
{
    ini->WriteInteger(section, STR_0083EFD0, unknown_00, 0);
    ini->WriteInteger(section, STR_0083EFC4, unknown_04, 0);
    ini->WriteInteger(section, STR_008332E8, unknown_08, 0);
    ini->WriteInteger(section, STR_00824E38, unknown_0C, 0);
    ini->WriteInteger(section, STR_0083D06C, unknown_10, 0);
    ini->WriteBool(section, STR_0083CFA8, unknown_14);
    ini->WriteBool(section, STR_0083CF94, unknown_15);
    ini->WriteBool(section, STR_0083CF84, unknown_16);
    ini->WriteBool(section, STR_0083EFB8, unknown_17);
    ini->WriteBool(section, STR_0083EFA8, unknown_18);
    char key[16];
    for (int slot = 1; slot < 8; ++slot) {
        sprintf(key, STR_0083EF9C, slot);
        ini->FUN_00477510(section, key, unknown_1C[slot][0],
                         unknown_1C[slot][1], unknown_1C[slot][2]);
    }
}

// FUNCTION: GAMEMD 0x699450
void SessionClass::FUN_00699450()
{
    RawFileClass file(STR_00826444);
    DAT_008870C0.WriteBool(STR_0082642C, STR_0083F13C, unknown_1ED9);
    DAT_008870C0.WriteBool(STR_0082642C, STR_0083F130, unknown_1ED8);
    DAT_008870C0.WriteBool(STR_0082642C, STR_0083F120, unknown_1FC1);
    DAT_008870C0.WriteBool(STR_0082642C, STR_0083F110, unknown_1FC0);
    DAT_008870C0.WriteCCFile(&file, false);
}

// FUNCTION: GAMEMD 0x69A310
unsigned int __stdcall FUN_0069A310(unsigned int index)
{
    if (index == 0xFFFFFFFEU)
        index = 8;
    if (index < 9)
        return DAT_0083ED14[index];
    return index;
}

// FUNCTION: GAMEMD 0x69B720
// Branching.
int Obj_0069B720::FUN_0069B720()
{
    if (unknown_160 != -2)
    {
        return unknown_15C;
    }
    return -2;
}

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// 0x69C9F3/0x69CA21 write array cookies for four-byte elements.
// 0x69CA81 calls the nontrivial assignment at 0x7B4940.
struct Wstring {
    char* unknown_00;
    Wstring();
    Wstring(const Wstring& o);
    ~Wstring();
    bool operator==(const Wstring& o) const;
    bool operator!=(const Wstring& o) const;
    // Declaration: GAMEMD 0x7B4940
    Wstring& operator=(const Wstring& o);
};
GG_STATIC_ASSERT(sizeof(Wstring) == 4);
GG_STATIC_ASSERT(offsetof(Wstring, unknown_00) == 0);

template class DynamicVectorClass<Wstring>;

#include "session_class_resume_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F1190
extern const double DAT_007F1190;
// GLOBAL: GAMEMD 0xB057E8
extern double DAT_00B057E8;
// GLOBAL: GAMEMD 0xB07760
extern double DAT_00B07760;
// GLOBAL: GAMEMD 0xB07768
extern int DAT_00B07768;
// GLOBAL: GAMEMD 0xB0776C
extern int DAT_00B0776C;
// GLOBAL: GAMEMD 0xB07770
extern int DAT_00B07770;
// GLOBAL: GAMEMD 0xB07778
extern double DAT_00B07778;

// FUNCTION: GAMEMD 0x696D50
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00696D50()
{
    DAT_00B07778 = DAT_00B057E8 / DAT_007F1190;
}

// FUNCTION: GAMEMD 0x696D70
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00696D70()
{
    DAT_00B07760 = DAT_007E1718 / DAT_00B07778;
}

// FUNCTION: GAMEMD 0x696EF0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00696EF0()
{
    DAT_00B07770 = 0;
    DAT_00B07768 = 0x80;
    DAT_00B0776C = 0x80;
}

// FUNCTION: GAMEMD 0x00696F10
int Obj_00696F10::FUN_00696F10() const
{
    if (unknown_4F == -2) {
        return -2;
    }
    return unknown_4B;
}

// FUNCTION: GAMEMD 0x00696F20
int Obj_00696F10::FUN_00696F20() const
{
    if (unknown_57 == -2) {
        return -2;
    }
    return unknown_53;
}

// FUNCTION: GAMEMD 0x696F30
int Obj_00696F10::FUN_00696F30() const
{
    if (unknown_57 == -2 && unknown_53 == -1)
        return -2;
    return unknown_53;
}

// FUNCTION: GAMEMD 0x00696F50
int Obj_00696F10::FUN_00696F50() const
{
    if (unknown_5F == -2 && unknown_5B == -1) {
        return -2;
    }
    return unknown_5B;
}

// FUNCTION: GAMEMD 0x00696F70
int Obj_00696F10::FUN_00696F70() const
{
    if (unknown_67 == -2 && unknown_63 == -1) {
        return -2;
    }
    return unknown_63;
}

// Declaration: GAMEMD 0x48DD50 -- no arguments, EAX result.
unsigned long __fastcall FUN_0048DD50();
// Declaration: GAMEMD 0x64DE80 -- accumulator in ECX, value in EDX.
void __fastcall FUN_0064DE80(unsigned long* accumulator, unsigned long value);
// Declaration: GAMEMD 0x4068E0 -- variadic cdecl logging entry.
extern "C" int __cdecl FUN_004068E0(const char*, ...);
// LIBRARY: GAMEMD 0x007CBC11
// getenv

// REA Evidence: ev_a1006eb97fea3a6f2a5255ae22ee61b5f974f50509498da97e6176ca3dc2c67a
// FUNCTION: GAMEMD 0x697AD0
void SessionClass::FUN_00697AD0()
{
    FUN_00699980();
    unsigned long value = timeGetTime();
    FUN_0064DE80(&value, FUN_0048DD50());
    const char* path = getenv(
        // STRING: GAMEMD 0x0083EF00
        "PATH");
    if (path) {
        for (unsigned int index = 0; index < strlen(path); ++index)
            FUN_0064DE80(&value, path[index]);
    }
    unknown_144 = value;
    FUN_004068E0(
        // STRING: GAMEMD 0x0083EED4
        "Session one time init. UniqueID is %08x\n", value);
}

// FUNCTION: GAMEMD 0x697B60
// Empty function.
void __cdecl FUN_00697B60()
{
}

// FUNCTION: GAMEMD 0x0069A300
void FUN_0069A300()
{
}

// FUNCTION: GAMEMD 0x69ACC0
// Member getter (dword).
int Obj_0069ACC0::FUN_0069ACC0() const
{
    return unknown_18C->unknown_00;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69ADE0
// Stores its argument in a member; pops its stack arguments.
void Obj_0069ADE0::FUN_0069ADE0(unsigned char a1)
{
    unknown_17C = a1;
}

// REA Evidence: ev_11ce794979f0e2980076f87c1eeffe96d530e6c29faed93d9a77c5cc87f93a03
// FUNCTION: GAMEMD 0x69ACD0
void Entry_00A8B8C8::FUN_0069ACD0(const wchar_t* source)
{
    if (source) {
        wcsncpy(unknown_000, source, 0x2C);
        unknown_000[0x2B] = 0;
    } else {
        wcscpy(unknown_000, FUN_00734E60(STR_0083F4B8, 0, STR_0083EEB8, 0xB1D));
    }
}

// FUNCTION: GAMEMD 0x69AD20
void Entry_00A8B8C8::FUN_0069AD20(const char* source)
{
    if (source) {
        strncpy(unknown_058, source, 0x104);
        unknown_058[0x103] = 0;
    } else {
        strcpy(unknown_058, STR_0083F658);
    }
}

// FUNCTION: GAMEMD 0x69AD80
void Entry_00A8B8C8::FUN_0069AD80(const char* source)
{
    if (source) {
        strncpy(unknown_15C, source, 0x20);
        unknown_15C[0x1F] = 0;
    } else {
        strcpy(unknown_15C, STR_0083F3E4);
    }
}

// FUNCTION: GAMEMD 0x69ADF0
bool Entry_00A8B8C8::FUN_0069ADF0()
{
    return _stricmp(unknown_058, STR_0082BC30) == 0;
}

// FUNCTION: GAMEMD 0x69AE70
bool SessionClass::FUN_0069AE70()
{
    return _stricmp(&unknown_300[0x3A8],
        // STRING: GAMEMD 0x0082BC30
        "RandMap.Sed") == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0069B540
void FUN_0069B540(Obj_0069B540* self)
{
    self->unknown_24 = 0;
    for (int i = 0; i < 8; i++) {
        self->unknown_4C[i] = -1;
        self->unknown_6C[i] = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69B700
// Branching.
int Obj_0069B700::FUN_0069B700()
{
    if (unknown_178 != -2)
    {
        return unknown_174;
    }
    return -2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69B740
// Branching.
int Obj_0069B740::FUN_0069B740()
{
    if (unknown_168 != -2)
    {
        return unknown_164;
    }
    return -2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69B8B0
// Empty function that pops its stack arguments.
void __stdcall FUN_0069B8B0(int a1, int a2)
{
}


#include "multiplayer_game_mode.h"
#include "transport/conn_types.h"
// GLOBAL: GAMEMD 0x83F710 -- external string address
extern const char STR_0083F710[];
// GLOBAL: GAMEMD 0x83F6E8 -- external string address
extern const char STR_0083F6E8[];
// GLOBAL: GAMEMD 0x83F6C8 -- external string address
extern const char STR_0083F6C8[];

// FUNCTION: GAMEMD 0x69B600
bool SessionClass::FUN_0069B600(int value)
{
    if (value == -2)
        return false;
    for (int i = 0; i < unknown_283C.Count; ++i) {
        NetPlayerClass* player = unknown_283C.Items[i];
        int current = player->unknown_57 == -2 && player->unknown_53 == -1
            ? -2 : player->unknown_53;
        if (current == value)
            return true;
    }
    for (int j = 0; j < 8; ++j) {
        if (unknown_84[j] == value)
            return true;
    }
    return false;
}

// REA Evidence: ev_767d44addc745194b26db1d3bd971e00440ac71dcacab4ecb0cfc03e7770823f
// FUNCTION: GAMEMD 0x69B670
int SessionClass::FUN_0069B670()
{
    return DAT_00A8B230->unknown_0218.RandomRanged(0, 9);
}

// FUNCTION: GAMEMD 0x69B690
// Every RET preserves the generated candidate in EAX. Original source
// return spelling is unknown; expose the observed register result.
int SessionClass::FUN_0069B690()
{
    int value;
    do {
        value = DAT_00A8B230->unknown_0218.RandomRanged(0, 7);
    } while (FUN_0069B600(value));
    return value;
}

// FUNCTION: GAMEMD 0x69B760
void SessionClass::FUN_0069B760(int value, bool randomize)
{
    if (value == -2) {
        if (randomize) {
            unknown_184 = DAT_00A8B230->unknown_0218.RandomRanged(0, 9);
            unknown_188 = -2;
        } else {
            unknown_184 = 0;
            unknown_188 = -2;
        }
    } else {
        unknown_184 = value;
        unknown_188 = -1;
    }
    unknown_174 = unknown_184;
    unknown_178 = unknown_188;
}

// FUNCTION: GAMEMD 0x69B7E0
void SessionClass::FUN_0069B7E0(int value, bool randomize)
{
    if (value == -2) {
        if (randomize) {
            unknown_17C = FUN_0069B690();
        } else {
            unknown_17C = 0;
        }
        unknown_180 = -2;
    } else {
        unknown_17C = value;
        unknown_180 = -1;
    }
    unknown_15C = unknown_17C;
    unknown_160 = unknown_180;
}

// FUNCTION: GAMEMD 0x69B8C0
void SessionClass::FUN_0069B8C0()
{
    FUN_004068E0(STR_0083F710);
    int count = PlayerCount_00A8DA84;
    for (int i = 0; i < count; ++i) {
        NetPlayerClass* player = Players_00A8DA78[i];
        if (player->unknown_4F == -3 || player->unknown_4B == -3) {
            player->unknown_4B = -3;
            player->unknown_4F = -1;
            player->unknown_53 = 8;
            player->unknown_57 = -1;
        } else {
            if (player->unknown_4F == -2) {
                player->unknown_4F = -1;
                if (unknown_04)
                    player->unknown_4B = unknown_04->vf_27();
                else
                    player->unknown_4B = DAT_00A8B230->unknown_0218.RandomRanged(0, 9);
            }
            if (player->unknown_57 == -2) {
                player->unknown_57 = -1;
                player->unknown_53 = -1;
                int value;
                do {
                    value = DAT_00A8B230->unknown_0218.RandomRanged(0, 7);
                } while (Session_00A8B238.FUN_0069B600(value));
                player->unknown_53 = value;
            }
        }
        if (i == 0)
            Session_00A8B238.unknown_15C = player->unknown_53;
        FUN_004068E0(STR_0083F6E8, i, player->FUN_007350C0(),
            player->unknown_4F == -2 ? -2 : player->unknown_4B,
            player->unknown_57 == -2 ? -2 : player->unknown_53);
    }
    for (int slot = 0; slot < 8; ++slot) {
        if (Session_00A8B238.unknown_64[slot] == -2) {
            if (unknown_04)
                Session_00A8B238.unknown_64[slot] = unknown_04->vf_28();
            else
                Session_00A8B238.unknown_64[slot] =
                    DAT_00A8B230->unknown_0218.RandomRanged(0, 9);
        }
        if (Session_00A8B238.unknown_84[slot] == -2) {
            int value;
            bool used;
            do {
                value = DAT_00A8B230->unknown_0218.RandomRanged(0, 7);
                used = false;
                if (value != -2) {
                    for (int i = 0; i < PlayerCount_00A8DA84; ++i) {
                        NetPlayerClass* player = Players_00A8DA78[i];
                        int current = player->unknown_57 == -2 &&
                            player->unknown_53 == -1 ? -2 : player->unknown_53;
                        if (current == value) {
                            used = true;
                            break;
                        }
                    }
                    if (!used) {
                        for (int i = 0; i < 8; ++i) {
                            if (Session_00A8B238.unknown_84[i] == value) {
                                used = true;
                                break;
                            }
                        }
                    }
                }
            } while (used);
            Session_00A8B238.unknown_84[slot] = value;
        }
        FUN_004068E0(STR_0083F6C8, slot, Session_00A8B238.unknown_64[slot],
            Session_00A8B238.unknown_84[slot]);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69BAB0
//
// Resume an in-game frame after a pause: mark the frame active, restore the
// saved game speed (campaign games are forced back to speed 2), re-arm the
// frame deadline when the provider flag is clear, make sure the mouse is
// captured, and finally set 0x4000 on the shared flags object — a __fastcall
// in tail position, which is why retail ends in a JMP.
void SessionClass::Resume()
{
    if (this->InGameFrameActive == 0 && DAT_00A8E9A0 != 0) {
        this->InGameFrameActive = 1;

        if (DAT_0083ED20 == -1) {
            DAT_0083ED20 = DAT_00A8EB60;
        }
        if (this->GameMode == 0) {
            DAT_00A8EB60 = 2;
        }
        if (DAT_00A8B230->unknown_35A2 == 0) {
            FUN_00684240();
            DAT_00B07784 = CurrentFrame + 3;
        }
        if (!(DAT_00887640->*DAT_00887640->Vtbl->At_1C)()) {
            (DAT_00887640->*DAT_00887640->Vtbl->At_18)();
        }
        DAT_0087E758->FUN_00407150(0x4000);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0069BBE0
char FUN_0069BBE0(Obj_0069BBE0* self)
{
    return self->unknown_30D8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69BBF0
void SessionClass::FUN_0069BBF0(int index)
{
    for (int i = index; i < 7; ++i)
        unknown_307A[i] = unknown_307A[i + 1];
}

#include "transport/conn_types.h"

// FUNCTION: GAMEMD 0x69BC20
unsigned short SessionClass::FUN_0069BC20(int id)
{
    for (int index = 0; index < PlayerCount_00A8DA84; ++index) {
        if (Players_00A8DA78[index]->Id == id)
            return unknown_307A[index];
    }
    return 0;
}

// GLOBAL: GAMEMD 0xA8DA90
extern NetPlayerClass* SlotPlayers_00A8DA90[8];
GG_STATIC_ASSERT(sizeof(SlotPlayers_00A8DA90) == 0x20);
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69C600
// DynamicVectorClass<GlobalPacketType*>::Clear

// FUNCTION: GAMEMD 0x69C630
// DynamicVectorClass<GlobalPacketType*>::Slot5

// FUNCTION: GAMEMD 0x69C650
// VectorClass<GlobalPacketType*>::Slot6

// FUNCTION: GAMEMD 0x69CFA0
// VectorClass<GlobalPacketType*>::operator==

// FUNCTION: GAMEMD 0x69CFE0
// VectorClass<GlobalPacketType*>::SetCapacity

// FUNCTION: GAMEMD 0x69D090
// VectorClass<GlobalPacketType*>::Clear

// FUNCTION: GAMEMD 0x69D0C0
// VectorClass<GlobalPacketType*>::FindItemIndex

// FUNCTION: GAMEMD 0x69D100
// VectorClass<GlobalPacketType*>::Slot5

// FUNCTION: GAMEMD 0x69D120
// DynamicVectorClass<GlobalPacketType*>::SetCapacity

// FUNCTION: GAMEMD 0x69D1D0
// DynamicVectorClass<GlobalPacketType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x69D630
// VectorClass<GlobalPacketType*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x69D680
// DynamicVectorClass<GlobalPacketType*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x7350C0 (decl; reloc)
extern const char* NarrowName_007350C0(const unsigned short* name);

// FUNCTION: GAMEMD 0x69BC60
int SessionClass::FUN_0069BC60(int index)
{
    for (int slot = 0; slot < 8; ++slot) {
        NetPlayerClass* selected = SlotPlayers_00A8DA90[slot];
        const char* playerName = NarrowName_007350C0(Players_00A8DA78[index]->Name);
        const char* slotName = NarrowName_007350C0(selected->Name);
        if (_stricmp(playerName, slotName) == 0)
            return slot;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x69BCC0
// RET4 and a single stack argument; ECX is unused on entry. No incoming
// references survive in current analysis, so retain an address-scoped ABI model.
int __stdcall FUN_0069BCC0(const char* name)
{
    for (int index = 0; index < 8; ++index) {
        if (_stricmp(name, NarrowName_007350C0(SlotPlayers_00A8DA90[index]->Name)) == 0)
            return index;
    }
    return 0;
}

// REA bytes: ev_6c3466240f0af9379dc0fd78a02b209a8d15120ced2c3bd76c6742cfb62f3565.
// Entry disassembly closes both RET4 paths at 0x69BD59; incoming ECX is unused.
// FUNCTION: GAMEMD 0x69BD00
int __stdcall FUN_0069BD00(int slot)
{
    for (int index = 0; index < PlayerCount_00A8DA84; ++index) {
        NetPlayerClass* selected = SlotPlayers_00A8DA90[slot];
        const char* playerName = NarrowName_007350C0(Players_00A8DA78[index]->Name);
        const char* slotName = NarrowName_007350C0(selected->Name);
        if (_stricmp(playerName, slotName) == 0)
            return index;
    }
    return 0;
}

#include "../_layout/node_name_type.h"
// Declaration: GAMEMD 0x7350C0 -- existing wide-name conversion, ECX input.
char* Narrow_007350C0(const wchar_t* text);
#include "wonline.h"
#include "transport/udp_interface_class.h"
GG_STATIC_ASSERT(offsetof(NodeNameType, Name) == 0);
GG_STATIC_ASSERT(offsetof(NodeNameType, Address) == 0x28);
GG_STATIC_ASSERT(offsetof(NodeNameType, unknown_53) == 0x53);
// Declaration: STRING GAMEMD 0x83F840
extern const char STR_0083F840[];
// Declaration: STRING GAMEMD 0x83F81C
extern const char STR_0083F81C[];
// Declaration: STRING GAMEMD 0x83F7F0
extern const char STR_0083F7F0[];
// Declaration: STRING GAMEMD 0x83F7A0
extern const char STR_0083F7A0[];
// Declaration: STRING GAMEMD 0x83F784
extern const char STR_0083F784[];
// Declaration: STRING GAMEMD 0x83F760
extern const char STR_0083F760[];
// Declaration: STRING GAMEMD 0x83F734
extern const char STR_0083F734[];

// FUNCTION: GAMEMD 0x69BD60
void SessionClass::FUN_0069BD60()
{
    DynamicVectorClass<NodeNameType*> ordered;
    unsigned int adjustment = 1;
    FUN_004068E0(STR_0083F840);
    if (unknown_283C.Count < 2)
        return;
    int nameCount = 0;
    memset(unknown_2E28, 0, sizeof(unknown_2E28));
    unknown_3018 = 1;
    for (int i = 0; i < unknown_283C.Count; ++i) {
        int slot = FUN_0069BC60(i);
        if (slot >= 0 && slot < 8) {
            unknown_283C.Items[i]->Address.FUN_0053F200((unsigned short)unknown_2FF8[slot]);
            const char* name = unknown_283C.Items[i]->FUN_007350C0();
            const char* address = unknown_283C.Items[i]->Address.FUN_0053F0E0(0);
            FUN_004068E0(STR_0083F81C, name, address);
        }
    }
    bool used[8] = { false, false, false, false, false, false, false, false };
    for (int pass = 0; pass < unknown_283C.Count; ++pass) {
        int smallest = 0x7FFFFFFF;
        int smallestValue = 0x7FFFFFFF;
        for (int candidate = 0; candidate < unknown_283C.Count; ++candidate) {
            if (!used[candidate] && unknown_283C.Items[candidate]->unknown_53 < smallestValue) {
                smallest = candidate;
                smallestValue = unknown_283C.Items[candidate]->unknown_53;
            }
        }
        if (smallest == 0x7FFFFFFF)
            break;
        used[smallest] = true;
        // Retail local vector RTTI is NodeNameType*. The existing Session
        // pointer declaration uses the older NetPlayerClass record view.
        ordered.AddItem(reinterpret_cast<NodeNameType*>(unknown_283C.Items[smallest]));
        if (ordered.Count == unknown_283C.Count)
            break;
    }
    memset(used, 0, sizeof(used));
    for (int first = 0; first < ordered.Count; ++first) {
        if (!used[first]) {
            IPXAddressClass address = ordered.Items[first]->Address;
            for (int second = 0; second < ordered.Count; ++second) {
                if (second != first && !used[second] && address.Equals_EF30(ordered.Items[second]->Address)) {
                    const char* firstName = Narrow_007350C0(ordered.Items[first]->Name);
                    int firstSlot = FUN_0069BCC0(firstName);
                    const char* secondName = Narrow_007350C0(ordered.Items[second]->Name);
                    int secondSlot = FUN_0069BCC0(secondName);
                    if (unknown_2FF8[firstSlot] == unknown_2FF8[secondSlot]) {
                        unsigned short offset = (unsigned short)adjustment++;
                        ordered.Items[second]->Address.FUN_0053F200((unsigned short)(unknown_2FF8[firstSlot] + offset));
                        used[second] = true;
                        FUN_004068E0(STR_0083F7F0, (unsigned int)offset, Narrow_007350C0(ordered.Items[second]->Name));
                    } else {
                        FUN_004068E0(STR_0083F7A0);
                    }
                    const char* name = Narrow_007350C0(ordered.Items[first]->Name);
                    const char* localName = DAT_00B73E40.FUN_007B5400();
                    if (_stricmp(name, localName) == 0)
                        strcpy(unknown_2E28[nameCount++], Narrow_007350C0(ordered.Items[second]->Name));
                    name = Narrow_007350C0(ordered.Items[second]->Name);
                    localName = DAT_00B73E40.FUN_007B5400();
                    if (_stricmp(name, localName) == 0)
                        strcpy(unknown_2E28[nameCount++], Narrow_007350C0(ordered.Items[first]->Name));
                }
            }
        }
    }
    if (unknown_301C != 0) {
        FUN_004068E0(STR_0083F784, unknown_301C);
        Players_00A8DA78[0]->Address.FUN_0053F200((unsigned short)unknown_301C);
        int slot = FUN_0069BC60(0);
        unknown_2858[slot]->Address.FUN_0053F200((unsigned short)unknown_301C);
    }
    for (int player = 0; player < unknown_283C.Count; ++player) {
        unknown_307A[player] = unknown_283C.Items[player]->Address.Port;
        if (unknown_307A[player] == 0)
            unknown_307A[player] = 1234;
    }
    IPXAddressClass firstAddress = unknown_283C.Items[0]->Address;
    NodeAddressType firstNode;
    firstAddress.FUN_0053EDC0(&firstNode);
    for (int other = 1; other < unknown_283C.Count; ++other) {
        if (firstAddress.Equals_EF30(unknown_283C.Items[other]->Address)) {
            FUN_004068E0(STR_0083F760, unknown_283C.Items[other]->FUN_007350C0());
            for (int candidate = 0; candidate < 8; ++candidate) {
                const char* otherName = unknown_283C.Items[other]->FUN_007350C0();
                const char* candidateName = unknown_2858[candidate]->FUN_007350C0();
                if (_stricmp(otherName, candidateName) == 0) {
                    NodeAddressType node;
                    unknown_2994[candidate].FUN_0053EDC0(&node);
                    unknown_283C.Items[other]->Address.FUN_0053ED20(
                        0, &node, unknown_283C.Items[other]->Address.Port);
                    const char* name = unknown_283C.Items[other]->FUN_007350C0();
                    const char* address = unknown_283C.Items[other]->Address.FUN_0053F0E0(0);
                    FUN_004068E0(STR_0083F734, name, address);
                }
            }
        }
    }
    if (Interface_00887628) {
        // UDP creation52F456 -> ctor7B2DB0 seats table7F7A6C at7B2E2D.
        // Native69C444/69C457 use UDP-only slots28/23; base slot7 follows.
        static_cast<UDPInterfaceClass*>(Interface_00887628)->CloseAllSpareSockets();
        static_cast<UDPInterfaceClass*>(Interface_00887628)->OpenPrimarySocket(unknown_307A[0]);
        Interface_00887628->StartListening();
    }
}

// TEMPLATE: GAMEMD 0x69C4F0
// VectorClass<DiskID>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x69C710
// VectorClass<DiskID>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x69C750
// VectorClass<DiskID>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69C830
// VectorClass<DiskID>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x69C870
// VectorClass<DiskID>::Slot5 (slot 5)
template class VectorClass<DiskID>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0069D4B0
// VectorClass<Wstring>::scalar deleting destructor
// FUNCTION: GAMEMD 0x0069C970
// VectorClass<Wstring>::operator==
// TEMPLATE: GAMEMD 0x69C9C0
// VectorClass<Wstring>::SetCapacity (slot 2).
// FUNCTION: GAMEMD 0x0069CB00
// VectorClass<Wstring>::Clear
// FUNCTION: GAMEMD 0x0069CB50
// VectorClass<Wstring>::FindItemIndex
// FUNCTION: GAMEMD 0x0069CBA0
// VectorClass<Wstring>::Slot5
// FUNCTION: GAMEMD 0x0069C580
// VectorClass<Wstring>::Slot6
// FUNCTION: GAMEMD 0x0069D520
// DynamicVectorClass<Wstring>::scalar deleting destructor
// FUNCTION: GAMEMD 0x0069C500
// DynamicVectorClass<Wstring>::Clear
// FUNCTION: GAMEMD 0x0069CD00
// DynamicVectorClass<Wstring>::FindItemIndex
// FUNCTION: GAMEMD 0x0069C560
// DynamicVectorClass<Wstring>::Slot5
// TEMPLATE: GAMEMD 0x69CBC0
// DynamicVectorClass<Wstring>::SetCapacity (slot 2).
// TEMPLATE: GAMEMD 0x69D7C0
// VectorClass<Wstring>::VectorClass(int, Wstring*)
template class VectorClass<Wstring>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x69C5D0
// DynamicVectorClass<MultiMission*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69C5F0
// VectorClass<MultiMission*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x69CD40
// VectorClass<MultiMission*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x69CD80
// VectorClass<MultiMission*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69CE60
// VectorClass<MultiMission*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x69CEA0
// VectorClass<MultiMission*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69CEC0
// DynamicVectorClass<MultiMission*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69CF70
// DynamicVectorClass<MultiMission*>::FindItemIndex (slot 4)
template class VectorClass<MultiMission*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x69C690
// DynamicVectorClass<PhoneEntryClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69C6B0
// VectorClass<PhoneEntryClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x69D200
// VectorClass<PhoneEntryClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x69D240
// VectorClass<PhoneEntryClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69D320
// VectorClass<PhoneEntryClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x69D360
// VectorClass<PhoneEntryClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69D380
// DynamicVectorClass<PhoneEntryClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69D430
// DynamicVectorClass<PhoneEntryClass*>::FindItemIndex (slot 4)
template class VectorClass<PhoneEntryClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69C890
bool VectorResizeFamily::FUN_69C890(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < Count) {
            Count = Length;
        }
        return true;
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69D8C0
void ShaEngineView_0069D8C0::FUN_0069D8C0(const void*& data, long& length)
{
    if (length == 0 || data == 0) return;
    if (PartialCount == 0 && length >= 64) return;

    int take = 64 - PartialCount;
    if (length < take) take = length;
    memcpy(&Partial[PartialCount], data, take);
    data = ((const char*)data) + take;
    PartialCount += take;
    length -= take;

    if (PartialCount == 64) {
        FUN_0069DB30(&Partial[0], Acc);
        Length += 64;
        PartialCount = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69DB30
void SHAState_0069DB30::FUN_0069DB30(const void* source, ShaState_0069DB30& acc) const
{
    unsigned long block[80];
    const unsigned long* data = (const unsigned long*)source;

    int index;
    for (index = 0; index < 16; index++) {
        block[index] = ByteSwap32(*data++);
    }
    for (index = 16; index < 80; index++) {
        block[index] = Rotl32(block[index - 3] ^ block[index - 8] ^ block[index - 16] ^ block[index - 14], 1);
    }

    ShaState_0069DB30 work = acc;

    for (unsigned int round = 0; round < 80; round++) {
        unsigned long temp = Rotl32(work.Long[0], 5) + Function(round, work.Long[1], work.Long[2], work.Long[3]) + work.Long[4] + block[round] + Constant(round);
        work.Long[4] = work.Long[3];
        work.Long[3] = work.Long[2];
        work.Long[2] = Rotl32(work.Long[1], 30);
        work.Long[1] = work.Long[0];
        work.Long[0] = temp;
    }

    acc.Long[0] += work.Long[0];
    acc.Long[1] += work.Long[1];
    acc.Long[2] += work.Long[2];
    acc.Long[3] += work.Long[3];
    acc.Long[4] += work.Long[4];
}
