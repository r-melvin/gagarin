// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Eleventh translation unit of the FlyLocomotionClass cluster: the
//   ILocomotion slot at +0x94 of the locomotor vtable 0x7E89F4, the last slot
//   of that table (0x7E8A98 already belongs to the next class). Membership is
//   settled by the vtable read, `ghidra memory read 0x7E89F4 200`.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// The displacements are interface-relative (four lower than the object's),
// because a COM slot receives the locomotor interface pointer:
//   +0x08 LinkedTo   `MOV EAX,[EBP+0x8]`, eight times
// The frame is `SUB ESP,0x30` with four callee-saved pushes and `RET 0x4`:
// the receiver only. The 0x30 of locals is exactly two 0x18-byte containers,
// at `[ESP+0x28]` and `[ESP+0x10]` off the four-push base; the flag byte the
// body computes first lives in the dead receiver's home slot.
//
// The containers are the engine's growing vector: base constructor out of
// line at 0x4D0440 (`[this+0x4]=items, [this+0x8]=capacity, [this+0xC]=1,
// [this+0xD]=allocated, [this]=0x7E192C`), then the derived part inlined -
// the vtable seated to 0x7E4F64, the count zeroed at +0x10 and the growth
// step set to ten at +0x14. `CALL [vptr+0x8]` is the virtual resize.
//
// The scanned array is the pair at 0xA8EC7C (items) / 0xA8EC88 (count), run
// backwards. Each candidate's members: +0x6C a travel counter, +0x81 and
// +0x90 two gate bytes, +0x21C its owner, +0x6C4 its type; its vtable slots
// +0x2C the type discriminant and +0x84 the type object. The type's gates are
// at +0x231, +0xC9A and +0xE0E. The owner's are +0x34 (a sub-object whose
// +0x1A6 is read) and +0x5600 (its index into the array at 0xA8022C).
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_PICK_TARGET_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_PICK_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Techno_004CFE80;

// ---------------------------------------------------------------- containers

struct DynVecVtbl_004CFE80;

// The base vector, whose constructor is called out of line and whose vtable
// the derived destructor re-seats. Modelled with the vtable as a plain member
// rather than as a real virtual base, which keeps control of exactly where
// each vtable seat is written.
struct DynVec_004CFE80
{
    DynVecVtbl_004CFE80* Vtbl;    // +0x00
    Techno_004CFE80**    Items;   // +0x04
    int                  Capacity;      // +0x08
    char                 IsInitialised; // +0x0C
    char                 IsAllocated;   // +0x0D
    int                  Count;         // +0x10
    int                  Increment;     // +0x14

    // FUNCTION: GAMEMD 0x4D0440 (decl; reloc) — the base constructor.
    void InitBase(int capacity, Techno_004CFE80** memory);

    DynVec_004CFE80(int capacity, Techno_004CFE80** memory);
    ~DynVec_004CFE80();
};

typedef char (DynVec_004CFE80::*FnResize_004CFE80)(int, Techno_004CFE80**);

struct DynVecVtbl_004CFE80
{
    char              _pad000[0x8];   // +0x0000
    FnResize_004CFE80 At_8;           // +0x0008
};
GG_STATIC_ASSERT(offsetof(DynVecVtbl_004CFE80, At_8) == 0x8);

GG_STATIC_ASSERT(offsetof(DynVec_004CFE80, Items) == 0x4 &&
                 offsetof(DynVec_004CFE80, Capacity) == 0x8 &&
                 offsetof(DynVec_004CFE80, IsInitialised) == 0xC &&
                 offsetof(DynVec_004CFE80, IsAllocated) == 0xD &&
                 offsetof(DynVec_004CFE80, Count) == 0x10 &&
                 offsetof(DynVec_004CFE80, Increment) == 0x14 &&
                 sizeof(DynVec_004CFE80) == 0x18);

