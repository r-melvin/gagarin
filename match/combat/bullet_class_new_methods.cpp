// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail entry bytes and accesses: ev_947587143ab3fdfa958fd4f166aa4fa4fcad73b494d72219e3902bb9f5571249,
//   ev_38dfebff60f332145fbe2fd81a2ce59c3c9a8b82b74e245b203356b37990a7f6,
//   ev_81ad9579baf187a65d54e521cd0517aaf6ac6e0f19182d833eb54badee583482.

#include "../_layout/bullet_class.h"
#include "bullet_type_class.h"
#include <windows.h>

// FUNCTION dependency: GAMEMD 0x004CAE30, double arguments and ST(0) result.
extern "C" double __cdecl FUN_004CAE30(double y, double x);

// GLOBAL: GAMEMD 0x007E2820
extern const double DAT_007E2820;
// GLOBAL: GAMEMD 0x007E2818
extern const double DAT_007E2818;
// GLOBAL: GAMEMD 0x007F4890
extern int DAT_007F4890[32];
// GLOBAL: GAMEMD 0x00ABCD3C
extern int DAT_00ABCD3C;

// FUNCTION: GAMEMD 0x468000
int BulletClass::vf_122()
{
    int frame = 0;
    if (!Type->unknown_2A1) {
        unsigned short raw = (unsigned short)(int)((FUN_004CAE30(
            -Velocity.Y, Velocity.X) - DAT_007E2820) * DAT_007E2818);
        frame = DAT_007F4890[((raw >> 10) + 1 >> 1) & 31];
    }
    if (Type->unknown_2F4 || Type->unknown_2F5)
        frame = AnimFrame;
    return frame;
}

// FUNCTION: GAMEMD 0x468B90
int BulletClass::vf_30()
{
    return Type->unknown_2F7 ? 1 : 3;
}

// FUNCTION: GAMEMD 0x46AFF0
ULONG __stdcall BulletClass::Release()
{
    --DAT_00ABCD3C;
    ULONG count = InterlockedDecrement(&RefCount);
    if (count == 0 && this)
        delete this;
    return count;
}
