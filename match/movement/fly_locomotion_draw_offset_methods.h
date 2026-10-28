// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x4CF830 queries IID 0x822410 and calls interface slot +0x0C.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_DRAW_OFFSET_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_DRAW_OFFSET_METHODS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/com_interfaces.h"
#include "../core/frame_counter.h"
// GLOBAL: GAMEMD 0x822410
extern const IID IID_00822410;
// LIBRARY: GAMEMD 0x7DC720 (decl; reloc)
void __stdcall FUN_007DC720(long hr);
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc)
extern "C" float __cdecl FUN_004CACB0(double angle);

// Scope owner of the reference returned by QueryInterface. Native 0x4CF830
// writes the result before releasing; the destructor preserves this order.
struct FlyDrawInterfaceHolder
{
    IFlyControl* Held;
    // Declaration: GAMEMD 0x4D0430 -- one-pointer release helper, ECX=this.
    void Release();
    // FUNCTION: GAMEMD 0x4D0400 -- comparison with a null literal.
    bool IsNull(int null) const;
    ~FlyDrawInterfaceHolder() throw()
    {
        if (Held != 0) Held->Release();
    }
};
GG_STATIC_ASSERT(offsetof(FlyDrawInterfaceHolder, Held) == 0);
GG_STATIC_ASSERT(sizeof(FlyDrawInterfaceHolder) == 4);
#endif
