// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "vector_remove_item_family_methods.h"

// FUNCTION: GAMEMD 0x0063DFD0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_000063DFD0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
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
bool ItemVector_0063DFD0::FUN_000063E5D0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
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
bool ItemVector_0063DFD0::FUN_000063E900(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
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
bool ItemVector_0063DFD0::FUN_000063EBD0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
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
bool ItemVector_0063DFD0::FUN_00006CE2D0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}