// VTABLE: GAMEMD 0x7E192C — the base vector's vtable.
extern DynVecVtbl_004CFE80 VecVtable_007E192C;
// VTABLE: GAMEMD 0x7E4F64 — the growing vector's vtable.
extern DynVecVtbl_004CFE80 DynVecVtable_007E4F64;

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — the array deallocator.
void __cdecl FUN_007C8B3D(void* block);

inline DynVec_004CFE80::DynVec_004CFE80(int capacity,
                                        Techno_004CFE80** memory)
{
    InitBase(capacity, memory);
    Vtbl = &DynVecVtable_007E4F64;
    // Growth step before count: retail stores +0x14 then +0x10.
    Increment = 10;
    Count = 0;
}

inline DynVec_004CFE80::~DynVec_004CFE80()
{
    Vtbl = &VecVtable_007E192C;
    if (Items != 0 && IsAllocated != 0) {
        FUN_007C8B3D(Items);
        Items = 0;
    }
    // The allocation flag before the capacity: retail stores +0xD then +0x8.
    IsAllocated = 0;
    Capacity = 0;
}

// The append, written as a free function taking the container: retail inlined
// it, and an inlined container operation reproduces only in that shape. The
// index is captured on its own line, which is what makes cl load the count,
// copy it, increment, store back and only then load the items pointer.
inline char AddItem_004CFE80(DynVec_004CFE80& self, Techno_004CFE80* item)
{
    if (self.Count >= self.Capacity) {
        if (self.IsAllocated == 0 && self.Capacity != 0) {
            return 0;
        }
        if (self.Increment <= 0) {
            return 0;
        }
        if ((self.*self.Vtbl->At_8)(self.Capacity + self.Increment, 0) == 0) {
            return 0;
        }
    }
    int index = self.Count;
    self.Count = index + 1;
    self.Items[index] = item;
    return 1;
}

// ------------------------------------------------------------- game objects

// The owner's sub-object at +0x34; only its gate byte is read.
struct HouseSub_004CFE80
{
    char _pad000[0x1A6];   // +0x0000
    char At_1A6;           // +0x01A6
};
GG_STATIC_ASSERT(offsetof(HouseSub_004CFE80, At_1A6) == 0x1A6);

struct House_004CFE80
{
    char              _pad000[0x34];           // +0x0000
    HouseSub_004CFE80* At_34;                  // +0x0034
    char              _pad038[0x5600 - 0x38];  // +0x0038
    int               At_5600;                 // +0x5600

    // FUNCTION: GAMEMD 0x50B730 (decl; reloc) — a per-house gate.
    char FUN_0050B730();
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc) — are the two houses allied?
    char IsAlliedWith(House_004CFE80* other);
};
GG_STATIC_ASSERT(offsetof(House_004CFE80, At_34) == 0x34 &&
                 offsetof(House_004CFE80, At_5600) == 0x5600);

// GLOBAL: GAMEMD 0xA8022C — the house array the owner index selects from.
extern House_004CFE80** HouseArray_00A8022C;

struct TechnoType_004CFE80
{
    char _pad000[0x231];             // +0x0000
    char At_231;                     // +0x0231
    char _pad232[0xC9A - 0x232];     // +0x0232
    char At_C9A;                     // +0x0C9A
    char _padC9B[0xE0E - 0xC9B];     // +0x0C9B
    char At_E0E;                     // +0x0E0E
};
GG_STATIC_ASSERT(offsetof(TechnoType_004CFE80, At_231) == 0x231 &&
                 offsetof(TechnoType_004CFE80, At_C9A) == 0xC9A &&
                 offsetof(TechnoType_004CFE80, At_E0E) == 0xE0E);

struct TechnoVtbl_004CFE80;

