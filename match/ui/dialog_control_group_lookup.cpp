// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x600CA0,
//   0x6015E0, 0x601D20 and 0x602490. Every constant below was extracted from
//   the disassembly in comparison order; none of it is guessed.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x600CA0  FUN_00600CA0 (__fastcall)
//   FUNCTION: GAMEMD 0x6015E0  FUN_006015E0 (__fastcall)
//   FUNCTION: GAMEMD 0x601D20  FUN_00601D20 (__fastcall)
//   FUNCTION: GAMEMD 0x602490  FUN_00602490 (__fastcall)
//   GLOBAL:   GAMEMD 0xAC1B00  the dialog-type hash table
//   GLOBAL:   GAMEMD 0xA8B238  the session object the last guard reads
//   GLOBAL:   GAMEMD 0x7E13B4  __imp__GetDlgCtrlID

#include "dialog_control_group_lookup.h"

// The hash-table probe all four bodies open with, expanded inline at each
// entry. It is the helper proven at 0x602B90/0x603240: it must be forced
// inline and it must keep the inner `n ? &n->Value : 0` guard, because that
// guard is the first of retail's two null tests on the hit path and the
// caller's own `p ? p->Field6C : 0` is the second. Dropping either one loses
// the `ADD EAX,4` block.
__forceinline static MapValue_00602B90* FindValue(int nKey)
{
    if (DAT_00AC1B00.Count != 0)
    {
        unsigned hash = DAT_00AC1B00.Hash(&nKey);
        MapNode_00602B90* node =
            DAT_00AC1B00.Buckets[hash & ((1u << DAT_00AC1B00.Shift) - 1u)];

        while (node != 0)
        {
            if (node->Key == nKey)
                return node ? &node->Value : 0;

            node = node->Next;
        }
    }

    return 0;
}

