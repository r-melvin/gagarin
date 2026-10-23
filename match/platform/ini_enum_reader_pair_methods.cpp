// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Two enumerated-value readers over an INI object, the same shape as the land
// type reader at 0x4754B0: the caller's default is turned into its name, the
// key is read as text into a 128-byte buffer with that name as the fallback,
// and a key that was present is turned back into a value; an absent key gives
// the default itself back. Each address uses its own pair of name/value
// conversion routines.

struct Ini_00476FC0
{
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- ReadString(section, key, default, buffer, size).
    int ReadString(const char* section, const char* key, const char* defaultValue,
                   char* buffer, int size);
    int ReadEnum_00476FC0(const char* section, const char* key, int defaultValue);
    int ReadEnum_00477050(const char* section, const char* key, int defaultValue);
};

// FUNCTION: GAMEMD 0x48E030 (decl; reloc) -- value -> name.
const char* FUN_0048E030(int value);
// FUNCTION: GAMEMD 0x48DFF0 (decl; reloc) -- name -> value.
int FUN_0048DFF0(const char* name);
// FUNCTION: GAMEMD 0x48E090 (decl; reloc) -- value -> name.
const char* FUN_0048E090(int value);
// FUNCTION: GAMEMD 0x48E050 (decl; reloc) -- name -> value.
int FUN_0048E050(const char* name);

// FUNCTION: GAMEMD 0x476FC0
int Ini_00476FC0::ReadEnum_00476FC0(const char* section, const char* key, int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, FUN_0048E030(defaultValue), buffer, sizeof(buffer))) {
        return FUN_0048DFF0(buffer);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x477050
int Ini_00476FC0::ReadEnum_00477050(const char* section, const char* key, int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, FUN_0048E090(defaultValue), buffer, sizeof(buffer))) {
        return FUN_0048E050(buffer);
    }

    return defaultValue;
}
