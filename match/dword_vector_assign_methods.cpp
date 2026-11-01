// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Assignment of one growable dword array from another: the old storage is
// released through the virtual clear in slot 3, the capacity and elements are
// copied into fresh storage, and the count and growth step are copied last
// whether or not the arrays were distinct.

// A growable array of dwords, assigned from another (slot 3 releases the old storage).
struct Vec_0067A570 {
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02();
    virtual void Clear();
    int* unknown_04;
    int unknown_08;
    bool unknown_0C;
    bool unknown_0D;
    int unknown_10;
    int unknown_14;
    Vec_0067A570* FUN_0067A570(const Vec_0067A570& other);
};
// FUNCTION: GAMEMD 0x0067A570
Vec_0067A570* Vec_0067A570::FUN_0067A570(const Vec_0067A570& other)
{
    if (this != &other) {
        Clear();
        unknown_08 = other.unknown_08;
        if (unknown_08 != 0) {
            unknown_04 = new int[unknown_08];
            if (unknown_04 != 0) {
                unknown_0D = true;
                for (int i = 0; i < unknown_08; ++i)
                    unknown_04[i] = other.unknown_04[i];
            }
        } else {
            unknown_04 = 0;
            unknown_0D = false;
        }
    }
    unknown_10 = other.unknown_10;
    unknown_14 = other.unknown_14;
    return this;
}
