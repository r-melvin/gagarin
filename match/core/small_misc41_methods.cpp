// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the three addresses below.

#include "small_misc41_methods.h"

// FUNCTION: GAMEMD 0x4067D0
bool FUN_004067D0(const char* name, int* value)
{
    NameValue_004067D0* entry = DAT_00816018;

    // The loop condition is the *terminator*, not the comparison. Retail
    // reloads `entry->Name` at the top of the body even though the guard above
    // it just read the same word, which is what loop rotation of
    // `while (entry->Name) { if (cmp) break; entry++; }` produces. Driving the
    // loop on the comparison instead - either as a top-tested `while` or as a
    // do-while inside an emptiness guard - makes VC6 peel the first compare and
    // emit the whole call block twice, 21.6% both ways.
    while (entry->Name != 0) {
        if (FUN_007C8D20(name, entry->Name) == 0) {
            break;
        }

        entry++;
    }

    if (value) {
        *value = entry->Value;
    }

    return entry->Name != 0;
}

// FUNCTION: GAMEMD 0x406820
//
// The sibling of 0x4067D0 over the second table. Written out longhand rather
// than shared: the argument order is reversed and the result is accumulated
// into the destination with `|=` instead of stored.
bool FUN_00406820(int* flags, const char* name)
{
    NameValue_004067D0* entry = DAT_008160C0;

    while (entry->Name != 0) {
        if (FUN_007C8D20(name, entry->Name) == 0) {
            break;
        }

        entry++;
    }

    if (flags) {
        *flags |= entry->Value;
    }

    return entry->Name != 0;
}

// FUNCTION: GAMEMD 0x406870
//
// The third of the family. Written out longhand: the walk is the same but the
// tail replaces conflicting flag groups before merging, and the merge re-reads
// the entry's value rather than reusing the register the tests ran on.
bool FUN_00406870(int* flags, const char* name)
{
    NameValue_004067D0* entry = DAT_00816048;

    while (entry->Name != 0) {
        if (FUN_007C8D20(name, entry->Name) == 0) {
            break;
        }

        entry++;
    }

    if (flags) {
        int value = entry->Value;

        if (value & 0x60) {
            *flags &= ~0x60;
        } else if (value & 0xC00) {
            *flags &= ~0xC00;
        }

        *flags |= entry->Value;
    }

    return entry->Name != 0;
}

// FUNCTION: GAMEMD 0x413CD0
bool FUN_00413CD0(Obj_00413CD0* self)
{
    if (self == 0) {
        return false;
    }

    Obj_00413CD0* typed = (self->WhatAmI() == 15) ? self : 0;

    if (typed == 0) {
        return false;
    }

    if (!typed->Settings->Enabled) {
        return false;
    }

    bool allowed = typed->Suppressed == 0;

    return allowed;
}

// FUNCTION: GAMEMD 0x452170
void Obj_00452170::FUN_00452170(int value)
{
    int stamp = value;

    if (value == 15 && vt_068(0, 0) == 5) {
        stamp = 0x10;
    }

    Slot_00452170** slot = Slots;
    int             n    = 0x15;

    do {
        Slot_00452170* item = *slot;

        if (item) {
            item->Stamp = (char)stamp;
        }

        slot++;
        n--;
    } while (n != 0);
}
