// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x473FC0 / 0x47AAB0 /
//   0x65CA70 / 0x65CB30 / 0x65D420 via the local Ghidra disassembly. The class
//   hierarchy, vtable slot order and member offsets come from the committed
//   model in ccfile_class.h (Handle @0x14, CCFileClass::Availability @0x68),
//   each reconfirmed here from the member-access instructions.
//
// File-open plumbing across the RawFileClass -> ... -> CCFileClass chain.
// Functions ordered ascending by retail address.

#include "ccfile_class.h"

// FUNCTION: GAMEMD 0x473C50  CCFileClass::Exists (__thiscall, ret 0x4)
// Four escalating ways for a file to exist — a cached yes, an open handle, a
// MIX directory entry, or the buffered base's own on-disk check — and the
// answer is cached in Availability either way (1 = present, 2 = absent).
// Retail parks the constant 1 in EBX and reuses it for both the flag store and
// every `return true`, which is what the repeated `Availability = 1;
// return true;` pairs produce.
bool CCFileClass::Exists(bool writeShared)
{
    if (Availability == 1)
        return true;

    if (HasHandle()) {
        Availability = 1;
        return true;
    }

    if (MixFileClass_Offset(GetFileName(), 0, 0, 0, 0)) {
        Availability = 1;
        return true;
    }

    if (BufferIOFileClass::Exists(false)) {
        Availability = 1;
        return true;
    }

    Availability = 2;
    return false;
}

// FUNCTION: GAMEMD 0x473FC0  CCFileClass::SetFileName (__thiscall)
// Renaming invalidates the cached MIX availability answer, then the base does
// the actual string work.
const char* CCFileClass::SetFileName(const char* pFileName)
{
    Availability = 0;
    return CDFileClass::SetFileName(pFileName);
}


// FUNCTION: GAMEMD 0x65CA70  RawFileClass::CDCheck (__thiscall)
// A real file on disk never needs the CD prompt, so the override is empty —
// retail is the single instruction `RET 0xC`.
void RawFileClass::CDCheck(unsigned long code, bool b, const char* f)
{
}

// FUNCTION: GAMEMD 0x65CB30  RawFileClass::OpenEx (__thiscall)
// Name-then-open, both dispatched *virtually* through this object (slots +0x08
// and +0x1C), so a derived class's overrides win.
bool RawFileClass::OpenEx(const char* pFileName, FileAccessMode a)
{
    SetFileName(pFileName);
    return Open(a);
}

// FUNCTION: GAMEMD 0x65D420  RawFileClass::HasHandle (__thiscall)
// INVALID_HANDLE_VALUE (-1), not null, is the "closed" sentinel here.
bool RawFileClass::HasHandle()
{
    return Handle != (void*)-1;
}
