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
// The element copy ctor 0x7B4690 (__thiscall), dtor 0x7B46F0, operator== 0x7B4780 and operator!= are out-of-line bodies bound by symbol map.

#include "../core/triple_timer_init_methods.h"
#include "../_layout/session_class.h"
#include "../core/mathtbl_init_shapes.h"
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
#include "../ui/shape_button_class.h"
// GLOBAL: GAMEMD 0x87F6C4
extern ColorConvert* DAT_0087F6C4;
#include <objidl.h>
#include "../ui/tooltip_manager_shared.h"
// GLOBAL: GAMEMD 0x887368
extern ToolTipManager* ToolTipManager_Instance;
// Declarations: zero-argument helpers called by native 0x69BB40.
void __fastcall FUN_005BF450(); // 0x5BF450
void __cdecl FUN_00406E80(); // 0x406E80
void __fastcall FUN_00750FA0(); // 0x750FA0
void __fastcall FUN_007535D0(); // 0x7535D0
void __fastcall FUN_00752CA0(); // 0x752CA0
#include "session_entry.h"
#include "../platform/buffer_straws.h"
#include <stdlib.h>
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
#include "../_layout/phone_entry_class.h"
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
#include "../_layout/cell_0050def0.h"

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
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

#include "../_layout/team_005095d0.h"

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

#include "../_layout/obj_005095d0.h"



#include "../_layout/obj_0053ecb0.h"

#include "../_layout/triple_0053eda0.h"

#include "../_layout/obj_0053eda0.h"

#include "../_layout/obj_005402b0.h"

#include "../_layout/obj_00542fc0.h"

#include "../_layout/entry_005657a0.h"

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

#include "../_layout/obj_005657a0.h"


#include "../_layout/iface_005bf500.h"

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

#include "../_layout/vector_005c6120.h"

#include "../_layout/obj_005f9710.h"

#include "../_layout/quad_00645c30.h"

#include "../_layout/record_00656580.h"

#include "../_layout/key_00656580.h"

#include "../_layout/obj_00656580.h"



#include "../_layout/pair_0065c890.h"

#include "../_layout/obj_0068bcb0.h"


#include "../_layout/obj_0068c030.h"


#include "../_layout/owner_006915d0.h"

#include "../_layout/cursor_006915d0.h"

#include "../_layout/obj_00696f10.h"


#include "../_layout/type_006a46d0.h"

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include "../core/vector_class_operations.h"

#include "../core/disk_id.h"


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

// SYNTHETIC: GAMEMD 0x4AEC30 -- emitted BufferStraw scalar deleting destructor.

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

// GLOBAL: GAMEMD 0xB73E44 -- observed written/read extent only.
extern unsigned int DAT_00B73E44[0x800];
// GLOBAL: GAMEMD 0xB76338 -- observed written/read extent only.
extern unsigned int DAT_00B76338[0x40];
// GLOBAL: GAMEMD 0xB07740 -- observed written/read extent only.
extern unsigned int DAT_00B07740;
// GLOBAL: GAMEMD 0xB07744 -- observed written/read extent only.
extern unsigned int DAT_00B07744;
// GLOBAL: GAMEMD 0xB07748 -- observed written/read extent only.
extern unsigned int DAT_00B07748;
extern const char STR_0083EEAC[]; // STRING: GAMEMD 0x83EEAC (decl; reloc)
extern const char STR_00889F64[]; // STRING: GAMEMD 0x889F64 (decl; reloc)

