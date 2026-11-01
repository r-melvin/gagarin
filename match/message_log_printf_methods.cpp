// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x5BD1F0 is a variadic member function (so __cdecl with `this` as the first
// stack word): when the byte at 0xABF23A is set it formats into a 256-byte
// frame buffer with vsprintf 0x7CB7BA, forces the last byte to zero and hands
// the buffer to 0x5BD0D0, a __thiscall method of the same object (that
// method also tests 0xABF23A first and reads members from +0x271C). Class,
// method and global names are descriptive; no size is asserted.
#include <stdarg.h>
#include <stddef.h>

// LIBRARY: GAMEMD 0x7CB7BA (decl; reloc) -- CRT vsprintf.
extern "C" int __cdecl vsprintf(char* buffer, const char* format, va_list args);
// LIBRARY: GAMEMD 0x7CA858 (decl; reloc) -- CRT vswprintf.
extern "C" int __cdecl vswprintf(wchar_t* buffer, const wchar_t* format, va_list args);
// LIBRARY: GAMEMD 0x7C8EF4 (decl; reloc) -- CRT sprintf.
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

class MessageLog_005BD0D0
{
public:
    // FUNCTION: GAMEMD 0x5BD0D0 (decl; reloc)
    void FUN_005BD0D0(const char* text);
    // FUNCTION: GAMEMD 0x5BD1F0
    void __cdecl Printf(const char* format, ...);
    // FUNCTION: GAMEMD 0x5BD240
    void __cdecl PrintfWide(const wchar_t* format, ...);

    // GLOBAL: GAMEMD 0xABF23A
    static bool Enabled;
};

// FUNCTION: GAMEMD 0x5BD1F0
void __cdecl MessageLog_005BD0D0::Printf(const char* format, ...)
{
    if (Enabled) {
        char text[256];
        va_list args;
        va_start(args, format);
        vsprintf(text, format, args);
        text[sizeof(text) - 1] = '\0';
        FUN_005BD0D0(text);
    }
}

// STRING: GAMEMD 0x82D020 -- "%S"
// FUNCTION: GAMEMD 0x5BD240
// Wide-character variant of Printf: formats with vswprintf, narrows the
// result through "%S", then hands it to the same log method.
void __cdecl MessageLog_005BD0D0::PrintfWide(const wchar_t* format, ...)
{
    if (Enabled) {
        wchar_t wide[256];
        char text[256];
        va_list args;
        va_start(args, format);
        vswprintf(wide, format, args);
        sprintf(text, "%S", wide);
        FUN_005BD0D0(text);
    }
}
