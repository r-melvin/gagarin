// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x528E00.

#include "ccini_class_unicode_methods.h"

// FUNCTION: GAMEMD 0x528E00
//
// Write a Unicode string as a comma-separated list of hexadecimal code units.
// A scratch buffer of eight bytes per character (up to four hex digits, the
// comma, and slack) plus the terminator is allocated, each code unit is
// rendered with _itoa at the cursor and a "," appended, and the cursor is
// re-derived from the buffer start before the string pointer advances. The
// list then goes through WriteString and the buffer is freed. A null string or a failed allocation writes nothing and reports
// false.
//
// Two spellings are load-bearing. The allocation size is `n + sizeof(char)`
// with `n = wcslen * 8` in its own local: every form that adds a literal 1
// (`* 8 + 1`, `(x << 3) + 1`, `+= 1`, `++n`, `+ 1U`, `+ (string != 0)`) is
// fused by cl into one `LEA EAX,[EAX*8+1]`, where retail has `SHL EAX,3;
// INC EAX`; the sizeof term keeps the two operations apart. The terminator
// store goes through the cursor (`*cursor = '\0'` after `cursor = buffer`)
// so that cl emits the immediate `MOV byte ptr [EBP],0` (C6 45 00 00);
// written as `buffer[0] = 0` it substitutes the zero already held in BL for
// the false result (`MOV [EBP],BL`, 88 5D 00), which is the same bytes
// minus one and shifts every later jump target. The loop is a `while` with
// `string++` as its last statement.
bool CCINI_00528E00::WriteUnicodeString(const char* section, const char* key,
                                        const wchar_t* string)
{
    bool result = false;

    if (string != 0) {
        unsigned n = wcslen(string) * 8;
        char* buffer = (char*)FUN_007C8E17(n + sizeof(char));
        if (buffer != 0) {
            char* cursor = buffer;
            *cursor = '\0';
            while (*string != 0) {
                _itoa(*string, cursor, 16);
                strcat(cursor, STR_00817F70);
                cursor = buffer + strlen(buffer);
                string++;
            }
            result = this->WriteString(section, key, buffer);
            FUN_007C8B3D(buffer);
        }
    }

    return result;
}