// FUNCTION: GAMEMD 0x6970A0
SessionClass::SessionClass()
    : unknown_04(0) // Declared before profile/record members: native early store.
{
    int index;
    unknown_30C8 = 0;
    GameMode = 0;
    unknown_14 = 2;
    unknown_18.unknown_04 = 0;
    unknown_18.Bases = true;
    unknown_18.Money = 0;
    unknown_18.BridgeDestruction = false;
    unknown_18.Crates = false;
    unknown_18.unknown_1D = false;
    unknown_18.UnitCount = 0;
    unknown_18.ShortGame = false;
    unknown_18.SWAllowed = false;
    unknown_18.unknown_14 = false;
    unknown_18.GameSpeed = 0;
    unknown_18.MultiEngineer = false;
    unknown_18.unknown_CC = false;
    unknown_18.HarvesterTruce = false;
    unknown_18.unknown_CE = false;
    unknown_18.FogOfWar = false;
    unknown_18.MCVRedeploy = false;
    unknown_18.AIDifficulty = 1;
    unknown_144 = 0;
    unknown_148[0] = 0;
    unknown_174 = 0;
    unknown_178 = -1;
    unknown_15C = 2;
    unknown_160 = -1;
    unknown_184 = unknown_174;
    unknown_188 = unknown_178;
    unknown_17C = unknown_15C;
    unknown_180 = unknown_160;
    unknown_1ED9 = true;
    unknown_1ED8 = true;
    unknown_1FC1 = true;
    unknown_1FC0 = true;
    for (index = 0; index < 8; ++index) unknown_307A[index] = 0;
    unknown_3078[0] = 0;
    unknown_306C = 0;
    unknown_306E = 0;
    unknown_3070 = 0;
    unknown_2FF0 = 1250;
    unknown_2FF4 = 0;
    unknown_3018 = true;
    unknown_2F48 = false;
    unknown_301C = 0;
    for (index = 0; index < 0x800; ++index) DAT_00B73E44[index] = 0;
    for (index = 0; index < 0x40; ++index) DAT_00B76338[index] = 0;
    unknown_300 = 0;
    unknown_304 = 0;
    unknown_30C = -1;
    unknown_308 = false;
    unknown_2968 = false;
    unknown_3074 = -1;
    // Exactly42 bytes, not the entire older54hex-byte opaque UTF16 region.
    for (index = 0; index < 21; ++index) unknown_3020[index] = 0;
    unknown_308C = 0;
    unknown_3090 = true;
    unknown_3094 = -1;
    unknown_3098[0] = 0;
    unknown_309C = 20;
    unknown_30A0 = 0;
    unknown_30A4 = 0;
    unknown_30A8 = -1;
    unknown_2984 = 0;
    unknown_688 = false;
    unknown_689 = false;
    unknown_68A = false;
    unknown_310 = 8;
    unknown_318 = 15;
    unknown_330 = 15;
    unknown_314 = 0;
    unknown_31C = 5;
    // Exact native bulk range[33C,67C), after embedded address construction.
    // No vptrs; physical array extent is proved. Not a whole-Session clear.
    memset(unknown_33C, 0, sizeof unknown_33C);
    unknown_334 = 0;
    unknown_338 = 0;
    unknown_67C = false;
    unknown_67D = false;
    unknown_680 = 0;
    unknown_684 = 0;
    unknown_1EDA = 0;
    // Mask behavior only: owning bitfield/state model remains unresolved.
    unknown_1FBC &= 0xFFFFFFFEu;
    unknown_2354.SetFileName(STR_0083EEAC);
    unknown_23C0 &= 0xFFFFFFF8u;
    unknown_23C4 = 0;
    unknown_23D4 = false;
    unknown_23D5 = true;
    unknown_23D6 = false;
    unknown_23D8 = 0;
    unknown_25D8 = 0;
    unknown_287C = 0;
    unknown_2964 = 1;
    unknown_2808 = 558;
    memset(unknown_908, 0, sizeof unknown_908);
    memset(unknown_928, 0xFF, sizeof unknown_928);
    unknown_2880 |= 1u;
    unknown_2884 = 0;
    unknown_2888 = 0x2F8;
    unknown_288C = 3;
    unknown_2890 = 9600;
    unknown_2894 = 0;
    unknown_2898 = -1;
    unknown_289C = 0;
    strcpy(unknown_28A8, STR_00889F64);
    unknown_28F8 = 0;
    unknown_30AC = 0x7FFFFFFF;
    unknown_30B0 = 0;
    unknown_30B4 = 0;
    // Preserve three global reads, even though initial image values are zero.
    unknown_30B8 = DAT_00B07740;
    unknown_30BC = DAT_00B07744;
    unknown_30C0 = DAT_00B07748;
    unknown_30C8 = 0; // Second native write retained.
    unknown_30CC = 0;
    unknown_30D0 = 0;
    unknown_30D4 = 0;
    unknown_2878 = false;
    unknown_18.AIPlayers = 0;
    for (index = 0; index < 8; ++index) {
        unknown_18.unknown_4C[index] = -1;
        unknown_18.unknown_6C[index] = -1;
    }
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_6A8[0] = 0;
    unknown_8CC = 0;
    unknown_8D0 = false;
    unknown_8D4 = 0;
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

// Existing CRT entry declaration shared with CCFile and INI cleanup.
// LIBRARY: GAMEMD 0x007C93E8
extern "C" void __cdecl FUN_007C93E8(void* block);

// FUNCTION: GAMEMD 0x697840
SessionClass::~SessionClass()
{
    while (unknown_2914.Count != 0) {
        delete[] unknown_2914.Items[0];
        unknown_2914.Delete(0);
    }
    while (unknown_292C.Count != 0) {
        // _wcsdup creates mutable allocated storage, retained by a const
        // string-pointer vector. Remove that access qualifier only to release
        // its owned allocation through CRT free, not to write string contents.
        FUN_007C93E8(const_cast<unsigned short*>(unknown_292C.Items[0]));
        unknown_292C.Delete(0);
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
        FUN_004068E0(STR_0083EF60, i, unknown_283C.Items[i], unknown_283C.Items[i]->unknown_6F);
        // Native name pointer is player+0, UTF16 consumed by _wcsicmp.
        if (_wcsicmp(reinterpret_cast<const wchar_t*>(unknown_283C.Items[i]->Name),
            HouseClass_ArrayItems[unknown_283C.Items[i]->unknown_6F]->UIName) != 0)
            return 0;
        if (_wcsicmp(reinterpret_cast<const wchar_t*>(unknown_283C.Items[i]->Name), unknown_3020) == 0) {
            unknown_3074 = unknown_283C.Items[i]->unknown_6F;
            Players_00A8DA78[i]->Address.FUN_0053EDA0(network, node);
            Address_00A8DBA4.FUN_0053ED20(network, node, 0);
            Manager_00A8E9C0.FUN_00543050(&Address_00A8DBA4);
        }
        HouseClass_ArrayItems[unknown_283C.Items[i]->unknown_6F]->TournamentTeamID = unknown_283C.Items[i]->unknown_7B;
        Players_00A8DA78[i]->Address.FUN_0053EDA0(network, node);
        int address = 0;
        for (int j = 0; j < 4; ++j)
            address = (address << 8) | node.Node[j];
        FUN_004068E0(STR_0083EF44, unknown_283C.Items[i]->unknown_6F, address, unknown_283C.Items[i]->unknown_7B);
        HouseClass_ArrayItems[unknown_283C.Items[i]->unknown_6F]->IPAddress = address;
        HouseClass_ArrayItems[unknown_283C.Items[i]->unknown_6F]->LostConnection = 0;
        if (i > 0) {
            Manager_00A8E9C0.FUN_00540DC0(unknown_283C.Items[i]->unknown_6F,
                unknown_283C.Items[i]->Name, &unknown_283C.Items[i]->Address);
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
    unknown_08 = ini->FUN_005276D0(section, STR_008332E8, RulesInstance->GameSpeed);
    unknown_0C = ini->FUN_005276D0(section, STR_00824E38, RulesInstance->Money);
    unknown_10 = ini->FUN_005276D0(section, STR_0083D06C, RulesInstance->UnitCount);
    unknown_14 = ini->FUN_005295F0(section, STR_0083CFA8, RulesInstance->ShortGame);
    unknown_15 = ini->FUN_005295F0(section, STR_0083CF94, RulesInstance->SuperWeaponsAllowed);
    unknown_16 = ini->FUN_005295F0(section, STR_0083CF84, RulesInstance->BuildOffAlly);
    unknown_17 = ini->FUN_005295F0(section, STR_0083EFB8, RulesInstance->MCVRedeploys);
    unknown_18 = ini->FUN_005295F0(section, STR_0083EFA8, RulesInstance->Crates);
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

extern const char STR_0083F368[]; // STRING: GAMEMD 0x0083F368 (decl; reloc)
extern const char STR_0083F358[]; // STRING: GAMEMD 0x0083F358 (decl; reloc)
extern const char STR_0083F348[]; // STRING: GAMEMD 0x0083F348 (decl; reloc)
extern const char STR_0083F334[]; // STRING: GAMEMD 0x0083F334 (decl; reloc)
extern const char STR_0083F32C[]; // STRING: GAMEMD 0x0083F32C (decl; reloc)
extern const char STR_008318B8[]; // STRING: GAMEMD 0x008318B8 (decl; reloc)
extern const char STR_0083F328[]; // STRING: GAMEMD 0x0083F328 (decl; reloc)
extern const char STR_0083F31C[]; // STRING: GAMEMD 0x0083F31C (decl; reloc)
extern const char STR_0083F318[]; // STRING: GAMEMD 0x0083F318 (decl; reloc)
extern const char STR_0083F308[]; // STRING: GAMEMD 0x0083F308 (decl; reloc)
extern const char STR_0083F2F8[]; // STRING: GAMEMD 0x0083F2F8 (decl; reloc)
extern const char STR_0083F2E8[]; // STRING: GAMEMD 0x0083F2E8 (decl; reloc)
extern const char STR_0083F2D8[]; // STRING: GAMEMD 0x0083F2D8 (decl; reloc)
extern const char STR_0083F2CC[]; // STRING: GAMEMD 0x0083F2CC (decl; reloc)
extern const char STR_0083F2B8[]; // STRING: GAMEMD 0x0083F2B8 (decl; reloc)
extern const char STR_0083F2A4[]; // STRING: GAMEMD 0x0083F2A4 (decl; reloc)
extern const char STR_0083F28C[]; // STRING: GAMEMD 0x0083F28C (decl; reloc)
extern const char STR_0083F26C[]; // STRING: GAMEMD 0x0083F26C (decl; reloc)
extern const char STR_0083F254[]; // STRING: GAMEMD 0x0083F254 (decl; reloc)
extern const char STR_0083F23C[]; // STRING: GAMEMD 0x0083F23C (decl; reloc)
extern const char STR_0083F224[]; // STRING: GAMEMD 0x0083F224 (decl; reloc)
extern const char STR_0083F20C[]; // STRING: GAMEMD 0x0083F20C (decl; reloc)
extern const char STR_0083F1F0[]; // STRING: GAMEMD 0x0083F1F0 (decl; reloc)
extern const char STR_0083F1E0[]; // STRING: GAMEMD 0x0083F1E0 (decl; reloc)
extern const char STR_0083F1D4[]; // STRING: GAMEMD 0x0083F1D4 (decl; reloc)
extern const char STR_0083F1C0[]; // STRING: GAMEMD 0x0083F1C0 (decl; reloc)
extern const char STR_0083F1AC[]; // STRING: GAMEMD 0x0083F1AC (decl; reloc)
extern "C" int __cdecl fprintf(FILE*, const char*, ...); // LIBRARY: GAMEMD 0x7CA7D8 (decl; VC6 CRT)
#include "../_layout/rules_class.h"
#include "../core/randomizer.h"
#include "../core/trivial_tu158_methods.h"
#include "mp_game_mode_class_get_methods.h"
#include "../ui/input_controls/ui_display_chain.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
// GLOBAL: GAMEMD 0xB07788
extern bool DAT_00B07788;
// GLOBAL: GAMEMD 0xABFED8
extern int DAT_00ABFED8;
// GLOBAL: GAMEMD 0xB057E0
extern CellStruct DAT_00B057E0;
// Declaration: GAMEMD 0x735090 -- ECX narrow output, EDX wide input, RET4.
void __fastcall FUN_00735090(char* output, const wchar_t* input, int maximum);
extern const char STR_008173F8[]; // STRING: GAMEMD 0x008173F8 (decl; reloc)
extern const char STR_008189B0[]; // STRING: GAMEMD 0x008189B0 (decl; reloc)
extern const char STR_0081C000[]; // STRING: GAMEMD 0x0081C000 (decl; reloc)
extern const char STR_00824314[]; // STRING: GAMEMD 0x00824314 (decl; reloc)
extern const char STR_00825BD4[]; // STRING: GAMEMD 0x00825BD4 (decl; reloc)
extern const char STR_00826420[]; // STRING: GAMEMD 0x00826420 (decl; reloc)
extern const char STR_00826438[]; // STRING: GAMEMD 0x00826438 (decl; reloc)
extern const char STR_0082A2D4[]; // STRING: GAMEMD 0x0082A2D4 (decl; reloc)
extern const char STR_0082A2E8[]; // STRING: GAMEMD 0x0082A2E8 (decl; reloc)
extern const char STR_0082BFAC[]; // STRING: GAMEMD 0x0082BFAC (decl; reloc)
extern const char STR_00832630[]; // STRING: GAMEMD 0x00832630 (decl; reloc)
extern const char STR_0083676C[]; // STRING: GAMEMD 0x0083676C (decl; reloc)
extern const char STR_0083ED5C[]; // STRING: GAMEMD 0x0083ED5C (decl; reloc)
extern const char STR_0083EFDC[]; // STRING: GAMEMD 0x0083EFDC (decl; reloc)
extern const char STR_0083EFE8[]; // STRING: GAMEMD 0x0083EFE8 (decl; reloc)
extern const char STR_0083EFEC[]; // STRING: GAMEMD 0x0083EFEC (decl; reloc)
extern const char STR_0083EFF4[]; // STRING: GAMEMD 0x0083EFF4 (decl; reloc)
extern const char STR_0083EFFC[]; // STRING: GAMEMD 0x0083EFFC (decl; reloc)
extern const char STR_0083F004[]; // STRING: GAMEMD 0x0083F004 (decl; reloc)
extern const char STR_0083F010[]; // STRING: GAMEMD 0x0083F010 (decl; reloc)
extern const char STR_0083F018[]; // STRING: GAMEMD 0x0083F018 (decl; reloc)
extern const char STR_0083F024[]; // STRING: GAMEMD 0x0083F024 (decl; reloc)
extern const char STR_0083F02C[]; // STRING: GAMEMD 0x0083F02C (decl; reloc)
extern const char STR_0083F038[]; // STRING: GAMEMD 0x0083F038 (decl; reloc)
extern const char STR_0083F040[]; // STRING: GAMEMD 0x0083F040 (decl; reloc)
extern const char STR_0083F048[]; // STRING: GAMEMD 0x0083F048 (decl; reloc)
extern const char STR_0083F184[]; // STRING: GAMEMD 0x0083F184 (decl; reloc)
extern const char STR_0083F19C[]; // STRING: GAMEMD 0x0083F19C (decl; reloc)
void __fastcall FUN_00735060(wchar_t* output, const char* input, int maximum);

extern const char* DAT_0083ECFC[];
extern const char STR_00817334[]; // STRING: GAMEMD 0x00817334 (decl; reloc)
extern const char STR_008173F8[]; // STRING: GAMEMD 0x008173F8 (decl; reloc)
extern const char STR_008189B0[]; // STRING: GAMEMD 0x008189B0 (decl; reloc)
extern const char STR_0081B138[]; // STRING: GAMEMD 0x0081B138 (decl; reloc)
extern const char STR_0081C000[]; // STRING: GAMEMD 0x0081C000 (decl; reloc)
extern const char STR_00824314[]; // STRING: GAMEMD 0x00824314 (decl; reloc)
extern const char STR_00825BD4[]; // STRING: GAMEMD 0x00825BD4 (decl; reloc)
extern const char STR_00826420[]; // STRING: GAMEMD 0x00826420 (decl; reloc)
extern const char STR_0082642C[]; // STRING: GAMEMD 0x0082642C (decl; reloc)
extern const char STR_00826438[]; // STRING: GAMEMD 0x00826438 (decl; reloc)
extern const char STR_00826444[]; // STRING: GAMEMD 0x00826444 (decl; reloc)
extern const char STR_0082A2D4[]; // STRING: GAMEMD 0x0082A2D4 (decl; reloc)
extern const char STR_0082A2E8[]; // STRING: GAMEMD 0x0082A2E8 (decl; reloc)
extern const char STR_0082BFAC[]; // STRING: GAMEMD 0x0082BFAC (decl; reloc)
extern const char STR_00832630[]; // STRING: GAMEMD 0x00832630 (decl; reloc)
extern const char STR_0083676C[]; // STRING: GAMEMD 0x0083676C (decl; reloc)
extern const char STR_0083ED5C[]; // STRING: GAMEMD 0x0083ED5C (decl; reloc)
extern const char STR_0083EEB8[]; // STRING: GAMEMD 0x0083EEB8 (decl; reloc)
extern const char STR_0083EFD0[]; // STRING: GAMEMD 0x0083EFD0 (decl; reloc)
extern const char STR_0083EFDC[]; // STRING: GAMEMD 0x0083EFDC (decl; reloc)
extern const char STR_0083EFE8[]; // STRING: GAMEMD 0x0083EFE8 (decl; reloc)
extern const char STR_0083EFEC[]; // STRING: GAMEMD 0x0083EFEC (decl; reloc)
extern const char STR_0083EFF4[]; // STRING: GAMEMD 0x0083EFF4 (decl; reloc)
extern const char STR_0083EFFC[]; // STRING: GAMEMD 0x0083EFFC (decl; reloc)
extern const char STR_0083F004[]; // STRING: GAMEMD 0x0083F004 (decl; reloc)
extern const char STR_0083F010[]; // STRING: GAMEMD 0x0083F010 (decl; reloc)
extern const char STR_0083F018[]; // STRING: GAMEMD 0x0083F018 (decl; reloc)
extern const char STR_0083F024[]; // STRING: GAMEMD 0x0083F024 (decl; reloc)
extern const char STR_0083F02C[]; // STRING: GAMEMD 0x0083F02C (decl; reloc)
extern const char STR_0083F038[]; // STRING: GAMEMD 0x0083F038 (decl; reloc)
extern const char STR_0083F040[]; // STRING: GAMEMD 0x0083F040 (decl; reloc)
extern const char STR_0083F048[]; // STRING: GAMEMD 0x0083F048 (decl; reloc)
extern const char STR_0083F050[]; // STRING: GAMEMD 0x0083F050 (decl; reloc)
extern const char STR_0083F05C[]; // STRING: GAMEMD 0x0083F05C (decl; reloc)
extern const char STR_0083F068[]; // STRING: GAMEMD 0x0083F068 (decl; reloc)
extern const char STR_0083F078[]; // STRING: GAMEMD 0x0083F078 (decl; reloc)
extern const char STR_0083F08C[]; // STRING: GAMEMD 0x0083F08C (decl; reloc)
extern const char STR_0083F09C[]; // STRING: GAMEMD 0x0083F09C (decl; reloc)
extern const char STR_0083F0A8[]; // STRING: GAMEMD 0x0083F0A8 (decl; reloc)
extern const char STR_0083F0B8[]; // STRING: GAMEMD 0x0083F0B8 (decl; reloc)
extern const char STR_0083F0C4[]; // STRING: GAMEMD 0x0083F0C4 (decl; reloc)
extern const char STR_0083F0CC[]; // STRING: GAMEMD 0x0083F0CC (decl; reloc)
extern const char STR_0083F0D0[]; // STRING: GAMEMD 0x0083F0D0 (decl; reloc)
extern const char STR_0083F0D8[]; // STRING: GAMEMD 0x0083F0D8 (decl; reloc)
extern const char STR_0083F0E8[]; // STRING: GAMEMD 0x0083F0E8 (decl; reloc)
extern const char STR_0083F0F4[]; // STRING: GAMEMD 0x0083F0F4 (decl; reloc)
extern const char STR_0083F100[]; // STRING: GAMEMD 0x0083F100 (decl; reloc)
extern const char STR_0083F104[]; // STRING: GAMEMD 0x0083F104 (decl; reloc)
extern const char STR_0083F110[]; // STRING: GAMEMD 0x0083F110 (decl; reloc)
extern const char STR_0083F120[]; // STRING: GAMEMD 0x0083F120 (decl; reloc)
extern const char STR_0083F130[]; // STRING: GAMEMD 0x0083F130 (decl; reloc)
extern const char STR_0083F13C[]; // STRING: GAMEMD 0x0083F13C (decl; reloc)
extern const char STR_0083F148[]; // STRING: GAMEMD 0x0083F148 (decl; reloc)
extern const char STR_0083F150[]; // STRING: GAMEMD 0x0083F150 (decl; reloc)
extern const char STR_0083F158[]; // STRING: GAMEMD 0x0083F158 (decl; reloc)
extern const char STR_0083F160[]; // STRING: GAMEMD 0x0083F160 (decl; reloc)
extern const char STR_0083F170[]; // STRING: GAMEMD 0x0083F170 (decl; reloc)
extern const char STR_0083F184[]; // STRING: GAMEMD 0x0083F184 (decl; reloc)
extern const char STR_0083F190[]; // STRING: GAMEMD 0x0083F190 (decl; reloc)
extern const char STR_0083F19C[]; // STRING: GAMEMD 0x0083F19C (decl; reloc)
extern const char STR_00889F64[]; // STRING: GAMEMD 0x00889F64 (decl; reloc)
// FUNCTION: GAMEMD 0x6980C0
void SessionClass::FUN_006980C0()
{
    Rules->Read_Countries(DAT_00887048);
    for (int stringIndex = 0; stringIndex < unknown_2914.Count; ++stringIndex)
        delete[] unknown_2914.Items[stringIndex];
    unknown_2914.Clear();
    for (int entryIndex = 0; entryIndex < unknown_28FC.Count; ++entryIndex) {
        PhoneEntryClass* entry = unknown_28FC.Items[entryIndex];
        if (entry) delete entry;
    }
    unknown_28FC.Clear();
    // Native4739F0 is CCFileClass, not RawFileClass65CA80. No Exists/Open.
    CCFileClass file(STR_00826444);
    if (!DAT_00B07788) {
        unknown_2FF0 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_00826438, 1250);
        unknown_2FF4 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083F19C, 0);
        int fallback = DAT_00886B88.RandomRanged(0, 0x8000) + 0x1000;
        DAT_00ABFED8 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_00826420, fallback);
        DAT_00B07788 = true;
        DAT_00ABFEC8.FUN_005D93D0();
    }
    Session_00A8B238.unknown_2F48 = DAT_008870C0.FUN_005295F0(STR_0082642C, STR_0082A2E8, false);
    Session_00A8B238.unknown_301C = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0082A2D4, 0);
    char buffer[1024];
    buffer[0] = 0;
    unknown_2884 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083F190, -1);
    unknown_30D0 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083F184, 0);
    unknown_308 = DAT_008870C0.FUN_005295F0(STR_0082642C, STR_0083F170, unknown_308);
    unknown_30C = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083F160, -1);
    wchar_t handle[20];
    DAT_008870C0.FUN_00528F00(STR_0082642C, STR_0083F158,
        FUN_00734E60(STR_0083676C, 0, STR_0083EEB8, 0x4EE), handle, 20);
    FUN_00735090(unknown_148, handle, -1);
    unknown_17C = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0081B138, unknown_17C);
    unknown_180 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083F150, unknown_180);
    unknown_184 = DAT_008870C0.FUN_00475540(STR_0082642C, STR_00817334, unknown_184);
    unknown_188 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083F148, unknown_188);
    unknown_1ED9 = DAT_008870C0.FUN_005295F0(STR_0082642C, STR_0083F13C, unknown_1ED9);
    unknown_1ED8 = DAT_008870C0.FUN_005295F0(STR_0082642C, STR_0083F130, unknown_1ED8);
    unknown_1FC1 = DAT_008870C0.FUN_005295F0(STR_0082642C, STR_0083F120, unknown_1FC1);
    unknown_1FC0 = DAT_008870C0.FUN_005295F0(STR_0082642C, STR_0083F110, unknown_1FC0);
    unknown_174 = unknown_184;
    if (unknown_184 == -2) unknown_174 = 0;
    unknown_178 = unknown_188;
    int mode = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_0083EFD0, 1);
    unknown_04 = MultiplayerGameMode_Get(mode);
    if (!unknown_04) unknown_04 = FUN_005D5E10();
    unknown_18C.FUN_00697F10(&DAT_008870C0, STR_0083F104, 1, 6);
    unknown_208.FUN_00697F10(&DAT_008870C0, STR_0083F100, 2, 2);
    unknown_284.FUN_00697F10(&DAT_008870C0, STR_0083F0F4, 2, 2);

    DAT_008870C0.FUN_00528A10(STR_0083F0D8, STR_0083F0E8, buffer, unknown_28B8, 0x3F);
    if (strcmp(unknown_28B8, buffer) == 0) unknown_28B8[0] = 0;
    unknown_2888 = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F0D0, 0);
    unknown_288C = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F0CC, -1);
    unknown_2890 = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F0C4, -1);
    unknown_28A0 = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F0B8, 0);
    unknown_28A4 = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F0A8, 0);
    DAT_008870C0.FUN_00528A10(STR_0083F0D8, STR_0083F09C, STR_0083ED5C, buffer, 2);
    int method;
    for (method = 0; method < 2; ++method) {
        if (_stricmp(buffer, DAT_0083ECFC[method]) == 0) {
            unknown_2894 = method;
            break;
        }
    }
    if (method == 2) unknown_2894 = 0;
    unknown_2898 = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F08C, -1);
    unknown_289C = DAT_008870C0.FUN_005276D0(STR_0083F0D8, STR_0083F078, 3);
    DAT_008870C0.FUN_00528A10(STR_0083F0D8, STR_0083F068, STR_00889F64, unknown_28A8, 16);
    if (unknown_288C == 0 || unknown_2890 == 0) {
        unknown_2888 = 0;
        unknown_288C = -1;
        unknown_2890 = -1;
    }
    int initCount = DAT_008870C0.GetKeyCount(STR_0083F05C);
    for (int initIndex = 0; initIndex < initCount; ++initIndex) {
        char* text = new char[41];
        if (text) {
            text[0] = 0;
            const char* key = DAT_008870C0.GetKeyName(STR_0083F05C, initIndex);
            DAT_008870C0.FUN_00528A10(STR_0083F05C, key, 0, text, 41);
            _strupr(text);
            unknown_2914.AddItem(text); // Native leaks allocation on append failure.
        }
    }
    unknown_2898 = initCount != 0 ? 0 : -1; // Overrides previously read INI value.
    int phoneCount = DAT_008870C0.GetKeyCount(STR_0083F050);
    for (int phoneIndex = 0; phoneIndex < phoneCount; ++phoneIndex) {
        PhoneEntryClass* entry = new PhoneEntryClass; // Native allocatesB0, no ctor.
        // Native does NOT test allocation before dereferencing; do not add guard.
        const char* key = DAT_008870C0.GetKeyName(STR_0083F050, phoneIndex);
        DAT_008870C0.FUN_00528A10(STR_0083F050, key, 0, buffer, 1024);
        char* token = strtok(buffer, STR_00832630);
        if (token) {
            FUN_00735060(entry->unknown_70, token, -1);
            _wcsupr(entry->unknown_70);
        } else entry->unknown_70[0] = 0;
        token = strtok(0, STR_00832630);
        if (token) {
            strcpy(entry->unknown_9A, token);
            _strupr(entry->unknown_9A);
        } else entry->unknown_9A[0] = 0;
        token = strtok(0, STR_00832630);
        if (token) sscanf(token, STR_00825BD4, &entry->unknown_00);
        else entry->unknown_00 = 0;
        token = strtok(0, STR_00832630);
        entry->unknown_04 = token ? atoi(token) : -1;
        token = strtok(0, STR_00832630);
        entry->unknown_08 = token ? atoi(token) : -1;
        token = strtok(0, STR_00832630);
        entry->unknown_18 = token ? atoi(token) : -1;
        token = strtok(0, STR_00832630);
        entry->unknown_1C = token ? atoi(token) : 0;
        token = strtok(0, STR_00832630);
        if (!token) entry->unknown_0C = 0;
        else {
            strcpy(buffer, token);
            for (method = 0; method < 2; ++method) {
                if (_stricmp(buffer, DAT_0083ECFC[method]) == 0) {
                    entry->unknown_0C = method;
                    break;
                }
            }
            if (method == 2) entry->unknown_0C = 0;
        }
        token = strtok(0, STR_00832630);
        entry->unknown_10 = token ? atoi(token) : -1;
        token = strtok(0, STR_00832630);
        entry->unknown_14 = token ? atoi(token) : 3;
        token = strtok(0, STR_00832630);
        if (token) strcpy(entry->unknown_20, token);
        else entry->unknown_20[0] = 0;
        unknown_28FC.AddItem(entry); // Failure leaks entry, as native.
    }
    if ((Session_00A8B238.unknown_23C0 & 2) != 0) {
        unknown_30AC = DAT_008870C0.FUN_005276D0(STR_0083F040, STR_0083F048, 0x7FFFFFFF);
        DAT_008870C0.FUN_00528A10(STR_0083F040, STR_00824314, STR_0083F038, buffer, 80);
        if (_stricmp(buffer, STR_0083F02C) == 0) unknown_30B0 = 2;
        else if (_stricmp(buffer, STR_0083F024) == 0) unknown_30B0 = 4;
        else if (_stricmp(buffer, STR_0083F018) == 0) unknown_30B0 = 6;
        else if (_stricmp(buffer, STR_0083F010) == 0) unknown_30B0 = 8;
        else if (_stricmp(buffer, STR_0083F004) == 0) unknown_30B0 = 15;
        else if (_stricmp(buffer, STR_0083EFFC) == 0) unknown_30B0 = 1;
        else unknown_30B0 = 0;
        DAT_008870C0.FUN_00528A10(STR_0083F040, STR_0083EFF4, STR_0082BFAC, buffer, 80);
        int x, y, z; // Native first parse results are locals, not Session coords.
        sscanf(buffer, STR_008189B0, &x, &y, &z);
        int target = DAT_008870C0.FUN_005276D0(STR_0083F040, STR_0083EFEC, -1);
        unknown_30C8 = target >> 24;
        unknown_30C4 = target & 0x00FFFFFF;
        DAT_008870C0.FUN_00528A10(STR_0083F040, STR_008173F8, STR_0083EFE8, buffer, 80);
        sscanf(buffer, STR_0081C000, &x, &y); // Reuses prior parse slots.
        CellStruct cell;
        cell.X = x;
        cell.Y = y;
        if (cell.X != DAT_00B057E0.X || cell.Y != DAT_00B057E0.Y)
            unknown_30CC = Map_0087F7E8.FUN_005657A0(&cell);
        unknown_30D4 = DAT_008870C0.FUN_005276D0(STR_0083F040, STR_0083EFDC, 0x7FFFFFFF);
    }
    // Natural CCFile destructor runs only now, after all reads/allocations.
}

