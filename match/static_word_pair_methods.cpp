// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Accessors for a function-local static record of two 16-bit words (both
// 0x7FFF) with an empty destructor: the first call builds the record through a
// temporary and registers the destructor stub with the CRT exit list. The
// stack argument (RET 4) is unused. Two copies, each owning its own static;
// owners are placeholders `Obj_<ADDR>`, and each address is verified separately.

struct WordPair_004238D0 {
    short unknown_00;
    short unknown_02;
    ~WordPair_004238D0() {}
};

inline WordPair_004238D0 MakeWordPair_004238D0(short a, short b)
{
    WordPair_004238D0 result;
    result.unknown_00 = a;
    result.unknown_02 = b;
    return result;
}

struct Obj_004238D0 {
    WordPair_004238D0* FUN_004238D0(int unused);
};

// FUNCTION: GAMEMD 0x004238D0
WordPair_004238D0* Obj_004238D0::FUN_004238D0(int unused)
{
    static WordPair_004238D0 value = MakeWordPair_004238D0(0x7FFF, 0x7FFF);
    return &value;
}

struct WordPair_00466660 {
    short unknown_00;
    short unknown_02;
    ~WordPair_00466660() {}
};

inline WordPair_00466660 MakeWordPair_00466660(short a, short b)
{
    WordPair_00466660 result;
    result.unknown_00 = a;
    result.unknown_02 = b;
    return result;
}

struct Obj_00466660 {
    WordPair_00466660* FUN_00466660(int unused);
};

// FUNCTION: GAMEMD 0x00466660
WordPair_00466660* Obj_00466660::FUN_00466660(int unused)
{
    static WordPair_00466660 value = MakeWordPair_00466660(0x7FFF, 0x7FFF);
    return &value;
}
