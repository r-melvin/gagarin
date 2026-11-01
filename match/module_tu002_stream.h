// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Stream thread parameter prefix, proved by 407550/407680/407780.
#ifndef GG_MODULE_TU002_STREAM_H
#define GG_MODULE_TU002_STREAM_H
#include "small_misc40_methods.h"
struct StreamState_00407680
{
    // Shared stop: thread407680 created407610 reads407693/40775A;
    // caller407780 writes407797. Only the declaration is volatile.
    volatile int unknown_00;
    int unknown_04;
    // Shared completion: thread writes407690/407764/407774;
    // caller reads4077A1/4077B4 after creation407610.
    volatile int unknown_08;
    int unknown_0C;
    unsigned __int64 unknown_10;
    int unknown_18;
    int unknown_1C;
    Obj_00403820 unknown_20;
};
GG_STATIC_ASSERT(offsetof(StreamState_00407680, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(StreamState_00407680, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(StreamState_00407680, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(StreamState_00407680, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(StreamState_00407680, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(StreamState_00407680, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(StreamState_00407680) == 0x78);
#endif
