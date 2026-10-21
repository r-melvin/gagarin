// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
//   Every address, constant and member offset below was read numerically off
//   the user's own retail gamemd.exe v1.001 through the local Ghidra CLI. No
//   YRpp header, RA1 file or TS++ header was consulted for this cluster - the
//   run carries no runtime type information of its own and was identified from
//   the CRT static-initialiser table instead.
//
// The file-scope dynamic initialisers of the rocket-locomotion translation
// unit, 0x661CB0-0x661EB6, fourteen bodies.
//
// HOW THE RUN WAS FOUND AND IDENTIFIED. The whole 0x660460-0x662240 range was
// swept as raw bytes (`ghidra memory read` piped through
// `objdump -D -b binary -m i386`) and its entry points taken from the 0x90 pad
// runs that end on a four-byte boundary. That found 73 candidate entries where
// the Ghidra function list knows about 38, and NONE of these fourteen is in the
// function list. Nothing in the analysed code calls them directly, which is
// exactly the systematic blind spot the sweep exists to cover: the only
// references are DATA references from 0x8147C4-0x8147FB, a contiguous slice of
// the CRT `_initterm` table. So each body here is the compiler-generated
// dynamic initialiser for one file-scope variable, and the slice's bounds are
// what proves the fourteen belong to one translation unit.
//
// WHICH translation unit is settled by the block they write. Every one of them
// stores into 0x00B04E00-0x00B04E7B, and the constructor at 0x661EC0 -
// RocketLocomotionClass, the next body in the same address run - copies
// 0xB04E38/3C/40 straight into its own +0x18/+0x1C/+0x20. So this is the
// rocket locomotor's own file-scope configuration block.
//
// WHAT THE VALUES ARE. 0xB04E20 is the diagonal of a 256x256-lepton cell
// (sqrt(256^2 + 256^2) = 362.04); 0xB04E00, 0xB04E28 and 0xB04E50 are 90, 60
// and 45 degrees in radians; 0xB04E70 is the cell diagonal per sixtieth and
// 0xB04E58 its reciprocal; 0xB04E78 is half the cell diagonal projected through
// the 30-degree difference of the first two angles, and 0xB04E30, 0xB04E48 and
// 0xB04E6C are derived from it.
#ifndef GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_GLOBALS_H
#define GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_GLOBALS_H

#include <stddef.h>
#include <math.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Compiler-facing views of the table-driven floating-point helpers. The
// stack double argument and ST(0) result do not establish the original return
// type. Float below preserves this TU's binding; it is not a recovered source
// declaration. Callers reserve and release the eight argument bytes.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4CAC40  square root by exponent halving plus a mantissa
//   table at 0x8650BC, with the zero and negative cases folded out first.
extern "C" float __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50  sine over a 4096-entry table at 0x85D0A4; the
//   argument is scaled by 4096/(2*pi) = 651.8986 and masked to twelve bits.
extern "C" float __cdecl FUN_004CAD50(double radians);
// FUNCTION: GAMEMD 0x4CADE0  arc tangent over a 4097-entry table at 0x8610B4
//   stepped by 0.0244133547, saturating to pi/2 past the end of the table.
extern "C" float __cdecl FUN_004CADE0(double ratio);

// ---------------------------------------------------------------------------
// The two named constants this file reads rather than spelling as literals.
// They live in their own .rdata slots rather than in the compiler's literal
// pool at 0x7E1708-0x7E1747, and the tell is constant folding: retail loads BOTH
// operands of the three degree-to-radian products from memory, which only
// happens when one of them is a named object cl may not fold against.
// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0x7F0B08  60.0 - the subdivision the cell diagonal is cut into.
extern const double DAT_007F0B08;
// GLOBAL: GAMEMD 0x7F0B10  0.017453292519943295 - degrees to radians.
extern const double DAT_007F0B10;

// ---------------------------------------------------------------------------
// The configuration block at 0x00B04E00. The scalars are declared one by one
// because the run gives no evidence that groups them; the four aggregates are
// declared as real structs, because each one IS initialised by a single body
// storing consecutive fields, which is evidence for the grouping and pins the
// member offsets numerically.
// ---------------------------------------------------------------------------