// FUNCTION: GAMEMD 0x698CB0
bool SessionClass::FUN_00698CB0(FILE* output)
{
    int selected = Session_00A8B238.unknown_18.unknown_04;
    if (selected < 0) {
        fprintf(output, STR_0083F368);
        Session_00A8B238.unknown_18.unknown_04 = 0;
        selected = 0;
    }
    // Native passes the mission-record pointer itself with a narrow %s.
    // Preserve that exact address; do not substitute its filename or a wide
    // conversion. The format/type anomaly is recorded as primary evidence.
    fprintf(output, STR_0083F358,
        Session_00A8B238.unknown_690.Items[selected]);
    fprintf(output, STR_0083F348, unknown_148);
    unsigned char network[4];
    unsigned char node[6];
    unsigned int part;
    for (int index = 0; index < unknown_314; ++index) {
        Session_00A8B238.unknown_283C.Items[index]->Address.GetAddress(network, node);
        fprintf(output, STR_0083F334, index);
        for (part = 0; part < 4; ++part)
            fprintf(output, STR_0083F32C, network[part]);
        fprintf(output, STR_008318B8);
        for (part = 0; part < 6; ++part)
            fprintf(output, STR_0083F32C, node[part]);
        fprintf(output, STR_0083F328);
    }
    fprintf(output, STR_0083F328);
    Session_00A8B238.unknown_8E4.GetAddress(network, node);
    fprintf(output, STR_0083F31C);
    for (part = 0; part < 4; ++part)
        fprintf(output, STR_0083F32C, network[part]);
    fprintf(output, STR_008318B8);
    for (part = 0; part < 6; ++part)
        fprintf(output, STR_0083F32C, node[part]);
    fprintf(output, STR_0083F318);
    fprintf(output, STR_0083F308, unknown_318);
    fprintf(output, STR_0083F2F8, unknown_680);
    fprintf(output, STR_0083F2E8, unknown_17C);
    fprintf(output, STR_0083F2D8, unknown_15C);
    fprintf(output, STR_0083F2CC, unknown_174);
    fprintf(output, STR_0083F2B8, unknown_314);
    fprintf(output, STR_0083F2A4, unknown_18.Bases);
    fprintf(output, STR_0083F28C, unknown_18.Money);
    fprintf(output, STR_0083F26C, unknown_18.BridgeDestruction);
    fprintf(output, STR_0083F254, unknown_18.Crates);
    fprintf(output, STR_0083F23C, unknown_18.unknown_1D);
    fprintf(output, STR_0083F224, unknown_18.UnitCount);
    fprintf(output, STR_0083F20C, unknown_18.AIPlayers);
    fprintf(output, STR_0083F1F0, unknown_18.AIDifficulty);
    fprintf(output, STR_0083F1E0, unknown_300);
    int mode = Session_00A8B238.GameMode;
    if (mode == 3)
        fprintf(output, STR_0083F1D4);
    else if (mode == 4)
        fprintf(output, STR_0083F1C0);
    else
        fprintf(output, STR_0083F1AC);
    return true;
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

extern const char STR_00817334[]; // STRING: GAMEMD 0x00817334 (decl; reloc)
extern const char STR_0081898C[]; // STRING: GAMEMD 0x0081898C (decl; reloc)
extern const char STR_0081B138[]; // STRING: GAMEMD 0x0081B138 (decl; reloc)
extern const char STR_0083F050[]; // STRING: GAMEMD 0x0083F050 (decl; reloc)
extern const char STR_0083F05C[]; // STRING: GAMEMD 0x0083F05C (decl; reloc)
extern const char STR_0083F068[]; // STRING: GAMEMD 0x0083F068 (decl; reloc)
extern const char STR_0083F078[]; // STRING: GAMEMD 0x0083F078 (decl; reloc)
extern const char STR_0083F08C[]; // STRING: GAMEMD 0x0083F08C (decl; reloc)
extern const char STR_0083F09C[]; // STRING: GAMEMD 0x0083F09C (decl; reloc)
extern const char STR_0083F0A8[]; // STRING: GAMEMD 0x0083F0A8 (decl; reloc)
extern const char STR_0083F0B8[]; // STRING: GAMEMD 0x0083F0B8 (decl; reloc)
extern const char STR_0083F0C4[]; // STRING: GAMEMD 0x0083F0C4 (decl; reloc)
extern const char STR_0083F0CC[]; // STRING: GAMEMD 0x0083F0CC (decl; reloc)
extern const char STR_0083F0D0[]; // STRING: GAMEMD 0x0083F0D0 (decl; reloc)
extern const char STR_0083F0D8[]; // STRING: GAMEMD 0x0083F0D8 (decl; reloc)
extern const char STR_0083F0E8[]; // STRING: GAMEMD 0x0083F0E8 (decl; reloc)
extern const char STR_0083F0F4[]; // STRING: GAMEMD 0x0083F0F4 (decl; reloc)
extern const char STR_0083F100[]; // STRING: GAMEMD 0x0083F100 (decl; reloc)
extern const char STR_0083F104[]; // STRING: GAMEMD 0x0083F104 (decl; reloc)
extern const char STR_0083F148[]; // STRING: GAMEMD 0x0083F148 (decl; reloc)
extern const char STR_0083F150[]; // STRING: GAMEMD 0x0083F150 (decl; reloc)
extern const char STR_0083F158[]; // STRING: GAMEMD 0x0083F158 (decl; reloc)
extern const char STR_0083F160[]; // STRING: GAMEMD 0x0083F160 (decl; reloc)
extern const char STR_0083F170[]; // STRING: GAMEMD 0x0083F170 (decl; reloc)
extern const char STR_0083F190[]; // STRING: GAMEMD 0x0083F190 (decl; reloc)
extern const char STR_0083F384[]; // STRING: GAMEMD 0x0083F384 (decl; reloc)
// GLOBAL: GAMEMD 0x83ECFC
extern const char* DAT_0083ECFC[];
// Declaration: GAMEMD 0x735120 -- fastcall ECX narrow input, EAX wide result.
extern "C" wchar_t* __fastcall Widen_00735120(const char* text);

// FUNCTION: GAMEMD 0x6990A0
void SessionClass::FUN_006990A0()
{
    RawFileClass file(STR_00826444);
    DAT_008870C0.WriteInteger(STR_0082642C, STR_0083F190, unknown_2884, 0);
    DAT_008870C0.WriteBool(STR_0082642C, STR_0083F170, unknown_308);
    DAT_008870C0.WriteInteger(STR_0082642C, STR_0083F160, unknown_30C, 0);
    DAT_008870C0.FUN_00528E00(STR_0082642C, STR_0083F158,
                              Widen_00735120(unknown_148));
    DAT_008870C0.WriteInteger(STR_0082642C, STR_0081B138, unknown_17C, 0);
    DAT_008870C0.WriteInteger(STR_0082642C, STR_0083F150, unknown_180, 0);
    DAT_008870C0.FUN_00475610(STR_0082642C, STR_00817334, unknown_184);
    DAT_008870C0.WriteInteger(STR_0082642C, STR_0083F148, unknown_188, 0);
    if (unknown_04)
        DAT_008870C0.WriteInteger(STR_0082642C, STR_0083EFD0, unknown_04->unknown_28, 0);
    else
        DAT_008870C0.WriteInteger(STR_0082642C, STR_0083EFD0, 0, 0);
    unknown_18C.FUN_00698F90(&DAT_008870C0, STR_0083F104);
    unknown_208.FUN_00698F90(&DAT_008870C0, STR_0083F100);
    unknown_284.FUN_00698F90(&DAT_008870C0, STR_0083F0F4);

    DAT_008870C0.Clear(STR_0083F0D8, 0);
    DAT_008870C0.WriteString(STR_0083F0D8, STR_0083F068, unknown_28A8);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F078, unknown_289C, 0);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F08C, unknown_2898, 0);
    DAT_008870C0.WriteString(STR_0083F0D8, STR_0083F09C, DAT_0083ECFC[unknown_2894]);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F0C4, unknown_2890, 0);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F0CC, unknown_288C, 0);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F0D0, unknown_2888, 1);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F0B8, unknown_28A0, 0);
    DAT_008870C0.WriteInteger(STR_0083F0D8, STR_0083F0A8, unknown_28A4, 0);
    DAT_008870C0.WriteString(STR_0083F0D8, STR_0083F0E8, unknown_28B8);

    DAT_008870C0.Clear(STR_0083F05C, 0);
    char key[12];
    for (int index = 0; index < unknown_2914.Count; ++index) {
        wsprintfA(key, STR_0081898C, index);
        // Items reload after the formatting callback, Count after WriteString.
        DAT_008870C0.WriteString(STR_0083F05C, key, unknown_2914.Items[index]);
    }
    DAT_008870C0.Clear(STR_0083F050, 0);
    // Snapshot count once, reverse scan. Pointer reloaded each iteration,
    // then held across the two formatting calls as native EAX snapshot.
    for (int phoneIndex = unknown_28FC.Count - 1; phoneIndex >= 0; --phoneIndex) {
        PhoneEntryClass* entry = unknown_28FC.Items[phoneIndex];
        char line[128];
        wsprintfA(line, STR_0083F384,
                  entry->unknown_70, entry->unknown_9A,
                  entry->unknown_00, entry->unknown_04, entry->unknown_08,
                  entry->unknown_18, entry->unknown_1C,
                  DAT_0083ECFC[entry->unknown_0C], entry->unknown_10,
                  entry->unknown_14, entry->unknown_20);
        wsprintfA(key, STR_0081898C, phoneIndex);
        DAT_008870C0.WriteString(STR_0083F050, key, line);
    }
    DAT_008870C0.WriteCCFile(&file, false);
    // Natural RawFileClass destructor65CA00 follows; no explicit close/new INI.
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
unsigned int SessionClass::FUN_0069A310(unsigned int index)
{
    if (index == 0xFFFFFFFEU)
        index = 8;
    if (index < 9)
        return DAT_0083ED14[index];
    return index;
}

