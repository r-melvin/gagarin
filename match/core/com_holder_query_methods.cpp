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
// SCHEDULING DELTA (status partial, 92.5% - 49/53, was 86.8%). Two residual spots, both
// instruction order rather than content. In the success epilogue retail is
// `POP EBX; MOV EAX,EDI` and we emit those two the other way round. On the
// empty-source path retail materialises the constant into the HRESULT's own
// register first (`MOV EDI,0x80004002; MOV EAX,EDI`) while we fold it straight
// into EAX, one instruction shorter. Nine phrasings were tried: assigning the
// constant before the release block, initialising `hr` at its declaration,
// routing it through a second local, a redundant `if (hr)` before the return,
// volatile reads of the member on either or both arms, if/else instead of early
// returns, and the inverted `hr >= 0` test. Every one of them lands on exactly
// 86.8% or worse. Thirteen more were measured in one compile since: the
// constant as the declaration initialiser, assigned before the release guard,
// returned as the assignment expression, carried in a second local live across
// the call, the release written through the member with no local, a single
// trailing return for the empty path, a full if/else with one exit (13.2%), a
// volatile-qualified `hr` (24.1%), and an inline-asm pin (0.0%) - all 86.8% or
// worse except one.
//
// That one is the volatile *read* at the return, which is what the body now
// uses: 92.5%. It restores retail's two-instruction `<reg> = const; EAX =
// <reg>` shape, and with the multiset back in agreement the epilogue cascade
// disappears too. It does not reach 100% because retail's register is EDI and
// the volatile lvalue is a stack home, which also leaves the success
// epilogue's `POP EBX` / `MOV EAX,EDI` pair transposed. The cause is NOT the
// toolchain: our objects stamp @comp.id 0x000b20ff, i.e. build 8447, retail's
// exact backend.
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
                COM_RELEASE(bad);
            }

            Held = 0;

            return hr;
        }

        IUnk* prev = Held;
        IUnk* got  = (IUnk*)pv;

        if (prev) {
            COM_RELEASE(prev);
        }

        Held = got;

        return hr;
    }

    IUnk* old = Held;

    if (old) {
        Held = 0;
        COM_RELEASE(old);
    }

    hr = 0x80004002;

    // Retail keeps the HRESULT in EDI on every path and ends each one with
    // `MOV EAX,EDI`; cl folds the constant straight into EAX here because the
    // local is dead. Reading it back through a volatile lvalue restores the
    // two-instruction form (86.8% -> 92.5%). See the note above.
    return *(volatile long*)&hr;
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
                COM_RELEASE(bad);
            }

            Held = 0;

            return hr;
        }

        IUnk* prev = Held;
        IUnk* got  = (IUnk*)pv;

        if (prev) {
            COM_RELEASE(prev);
        }

        Held = got;

        return hr;
    }

    IUnk* old = Held;

    if (old) {
        Held = 0;
        COM_RELEASE(old);
    }

    hr = 0x80004002;

    // Retail keeps the HRESULT in EDI on every path and ends each one with
    // `MOV EAX,EDI`; cl folds the constant straight into EAX here because the
    // local is dead. Reading it back through a volatile lvalue restores the
    // two-instruction form (86.8% -> 92.5%). See the note above.
    return *(volatile long*)&hr;
}
