// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared notice interface: retail RTTI at the AbstractClass and TabClass tables.
#include "../_rt/gg_static_assert.h"

#ifndef GG_MATCH_LAYOUT_INOTICESINK_DEFINED
#define GG_MATCH_LAYOUT_INOTICESINK_DEFINED
// VTABLE: GAMEMD 0x7E1FBC (1 slot, _purecall). Slot 0 overrides return false
// with RET 8 (0x410580).
class INoticeSink
{
public:
    virtual bool Notice(int id, int arg) = 0;            // 0
};
GG_STATIC_ASSERT(sizeof(INoticeSink) == 4);
#endif

