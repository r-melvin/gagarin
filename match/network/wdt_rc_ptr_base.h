// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   rc_ptr_base (vtable 0x7F094C) and the rc_ptr<T> template over it; see
//   wdt_rc_ptr.h for what the retail bodies do. This header holds only the
//   pointer classes, so a unit that models ReferenceCounted its own way (the
//   World Domination Tour data classes) can share them.
#ifndef GG_MATCH_NETWORK_WDT_RC_PTR_BASE_H
#define GG_MATCH_NETWORK_WDT_RC_PTR_BASE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7F094C (rc_ptr_base)
class rc_ptr_base
{
public:
    // FUNCTION: GAMEMD 0x65D430 (decl; reloc)
    rc_ptr_base();
    // FUNCTION: GAMEMD 0x65D460 (decl; reloc)
    virtual ~rc_ptr_base();
    // FUNCTION: GAMEMD 0x65D480 (decl; reloc) -- RET 4.
    void Assign(void* pointer);

    void* Pointer;   // +0x04
};
GG_STATIC_ASSERT(offsetof(rc_ptr_base, Pointer) == 0x04);
GG_STATIC_ASSERT(sizeof(rc_ptr_base) == 0x08);

template <class T>
class rc_ptr : public rc_ptr_base
{
public:
    rc_ptr() {}
    rc_ptr(T* pointer) { Assign(pointer); }
    rc_ptr(const rc_ptr<T>& other) { Assign(other.Pointer); }
    virtual ~rc_ptr() {}
    rc_ptr<T>& operator=(const rc_ptr<T>& other)
    {
        Assign(other.Pointer);
        return *this;
    }
    T* operator->() const { return static_cast<T*>(Pointer); }
    T* Get() const { return static_cast<T*>(Pointer); }
    bool operator==(const rc_ptr<T>& other) const { return Pointer == other.Pointer; }
    bool operator!=(const rc_ptr<T>& other) const { return Pointer != other.Pointer; }
};

#endif  // GG_MATCH_NETWORK_WDT_RC_PTR_BASE_H
