// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x510D10, 0x510E10
//   (partial), 0x510ED0, 0x510F60 and 0x510FB0.

#include "house_class_lookup_methods.h"

extern "C" char* __cdecl strcpy(char* dst, const char* src);
extern "C" int __cdecl strcmp(const char* a, const char* b);

// FUNCTION: GAMEMD 0x510D10
// Add the eight "<Player @ X>" names to a combo box (0x143 = CB_ADDSTRING),
// tagging each new item with its code (0x151 = CB_SETITEMDATA).
void FUN_00510D10(HWND__* combo)
{
    long index;

    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ A>");
    SendMessageA(combo, 0x151, index, 0x117B);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ B>");
    SendMessageA(combo, 0x151, index, 0x117C);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ C>");
    SendMessageA(combo, 0x151, index, 0x117D);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ D>");
    SendMessageA(combo, 0x151, index, 0x117E);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ E>");
    SendMessageA(combo, 0x151, index, 0x117F);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ F>");
    SendMessageA(combo, 0x151, index, 0x1180);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ G>");
    SendMessageA(combo, 0x151, index, 0x1181);
    index = SendMessageA(combo, 0x143, 0, (long)"<Player @ H>");
    SendMessageA(combo, 0x151, index, 0x1182);
}

// FUNCTION: GAMEMD 0x510E10
// Copy the "<Player @ X>" name of a pseudo-house code into `buffer`; any
// other code gives the empty string. A buffer of fewer than 16 bytes is
// cleared first, and one of no bytes at all is left alone.
// PARTIAL 85.7%: retail saves ESI/EDI before the size test (the early return
// shares the epilogue); cl shrink-wraps them after it. Tried an outer size
// guard, an if/else on `size > 0` and a block-scoped body: all 85.7%.
void FUN_00510E10(int code, char* buffer, int size)
{
    const char* name;

    if (size < 16) {
        if (size < 1) {
            return;
        }
        *buffer = '\0';
    }
    if (code == 0x117B) {
        name = "<Player @ A>";
    } else if (code == 0x117C) {
        name = "<Player @ B>";
    } else if (code == 0x117D) {
        name = "<Player @ C>";
    } else if (code == 0x117E) {
        name = "<Player @ D>";
    } else if (code == 0x117F) {
        name = "<Player @ E>";
    } else if (code == 0x1180) {
        name = "<Player @ F>";
    } else if (code == 0x1181) {
        name = "<Player @ G>";
    } else if (code == 0x1182) {
        name = "<Player @ H>";
    } else {
        name = STR_00889F64;
    }
    strcpy(buffer, name);
}

// FUNCTION: GAMEMD 0x510ED0
//
// Map a "<Player @ X>" house-type index (0x117B..0x1182 = A..H) to the house
// that spawned at that starting position.  Each letter arm asks the scenario's
// HouseIndices table for the HouseClass::Array index of that slot; the index
// is then bounds-checked against the array before being dereferenced.  Any
// other type index yields null.
//
// The eight arms are a plain if-chain in retail, each arm pushing its slot
// constant and falling into one cross-jumped copy of the lookup call.
HouseClass* HouseClass::FindByPlayerAt(int at)
{
    int idx;

    if (at == 0x117B) {
        idx = ScenarioInstance->GetHouseIndex(0);
    } else if (at == 0x117C) {
        idx = ScenarioInstance->GetHouseIndex(1);
    } else if (at == 0x117D) {
        idx = ScenarioInstance->GetHouseIndex(2);
    } else if (at == 0x117E) {
        idx = ScenarioInstance->GetHouseIndex(3);
    } else if (at == 0x117F) {
        idx = ScenarioInstance->GetHouseIndex(4);
    } else if (at == 0x1180) {
        idx = ScenarioInstance->GetHouseIndex(5);
    } else if (at == 0x1181) {
        idx = ScenarioInstance->GetHouseIndex(6);
    } else if (at == 0x1182) {
        idx = ScenarioInstance->GetHouseIndex(7);
    } else {
        return 0;
    }

    if (idx >= 0 && idx < HouseArray.Count) {
        return HouseArray.Items[idx];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x510F60
bool FUN_00510F60(int code)
{
    if (code == 0x117B || code == 0x117C || code == 0x117D || code == 0x117E
        || code == 0x117F || code == 0x1180 || code == 0x1181 || code == 0x1182) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x510FB0
// The pseudo-house code a "<Player @ X>" name stands for, or -1.
int FUN_00510FB0(const char* name)
{
    if (strcmp(name, "<Player @ A>") == 0) {
        return 0x117B;
    }
    if (strcmp(name, "<Player @ B>") == 0) {
        return 0x117C;
    }
    if (strcmp(name, "<Player @ C>") == 0) {
        return 0x117D;
    }
    if (strcmp(name, "<Player @ D>") == 0) {
        return 0x117E;
    }
    if (strcmp(name, "<Player @ E>") == 0) {
        return 0x117F;
    }
    if (strcmp(name, "<Player @ F>") == 0) {
        return 0x1180;
    }
    if (strcmp(name, "<Player @ G>") == 0) {
        return 0x1181;
    }
    return strcmp(name, "<Player @ H>") == 0 ? 0x1182 : -1;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA80228
HouseArray_00510ED0 HouseArray;
// GLOBAL: GAMEMD 0xA8B230
Scenario_00510ED0* ScenarioInstance;
// END defined globals
