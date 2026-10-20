// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x71F680 (name from the
//   YRpp method map, consult-only).

#include "tevent_class_attach_type_methods.h"

// FUNCTION: GAMEMD 0x71F680
//
// Five independent membership tests over the event kind, each contributing one
// bit. Four are dense enough that the compiler emits a byte-indexed jump table
// (range check, index byte, JMP [table]); the third set has only two members
// and is a pair of compares. The first set assigns (MOV ESI,1) rather than ORs
// because the accumulator is still known to be zero there.
unsigned int __fastcall TEventClass_0071F680::GetAttachType(int kind)
{
    unsigned int bits = 0;

    switch (kind) {
    case 0x00: case 0x01: case 0x04: case 0x08: case 0x18: case 0x19:
    case 0x1A: case 0x1F: case 0x35: case 0x36: case 0x3B:
        bits = 1;
        break;
    }

    switch (kind) {
    case 0x00: case 0x01: case 0x02: case 0x04: case 0x06: case 0x07:
    case 0x08: case 0x1D: case 0x21: case 0x22: case 0x23: case 0x26:
    case 0x27: case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2C:
    case 0x30: case 0x31:
        bits |= 2;
        break;
    }

    if (kind == 0x08 || kind == 0x18)
        bits |= 4;

    switch (kind) {
    case 0x03: case 0x05: case 0x08: case 0x09: case 0x0A: case 0x0B:
    case 0x0C: case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x14: case 0x15: case 0x16: case 0x1E: case 0x20: case 0x34:
    case 0x37: case 0x38: case 0x39: case 0x3A:
        bits |= 8;
        break;
    }

    switch (kind) {
    case 0x08: case 0x0D: case 0x0E: case 0x17: case 0x1B: case 0x1C:
    case 0x24: case 0x25: case 0x2D: case 0x2E: case 0x2F: case 0x32:
    case 0x33: case 0x3C: case 0x3D:
        bits |= 0x10;
        break;
    }

    return bits;
}
