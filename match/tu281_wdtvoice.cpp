// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at each address below.
//   Cluster between WDTTerr.cpp and WOLPersonaInformation.cpp; the owning classes are
//   unknown, so the receivers are placeholder views (no canonical header exists for them).
//
//   Ordered ascending by retail address.

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "string_class.h"
#include "randomizer.h"
#include "vector_class_operations.h"
#include "vector_class_mutation.h"
#include "game_timing_methods.h"
#include "_layout/elapsed_timer.h"
#include "_layout/ini_class.h"
#include <new.h>

// Retail expands the capacity-0 constructors inline into the array initialiser of
// 0x770E10, so both are given inline bodies here (same bodies as vector_class_operations.h).
template<> inline VectorClass<unsigned>::VectorClass(int capacity, unsigned* pMem)
    : Items(0), Capacity(capacity), IsInitialized(true), IsAllocated(false)
{
    if (capacity != 0) {
        if (pMem != 0)
            Items = new((void*)pMem) unsigned[capacity];
        else {
            Items = new unsigned[capacity];
            IsAllocated = true;
        }
    }
}

template<> inline DynamicVectorClass<unsigned>::DynamicVectorClass(int capacity, unsigned* pMem)
    : VectorClass<unsigned>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}

#include "wdt_voice_classes.h"

// FUNCTION: GAMEMD 0x770550
void Obj_00770430::FUN_00770550(INIClass* ini, const Wstring* section)
{
    for (int i = 0; i < 6; ++i) {
        unknown_04[i].ReadCases(ini, section, unknown_00);
    }
    {
        Wstring tag("Startup");
        Wstring key = FUN_007B64E0(*FUN_007AF2A0(unknown_00), tag);
        Wstring list;
        {
            Wstring fallback(STR_00889F64);
            ini->FUN_00528C00(section, &key, &fallback, &list);
        }
        ParseIntList(&list, &unknown_37C[0]);
    }
    {
        Wstring tag("TerritorySelect");
        Wstring key = FUN_007B64E0(*FUN_007AF2A0(unknown_00), tag);
        Wstring list;
        {
            Wstring fallback(STR_00889F64);
            ini->FUN_00528C00(section, &key, &fallback, &list);
        }
        ParseIntList(&list, &unknown_37C[1]);
    }
}

// FUNCTION: GAMEMD 0x770850
void Obj_00770430::FUN_00770850(INIClass* ini, const Wstring* section, int index, const Wstring* key)
{
    Wstring name = FUN_007B64E0(*FUN_007AF2A0(unknown_00), *key);
    Wstring list;
    {
        Wstring fallback(STR_00889F64);
        ini->FUN_00528C00(section, &name, &fallback, &list);
    }
    ParseIntList(&list, &unknown_37C[index]);
}

// FUNCTION: GAMEMD 0x770970
bool Obj_00770430::FUN_00770970(int set, int kind, Wstring& out)
{
    return unknown_04[set].PickA(unknown_00, kind, out);
}

// FUNCTION: GAMEMD 0x770A50
bool Obj_00770430::FUN_00770A50(int set, int kind, Wstring& out)
{
    return unknown_04[set].PickB(unknown_00, kind, out);
}

// FUNCTION: GAMEMD 0x770B30
bool Obj_00770430::FUN_00770B30(int index, Wstring& out)
{
    return PickLine(unknown_00, &unknown_37C[index], out);
}

// FUNCTION: GAMEMD 0x770C10
bool __fastcall FUN_00770C10(int side, DynamicVectorClass<unsigned>* lines, Wstring& out)
{
    return PickLine(side, lines, out);
}

// FUNCTION: GAMEMD 0x770D70
void __fastcall FUN_00770D70(Wstring* text, DynamicVectorClass<unsigned>* lines)
{
    ParseIntList(text, lines);
}

// FUNCTION: GAMEMD 0x770E10
Obj_00770E10::Obj_00770E10()
{
    unknown_00 = STR_00889F64;
}

// FUNCTION: GAMEMD 0x770E70
void Obj_00770E10::FUN_00770E70(INIClass* ini, const Wstring* section, int side)
{
    ReadCases(ini, section, side);
}

// FUNCTION: GAMEMD 0x770F10
bool Obj_00770E10::FUN_00770F10(int side, int kind, Wstring& out)
{
    return PickA(side, kind, out);
}

// FUNCTION: GAMEMD 0x770FE0
bool Obj_00770E10::FUN_00770FE0(int side, int kind, Wstring& out)
{
    return PickLine(side, &unknown_04[kind * 2 + 1], out);
}

// FUNCTION: GAMEMD 0x7710B0
void Obj_00770E10::FUN_007710B0(INIClass* ini, const Wstring* section, int side, int kind, const Wstring* suffix)
{
    Wstring key = FUN_007B64E0(*FUN_007AF2A0(side), unknown_00) + *suffix;
    Wstring list;
    {
        Wstring fallback(STR_00889F64);
        ini->FUN_00528C00(section, &key, &fallback, &list);
    }
    ParseIntList(&list, &unknown_04[kind * 2]);
    key += "Emphasis";
    {
        Wstring fallback(STR_00889F64);
        ini->FUN_00528C00(section, &key, &fallback, &list);
    }
    ParseIntList(&list, &unknown_04[kind * 2 + 1]);
}

// FUNCTION: GAMEMD 0x7714B0
void Obj_00770430::FUN_007714B0(int index, bool counted, int ticks)
{
    DropExtra();
    Wstring text;
    int side = unknown_00;
    DynamicVectorClass<unsigned>& lines = unknown_37C[index];
    text.FUN_007B5340();
    int count = lines.Count;
    if (count > 0) {
        int pick = count == 1 ? 0 : DAT_00886B88.RandomRanged(0, count - 1);
        if (FUN_00770CE0(side, lines.Items[pick], &text)) {
            if (!FUN_007529E0()) {
                unknown_3AC = ScenarioElapsedTimer(ticks);
            }
            unknown_3C0.AddItem(text);
            if (counted) {
                unknown_3BC++;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x771620
void Obj_00770430::FUN_00771620()
{
    if (unknown_3AC.GetTimeLeft() != 0) {
        return;
    }
    if (unknown_3C0.Count > 0 && !FUN_007529E0()) {
        if (!unknown_3B8) {
            unknown_3C0.Delete(0);
            if (unknown_3BC > 0) {
                unknown_3BC--;
            }
        }
        if (unknown_3C0.Count > 0) {
            FUN_00752480(FUN_00753250(unknown_3C0.Items[0].FUN_007B5400()), -1, -1);
            unknown_3B8 = false;
        } else {
            unknown_3BC = 0;
            unknown_3B8 = true;
        }
    }
}

// FUNCTION: GAMEMD 0x771710
void Obj_00770430::FUN_00771710()
{
    DropExtra();
}

// FUNCTION: GAMEMD 0x7717A0
void Obj_00770430::FUN_007717A0()
{
    if (unknown_3C0.Count > 0) {
        FUN_007529A0(true);
        unknown_3C0.Clear();
    }
    unknown_3AC = ScenarioElapsedTimer();
}
