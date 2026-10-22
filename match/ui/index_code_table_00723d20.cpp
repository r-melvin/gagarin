// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// A free __fastcall table lookup at 0x723D20: an index below 0x3C selects one
// of twenty result codes through a byte-indexed jump table; any other index
// gives 0. Its callers and the meaning of the codes are not recovered (no
// direct code references). The case blocks are written in retail's block
// order (0x723D38 onwards).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy

// FUNCTION: GAMEMD 0x723D20
int __fastcall FUN_00723D20(unsigned int index)
{
    switch (index) {
    case 0x00:
    case 0x39:
        return 0x0F;
    case 0x04:
        return 0x13;
    case 0x22:
        return 0x20;
    case 0x0C:
    case 0x26:
        return 0x16;
    case 0x27:
    case 0x28:
        return 0x1D;
    case 0x05:
    case 0x06:
    case 0x0D:
    case 0x20:
    case 0x2A:
    case 0x32:
        return 0x0A;
    case 0x01:
    case 0x03:
    case 0x0F:
    case 0x10:
    case 0x3B:
        return 0x09;
    case 0x14:
        return 0x0D;
    case 0x0B:
        return 0x12;
    case 0x11:
        return 0x14;
    case 0x12:
        return 0x0C;
    case 0x18:
        return 0x04;
    case 0x19:
        return 0x03;
    case 0x1A:
        return 0x02;
    case 0x1B:
        return 0x01;
    case 0x2E:
    case 0x2F:
    case 0x38:
    case 0x3A:
        return 0x24;
    case 0x08:
        return 0x25;
    case 0x33:
        return 0x29;
    case 0x34:
        return 0x2A;
    }
    return 0;
}
