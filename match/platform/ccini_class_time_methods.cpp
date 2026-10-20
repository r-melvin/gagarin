// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x52A940. The format
//   string is read out of the image at 0x81F0A8.

#include "ccini_class_time_methods.h"

// FUNCTION: GAMEMD 0x52A940
//
// Write a tick count as an "hh:mm:ss" string. The value is divided by sixty
// three times in a row — ticks to seconds, seconds to minutes, minutes to
// hours — and the two lower fields are reduced modulo sixty. All three
// divisions come out as the same 0x88888889 magic-multiply, and the two
// remainders reuse the quotient already in hand.
//
// The remainders are spelled `q - (q / 60) * 60` rather than `q % 60`: VC6
// does not strength-reduce a signed `%` by a constant into the shared
// quotient, it emits a separate CDQ/IDIV, where retail has the LEA/SHL/SUB
// multiply-back off the quotient it already computed.
bool CCINI_0052A940::WriteTime(const char* section, const char* key, int value)
{
    char buffer[32];

    int seconds = value / 60;
    int minutes = seconds / 60;
    int hours   = minutes / 60;

    // STRING: GAMEMD 0x81F0A8 "%02d:%02d:%02d"
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes - hours * 60, seconds - minutes * 60);

    return WriteString(section, key, buffer);
}
