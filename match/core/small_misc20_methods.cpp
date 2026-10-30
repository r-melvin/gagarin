// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc20_methods.h"
#include "small_misc12_methods.h"
#include "../audio/audio_stop_methods.h"
#include "../platform/pk_blow_pipes.h"
#include "../platform/com_holder_ctor_methods.h"

// FUNCTION: GAMEMD 0x408200
void __cdecl FUN_00408200()
{
    if (DAT_0087E81C == 0) {
        return;
    }

    ListNode* node = (&DAT_0087E810)->FUN_004073C0();

    if (node == 0) {
        return;
    }

    do {
        // PARTIAL: VC6 hoists the next call's `this` load into the middle of
        // this increment, where retail keeps the read-modify-write together.
        ++((Counted_00408200*)node)->at88;

        node = (node)->FUN_004073E0();
    } while (node);
}

// FUNCTION: GAMEMD 0x408390
// Same list walk as 0x408200, calling into each entry's sub-object at +0x10
// rather than bumping a counter. The gate and the empty-list check are both
// early returns, so only a non-empty armed list does any work.
void __cdecl FUN_00408390()
{
    if (DAT_0087E81C == 0) {
        return;
    }

    ListNode* node = (&DAT_0087E810)->FUN_004073C0();

    if (node == 0) {
        return;
    }

    do {
        FUN_00407170(&((Holder_00408390*)node)->at14->unknown_10, 0);

        node = (node)->FUN_004073E0();
    } while (node);
}

// FUNCTION: GAMEMD 0x4083D0
// The 0x408390 walk again, passing 0x4000 instead of zero. Written out longhand
// rather than parameterised, per the family rule.
void __cdecl FUN_004083D0()
{
    if (DAT_0087E81C == 0) {
        return;
    }

    ListNode* node = (&DAT_0087E810)->FUN_004073C0();

    if (node == 0) {
        return;
    }

    do {
        FUN_00407170(&((Holder_00408390*)node)->at14->unknown_10, 0x4000);

        node = (node)->FUN_004073E0();
    } while (node);
}

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

// FUNCTION: GAMEMD 0x437FC0
BlockCipherView::~BlockCipherView()
{
    if (Interface) {
        IFACE_CALL(Interface, 0x8);
    }
}

// FUNCTION: GAMEMD 0x437FD0
// The two arguments reach the interface in the opposite order to the one they
// arrive in: retail pushes the first parameter first, so it ends up rightmost.
void BlockCipherView::Key(const void* key, int length)
{
    if (Interface == 0) {
        FUN_007DC720(0x80004003);
    }

    IFACE_CALL2(Interface, 0xC, length, (int)key);
}

// FUNCTION: GAMEMD 0x438000
int BlockCipherView::Forward(const void* in, int length, void* out)
{
    if (Interface == 0) {
        FUN_007DC720(0x80004003);
    }

    IFACE_CALL3(Interface, 0x18, length, (int)in, (int)out);

    return length;
}

// FUNCTION: GAMEMD 0x438030
int BlockCipherView::Reverse(const void* in, int length, void* out)
{
    if (Interface == 0) {
        FUN_007DC720(0x80004003);
    }

    IFACE_CALL3(Interface, 0x1C, length, (int)in, (int)out);

    return length;
}
