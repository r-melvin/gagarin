// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 17 remaining four-byte-element resize bodies retain address-scoped
// views until their actual template classes are integrated. Recovered entries
// are bound in their native specialization implementations.
// Entry-origin spans are 0xB0 bytes. Instructions confirm Items+4, Capacity+8,
// initialization flag+C, ownership flag+D, live count+10 and Clear slot+C.
// Original source ownership and TU grouping are not established by this sweep.
//
// The source keeps the base resize as an inline call and clamps the count only
// on success. The capacity-zero branch dispatches Clear; allocation failure
// returns false. The ownership expression retains the verified short-circuit
// term so VC6 schedules SETZ and the pointer/capacity stores as retail does.
// These views remain verified under /O2 /DNDEBUG /Gy /GX.

#include "vector_resize_family_methods.h"

// FUNCTION: GAMEMD 0x49EA70
bool VectorResizeFamily::FUN_49EA70(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x49ED30
bool VectorResizeFamily::FUN_49ED30(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4A13C0
bool VectorResizeFamily::FUN_4A13C0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4E9840
bool VectorResizeFamily::FUN_4E9840(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4EA1C0
bool VectorResizeFamily::FUN_4EA1C0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4EE360
bool VectorResizeFamily::FUN_4EE360(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4F2A60
bool VectorResizeFamily::FUN_4F2A60(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5AC820
bool VectorResizeFamily::FUN_5AC820(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5AD010
bool VectorResizeFamily::FUN_5AD010(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5C5510
bool VectorResizeFamily::FUN_5C5510(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5D0C60
bool VectorResizeFamily::FUN_5D0C60(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5D0EC0
bool VectorResizeFamily::FUN_5D0EC0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5D8730
bool VectorResizeFamily::FUN_5D8730(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x627F90
bool VectorResizeFamily::FUN_627F90(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x69C890
bool VectorResizeFamily::FUN_69C890(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x6B15F0
bool VectorResizeFamily::FUN_6B15F0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x6B8400
bool VectorResizeFamily::FUN_6B8400(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}
