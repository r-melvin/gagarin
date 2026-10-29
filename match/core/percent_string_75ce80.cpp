// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Evidence: disassembled from the user's gamemd.exe v1.001 at 0x75CE80; the
//   constant at 0x7E3808 is the double 0.01 (bytes 7B14AE47E17A843F).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// CRT atoi (0x7C9BFD).
int    __cdecl P_atoi(const char* str);
// CRT strchr (0x7CAF30).
char*  __cdecl P_strchr(const char* str, int ch);
// CRT atof (0x7C9D66).
double __cdecl P_atof(const char* str);

// Parses a number that may carry a '%' suffix: with the suffix the integer
// part is scaled by 0.01, otherwise the text is read as a plain double.
// FUNCTION: GAMEMD 0x0075CE80
double __fastcall ParsePercentOrNumber_0075CE80(const char* text)
{
    if (P_strchr(text, '%') != 0) {
        return P_atoi(text) * 0.01;
    }
    return P_atof(text);
}
