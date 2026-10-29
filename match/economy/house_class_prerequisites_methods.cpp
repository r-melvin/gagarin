// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x505360.

#include "house_class_prerequisites_methods.h"

// FUNCTION: GAMEMD 0x505360
//
// Are all of a type's prerequisites among the first `count` owned building
// types? A non-negative entry names one building type; a negative one is a
// generic class (power, factory, barracks, radar, tech, ...) satisfied by
// any type in the matching rules list.
//
// The outer prerequisite loop is written with explicit labels, because retail
// lays every loop out as `Jcc far-exit; JMP top` with the shared false/true
// epilogues at the end.
//
// The two inner search loops are written as `while (1) { if (!(exit test))
// goto ...; advance; if (!(continuation)) goto fail; }`, with the negation
// wrapping each whole test. That is what gives retail's `Jcc far-exit; JMP
// top` back edges. Written as explicit labels with a trailing `goto scan`,
// cl 8804 threads the back edge: it replaces the unconditional jump with a
// copy of the loop head's compare and branch (`JGE fail; CMP [EAX],EDX;
// JNE scan` for retail's `JGE fail; JMP scan`), which then lets the positive
// path fall into the `found:` increment and duplicates the `return true`
// epilogue after it instead of jumping to the shared one. The outer
// prerequisite loop stays on explicit labels; turning it into a `while (1)`
// as well drops to 40.6%, and a `while (*item != building)` over the scan
// with the found exit after it stays at the label form's score. Same lever as
// 0x40E3E0 / 0x526CC0: the negation has to wrap the whole test.
bool HouseClass::AllPrerequisitesAvailable(TechnoTypeClass* type,
                                           DynamicVectorClass<BuildingTypeClass*>* owned,
                                           int count)
{
    int i = 0;
    if (type->Prerequisite.Count <= 0) {
        goto done;
    }
top:
    {
        int prerequisite = type->Prerequisite.Items[i];
        if (prerequisite >= 0) {
            int k = 0;
            if (count <= 0) {
                goto fail;
            }
            const BuildingTypeClass* building = DAT_00A83C6C[prerequisite];
            BuildingTypeClass** item = owned->Items;
            while (1) {
                if (!(*item != building)) {
                    goto found;
                }
                k++;
                item++;
                if (!(k < count)) {
                    goto fail;
                }
            }
        } else {
            TypeList<const BuildingTypeClass*>* list = 0;
            switch (prerequisite) {
            case -1: list = &RulesInstance->list_08C8;    break;
            case -2: list = &RulesInstance->list_0938;     break;
            case -3: list = &RulesInstance->list_0900; break;
            case -4: list = &RulesInstance->list_0A34;               break;
            case -5: list = &RulesInstance->list_091C;    break;
            case -6: list = &RulesInstance->list_08E4;  break;
            }
            int j = 0;
            if (list->Count <= 0) {
                goto fail;
            }
            while (1) {
                const BuildingTypeClass* building = list->Slot6(j);
                for (int k = 0; k < count; k++) {
                    if (owned->Items[k] == building) {
                        goto found;
                    }
                }
                j++;
                if (!(j < list->Count)) {
                    goto fail;
                }
            }
        }
    }
found:
    i++;
    if (i >= type->Prerequisite.Count) {
        goto done;
    }
    goto top;
fail:
    return false;
done:
    return true;
}
