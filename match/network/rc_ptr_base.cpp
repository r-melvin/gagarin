// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   rc_ptr_base (RTTI `.?AVrc_ptr_base@@`, vtable 0x7F094C), read off the
//   user's retail gamemd.exe v1.001. The constructor seats the table, so this
//   unit also emits the table and its scalar deleting destructor 0x65D4D0.

#include "wdt_rc_ptr.h"

// FUNCTION: GAMEMD 0x65D430
rc_ptr_base::rc_ptr_base()
    : Pointer(0)
{
}

// FUNCTION: GAMEMD 0x65D460
// Release the pointee through its slot 2.
rc_ptr_base::~rc_ptr_base()
{
    if (Pointer != 0) {
        ReferenceCounted* old = (ReferenceCounted*)Pointer;
        Pointer = 0;
        old->vf_2();
    }
}

// SYNTHETIC: GAMEMD 0x65D4D0
// rc_ptr_base scalar deleting destructor, the destructor body inlined.

// FUNCTION: GAMEMD 0x65D4B0
// Copy constructor: share the pointee and count the new reference.
rc_ptr_base::rc_ptr_base(const rc_ptr_base& other)
    : Pointer(other.Pointer)
{
    if (Pointer != 0)
        ++((ReferenceCounted*)Pointer)->RefCount;
}

// FUNCTION: GAMEMD 0x65D660
// Seats the table; out of line, called by every derived destructor.
ReferenceCounted::~ReferenceCounted()
{
}

// FUNCTION: GAMEMD 0x65D670
// Drop one reference; the last one deletes the object.
void ReferenceCounted::vf_2()
{
    if (--RefCount == 0 && this != 0)
        delete this;
}

// FUNCTION: GAMEMD 0x65D690
// Vtable slot 1 of every ReferenceCounted table: returns false.
bool ReferenceCounted::vf_1(int)
{
    return false;
}

// SYNTHETIC: GAMEMD 0x65D6A0
// ReferenceCounted scalar deleting destructor, the destructor body inlined.
