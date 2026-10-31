// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
//   Original translation unit Credits.CPP. The name is the source-file string at 0x81fbbc
//   in retail gamemd.exe v1.001, passed by the assert at 0x4a248d inside this object's
//   code range (0x4a2160-0x4a292f). Functions are in ascending retail address order.
//
// Straw slot 2 takes a destination pointer and a signed byte count.

#include "buffer_straws.h"
#include "../core/mathtbl_init_shapes.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <math.h>
#include "../core/header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E5D80
extern const double DAT_007E5D80;
// GLOBAL: GAMEMD 0x89F900
extern double DAT_0089F900;

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E5D88 -- degrees to radians
const double DAT_007E5D88 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4A2160
// GLOBAL: GAMEMD 0x89F900
double DAT_0089F900 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x004A2190
// GLOBAL: GAMEMD 0x0089F950
double DAT_0089F950 = DAT_0089F900 / DAT_007E5D80;

// SYNTHETIC: GAMEMD 0x004A21B0
// GLOBAL: GAMEMD 0x0089F938
double DAT_0089F938 = DAT_007E1718 / DAT_0089F950;

// SYNTHETIC: GAMEMD 0x4A21D0
// GLOBAL: GAMEMD 0x89F930
double DAT_0089F930 = DAT_007E5D88 * 45.0;
// SYNTHETIC: GAMEMD 0x4A21F0
// GLOBAL: GAMEMD 0x89F908
double DAT_0089F908 = DAT_007E5D88 * 60.0;
// SYNTHETIC: GAMEMD 0x4A2210
// GLOBAL: GAMEMD 0x89F8E0
double DAT_0089F8E0 = DAT_007E5D88 * 90.0;
// SYNTHETIC: GAMEMD 0x4A2230
// GLOBAL: GAMEMD 0x89F958
int DAT_0089F958 = (int)(FUN_004CAD50(DAT_0089F8E0 - DAT_0089F908) * DAT_0089F900 * 0.5);
// SYNTHETIC: GAMEMD 0x4A2270
// GLOBAL: GAMEMD 0x89F910
double DAT_0089F910 = FUN_004CADE0(DAT_0089F958 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4A22A0
// GLOBAL: GAMEMD 0x89F928
double DAT_0089F928 = FUN_004CADE0((DAT_0089F958 * 2) / DAT_0089F900);
// SYNTHETIC: GAMEMD 0x4A22D0
// GLOBAL: GAMEMD 0x89F94C
int DAT_0089F94C = (int)(DAT_0089F958 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4A2300
// GLOBAL: GAMEMD 0x89F8F8
HeaderCellInit DAT_0089F8F8(0, 0);
// SYNTHETIC: GAMEMD 0x4A2310
// GLOBAL: GAMEMD 0x89F918
HeaderCoordInit DAT_0089F918(0, 0, 0);
// SYNTHETIC: GAMEMD 0x004A2330
// GLOBAL: GAMEMD 0x0089F940
MathTblCoord DAT_0089F940;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4A2780
int CacheStraw::FUN_006C98E0(void* first, int second)
{
    int total = 0;

    if (Buffer.Buffer != 0 && first != 0 && second > 0) {
        while (second > 0) {
            if (Length > 0) {
                int tocopy = (Length < second) ? Length : second;
                memmove(first, (char*)Buffer.Buffer + Index, tocopy);
                second -= tocopy;
                Index += tocopy;
                total += tocopy;
                Length -= tocopy;
                first = static_cast<char*>(first) + tocopy;
            }
            if (second == 0) {
                break;
            }
            Length = Straw::FUN_006C98E0(Buffer.Buffer, Buffer.Size);
            Index = 0;
            if (Length == 0) {
                break;
            }
        }
    }
    return total;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E5D80
extern const double DAT_007E5D80 = 60.0;
// END defined globals
