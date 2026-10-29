// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every vtable constant and member displacement below read numerically off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI, from the
//   `MOV dword ptr [EAX],imm32` and `MOV [EAX+n],reg` stores of the function at
//   each annotated address. None of these classes is bound by YRpp,
//   so all keep Ghidra placeholder names.
//
// Shape: constructors whose whole body is "seat the vtable and return this",
//   optionally copying one or two arguments into the first members first. The
//   VC6 emission order — base constructors, member initializers, vptr seat,
//   constructor body — is what puts the `MOV dword ptr [EAX],vtable` last in
//   every one of them, so the members are written as member initializers, not
//   as body assignments.
//
// Five sub-shapes, the last seating a null first word instead of a vtable:
//   `MOV EAX,ECX; MOV [EAX],vtbl; RET`                        no arguments
//   `MOV EAX,ECX; MOV [EAX],vtbl; RET 4`                      one ignored argument
//   `MOV EAX,ECX; MOV [EAX+4],arg; MOV [EAX],vtbl; RET 4`     one stored argument
//   `... MOV [EAX+4],a; MOV [EAX+8],b; MOV [EAX],vtbl; RET 8` two stored
//   `MOV EAX,ECX; MOV dword ptr [EAX],0; RET`                 null first word
#ifndef GG_MATCH_CORE_VTABLE_SEATING_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VTABLE_SEATING_CTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Sub-shape 1: a polymorphic class whose default constructor only seats its
// vtable. Nothing but the vptr is touched, so nothing but the vptr is modelled.
#define GG_SEAT0_DECL(TAG)                                                \
class Seat0_##TAG                                                         \
{                                                                         \
public:                                                                   \
    Seat0_##TAG();                                                        \
    virtual ~Seat0_##TAG();                                               \
    virtual void Slot1();                                                 \
}

#define GG_SEAT0_BODY(TAG) Seat0_##TAG::Seat0_##TAG() {}

// Sub-shape 2: the same, with one argument the constructor never uses.
#define GG_SEAT0A_DECL(TAG)                                               \
class Seat0A_##TAG                                                        \
{                                                                         \
public:                                                                   \
    Seat0A_##TAG(int unused);                                             \
    virtual ~Seat0A_##TAG();                                              \
    virtual void Slot1();                                                 \
}

#define GG_SEAT0A_BODY(TAG) Seat0A_##TAG::Seat0A_##TAG(int) {}

// Sub-shape 3: one argument stored at +0x04, then the vtable.
#define GG_SEAT1_DECL(TAG)                                                \
class Seat1_##TAG                                                         \
{                                                                         \
public:                                                                   \
    Seat1_##TAG(int a);                                                   \
    virtual ~Seat1_##TAG();                                               \
    virtual void Slot1();                                                 \
    int unknown_04;                                                       \
}

#define GG_SEAT1_BODY(TAG) Seat1_##TAG::Seat1_##TAG(int a) : unknown_04(a) {}

// Sub-shape 4: two arguments stored at +0x04 and +0x08, then the vtable.
#define GG_SEAT2_DECL(TAG)                                                \
class Seat2_##TAG                                                         \
{                                                                         \
public:                                                                   \
    Seat2_##TAG(int a, int b);                                            \
    virtual ~Seat2_##TAG();                                               \
    virtual void Slot1();                                                 \
    int unknown_04;                                                       \
    int unknown_08;                                                       \
}

#define GG_SEAT2_BODY(TAG)                                                \
    Seat2_##TAG::Seat2_##TAG(int a, int b) : unknown_04(a), unknown_08(b) {}

// Sub-shape 5: a non-polymorphic class whose constructor nulls its first word.
// The stored constant is literal zero, not a relocated vtable address, so this
// carries no VTABLE annotation.
#define GG_SEATNULL_DECL(TAG)                                             \
class SeatNull_##TAG                                                      \
{                                                                         \
public:                                                                   \
    SeatNull_##TAG();                                                     \
    int unknown_00;                                                       \
}