// FUNCTION: GAMEMD 0x69B720
// Branching.
int SessionClass::FUN_0069B720()
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
#include "../core/string_class.h"

template class DynamicVectorClass<Wstring>;

#include "session_class_resume_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F1190
extern const double DAT_007F1190;
// GLOBAL: GAMEMD 0xB057E8
extern double DAT_00B057E8;

// SYNTHETIC: GAMEMD 0x00696D50
// dynamic initializer for DAT_00B07778
// GLOBAL: GAMEMD 0x00B07778
double DAT_00B07778 = DAT_00B057E8 / DAT_007F1190;

// SYNTHETIC: GAMEMD 0x00696D70
// dynamic initializer for DAT_00B07760
// GLOBAL: GAMEMD 0x00B07760
double DAT_00B07760 = 1.0 / DAT_00B07778;

GG_STATIC_ASSERT(sizeof(DAT_00B07778) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00B07760) == 8);

// SYNTHETIC: GAMEMD 0x00696EF0
// GLOBAL: GAMEMD 0x00B07768
MathTblCoord DAT_00B07768;

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

#include "../_layout/house_class.h"
#include "../core/scenario_class_methods.h"
#include "../core/vector_class_operations.h"
// GLOBAL: GAMEMD 0xA8B230
extern ScenarioClass* ScenarioInstance;
// Declaration: GLOBAL GAMEMD 0xA80228 -- existing house-vector owner.
extern DynamicVectorClass<HouseClass*> HouseArray_00A80228;
// Declaration: GLOBAL GAMEMD 0xB77A04 -- logical buffer bounds unproven.
extern char DAT_00B77A04[];
// Declaration: GLOBAL GAMEMD 0xB76568 -- logical buffer bounds unproven.
extern char DAT_00B76568[];
// Declaration: STRING GAMEMD 0x83F6B8
extern const char STR_0083F6B8[];
// Declaration: STRING GAMEMD 0x83F6A8
extern const char STR_0083F6A8[];
// Declaration: STRING GAMEMD 0x817F70 -- comma, primary bytes confirmed.
extern const char STR_00817F70[];
// Declaration: FUNCTION GAMEMD 0x4068E0
extern "C" int __cdecl FUN_004068E0(const char*, ...);
GG_STATIC_ASSERT(offsetof(SessionClass, unknown_688) == 0x688);
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer) == 0x1EC);
GG_STATIC_ASSERT(offsetof(HouseClass, PlainName) == 0x15FF4);
// FUNCTION: GAMEMD 0x69B170
void SessionClass::FUN_0069B170()
{
    unknown_688 = 0;
    if (GameMode != 4) return;
    ScenarioInstance->unknown_0000 &= ~0x400U;
    FUN_004068E0(STR_0083F6B8, DAT_00B77A04);
    FUN_004068E0(STR_0083F6A8, DAT_00B76568);
    if (strlen(DAT_00B77A04) == 0) return;
    if (strlen(DAT_00B76568) == 0) return;

    DynamicVectorClass<HouseClass*> first;
    DynamicVectorClass<HouseClass*> second;
    // Native compares lengths unsigned and selects the SECOND on a tie.
    const char* longest = strlen(DAT_00B77A04) > strlen(DAT_00B76568)
        ? DAT_00B77A04 : DAT_00B76568;
    char* buffer = new char[strlen(longest) + 32];
    strcpy(buffer, DAT_00B77A04);
    char* token = strtok(buffer, STR_00817F70);
    while (token != 0 && *token != 0) {
        for (int index = 0; index < HouseArray_00A80228.Count; ++index) {
            HouseClass* house = HouseArray_00A80228.Items[index];
            if (house->IsHumanPlayer && _stricmp(house->PlainName, token) == 0)
                first.AddItem(house);
        }
        token = strtok(0, STR_00817F70);
    }
    strcpy(buffer, DAT_00B76568);
    token = strtok(buffer, STR_00817F70);
    while (token != 0 && *token != 0) {
        for (int index = 0; index < HouseArray_00A80228.Count; ++index) {
            HouseClass* house = HouseArray_00A80228.Items[index];
            if (house->IsHumanPlayer && _stricmp(house->PlainName, token) == 0)
                second.AddItem(house);
        }
        token = strtok(0, STR_00817F70);
    }
    if (first.Count > 1) {
        for (int index = 0; index < first.Count; ++index) {
            for (int other = 0; other < first.Count; ++other) {
                if (first.Items[index]->ArrayIndex != first.Items[other]->ArrayIndex)
                    first.Items[index]->FUN_004F9B70(first.Items[other], false);
            }
        }
    }
    if (second.Count > 1) {
        for (int index = 0; index < second.Count; ++index) {
            for (int other = 0; other < second.Count; ++other) {
                if (second.Items[index]->ArrayIndex != second.Items[other]->ArrayIndex)
                    second.Items[index]->FUN_004F9B70(second.Items[other], false);
            }
        }
    }
    delete[] buffer;
    unknown_688 = 1;
    ScenarioInstance->unknown_0000 |= 0x400U;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69ADE0
// Stores its argument in a member; pops its stack arguments.
void Obj_0069ADE0::FUN_0069ADE0(unsigned char a1)
{
    unknown_17C = a1;
}

// REA Evidence: ev_11ce794979f0e2980076f87c1eeffe96d530e6c29faed93d9a77c5cc87f93a03
#include "../platform/ccfile_class.h"
GG_STATIC_ASSERT(sizeof(RawFileClass) == 0x24);
extern const char STR_00830A14[]; // STRING: GAMEMD 0x830A14 (decl; reloc)

extern const char STR_00817854[]; // STRING: GAMEMD 0x00817854 (decl; reloc)
extern const char STR_0081BFE0[]; // STRING: GAMEMD 0x0081BFE0 (decl; reloc)
extern const char STR_00829284[]; // STRING: GAMEMD 0x00829284 (decl; reloc)
extern const char STR_0082BF9C[]; // STRING: GAMEMD 0x0082BF9C (decl; reloc)
extern const char STR_00831898[]; // STRING: GAMEMD 0x00831898 (decl; reloc)
extern const char STR_0083DC5C[]; // STRING: GAMEMD 0x0083DC5C (decl; reloc)
extern const char STR_0083F3A8[]; // STRING: GAMEMD 0x0083F3A8 (decl; reloc)
extern const char STR_0083F3BC[]; // STRING: GAMEMD 0x0083F3BC (decl; reloc)
extern const char STR_0083F3F0[]; // STRING: GAMEMD 0x0083F3F0 (decl; reloc)
extern const char STR_0083F3FC[]; // STRING: GAMEMD 0x0083F3FC (decl; reloc)
extern const char STR_0083F408[]; // STRING: GAMEMD 0x0083F408 (decl; reloc)
extern const char STR_0083F440[]; // STRING: GAMEMD 0x0083F440 (decl; reloc)
extern const char STR_0083F44C[]; // STRING: GAMEMD 0x0083F44C (decl; reloc)
extern const char STR_0083F484[]; // STRING: GAMEMD 0x0083F484 (decl; reloc)
extern const char STR_0083F488[]; // STRING: GAMEMD 0x0083F488 (decl; reloc)
extern const char STR_00889F64[]; // STRING: GAMEMD 0x00889F64 (decl; reloc)
void __fastcall FUN_00735060(wchar_t* out, const char* text, int length);

// FUNCTION: GAMEMD 0x6994F0
void __fastcall FUN_006994F0(const char* filename, wchar_t* description,
                            char* digest, char* modes, bool* official,
                            int* minimum, int* maximum)
{
    CCFileClass file(filename);
    if (!file.Exists(false) || !file.Open(1)) return;
    char* front = 0;
    char* end = 0;
    bool foundBasic = false;
    int percent;
    for (percent = 5; percent <= 100; percent += 5) {
        // Native signed32 multiplication happens BEFORE division by100.
        int length = file.GetFileSize() * percent / 100;
        if (front) delete[] front;
        front = new char[length + 1];
        if (!front) return;
        file.Seek(0, 0);
        file.ReadBytes(front, length);
        front[length] = 0;
        char* begin = strstr(front, STR_0083F488); // [Basic]
        if (begin) {
            end = strstr(begin + 5, STR_0083F484); // raw marker is newline+'['
            // Both successful strstr results lie in the same allocation.
            // Keep a normal null check; any extra instruction is a future
            // partial-match delta, not a reason for pointer/integer steering.
            if (end != 0 && end > begin) {
                end[1] = 0; // overwrite '[', retain preceding newline
                FUN_004068E0(STR_0083F44C, percent);
                foundBasic = true;
                break;
            }
        }
    }
    if (!foundBasic) {
        delete[] front;
        return;
    }
    char* back = 0;
    bool foundDigest = false;
    for (percent = 1; percent <= 100; ++percent) {
        int length = file.GetFileSize() * percent / 100;
        if (back) delete[] back;
        back = new char[length + 1];
        // Native null suffix allocation returns without releasing front.
        // Raw ownership deliberately preserves that behavior; no RAII fix.
        if (!back) return;
        file.Seek(-length, 2);
        file.ReadBytes(back, length);
        back[length] = 0;
        if (strstr(back, STR_0083F440)) { // [Digest]
            FUN_004068E0(STR_0083F408, percent);
            foundDigest = true;
            break;
        }
    }
    if (!foundDigest) {
        delete[] front;
        delete[] back;
        return;
    }
    CCINIClass basicIni;
    // Front stream starts at allocation beginning, not at '[Basic]'. Its
    // length excludes the newline at end, despite end[1] being the terminator.
    BufferStraw basicStream(front, end - front);
    basicIni.FUN_00474320(&basicStream, false, false);
    CCINIClass digestIni;
    BufferStraw digestStream(back, strlen(back) + 1);
    digestIni.FUN_00474320(&digestStream, false, false);
    *minimum = basicIni.FUN_005276D0(STR_0082BF9C, STR_0083F3FC, *minimum);
    *maximum = basicIni.FUN_005276D0(STR_0082BF9C, STR_0083F3F0, *maximum);
    basicIni.FUN_00528A10(STR_0082BF9C, STR_0083EFD0, STR_00889F64, modes, 0x100);
    char name[64];
    basicIni.FUN_00528A10(STR_0082BF9C, STR_00817854, STR_00829284, name, 0x40);
    FUN_00735060(description, name, -1);
    digestIni.FUN_00528A10(STR_0081BFE0, STR_00831898, STR_0083F3E4, digest, 0x20);
    bool isOfficial = basicIni.FUN_005295F0(STR_0082BF9C, STR_0083DC5C, false);
    *official = isOfficial;
    FUN_004068E0(STR_0083F3BC, filename, *minimum, *maximum, isOfficial, name);
    FUN_004068E0(STR_0083F3A8, modes);
    // Deliberately before borrowed straw/INI destructors. Native order then:
    // digestStream, digestIni, basicStream, basicIni, file. No explicit dtors.
    delete[] front;
    delete[] back;
}

extern const char STR_0081B1A4[]; // STRING: GAMEMD 0x0081B1A4 (decl; reloc)
extern const char STR_0081B1D4[]; // STRING: GAMEMD 0x0081B1D4 (decl; reloc)
extern const char STR_0082DF18[]; // STRING: GAMEMD 0x0082DF18 (decl; reloc)
extern const char STR_0083F608[]; // STRING: GAMEMD 0x0083F608 (decl; reloc)
extern const char STR_0083F648[]; // STRING: GAMEMD 0x0083F648 (decl; reloc)

#include "../platform/mix_file_class.h"
extern const wchar_t STR_0082083C[]; // STRING: GAMEMD 0x0082083C (decl; reloc)
extern const char STR_0083F490[]; // STRING: GAMEMD 0x0083F490 (decl; reloc)
extern const char STR_0083F498[]; // STRING: GAMEMD 0x0083F498 (decl; reloc)
extern const wchar_t STR_0083F4CC[]; // STRING: GAMEMD 0x0083F4CC (decl; reloc)
extern const wchar_t STR_0083F4DC[]; // STRING: GAMEMD 0x0083F4DC (decl; reloc)
extern const char STR_0083F4F0[]; // STRING: GAMEMD 0x0083F4F0 (decl; reloc)
extern const char STR_0083F4F4[]; // STRING: GAMEMD 0x0083F4F4 (decl; reloc)
extern const char STR_0083F504[]; // STRING: GAMEMD 0x0083F504 (decl; reloc)
extern const char STR_0083F50C[]; // STRING: GAMEMD 0x0083F50C (decl; reloc)
extern const char STR_0083F514[]; // STRING: GAMEMD 0x0083F514 (decl; reloc)
extern const char STR_0083F520[]; // STRING: GAMEMD 0x0083F520 (decl; reloc)
extern const char STR_00886980[]; // STRING: GAMEMD 0x00886980 (decl; reloc)

GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, dwFileAttributes) == 0);
GG_STATIC_ASSERT(sizeof(((WIN32_FIND_DATAA*)0)->dwFileAttributes) == 4);
GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, cFileName) == 0x2C);
GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, cAlternateFileName) == 0x130);
GG_STATIC_ASSERT(sizeof(((WIN32_FIND_DATAA*)0)->cFileName) == 260);
GG_STATIC_ASSERT(sizeof(((WIN32_FIND_DATAA*)0)->cAlternateFileName) == 14);
GG_STATIC_ASSERT(sizeof(WIN32_FIND_DATAA) == 0x140);

