// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x49FF80 and 0x4A0920 (compare the id against the enumerator's own id and IUnknown).
//
// QueryInterface of the two connection enumerators.
// Address index: 0x49FF80 EnumConnectionsClass::QueryInterface,
// 0x4A0920 EnumConnectionPointsClass::QueryInterface.

#include <string.h>
#include "../_layout/enum_connections_class.h"
#include "../_layout/enum_connection_points_class.h"

#pragma intrinsic(memcmp)

// GLOBAL: GAMEMD 0x7F7C90 - IID_IUnknown
extern const GUID DAT_007F7C90;
// GLOBAL: GAMEMD 0x7F7CB0 - IID_IEnumConnections
extern const GUID DAT_007F7CB0;
// GLOBAL: GAMEMD 0x7F7CE0 - IID_IEnumConnectionPoints
extern const GUID DAT_007F7CE0;

// FUNCTION: GAMEMD 0x49FF80
HRESULT __stdcall EnumConnectionsClass::QueryInterface(REFIID riid, void** ppvObject)
{
    if (ppvObject == 0)
        return E_POINTER;
    *ppvObject = 0;
    if (memcmp(&riid, &DAT_007F7C90, sizeof(GUID)) == 0)
        *ppvObject = this;
    if (memcmp(&riid, &DAT_007F7CB0, sizeof(GUID)) == 0)
        *ppvObject = this;
    if (*ppvObject) {
        AddRef();
        return 0;
    }
    return E_NOINTERFACE;
}

// FUNCTION: GAMEMD 0x4A0920
HRESULT __stdcall EnumConnectionPointsClass::QueryInterface(REFIID riid, void** ppvObject)
{
    if (ppvObject == 0)
        return E_POINTER;
    void* result = 0;
    if (memcmp(&riid, &DAT_007F7CE0, sizeof(GUID)) == 0 || memcmp(&riid, &DAT_007F7C90, sizeof(GUID)) == 0)
        result = this;
    *ppvObject = result;
    if (result) {
        AddRef();
        return 0;
    }
    return E_NOINTERFACE;
}
