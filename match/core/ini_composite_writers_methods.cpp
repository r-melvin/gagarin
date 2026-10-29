// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// SPDX-License-Identifier: GPL-3.0-or-later
// Small INI writers that format a composite value into a stack buffer and
// forward it to the string writer at 0x528660 (this in ECX, three pushed
// pointers). Each body pops three arguments (RET 0xC): section, key and the
// value by reference. The 0x52A610 writer pops one argument and hands two
// encoded key blocks to the uuencoded block writer at 0x526E80.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../platform/ccini_class_methods.h"

// LIBRARY: GAMEMD 0x7C8EF4 (decl; reloc) -- CRT sprintf.
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// Four ints read at +0/+4/+8/+0xC by 0x527C10.
struct IniIntQuad { int A; int B; int C; int D; };
GG_STATIC_ASSERT(offsetof(IniIntQuad, D) == 0xC);
// Three ints read at +0/+4/+8 by 0x529BF0.
struct IniIntTriple { int A; int B; int C; };
GG_STATIC_ASSERT(offsetof(IniIntTriple, C) == 0x8);
// Three floats read at +0/+4/+8 by 0x52A040 (FLD DWORD, widened for printf).
struct IniFloatTriple { float A; float B; float C; };
GG_STATIC_ASSERT(offsetof(IniFloatTriple, C) == 0x8);

// Key object whose two encoders (0x631FC0, 0x631FE0) fill a buffer and return
// the encoded length.
class IniKeyBlockSource
{
public:
    // FUNCTION: GAMEMD 0x631FC0 (decl; reloc)
    int EncodeFirst(char* buffer) const;
    // FUNCTION: GAMEMD 0x631FE0 (decl; reloc)
    int EncodeSecond(char* buffer) const;
};



// FUNCTION: GAMEMD 0x527C10
bool INIClass::WriteIntQuad(const char* section, const char* key, const IniIntQuad& value)
{
    char buffer[64];
    sprintf(buffer, "%d,%d,%d,%d", value.A, value.B, value.C, value.D);
    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x529BF0
bool INIClass::WriteIntTriple(const char* section, const char* key, const IniIntTriple& value)
{
    char buffer[56];
    sprintf(buffer, "%d,%d,%d", value.A, value.B, value.C);
    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x52A040
bool INIClass::WriteFloatTriple(const char* section, const char* key, const IniFloatTriple& value)
{
    char buffer[56];
    sprintf(buffer, "%f,%f,%f", value.A, value.B, value.C);
    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x52A610
bool CCINIClass::WriteKeyBlocks(const IniKeyBlockSource& key)
{
    char buffer[512];
    WriteUUBlock("PublicKey", buffer, key.EncodeFirst(buffer));
    WriteUUBlock("PrivateKey", buffer, key.EncodeSecond(buffer));
    return true;
}
