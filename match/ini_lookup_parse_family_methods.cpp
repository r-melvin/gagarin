// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Five INI lookup-and-parse forwarders. Each reads one entry into a 0x80-byte
// stack buffer through the shared string reader, hands the text to its own
// parser and returns the parsed value, or returns the caller's fallback when
// the entry is absent. Ordered ascending by retail address.

#include "ini_lookup_parse_family_methods.h"
#include "rules_class_ini_support.h"
#include "types_shared.h"

// FUNCTION: GAMEMD 0x0067B500
GG_INI_LOOKUP_PARSE_BODY(0067B500)

// FUNCTION: GAMEMD 0x0067B8F0
// Read a comma-separated list of aircraft type names: the entry is read into a stack buffer and
// every name that resolves is appended to a fresh list; when the entry is absent the caller's
// list is returned. The list result comes back through a hidden pointer in ECX, so the reader
// arrives in EDX.
TypeList<const AircraftTypeClass*> __fastcall FUN_0067B8F0(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const AircraftTypeClass*>& defaultValue)
{
    char buffer[0x80];
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80)) {
        TypeList<const AircraftTypeClass*> list(0, 0);
        for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
            const AircraftTypeClass* type = TypesFindAircraftType(token);
            if (type)
                list.AddItem(type);
        }
        return list;
    }
    return defaultValue;
}

// FUNCTION: GAMEMD 0x0067BAC0
GG_INI_LOOKUP_PARSE_BODY(0067BAC0)

// FUNCTION: GAMEMD 0x0067BCE0
GG_INI_LOOKUP_PARSE_BODY(0067BCE0)

// FUNCTION: GAMEMD 0x0067BD30
GG_INI_LOOKUP_PARSE_BODY(0067BD30)

// FUNCTION: GAMEMD 0x0067BD80
GG_INI_LOOKUP_PARSE_BODY(0067BD80)
