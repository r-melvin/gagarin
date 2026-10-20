// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41F230.

#include "threshold_compare_methods.h"

// FUNCTION: GAMEMD 0x41F230
//
// Compare the node's measured value against this object's threshold using
// whichever of six relational operators is selected. A missing node, or an
// operator outside the table, is false.
//
// Every case assigns the function-scope `result` and `break`s to the single
// `return result` at the end. That is what keeps the result in BL — the
// register it was zeroed into at entry (`XOR BL,BL`) — with each case's
// `SETcc BL; MOV AL,BL` and its own epilogue for cases 0..4, while case 5
// falls into the default exit at 0x41F2BD. Returning per case (`return value
// < Threshold;` or `result = ...; return result;`) makes VC6 write each
// `SETcc` straight to AL and drops the five `MOV AL,BL` (30.4%); an inline
// helper holding the switch adds an extra register round-trip (7.1%).
bool Obj_0041F230::FUN_0041F230(int, Node_0041F230* node)
{
    bool result = false;
    if (node != 0) {
        int value = node->Sub.Vptr->At_18(&node->Sub);
        switch (this->Op) {
        case 0:
            result = value < this->Threshold;
            break;
        case 1:
            result = value <= this->Threshold;
            break;
        case 2:
            result = value == this->Threshold;
            break;
        case 3:
            result = value >= this->Threshold;
            break;
        case 4:
            result = value > this->Threshold;
            break;
        case 5:
            result = value != this->Threshold;
            break;
        }
    }
    return result;
}
