// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The checked techno test read at 0x5F52B2 (ObjectClass::vf_55) and in the UICmnds selection walks:
//   a null guard, then the +0x14 bit-0 read, carried through a result local whose byte stays in the
//   frame in retail.
#ifndef GG_MATCH_OBJECT_FLAG_IS_TECHNO_H
#define GG_MATCH_OBJECT_FLAG_IS_TECHNO_H

#include "_layout/object_class.h"

inline bool ObjectFlagIsTechno(ObjectClass* object)
{
    bool result = false;
    if (object != 0) {
        result = object->Flags.IsTechno;
    }
    return result;
}

#endif
