// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4756F0, 0x4757D0,
//   0x475820, 0x475870, 0x4758C0, 0x4758F0, 0x475950, 0x475980, 0x4759D0
//   and 0x4759F0.

#include "ccini_class_theater_theme_methods.h"

// Find a movie record's index in the registry. Retail inlined this and
// kept the record pointer in the return register across the whole search,
// which only the free-function form over the global container reproduces:
// written as a loop in the reader's own body, the pointer is homed in a
// callee-saved register and the whole register rotation turns over (6.0%
// against 100%).
static __forceinline int IndexOfMovie(MovieType_006A4550* movie)
{
    int count = DAT_008B4120.Count;

    for (int i = 0; i < count; ++i) {
        if (DAT_008B4120.Items[i] == movie) {
            return i;
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x4756F0
//
// Read a movie by name. An absent key leaves the caller's index alone; a
// name already in the registry gives its index straight back; and a name
// the registry has never seen is registered on the spot, the new record's
// index being recovered by looking the pointer back up in the vector.
int CCINI_004756F0::ReadMovie(const char* section, const char* key,
                              int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        int index = FUN_006A46D0(buffer);

        if (index == -1) {
            MovieType_006A4550* movie = new MovieType_006A4550(buffer);

            return IndexOfMovie(movie);
        }

        return index;
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x4757D0
//
// Read a name and parse it; both an absent key and an unparseable name fall
// back on the caller's value, which is why the two arms share one epilogue.
int CCINI_004756F0::FUN_004757D0(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        int value = FUN_0048DF30(buffer);

        if (value != -1) {
            return value;
        }
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x475820
//
// Write an index out as its name, with an out-of-range index spelled
// "<none>". The bound test is unsigned, so a negative index takes the
// "<none>" arm too.
bool CCINI_004756F0::FUN_00475820(const char* section, const char* key,
                                  unsigned int index)
{
    if (index >= DAT_00ABF3A0) {
        return WriteString(section, key, STR_00817474);
    }

    return WriteString(section, key, DAT_00ABF394[index]);
}

// FUNCTION: GAMEMD 0x475870
//
// The 0x4757D0 reader over the 0x48DBE0 parser, without the -1 retry.
int CCINI_004756F0::FUN_00475870(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        return FUN_0048DBE0(buffer);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x4758C0
//
// Write a theater index out as that theater's inline name. The record is
// 0x70 bytes wide, which is why the index arrives as a shift-and-subtract
// rather than a scaled index.
bool CCINI_004756F0::WriteTheater(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_007E1B78[index].Name);
}

// FUNCTION: GAMEMD 0x4758F0
//
// Read a theme by name off the theme player itself rather than a table.
int CCINI_004756F0::ReadTheme(const char* section, const char* key,
                              int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        return DAT_00A83D10.FindName(buffer);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x475950
//
// The matching writer: the player turns the index back into a name.
bool CCINI_004756F0::WriteTheme(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_00A83D10.GetName(index));
}

// FUNCTION: GAMEMD 0x475980
//
// The 0x475870 reader over the 0x48DB80 parser.
int CCINI_004756F0::FUN_00475980(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        return FUN_0048DB80(buffer);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x4759D0
//
// Write a map-edge index out as its name. The table is an array of
// pointers, so this is a scaled load and a tail call with the receiver
// never touched.
bool CCINI_004756F0::WriteEdge(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_007E1B60[index]);
}

// FUNCTION: GAMEMD 0x4759F0
//
// The 0x475870 reader over the 0x48DE70 parser.
int CCINI_004756F0::FUN_004759F0(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        return FUN_0048DE70(buffer);
    }

    return defaultValue;
}
