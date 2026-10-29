// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small bodies
//   from the 0x54E000-0x6AC000 range; receivers are placeholder views of the members touched.
//
// Address index: 0x692270 0x692F20 0x598000 0x5DB6F0 0x6AC740 0x6A94F0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "trivial_tu130_methods.h"
#include "../network/transport/winsock_interface_class.h"

// GLOBAL: GAMEMD 0xB05629
extern unsigned char DAT_00B05629;

// FUNCTION: GAMEMD 0x692270
// Set the run-once bit in the guard byte.
void __cdecl FUN_00692270()
{
    if ((DAT_00B05629 & 1) == 0) {
        DAT_00B05629 |= 1;
    }
}

// FUNCTION: GAMEMD 0x692F20
// Empty callback.
void __cdecl FUN_00692F20()
{
}

// FUNCTION: GAMEMD 0x598000
// A uniform random value in [0, 1): the raw 32-bit draw scaled by 2^-32.
double __cdecl FUN_00598000()
{
    unsigned int draw = DAT_00ABE890.FUN_0065C780();
    return (double)draw * 2.3283064370807974e-10;
}

// FUNCTION: GAMEMD 0x5E8A20 (decl; reloc)
void __cdecl FUN_005E8A20();

// GLOBAL: GAMEMD 0xA8D610
extern short DAT_00A8D610;

// FUNCTION: GAMEMD 0x5DB6F0
// Run the shutdown helper, clear the status word and release the interface object.
void __cdecl FUN_005DB6F0()
{
    FUN_005E8A20();
    DAT_00A8D610 = 0;
    if (Interface_00887628 != 0) {
        delete Interface_00887628;
    }
    Interface_00887628 = 0;
}

// GLOBAL: GAMEMD 0xA8ED84
extern int DAT_00A8ED84;

// One 0x34-byte slot; a key at +0x00 and an expiry frame at +0x30.
struct Slot_006AC740
{
    int Key;                    // +0x0000
    char unknown_04[0x2C];
    int ExpiryFrame;            // +0x0030
};
GG_STATIC_ASSERT(sizeof(Slot_006AC740) == 0x34);

struct SlotTable_006AC740
{
    char unknown_00[0x58];
    Slot_006AC740 Slots[0x4B];  // +0x0058

    // FUNCTION: GAMEMD 0x6AC740
    void FUN_006AC740(int key, int delay);
};
GG_STATIC_ASSERT(offsetof(SlotTable_006AC740, Slots) == 0x58);

// FUNCTION: GAMEMD 0x6AC740
// Find the slot with the key and set it to expire `delay` frames from now.
void SlotTable_006AC740::FUN_006AC740(int key, int delay)
{
    for (int i = 0; i < 0x4B; i++) {
        if (Slots[i].Key == key) {
            Slots[i].ExpiryFrame = DAT_00A8ED84 + delay;
            return;
        }
    }
}

// Object queried for its length by the entries below.
struct Source_006A94F0
{
    // FUNCTION: GAMEMD 0x4CA120 (decl; reloc)
    int FUN_004CA120();
};

struct Entry_006A94F0
{
    Source_006A94F0* Source;    // +0x0000
    int Mode;                   // +0x0004
    int Minimum;                // +0x0008
    char unknown_0C[0x28];
};
GG_STATIC_ASSERT(sizeof(Entry_006A94F0) == 0x34);

struct EntryTable_006A94F0
{
    char unknown_00[0x64];
    Entry_006A94F0 Entries[1];  // +0x0064

    // FUNCTION: GAMEMD 0x6A94F0
    int FUN_006A94F0(int index);
};
GG_STATIC_ASSERT(offsetof(EntryTable_006A94F0, Entries) == 0x64);

// FUNCTION: GAMEMD 0x6A94F0
// Length of an entry's source, raised to the midpoint with its minimum when it runs in mode 1.
int EntryTable_006A94F0::FUN_006A94F0(int index)
{
    int length = 0;
    if (Entries[index].Source != 0) {
        length = Entries[index].Source->FUN_004CA120();
    }
    if (Entries[index].Mode == 1 && Entries[index].Minimum > length) {
        length = (length + Entries[index].Minimum) / 2;
    }
    return length;
}