// FUNCTION: GAMEMD 0x699980
void SessionClass::FUN_00699980()
{
    INIClass ini; // Native base vptr7EA5F4, NOT CCINIClass7E1AF4.
    unknown_690.Clear(); // Does not delete pointees; preserve separate cleanup.
    CCFileClass file(STR_0083F520);
    char section[64];
    char digest[32];
    wchar_t display[44];
    WIN32_FIND_DATAA found;
    wchar_t players[64];
    wchar_t description[64];
    char filename[256];
    char modes[256];
    if (file.Exists(false)) {
        ini.FUN_00525A10(&file, false);
        int count = ini.GetKeyCount(STR_0083F514);
        for (int index = 0; index < count; ++index) {
            if (ini.FUN_00528A10(STR_0083F514, ini.GetKeyName(STR_0083F514, index), STR_00889F64, section, 64) != 0) {
                MultiMission* mission = new MultiMission(&ini, section);
                unknown_690.AddItem(mission); // Native appends null on allocation failure.
            }
        }
    }
    ini.Clear(0, 0);
    file.Close();
    HANDLE search = FindFirstFileA(STR_0083F50C, &found);
    if (search != INVALID_HANDLE_VALUE) {
        do {
            if ((found.dwFileAttributes & 0x116) == 0) {
                const char* name = found.cAlternateFileName;
                if (strlen(name) == 0) name = found.cFileName;
                if (_stricmp(name, STR_0083F520) != 0) {
                    file.SetFileName(name);
                    ini.FUN_00525A10(&file, false); // No Exists test in PKT path.
                    int count = ini.GetKeyCount(STR_0083F514);
                    for (int index = 0; index < count; ++index) {
                        if (ini.FUN_00528A10(STR_0083F514, ini.GetKeyName(STR_0083F514, index), STR_00889F64, section, 64) != 0) {
                            MultiMission* mission = new MultiMission(&ini, section);
                            unknown_690.AddItem(mission); // Null appends retained.
                        }
                    }
                }
            }
        } while (FindNextFileA(search, &found));
        FindClose(search);
    }
    ini.Clear(0, 0);
    file.Close();

    search = FindFirstFileA(STR_0083F504, &found);
    int savedSearchMode = g_FileSearchMode;
    SetFileSearchMode(-2); // Called even if no YRO handle exists.
    if (search != INVALID_HANDLE_VALUE) {
        do {
            if ((found.dwFileAttributes & 0x116) == 0) {
                const char* name = found.cAlternateFileName;
                if (strlen(name) == 0) name = found.cFileName;
                if (_stricmp(name, STR_0083F4F4) != 0) {
                    MixFileClass* mix = new MixFileClass(name, STR_00886980);
                    if (mix) {
                        DAT_00884DC0.AddItem(mix); // Mount retained even if append fails.
                        int length = strlen(name);
                        strncpy(filename, name, length - 3);
                        filename[length - 3] = 0;
                        strcat(filename, STR_0083F4F0);
                        filename[length] = 0;
                        file.SetFileName(filename);
                        if (file.Exists(false)) {
                            ini.FUN_00525A10(&file, false);
                            int count = ini.GetKeyCount(STR_0083F514);
                            for (int index = 0; index < count; ++index) {
                                if (ini.FUN_00528A10(STR_0083F514, ini.GetKeyName(STR_0083F514, index), STR_00889F64, section, 64) != 0) {
                                    MultiMission* mission = new MultiMission(&ini, section);
                                    if (mission) { // YRO differs: no null append.
                                        if (mission->unknown_180 != mission->unknown_184)
                                            swprintf(players, STR_0083F4DC, 0x28, mission->unknown_180,
                                                     mission->unknown_184, 0x29);
                                        else
                                            swprintf(players, STR_0083F4CC, 0x28, mission->unknown_180, 0x29);
                                        int length = wcslen(mission->unknown_000);
                                        wcscpy(display, mission->unknown_000);
                                        wcsncat(display, STR_0082083C, 44 - length);
                                        ++length;
                                        wcsncat(display, players, 44 - length);
                                        mission->FUN_0069ACD0(display);
                                        unknown_690.AddItem(mission);
                                    }
                                }
                            }
                            ini.Clear(0, 0); // Only after Exists/read branch, even zero keys.
                        } else {
                            FUN_004068E0(STR_0083F498);
                        }
                    }
                }
            }
        } while (FindNextFileA(search, &found));
    }
    SetFileSearchMode(savedSearchMode);
    if (search != INVALID_HANDLE_VALUE) FindClose(search);
    ini.Clear(0, 0);
    file.Close();

    search = FindFirstFileA(STR_0083F490, &found);
    if (search != INVALID_HANDLE_VALUE) {
        do {
            if ((found.dwFileAttributes & 0x116) == 0) {
                const char* name = found.cAlternateFileName;
                if (strlen(name) == 0) name = found.cFileName;
                ini.FUN_00528A10(STR_0082BF9C, STR_00817854, STR_00829284, section, 64);
                ini.FUN_00528A10(STR_0081BFE0, STR_00831898, STR_0083F3E4, digest, 32);
                FUN_00735060(description, section, -1);
                bool official = ini.FUN_005295F0(STR_0082BF9C, STR_0083DC5C, false);
                int minimum = 2;
                int maximum = 4;
                FUN_006994F0(name, description, digest, modes, &official, &minimum, &maximum);
                MultiMission* mission = new MultiMission(name, description, digest, official,
                                                         modes, minimum, maximum);
                unknown_690.AddItem(mission); // YRM also appends null on failure.
            }
        } while (FindNextFileA(search, &found));
        FindClose(search);
    }
    // Natural file destructor followed by base INIClass destructor.
}

