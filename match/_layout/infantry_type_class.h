// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: InfantryTypeClass ctor FUN_0x005236A0 member-access sites
//   (start 0xDF8, size 0xED0), cross-checked vs YRpp.
//   Verified by the pad anchors align_ECC@0xECC,
//   FireUp@0xE40, DeadBodies@0xE50, HarvestRate@0xEB8 landing exactly.
//
// InfantryTypeClass — leaf type blueprint for infantry units. Derives
// TechnoTypeClass (the full techno blueprint spine) at offset 0, and adds the
// infantry-specific occupy/sequence/voice/flag fields from 0xDF8. Smallest of
// the four leaf type classes (sizeof 0xED0).
//
// Pointer / TypeList / WeaponStruct members read as int/undefined4 in decomp
// are 32-bit truncation sites; modelled here as real 4-byte pointers /
// exact-size component structs so every downstream offset stays byte-exact.
#ifndef GG_MATCH_LAYOUT_INFANTRY_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_INFANTRY_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_type_class.h"   // TechnoTypeClass (sizeof 0xDF8), TypeListLayout,
                                 // WeaponStruct, AnimTypeClass fwd-decl

// Opaque forward decl for the truncation-site pointer member (4 bytes).
struct SequenceStruct;

// ---------------------------------------------------------------------------
// InfantryTypeClass  (0xDF8..0xECF, sizeof = 0xED0)
// ---------------------------------------------------------------------------
class InfantryTypeClass : public TechnoTypeClass
{
public:
    int             ArrayIndex;          // +0xDF8
    int             Pip;                 // +0xDFC (PipIndex enum)
    int             OccupyPip;           // +0xE00 (PipIndex enum)
    WeaponStruct    OccupyWeapon;        // +0xE04 (0x1C)
    WeaponStruct    EliteOccupyWeapon;   // +0xE20 (0x1C)
    SequenceStruct* Sequence;            // +0xE3C
    int             FireUp;              // +0xE40
    int             FireProne;           // +0xE44
    int             SecondaryFire;       // +0xE48
    int             SecondaryProne;      // +0xE4C
    TypeListLayout  DeadBodies;          // +0xE50 (TypeList<AnimTypeClass*>)
    TypeListLayout  DeathAnims;          // +0xE6C (TypeList<AnimTypeClass*>)
    TypeListLayout  VoiceComment;        // +0xE88 (TypeList<int>)
    int             EnterWaterSound;     // +0xEA4
    int             LeaveWaterSound;     // +0xEA8
    bool            Cyborg;              // +0xEAC
    bool            NotHuman;            // +0xEAD
    bool            Ivan;                // +0xEAE
    unsigned char   _pad_EAF[1];         // +0xEAF
    int             DirectionDistance;   // +0xEB0
    bool            Occupier;            // +0xEB4
    bool            Assaulter;           // +0xEB5
    unsigned char   _pad_EB6[2];         // +0xEB6
    int             HarvestRate;         // +0xEB8
    bool            Fearless;            // +0xEBC
    bool            Crawls;              // +0xEBD
    bool            Infiltrate;          // +0xEBE
    bool            Fraidycat;           // +0xEBF
    bool            TiberiumProof;       // +0xEC0
    bool            Civilian;            // +0xEC1
    bool            C4;                  // +0xEC2
    bool            Engineer;            // +0xEC3
    bool            Agent;               // +0xEC4
    bool            Thief;               // +0xEC5
    bool            VehicleThief;        // +0xEC6
    bool            Doggie;              // +0xEC7
    bool            Deployer;            // +0xEC8
    bool            DeployedCrushable;   // +0xEC9
    bool            UseOwnName;          // +0xECA
    bool            JumpJetTurn;         // +0xECB
    unsigned long   align_ECC;           // +0xECC (DWORD)
};

// --- Representative offset asserts (spanning the struct) + final sizeof ------
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, ArrayIndex)        == 0xDF8);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, OccupyWeapon)      == 0xE04);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, EliteOccupyWeapon) == 0xE20);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, Sequence)          == 0xE3C);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, FireUp)            == 0xE40);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, DeadBodies)        == 0xE50);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, VoiceComment)      == 0xE88);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, EnterWaterSound)   == 0xEA4);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, Cyborg)            == 0xEAC);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, DirectionDistance) == 0xEB0);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, HarvestRate)       == 0xEB8);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, Fearless)          == 0xEBC);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, JumpJetTurn)       == 0xECB);
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, align_ECC)         == 0xECC);
GG_STATIC_ASSERT(sizeof(InfantryTypeClass)                      == 0xED0);

#endif  // GG_MATCH_LAYOUT_INFANTRY_TYPE_CLASS_H