// PARTIAL (34.8% by the instruction differ, 671/1718 bytes identical).
// The instruction stream is retail's except for the placement of the return
// blocks: retail carries five of them, one laid out inline at the fallthrough
// of each clause that produces it, and cl 8804 sinks them to the end of the
// function and folds the four `return 0x1E` copies into one. The full-stream
// multiset differs by exactly {jne,pop,pop,pop,mov,ret} retail-only against
// {je,je,je} ours — one whole return block and three branch polarities, which
// is the signature of that sink-and-fold and nothing else. Variants tried:
// the clause written flat with `&&` (this form) and nested as `if (cat) { if
// (id) ... }` (byte-identical output); `else if` chains; an explicit
// `if (!(chain)) goto next; return X;` spelling of retail's own block order;
// each of the fourteen terms of a chain as its own `if` (worse, 951/1730 on
// the sibling); the tail guard written as a bare call statement (worse, 233
// bytes); /Ox, /O1, /Ob2, /Gf, and /O2 decomposed with and without /Og (only
// /Og removes the fold, and without it the whole function regresses to 221
// bytes). Recorded as the 8447-vs-8804 identical-tail cross-jump difference
// already banked for 0x459C00 and 0x41EAF0.
//
// FUNCTION: GAMEMD 0x600CA0  FUN_00600CA0 (__fastcall)
// The first of four sibling group-size lookups. The keyed object supplies a
// category through the hash table, the control supplies its dialog ID, and
// the pair selects one of three group sizes. The clause order, the term
// order inside each clause and the constants themselves are retail's own:
// cl lays a disjunction of equality tests out verbatim, so the chains are
// transcribed in comparison order rather than sorted or switched.
//
// The trailing probe is a call whose result retail discards, because both
// arms of the guard it belongs to answer the same constant (0xF) and cl
// folded the test away; the call itself survives because FUN_00601360 is
// out of line and its side effects are not visible here.
int __fastcall FUN_00600CA0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = FindValue(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103 || category == 0x125 || category == 0xE7 ||
         category == 0x116 || category == 0xC2 || category == 0xC9 ||
         category == 0x11D || category == 0x11C || category == 0x114 ||
         category == 0x2BC || category == 0x113 || category == 0x109 ||
         category == 0x10F || category == 0x117 || category == 0xE6 ||
         category == 0xF3 || category == 0xF4 || category == 0x10E ||
         category == 0x112)
        && nCtlID == 0x694)
    {
        return 0x1E;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 0x1E;
    }

    if (category == 0x103 || category == 0xBC7)
    {
        if (nCtlID == 0x6F4)
            return 0xF;

        if (nCtlID == 0x6F3 || nCtlID == 0x69F || nCtlID == 0x6F6 ||
            nCtlID == 0x6EF || nCtlID == 0x6F1 || nCtlID == 0x6F0 ||
            nCtlID == 0x6F2 || nCtlID == 0x73C || nCtlID == 0x73D ||
            nCtlID == 0x73E || nCtlID == 0x73F || nCtlID == 0x740 ||
            nCtlID == 0x735 || nCtlID == 0x732 || nCtlID == 0x3EA ||
            nCtlID == 0x733)
        {
            return 0x1E;
        }

        if (nCtlID == 0x411 || nCtlID == 0x412 || nCtlID == 0x419 ||
            nCtlID == 0x41A || nCtlID == 0x6A3 || nCtlID == 0x6A4 ||
            nCtlID == 0x6A5 || nCtlID == 0x6A7 || nCtlID == 0x6A6 ||
            nCtlID == 0x6A8 || nCtlID == 0x73A || nCtlID == 0x739 ||
            nCtlID == 0x73B || nCtlID == 0x738)
        {
            return 0x3C;
        }
    }

    if (category == 0x108 || category == 0xBC6)
    {
        if (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x733 ||
            nCtlID == 0x71B || nCtlID == 0x732 || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418)
        {
            return 0x1E;
        }

        if (nCtlID == 0x419 || nCtlID == 0x41A || nCtlID == 0x41B ||
            nCtlID == 0x41C || nCtlID == 0x41D || nCtlID == 0x41E ||
            nCtlID == 0x41F || nCtlID == 0x420 || nCtlID == 0x6A3 ||
            nCtlID == 0x6A4 || nCtlID == 0x6A9 || nCtlID == 0x6AC ||
            nCtlID == 0x6AF || nCtlID == 0x6B2 || nCtlID == 0x6B5 ||
            nCtlID == 0x6B8 || nCtlID == 0x6A5 || nCtlID == 0x6A7 ||
            nCtlID == 0x6AA || nCtlID == 0x6AD || nCtlID == 0x6B0 ||
            nCtlID == 0x6B3 || nCtlID == 0x6B6 || nCtlID == 0x6B9 ||
            nCtlID == 0x6A6 || nCtlID == 0x6A8 || nCtlID == 0x6AB ||
            nCtlID == 0x6AE || nCtlID == 0x6B1 || nCtlID == 0x6B4 ||
            nCtlID == 0x6B7 || nCtlID == 0x6BA || nCtlID == 0x70A ||
            nCtlID == 0x70B || nCtlID == 0x70C || nCtlID == 0x70D ||
            nCtlID == 0x70E || nCtlID == 0x70F || nCtlID == 0x710 ||
            nCtlID == 0x711)
        {
            return 0x3C;
        }
    }

    if (FUN_00601360(category) && nCtlID == 0x695)
        return 0xF;

    return 0xF;
}

