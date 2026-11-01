// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. Each of these eight functions is the plain (non-deleting)
//   destructor of one vector instantiation: reseat the base vtable, release
//   the element block if this vector owns one, then clear the bookkeeping.
//   The only per-instance variation is the vtable constant stored at +0 and
//   the relative displacement of the CALL to the CRT free; every other byte is
//   identical across the family, so the body is written once as a macro and
//   expanded per instantiation. Ordered ascending by retail address.

#include "vector_vtable_plain_dtor_family_methods.h"

// FUNCTION: GAMEMD 0x0049F9D0
GG_VTBL_PLAIN_DTOR_BODY(0049F9D0, 007E4DB8)

// FUNCTION: GAMEMD 0x00679F70
GG_VTBL_PLAIN_DTOR_BODY(00679F70, 007E4DB8)

// FUNCTION: GAMEMD 0x00679FA0
GG_VTBL_PLAIN_DTOR_BODY(00679FA0, 007EAA08)

// FUNCTION: GAMEMD 0x00679FD0
GG_VTBL_PLAIN_DTOR_BODY(00679FD0, 007EAC48)

// FUNCTION: GAMEMD 0x0067A000
GG_VTBL_PLAIN_DTOR_BODY(0067A000, 007EAC68)

// FUNCTION: GAMEMD 0x0067A030
GG_VTBL_PLAIN_DTOR_BODY(0067A030, 007EAC28)

// FUNCTION: GAMEMD 0x0067A060
GG_VTBL_PLAIN_DTOR_BODY(0067A060, 007F0D9C)

// FUNCTION: GAMEMD 0x00771A00
GG_VTBL_PLAIN_DTOR_BODY(00771A00, 007E37EC)