// Four consecutive dwords zeroed together by the body at 0x661EA0.
struct GgQuadInt
{
    int A;  // +0x00
    int B;  // +0x04
    int C;  // +0x08
    int D;  // +0x0C
};
GG_STATIC_ASSERT(offsetof(GgQuadInt, A) == 0x00);
GG_STATIC_ASSERT(offsetof(GgQuadInt, B) == 0x04);
GG_STATIC_ASSERT(offsetof(GgQuadInt, C) == 0x08);
GG_STATIC_ASSERT(offsetof(GgQuadInt, D) == 0x0C);
GG_STATIC_ASSERT(sizeof(GgQuadInt) == 0x10);

// Two consecutive words zeroed together by the body at 0x661E50. The stores are
// `MOV word ptr ds:[...],AX`, so these really are 16-bit members and not one
// dword: a whole-object clear would have been a single dword move.
struct GgPairShort
{
    short A;  // +0x00
    short B;  // +0x02
};
GG_STATIC_ASSERT(offsetof(GgPairShort, A) == 0x00);
GG_STATIC_ASSERT(offsetof(GgPairShort, B) == 0x02);
GG_STATIC_ASSERT(sizeof(GgPairShort) == 0x04);

// Three consecutive dwords, written together by the bodies at 0x661E60 and
// 0x661E80. The first of the two is the triple RocketLocomotionClass's
// constructor copies into its own +0x18/+0x1C/+0x20 at 0x661EC8-0x661EE5, which
// is what pins all three offsets and the 12-byte size.
struct GgTripleInt
{
    int A;  // +0x00
    int B;  // +0x04
    int C;  // +0x08
};
GG_STATIC_ASSERT(offsetof(GgTripleInt, A) == 0x00);
GG_STATIC_ASSERT(offsetof(GgTripleInt, B) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTripleInt, C) == 0x08);
GG_STATIC_ASSERT(sizeof(GgTripleInt) == 0x0C);

// GLOBAL: GAMEMD 0xB04E00  90 degrees in radians.
extern double      DAT_00B04E00;
// GLOBAL: GAMEMD 0xB04E08  four dwords, cleared at startup.
extern GgQuadInt   DAT_00B04E08;
// GLOBAL: GAMEMD 0xB04E18  two words, cleared at startup.
extern GgPairShort DAT_00B04E18;
// GLOBAL: GAMEMD 0xB04E20  the 256x256-lepton cell diagonal, 362.04.
extern double      DAT_00B04E20;
// GLOBAL: GAMEMD 0xB04E28  60 degrees in radians.
extern double      DAT_00B04E28;
// GLOBAL: GAMEMD 0xB04E30  arc tangent of 0xB04E78 over 256.
extern double      DAT_00B04E30;
// GLOBAL: GAMEMD 0xB04E38  the triple the rocket locomotor seeds itself from.
extern GgTripleInt DAT_00B04E38;
// GLOBAL: GAMEMD 0xB04E48  arc tangent of twice 0xB04E78 over the cell diagonal.
extern double      DAT_00B04E48;
// GLOBAL: GAMEMD 0xB04E50  45 degrees in radians.
extern double      DAT_00B04E50;
// GLOBAL: GAMEMD 0xB04E58  the reciprocal of 0xB04E70.
extern double      DAT_00B04E58;
// GLOBAL: GAMEMD 0xB04E60  a triple seeded to 0x80, 0x80, 0.
extern GgTripleInt DAT_00B04E60;
// GLOBAL: GAMEMD 0xB04E6C  four times 0xB04E78, rounded.
extern int         DAT_00B04E6C;
// GLOBAL: GAMEMD 0xB04E70  the cell diagonal per sixtieth.
extern double      DAT_00B04E70;
// GLOBAL: GAMEMD 0xB04E78  half the cell diagonal projected through 30 degrees.
extern int         DAT_00B04E78;

#endif  // GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_GLOBALS_H