// FUNCTION: GAMEMD 0x6015E0  FUN_006015E0 (__fastcall)
// The same lookup answering a different quantity: 1 for every ordinary
// group and 3 for the two special controls. Here the trailing probe's
// result is live, because its arm answers 3 while the fallthrough answers
// 1, which is what keeps the TEST AL,AL and the 0x695 compare in the body.
int __fastcall FUN_006015E0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = FindValue(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103 || category == 0x125 || category == 0xE7 ||
         category == 0x116 || category == 0xC2 || category == 0xC9 ||
         category == 0x11D || category == 0x11C || category == 0x114 ||
         category == 0x2BC || category == 0x113 || category == 0x109 ||
         category == 0x10F || category == 0x117 || category == 0xE6 ||
         category == 0xF3 || category == 0xF4 || category == 0x10E ||
         category == 0x112)
        && nCtlID == 0x694)
    {
        return 1;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 1;
    }

    if (category == 0x103 || category == 0xBC7)
    {
        if (nCtlID == 0x6F4)
            return 3;

        if (nCtlID == 0x6F3 || nCtlID == 0x69F || nCtlID == 0x6F6 ||
            nCtlID == 0x6EF || nCtlID == 0x6F1 || nCtlID == 0x6F0 ||
            nCtlID == 0x6F2 || nCtlID == 0x733 || nCtlID == 0x735 ||
            nCtlID == 0x732 || nCtlID == 0x3EA || nCtlID == 0x73C ||
            nCtlID == 0x73D || nCtlID == 0x73E || nCtlID == 0x73F ||
            nCtlID == 0x740 || nCtlID == 0x736 || nCtlID == 0x737 ||
            nCtlID == 0x411 || nCtlID == 0x412 || nCtlID == 0x419 ||
            nCtlID == 0x41A || nCtlID == 0x6A3 || nCtlID == 0x6A4 ||
            nCtlID == 0x6A5 || nCtlID == 0x6A7 || nCtlID == 0x6A6 ||
            nCtlID == 0x6A8 || nCtlID == 0x73A || nCtlID == 0x739 ||
            nCtlID == 0x73B || nCtlID == 0x738)
        {
            return 1;
        }
    }

    if ((category == 0x108 || category == 0xBC6)
        && (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x733 ||
            nCtlID == 0x71B || nCtlID == 0x732 || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418 || nCtlID == 0x419 || nCtlID == 0x41A ||
            nCtlID == 0x41B || nCtlID == 0x41C || nCtlID == 0x41D ||
            nCtlID == 0x41E || nCtlID == 0x41F || nCtlID == 0x420 ||
            nCtlID == 0x6A3 || nCtlID == 0x6A4 || nCtlID == 0x6A9 ||
            nCtlID == 0x6AC || nCtlID == 0x6AF || nCtlID == 0x6B2 ||
            nCtlID == 0x6B5 || nCtlID == 0x6B8 || nCtlID == 0x6A5 ||
            nCtlID == 0x6A7 || nCtlID == 0x6AA || nCtlID == 0x6AD ||
            nCtlID == 0x6B0 || nCtlID == 0x6B3 || nCtlID == 0x6B6 ||
            nCtlID == 0x6B9 || nCtlID == 0x6A6 || nCtlID == 0x6A8 ||
            nCtlID == 0x6AB || nCtlID == 0x6AE || nCtlID == 0x6B1 ||
            nCtlID == 0x6B4 || nCtlID == 0x6B7 || nCtlID == 0x6BA ||
            nCtlID == 0x70A || nCtlID == 0x70B || nCtlID == 0x70C ||
            nCtlID == 0x70D || nCtlID == 0x70E || nCtlID == 0x70F ||
            nCtlID == 0x710 || nCtlID == 0x711))
    {
        return 1;
    }

    if (FUN_00601360(category) && nCtlID == 0x695)
        return 3;

    return 1;
}

