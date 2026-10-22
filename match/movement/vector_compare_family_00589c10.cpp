// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry-origin retail disassembly. | YRpp-cross-check
#include "vector_compare_family_00589c10.h"
// FUNCTION: GAMEMD 0x589C10
int SearchVector36_00589C10::Find(const SearchRecord36_00589C10& value) const
{
    for (int i = 0; i < Count; ++i) {
        if (Data[i].Key_18 == value.Key_18 && Data[i].Key_1C == value.Key_1C)
            return i;
    }
    return -1;
}
// FUNCTION: GAMEMD 0x589CA0
bool CompareVector4_00589CA0::EqualsA(const CompareVector4_00589CA0& other) const
{
    if (Count == other.Count) {
        for (int i = 0; i < Count; ++i) if (Data[i] != other.Data[i]) return false;
        return true;
    }
    return false;
}
// FUNCTION: GAMEMD 0x589EB0
bool CompareVector4_00589CA0::EqualsB(const CompareVector4_00589CA0& other) const
{
    if (Count == other.Count) {
        for (int i = 0; i < Count; ++i) if (Data[i] != other.Data[i]) return false;
        return true;
    }
    return false;
}
// FUNCTION: GAMEMD 0x58A110
bool CompareVector8_0058A110::Equals(const CompareVector8_0058A110& other) const
{
    if (Count == other.Count) {
        for (int i = 0; i < Count; ++i) if (Data[i].Key != other.Data[i].Key) return false;
        return true;
    }
    return false;
}
// FUNCTION: GAMEMD 0x58A260
bool CompareVector12_0058A260::Equals(const CompareVector12_0058A260& other) const
{
    if (Count == other.Count) {
        for (int i = 0; i < Count; ++i) if (Data[i].Key != other.Data[i].Key) return false;
        return true;
    }
    return false;
}
