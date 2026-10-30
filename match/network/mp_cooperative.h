// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   MPCooperative, the co-operative MultiplayerGameMode leaf (RTTI name under
//   its vtable 0x7EE27C), whose bodies sit in the retail block of MPCoop.cpp
//   (assert __FILE__). Only what the bodies here touch is modelled: the
//   0x70-byte helper object owned at +0x40.
#ifndef GG_MATCH_NETWORK_MP_COOPERATIVE_H
#define GG_MATCH_NETWORK_MP_COOPERATIVE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "multiplayer_game_mode.h"
#include "../_layout/vector_class.h"

// CoopCampaignClass: the 0x70-byte object behind MPCooperative +0x40 and the
// element of the +0x324 vector (RTTI `DynamicVectorClass<CoopCampaignClass*>`,
// vtable 0x7EE350; `PUSH 0x70` before each allocation). Placeholder members.
class CoopCampaignClass
{
public:
    CoopCampaignClass();                  // GAMEMD 0x49B610 (decl; reloc)
    ~CoopCampaignClass();                 // GAMEMD 0x49B720 (decl; reloc)
    void FUN_0049B760(void* a, void* b);  // GAMEMD 0x49B760 (decl; reloc) RET 8
    void FUN_0049CAF0(int a);             // GAMEMD 0x49CAF0 (decl; reloc) RET 4
    bool FUN_0049BC80(int* out);          // GAMEMD 0x49BC80 (decl; reloc) RET 4
    bool FUN_0049BCC0(int* out);          // GAMEMD 0x49BCC0 (decl; reloc) RET 4

    char unknown_00[0x70];                // +0x00
};
GG_STATIC_ASSERT(sizeof(CoopCampaignClass) == 0x70);

// A 12-byte record whose constructor 0x53ECB0 fills its first ten bytes with
// 0xFF (the array at +0xC4 steps by 0xC).
struct SlotBytes_0053ECB0
{
    SlotBytes_0053ECB0();                 // GAMEMD 0x53ECB0 (decl; reloc)
    unsigned char unknown_00[10];         // +0x00
    short unknown_0A;                     // +0x0A
};
GG_STATIC_ASSERT(sizeof(SlotBytes_0053ECB0) == 0xC);

// The object owned at +0x50: deleted through its slot 0 with the flag 1.
class Owned_MPCoop50
{
public:
    virtual ~Owned_MPCoop50();
};

struct NodeNameType;


// The scenario singleton as the start-spot code sees it.
struct MPCoopRandom
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) -- RandomRanged(low, high).
    int FUN_0065C7E0(int low, int high);
};
struct MPCoopScenario
{
    char         unknown_0000[0x218];        // +0x0000
    MPCoopRandom Random;                     // +0x0218
    char         unknown_021C[0x1180 - 0x21C];
    int          StartHouse[16];             // +0x1180 house index per start spot
    char         unknown_11C0[0x11E4 - 0x11C0];
    int          NumCoopHumanStartSpots;     // +0x11E4 (INI key string 0x83DE30)
};
GG_STATIC_ASSERT(offsetof(MPCoopScenario, Random) == 0x218);
GG_STATIC_ASSERT(offsetof(MPCoopScenario, StartHouse) == 0x1180);
GG_STATIC_ASSERT(offsetof(MPCoopScenario, NumCoopHumanStartSpots) == 0x11E4);
// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern MPCoopScenario* MPCoopScenario_00A8B230;

// VTABLE: GAMEMD 0x7EE27C
class MPCooperative : public MultiplayerGameMode
{
public:
    MPCooperative(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f);
    virtual ~MPCooperative();

    // FUNCTION: GAMEMD 0x5C1CB0 (declaration; slot 9)
    virtual void vf_9();

    // FUNCTION: GAMEMD 0x5C36F0 (declaration; slot 35)
    virtual bool vf_35();

    // FUNCTION: GAMEMD 0x5C3700 (declaration; slot 15)
    virtual bool vf_15();

    // FUNCTION: GAMEMD 0x5C42C0 (declaration; slot 38)
    virtual int vf_38();

    // FUNCTION: GAMEMD 0x5C4EE0 (declaration; slot 1)
    virtual bool vf_1();

    // FUNCTION: GAMEMD 0x5C4EF0 (declaration; slot 2)
    virtual bool vf_2();

    // FUNCTION: GAMEMD 0x5C4F00 (declaration; slot 47)
    virtual bool vf_47();


    void FUN_005C21D0(struct HWND__* dialog, bool show);
    void FUN_005C23B0(struct HWND__* dialog, int id);
    void FUN_005C2500(struct HWND__* dialog);
    void FUN_005C2D00(int house, DynamicVectorClassLayout* spots, bool* taken);
    bool FUN_005C3EC0();

    CoopCampaignClass* unknown_40;                       // +0x040
    int   unknown_44;                                    // +0x044
    bool  unknown_48;                                    // +0x048
    bool  unknown_49;                                    // +0x049
    char  unknown_4A[2];                                 // +0x04A
    int   unknown_4C;                                    // +0x04C
    Owned_MPCoop50* unknown_50;                          // +0x050
    int   unknown_54;                                    // +0x054
    DynamicVectorClass<NodeNameType*> Nodes;             // +0x058 (vtable 0x7EE370)
    char  unknown_70[0xC4 - 0x70];                       // +0x070
    SlotBytes_0053ECB0 unknown_C4[8];                    // +0x0C4
    char  unknown_124[0x1A4 - 0x124];                    // +0x124
    DynamicVectorClass<int> unknown_1A4[8];              // +0x1A4
    DynamicVectorClass<int> unknown_264[8];              // +0x264
    DynamicVectorClass<CoopCampaignClass*> Campaigns;    // +0x324 (vtable 0x7EE350)
    int   unknown_33C;                                   // +0x33C
    bool  unknown_340;                                   // +0x340
};
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(MPCooperative, Nodes) == 0x58);
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_1A4) == 0x1A4);
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_264) == 0x264);
GG_STATIC_ASSERT(offsetof(MPCooperative, Campaigns) == 0x324);
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_33C) == 0x33C);
GG_STATIC_ASSERT(offsetof(MPCooperative, unknown_340) == 0x340);

// Native 0x5C1CB0 writes one byte at +0x340.
GG_STATIC_ASSERT(sizeof(((MPCooperative*)0)->unknown_340) == 1);
// Plain table model for the native 52-slot address point at 0x7EE27C.
struct MPCooperativeVtableLayoutEvidence { void* Slots[52]; };
GG_STATIC_ASSERT(sizeof(MPCooperativeVtableLayoutEvidence) == 0xD0);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 1 * sizeof(void*) == 0x4);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 2 * sizeof(void*) == 0x8);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 9 * sizeof(void*) == 0x24);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 15 * sizeof(void*) == 0x3C);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 35 * sizeof(void*) == 0x8C);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 38 * sizeof(void*) == 0x98);
GG_STATIC_ASSERT(offsetof(MPCooperativeVtableLayoutEvidence, Slots) + 47 * sizeof(void*) == 0xBC);

#endif  // GG_MATCH_NETWORK_MP_COOPERATIVE_H
