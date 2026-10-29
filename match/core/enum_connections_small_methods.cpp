// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x49FFF0, 0x4A0160, 0x4A0180, 0x4A0990, 0x4A0AF0, 0x4A0B10.
//
// Small IEnumConnections / IEnumConnectionPoints bodies: AddRef, Skip and Reset.
// Both enumerators keep a cursor that Skip advances and Reset zeroes.
// Address index: 0x49FFF0 EnumConnectionsClass::AddRef, 0x4A0160 ::Skip,
// 0x4A0180 ::Reset, 0x4A0990 EnumConnectionPointsClass::AddRef, 0x4A0AF0 ::Skip,
// 0x4A0B10 ::Reset.

#include "../_layout/enum_connections_class.h"
#include "../_layout/enum_connection_points_class.h"

// GLOBAL: GAMEMD 0xABCD3C - live COM-object counter.
extern int DAT_00ABCD3C;

// FUNCTION: GAMEMD 0x49FFF0
ULONG __stdcall EnumConnectionsClass::AddRef()
{
    DAT_00ABCD3C++;
    return InterlockedIncrement((LONG*)&RefCount);
}

// FUNCTION: GAMEMD 0x4A0160
HRESULT __stdcall EnumConnectionsClass::Skip(ULONG cConnections)
{
    Index += cConnections;
    return 0;
}

// FUNCTION: GAMEMD 0x4A0180
HRESULT __stdcall EnumConnectionsClass::Reset()
{
    Index = 0;
    return 0;
}

// FUNCTION: GAMEMD 0x4A0990
ULONG __stdcall EnumConnectionPointsClass::AddRef()
{
    DAT_00ABCD3C++;
    return InterlockedIncrement((LONG*)&RefCount);
}

// FUNCTION: GAMEMD 0x4A0AF0
HRESULT __stdcall EnumConnectionPointsClass::Skip(ULONG cConnections)
{
    Index += cConnections;
    return 0;
}

// FUNCTION: GAMEMD 0x4A0B10
HRESULT __stdcall EnumConnectionPointsClass::Reset()
{
    Index = 0;
    return 0;
}
