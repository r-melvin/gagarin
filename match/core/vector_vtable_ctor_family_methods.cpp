// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x65D430.
//
//   One explicit instantiation: the traits type names rc_ptr_base's retail
//   vtable, and `template struct VtableObj<Vtbl_rc_ptr_base>;` makes the
//   compiler generate the 0x10-byte body at the annotated address: clear the
//   member at +4, seat the vtable at +0, return the object in EAX. See the
//   header for why this stand-in remains.

#include "vector_vtable_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x0065D430
// rc_ptr_base -- seats retail vtable 0x007F094C; locator 0x008087C0 -> type
//   descriptor 0x00827F78 `.?AVrc_ptr_base@@`.
struct Vtbl_rc_ptr_base { static char* Vtable() { return &VT_007F094C; } };
template struct VtableObj<Vtbl_rc_ptr_base>;

// Layout asserted on the instantiation. The assert has to follow an explicit instantiation: VC6 fails to re-parse
// the template body when offsetof is what first instantiates it, and it will
// not take a template-id as offsetof's first argument either, hence the
// typedef.
typedef VtableObj<Vtbl_rc_ptr_base> GgVtableObjRep;
GG_STATIC_ASSERT(offsetof(GgVtableObjRep, Vptr)   == 0x0);
GG_STATIC_ASSERT(offsetof(GgVtableObjRep, Field4) == 0x4);
GG_STATIC_ASSERT(sizeof(GgVtableObjRep)           == 0x8);
