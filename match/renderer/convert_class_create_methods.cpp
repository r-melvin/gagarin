// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x72ADE0.

#include "convert_class_create_methods.h"
#include "../_layout/memory_buffer.h"

// FUNCTION: GAMEMD 0x72ADE0
//
// Build a palette and a convert (colour-remap table) out of a palette file.
// The whole file is slurped through a stack file object; a fresh 0x300-byte
// palette is allocated and zeroed, each of the 256 file triples is shifted from
// 6-bit VGA range into 8-bit range and stored, the file buffer is released, and
// a 0x188-byte convert is built against the new palette and the global surface.
// A missing file leaves both out-parameters untouched. The stack file object is
// torn down inline on both paths.
//
// Phrasing notes (load-bearing):
//   * Both allocations are written out by hand as operator new / null test /
//     constructor call. A real `new ConvertClass(...)` makes VC6 emit a /GX
//     exception frame retail does not have (the same trap as 0x641DB0).
//   * The destination is indexed off the *reference* parameter
//     (`pPalette[i % 256]`), which is why retail re-reads the pointer through
//     the reference on every iteration instead of caching it.
//   * `i % 256` on a signed `int` is what produces retail's
//     `AND ECX,0x800000FF; JNS; DEC; OR ECX,0xFFFFFF00; INC` sign fix-up.
//
// PARTIAL (17.3%, 17/98). Two residual deltas, both register allocation:
//   1. cl 8804 forms a shared zero in EBX (`XOR EBX,EBX`, then `CMP reg,EBX`
//      for the three null tests and `MOV byte ptr [ECX],BL` for the palette
//      fill); retail has no zero register at all — `TEST EBP,EBP`,
//      `TEST EAX,EAX` and three `MOV byte ptr [..],0` immediates. That costs
//      2 XOR / 3 CMP against retail's 3 TEST and, because EBX is taken, pushes
//      the palette out-reference into EDI, adding a fourth entry-time PUSH and
//      shrinking the frame from 0x78 to 0x70 (retail spills the reference to
//      [ESP+0x14] and reloads it at the top of every iteration; we keep it
//      live in EDI). Every displacement downstream then differs.
//   2. Retail addresses the source triple through three reduced induction
//      pointers — base EAX = data+1 with the other two as *register* offsets
//      EDI = -1 and EBP = +1 (`MOV CL,[EDI+EAX]`, `MOV DL,[EAX+EBP]`) — where
//      cl 8804 folds them into one cursor with constant displacements.
// Variants tried: the index form `data[i*3+k]` (17.3%, kept); three explicit
// source cursors `sr/sg/sb` advancing by 3 (7.1% — this *does* reproduce
// retail's register-indexed form, but with one offset register instead of two,
// since cl 8804 folds EBP = EDI+2 back into a displacement, and the lower head
// alignment costs more than the loop gains); `new ColorStruct[0x100]` with a
// zeroing constructor in place of the hand-written fill (7.1%, byte-identical
// to the hand-written fill — confirms the fill shape is right); implicit truth
// tests `if (data)` / ternary for the convert allocation (7.1%, no change);
// G-before-R member order in the temp (17.3%, identical bytes).
// Lift pass 2 (2026-09-18): one more rejected - `volatile ColorStruct*` for the
// fill cursor, to try to force retail's three immediate byte stores instead of
// cl's `MOV byte ptr [..],BL`; identical stream, 17.3%. Delta 1 is the banked
// 8447-vs-8804 shared-zero-register class (the inverse direction of the usual
// one) and is not steerable from source; best form kept at 17.3%.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): this is the ONE function in
// the register-residual sweep where the diagnostic fires positively. Retail's
// prologue pushes only EBX and EBP (`SUB ESP,0x78; PUSH EBX; PUSH EBP; MOV
// EBX,EDX; PUSH ECX`) and sinks PUSH ESI / PUSH EDI into the palette-conversion
// region, popping them again mid-function at `POP EDI; POP ESI` before the
// shared tail — two separate epilogues. Our output hoists PUSH EDI into the
// prologue and carries it to the single final epilogue, which is exactly the
// merged-return shape the eleventh batch describes. The frame is also 0x70
// against retail's 0x78 and the multiset is not yet identical (five retail-only
// MOVs, two SUBs and a JMP missing, three TESTs spelled as CMPs against the
// zero register), so the body needs structural work before the lever can be
// tested cleanly: the conversion loop wants to be its own inline function
// carrying its own return, which should un-merge the two epilogues and restore
// the sunk ESI/EDI pushes. Not attempted in this pass.
void ConvertClass::CreateFromFile(const char* pFilename,
                                  ColorStruct_0072ADE0*& pPalette,
                                  ConvertClass*& pDestination)
{
    File_0072ADE0 file;
    file.FUN_004739F0(pFilename);

    unsigned char* data = (unsigned char*)file.ReadWholeFile();
    if (data != 0) {
        ColorStruct_0072ADE0* pal =
            (ColorStruct_0072ADE0*)FUN_007C8E17(0x100 * sizeof(ColorStruct_0072ADE0));
        if (pal != 0) {
            ColorStruct_0072ADE0* p = pal;
            int n = 0x100;
            do {
                p->R = 0;
                p->G = 0;
                p->B = 0;
                ++p;
            } while (--n != 0);
        } else {
            pal = 0;
        }
        pPalette = pal;

        for (int i = 0; i < 0x100; ++i) {
            ColorStruct_0072ADE0 c;
            c.R = (unsigned char)(data[i * 3 + 0] << 2);
            c.G = (unsigned char)(data[i * 3 + 1] << 2);
            c.B = (unsigned char)(data[i * 3 + 2] << 2);
            pPalette[i % 256] = c;
        }

        FUN_007C8B3D(data);

        ConvertClass* raw = (ConvertClass*)FUN_007C8E17(sizeof(ConvertClass));
        ConvertClass* made;
        if (raw != 0) {
            made = raw->FUN_0048E740(pPalette, pPalette, DAT_00887310, 1, 0);
        } else {
            made = 0;
        }
        pDestination = made;
    }

    file.Vtbl    = &VT_007E16B0;
    file.Reset64 = 0;
    ((MemoryBuffer*)file.Sub58)->Clear();
    file.Vtbl    = &VT_007E1668;
    FUN_00431B80(&file);
}
