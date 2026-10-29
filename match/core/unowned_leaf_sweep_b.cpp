// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
#include "../_layout/cell_0050def0.h"

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

#include "../_layout/team_005095d0.h"

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

#include "../_layout/obj_005095d0.h"


#include "../_layout/obj_0050da10.h"


// FUNCTION: GAMEMD 0x0053EC90
// Live key state, or the recorded word for the key's low byte.
short FUN_0053EC90(int key)
{
    if (DAT_00AA0444 == 0) {
        return GetAsyncKeyState(key);
    }
    return DAT_00AA0168[key & 0xFF];
}

#include "../_layout/obj_0053ecb0.h"

// FUNCTION: GAMEMD 0x0053ECB0
Obj_0053ECB0::Obj_0053ECB0()
{
    unknown_0[0] = 0xFF;
    unknown_0[1] = 0xFF;
    unknown_0[2] = 0xFF;
    unknown_0[3] = 0xFF;
    unknown_0[4] = 0xFF;
    unknown_0[5] = 0xFF;
    unknown_0[6] = 0xFF;
    unknown_0[7] = 0xFF;
    unknown_0[8] = 0xFF;
    unknown_0[9] = 0xFF;
}

#include "../_layout/triple_0053eda0.h"

#include "../_layout/obj_0053eda0.h"

// FUNCTION: GAMEMD 0x0053EDA0
void Obj_0053EDA0::FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const
{
    *rest = unknown_4;
    *first = unknown_0;
}

#include "../_layout/obj_005402b0.h"

#include "../_layout/obj_00542fc0.h"

// FUNCTION: GAMEMD 0x00542FC0
void Obj_00542FC0::FUN_00542FC0(int value)
{
    if (unknown_48 != NULL) {
        unknown_48->FUN_005402B0(value);
    }
}

#include "../_layout/entry_005657a0.h"

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

#include "../_layout/obj_005657a0.h"

// FUNCTION: GAMEMD 0x005657A0
// The entry for `cell` in the 512-wide table at +0x13C; out of range or empty
// gives the shared entry at 0xABDC50 with the cell stored into its +0x24.
Entry_005657A0* Obj_005657A0::FUN_005657A0(const Cell_0050DEF0& cell) const
{
    int index = (cell.Y << 9) + cell.X;
    if (index >= 0 && index < 0x40000) {
        Entry_005657A0* entry = unknown_13C[index];
        if (entry != NULL) {
            return entry;
        }
    }
    DAT_00ABDC50.unknown_24 = cell;
    return &DAT_00ABDC50;
}

// FUNCTION: GAMEMD 0x0056BC50
int __stdcall FUN_0056BC50(const Cell_0050DEF0* cell)
{
    return cell->X / 4 + (cell->Y / 4) * 130 + 0x83;
}

#include "../_layout/iface_005bf500.h"

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

// FUNCTION: GAMEMD 0x005BF500
// Forward `value` to slot 3 of the first entry of the vector at 0xB45B58.
void FUN_005BF500(int value)
{
    if (DAT_00B45B68 > 0) {
        DAT_00B45B5C[0]->vf_3(value);
    }
}

#include "../_layout/vector_005c6120.h"


#include "../_layout/obj_005f9710.h"

// FUNCTION: GAMEMD 0x005F9710
void FUN_005F9710(Obj_005F9710* self)
{
    self->unknown_1 = 0x47;
}

// FUNCTION: GAMEMD 0x00623840
// Delete every string of the combo box `window`, last first.
int FUN_00623840(HWND window)
{
    int count = SendMessageA(window, CB_GETCOUNT, 0, 0);
    while (count--) {
        SendMessageA(window, CB_DELETESTRING, count, 0);
    }
    return 0;
}

#include "../_layout/quad_00645c30.h"


#include "../_layout/record_00656580.h"

#include "../_layout/key_00656580.h"

#include "../_layout/obj_00656580.h"


#include "../_layout/pair_0065c890.h"

// FUNCTION: GAMEMD 0x0065C890
Pair_0065C890::Pair_0065C890(int a, int b)
{
    unknown_0 = a;
    unknown_4 = b;
}

#include "../_layout/obj_0068bcb0.h"


#include "../_layout/obj_0068c030.h"


#include "../_layout/owner_006915d0.h"

#include "../_layout/cursor_006915d0.h"

// FUNCTION: GAMEMD 0x006915D0
bool FUN_006915D0(Cursor_006915D0* self)
{
    return self->unknown_2C < self->unknown_24->unknown_A0;
}

#include "../_layout/obj_00696f10.h"


#include "../_layout/obj_0069b540.h"




#include "../_layout/type_006a46d0.h"

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

// FUNCTION: GAMEMD 0x006A46D0
// Index of the entry of the vector at 0x8B4120 whose name at +0x24 is `name`,
// or -1.
int FUN_006A46D0(const char* name)
{
    for (int i = 0; i < DAT_008B4130; i++) {
        if (_stricmp(DAT_008B4124[i]->unknown_24, name) == 0) {
            return i;
        }
    }
    return -1;
}
