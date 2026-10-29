// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// Each entry below records its exact extent and compiled ABI symbol;
// the symbols encode the inferred member calling convention and types. The
// methods touch no object fields. The shared declarations and RTTI/table
// identity are in blitter.h and blit_plain.h. This TU makes no table/G-body
// emission claim.
// Paired /GX and no-/GX probes match all eight bodies and relocation fields.
#include <string.h>
#include "blit_plain.h"

// LIBRARY: GAMEMD 0x7CA090 -- CRT memmove (__cdecl).

// FUNCTION: GAMEMD 0x7BC750
// BlitPlain<unsigned char>::BlitCopy
// Retail span: 0x21 bytes; symbol ?BlitCopy@?$BlitPlain@E@@UAEXPAXPBXHHPAG2HH@Z.
// This is an explicit specialization so every address annotation appears in
// ascending retail order in the implementation TU.
template <>
void BlitPlain<unsigned char>::BlitCopy(void* dest, const void* src, int len,
                                         int, unsigned short*, unsigned short*,
                                         int, int)
{
    memcpy(dest, src, len * sizeof(unsigned char));
}

// FUNCTION: GAMEMD 0x7BC780
// BlitPlain<unsigned char>::BlitMove
// Retail span: 0x1A bytes; symbol ?BlitMove@?$BlitPlain@E@@UAEXPAXPBXHHPAG2H@Z.
template <>
void BlitPlain<unsigned char>::BlitMove(void* dest, const void* src, int len,
                                         int, unsigned short*, unsigned short*,
                                         int)
{
    memmove(dest, src, len * sizeof(unsigned char));
}

// FUNCTION: GAMEMD 0x7BC7A0
// BlitPlain<unsigned char>::BlitCopyTint
// Retail span: 0x21 bytes; symbol ?BlitCopyTint@?$BlitPlain@E@@UAEXPAXPBXHHPAG2HHG@Z.
template <>
void BlitPlain<unsigned char>::BlitCopyTint(void* dest, const void* src,
                                             int len, int, unsigned short*,
                                             unsigned short*, int, int,
                                             unsigned short)
{
    memcpy(dest, src, len * sizeof(unsigned char));
}

// FUNCTION: GAMEMD 0x7BC7D0
// BlitPlain<unsigned char>::BlitMoveTint
// Retail span: 0x1A bytes; symbol ?BlitMoveTint@?$BlitPlain@E@@UAEXPAXPBXHHPAG2HG@Z.
template <>
void BlitPlain<unsigned char>::BlitMoveTint(void* dest, const void* src,
                                             int len, int, unsigned short*,
                                             unsigned short*, int, unsigned short)
{
    memmove(dest, src, len * sizeof(unsigned char));
}

// FUNCTION: GAMEMD 0x7BC7F0
// BlitPlain<unsigned short>::BlitCopy
// Retail span: 0x24 bytes; symbol ?BlitCopy@?$BlitPlain@G@@UAEXPAXPBXHHPAG2HH@Z.
template <>
void BlitPlain<unsigned short>::BlitCopy(void* dest, const void* src, int len,
                                          int, unsigned short*, unsigned short*,
                                          int, int)
{
    memcpy(dest, src, len * sizeof(unsigned short));
}

// FUNCTION: GAMEMD 0x7BC820
// BlitPlain<unsigned short>::BlitMove
// Retail span: 0x1D bytes; symbol ?BlitMove@?$BlitPlain@G@@UAEXPAXPBXHHPAG2H@Z.
template <>
void BlitPlain<unsigned short>::BlitMove(void* dest, const void* src, int len,
                                          int, unsigned short*, unsigned short*,
                                          int)
{
    memmove(dest, src, len * sizeof(unsigned short));
}

// FUNCTION: GAMEMD 0x7BC840
// BlitPlain<unsigned short>::BlitCopyTint
// Retail span: 0x24 bytes; symbol ?BlitCopyTint@?$BlitPlain@G@@UAEXPAXPBXHHPAG2HHG@Z.
template <>
void BlitPlain<unsigned short>::BlitCopyTint(void* dest, const void* src,
                                              int len, int, unsigned short*,
                                              unsigned short*, int, int,
                                              unsigned short)
{
    memcpy(dest, src, len * sizeof(unsigned short));
}

// FUNCTION: GAMEMD 0x7BC870
// BlitPlain<unsigned short>::BlitMoveTint
// Retail span: 0x1D bytes; symbol ?BlitMoveTint@?$BlitPlain@G@@UAEXPAXPBXHHPAG2HG@Z.
template <>
void BlitPlain<unsigned short>::BlitMoveTint(void* dest, const void* src,
                                              int len, int, unsigned short*,
                                              unsigned short*, int,
                                              unsigned short)
{
    memmove(dest, src, len * sizeof(unsigned short));
}
