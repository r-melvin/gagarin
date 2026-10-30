// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Distinct external COM interface projections selected by the two IIDs passed
// to CoCreateInstance at 0x7853E6 and 0x7854C4. Only observed caller slots are
// callable here. These are prefix lower bounds, not complete external tables.
#ifndef GG_MATCH_LAYOUT_COM_0048D080_H
#define GG_MATCH_LAYOUT_COM_0048D080_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00AC116C;
struct Obj_00AC1170;

// Stack self and explicit argument widths come from native callers. Only
// At_24's signed 32-bit result is consumed (0x791AF4/6). Other result types
// retain existing caller projections; their original external types are unknown.
struct Vtbl_00AC116C
{
    char unknown_00[0x0C];
    void (__stdcall* At_0C)(Obj_00AC116C* self); // 0x48D19E, result ignored
    char unknown_10[0x14];
    long (__stdcall* At_24)(Obj_00AC116C* self);
    char unknown_28[4];
    long (__stdcall* At_2C)(Obj_00AC116C* self, const char* text);
    char unknown_30[8];
    long (__stdcall* At_38)(Obj_00AC116C* self, void* message, const char* text);
    long (__stdcall* At_3C)(Obj_00AC116C* self, const char* text);
    char unknown_40[0x14];
    long (__stdcall* At_54)(Obj_00AC116C* self, void* record);
    char unknown_58[0x10];
    long (__stdcall* At_68)(Obj_00AC116C* self, int a, int b);
    char unknown_6C[0x10];
    long (__stdcall* At_7C)(Obj_00AC116C* self, int value);
    char unknown_80[0x0C];
    long (__stdcall* At_8C)(Obj_00AC116C* self, unsigned long value);
    // 0x789500: slot lookup (slot, text out, second out), slot store (slot, text, value, flag), slot text store.
    long (__stdcall* At_90)(Obj_00AC116C* self, int slot, const char** text, int* value);
    long (__stdcall* At_94)(Obj_00AC116C* self, int slot, const char* text, int value, int flag);
    char unknown_98[0x30];
    long (__stdcall* At_C8)(Obj_00AC116C* self, int slot, const char* text);
    char unknown_CC[0x1C];
    // 0x77E1D0 / 0x77E300: the list-box selection, as a text (no selection) or a node chain.
    long (__stdcall* At_E8)(Obj_00AC116C* self, const wchar_t* text);
    long (__stdcall* At_EC)(Obj_00AC116C* self, const void* chain, const wchar_t* text);
    long (__stdcall* At_F0)(Obj_00AC116C* self, const wchar_t* text);
    long (__stdcall* At_F4)(Obj_00AC116C* self, const void* chain, const wchar_t* text);
};
struct Obj_00AC116C
{
    Vtbl_00AC116C* Vtbl;
};

struct Vtbl_00AC1170
{
    char unknown_00[0x18];
    // 0x64B023: opaque buffer and output addresses, with literal timeout1000.
    void (__stdcall* At_18)(Obj_00AC1170* self, void* buffer, int value, void* output);
    void (__stdcall* At_1C)(Obj_00AC1170* self); // 0x48D1AD, result ignored
    long (__stdcall* At_20)(Obj_00AC1170* self, int value, int* output);
    char unknown_24[8];
    // Distinct from AC116C+2C: native pushes host, port and literal3.
    long (__stdcall* At_2C)(Obj_00AC1170* self, const char* host, int port, int value);
};
struct Obj_00AC1170
{
    Vtbl_00AC1170* Vtbl;
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(Obj_00AC116C*) == 4);
GG_STATIC_ASSERT(sizeof(Obj_00AC1170*) == 4);
GG_STATIC_ASSERT(sizeof(long) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned long) == 4);
GG_STATIC_ASSERT(offsetof(Obj_00AC116C, Vtbl) == 0);
GG_STATIC_ASSERT(offsetof(Obj_00AC1170, Vtbl) == 0);
GG_STATIC_ASSERT(sizeof(Obj_00AC116C) == 4);
GG_STATIC_ASSERT(sizeof(Obj_00AC1170) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_00AC116C*)0)->Vtbl) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_00AC1170*)0)->Vtbl) == 4);
// All sizeof checks pin source projections, not complete external objects or tables.
// Unconsumed result types, scalar signedness and text constness retain caller
// projections; they do not establish original external C++ declarations.
GG_STATIC_ASSERT(sizeof(Vtbl_00AC116C) == 0xF8);
GG_STATIC_ASSERT(sizeof(Vtbl_00AC1170) == 0x30);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_0C) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_24) == 0x24);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_24) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_2C) == 0x2C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_2C) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_38) == 0x38);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_38) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_3C) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_54) == 0x54);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_54) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_68) == 0x68);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_68) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_7C) == 0x7C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_7C) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_8C) == 0x8C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC116C*)0)->At_8C) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_EC) == 0xEC);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC116C, At_F4) == 0xF4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC1170, At_18) == 0x18);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC1170*)0)->At_18) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC1170, At_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC1170*)0)->At_1C) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC1170, At_20) == 0x20);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC1170*)0)->At_20) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_00AC1170, At_2C) == 0x2C);
GG_STATIC_ASSERT(sizeof(((Vtbl_00AC1170*)0)->At_2C) == 4);

// GLOBAL: GAMEMD 0xAC116C
extern Obj_00AC116C* DAT_00AC116C;
// GLOBAL: GAMEMD 0xAC1170
extern Obj_00AC1170* DAT_00AC1170;

#endif
