// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x509CD0.

#include "house_class_paradrop_methods.h"

// Inlined by retail: BaseCenter when set, otherwise BaseSpawnCell.
inline Cell HouseClass::GetBaseCenter() const
{
    if (this->BaseCenter.X != DAT_00A8EF98.X || this->BaseCenter.Y != DAT_00A8EF98.Y) {
        return this->BaseCenter;
    }
    return this->BaseSpawnCell;
}

// FUNCTION: GAMEMD 0x509CD0
//
// Fire the paradrop super-weapon. The drop goes to the preferred target cell
// when one is set; otherwise, for target type 1, to a free 5x5 spot near the
// enemy house's base centre (this house when no enemy is chosen), offset by
// two cells; for any other type to whatever the by-type picker returns. A
// target that is still the sentinel is not fired at.
//
// PARTIAL (31.1%, up from 18.9%; 87 instructions against retail's 90).
// The block-layout half of the residual is solved by the same lever that took
// the sibling 0x509E00 to 100%: an explicit goto skeleton with the have-cell
// block written BEFORE the join label. Retail keeps the have-cell load in
// source position (`MOV EAX,[ESI+0x54F0]; MOV [ESP+8],EAX; JMP join`) and lets
// the paradrop arm fall into the join; every if/else-if spelling makes cl 8804
// sink that block to the end and drop the JMP. `have:` written after the join
// label instead is 22.2%, which is what establishes that the order is the
// lever and not the gotos.
//
// Residual, and it is the banked 8447-vs-8804 constant-materialisation class:
// at the NearByLocation call retail builds the constant 5 once and copies it
// (`MOV EAX,5; MOV ECX,EAX; PUSH ECX; PUSH EAX`) and holds the zero in EDX,
// where cl pushes both immediates and keeps the zero in EAX. Passing the 5
// through a named local, declared either side of the base-centre read, is
// constant-folded and leaves the stream unchanged (31.1% both ways).
// Second-look lever (42.2%): the by-value zero cell is built in the argument
// list as a temporary (`Cell(0, 0)`, needs the two-argument ctor added to
// Cell in the header), so its stores happen at argument-evaluation
// time just before the call as in retail, rather than as a named local
// initialised ahead of the pushes.
void HouseClass::Fire_ParaDrop(SuperClass* pSuper)
{
    HouseClass* enemy;
    if (this->EnemyHouseIndex != -1) {
        enemy = DAT_00A8022C[this->EnemyHouseIndex];
    } else {
        enemy = this;
    }

    Cell cell = DAT_00A8EF98;
    Cell buf;

    if (this->PreferredTargetCell.X != DAT_00A8EF98.X) goto have;
    if (this->PreferredTargetCell.Y != DAT_00A8EF98.Y) goto have;
    if (this->PreferredTargetType != 1) {
        cell = this->PickTargetByType(this->PreferredTargetType);
        goto join;
    }
    {
        cell = enemy->GetBaseCenter();
        cell = *MapInstance_00509CD0.NearByLocation(&buf, cell, 0, -1, 0, false, 5, 5,
                                                    false, false, false, true, Cell(0, 0),
                                                    false, false);
        cell.X += 2;
        cell.Y += 2;
    }
    goto join;
have:
    cell = this->PreferredTargetCell;
join:
    if (cell.X != DAT_00A8EF98.X || cell.Y != DAT_00A8EF98.Y) {
        this->Fire_SW(this->Supers.FindItemIndex(pSuper), cell);
    }
}
