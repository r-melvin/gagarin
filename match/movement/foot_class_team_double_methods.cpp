// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DC760.

#include "../_layout/foot_class.h"

// The team type seen through its flag at +0xF2.
struct TeamTypeView_004DC760
{
    char _pad000[0xF2];
    bool unknown_F2;    // +0xF2
};
GG_STATIC_ASSERT(offsetof(TeamTypeView_004DC760, unknown_F2) == 0xF2);

// The team seen through its type at +0x24.
class TeamClass
{
public:
    char                  _pad000[0x24];
    TeamTypeView_004DC760* Type;     // +0x24
};
GG_STATIC_ASSERT(offsetof(TeamClass, Type) == 0x24);

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// FUNCTION: GAMEMD 0x4DC760
//
// A foot unit that belongs to a team whose type has the flag set reports a
// fixed constant; everyone else reports the stored double.
double FootClass::FUN_004DC760()
{
    if (this->Team != 0 && this->Team->Type->unknown_F2) {
        return DAT_007E1718;
    }
    return this->unknown_530;
}
