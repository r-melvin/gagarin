// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x602B90 and 0x603240.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x602B90  FUN_00602B90 (__fastcall)
//   FUNCTION: GAMEMD 0x603240  FUN_00603240 (__fastcall)
//   GLOBAL:   GAMEMD 0xAC1B00  the hash table
//   GLOBAL:   GAMEMD 0x7E13B4  __imp__GetDlgCtrlID

#include "dialog_type_lookup_predicates.h"

// The hash-table probe both predicates open with, expanded inline at 0x602B91
// and again at 0x603241. It must be forced inline and it must keep the inner
// `n ? &n->Value : 0` guard: that guard is the first of retail's two null tests
// on the hit path, and the caller's own `p ? p->Field6C : 0` is the second.
// Dropping either one loses the `ADD EAX,4` block entirely.
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

// FUNCTION: GAMEMD 0x602B90  FUN_00602B90 (__fastcall)
// Decide whether a given control belongs to the keyed object. The object's
// category is looked up in the hash table and paired with the control's own
// dialog ID: each category owns one contiguous run of control IDs, and the
// answer is whether this control falls in the run that category owns.
//
// The category tests come first in every clause because that is retail's own
// order — the category is compared, and only on a hit is the control ID walked.
bool __fastcall FUN_00602B90(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = FindValue(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if (((category == 0xBC || category == 0xBD || category == 0xC2 ||
          category == 0xC9 || category == 0xBC6)
         && (nCtlID == 0x6D2 || nCtlID == 0x6D3 || nCtlID == 0x6D4 ||
             nCtlID == 0x6D5 || nCtlID == 0x6D6 || nCtlID == 0x6D7 ||
             nCtlID == 0x6D8 || nCtlID == 0x6D9))
        || ((category == 0x102 || category == 0xBC || category == 0xBD ||
             category == 0xC2 || category == 0xC9)
            && (nCtlID == 0x6DA || nCtlID == 0x6DB || nCtlID == 0x6DC ||
                nCtlID == 0x6DD || nCtlID == 0x6DE || nCtlID == 0x6DF ||
                nCtlID == 0x6E0 || nCtlID == 0x6E1))
        || ((category == 0xC2 || category == 0xC9)
            && (nCtlID == 0x754 || nCtlID == 0x755 || nCtlID == 0x756 ||
                nCtlID == 0x757 || nCtlID == 0x758 || nCtlID == 0x759 ||
                nCtlID == 0x75A || nCtlID == 0x75B))
        || (category == 0xBC6 && (nCtlID == 0x77F || nCtlID == 0x6DB)))
    {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x603240  FUN_00603240 (__fastcall)
// The same probe against a single control: thirty categories all share the one
// control ID 0x71C, so the answer is simply whether the keyed object is one of
// them and the control is that one. Unlike its sibling this one answers a full
// dword, which is why the constant returns are written as `int`.
int __fastcall FUN_00603240(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = FindValue(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x94 || category == 0xD8 || category == 0xF5 ||
         category == 0xE2 || category == 0xD5 || category == 0x101 ||
         category == 0x129 || category == 0xD7 || category == 0xBB ||
         category == 0x100 || category == 0xD6 || category == 0x125 ||
         category == 0x122 || category == 0x112 || category == 0xE7 ||
         category == 0x116 || category == 0x11D || category == 0x11C ||
         category == 0xFE || category == 0x10F || category == 0x117 ||
         category == 0x114 || category == 0xE6 || category == 0xF3 ||
         category == 0xF4 || category == 0x2BC || category == 0x10E ||
         category == 0x108 || category == 0xBC6 || category == 0xBC7)
        && nCtlID == 0x71C)
    {
        return 1;
    }

    return 0;
}
