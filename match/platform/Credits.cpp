// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E5D80
extern const double DAT_007E5D80;
// GLOBAL: GAMEMD 0x89F900
extern double DAT_0089F900;

// SYNTHETIC: GAMEMD 0x004A2190
// GLOBAL: GAMEMD 0x0089F950
double DAT_0089F950 = DAT_0089F900 / DAT_007E5D80;

// SYNTHETIC: GAMEMD 0x004A21B0
// GLOBAL: GAMEMD 0x0089F938
double DAT_0089F938 = DAT_007E1718 / DAT_0089F950;

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
