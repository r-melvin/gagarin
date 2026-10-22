// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x65D430: a four-instruction body,
//   `MOV EAX,ECX; MOV [EAX+4],0; MOV [EAX],<vtable>; RET`. The member at +4
//   is cleared before the vtable is seated at +0 and the object is returned
//   in EAX. The vtable is rc_ptr_base's (0x7F094C; its complete object
//   locator 0x8087C0 names `.?AVrc_ptr_base@@`).
//
//   This family once held 77 sibling bodies of the same shape: the
//   constructors of the TClassFactory<T> instantiations. Those now live in
//   class_factory.cpp as the real member-initialiser constructor
//   `TClassFactory() : RefCount(0) {}`, which VC6 compiles to exactly this
//   store order (clear +4, then seat the vptr). That disproves the earlier
//   reading that the store order rules out a constructor.
//
//   rc_ptr_base 0x65D430 stays on the `VtableObj<traits>::Init` stand-in
//   below until rc_ptr_base has its own class model: the stand-in carries the
//   vtable as an explicit member instead of a compiler-managed vptr.
#ifndef GG_MATCH_CORE_VECTOR_VTABLE_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_VTABLE_CTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The object this family seats a vtable into. The vtable pointer is an
// explicit member, not a compiler-managed one, for the reason given above.
template<class T>
struct VtableObj
{
    char* Vptr;    // +0x0000
    int   Field4;  // +0x0004

    VtableObj* Init()
    {
        this->Field4 = 0;
        this->Vptr   = T::Vtable();
        return this;
    }
};

// The retail vtable seated by the one remaining instantiation.
// VTABLE: GAMEMD 0x7F094C -- rc_ptr_base
extern char VT_007F094C;

#endif  // GG_MATCH_CORE_VECTOR_VTABLE_CTOR_FAMILY_METHODS_H
