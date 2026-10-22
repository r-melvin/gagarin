// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native AbstractClass constructor at 0x410170. PARTIAL, 12.5% (2/16), plain
// member stores. Retail keeps two interface-base vptr stores that are later
// overwritten and clears the low flag bits with a byte AND; this plain body
// lets cl drop the two dead stores (14 vs 16 instructions) and emits a dword
// AND, so everything after the zeroing XOR is shifted.
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
    _vtable_INoticeSink = &VT_007E1FBC;
    _vtable_INoticeSource = &VT_007E1FB4;

    unknown_18 = 0;
    RefCount = 0;
    Dirty = 0;
    UniqueID = -1;
    AbstractFlags &= ~7;

    _vtable_IPersistStream = &VT_007E1F50;
    _vtable_IRTTITypeInfo = &VT_007E1F34;
    _vtable_INoticeSink = &VT_007E1F2C;
    _vtable_INoticeSource = &VT_007E1F24;

}
