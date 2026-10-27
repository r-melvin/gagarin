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
// The receiver arrives in ECX and the stream as the single stack argument
// (`RET 4`), so each entry point is a __thiscall member of the vector. Modelled
// earlier as a __fastcall free function with an unused EDX parameter, cl
// scheduled the loop-counter update ahead of the count reload (88.9%); as a
// member function it emits retail's order and all ten match.

#include "vector_stream_save_family_methods.h"

// FUNCTION: GAMEMD 0x0067A3C0
GG_VECTOR_STREAM_SAVE_BODY(0067A3C0)

// FUNCTION: GAMEMD 0x0067A4A0
template<> int TypeList<const AnimTypeClass*>::FUN_0067A4A0(IStream* stream)
{
    int count = Count;
    stream->Write(&count, 4, 0);
    for (int i = 0; i < count; ++i) {
        stream->Write(&Items[i], 4, 0);
    }
    return count;
}

// FUNCTION: GAMEMD 0x0067A520
template<> int TypeList<int>::FUN_0067A520(IStream* stream)
{
    int count = Count;
    stream->Write(&count, 4, 0);
    for (int i = 0; i < count; ++i) {
        stream->Write(&Items[i], 4, 0);
    }
    return count;
}

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
template<> int TypeList<const ParticleSystemTypeClass*>::FUN_00717B20(IStream* stream)
{
    int count = Count;
    stream->Write(&count, 4, 0);
    for (int i = 0; i < count; ++i) {
        stream->Write(&Items[i], 4, 0);
    }
    return count;
}
