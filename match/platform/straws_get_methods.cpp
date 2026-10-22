// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x552490.

#include "straws_get_methods.h"

// FUNCTION: GAMEMD 0x552490  LCWStraw::Get (__thiscall, ret 8)
//
// Pull `slen` bytes through the LCW straw. Whatever is already staged in the
// working buffer is handed over first; when the caller still wants more, one
// more block is pulled from the straw below and either decompressed into the
// working buffer (Control == 1: read the 4-byte header, read the compressed
// payload into the far end of the buffer, expand it) or compressed into the
// second buffer behind a freshly written header. Any short read from below
// ends the transfer and the running total is returned.
//
// PARTIAL (4.6%, 6/131 by the positional aligner; the real content delta is
// three instructions). Every block, every callee, every argument order, the
// deferred `PUSH EDI`, the duplicated loop-head test, both return tails and
// all the member arithmetic reproduce exactly; the whole body is shifted by
// one instruction from the prologue on. Retail saves the destination pointer
// in EBP (`PUSH EBP; MOV EBP,[ESP+0x10]; PUSH ESI`) and keeps the length in
// EBX, spilling the length to its parameter home slot; cl 12.00.8804 loads
// the destination into EAX ahead of the pushes, gives EBP to the length and
// wastes EBX on the CSE'd constant 1 (it is shared by `slen < 1` and the two
// `Control == 1` tests), so the destination has no callee-saved register and
// is reloaded from its home slot twice inside the copy block — retail-only
// {push:1}, compiled-only {mov:2}. This is the recorded EBX/EBP allocation
// swap class (0x50D440) with two reload movs attached. Variants tried: the
// null and length guards split into two separate `if`s (3.6% — cl then
// duplicates the whole `return 0` tail); a `char* dest` local copy of the
// parameter advanced instead of the parameter itself (3.8%, a third reload);
// a `char*` parameter with `dest += len` (4.6%, byte-identical output to
// this form); and `slen <= 0` for the guard, which does free EBX of the
// constant but then deletes retail's duplicated loop-head `TEST EBX,EBX`
// and still leaves the destination in EAX, so it is strictly further away.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): already satisfied, so it is
// not the lever here. Retail pushes ECX, EBX, EBP and ESI in the prologue and
// sinks PUSH EDI to 0x29, giving two epilogues with different pop sets — one
// at 0x149 that pops EDI and one at 0x151 that does not. Our output has the
// same two epilogues with the same asymmetry, so nothing is merged that retail
// leaves split. This function's residual is far larger than a colouring
// exchange (4.6%, heavy block-order divergence) and needs its own pass.
int Straw_00552490::Get(void* dest, int slen)
{
    int total = 0;

    if (dest == 0 || slen < 1) {
        return 0;
    }

    while (slen > 0) {
        if (this->Counter > 0) {
            int len = (slen < this->Counter) ? slen : this->Counter;

            char* source;
            if (this->Control == 1) {
                source = (this->Buffer + this->Header.UnpackedSize) - this->Counter;
            } else {
                source = (this->Buffer2 + this->Header.PackedSize) - this->Counter + 4;
            }

            memmove(dest, source, len);
            dest = (char*)dest + len;
            slen -= len;
            total += len;
            this->Counter -= len;
        }

        if (slen == 0) {
            break;
        }

        if (this->Control == 1) {
            if (this->Get_006C98E0(&this->Header, 4) != 4) {
                break;
            }

            char* ptr = (this->SafetyMargin + this->BlockSize
                         - this->Header.PackedSize) + this->Buffer;
            if (this->Get_006C98E0(ptr, this->Header.PackedSize)
                != this->Header.PackedSize) {
                break;
            }

            FUN_00551C60(ptr, this->Buffer, 0);
            this->Counter = this->Header.UnpackedSize;
        } else {
            this->Header.UnpackedSize =
                (unsigned short)this->Get_006C98E0(this->Buffer, this->BlockSize);
            if (this->Header.UnpackedSize == 0) {
                break;
            }

            this->Header.PackedSize =
                (unsigned short)FUN_00551E50(this->Buffer, this->Buffer2 + 4,
                                             this->Header.UnpackedSize);
            memmove(this->Buffer2, &this->Header, 4);
            this->Counter = this->Header.PackedSize + 4;
        }
    }

    return total;
}
