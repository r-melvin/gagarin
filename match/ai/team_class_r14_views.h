// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing Team action argument and member dispatch views, shared by the
// recovered action methods; names are placeholders, not retail type claims.
#ifndef GG_MATCH_AI_TEAM_CLASS_R14_VIEWS_H
#define GG_MATCH_AI_TEAM_CLASS_R14_VIEWS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct ActionArg_r14 {
    int unknown_00;
    int unknown_04;   // +0x04
};

struct TeamMemberVtbl_r14;

struct TeamMember_r14 {
    TeamMemberVtbl_r14* Vtbl;                 // +0x000
    char                _pad004[0x5D8 - 0x04];
    TeamMember_r14*     Next;                 // +0x5D8
    char                _pad5DC[0x689 - 0x5DC];
    bool                Flag689;              // +0x689
};
GG_STATIC_ASSERT(offsetof(TeamMember_r14, Next)    == 0x5D8);
GG_STATIC_ASSERT(offsetof(TeamMember_r14, Flag689) == 0x689);


typedef void (TeamMember_r14::*Fn174_r14)(void* a1, int a2, int a3);
typedef void (TeamMember_r14::*Fn3D4_r14)(int a1);
typedef bool (TeamMember_r14::*Fn33C_r14)();
typedef void (TeamMember_r14::*Fn51C_r14)();
struct TeamMemberVtbl_r14 {
    char      _pad000[0x174];
    Fn174_r14 At_174;                         // +0x174
    char      _pad178[0x33C - 0x178];
    Fn33C_r14 At_33C;                         // +0x33C
    char      _pad340[0x3D4 - 0x340];
    Fn3D4_r14 At_3D4;                         // +0x3D4
    char      _pad3D8[0x51C - 0x3D8];
    Fn51C_r14 At_51C;                         // +0x51C
};
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_174) == 0x174);
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_33C) == 0x33C);
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_3D4) == 0x3D4);
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_51C) == 0x51C);

struct ObjList_r14_6502D30 {
    // FUNCTION: GAMEMD 0x502D30 (decl; reloc)
    int FUN_00502D30(int a1);
};

// GLOBAL: GAMEMD 0xB0E968 -- constant argument for member slot 0x174.
extern char DAT_00B0E968[];


#endif // GG_MATCH_AI_TEAM_CLASS_R14_VIEWS_H
