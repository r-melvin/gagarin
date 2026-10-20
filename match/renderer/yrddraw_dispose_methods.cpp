// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6BB8E0. Names from
//   YRpp YRDDraw.h (consult-only).

#include "yrddraw_dispose_methods.h"

// FUNCTION: GAMEMD 0x6BB8E0
//
// Shutdown of the DirectDraw layer. The sidebar/tab surfaces go first if they
// were ever built, then -- once only, guarded by the 0xB0BCF5 flag -- the six
// global surfaces are deleted and nulled and the display is restored.
void YRDDraw::DisposeOfStuff()
{
    if (DAT_008A0DEF != 0)
        FUN_004C19B0();

    if (DAT_00B0BCF5 == 0) {
        if (DAT_0088730C != 0) {
            delete DAT_0088730C;
            DAT_0088730C = 0;
        }
        if (DAT_00887310 != 0) {
            delete DAT_00887310;
            DAT_00887310 = 0;
        }
        if (DAT_008872FC != 0) {
            delete DAT_008872FC;
            DAT_008872FC = 0;
        }
        if (DAT_00887300 != 0) {
            delete DAT_00887300;
            DAT_00887300 = 0;
        }
        if (DAT_0088731C != 0) {
            delete DAT_0088731C;
            DAT_0088731C = 0;
        }
        if (DAT_00887308 != 0) {
            delete DAT_00887308;
            DAT_00887308 = 0;
        }
        Restore();
        DAT_00B0BCF5 = 1;
    }
}
