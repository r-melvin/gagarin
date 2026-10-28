// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x53EE70 and 0x53EF60; the transport-mode global
//   (0x828140) is the one read by the sibling comparison at 0x53EF30.
//
// IPXAddressClass equality and inequality. Address index: 0x53EE70, 0x53EF60.

#include <string.h>
#pragma intrinsic(memcmp)
#include "../_layout/ipx_address_class.h"

// GLOBAL: GAMEMD 0x828140 -- transport mode; 2 compares the node and port only.
extern int DAT_00828140;

// FUNCTION: GAMEMD 0x53EE70
// Two addresses are equal when their node bytes match and, if both carry a
// network number, the numbers match as well (mode 2: node dword plus port).
bool IPXAddressClass::FUN_0053EE70(const IPXAddressClass* other)
{
    if (DAT_00828140 == 2) {
        if (memcmp(NodeAddress, other->NodeAddress, 4) == 0 && Port == other->Port)
            return true;
        return false;
    }
    if (!(NetworkNumber[0] || NetworkNumber[1] || NetworkNumber[2] || NetworkNumber[3])
        || !(other->NetworkNumber[0] || other->NetworkNumber[1] || other->NetworkNumber[2]
             || other->NetworkNumber[3])) {
        bool same = memcmp(NodeAddress, other->NodeAddress, 6) == 0;
        return same;
    }
    if (memcmp(NodeAddress, other->NodeAddress, 6) == 0
        && *(unsigned long*)NetworkNumber == *(unsigned long*)other->NetworkNumber)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x53EF60
// The inverse of the comparison above.
bool IPXAddressClass::FUN_0053EF60(const IPXAddressClass* other)
{
    if (DAT_00828140 == 2) {
        if (memcmp(NodeAddress, other->NodeAddress, 4) == 0 && Port == other->Port)
            return false;
        return true;
    }
    if (!(NetworkNumber[0] || NetworkNumber[1] || NetworkNumber[2] || NetworkNumber[3])
        || !(other->NetworkNumber[0] || other->NetworkNumber[1] || other->NetworkNumber[2]
             || other->NetworkNumber[3])) {
        bool differs = memcmp(NodeAddress, other->NodeAddress, 6) != 0;
        return differs;
    }
    if (memcmp(NodeAddress, other->NodeAddress, 6) == 0
        && *(unsigned long*)NetworkNumber == *(unsigned long*)other->NetworkNumber)
        return false;
    return true;
}
