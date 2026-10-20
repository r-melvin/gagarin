// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "guarded_forward_methods.h"

// FUNCTION: GAMEMD 0x437FC0
void Holder_IFace::FUN_00437FC0()
{
    if (Held) {
        IFACE_CALL(Held, 0x8);
    }
}

// FUNCTION: GAMEMD 0x45A160
void Holder_IFace::FUN_0045A160()
{
    if (Held) {
        IFACE_CALL(Held, 0x8);
    }
}

// FUNCTION: GAMEMD 0x45A170
void Holder_IFace::FUN_0045A170()
{
    if (Held) {
        IFACE_CALL(Held, 0x4);
    }
}

// FUNCTION: GAMEMD 0x465B30
void Owned_465B30::FUN_00465B30()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x465B70
void Owned_465B70::FUN_00465B70()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x465BB0
void Owned_465BB0::FUN_00465BB0()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x465BF0
void Owned_465BF0::FUN_00465BF0()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x465C30
void Owned_465C30::FUN_00465C30()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x465C70
void Owned_465C70::FUN_00465C70()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}
