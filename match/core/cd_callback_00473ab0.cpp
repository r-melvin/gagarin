// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-origin 0x473AB0 and the RTTI-backed CD table at 0x7E4C30.
// RTTI identifies CD as the callback-table owner; its full layout and method
// names are not recovered. The outer receiver class remains unknown.
#include "../_rt/gg_static_assert.h"
#include "../_layout/global_0081c1d0.h"
#include <stddef.h>
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);

// Slot-0 call view: ECX receiver and one stack dword. The AL result is
// discarded here; void is a caller ABI view, not a recovered CD signature.
struct CallbackView_00473AB0 { virtual void first(int value) = 0; };
// This caller reserves eight stack bytes and writes only the first dword.
// This stack view does not establish sizeof(CD) or its complete layout.
struct CallbackStorage_00473AB0 { void* vtable; unsigned char unknown_04[4]; };
GG_STATIC_ASSERT(offsetof(CallbackStorage_00473AB0, vtable) == 0);
GG_STATIC_ASSERT(offsetof(CallbackStorage_00473AB0, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(CallbackStorage_00473AB0) == 8);

typedef void (CallbackView_00473AB0::*CallbackCall_00473AB0)(int);
struct CallbackSlots_00473AB0 { CallbackCall_00473AB0 first; };
GG_STATIC_ASSERT(sizeof(CallbackCall_00473AB0) == 4);
GG_STATIC_ASSERT(offsetof(CallbackSlots_00473AB0, first) == 0);

// VTABLE: GAMEMD 0x007E4C30 -- CD slots: 0x4790E0, 0x479110, 0x4791F0.
// The extern is an address binding, not a reconstructed emitted CD vtable.
extern "C" void* DAT_007E4C30;
// The outer receiver and three ignored stack words are ABI views only.

struct FUN_00473AB0_View
{
    unsigned char unknown_00[4];
    unsigned char unknown_04;
    unsigned char unknown_05[3];
    void FUN_00473AB0(int unknown_08, int unknown_0C, int unknown_10);
};
GG_STATIC_ASSERT(offsetof(FUN_00473AB0_View, unknown_04) == 4);

// FUNCTION: GAMEMD 0x00473AB0 (40 bytes, ending RET 0x0c)
void FUN_00473AB0_View::FUN_00473AB0(int, int, int)
{
    if (unknown_04 == 0) {
        CallbackStorage_00473AB0 callback;
        callback.vtable = &DAT_007E4C30;
        ((CallbackView_00473AB0*)&callback)->first(g_FileSearchMode);
    }
}
