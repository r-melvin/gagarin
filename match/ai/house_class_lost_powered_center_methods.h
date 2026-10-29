// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots and globals read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x50E0E0: on the house
//   `[EBP+0x2D8]` (the powered-centre count, DEC'd), `[EBP+0x1EC]` and
//   `[EBP+0x1ED]` (the two player-control bytes); the techno array's Count
//   and Items at `[0xA8EC88]` / `[0xA8EC7C]` (base 0xA8EC78, +0x10 / +0x04);
//   on each techno `[ESI+0x21C]` Owner, the slot `[EDX+0x84]` (GetTechnoType,
//   no arguments) and `[ESI+0x81]` InLimbo; the callee 0x70FC90
//   (TechnoClass::Deactivate, __thiscall, no arguments); the globals
//   `[0xA8E9A0]` (byte), `[0xA8B238]` (dword), `[0xA83D4C]` (HouseClass*) and
//   `[0xA8E7AC]` (dword); and the EVA call `MOV ECX,0x824E4C; OR EDX,-1;
//   PUSH -1; CALL 0x752700` (VoxClass::Play, __fastcall). Names are the YRpp
//   ones; every offset re-derived here. Owner @0x21C and
//   InLimbo @0x81 agree with match/_layout/techno_class.h (not included:
//   this TU needs the pointer-to-member vtable idiom on a locally complete
//   type).
#ifndef GG_MATCH_AI_HOUSE_CLASS_LOST_POWERED_CENTER_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_LOST_POWERED_CENTER_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Type_0050E0E0;
struct House_0050E0E0;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct TechnoVtbl_0050E0E0;

// TechnoClass as seen from this call site.
struct Techno_0050E0E0
{
    TechnoVtbl_0050E0E0* Vtbl;              // +0x0000
    char                 _pad004[0x81 - 0x4];
    unsigned char        InLimbo;           // +0x0081
    char                 _pad082[0x21C - 0x82];
    House_0050E0E0*      Owner;             // +0x021C

    // FUNCTION: GAMEMD 0x70FC90 (decl; reloc) — TechnoClass::Deactivate.
    void Deactivate();
};
GG_STATIC_ASSERT(offsetof(Techno_0050E0E0, InLimbo) == 0x81);
GG_STATIC_ASSERT(offsetof(Techno_0050E0E0, Owner)   == 0x21C);

typedef Type_0050E0E0* (Techno_0050E0E0::*Fn84_0050E0E0)();

// A cell as two shorts, copied as one dword (slot 0x1B8 returns it through a hidden pointer).
struct TechnoCell_0050E0E0
{
    short X;
    short Y;
};
typedef TechnoCell_0050E0E0* (Techno_0050E0E0::*Fn1B8_0050E0E0)(TechnoCell_0050E0E0* out);

struct TechnoVtbl_0050E0E0
{
    char           _pad000[0x84];      // +0x0000
    Fn84_0050E0E0  GetTechnoType;      // +0x0084
    char           _pad088[0x1B8 - 0x88];
    Fn1B8_0050E0E0 GetCell;            // +0x01B8
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0050E0E0, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0050E0E0, GetCell) == 0x1B8);

// DynamicVectorClass<TechnoClass*> — only Items and Count are read.
struct TechnoVector_0050E0E0
{
    void*              Vtable;        // +0x0000
    Techno_0050E0E0**  Items;         // +0x0004
    char               _pad008[0x8];  // +0x0008
    int                Count;         // +0x0010
};
GG_STATIC_ASSERT(offsetof(TechnoVector_0050E0E0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TechnoVector_0050E0E0, Count) == 0x10);

// GLOBAL: GAMEMD 0xA8EC78 — TechnoClass::Array.
extern TechnoVector_0050E0E0 DAT_00A8EC78;
// GLOBAL: GAMEMD 0xA8E9A0 — Unsorted::IsActive (byte).
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_0050E0E0* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8E7AC — dword; nonzero suppresses the EVA line.
extern int DAT_00A8E7AC;
// STRING: GAMEMD 0x824E4C  "EVA_RobotTanksOffline"
extern const char STR_00824E4C[];

struct Vox_0050E0E0
{
    // FUNCTION: GAMEMD 0x752700 (decl; reloc) — VoxClass::Play.
    static void Play(const char* name, int a, int b);
};

struct House_0050E0E0
{
    char           _pad000[0x1EC];          // +0x0000
    unsigned char  IsHumanPlayer;           // +0x01EC
    unsigned char  IsInPlayerControl;       // +0x01ED
    char           _pad1EE[0x2D8 - 0x1EE];  // +0x01EE
    int            PoweredCenterCount;      // +0x02D8

    // HouseClass::IsControlledByCurrentPlayer (0x50B6F0), inlined by retail
    // at 0x50E15C..0x50E186 in exactly this shape: the campaign arm tests the
    // two bytes by branches, the other arm materialises the pointer compare
    // as a bool (`SETZ AL; TEST AL,AL`).
    bool IsControlledByCurrentPlayer()
    {
        if (Session_00A8B238.GameMode == 0) {
            return this->IsHumanPlayer || this->IsInPlayerControl;
        }
        return this == DAT_00A83D4C;
    }

    // FUNCTION: GAMEMD 0x50E0E0
    void LostPoweredCenter(Type_0050E0E0* type);
};
GG_STATIC_ASSERT(offsetof(House_0050E0E0, IsHumanPlayer)      == 0x1EC);
GG_STATIC_ASSERT(offsetof(House_0050E0E0, IsInPlayerControl)  == 0x1ED);
GG_STATIC_ASSERT(offsetof(House_0050E0E0, PoweredCenterCount) == 0x2D8);

#endif  // GG_MATCH_AI_HOUSE_CLASS_LOST_POWERED_CENTER_METHODS_H
