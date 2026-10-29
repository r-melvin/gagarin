// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FC790 via the local
//   Ghidra disassembly. Offsets, vtable slots and globals confirmed numerically
//   (see the header). Name from YRpp (reconfirmed:
//   the whatAmI comparison against AbstractType::Building at 0x4FC7BE is what
//   distinguishes this member of the DestroyAll family).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4FC790   HouseClass::DestroyAllBuildings (__thiscall)
//   GLOBAL:   GAMEMD 0xA8EC78   TechnoClass::Array
//   GLOBAL:   GAMEMD 0x8871E0   RulesClass::Instance pointer

#include "house_class_destroy_all_methods.h"

// FUNCTION: GAMEMD 0x4FC6D0  HouseClass::DestroyAll (__thiscall)
//
// The unrestricted member of the family: no type test at all, but an extra
// ownership rule. GetOriginalOwner is compared against the techno's *current*
// Owner at +0x21C, and when those disagree the object has changed hands. In
// that case a unit currently held by someone else's capture manager is spared
// - that is the CaptureManager call at 0x4FC71E - so a house destroying itself
// does not take down units it no longer controls.
//
// The `owner == this` test appears twice in retail (0x4FC707 and 0x4FC727),
// once inside the changed-hands branch and once on the common path, and that
// duplication is what the source shape has to produce. Writing it literally,
// with an inner `if` per skip case and an explicit `i++; continue;` in each,
// scores 26.1% - VC6 emits a separate increment per exit instead of retail's
// one shared block at 0x4FC770. The form below keeps the sibling functions'
// single trailing `else { i++; }` and gets the second test from the negated
// spare-this-unit chain sitting in front of it; VC6 threads the failing
// `owner == this` inside that chain straight to the else, which is where
// retail's 0x4FC70B jump goes.
void HouseClass::DestroyAll()
{
    int i = 0;
    TechnoClass* lastDestroyed = 0;

    while (i < TechnoArray.Count) {
        TechnoClass* techno = TechnoArray.Items[i];
        HouseClass* owner = techno->GetOriginalOwner();

        if (!(owner != techno->Owner
              && owner == this
              && techno->MindControlledBy
              && ((CaptureManagerClass*)((TechnoClass*)techno->MindControlledBy)->CaptureManager)->FUN_00472330(techno))
            && owner == this
            && techno != lastDestroyed) {

            int damage = techno->Health;

            if (techno->TemporalTargetingMe) {
                ((TemporalClass*)techno->TemporalTargetingMe)->JustLetGo();
            }

            techno->vf_91(&damage, 0, Rules->C4Warhead, 0, true, true, 0);
            lastDestroyed = techno;
        } else {
            i++;
        }
    }
}

// FUNCTION: GAMEMD 0x4FC790  HouseClass::DestroyAllBuildings (__thiscall)
//
// Walk every techno in the global array; each building this house owns takes
// damage equal to its own remaining health, which destroys it.
//
// Two shapes here are load-bearing.
//
// The index is not advanced on the destroy path. Destroying an object removes
// it from the array, so the entry that slid into this slot has not been looked
// at yet and the walk must re-examine the same index. Retail expresses that as
// `MOV EDI,ESI; JMP` straight over the `INC EBX` at 0x4FC810 — an else-branch
// increment, not the `i--` idiom documented in the methodology (which would
// show an adjacent DEC/INC pair). Written as a `while` with `i++` in the else,
// the four failing conditions all land on the increment exactly as retail has
// them.
//
// The damage slot is declared once at function scope. Declared inside the
// destroy branch, VC6 hoists the TemporalTargetingMe load ahead of the Health
// store (93.0%); at function scope the store comes first, as in retail.
//
// `lastDestroyed` is the guard that keeps that from looping forever. If the
// receiveDamage call does not actually remove the object, the next pass would
// see the same pointer at the same index; comparing against the previous one
// forces the walk to move on. Retail keeps it in EDI, zeroed on entry.
void HouseClass::DestroyAllBuildings()
{
    int i = 0;
    TechnoClass* lastDestroyed = 0;
    int damage;

    while (i < TechnoArray.Count) {
        TechnoClass* techno = TechnoArray.Items[i];

        if (techno->GetOriginalOwner() == this
            && techno->vf_11() == ABSTRACT_TYPE_BUILDING
            && !techno->InLimbo
            && techno != lastDestroyed) {

            damage = techno->Health;

            if (techno->TemporalTargetingMe) {
                ((TemporalClass*)techno->TemporalTargetingMe)->JustLetGo();
            }

            techno->vf_91(&damage, 0, Rules->C4Warhead, 0, true, true, 0);
            lastDestroyed = techno;
        } else {
            i++;
        }
    }
}

// FUNCTION: GAMEMD 0x4FC820  HouseClass::DestroyAllNonBuildingsNonNaval (__thiscall)
//
// The same walk as DestroyAllBuildings with the building test inverted and one
// extra condition: anything whose type carries the naval flag is left alone,
// which is what separates this from DestroyAllNonBuildingsNaval @0x4FC8D0. The
// type comes through vtable slot +0x84 (getTechnoType) and the flag is the byte
// at +0xCCE on it.
//
// Written out longhand rather than derived from the sibling above. The two look
// interchangeable and are not: the conditions differ in count and in order, and
// the family rule in the methodology exists because macro-generated siblings
// have already been caught diverging.
void HouseClass::DestroyAllNonBuildingsNonNaval()
{
    int i = 0;
    TechnoClass* lastDestroyed = 0;

    while (i < TechnoArray.Count) {
        TechnoClass* techno = TechnoArray.Items[i];

        if (techno->GetOriginalOwner() == this
            && techno->vf_11() != ABSTRACT_TYPE_BUILDING
            && !techno->InLimbo
            && !techno->vf_33()->Naval
            && techno != lastDestroyed) {

            int damage = techno->Health;

            if (techno->TemporalTargetingMe) {
                ((TemporalClass*)techno->TemporalTargetingMe)->JustLetGo();
            }

            techno->vf_91(&damage, 0, Rules->C4Warhead, 0, true, true, 0);
            lastDestroyed = techno;
        } else {
            i++;
        }
    }
}

// FUNCTION: GAMEMD 0x4FC8D0  HouseClass::DestroyAllNonBuildingsNaval (__thiscall)
//
// The naval half of the pair above: same walk, same conditions, with the type
// flag test the other way round (`JZ` skip at 0x4FC923 rather than `JNZ`), so
// only naval units are destroyed. Written out longhand for the same reason.
void HouseClass::DestroyAllNonBuildingsNaval()
{
    int i = 0;
    TechnoClass* lastDestroyed = 0;

    while (i < TechnoArray.Count) {
        TechnoClass* techno = TechnoArray.Items[i];

        if (techno->GetOriginalOwner() == this
            && techno->vf_11() != ABSTRACT_TYPE_BUILDING
            && !techno->InLimbo
            && techno->vf_33()->Naval
            && techno != lastDestroyed) {

            int damage = techno->Health;

            if (techno->TemporalTargetingMe) {
                ((TemporalClass*)techno->TemporalTargetingMe)->JustLetGo();
            }

            techno->vf_91(&damage, 0, Rules->C4Warhead, 0, true, true, 0);
            lastDestroyed = techno;
        } else {
            i++;
        }
    }
}
