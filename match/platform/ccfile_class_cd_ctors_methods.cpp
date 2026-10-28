// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at each address below; the base
//   constructor 0x431B20 is called out of line, IsDisabled (+0x54) is cleared,
//   the vtable 0x7E1668 is seated and, where a name is given, 0x47AE10 stores it.
//
//   0x47A9D0  CDFileClass::CDFileClass(const char*)
//   0x47AA00  CDFileClass::CDFileClass(const Wstring&)
//   0x47AA30  CDFileClass::CDFileClass()

#include "ccfile_class.h"
#include "../core/string_class.h"

// FUNCTION: GAMEMD 0x47A9D0
CDFileClass::CDFileClass(const char* pFileName) : IsDisabled(false)
{
    CDFileClass::SetFileName(pFileName);
}

// FUNCTION: GAMEMD 0x47AA00
CDFileClass::CDFileClass(const Wstring& name) : IsDisabled(false)
{
    const char* filename = name.FUN_007B5440();
    CDFileClass::SetFileName(filename);
}

// FUNCTION: GAMEMD 0x47AA30
CDFileClass::CDFileClass() : IsDisabled(false)
{
}