// PARTIAL (50.9% by the instruction differ, 1031/1730 bytes identical).
// The closest of the three: the full-stream instruction multiset differs from
// retail by exactly two `je` against two `jne` and nothing else, so this body
// has retail's five return blocks and retail's every compare — only two of
// the blocks sit at the end of the function instead of inline at the
// fallthrough of the last `if` in each nest. Same lever and same variant list
// as 0x600CA0 above.
//
// FUNCTION: GAMEMD 0x601D20  FUN_00601D20 (__fastcall)
// The widest of the four: four distinct answers (8, 0x10, 0x20, 0x40) and
// the only one whose third clause splits its control IDs three ways. The
// shared return blocks retail cross-jumps to are the compiler's own doing,
// not a source-level goto.
int __fastcall FUN_00601D20(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = FindValue(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103 || category == 0x125 || category == 0xE7 ||
         category == 0x116 || category == 0xC2 || category == 0xC9 ||
         category == 0x11D || category == 0x11C || category == 0x114 ||
         category == 0x2BC || category == 0x113 || category == 0x109 ||
         category == 0x10F || category == 0x117 || category == 0xE6 ||
         category == 0xF3 || category == 0xF4 || category == 0x10E ||
         category == 0x112)
        && nCtlID == 0x694)
    {
        return 8;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 8;
    }

    if (category == 0x103 || category == 0xBC7)
    {
        if (nCtlID == 0x6F4)
            return 0x10;

        if (nCtlID == 0x6F3 || nCtlID == 0x69F || nCtlID == 0x6F6 ||
            nCtlID == 0x6EF || nCtlID == 0x6F1 || nCtlID == 0x6F0 ||
            nCtlID == 0x6F2 || nCtlID == 0x733 || nCtlID == 0x735 ||
            nCtlID == 0x732 || nCtlID == 0x3EA)
        {
            return 8;
        }

        if (nCtlID == 0x73C || nCtlID == 0x73D || nCtlID == 0x73E ||
            nCtlID == 0x73F || nCtlID == 0x740)
        {
            return 0x10;
        }

        if (nCtlID == 0x411 || nCtlID == 0x412 || nCtlID == 0x419 ||
            nCtlID == 0x41A || nCtlID == 0x6A3 || nCtlID == 0x6A4 ||
            nCtlID == 0x6A5 || nCtlID == 0x6A7 || nCtlID == 0x6A6 ||
            nCtlID == 0x6A8 || nCtlID == 0x73A || nCtlID == 0x739 ||
            nCtlID == 0x73B || nCtlID == 0x738)
        {
            return 0x20;
        }
    }

    if (category == 0x108 || category == 0xBC6)
    {
        if (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x733 ||
            nCtlID == 0x71B || nCtlID == 0x732 || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418)
        {
            return 0x20;
        }

        if (nCtlID == 0x419 || nCtlID == 0x41A || nCtlID == 0x41B ||
            nCtlID == 0x41C || nCtlID == 0x41D || nCtlID == 0x41E ||
            nCtlID == 0x41F || nCtlID == 0x420 || nCtlID == 0x6A3 ||
            nCtlID == 0x6A4 || nCtlID == 0x6A9 || nCtlID == 0x6AC ||
            nCtlID == 0x6AF || nCtlID == 0x6B2 || nCtlID == 0x6B5 ||
            nCtlID == 0x6B8 || nCtlID == 0x6A5 || nCtlID == 0x6A7 ||
            nCtlID == 0x6AA || nCtlID == 0x6AD || nCtlID == 0x6B0 ||
            nCtlID == 0x6B3 || nCtlID == 0x6B6 || nCtlID == 0x6B9 ||
            nCtlID == 0x6A6 || nCtlID == 0x6A8 || nCtlID == 0x6AB ||
            nCtlID == 0x6AE || nCtlID == 0x6B1 || nCtlID == 0x6B4 ||
            nCtlID == 0x6B7 || nCtlID == 0x6BA || nCtlID == 0x70A ||
            nCtlID == 0x70B || nCtlID == 0x70C || nCtlID == 0x70D ||
            nCtlID == 0x70E || nCtlID == 0x70F || nCtlID == 0x710 ||
            nCtlID == 0x711)
        {
            return 0x40;
        }
    }

    if (FUN_00601360(category) && nCtlID == 0x695)
        return 0x10;

    return 8;
}

