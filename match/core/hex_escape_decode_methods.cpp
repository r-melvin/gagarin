// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.

// GLOBAL: GAMEMD 0x89F118 -- decode output buffer (its length is not established here).
extern char DAT_0089F118[];

// The value of one hexadecimal digit, 0 for any other character.
inline int HexDigit(char c)
{
    if (c <= '9' && c >= '0')
        return c - '0';
    if (c <= 'f' && c >= 'a')
        return c - 'a' + 10;
    if (c <= 'F' && c >= 'A')
        return c - 'A' + 10;
    return 0;
}

// FUNCTION: GAMEMD 0x49B540
// Copies a string into the shared decode buffer, turning "=" followed by up to two
// hexadecimal digits into the byte they spell; returns the buffer.
char* __fastcall FUN_0049B540(const char* text)
{
    char* out = DAT_0089F118;
    while (*text != 0) {
        if (*text == '=') {
            if (text[1] == 0)
                break;
            *out = HexDigit(text[1]);
            text++;
            if (text[1] != 0) {
                *out = *out << 4;
                *out |= HexDigit(text[1]);
                text++;
            }
        } else {
            *out = *text;
        }
        text++;
        out++;
    }
    *out = 0;
    return DAT_0089F118;
}
