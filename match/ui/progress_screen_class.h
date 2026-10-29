// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (reconfirmed here).
//
// ProgressScreenClass — the load/progress screen. Only the PlayerSide accessor
// pair (SetSide/GetSide) is modelled in this TU; the full layout is P2.
#ifndef GG_MATCH_UI_PROGRESS_SCREEN_CLASS_H
#define GG_MATCH_UI_PROGRESS_SCREEN_CLASS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// ProgressScreenClass
//
// SetSide @0x642B10:  MOV EAX,[ESP+4]; MOV [ECX+0x80],EAX; RET 4
// GetSide @0x642B20:  MOV EAX,[ECX+0x80]; RET
// Both touch only the single dword at +0x80 (YRpp: `PlayerSide`). The base is
// padded to 0x80; the full member set is P2.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7F0064 (RTTI .?AVProgressScreenClass@@; one slot). The
// constructors 0x6429A0 / 0x6429E0 / 0x642A30 store it at +0x00; slot 0 is
// 0x643E80 (`MOV EAX,[ESP+4]; MOV [ECX+4],EAX; RET 4`), called directly three
// times from 0x684620 with ECX = 0xAC4F58.
class ProgressScreenClass
{
public:
    virtual void Slot0(int value);  // slot 0, 0x643E80: stores +0x04

    void SetSide(int idx);        // GAMEMD 0x642B10 __thiscall
    int  GetSide();               // GAMEMD 0x642B20 __thiscall
    void Setup(int first, int second, char slotCount, int unknown);  // GAMEMD 0x642A60 __thiscall, RET 0x10

    ProgressScreenClass();        // GAMEMD 0x6429E0 (no arguments)
    // Exit-time destructor: its body is inlined into the atexit thunk 0x6429A0.
    ~ProgressScreenClass()
    {
        if (BufferOwned) {
            delete Buffer;
            BufferOwned = false;
        }
        Buffer = 0;
    }

    int  Field04;                 // +0x04, slot 0
    int  Table08[16];             // +0x08 .. +0x47, zeroed by the constructor
    int  unknown_48;              // +0x48
    int  unknown_4C;              // +0x4C
    int  unknown_50;              // +0x50
    char* Buffer;                 // +0x54, released by the destructor
    bool BufferOwned;             // +0x58
    char _pad_59[3];              // +0x59 .. +0x5B untouched here
    int  unknown_5C;              // +0x5C
    bool unknown_60;              // +0x60
    char unknown_61;              // +0x61 slot count (read with MOVSX by Setup 0x642A60)
    bool unknown_62;              // +0x62
    char _pad_63;                 // +0x63 untouched here
    int  unknown_64;              // +0x64
    int  unknown_68;              // +0x68
    int  unknown_6C;              // +0x6C
    bool unknown_70;              // +0x70
    char _pad_71[3];              // +0x71 .. +0x73 untouched here
    int  unknown_74;              // +0x74 untouched here
    int  unknown_78;              // +0x78
    int  unknown_7C;              // +0x7C
    int  PlayerSide;              // +0x80
};

GG_STATIC_ASSERT(offsetof(ProgressScreenClass, Field04) == 0x04);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, Table08) == 0x08);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, Buffer) == 0x54);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, BufferOwned) == 0x58);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_61) == 0x61);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_62) == 0x62);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, PlayerSide) == 0x80);

#endif  // GG_MATCH_UI_PROGRESS_SCREEN_CLASS_H
