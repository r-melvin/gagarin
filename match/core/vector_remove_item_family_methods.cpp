// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "vector_remove_item_family_methods.h"

// FUNCTION: GAMEMD 0x0063DFD0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool __fastcall FUN_000063DFD0(ItemVector_0063DFD0* self, int, int item)
{
    int index = (self->*self->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < self->Count) {
            self->Count = self->Count - 1;
            for (int i = index; i < self->Count; i++) {
                self->Items[i] = self->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x0063E5D0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool __fastcall FUN_000063E5D0(ItemVector_0063DFD0* self, int, int item)
{
    int index = (self->*self->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < self->Count) {
            self->Count = self->Count - 1;
            for (int i = index; i < self->Count; i++) {
                self->Items[i] = self->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x0063E900
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool __fastcall FUN_000063E900(ItemVector_0063DFD0* self, int, int item)
{
    int index = (self->*self->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < self->Count) {
            self->Count = self->Count - 1;
            for (int i = index; i < self->Count; i++) {
                self->Items[i] = self->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x0063EBD0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool __fastcall FUN_000063EBD0(ItemVector_0063DFD0* self, int, int item)
{
    int index = (self->*self->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < self->Count) {
            self->Count = self->Count - 1;
            for (int i = index; i < self->Count; i++) {
                self->Items[i] = self->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x006CE2D0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool __fastcall FUN_00006CE2D0(ItemVector_0063DFD0* self, int, int item)
{
    int index = (self->*self->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < self->Count) {
            self->Count = self->Count - 1;
            for (int i = index; i < self->Count; i++) {
                self->Items[i] = self->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}
