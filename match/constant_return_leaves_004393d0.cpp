// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail gamemd.exe v1.001 instructions at 0x004393D0 and 0x004393E0 each
// return a fixed immediate in EAX and execute RET. Both addresses are stored
// in separate read-only data cells at 0x007E3D40 and 0x007E3D3C.

// FUNCTION: GAMEMD 0x004393D0
unsigned int __stdcall FUN_004393D0()
{
    return 0x5C;
}

// FUNCTION: GAMEMD 0x004393E0
unsigned int __stdcall FUN_004393E0()
{
    return 0x44;
}