// FUNCTION: GAMEMD 0x69A1F0
void SessionClass::FUN_0069A1F0()
{
    for (int missionIndex = 0; missionIndex < unknown_690.Count; ++missionIndex) {
        MultiMission* mission = unknown_690.Items[missionIndex];
        if (mission != 0)
            delete mission;
    }
    unknown_690.Clear();

    for (int stringIndex = 0; stringIndex < unknown_2914.Count; ++stringIndex)
        delete[] unknown_2914.Items[stringIndex];
    unknown_2914.Clear();

    for (int phoneIndex = 0; phoneIndex < unknown_28FC.Count; ++phoneIndex) {
        PhoneEntryClass* entry = unknown_28FC.Items[phoneIndex];
        if (entry != 0)
            delete entry;
    }
    unknown_28FC.Clear();
}

// FUNCTION: GAMEMD 0x69A3B0
MultiMission::MultiMission(INIClass* ini, const char* section)
    : unknown_188(), unknown_1A4()
{
    unknown_000[0] = 0;
    unknown_058[0x103] = 0; // Native leaves filename[0] and remainder untouched.
    strcpy(unknown_15C, STR_0083F3E4);
    unknown_17C = true;
    unknown_180 = 2;
    unknown_184 = 4;
    unknown_188.Clear();
    if (!section) return;
    strcpy(unknown_058, section);
    strcat(unknown_058, STR_0082DF18);
    if (ini->Exists(section, STR_0083F648)) {
        char description[0x2C];
        ini->FUN_00528A10(section, STR_0083F648, STR_00889F64, description, 0x2C);
        FUN_00735060(unknown_000, description, -1);
    } else {
        ini->FUN_00529160(section, STR_0081B1A4, unknown_000, 0x2C);
    }
    unknown_180 = ini->FUN_005276D0(section, STR_0083F3FC, unknown_180);
    unknown_184 = ini->FUN_005276D0(section, STR_0083F3F0, unknown_184);
    char disks[128];
    {
        if (ini->FUN_00528A10(section, STR_0081B1D4, STR_00889F64, disks, 128) != 0) {
            char* token = strtok(disks, STR_00817F70);
            while (token != 0 && *token != 0) {
                unknown_188.AddItem(static_cast<DiskID>(atoi(token)));
                token = strtok(0, STR_00817F70);
            }
        }
    }
    Wstring list;
    bool haveModes;
    {
        // Preserve construction fallback,key,section; destruction in reverse
        // before testing the result. Do not merge argument temporaries.
        Wstring fallback(STR_00889F64);
        Wstring key(STR_0083EFD0);
        Wstring sectionText(section);
        haveModes = ini->FUN_00528C00(&sectionText, &key, &fallback, &list) > 0;
    }
    if (haveModes) {
        Wstring token;
        int cursor = list.FUN_007B5F10(0, STR_00817F70, &token);
        while (cursor != -1) {
            {
                Wstring leftTrim(STR_00830A14);
                token.FUN_007B51D0(&leftTrim);
            }
            {
                Wstring rightTrim(STR_00830A14);
                token.FUN_007B5230(&rightTrim);
            }
            unknown_1A4.AddItem(token);
            cursor = list.FUN_007B5F10(cursor, STR_00817F70, &token);
        }
    }
    {
        CCFileClass file(unknown_058);
        if (!file.Exists(false)) {
            FUN_004068E0(STR_0083F608, unknown_058);
        } else if (file.Open(1)) {
            file.Seek(-100, 2);
            char footer[128];
            memset(footer, 0, sizeof(footer)); // Native clears32 full dwords, then reads100.
            file.ReadBytes(footer, 100);
            file.Close();
            if (strstr(footer, STR_0083F440)) {
                CCINIClass digestIni;
                BufferStraw digestStream(footer, 100);
                digestIni.FUN_00474320(&digestStream, false, false);
                digestIni.FUN_00528A10(STR_0081BFE0, STR_00831898, 0, footer, 128);
                FUN_0069AD80(footer);
            }
        }
    }
    // Natural teardown: inner straw then INI, then file, then list.
}

