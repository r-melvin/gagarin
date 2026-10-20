// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x46D360.
//
// STRING: GAMEMD 0x81B2EC  "TXT_TIME_FORMAT_HOURS"

#include "format_duration_methods.h"

// FUNCTION: GAMEMD 0x46D360
//
// Format a duration in seconds as hours, minutes and seconds into the caller's
// buffer, capped at 99:59:59.
//
// The hour count is computed twice — once to test the cap and again after it —
// rather than being clamped in place. Retail emits both divisions (0x46D373 and
// 0x46D390), so the source tests `seconds / 3600` and then recomputes it.
void __fastcall FUN_0046D360(gg_wchar* buffer, int seconds)
{
    if (buffer == 0) {
        return;
    }

    if (seconds / 3600 > 99) {
        seconds = 359999;
    }

    int hours = seconds / 3600;
    seconds -= hours * 3600;

    int minutes = seconds / 60;
    seconds -= minutes * 60;

    FUN_007CA564(buffer,
                 FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0081B304, 0xA9),
                 hours, minutes, seconds);
}

// FUNCTION: GAMEMD 0x470C90
//
// A second copy of the same formatter. The two differ in exactly one constant:
// the line number handed to the label lookup, 0x6EA here against 0xA9 at
// 0x46D360. Same file path in both, so this is the same helper written out twice
// in one source file, at lines 169 and 1770 — which is itself the evidence that
// it was duplicated by hand rather than shared. Written out longhand rather than
// shared: the family rule in the methodology exists because look-alike siblings
// have been caught diverging, and confirming these two are identical is a check,
// not an assumption.
void __fastcall FUN_00470C90(gg_wchar* buffer, int seconds)
{
    if (buffer == 0) {
        return;
    }

    if (seconds / 3600 > 99) {
        seconds = 359999;
    }

    int hours = seconds / 3600;
    seconds -= hours * 3600;

    int minutes = seconds / 60;
    seconds -= minutes * 60;

    FUN_007CA564(buffer,
                 FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0081B304, 0x6EA),
                 hours, minutes, seconds);
}
