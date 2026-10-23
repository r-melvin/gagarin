// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x629E90.

#include "foot_class_wakes_methods.h"

// FUNCTION: GAMEMD 0x629E90
//
// Drop three wake animations behind a moving unit. The unit's current facing is
// turned into an angle, and each wake is placed at a random offset (+/-0xB4
// along the hull, +/-0x40 across it) rotated into world space by that angle and
// added to the passed-in coordinate. Each wake is an AnimClass built directly
// at the resulting spot.
//
// Phrasing notes (load-bearing):
//   * The sin/cos pair is declared as plain `extern "C" double __cdecl`
//     functions under placeholder names, so cl calls them the retail way
//     (`MOV ESI,[angle+4]; MOV EDI,[angle]; PUSH ESI; PUSH EDI; CALL`) with the
//     two stack cleanups merged into one `ADD ESP,0x10`, instead of
//     substituting an x87 intrinsic.
//   * 0x4CAD00 is cos and 0x4CACB0 is sin: the first result multiplies `along`
//     in the X term and `across` in the Y term, which is the standard rotation.
//   * The AnimClass allocation is written out by hand as operator new / null
//     test / constructor call (a real `new T(...)` adds a /GX EH frame retail
//     does not have, as at 0x641DB0), and there is no else-arm because retail
//     never stores the result.
//
// PARTIAL (31.2%, 29/93). The prologue, the facing read, the angle
// computation and both trig calls are byte-exact through 0x4C. Three residual
// deltas:
//   1. Frame size 0x3C against retail's 0x34. Retail merges the 4-byte facing
//      out-buffer with the 8-byte angle slot at [ESP+0x10] even though its
//      address was taken; cl 8804 will not merge an address-taken local, so it
//      spends a separate 8-byte slot. Forcing the merge with a
//      `union { double; DirStruct; }` does produce SUB ESP,0x34, but it also
//      moves the union above the int conversion slot and every later
//      displacement then differs (23.7%).
//   2. Retail caches only the Y and Z arguments in EDI/EBX and re-reads X from
//      [EBP+8] inside the loop, keeping ESI for the first `_ftol` result; cl
//      caches all three and stores coord.X as soon as the first `_ftol`
//      returns instead of after the second.
//   3. Retail converts `along` to double (`FILD`/`FSTP`) before the second
//      randomizer call; cl defers both conversions until after it.
// Variants tried: the coordinate terms written inline in the member stores
// (31.2%, kept); named `dx`/`dy` locals computed before the stores plus an
// 8-byte out-buffer (29.0%); a `double` out-buffer with a cast (29.0%); the
// union-shared slot, with and without the named deltas (23.7% both).
// Lift pass 2 (2026-09-18): one more rejected - `double dalong = along;`
// between the two randomizer calls to force retail's early FILD/FSTP (delta 3).
// It does move the conversion, but costs the `MOV` and `FXCH` retail has and
// drops to 28.0%; the kept form is still the inline-terms one at 31.2%.
// Delta 1 (the unmergeable address-taken frame slot) is the banked
// 8447-vs-8804 class and dominates the positional score.
void FootClass::CreateWakes(int x, int y, int z)
{
    DirStruct tmp;
    DirStruct* facing = this->PrimaryFacing.FUN_004C93D0(&tmp);
    double angle = -((double)((short)facing->Raw - 0x3FFF) * DAT_007E2810);
    double c = FUN_004CAD00(angle);
    double s = FUN_004CACB0(angle);

    int i = 3;
    do {
        int along  = DAT_00A8B230->Random.RandomRanged(-0xB4, 0xB4);
        int across = DAT_00A8B230->Random.RandomRanged(-0x40, 0x40);

        CoordStruct_00629E90 coord;
        coord.X = x + (int)(along * c - across * s);
        coord.Y = y + (int)(along * s + across * c);
        coord.Z = z;

        AnimClass_00629E90* anim =
            (AnimClass_00629E90*)FUN_007C8E17(sizeof(AnimClass_00629E90));
        if (anim != 0) {
            anim->FUN_00421EA0(DAT_008871E0->At_94, coord, 0, 1, 0x600, 0, 0);
        }
    } while (--i != 0);
}