// FUNCTION: GAMEMD 0x69A980
MultiMission::MultiMission(const char* filename, const wchar_t* description,
                           const char* digest, bool flag, const char* modeList,
                           int value180, int value184)
    : unknown_188(), unknown_1A4()
{
    if (filename) {
        strncpy(unknown_058, filename, 0x104);
        unknown_058[0x103] = 0;
    } else {
        strcpy(unknown_058, STR_0083F658);
    }
    if (description) {
        wcsncpy(unknown_000, description, 0x2C);
        unknown_000[0x2B] = 0;
    } else {
        wcscpy(unknown_000, FUN_00734E60(STR_0083F4B8, 0, STR_0083EEB8, 0xB1D));
    }
    if (digest) {
        strncpy(unknown_15C, digest, 0x20);
        unknown_15C[0x1F] = 0;
    } else {
        strcpy(unknown_15C, STR_0083F3E4);
    }
    unknown_180 = value180;
    unknown_17C = flag;
    unknown_184 = value184;
    unknown_188.Clear();
    unknown_188.AddItem(static_cast<DiskID>(-2));

    if (modeList) {
        Wstring list(modeList);
        if (list.Length() != 0) {
            Wstring token;
            int cursor = list.FUN_007B5F10(0, STR_00817F70, &token);
            while (cursor != -1) {
                // Two separate natural RAII lifetimes. Native destroys left
                // trim argument BEFORE constructing the right trim argument.
                {
                    Wstring leftTrim(STR_00830A14);
                    token.FUN_007B51D0(&leftTrim);
                }
                {
                    Wstring rightTrim(STR_00830A14);
                    token.FUN_007B5230(&rightTrim);
                }
                unknown_1A4.AddItem(token);
                cursor = list.FUN_007B5F10(cursor, STR_00817F70, &token);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x69AC30
bool MultiMission::FUN_0069AC30(int value)
{
    if (value == -2) {
        return RawFileClass(unknown_058).Exists(false);
    }
    // Use the counted-vector implementation directly: native has no virtual search call.
    if (unknown_188.DynamicVectorClass<DiskID>::FindItemIndex(static_cast<DiskID>(-1)) != -1)
        return true;
    return unknown_188.DynamicVectorClass<DiskID>::FindItemIndex(static_cast<DiskID>(value)) != -1;
}

// FUNCTION: GAMEMD 0x69ACD0
void MultiMission::FUN_0069ACD0(const wchar_t* source)
{
    if (source) {
        wcsncpy(unknown_000, source, 0x2C);
        unknown_000[0x2B] = 0;
    } else {
        wcscpy(unknown_000, FUN_00734E60(STR_0083F4B8, 0, STR_0083EEB8, 0xB1D));
    }
}

// FUNCTION: GAMEMD 0x69AD20
void MultiMission::FUN_0069AD20(const char* source)
{
    if (source) {
        strncpy(unknown_058, source, 0x104);
        unknown_058[0x103] = 0;
    } else {
        strcpy(unknown_058, STR_0083F658);
    }
}

// FUNCTION: GAMEMD 0x69AD80
void MultiMission::FUN_0069AD80(const char* source)
{
    if (source) {
        strncpy(unknown_15C, source, 0x20);
        unknown_15C[0x1F] = 0;
    } else {
        strcpy(unknown_15C, STR_0083F3E4);
    }
}

// FUNCTION: GAMEMD 0x69ADF0
bool MultiMission::FUN_0069ADF0()
{
    return _stricmp(unknown_058, STR_0082BC30) == 0;
}

// FUNCTION: GAMEMD 0x69AE70
bool SessionClass::FUN_0069AE70()
{
    return _stricmp(unknown_6A8,
        // STRING: GAMEMD 0x0082BC30
        "RandMap.Sed") == 0;
}

extern const char STR_0083F668[]; // STRING: GAMEMD 0x83F668 (decl; reloc)

// FUNCTION: GAMEMD 0x69AE10
bool MultiMission::FUN_0069AE10(Wstring* mode)
{
    if (unknown_1A4.Count == 0) {
        return mode->FUN_007B4710(STR_0083F668);
    }
    for (int index = 0; index < unknown_1A4.Count; ++index) {
        if (*mode == unknown_1A4.Items[index]) {
            return true;
        }
    }
    return false;
}

#include <windows.h>
#include "../_layout/audio_0048d080.h"
#include "../_layout/elapsed_timer.h"
#include "../platform/input_manager_class_methods.h"
#include "null_modem_class_methods.h"
#include "command_packet_layouts.h"
// Declaration: GAMEMD 0x48D080 -- no arguments, cdecl shared pump.
void __cdecl Unsorted_CallBack();
extern unsigned char DAT_00A8ED6B; // GLOBAL: GAMEMD 0xA8ED6B (decl; reloc)
extern const char STR_0083F674[]; // STRING: GAMEMD 0x83F674 (decl; reloc)

// FUNCTION: GAMEMD 0x69AE90
void SessionClass::FUN_0069AE90(int progress)
{
    if (DAT_00A8ED6B) return;
    int adjusted = progress;
    if (ScenarioInstance->unknown_34BD) adjusted /= 2;
    double requested = adjusted;
    if (DAT_00AC4F58.FUN_00643E90(0) * 100.0 < requested)
        DAT_00AC4F58.FUN_00643C50(0, requested, -1, -1);
    if (unknown_283C.Count == 1) return;

    // Canonical timer constructor calls GameClockClass::GetTime on its
    // empty embedded clock; do not replace with a free clock function.
    ScenarioElapsedTimer timer(240);
    switch (GameMode) {
    case 1:
    case 2: {
        Payload_0069B08C packet;
        memset(&packet, 0, sizeof(packet));
        packet.unknown_00 = 0x6C;
        packet.unknown_19 = DAT_00AC4F58.FUN_00643E90(0) * 100.0;
        packet.unknown_18 = Session_00A8B238.unknown_28F8;
        DAT_00A8EA70.FUN_005F1BF0(&packet, 250, 0);
        DAT_00A8EA70.NullModemClass::Service();
        while (DAT_00A8EA70.FUN_005F1EA0() > 5) {
            if (timer.GetTimeLeft() <= 0) break;
            Sleep(20);
            DAT_0087F770->FUN_0054F000();
            DAT_00A8EA70.NullModemClass::Service();
        }
        break;
    }
    case 3:
    case 4: {
        Payload_0069AF45 packet;
        memset(&packet, 0, sizeof(packet));
        packet.unknown_00 = 15;
        packet.unknown_2F = DAT_00AC4F58.FUN_00643E90(0) * 100.0;
        // This is the GLOBAL Session vector, not necessarily this receiver's
        // vector. Its first element is dereferenced without count/null guard.
        strcpy(packet.unknown_04,
               NarrowName_007350C0(Session_00A8B238.unknown_283C.Items[0]->Name));
        if (packet.unknown_2F < 99.95) {
            Manager_00A8E9C0.FUN_005410F0(&packet, 51, 0, 0, 0, 0);
        } else {
            for (int index = 1; index < Session_00A8B238.unknown_283C.Count; ++index) {
                FUN_004068E0(STR_0083F674);
                // Pointer/global array reload occurs after logging callback.
                Manager_00A8E9C0.FUN_00541260(&packet, 51, 1,
                    Session_00A8B238.unknown_283C.Items[index]->Name);
            }
        }
        Unsorted_CallBack();
        while (Manager_00A8E9C0.IPXManagerClass::vf_7() > 5) {
            if (timer.GetTimeLeft() <= 0) break;
            Sleep(20);
            FUN_005D4D50();
            Unsorted_CallBack();
        }
        break;
    }
    default:
        break;
    }
    // Exactly one terminal pump after any mode switch path, including invalid
    // modes. Early A8ED6B/Count==1 guards return before timer and terminal pump.
    Unsorted_CallBack();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0069B540
void GameModeOptionsClass_Opt::Clear()
{
    AIPlayers = 0;
    for (int i = 0; i < 8; i++) {
        unknown_4C[i] = -1;
        unknown_6C[i] = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69B560
bool GameModeOptionsClass_Opt::FUN_0069B560(IStream* stream)
{
    if (stream) {
        unsigned long length = 300;
        if (stream->Write(&length, 4, 0) >= 0 &&
            stream->Write(this, length, 0) >= 0)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x69B5B0
bool GameModeOptionsClass_Opt::FUN_0069B5B0(IStream* stream)
{
    if (stream) {
        unsigned long length;
        if (stream->Read(&length, 4, 0) >= 0 && length == 300) {
            HRESULT result = stream->Read(this, 300, 0);
            // Native writes the sentinel even when the second Read fails.
            unknown_04 = -1;
            if (result >= 0)
                return true;
        }
    }
    return false;
}

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
        NodeNameType* player = unknown_283C.Items[i];
        int current = player->unknown_57 == -2 && player->unknown_53 == -1
            ? -2 : player->unknown_53;
        if (current == value)
            return true;
    }
    for (int j = 0; j < 8; ++j) {
        if (unknown_18.unknown_6C[j] == value)
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
        NodeNameType* player = Players_00A8DA78[i];
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
        FUN_004068E0(STR_0083F6E8, i, NarrowName_007350C0(player->Name),
            player->unknown_4F == -2 ? -2 : player->unknown_4B,
            player->unknown_57 == -2 ? -2 : player->unknown_53);
    }
    for (int slot = 0; slot < 8; ++slot) {
        if (Session_00A8B238.unknown_18.unknown_4C[slot] == -2) {
            if (unknown_04)
                Session_00A8B238.unknown_18.unknown_4C[slot] = unknown_04->vf_28();
            else
                Session_00A8B238.unknown_18.unknown_4C[slot] =
                    DAT_00A8B230->unknown_0218.RandomRanged(0, 9);
        }
        if (Session_00A8B238.unknown_18.unknown_6C[slot] == -2) {
            int value;
            bool used;
            do {
                value = DAT_00A8B230->unknown_0218.RandomRanged(0, 7);
                used = false;
                if (value != -2) {
                    for (int i = 0; i < PlayerCount_00A8DA84; ++i) {
                        NodeNameType* player = Players_00A8DA78[i];
                        int current = player->unknown_57 == -2 &&
                            player->unknown_53 == -1 ? -2 : player->unknown_53;
                        if (current == value) {
                            used = true;
                            break;
                        }
                    }
                    if (!used) {
                        for (int i = 0; i < 8; ++i) {
                            if (Session_00A8B238.unknown_18.unknown_6C[i] == value) {
                                used = true;
                                break;
                            }
                        }
                    }
                }
            } while (used);
            Session_00A8B238.unknown_18.unknown_6C[slot] = value;
        }
        FUN_004068E0(STR_0083F6C8, slot, Session_00A8B238.unknown_18.unknown_4C[slot],
            Session_00A8B238.unknown_18.unknown_6C[slot]);
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
            DAT_0083ED20 = DAT_00A8EB60.GameSpeed;
        }
        if (this->GameMode == 0) {
            DAT_00A8EB60.GameSpeed = 2;
        }
        if (DAT_00A8B230->unknown_35A2 == 0) {
            FUN_00684240();
            DAT_00B07784 = CurrentFrame + 3;
        }
        if (!WWMouseClassInstance->IsCaptured()) {
            WWMouseClassInstance->CaptureMouse();
        }
        FUN_00407150(&DAT_0087E758->First, 0x4000);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x69BB40
void SessionClass::FUN_0069BB40()
{
    if (InGameFrameActive == 0)
        return;
    InGameFrameActive = 0;
    if (DAT_0083ED20 != -1) {
        DAT_00A8EB60.GameSpeed = DAT_0083ED20;
        DAT_0083ED20 = -1;
    }
    FUN_00532130();
    FUN_005BF450();
    FUN_00406E80();
    FUN_00750FA0();
    FUN_007535D0();
    FUN_00752CA0();
    FUN_00407150(&DAT_0087E758->First, 0x4000);
    if (ToolTipManager_Instance)
        ToolTipManager_Instance->SetState(false);
    if (WWMouseClassInstance->IsCaptured())
        WWMouseClassInstance->vf_5();
    WWMouseClassInstance->vf_3();
    DAT_00B07784 = 0;
}

// FUNCTION: GAMEMD 0x0069BBE0
bool SessionClass::FUN_0069BBE0()
{
    return InGameFrameActive;
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
        if (Players_00A8DA78[index]->unknown_6F == id)
            return unknown_307A[index];
    }
    return 0;
}

// GLOBAL: GAMEMD 0xA8DA90
extern NodeNameType* SlotPlayers_00A8DA90[8];
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
        NodeNameType* selected = SlotPlayers_00A8DA90[slot];
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
        NodeNameType* selected = SlotPlayers_00A8DA90[slot];
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

// FUNCTION: GAMEMD 0x0069BD60
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
            const char* name = NarrowName_007350C0(unknown_283C.Items[i]->Name);
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
        ordered.AddItem(unknown_283C.Items[smallest]);
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
            FUN_004068E0(STR_0083F760, NarrowName_007350C0(unknown_283C.Items[other]->Name));
            for (int candidate = 0; candidate < 8; ++candidate) {
                const char* otherName = NarrowName_007350C0(unknown_283C.Items[other]->Name);
                const char* candidateName = NarrowName_007350C0(unknown_2858[candidate]->Name);
                if (_stricmp(otherName, candidateName) == 0) {
                    NodeAddressType node;
                    unknown_2994[candidate].FUN_0053EDC0(&node);
                    unknown_283C.Items[other]->Address.FUN_0053ED20(
                        0, &node, unknown_283C.Items[other]->Address.Port);
                    const char* name = NarrowName_007350C0(unknown_283C.Items[other]->Name);
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
// FUNCTION: GAMEMD 0x69D870
// VectorClass<HouseClass*>::VectorClass(int, HouseClass**)
template class VectorClass<HouseClass*>;

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

// FUNCTION: GAMEMD 0x69DCF0
ShapeButtonClass::ShapeButtonClass()
    : ToggleClass(0, 0, 0, 0, 0),
      IsToFlash(false), FlashDelay(0), FlashCounter(0), HasFrames(0),
      OffsetX(0), OffsetY(0), UsesSidebarSurface(0), Convert(DAT_0087F6C4),
      unknown_55(0), IsShapeLoaded(false)
{
    // Native leaves ShapeData+58, unknown54 and every padding byte untouched.
}

// FUNCTION: GAMEMD 0x69DD30
ShapeButtonClass::ShapeButtonClass(int id, const void* shape, int x, int y,
                                   int width, int height, int flags)
    : ToggleClass(id, x, y, 0, 0),
      IsToFlash(false), FlashDelay(0), HasFrames(0),
      OffsetX(0), OffsetY(0), UsesSidebarSurface(0), Convert(DAT_0087F6C4),
      unknown_55(flags), IsShapeLoaded(false)
{
    // FlashCounter+3C deliberately omitted: parameterized native never writes
    // it. ShapeData assigned in body after generated most-derived vptr store.
    // Native 0x69DD7E stores this opaque argument as the shape pointer;
    // 0x69DD83/8A read its signed words at +2/+4. Recover that format here.
    ShapeData = const_cast<ShapeHeader*>(static_cast<const ShapeHeader*>(shape));
    if (ShapeData) {
        // Native MOVSX from signed16-bit fields+2/+4, not unsigned dimensions.
        Width = ShapeData->Width;
        Height = ShapeData->Height;
    } else {
        Width = 0;
        Height = 0;
    }
    if (width != 0) Width = width;
    if (height != 0) Height = height;
}
