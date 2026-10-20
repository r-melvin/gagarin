// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. Each of these ten functions serialises one growable vector of
//   four-byte elements to a COM stream: write the element count, then write
//   each element in turn, all through IStream::Write with a null pcbWritten.
//   Every instance is the same 75 bytes with no relocation at all — the
//   element type is erased by the COM indirection and the literal length — so
//   the body is written once as a macro and expanded per entry point.
//   Ordered ascending by retail address.
//
// STATUS: PARTIAL, 88.9% (32/36 instructions, multiset identical). The only
// residual is a two-position scheduling swap, twice: retail issues the reload
// of the count ahead of the induction-variable update (`MOV EAX,[ESP+0xC];
// XOR ESI,ESI` and `MOV EAX,[ESP+0xC]; INC ESI`) where cl issues the update
// first. Fourteen spellings were measured against this address in one
// match_all run — `void` and `int` returns, `count > i`, postfix and prefix
// increments, while/for/do-while/for(;;)+break, a hoisted guard with an early
// return, a named element pointer, `self->Items + i`, a pointer-to-the-count,
// a struct-wrapped count and a volatile count — and every structurally correct
// one lands on exactly 88.9%; the rest are worse. Flag bisection over /O1,
// /O2, /Ox, /Ot /Og /Oi /Oy, /Gy on and off, /G5, /G6 and /Gr moves nothing
// either (/G6 is worse, /O1 is a different body).
//
// A later pass added the boundary levers of the ninth and tenth batches and
// they do not reach this either: the loop moved into a free inline function
// taking the container as a parameter, the same with the count passed by
// pointer so the reload is the helper's own parameter read, both writes
// inside one helper, the element write as its own helper, the index declared
// ahead of the count, a while loop with a trailing increment, and a guarded
// do/while with the increment in the condition. Six of the eight land on
// exactly 88.9% again, the container-parameter helper collapses to 10.3% and
// the do/while to 41.7%. Twenty-two structurally correct spellings now agree
// on this number, so the swap is not reachable from the source side and this
// is the strongest candidate in the tree for a genuine 8447-versus-8804
// scheduling difference rather than an unfound lever.

#include "vector_stream_save_family_methods.h"

// FUNCTION: GAMEMD 0x0067A3C0
GG_VECTOR_STREAM_SAVE_BODY(0067A3C0)

// FUNCTION: GAMEMD 0x0067A4A0
GG_VECTOR_STREAM_SAVE_BODY(0067A4A0)

// FUNCTION: GAMEMD 0x0067A520
GG_VECTOR_STREAM_SAVE_BODY(0067A520)

// FUNCTION: GAMEMD 0x0067A630
GG_VECTOR_STREAM_SAVE_BODY(0067A630)

// FUNCTION: GAMEMD 0x0067A6E0
GG_VECTOR_STREAM_SAVE_BODY(0067A6E0)

// FUNCTION: GAMEMD 0x0067A770
GG_VECTOR_STREAM_SAVE_BODY(0067A770)

// FUNCTION: GAMEMD 0x0067A7D0
GG_VECTOR_STREAM_SAVE_BODY(0067A7D0)

// FUNCTION: GAMEMD 0x0067A850
GG_VECTOR_STREAM_SAVE_BODY(0067A850)

// FUNCTION: GAMEMD 0x0067A8E0
GG_VECTOR_STREAM_SAVE_BODY(0067A8E0)

// FUNCTION: GAMEMD 0x00717B20
GG_VECTOR_STREAM_SAVE_BODY(00717B20)