#define GG_SEATNULL_BODY(TAG) SeatNull_##TAG::SeatNull_##TAG() : unknown_00(0) {}

// VTABLE: GAMEMD 0x007F0DCC
GG_SEAT0A_DECL(007F0DCC);
GG_STATIC_ASSERT(sizeof(Seat0A_007F0DCC) == 0x4);

// VTABLE: GAMEMD 0x007E4E78
GG_SEAT0A_DECL(007E4E78);
GG_STATIC_ASSERT(sizeof(Seat0A_007E4E78) == 0x4);

// VTABLE: GAMEMD 0x007EAA28
GG_SEAT0A_DECL(007EAA28);
GG_STATIC_ASSERT(sizeof(Seat0A_007EAA28) == 0x4);

// VTABLE: GAMEMD 0x007EB714
GG_SEAT0A_DECL(007EB714);
GG_STATIC_ASSERT(sizeof(Seat0A_007EB714) == 0x4);

// VTABLE: GAMEMD 0x007F0D3C
GG_SEAT0A_DECL(007F0D3C);
GG_STATIC_ASSERT(sizeof(Seat0A_007F0D3C) == 0x4);

// VTABLE: GAMEMD 0x007E4DD8
GG_SEAT0A_DECL(007E4DD8);
GG_STATIC_ASSERT(sizeof(Seat0A_007E4DD8) == 0x4);

// VTABLE: GAMEMD 0x007F72C4
GG_SEAT2_DECL(007F72C4);
GG_STATIC_ASSERT(offsetof(Seat2_007F72C4, unknown_04) == 0x4 &&
                 offsetof(Seat2_007F72C4, unknown_08) == 0x8 &&
                 sizeof(Seat2_007F72C4) == 0xC);

// VTABLE: GAMEMD 0x007F72D8
GG_SEAT2_DECL(007F72D8);
GG_STATIC_ASSERT(offsetof(Seat2_007F72D8, unknown_04) == 0x4 &&
                 offsetof(Seat2_007F72D8, unknown_08) == 0x8 &&
                 sizeof(Seat2_007F72D8) == 0xC);

class CCINIClass;
// Existing four-byte prefix, extended only with calls observed at 0x687DF3.
class SeatNull_006406E0
{
public:
    SeatNull_006406E0();
    ~SeatNull_006406E0(); // GAMEMD 0x6406F0
    void FUN_00641140(); // GAMEMD 0x641140
    void FUN_006418B0(CCINIClass* ini); // GAMEMD 0x6418B0
    int unknown_00;
};
GG_STATIC_ASSERT(offsetof(SeatNull_006406E0, unknown_00) == 0x0 &&
                 sizeof(SeatNull_006406E0) == 0x4);

GG_SEATNULL_DECL(0074FF30);
GG_STATIC_ASSERT(offsetof(SeatNull_0074FF30, unknown_00) == 0x0 &&
                 sizeof(SeatNull_0074FF30) == 0x4);

// Address -> class map. A constructor cannot be redeclared at namespace scope,
// so the reccmp `// FUNCTION:` annotations live on the bodies in the .cpp; this
// is the index.
//   0x006406E0  ->  SeatNull_006406E0
//   0x00717BC0  ->  Seat0A_007F0DCC
//   0x00717BD0  ->  Seat0A_007E4E78
//   0x00717BE0  ->  Seat0A_007EAA28
//   0x00717BF0  ->  Seat0A_007EB714
//   0x0074FF30  ->  SeatNull_0074FF30
//   0x0075E690  ->  Seat0A_007F0D3C
//   0x0075E6A0  ->  Seat0A_007E4DD8
//   0x0076F090  ->  Seat2_007F72C4
//   0x0076F0C0  ->  Seat2_007F72D8

#endif  // GG_MATCH_CORE_VTABLE_SEATING_CTOR_FAMILY_METHODS_H
