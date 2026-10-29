// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DC760.

#include "../_layout/foot_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"



// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// FUNCTION: GAMEMD 0x4DC760
//
// A foot unit that belongs to a team whose type has the flag set reports a
// fixed constant; everyone else reports the stored double.
double FootClass::FUN_004DC760()
{
    if (this->Team != 0 && this->Team->Type->Flag_F2) {
        return DAT_007E1718;
    }
    return this->unknown_530;
}
