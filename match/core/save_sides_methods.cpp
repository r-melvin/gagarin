// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6805F0 (name from the
//   YRpp method map).

#include "save_sides_methods.h"

// FUNCTION: GAMEMD 0x6805F0
//
// Serialise the side vector: the element count first, then each element via
// its IPersistStream (QueryInterface -> OleSaveToStream -> Release). Any
// failing HRESULT ends the walk and is returned as-is; the count is re-read
// from its stack slot every iteration because its address escaped into the
// Write call.
long __fastcall Save_Sides(Stream_006805F0* stream, SideVector_006805F0* sides)
{
    int count = sides->Count;
    long hr = STREAM_WRITE(stream, &count, 4);
    if (hr < 0)
        return hr;

    for (int i = 0; i < count; ++i) {
        Persist_006805F0* persist = 0;
        hr = COM_QUERY(sides->Items[i], &IID_IPersistStream_007F7C80, (void**)&persist);
        if (hr < 0)
            return hr;
        hr = OleSaveToStream(persist, stream);
        if (hr < 0)
            return hr;
        hr = COM_SLOT_08(persist);
        if (hr < 0)
            return hr;
    }
    return 0;
}
