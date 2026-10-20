// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5519B0.

#include "map_class_add_object_methods.h"

// FUNCTION: GAMEMD 0x5519B0
//
// Add an object to this draw layer, either at its sorted position or appended
// at the end. The plain append is DynamicVectorClass::AddItem inlined (body in
// the header).
//
// Both answers are re-normalised on the way out: the sorted insert's full-width
// result becomes `NEG EAX; SBB EAX,EAX; NEG EAX`, and the inlined append's AL
// is squeezed through `XOR EDX,EDX; TEST AL,AL; SETNZ DL; MOV AL,DL` on each of
// its two tails. The second only appears with an explicit `!= 0` on the bool;
// a bare `return AddItem(object)`, or binding it to a bool local first, drops
// the four-instruction tail (60.4%), and a `?:` over the two calls re-shapes the
// whole function (58.5% / 13.2%).
bool LayerClass::AddObject(ObjectClass* object, bool sorted)
{
    if (sorted) {
        return SortedAdd(object) != 0;
    }
    return AddItem(object) != 0;
}
