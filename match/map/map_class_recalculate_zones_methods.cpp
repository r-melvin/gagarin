// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x56D5A0.

#include "map_class_recalculate_zones_methods.h"

// FUNCTION: GAMEMD 0x56D5A0
//
// Patch the zone index of one cell instead of rebuilding the whole zone map.
// The cell's entry is found by the clamped row-major index; if it is not the
// impassable type 7, its eight neighbours are searched for one of the same
// type. When such a neighbour exists, the neighbours are walked a second time
// counting how many *distinct* remapped zones they touch; up to three the cell
// simply inherits the found neighbour's zone index, and anything more (or no
// same-type neighbour at all) forces the full rebuild on the map singleton.
//
// Phrasing notes (load-bearing):
//   * The eight neighbour offsets must live in a `volatile int[8]`. Without it
//     cl 8804 forwards the stored values into both walks — the first iteration
//     of each loop is then folded against the register still holding
//     -stride — where retail re-reads every offset from the frame slot through
//     the walking pointer. volatile alone lifted this from 12.7% to 23.5%.
//   * `here->Type` is read into an int before the offsets are built, so the
//     zero-extended byte load lands where retail has it.
//   * `touched <= 3` keeps retail's `CMP dword ptr [ESP+0x3C],3; JG`; `< 4`
//     gives `CMP ..,4; JGE`.
//   * The found-body sits inside the search loop's `if` and ends in a `return`
//     for the success path and a `break` for the rest, so both failure paths
//     share the single rebuild call after the loop.
//
// PARTIAL (29.4%, 32/109). The whole prologue through the clamp is byte-exact
// (21 instructions). Three residual deltas, all recorded classes:
//   1. cl 8804 duplicates the head of the first search loop at the back edge
//      (`MOV EBX,dword ptr [ESP+0x18]` peeled for iteration 0, then the rotated
//      body); retail's loop is a plain do-while with the load at the top.
//   2. Register naming: retail parks the zone pointer in ESI and the cached
//      type in EDX (`XOR EDX,EDX; MOV DL,[ESI]`); cl picks EDX for the pointer
//      and ESI for the type, which costs one extra `MOV ESI,EAX` because EAX
//      is simultaneously the stride.
//   3. In the second walk retail materialises the neighbour address once
//      (`LEA ECX,[ESI+ECX*4]`) and reuses it for the `CMP byte ptr [ECX],7`,
//      where cl folds the scaled address back into the compare.
// Variants tried: non-volatile `int offsets[8]` in natural index order (12.7%);
// volatile array stored in retail's observed store order (23.5%); the cached
// type read before the stride (29.4%, kept); the cached type read after the
// stride (28.4%).
// Lift pass 2 (2026-09-18): the two immediate offset stores (`offsets[2] = 1;
// offsets[6] = -1;`) now sit between the `here` computation and the stride, so
// they land byte-exact in retail's own slots at 0x56D5E0/0x56D5E8 - declaring
// the array before `here` pushes them above the Zones load instead (26.6%) and
// after the stride puts them below the LEA. Still 29.4% overall: the gain is
// offset by cl scheduling the `LEA EDX,[EDX+EAX*4]` immediately after the
// Zones load where retail defers it past the two stores. Also re-tried naming
// `DAT_0087F8E0` in a local to pull its load up to retail's 0x56D5DA slot -
// identical stream. Deltas 1-3 above stand.
// Lift pass 3 (2026-09-18): re-tested delta 1 against the loop-rotation lever
// that took 0x40E3E0, 0x505360 and 0x526CC0 to 100% — `while (1) { body; ++i;
// ++p; if (!(i < 8)) break; }` with the negation wrapping the whole test. It
// is a large negative here: 1.0% for that form, 1.0% with the type compare
// also negated, and 1.9% for a plain `for (i = 0; i < 8; ++i, ++p)`. The
// do-while below stays at 29.4% and is kept. So the rotation lever is specific
// to loops whose back edge retail writes as an unconditional jump to a memory
// test; where retail already emits a bottom-tested do-while, as here, the
// lever inverts the layout instead of fixing it.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void Map_0056D5A0::RecalculateZones(CellStruct_0056D5A0& cell)
{
    int idx = (this->At_F8 + this->At_F4 + 1) * cell.Y + cell.X;
    if (idx < 0) {
        idx = 0;
    } else if (idx >= this->ZoneCount) {
        idx = this->ZoneCount - 1;
    }

    Zone_0056D5A0* here = this->Zones + idx;

    volatile int offsets[8];
    offsets[2] = 1;
    offsets[6] = -1;

    int stride = DAT_0087F8E0 + DAT_0087F8DC + 1;
    int type = here->Type;
    offsets[4] = stride;
    offsets[0] = -stride;
    offsets[1] = 1 - stride;
    offsets[3] = stride + 1;
    offsets[5] = stride - 1;
    offsets[7] = -1 - stride;

    if (type != 7) {
        int i = 0;
        volatile int* p = offsets;
        do {
            Zone_0056D5A0* other = here + *p;
            if (other->Type == type) {
                int best = 0;
                if (other != 0) {
                    int touched = 0;
                    volatile int* q = offsets;
                    int n = 8;
                    do {
                        int off = *q;
                        int zone = here[off].Index;
                        if (this->ZoneRemap[zone] != this->ZoneRemap[best]) {
                            if (here[off].Type != 7) {
                                best = zone;
                                ++touched;
                            }
                        }
                        ++q;
                    } while (--n != 0);

                    if (touched <= 3) {
                        here->Index = other->Index;
                        return;
                    }
                }
                break;
            }
            ++i;
            ++p;
        } while (i < 8);

        DAT_0087F7E8.FUN_0056C510();
    }
}
