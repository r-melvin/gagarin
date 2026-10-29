// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4A00B0 and 0x4A0A50.
//
// Next of the two connection enumerators: copy up to the requested count of entries
// from the cursor onward, taking a reference on each, and report E_FAIL when none were
// handed out.
// PARTIAL: both bodies score 95% (only the position of the output-pointer add differs).
// Address index: 0x4A00B0 EnumConnectionsClass::Next, 0x4A0A50 EnumConnectionPointsClass::Next.

#include "../_layout/enum_connections_class.h"
#include "../_layout/enum_connection_points_class.h"

// FUNCTION: GAMEMD 0x4A00B0
HRESULT __stdcall EnumConnectionsClass::Next(ULONG cConnections, LPCONNECTDATA rgcd, ULONG* pcFetched)
{
    if (rgcd == 0)
        return E_POINTER;
    if (cConnections > 1) {
        if (pcFetched == 0)
            return E_INVALIDARG;
    }
    if (pcFetched)
        *pcFetched = 0;
    ULONG fetched = 0;
    ULONG i = 0;
    while (i < cConnections && Index < Connections.Count) {
        Connections.Items[Index].pUnk->AddRef();
        fetched++;
        i++;
        int index = Index++;
        *rgcd++ = Connections.Items[index];
    }
    if (pcFetched)
        *pcFetched = fetched;
    return fetched ? S_OK : E_FAIL;
}

// FUNCTION: GAMEMD 0x4A0A50
HRESULT __stdcall EnumConnectionPointsClass::Next(ULONG cConnections, LPCONNECTIONPOINT* ppCP, ULONG* pcFetched)
{
    if (ppCP == 0)
        return E_POINTER;
    if (cConnections > 1) {
        if (pcFetched == 0)
            return E_POINTER;
    }
    if (pcFetched)
        *pcFetched = 0;
    ULONG fetched = 0;
    ULONG i = 0;
    while (i < cConnections && Index < Points.Count) {
        Points.Items[Index]->AddRef();
        fetched++;
        i++;
        int index = Index++;
        *ppCP++ = Points.Items[index];
    }
    if (pcFetched)
        *pcFetched = fetched;
    return fetched ? S_OK : E_FAIL;
}
