// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x475A40, 0x475A60
//   and 0x475B70.

#include "ccini_class_base_category_methods.h"

// FUNCTION: GAMEMD 0x475A40
//
// Write an index out as its name, with no sentinel: the receiver passes
// straight through in ECX into the tail call.
bool CCINI_00475A40::FUN_00475A40(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_007E523C[index]);
}

// FUNCTION: GAMEMD 0x475A60
//
// Read a comma-separated list of base categories into a bit mask. The four
// named categories claim the top four bits and are tested unconditionally
// one after another rather than as an exclusive chain, so a token matching
// one is still looked up as a category afterwards.
//
// The accumulator is declared above the `if` and assigned on both arms, and
// that single-exit shape is what the retail bytes require: retail saves both
// callee-saved registers at the top of the body and pops them in each of the
// two return blocks. Written with a `return flags;` inside the arm and a
// `return defaultValue;` after it, cl 8804 instead shrink-wraps the pushes
// into the success arm and leaves the cold return with no pops at all,
// shifting every byte after offset 0x0E (181 of 263 bytes). Assigning the
// default to the same variable on the else arm keeps it live on both paths,
// which restores the entry save without hoisting its zeroing above the
// ReadString call.
int CCINI_00475A40::ReadCategoryList(const char* section, const char* key,
                                     int defaultValue)
{
    char buffer[128];
    int flags;

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        flags = 0;

            for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            if (FUN_007C8D20(token, STR_0081C030) == 0) {
                flags |= 0x80000000;
            }

            if (FUN_007C8D20(token, STR_0081C028) == 0) {
                flags |= 0x40000000;
            }

            if (FUN_007C8D20(token, STR_0081C01C) == 0) {
                flags |= 0x20000000;
            }

            if (FUN_007C8D20(token, STR_0081C014) == 0) {
                flags |= 0x10000000;
            }

            int bit = FUN_0045E7B0(token);

            if (bit != -1) {
                flags |= 1 << bit;
            }
        }

    } else {
        flags = defaultValue;
    }

    return flags;
}

// FUNCTION: GAMEMD 0x475B70
//
// The writer 0x475A60 pairs with: turn a base-category bit mask back into a
// comma-separated list of category names. Only the low bits are spelled --
// the walk is capped at 32 entries, one per bit of the mask -- so the four
// named flags the reader folds into the top bits are not written back here.
// Both string appends are the /O2 inlined strcat, and the registry's Items
// pointer is hoisted out of the loop because nothing in the body calls.
bool CCINI_00475A40::WriteCategoryList(const char* section, const char* key,
                                       int mask)
{
    char buffer[128] = "";

    int total = DAT_00A83C68.Count;
    int count = total > 32 ? 32 : total;

    for (int i = 0; i < count; ++i) {
        if (mask & (1 << i)) {
            if (buffer[0] != '\0') {
                strcat(buffer, STR_00817F70);
            }

            strcat(buffer, DAT_00A83C68.Items[i]->ID);
        }
    }

    return WriteString(section, key, buffer);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x81C014
extern const char STR_0081C014[] = "RADAR";
// GLOBAL: GAMEMD 0x81C01C
extern const char STR_0081C01C[] = "BARRACKS";
// GLOBAL: GAMEMD 0x81C028
extern const char STR_0081C028[] = "FACTORY";
// GLOBAL: GAMEMD 0x81C030
extern const char STR_0081C030[] = "POWER";
// END defined globals
