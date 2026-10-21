// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the three addresses below.

#include "small_misc42_methods.h"

// FUNCTION: GAMEMD 0x402940
int __cdecl FUN_00402940()
{
    FUN_004072C0(DAT_00815E98);
    FUN_004072C0((char*)DAT_00815E98 + 0xC);

    DAT_00815E98->field_18 = 0;

    void* tail = DAT_00815E98->Tail;

    DAT_0087DE30 = tail;

    FUN_00401000(tail);

    DAT_0087DE2C = 1;

    return 0;
}

// FUNCTION: GAMEMD 0x429500
long __stdcall FUN_00429500(void* self, int* value)
{
    if (value == 0) {
        return 0x80004003;
    }

    // The global is written out twice rather than held in a local. Retail reads
    // it once (VC6 does the CSE either way) and immediately derives both
    // `LEA ESI,[EAX+0x614]` and the base counter from it, leaving the source
    // pointer dead. Naming it as a local keeps it alive for the whole function
    // instead, and the `&...->Timer` folds away into 0x614-sized displacements -
    // six spellings of the held-pointer form all sit at 32%.
    int reading = DAT_00A8B230->Base;

    Timer_00429500* timer = &DAT_00A8B230->Timer;

    if (timer->Started != -1) {
        reading += FUN_006C8C40(&timer->Handle) - timer->Started;
    }

    *value = reading;

    return 0;
}