// PARTIAL (28.1% by the instruction differ, 521/1602 bytes identical).
// Retail keeps five separate `POP EDI; MOV AL,1; POP ESI; POP ECX; RET`
// blocks, one per clause; cl 8804 folds all five into one. The multiset
// residual is exactly four of those blocks plus five branch polarities. The
// `(char)` cast on FUN_00602AE0's result is load-bearing and stays: retail
// tests that call with `TEST AL,AL` while the callee's own exit at 0x602AE0
// is `MOV EAX,1`, so the value is narrowed at the call site, not at the
// definition. Same variant list as 0x600CA0 above.
//
// FUNCTION: GAMEMD 0x602490  FUN_00602490 (__fastcall)
// The predicate of the family, and the one that answers a byte: its exits
// are MOV AL,1 / XOR AL,AL, where the three siblings above load EAX. Its
// first clause widens the category set with the out-of-line membership test
// at 0x602AE0, and its tail adds one more guard, a flag read off the
// session object at 0xA8B238 + 0x30D8 through the accessor at 0x69BBE0.
bool __fastcall FUN_00602490(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = FindValue(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103
         || (char)FUN_00602AE0(category))
        && nCtlID == 0x694)
    {
        return true;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return true;
    }

    if ((category == 0x103 || category == 0xBC7)
        && (nCtlID == 0x6F3 || nCtlID == 0x6F4 || nCtlID == 0x69F ||
            nCtlID == 0x6F6 || nCtlID == 0x6EF || nCtlID == 0x6F1 ||
            nCtlID == 0x6F0 || nCtlID == 0x6F2 || nCtlID == 0x733 ||
            nCtlID == 0x735 || nCtlID == 0x732 || nCtlID == 0x3EA ||
            nCtlID == 0x736 || nCtlID == 0x737 || nCtlID == 0x73C ||
            nCtlID == 0x73D || nCtlID == 0x73E || nCtlID == 0x73F ||
            nCtlID == 0x740 || nCtlID == 0x411 || nCtlID == 0x412 ||
            nCtlID == 0x419 || nCtlID == 0x41A || nCtlID == 0x6A3 ||
            nCtlID == 0x6A4 || nCtlID == 0x6A5 || nCtlID == 0x6A7 ||
            nCtlID == 0x6A6 || nCtlID == 0x6A8 || nCtlID == 0x73A ||
            nCtlID == 0x739 || nCtlID == 0x73B || nCtlID == 0x738))
    {
        return true;
    }

    if ((category == 0x108 || category == 0xBC6)
        && (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418 || nCtlID == 0x419 || nCtlID == 0x41A ||
            nCtlID == 0x41B || nCtlID == 0x41C || nCtlID == 0x41D ||
            nCtlID == 0x41E || nCtlID == 0x41F || nCtlID == 0x420 ||
            nCtlID == 0x6A3 || nCtlID == 0x6A4 || nCtlID == 0x6A9 ||
            nCtlID == 0x6AC || nCtlID == 0x6AF || nCtlID == 0x6B2 ||
            nCtlID == 0x6B5 || nCtlID == 0x6B8 || nCtlID == 0x6A5 ||
            nCtlID == 0x6A7 || nCtlID == 0x6AA || nCtlID == 0x6AD ||
            nCtlID == 0x6B0 || nCtlID == 0x6B3 || nCtlID == 0x6B6 ||
            nCtlID == 0x6B9 || nCtlID == 0x6A6 || nCtlID == 0x6A8 ||
            nCtlID == 0x6AB || nCtlID == 0x6AE || nCtlID == 0x6B1 ||
            nCtlID == 0x6B4 || nCtlID == 0x6B7 || nCtlID == 0x6BA ||
            nCtlID == 0x70A || nCtlID == 0x70B || nCtlID == 0x70C ||
            nCtlID == 0x70D || nCtlID == 0x70E || nCtlID == 0x70F ||
            nCtlID == 0x710 || nCtlID == 0x711 || nCtlID == 0x733 ||
            nCtlID == 0x732 || nCtlID == 0x71B || nCtlID == 0x735))
    {
        return true;
    }

    if (FUN_00601360(category) && nCtlID == 0x695
        && !DAT_00A8B238_Session.FUN_0069BBE0())
    {
        return true;
    }

    return false;
}
