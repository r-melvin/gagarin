// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x45AEA0 and 0x45AF20.

#include "com_holder_query_methods.h"

// FUNCTION: GAMEMD 0x45AEA0
//
// Three exits, and each drops the currently-held interface differently, which
// is why they are written out rather than folded:
//   - empty source: clear the field first, then release the saved pointer, and
//     report E_NOINTERFACE
//   - failed query: release first, then clear, and report the query's HRESULT
//   - success: release the old one and store the new
//
// The empty-source case is the *trailing* block: retail's `JZ` at 0x45AEAC
// jumps forward past the whole query, so the query is the fall-through and the
// guard is written positively. Leading with the empty case instead scores
// 11.3%.
//
// `pv` lands in the incoming argument's own stack slot (`LEA EDX,[ESP+0xC]`,
// read back later as `[ESP+0x10]` once EBX is pushed). That is VC6 reusing the
// parameter home once the parameter is dead, not the source writing through the
// argument - `source` is read exactly once, at the top.
//
// The HRESULT is held in a named local rather than returned directly from each
// branch: retail keeps it in EDI and ends every path with `MOV EAX,EDI`.
//
// Each branch captures the held pointer into its *own* named local. Reading the
// member directly in both arms lets VC6 hoist the one load above the `TEST EDI,
// EDI`, which then serves both blocks and removes the success block's `PUSH EBX`
// - 43.4%. Distinct locals defeat that partial-redundancy elimination and the
// two blocks come out as retail has them.
//
// PARTIAL: retail uses a different HRESULT register and epilogue ordering.
// Use an ordinary return; volatile reloads used only for scheduling are forbidden.
long ComHolder_0045AEA0::FUN_0045AEA0(IUnk** source)
{
    long   hr;
    IUnk*  from = *source;

    if (from != 0) {
        void* pv;

        hr = COM_QUERY(from, &DAT_00818858, &pv);

        if (hr < 0) {
            IUnk* bad = Held;

            if (bad) {
                COM_SLOT_08(bad);
            }

            Held = 0;

            return hr;
        }

        IUnk* prev = Held;
        IUnk* got  = (IUnk*)pv;

        if (prev) {
            COM_SLOT_08(prev);
        }

        Held = got;

        return hr;
    }

    IUnk* old = Held;

    if (old) {
        Held = 0;
        COM_SLOT_08(old);
    }

    hr = 0x80004002;

    return hr;
}

// FUNCTION: GAMEMD 0x45AF20
//
// The same helper for the second interface. Written out rather than shared.
long ComHolder_0045AEA0::FUN_0045AF20(IUnk** source)
{
    long   hr;
    IUnk*  from = *source;

    if (from != 0) {
        void* pv;

        hr = COM_QUERY(from, &DAT_00819088, &pv);

        if (hr < 0) {
            IUnk* bad = Held;

            if (bad) {
                COM_SLOT_08(bad);
            }

            Held = 0;

            return hr;
        }

        IUnk* prev = Held;
        IUnk* got  = (IUnk*)pv;

        if (prev) {
            COM_SLOT_08(prev);
        }

        Held = got;

        return hr;
    }

    IUnk* old = Held;

    if (old) {
        Held = 0;
        COM_SLOT_08(old);
    }

    hr = 0x80004002;

    return hr;
}
