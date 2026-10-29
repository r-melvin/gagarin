// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Op /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Ion.cpp. The name is the source-file string at 0x828034
//   in retail gamemd.exe v1.001, passed by the assert at 0x53a062 inside this object's
//   code range (0x539350-0x53c81f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
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

#include <math.h>
#pragma intrinsic(pow)
#include "lightning_storm_methods.h"

#include "../core/techno_class_mindcontrol_query_methods.h"

#include "../core/trivial_tu104_methods.h"

#include <windows.h>
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
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
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

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA9FA78
extern int DAT_00A9FA78;
// GLOBAL: GAMEMD 0xA9FA7C
extern int DAT_00A9FA7C;
// GLOBAL: GAMEMD 0xA9FA80
extern int DAT_00A9FA80;


// Raw PBVAnimClass RTTI identifies const pointer elements and the
// DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// No TypeList or constructor address is claimed. Original TU boundaries,
// final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"
class AnimClass;

// VTABLE: GAMEMD 0x7EBFEC -- VectorClass<const AnimClass*>.
template class VectorClass<const AnimClass*>;
typedef VectorClass<const AnimClass*> GgAnimVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EBFCC -- DynamicVectorClass<const AnimClass*>.
template class DynamicVectorClass<const AnimClass*>;
typedef DynamicVectorClass<const AnimClass*> GgAnimDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const AnimClass*) == 4);

// Declaration: GAMEMD 0x4CAC40 -- engine helper, stacked double/ST0 result.
double __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0xA9FA00
extern double DAT_00A9FA00;

// GLOBAL: GAMEMD 0xA9FA88
extern double DAT_00A9FA88;

// GLOBAL: GAMEMD 0xA9FA58
extern double DAT_00A9FA58;

// SYNTHETIC: GAMEMD 0x00539560
// GLOBAL: GAMEMD 0x00A9F9CC
int DAT_00A9F9CC = DAT_00A9F9F8;

// SYNTHETIC: GAMEMD 0x00539570
// GLOBAL: GAMEMD 0x00A9FA48
int DAT_00A9FA48 = DAT_00A9F9F8;

// FUNCTION: GAMEMD 0x539EA0
// Stores to a global.
void FUN_00539EA0(int a1)
{
    DAT_00A9FAB4 = a1;
}


// GLOBAL: GAMEMD 0xA9F9F8
extern int DAT_00A9F9F8;
// GLOBAL: GAMEMD 0xA9FAB4
extern unsigned char DAT_00A9FAB4;
// GLOBAL: GAMEMD 0xA9FACC
extern int DAT_00A9FACC;
// GLOBAL: GAMEMD 0xA9FAD0
extern unsigned char DAT_00A9FAD0;

// FUNCTION: GAMEMD 0x53C280 (decl; reloc)
void FUN_0053C280(unsigned char, int);


// FUNCTION: GAMEMD 0x53A090
unsigned char __cdecl FUN_0053A090();
// FUNCTION: GAMEMD 0x53A0B0
void FUN_0053A0B0(int a1, int a2);

// FUNCTION: GAMEMD 0x53A090
// Branching.
unsigned char __cdecl FUN_0053A090()
{
    if (DAT_00A9FAB4 != 0)
    {
        DAT_00A9FAD0 = 1;
    }
    return DAT_00A9FAB4;
}

// FUNCTION: GAMEMD 0x53A0B0
// Branching.
void FUN_0053A0B0(int a1, int a2)
{
    if (DAT_00A9FAB4 != (unsigned char)0)
    {
        unsigned char t1 = DAT_00A9FAB4;
        DAT_00A9FAB4 = 0;
        DAT_00A9FACC = 0;
        DAT_00A9F9CC = DAT_00A9F9F8;
        FUN_0053C280(t1, a2);
    }
}

// FUNCTION: GAMEMD 0x53A110
// Returns a comparison result.
bool __cdecl FUN_0053A110()
{
    return DAT_00A9FABC == 1;
}

// FUNCTION: GAMEMD 0x53A120
// Returns a comparison result.
bool __cdecl FUN_0053A120()
{
    return DAT_00A9FABC == 2;
}

// FUNCTION: GAMEMD 0x53AB50  LightningStorm::Init (__fastcall, static)
// Re-light the map for the storm, then raise the local player's flag. The
// lighting call takes no arguments, so retail issues it before touching the
// global at all.
void LightningStorm::Init()
{
    ScenarioClass::UpdateLighting();
    CurrentPlayer->RecheckRadar = true;
}

// FUNCTION: GAMEMD 0x53B3F0
// Empty function.
void __cdecl FUN_0053B3F0()
{
}

// FUNCTION: GAMEMD 0x53B400
// Returns a comparison result.
bool __cdecl FUN_0053B400()
{
    return (DAT_00A9FAC0 != 0) ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0053BAD0
int FUN_0053BAD0()
{
    return DAT_00A9FAB0 != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0053BAE0
int FUN_0053BAE0()
{
    return DAT_00A9FAB0 != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x53C450  TechnoClass::CanBePermaMindControlled (__thiscall)
// A chain of disqualifiers, each returning early — which is why retail carries
// five separate `XOR AL,AL; POP ESI; RET` epilogues rather than one shared exit.
// It opens by testing `this` itself, so retail expects to be called on a
// possibly-null pointer.
//
// The final disqualifier is written as a branch, not a negation. `return !x;`,
// `x == 0` and `x == false` all compile to the full-width bool idiom
// `NEG AL; SBB EAX,EAX; INC EAX` regardless of whether the slot is typed bool,
// unsigned char or int — a standalone probe confirmed all six combinations.
// Writing it as a branch instead (`if (x) return false; return true;`, or the
// equivalent ternary) gives retail's `TEST AL,AL; SETE AL`. That is the whole
// difference between the earlier 91.8% and byte parity here.
bool TechnoClass::CanBePermaMindControlled()
{
    if (this == 0)
        return false;

    if (TECHNO_WHAT_AM_I(this) == ABS_BUILDING)
        return false;

    if (TECHNO_GET_TYPE(this)->unknown_D35)
        return false;

    if (TECHNO_SLOT_160(this))
        return false;

    if (TECHNO_GET_TYPE(this)->unknown_D6A)
        return false;

    if (TECHNO_SLOT_54(this))
        return false;

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x53C4C0
// DynamicVectorClass<const AnimClass*>::Clear

// FUNCTION: GAMEMD 0x53C4F0
// DynamicVectorClass<const AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x53C510
// VectorClass<const AnimClass*>::Slot6

// FUNCTION: GAMEMD 0x53C520
// VectorClass<const AnimClass*>::operator==

// FUNCTION: GAMEMD 0x53C560
// VectorClass<const AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53C610
// VectorClass<const AnimClass*>::Clear

// FUNCTION: GAMEMD 0x53C640
// VectorClass<const AnimClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x53C680
// VectorClass<const AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x53C6A0
// DynamicVectorClass<const AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53C750
// DynamicVectorClass<const AnimClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x53C780
// VectorClass<const AnimClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x53C7D0
// DynamicVectorClass<const AnimClass*>::scalar deleting destructor
