// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452260: on the building the bytes `[ESI+0x660]`
//   (tested, then set), `[ESI+0x80]` (set) and `[ESI+0x6EA]` (set), the
//   dword `[ESI+0x504]` (tested for zero), the owner at `[ESI+0x21C]`, the
//   type at `[ESI+0x520]`, the light source at `[ESI+0x614]` and the anim
//   pointers from `[ESI+0x55C]` stepping 4; on the type the per-anim flag
//   `[EDI+EAX+0xF8C]` stepping 0x44 to 0x594, the byte `[EDX+0x16BE]`, the
//   dword `[EAX+0xEB8]` (pushed) and the byte `[EAX+0xCCE]`; on the owner
//   the bytes `[ECX+0x5778]`, `[EDX+0x5779]` and `[ECX+0x1FC]`. Callees:
//   0x554A60 (LightSourceClass::Activate, __thiscall, one pushed 0),
//   0x4533A0 (BuildingClass::CreateEndPost, __thiscall, one pushed 0),
//   0x425270 (per-anim enable, __fastcall, anim in ECX), 0x509140
//   (HouseClass::Update_FactoriesQueues, __thiscall, three pushed args),
//   0x50B6F0 (HouseClass::IsControlledByCurrentPlayer, __thiscall, AL) and
//   0x752700 (VoxClass::Play, __fastcall: ECX = name, EDX = -1, pushed -1).
//   Names cross-checked against YRpp BuildingClass::GoOnline / EnableStuff
//   (consult-only, no LICENSE) and the sibling TUs
//   match/combat/building_class_offline_methods.h and
//   match/economy/building_class_enable_methods.h, re-derived here under
//   this TU's own tags; +0x504 is TechnoClass::EMPLockRemaining per
//   match/_layout/techno_class.h.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_GO_ONLINE_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_GO_ONLINE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HouseClass_00452260
{
    char _pad0000[0x1FC];             // +0x0000
    char RecheckTechTree;             // +0x01FC
    char _pad01FD[0x5778 - 0x1FD];    // +0x01FD
    char PowerBlackoutWasActivated;   // +0x5778
    char RadarBlackoutWasActivated;   // +0x5779

    // FUNCTION: GAMEMD 0x509140 (decl; reloc) — HouseClass::Update_FactoriesQueues.
    void Update_FactoriesQueues(int factoryOf, bool isNaval, int buildCat);
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc) — HouseClass::IsControlledByCurrentPlayer.
    bool IsControlledByCurrentPlayer();
};
GG_STATIC_ASSERT(offsetof(HouseClass_00452260, RecheckTechTree) == 0x1FC);
GG_STATIC_ASSERT(offsetof(HouseClass_00452260, PowerBlackoutWasActivated) == 0x5778);
GG_STATIC_ASSERT(offsetof(HouseClass_00452260, RadarBlackoutWasActivated) == 0x5779);

// One per-animation record of the type; 0x44 bytes (the loop stride), with
// the enable flag at +0x40 (the loop reads `+0xF8C` = 0xF4C + 0x40).
struct AnimRecord_00452260
{
    char _pad00[0x40];   // +0x00
    bool Enabled;        // +0x40
    char _pad41[3];      // +0x41
};
GG_STATIC_ASSERT(offsetof(AnimRecord_00452260, Enabled) == 0x40);
GG_STATIC_ASSERT(sizeof(AnimRecord_00452260) == 0x44);

#define ANIM_COUNT_00452260 21

struct Type_00452260
{
    char                _pad0000[0xCCE];                       // +0x0000
    bool                Naval;                                 // +0x0CCE
    char                _pad0CCF[0xEB8 - 0xCCF];               // +0x0CCF
    int                 Factory;                               // +0x0EB8
    char                _pad0EBC[0xF4C - 0xEBC];               // +0x0EBC
    AnimRecord_00452260 Anims[ANIM_COUNT_00452260];            // +0x0F4C
    char                _pad14E0[0x16BE - (0xF4C + ANIM_COUNT_00452260 * 0x44)];
    bool                HasEndPost;                            // +0x16BE
};
GG_STATIC_ASSERT(offsetof(Type_00452260, Naval) == 0xCCE);
GG_STATIC_ASSERT(offsetof(Type_00452260, Factory) == 0xEB8);
GG_STATIC_ASSERT(offsetof(Type_00452260, Anims) == 0xF4C);
GG_STATIC_ASSERT(offsetof(Type_00452260, HasEndPost) == 0x16BE);

struct LightSource_00452260
{
    // FUNCTION: GAMEMD 0x554A60 (decl; reloc) — LightSourceClass::Activate.
    void Activate(unsigned long zero);
};

struct Anim_00452260;
// FUNCTION: GAMEMD 0x425270 (decl; reloc) — per-animation enable.
void __fastcall FUN_00425270(Anim_00452260* anim);

struct VoxClass_00452260
{
    // FUNCTION: GAMEMD 0x752700 (decl; reloc) — VoxClass::Play.
    static void __fastcall Play(const char* name, int a, int b);
};

struct BuildingClass_00452260
{
    char                   _pad0000[0x80];                      // +0x0000
    char                   NeedsRedraw;                         // +0x0080
    char                   _pad0081[0x21C - 0x81];              // +0x0081
    HouseClass_00452260*   Owner;                               // +0x021C
    char                   _pad0220[0x504 - 0x220];             // +0x0220
    unsigned int           EMPLockRemaining;                    // +0x0504
    char                   _pad0508[0x520 - 0x508];             // +0x0508
    Type_00452260*         Type;                                // +0x0520
    char                   _pad0524[0x55C - 0x524];             // +0x0524
    Anim_00452260*         Anims[ANIM_COUNT_00452260];          // +0x055C
    char                   _pad05B0[0x614 - (0x55C + ANIM_COUNT_00452260 * 4)];
    LightSource_00452260*  LightSource;                         // +0x0614
    char                   _pad0618[0x660 - 0x618];             // +0x0618
    char                   HasPower;                            // +0x0660
    char                   _pad0661[0x6EA - 0x661];             // +0x0661
    bool                   IsEnabled;                           // +0x06EA

    // FUNCTION: GAMEMD 0x4533A0 (decl; reloc) — BuildingClass::CreateEndPost.
    void CreateEndPost(bool arg);

    // FUNCTION: GAMEMD 0x452410 — BuildingClass::EnableStuff (matched out of
    // line in match/economy/building_class_enable_methods.cpp). Defined in
    // the class body here because GoOnline expands it inline — retail keeps
    // the callee's own EBX/EDI save/restore around the expanded loop.
    void EnableStuff()
    {
        IsEnabled = true;
        if (LightSource != 0)
            LightSource->Activate(0);
        if (Type->HasEndPost)
            CreateEndPost(false);
        for (int i = 0; i < ANIM_COUNT_00452260; i++) {
            if (Type->Anims[i].Enabled && Anims[i] != 0)
                FUN_00425270(Anims[i]);
        }
    }

    // FUNCTION: GAMEMD 0x452260
    void GoOnline();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, NeedsRedraw) == 0x80);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, EMPLockRemaining) == 0x504);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, Anims) == 0x55C);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, HasPower) == 0x660);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452260, IsEnabled) == 0x6EA);

// STRING: GAMEMD 0x8190C8 — "EVA_BuildingOnLine".
extern const char EvaBuildingOnLine_00452260[];

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_GO_ONLINE_METHODS_H
