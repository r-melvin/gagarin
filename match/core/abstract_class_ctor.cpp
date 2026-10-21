// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native AbstractClass constructor at 0x410170. The 71-byte body retains
// the existing partial match: VC6 places the zero-register initialization
// after the first two volatile vptr stores; retail places it before them.
// Migrating the opaque host to this constructor preserves its COFF bytes and
// relocation offsets. This function remains partial, not a new exact match.
#include "../_layout/abstract_class.h"

// VTABLE: GAMEMD 0x007E1FBC
extern char VT_007E1FBC;
// VTABLE: GAMEMD 0x007E1FB4
extern char VT_007E1FB4;
// VTABLE: GAMEMD 0x007E1F50
extern char VT_007E1F50;
// VTABLE: GAMEMD 0x007E1F34
extern char VT_007E1F34;
// VTABLE: GAMEMD 0x007E1F2C
extern char VT_007E1F2C;
// VTABLE: GAMEMD 0x007E1F24
extern char VT_007E1F24;

GG_STATIC_ASSERT(offsetof(AbstractClass, _vtable_IPersistStream) == 0x00);
GG_STATIC_ASSERT(offsetof(AbstractClass, _vtable_IRTTITypeInfo) == 0x04);
GG_STATIC_ASSERT(offsetof(AbstractClass, _vtable_INoticeSink) == 0x08);
GG_STATIC_ASSERT(offsetof(AbstractClass, _vtable_INoticeSource) == 0x0C);

// FUNCTION: GAMEMD 0x410170
AbstractClass::AbstractClass()
{
    *(char* volatile*)&_vtable_INoticeSink = &VT_007E1FBC;
    *(char* volatile*)&_vtable_INoticeSource = &VT_007E1FB4;

    unknown_18 = 0;
    RefCount = 0;
    Dirty = 0;

    // The flag read is volatile so it cannot drift past the -1 store, and the
    // -1 store is volatile so it cannot be hoisted ahead of the read - retail
    // has `MOV CL,[EAX+0x14]; AND CL,0xF8; MOV [EAX+0x10],-1` in that order and
    // both plain forms move it.
    char flags = *(volatile char*)&AbstractFlags & 0xF8;

    *(volatile int*)&UniqueID = -1;

    _vtable_IPersistStream = &VT_007E1F50;
    _vtable_IRTTITypeInfo = &VT_007E1F34;
    _vtable_INoticeSink = &VT_007E1F2C;
    _vtable_INoticeSource = &VT_007E1F24;

    *(unsigned char*)&AbstractFlags = flags;

}
