// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x408410 and 0x40A950.

#include "small_misc44_methods.h"

// FUNCTION: GAMEMD 0x408410
int __cdecl FUN_00408410()
{
    if (DAT_0087E81C == 0) {
        return 1;
    }

    ListNode* node = (&DAT_0087E810)->FUN_004073C0();

    if (node == 0) {
        return 1;
    }

    do {
        Entry_00408410* entry = (Entry_00408410*)node;

        if (*(unsigned char*)&entry->Flags & 1) {
            Tracked_00408410* tracked = entry->Tracked;

            if (tracked->Head != tracked->Tail) {
                return 0;
            }
        }

        node = (node)->FUN_004073E0();
    } while (node);

    return 1;
}

// FUNCTION: GAMEMD 0x4081A0
void __cdecl FUN_004081A0()
{
    if (DAT_0087E81C == 0) {
        return;
    }

    ListNode* node = (&DAT_0087E810)->FUN_004073C0();

    if (node == 0) {
        return;
    }

    void (__stdcall* enter)(CriticalSection_004081A0*) = EnterCriticalSection;
    void (__stdcall* leave)(CriticalSection_004081A0*) = LeaveCriticalSection;

    do {
        Armed_004081A0* entry = (Armed_004081A0*)node;

        if (entry->Busy == 0 && entry->Subject != 0) {
            enter(&DAT_0087E7F8);

            FUN_004025B0(entry->Subject);

            leave(&DAT_0087E7F8);
        }

        node = (node)->FUN_004073E0();
    } while (node);
}

// FUNCTION: GAMEMD 0x40A950
void __cdecl FUN_0040A950()
{
    int status;

    if (DAT_0087E8A0 == 0) {
        return;
    }

    POLL_CALL1(DAT_0087E8A0, 0x24, &status);

    if (*(unsigned char*)&status & 2) {
        POLL_CALL0(DAT_0087E8A0, 0x50);
    }

    if (!(*(unsigned char*)&status & 1)) {
        POLL_CALL3(DAT_0087E8A0, 0x30, 0, 0, 1);
    }
}

// FUNCTION: GAMEMD 0x435560   BitText::`scalar deleting destructor'
void* BitText::ScalarDeletingDestructor(char flags)
{
    Vtable = &VT_007E3A80;

    Singleton_00435560* singleton = DAT_0089C4D0;

    if (singleton) {
        singleton->vt_000(1);
    }

    if (singleton == DAT_0089C4D0) {
        DAT_0089C4D0 = 0;
    }

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
