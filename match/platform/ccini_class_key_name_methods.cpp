// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x526CC0. Name from
//   YRpp (consult-only).

#include "ccini_class_key_name_methods.h"

// FUNCTION: GAMEMD 0x526CC0
//
// Name of the index-th key of a section. The section name is CRC'd, the
// section index probed (IsPresent inlined: count test, archive probe, node
// search) and fetched; when the index is inside the section's key count the
// entry list is walked, counting down, until the wanted entry is reached and
// its name returned. Every miss answers null.
// The walk is written as retail's own shape rather than as a `while` over the
// three clauses. Retail tests the head once (`MOV EAX,[EAX+0x18]; TEST EAX,EAX`
// at 0x526D56), then the loop head is the `Next` load at 0x526D5D, and the back
// edge is an unconditional `JMP 0x526D5D` reached through a second null test
// that follows the advance. So the null test is peeled at entry and repeated at
// the bottom; it is not the leading clause of a three-way conjunction. Writing
// it that way puts the found block ahead of the shared zero tail exactly as
// retail has it, and the whole function falls out byte for byte.
//
// Measured alternatives: the three clauses as one `while` condition 74.0%, the
// same conjunction inside `while (1)` behind a single negation 68.8%, a
// `for (;;)` with explicit breaks in retail's order 70.9%, and a `do`/`while
// (node != 0)` 70.9%. Retail advances before it decrements (`MOV EAX,ECX;
// DEC EDX`); the other order also reaches 100%, so only the loop's shape is
// load-bearing.
const char* INIClass::GetKeyName(const char* section, int index)
{
    if (section != 0) {
        CRC_00526CC0 engine;
        int crc = engine(section, strlen(section));

        Index_00526CC0* indexView = reinterpret_cast<Index_00526CC0*>(&SectionIndex);
        if (indexView->IsPresent(crc)) {
            INIClass::INISection* sec = (*indexView)[crc];
            if (sec != 0 && index < sec->EntryIndex.IndexCount) {
                INIClass::INIEntry* node = sec->FirstEntry();
                if (node != 0) {
                    while (1) {
                        if (!(node->NextNode != 0 && node->PrevNode != 0)) {
                            break;
                        }
                        if (index == 0) {
                            return node->Entry;
                        }
                        node = static_cast<INIClass::INIEntry*>(node->NextNode);
                        index--;
                        if (node == 0) {
                            break;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
