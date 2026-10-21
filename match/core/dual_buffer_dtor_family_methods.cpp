// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Six address-scoped entries: three destructors and the three scalar-deleting
// destructors that wrap them. Each releases the two heap buffers the object
// owns, nulls both slots, and chains to the base destructor; the deleting
// form then frees the object itself when the caller asked for it. Ordered
// ascending by retail address.

#include "dual_buffer_dtor_family_methods.h"

// FUNCTION: GAMEMD 0x00552450
GG_DUALBUF_DTOR_BODY(00552450, 007ECF44, ((Straw*)this)->Straw::~Straw())

// FUNCTION: GAMEMD 0x005525F0
GG_DUALBUF_SDD_BODY(005525F0, 007ECF44, ((Straw*)self)->Straw::~Straw())

// FUNCTION: GAMEMD 0x0055C310
GG_DUALBUF_DTOR_BODY(0055C310, 007ED37C, ((Pipe*)this)->Pipe::~Pipe())

// FUNCTION: GAMEMD 0x0055C6D0
GG_DUALBUF_SDD_BODY(0055C6D0, 007ED37C, ((Pipe*)self)->Pipe::~Pipe())

// FUNCTION: GAMEMD 0x0055C780
GG_DUALBUF_DTOR_BODY(0055C780, 007ED394, ((Straw*)this)->Straw::~Straw())

// FUNCTION: GAMEMD 0x0055C990
GG_DUALBUF_SDD_BODY(0055C990, 007ED394, ((Straw*)self)->Straw::~Straw())
