// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x437F50.

#include "com_holder_ctor_methods.h"
#include "pk_blow_pipes.h"

// FUNCTION: GAMEMD 0x437F50
//
// Construct the holder: create the object as IUnknown, run it, query it for the
// interface the holder actually wants, and release the IUnknown either way. The
// constructor returns the holder rather than the HRESULT, so a failure leaves the
// interface null and is only reported.
//
// E_NOINTERFACE is swallowed. Every other failure goes to the reporter, which
// makes "this build does not have that component" a quiet outcome and everything
// else loud.
//
// The out-parameter stays address-taken and is re-read at each use — retail
// reloads `[ESP+8]` for the OleRun call, the query and the release rather than
// holding it. That is the opposite of 0x46B050, where retail holds the same kind
// of value in a register; the disassembly says which, and here it reloads.
BlockCipherView::BlockCipherView()
{
    IUnk_00437F50* created;

    this->Interface = 0;

    long hr = CoCreateInstance(rclsid_007E9500, 0, 7, riid_00817BC0,
                               (void**)&created);
    if (hr >= 0) {
        hr = OleRun(created);
        if (hr >= 0) {
            hr = created->Vtbl->QueryInterface(created, riid_00818C08,
                                               (void**)this);
        }
        created->Vtbl->Release(created);
    }

    if (hr < 0 && hr != 0x80004002) {
        FUN_007DC720(hr);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x818C08
extern const char riid_00818C08[16] = {0, 49, 17, -32, 124, 106, -47, 17, -74, -7, 0, -96, 36, -35, -81, -47};
// GLOBAL: GAMEMD 0x7E9500
extern const char rclsid_007E9500[16] = {16, -83, 64, 20, -88, 106, -47, 17, -74, -7, 0, -96, 36, -35, -81, -47};
// END defined globals
