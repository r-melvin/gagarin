// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Constructors that seat their object's first word and return `this`.
// Ten remaining instantiations across three sub-shapes; within a sub-shape every
// byte outside the vtable constant is identical, so each body is written once
// as a macro and expanded per instantiation. Ordered ascending by retail
// address.

#include "vtable_seating_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x006406E0
GG_SEATNULL_BODY(006406E0)

// FUNCTION: GAMEMD 0x00717BC0
GG_SEAT0A_BODY(007F0DCC)

// FUNCTION: GAMEMD 0x00717BD0
GG_SEAT0A_BODY(007E4E78)

// FUNCTION: GAMEMD 0x00717BE0
GG_SEAT0A_BODY(007EAA28)

// FUNCTION: GAMEMD 0x00717BF0
GG_SEAT0A_BODY(007EB714)

// FUNCTION: GAMEMD 0x0074FF30
GG_SEATNULL_BODY(0074FF30)

// FUNCTION: GAMEMD 0x0075E690
GG_SEAT0A_BODY(007F0D3C)

// FUNCTION: GAMEMD 0x0075E6A0
GG_SEAT0A_BODY(007E4DD8)

// FUNCTION: GAMEMD 0x0076F090
GG_SEAT2_BODY(007F72C4)

// FUNCTION: GAMEMD 0x0076F0C0
GG_SEAT2_BODY(007F72D8)

