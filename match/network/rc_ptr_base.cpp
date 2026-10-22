// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
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
