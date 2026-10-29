// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: list handling of PacketClass (fields chained through FieldClass::Next at +0x0C,
//   head at +0x04) disassembled at 0x625AB0, 0x625AE0 and 0x625D20 in the user's gamemd.exe.

#include <string.h>
#include "packet_class.h"

// FUNCTION: GAMEMD 0x625AB0
// Destroys every field in the packet's list.
PacketClass::~PacketClass()
{
    FieldClass* field = Head;
    while (field) {
        FieldClass* next = field->Next;
        delete field;
        field = next;
    }
}

// FUNCTION: GAMEMD 0x625AE0
// Pushes a field on the front of the list.
void PacketClass::AddField(FieldClass* field)
{
    field->Next = Head;
    Head = field;
}

// FUNCTION: GAMEMD 0x625D20
// Finds the first field whose four-character ID matches, or returns null.
FieldClass* PacketClass::FindField(const char* id)
{
    for (FieldClass* field = Head; field; field = field->Next) {
        if (strncmp(id, field->ID, 4) == 0) {
            return field;
        }
    }
    return 0;
}
