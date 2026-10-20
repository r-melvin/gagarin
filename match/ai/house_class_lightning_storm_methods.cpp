// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x509E00.

#include "house_class_lightning_storm_methods.h"

// FUNCTION: GAMEMD 0x509E00
//
// Fire the storm super-weapon. Nothing happens while the global flag is set or
// while nothing is prepared at +0x5600. The target is the stored cell at
// +0x54F0 if it is real, otherwise one is picked now (the ion-cannon picker for
// mode 1, the by-type picker otherwise) into a shared 4-byte buffer; a target
// that is still the sentinel is not fired at.
//
// MATCHED 100% (50/50). The residual was never phrasing inside the
// expressions -- it was block placement, and the lever is an explicit goto
// skeleton with the blocks written in retail's own order. Retail lays the
// have-cell load out FIRST, immediately after the two sentinel tests
// (`MOV EAX,[ESI+0x54F0]; JMP join`), then the two pickers, then one shared
// `MOV EAX,[EAX]` dereference that the ion picker jumps to and the by-type
// picker falls into. Written as `if/else if/else` (any of the fourteen forms
// previously measured here, 12.5-21.6%) cl 8804 sinks the have-cell block to
// the end and tail-duplicates the one-instruction dereference into both
// picker arms. Spelled as `goto have;` twice, `goto join;` out of each picker
// and the `have:` block placed before `join:`, cl reproduces retail's layout
// exactly. Two neighbouring skeletons confirm the order is what matters:
// `have:` after `join:` is 21.2% (two extra MOVs), and joining through a
// `Cell*` selected in each arm is 60.0% (a LEA where retail has a MOV).
void House_00509E00::Fire_LightningStorm(Super_00509E00* pSuper)
{
    if (FUN_0053A100()) {
        return;
    }
    if (this->At_5600 == -1) {
        return;
    }

    Cell_00509E00 cell = DAT_00A8EF98;
    Cell_00509E00 buf;

    if (this->At_54F0.X != DAT_00A8EF98.X) goto have;
    if (this->At_54F0.Y != DAT_00A8EF98.Y) goto have;
    if (this->At_54EC == 1) {
        cell = *this->PickIonCannonTarget(&buf);
        goto join;
    }
    cell = *this->PickTargetByType(&buf, this->At_54EC);
    goto join;
have:
    cell = this->At_54F0;
join:
    ;
    if (cell.X != DAT_00A8EF98.X || cell.Y != DAT_00A8EF98.Y) {
        this->Fire_SW(this->Supers.FindItemIndex(pSuper), cell);
    }
}