struct Techno_004CFE80
{
    TechnoVtbl_004CFE80* Vtbl;                  // +0x0000
    char                 _pad004[0x6C - 0x4];   // +0x0004
    int                  At_6C;                 // +0x006C
    char                 _pad070[0x81 - 0x70];  // +0x0070
    char                 At_81;                 // +0x0081
    char                 _pad082[0x90 - 0x82];  // +0x0082
    char                 At_90;                 // +0x0090
    char                 _pad091[0x21C - 0x91]; // +0x0091
    House_004CFE80*      Owner;                 // +0x021C
    char                 _pad220[0x6C4 - 0x220];
    TechnoType_004CFE80* Type;                  // +0x06C4
};
GG_STATIC_ASSERT(offsetof(Techno_004CFE80, At_6C) == 0x6C &&
                 offsetof(Techno_004CFE80, At_81) == 0x81 &&
                 offsetof(Techno_004CFE80, At_90) == 0x90 &&
                 offsetof(Techno_004CFE80, Owner) == 0x21C &&
                 offsetof(Techno_004CFE80, Type) == 0x6C4);

typedef int (Techno_004CFE80::*FnInt_004CFE80)();
typedef TechnoType_004CFE80* (Techno_004CFE80::*FnType_004CFE80)();

struct TechnoVtbl_004CFE80
{
    char            _pad000[0x2C];          // +0x0000
    FnInt_004CFE80  At_2C;                  // +0x002C
    char            _pad030[0x84 - 0x30];   // +0x0030
    FnType_004CFE80 At_84;                  // +0x0084
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_004CFE80, At_2C) == 0x2C &&
                 offsetof(TechnoVtbl_004CFE80, At_84) == 0x84);

// GLOBAL: GAMEMD 0xA8EC7C — the scanned object array.
extern Techno_004CFE80** ObjectArray_00A8EC7C;
// GLOBAL: GAMEMD 0xA8EC88 — its count.
extern int ObjectCount_00A8EC88;
// GLOBAL: GAMEMD 0xA8B238 — the mode gate the whole body keys off.
extern int Mode_00A8B238;

struct RandomClass_004CFE80
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) — RandomClass::RandomRanged.
    int RandomRanged(int minval, int maxval);
};

struct ScenarioClass_004CFE80
{
    int                 Flags;                    // +0x0000
    char                _pad004[0x218 - 0x4];     // +0x0004
    RandomClass_004CFE80 RandomNumber;            // +0x0218
};
GG_STATIC_ASSERT(offsetof(ScenarioClass_004CFE80, RandomNumber) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 — the scenario object.
extern ScenarioClass_004CFE80* Scenario_00A8B230;

// ------------------------------------------------------------- the locomotor

struct Foot_004CFE80;
struct FootVtbl_004CFE80;

struct Foot_004CFE80
{
    FootVtbl_004CFE80* Vtbl;                   // +0x0000
    char               _pad004[0x21C - 0x4];   // +0x0004
    House_004CFE80*    Owner;                  // +0x021C
    char               _pad220[0x2B4 - 0x220]; // +0x0220
    int                At_2B4;                 // +0x02B4
};
GG_STATIC_ASSERT(offsetof(Foot_004CFE80, Owner) == 0x21C &&
                 offsetof(Foot_004CFE80, At_2B4) == 0x2B4);

typedef void (Foot_004CFE80::*FnAssign_004CFE80)(Techno_004CFE80*);

struct FootVtbl_004CFE80
{
    char              _pad000[0x3C8];   // +0x0000
    FnAssign_004CFE80 At_3C8;           // +0x03C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CFE80, At_3C8) == 0x3C8);

#pragma pack(push, 4)
struct FlyLocoPick
{
    void*           _vtable_locomotor;     // +0x0000  (object +0x04)
    void*           _vtable_persist;       // +0x0004  (object +0x08)
    Foot_004CFE80*  LinkedTo;              // +0x0008  (object +0x0C)

    // FUNCTION: GAMEMD 0x4CFE80
    void __stdcall PickTarget();
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(FlyLocoPick, LinkedTo) == 0x08);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_PICK_TARGET_METHODS_H
