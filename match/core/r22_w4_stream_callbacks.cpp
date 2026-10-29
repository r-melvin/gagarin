// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small callbacks read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI.
//   Address index: 0x759FA0, 0x75A2F0.

#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00759FA0
{
    char unknown_000[0x544];
    void (Obj_00759FA0::*Handler)();   // +0x544

    // FUNCTION: GAMEMD 0x759FA0 (__thiscall)
    void FUN_00759FA0();
};
GG_STATIC_ASSERT(offsetof(Obj_00759FA0, Handler) == 0x544);

// FUNCTION: GAMEMD 0x759FA0
// Tail-calls the handler stored at +0x544.
void Obj_00759FA0::FUN_00759FA0()
{
    (this->*Handler)();
}

// FUNCTION: GAMEMD 0x75A2F0
// Allocator callback: op 2 allocates, op 3 frees, op 4/5 return the pointer, op 6 stores -1.
void* __cdecl FUN_0075A2F0(int unused, int op, unsigned int* p, size_t n)
{
    switch (op) {
    case 2:
        return malloc(n);
    case 3:
        free(p);
        return 0;
    case 4:
    case 5:
        return p;
    case 6:
        *p = 0xFFFFFFFF;
    }
    return 0;
}
