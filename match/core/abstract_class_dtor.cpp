// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x4101F0 reinstalls the four AbstractClass vptrs and returns.
#include "../_layout/abstract_class.h"
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

// FUNCTION: GAMEMD 0x4101F0
AbstractClass::~AbstractClass()
{
    _vtable_IPersistStream = &VT_007E1F50;
    _vtable_IRTTITypeInfo = &VT_007E1F34;
    _vtable_INoticeSink = &VT_007E1F2C;
    _vtable_INoticeSource = &VT_007E1F24;
}
