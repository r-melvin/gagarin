// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPLayer.CPP. The name is the source-file string at 0x82e134
//   in retail gamemd.exe v1.001, passed by the assert at 0x5c60da inside this object's
//   code range (0x5c5e90-0x5c91ef). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//
//   Multi-word unsigned integer helpers (little-endian 32-bit word arrays).

#include <ctype.h>
#include <string.h>

// Library helpers. Out-of-line copies exist in retail; /Ob2 also inlines
// them into the callers below.
void WordsIncrement(unsigned int* a, int n)
{
    while (++*a == 0) {
        a++;
        if (--n == 0) {
            break;
        }
    }
}

void WordsDecrement(unsigned int* a, int n)
{
    while (--*a == 0xFFFFFFFF) {
        a++;
        if (--n == 0) {
            break;
        }
    }
}

void WordsInvert(unsigned int* a, int n)
{
    for (int i = 0; i < n; i++) {
        *a = ~*a;
        a++;
    }
}

void WordsNegate(unsigned int* a, int n)
{
    WordsInvert(a, n);
    WordsIncrement(a, n);
}

void WordsCopy(unsigned int* dst, const unsigned int* src, int n)
{
    memcpy(dst, src, n * 4);
}

void WordsSetSmall(unsigned int* r, unsigned int v, int n)
{
    memset(r, 0, n * 4);
    *r = v;
}

int WordsUsedCount(const unsigned int* a, int n)
{
    a += n - 1;
    while (*a == 0) {
        if (--n == 0) {
            break;
        }
        a--;
    }
    return n;
}

inline bool WordsAreZero(const unsigned int* a, int n)
{
    return *a == 0 && WordsUsedCount(a, n) <= 1;
}

inline bool WordsAreOne(const unsigned int* a, int n)
{
    return *a == 1 && WordsUsedCount(a, n) <= 1;
}

int WordsBitLength(const unsigned int* a, int n)
{
    int w = WordsUsedCount(a, n);
    if (w == 0) {
        return 0;
    }
    unsigned int mask = 0x80000000;
    int bits = w * 32;
    while (!(mask & a[w - 1])) {
        mask >>= 1;
        bits--;
    }
    return bits;
}

void WordsSetBit(unsigned int* a, unsigned int bit)
{
    a[bit >> 5] |= 1 << (bit & 31);
}

int WordsCompare(const unsigned int* a, const unsigned int* b, int n)
{
    a += n - 1;
    b += n - 1;
    do {
        if (*a < *b) {
            return -1;
        }
        if (*a > *b) {
            return 1;
        }
        a--;
        b--;
    } while (--n);
    return 0;
}

bool WordsAddWithCarry(unsigned int* dst, const unsigned int* x, const unsigned int* y, bool carry, int n)
{
    while (n--) {
        unsigned int sum = *x + *y;
        unsigned int res = sum + carry;
        carry = sum < *x || (carry && res == 0);
        *dst = res;
        y++;
        x++;
        dst++;
    }
    return carry;
}

bool WordsAddSmall(unsigned int* dst, const unsigned int* x, unsigned int y, bool carry, int n)
{
    while (n--) {
        unsigned int sum = y + *x;
        unsigned int res = sum + carry;
        carry = sum < *x || (carry && res == 0);
        *dst = res;
        y = 0;
        x++;
        dst++;
    }
    return carry;
}

bool WordsSubWithBorrow(unsigned int* dst, const unsigned int* x, const unsigned int* y, bool borrow, int n)
{
    unsigned short* d = (unsigned short*)dst;
    const unsigned short* a = (const unsigned short*)x;
    const unsigned short* b = (const unsigned short*)y;
    n += n;
    while (n--) {
        unsigned int t = (unsigned int)*a - *b - borrow;
        *d = (unsigned short)t;
        borrow = (t >> 16) & 1;
        d++;
        a++;
        b++;
    }
    return borrow;
}

int WordsMulSmall(unsigned int* dst, const unsigned int* src, short m, int n)
{
    unsigned short* d = (unsigned short*)dst;
    const unsigned short* a = (const unsigned short*)src;
    unsigned int carry = 0;
    n += n;
    for (int i = 0; i < n; i++) {
        unsigned int t = *a * m + carry;
        a++;
        *d = (unsigned short)t;
        d++;
        carry = t >> 16;
    }
    return 0;
}

void HalfWordsMulAdd(unsigned short* dst, const unsigned short* src, unsigned short m, int n)
{
    unsigned int carry = 0;
    for (int i = 0; i < n; i++) {
        unsigned int t = *src * m + (*dst + carry);
        src++;
        *dst = (unsigned short)t;
        dst++;
        carry = t >> 16;
    }
    *dst += (unsigned short)carry;
}

// Modulus state set up by FUN_005c7ec0.
// GLOBAL: GAMEMD 0x00abf59c
extern int DAT_00abf59c;
// GLOBAL: GAMEMD 0x00abf5a0
extern unsigned short DAT_00abf5a0;
// GLOBAL: GAMEMD 0x00abf5a4
extern unsigned int DAT_00abf5a4[4];
// GLOBAL: GAMEMD 0x00abf5b4
extern unsigned int DAT_00abf5b4[64];
// GLOBAL: GAMEMD 0x00abf6b4
extern unsigned short DAT_00abf6b4;
// GLOBAL: GAMEMD 0x00abf6b8
extern int DAT_00abf6b8;
// GLOBAL: GAMEMD 0x00abf6bc
extern unsigned int DAT_00abf6bc[130];
// GLOBAL: GAMEMD 0x00abf8c4
extern int DAT_00abf8c4;
// GLOBAL: GAMEMD 0x00abf8c8
extern unsigned int DAT_00abf8c8[4];

// Ascending table of the 3511 odd primes below 2^15; also the Fermat bases.
// GLOBAL: GAMEMD 0x0082e174
extern unsigned short DAT_0082e174[3511];

// Byte source used by FUN_005c8e40; only slot 2 (fill buffer) is called here.
class ByteSource_005C8980 {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Fill(void* buffer, int length);
};

// Remainder of a (n words) by a 16-bit divisor; quotient into q. Defined
// elsewhere; declared for the call below.
unsigned short FUN_005c71e0(unsigned int* q, unsigned int* a, unsigned short d, int n);

inline const unsigned short* FindTablePrime(unsigned short key)
{
    const unsigned short* base = DAT_0082e174;
    const unsigned short* found = 0;
    int count = 3511;
    while (count > 0) {
        int mid = count / 2;
        const unsigned short* e = &base[mid];
        if (*e > key) {
            count = mid;
        } else if (*e == key) {
            found = e;
            break;
        } else {
            base = e + 1;
            count -= mid + 1;
        }
    }
    return found;
}


//   block of MPLayer.CPP (its __FILE__ string 0x82E134).

//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.

//   block of MPLayer.CPP (its __FILE__ string 0x82E134 is the one passed to
//   the string-table loads below).

#include "../core/global_getter_family_methods.h"

#include "mp_game_mode_leaf_classes.h"

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
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

struct Team_005095D0
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[4];
    void* unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Team_005095D0, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

struct Obj_005095D0
{
    int FUN_005095D0(int kind);
};


struct Obj_0050DA10
{
    char Pad_00[0x5490];
    Cell_0050DEF0 unknown_5490;
    Cell_0050DEF0 unknown_5494;
    char Pad_5498[0x54F0 - 0x5498];
    Cell_0050DEF0 unknown_54F0;
    Cell_0050DEF0 unknown_54F4;
    Cell_0050DEF0 unknown_54F8;
    int unknown_54FC;
    char Pad_5500[0x577C - 0x5500];
    int unknown_577C;

    void FUN_0050DA10();
    void FUN_0050DA50();
    int FUN_0050DA80() const;
    Cell_0050DEF0 FUN_0050DEF0() const;
    void FUN_0050DFF0();
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_5490) == 0x5490);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54FC) == 0x54FC);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_577C) == 0x577C);

struct Obj_0053ECB0
{
    unsigned char unknown_0[10];

    Obj_0053ECB0();
};

struct Triple_0053EDA0
{
    short unknown_0;
    short unknown_2;
    short unknown_4;
};
GG_STATIC_ASSERT(sizeof(Triple_0053EDA0) == 6);

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);

struct Obj_005402B0
{
    void FUN_005402B0(int value);
};

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);

struct Entry_005657A0
{
    char Pad_00[0x24];
    Cell_0050DEF0 unknown_24;
};

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);


struct Iface_005BF500
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3(int value) = 0;
};

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

struct Vector_005C6120
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;

    void** unknown_4;
    int Pad_08;
    int Pad_0C;
    int unknown_10;

    void FUN_005C6120();
};

struct Obj_005F9710
{
    char unknown_0;
    char unknown_1;
};

struct Quad_00645C30
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_00645C30(int a, int b, int c, int d);
};

struct Record_00656580
{
    char Bytes[0x18];
};

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);

struct Obj_00656580
{
    Record_00656580 unknown_0[1];

    Record_00656580* FUN_00656580(const Key_00656580* key);
};


struct Obj_0065AD30
{
    char Pad_00[0xE4];
    int* unknown_E4;

    int FUN_0065AD30(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD30, unknown_E4) == 0xE4);

struct Pair_0065C890
{
    int unknown_0;
    int unknown_4;

    Pair_0065C890(int a, int b);
};

struct Obj_0068BCB0
{
    char Pad_00[0x214];
    int unknown_214;
};
GG_STATIC_ASSERT(offsetof(Obj_0068BCB0, unknown_214) == 0x214);


struct Obj_0068C030
{
    char Pad_00[0x1180];
    int unknown_1180[16];

    int FUN_0068C030(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0068C030, unknown_1180) == 0x1180);


struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);


struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);


struct Obj_0069BBE0
{
    char Pad_00[0x30D8];
    char unknown_30D8;
};
GG_STATIC_ASSERT(offsetof(Obj_0069BBE0, unknown_30D8) == 0x30D8);


struct Type_006A46D0
{
    char Pad_00[0x24];
    char unknown_24[1];
};

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include <stddef.h>
#include "../_layout/dialog_005d3490.h"

// STRING: GAMEMD 0x825FB0 -- "TXT_OK".
extern const char STR_00825FB0[];
// STRING: GAMEMD 0x825FD0 -- "TXT_CANCEL".
extern const char STR_00825FD0[];
// STRING: GAMEMD 0x82E134 -- this module's __FILE__ ("D:\\ra2mdpost\\MPLayer.CPP").
extern const char STR_0082E134[];

// Declaration: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
wchar_t* StringTable_LoadString(const char* label, int* out,
                                const char* file, int line);

// FUNCTION: GAMEMD 0x5C60D0
// Ask an OK / Cancel question; true when the first button (OK) was chosen.
bool FUN_005C60D0(const wchar_t* message)
{
    Dialog_005D3490 dialog;
    return dialog.FUN_005D3490(message,
                               StringTable_LoadString(STR_00825FB0, 0, STR_0082E134, 0x6C),
                               StringTable_LoadString(STR_00825FD0, 0, STR_0082E134, 0x6C),
                               0, 0) == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005C6120
// Free every pointer held, then slot 3.
void Vector_005C6120::FUN_005C6120()
{
    for (int i = 0; i < unknown_10; i++) {
        operator delete(unknown_4[i]);
    }
    vf_3();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C6150
MultiplayerManBattle::MultiplayerManBattle(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C6190
MultiplayerManBattle::~MultiplayerManBattle()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005C61D0
const unsigned short* FUN_005C61D0()
{
    return (const unsigned short*)&DAT_0082E174;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005C61E0
int FUN_005C61E0()
{
    return (int)&DAT_00000DB7;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c6660
// Shifts the n-word value at p right by shift bits, in place.
void FUN_005c6660(unsigned int* p, int shift, int n)
{
    unsigned int carry = 0;
    if (shift == 0) {
        return;
    }
    if (shift == 32) {
        p += n;
        while (n--) {
            unsigned int t = *--p;
            *p = carry;
            carry = t;
        }
        return;
    }
    if (shift < 32) {
        unsigned int mask = (1 << shift) - 1;
        int inv = 32 - shift;
        p += n;
        while (n--) {
            p--;
            unsigned int t = *p & mask;
            *p = (*p >> shift) | (carry << inv);
            carry = t;
        }
        return;
    }
    int words = shift / 32;
    int bits = shift % 32;
    int i;
    for (i = words; i < n - 1; i++) {
        *p = (p[words + 1] << (32 - bits)) | (p[words] >> bits);
        p++;
    }
    if (words < n) {
        *p = p[words] >> bits;
        p++;
    }
    for (i = 0; i < (words < n ? words : n); i++) {
        *p++ = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c67a0
// Shifts the n-word value at p left by shift bits, in place.
void FUN_005c67a0(unsigned int* p, int shift, int n)
{
    if (shift == 0) {
        return;
    }
    if (shift == 32) {
        unsigned int carry = 0;
        while (n--) {
            unsigned int t = *p;
            *p++ = carry;
            carry = t;
        }
        return;
    }
    if (shift < 32) {
        int inv = 32 - shift;
        unsigned int mask = ~(0xFFFFFFFFu >> shift);
        unsigned int carry = 0;
        while (n--) {
            unsigned int t = *p & mask;
            *p = (*p << shift) | (carry >> inv);
            p++;
            carry = t;
        }
        return;
    }
    int words = shift / 32;
    int bits = shift % 32;
    unsigned int* q = p + n - 1;
    int i;
    for (i = words; i < n - 1; i++) {
        *q = (q[-words] << bits) | (q[-words - 1] >> (32 - bits));
        q--;
    }
    if (words < n) {
        *q = q[-words] << bits;
        q--;
    }
    for (i = 0; i < (words < n ? words : n); i++) {
        *q-- = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c6bc0
// r = a * b over n words (shift-and-add). Always returns 0.
int FUN_005c6bc0(unsigned int* r, unsigned int* a, unsigned int* b, int n)
{
    WordsSetSmall(r, 0, n);
    if (WordsAreZero(a, n)) {
        return 0;
    }
    if (WordsAreZero(b, n)) {
        return 0;
    }
    int bits = WordsBitLength(b, n);
    unsigned int mask;
    if (bits == 0) {
        mask = 0;
    } else {
        mask = 1 << ((bits - 1) % 32);
    }
    int words = (bits + 31) / 32;
    if (words == 0 || bits == 0) {
        return 0;
    }
    unsigned int* bp = &b[words - 1];
    for (int i = bits; i != 0; i--) {
        FUN_005c67a0(r, 1, n);
        if (*bp & mask) {
            WordsAddWithCarry(r, r, a, false, n);
        }
        mask >>= 1;
        if (mask == 0) {
            mask = 0x80000000;
            bp--;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c6fe0
// Signed r = a * b over n words: multiplies magnitudes and fixes the sign.
int FUN_005c6fe0(unsigned int* r, unsigned int* a, unsigned int* b, int n)
{
    unsigned int ta[64];
    unsigned int tb[64];
    if ((int)a[n - 1] < 0) {
        WordsCopy(ta, a, n);
        WordsNegate(ta, n);
        if ((int)b[n - 1] < 0) {
            WordsCopy(tb, b, n);
            WordsNegate(tb, n);
            FUN_005c6bc0(r, ta, tb, n);
            return 0;
        }
        FUN_005c6bc0(r, ta, b, n);
        WordsNegate(r, n);
        return 0;
    }
    if ((int)b[n - 1] < 0) {
        WordsCopy(tb, b, n);
        WordsNegate(tb, n);
        FUN_005c6bc0(r, a, tb, n);
        WordsNegate(r, n);
        return 0;
    }
    FUN_005c6bc0(r, a, b, n);
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c7310
// rem = a % d, quot = a / d over n words (shift-and-subtract).
// Returns -1 when d is zero, else 0.
int FUN_005c7310(unsigned int* rem, unsigned int* quot, unsigned int* a, unsigned int* d, int n)
{
    if (WordsAreZero(d, n)) {
        return -1;
    }
    WordsSetSmall(rem, 0, n);
    WordsSetSmall(quot, 0, n);
    int bits = WordsBitLength(a, n);
    int words = (bits + 31) / 32;
    if (words == 0) {
        return 0;
    }
    unsigned int* ap = &a[words - 1];
    unsigned int* qp = &quot[words - 1];
    unsigned int mask;
    if (bits == 0) {
        mask = 0;
    } else {
        mask = 1 << ((bits - 1) % 32);
    }
    for (int i = bits; i != 0; i--) {
        FUN_005c67a0(rem, 1, n);
        if (*ap & mask) {
            WordsIncrement(rem, n);
        }
        if (WordsCompare(rem, d, n) >= 0) {
            WordsSubWithBorrow(rem, rem, d, false, n);
            *qp |= mask;
        }
        mask >>= 1;
        if (mask == 0) {
            mask = 0x80000000;
            ap--;
            qp--;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c7740
// inv = a^-1 mod m over n words (extended Euclid with three rotating rows).
void FUN_005c7740(unsigned int* inv, unsigned int* a, unsigned int* m, int n)
{
    unsigned int g[3][64];
    unsigned int q[64];
    unsigned int v[3][64];
    WordsCopy(g[0], m, n);
    WordsCopy(g[1], a, n);
    WordsSetSmall(v[0], 0, n);
    WordsSetSmall(v[1], 1, n);
    int j = 0;
    int i = 1;
    while (!WordsAreZero(g[i % 3], n)) {
        FUN_005c7310(g[(j + 2) % 3], q, g[j % 3], g[i % 3], n);
        FUN_005c6bc0(inv, v[i % 3], q, n);
        WordsSubWithBorrow(v[(j + 2) % 3], v[j % 3], inv, false, n);
        i++;
        j++;
    }
    int k = (i - 1) % 3;
    if ((int)v[k][n - 1] < 0) {
        WordsAddWithCarry(v[k], v[k], m, false, n);
    }
    WordsCopy(inv, v[k], n);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c7990
// q = 2^(2*bits(d)-1) / d style reciprocal over n words (shift-and-subtract
// starting from the top bit of d). Returns -1 when d is zero, else 0.
int FUN_005c7990(unsigned int* q, unsigned int* d, int n)
{
    unsigned int r[64];
    if (WordsAreZero(d, n)) {
        return -1;
    }
    WordsSetSmall(r, 0, n);
    WordsSetSmall(q, 0, n);
    int bits = WordsBitLength(d, n);
    int t = bits + 1;
    unsigned int mask;
    if (t == 0) {
        mask = 0;
    } else {
        mask = 1 << ((t - 1) % 32);
    }
    WordsSetBit(r, bits - 1);
    unsigned int* qp = &q[(t + 31) / 32 - 1];
    while (bits--) {
        FUN_005c67a0(r, 1, n);
        if (WordsCompare(r, d, n) >= 0) {
            WordsSubWithBorrow(r, r, d, false, n);
            *qp |= mask;
        }
        mask >>= 1;
        if (mask == 0) {
            mask = 0x80000000;
            qp--;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c7ba0
// Parses text into r (n words). A trailing H/O/B selects base 16/8/2,
// otherwise base 10; a leading '-' negates; ',' separators are skipped.
void FUN_005c7ba0(const char* s, unsigned int* r, int n)
{
    WordsSetSmall(r, 0, n);
    if (s == 0) {
        return;
    }
    int len = strlen(s);
    if (len == 0) {
        return;
    }
    int base;
    switch (toupper(s[len - 1])) {
    case 'H':
        base = 16;
        break;
    case 'O':
        base = 8;
        break;
    case 'B':
        base = 2;
        break;
    case '.':
        base = 10;
        break;
    default:
        base = 10;
        break;
    }
    bool neg = *s == '-';
    if (neg) {
        s++;
    }
    unsigned int c;
    while ((c = (unsigned char)*s++) != 0) {
        if (c == ',') {
            continue;
        }
        if (!isxdigit((char)c)) {
            break;
        }
        if (isdigit((char)c)) {
            c -= '0';
        } else {
            c = (unsigned char)(toupper((char)c) - 'A') + 10;
        }
        if (c >= (unsigned short)base) {
            break;
        }
        WordsMulSmall(r, r, (short)base, n);
        WordsAddSmall(r, r, c, false, n);
    }
    if (neg) {
        WordsNegate(r, n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c7ec0
// Installs mod (n words) as the current modulus and precomputes a
// normalised two-word reciprocal of its top bits. Returns 0.
int FUN_005c7ec0(unsigned int* mod, int n)
{
    WordsCopy(DAT_00abf5b4, mod, n);
    DAT_00abf6b8 = WordsBitLength(DAT_00abf5b4, n);
    DAT_00abf59c = (DAT_00abf6b8 + 15) / 16;
    WordsCopy(DAT_00abf8c8, &DAT_00abf5b4[WordsUsedCount(DAT_00abf5b4, n) - 2], 2);
    DAT_00abf8c4 = WordsBitLength(DAT_00abf8c8, 2) - 32;
    FUN_005c6660(DAT_00abf8c8, DAT_00abf8c4, 2);
    FUN_005c7990(DAT_00abf5a4, DAT_00abf8c8, 2);
    FUN_005c6660(DAT_00abf5a4, 1, 2);
    DAT_00abf8c4 = (DAT_00abf8c4 + 15) % 16 + 1;
    WordsIncrement(DAT_00abf5a4, 2);
    if ((unsigned int)WordsBitLength(DAT_00abf5a4, 2) > 32) {
        FUN_005c6660(DAT_00abf5a4, 1, 2);
        DAT_00abf8c4--;
    }
    DAT_00abf5a0 = ((unsigned short*)DAT_00abf5a4)[0];
    DAT_00abf6b4 = ((unsigned short*)DAT_00abf5a4)[1];
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c80a0
// r = (a * b) mod the installed modulus, n words. Schoolbook 16-bit
// multiply into the scratch buffer, then quotient-estimate reduction using
// the precomputed reciprocal. Returns 0.
int FUN_005c80a0(unsigned int* r, unsigned int* a, unsigned int* b, int n)
{
    WordsSetSmall(DAT_00abf6bc, 0, n * 2);
    const unsigned short* bp = (const unsigned short*)b;
    for (int i = 0; i < n * 2; i++) {
        HalfWordsMulAdd((unsigned short*)DAT_00abf6bc + i, (const unsigned short*)a, bp[i], n * 2);
    }
    int m = n * 2 + 1;
    DAT_00abf6bc[m - 1] = 0;
    int halves = WordsUsedCount(DAT_00abf6bc, m) * 2;
    if (halves >= DAT_00abf59c) {
        WordsIncrement(DAT_00abf6bc, m);
        WordsNegate(DAT_00abf6bc, m);
        unsigned short* p = (unsigned short*)DAT_00abf6bc + halves + 1;
        unsigned short* d = p - DAT_00abf59c;
        for (int k = halves - DAT_00abf59c + 1; k != 0; k--) {
            p--;
            d--;
            unsigned int c0 = (unsigned short)~p[0];
            unsigned int c1 = (unsigned short)~p[-1];
            unsigned int c2 = (unsigned short)~p[-2];
            unsigned int lo = DAT_00abf5a0;
            unsigned int hi = DAT_00abf6b4;
            unsigned int q = ((((c2 + 1) * hi >> 1) + ((c1 * lo + 0x10000) >> 1) + 1) >> 16) + (c1 * hi >> 1);
            q = ((q + (c0 * lo >> 1) + 1) >> 14) + c0 * hi * 2;
            q >>= DAT_00abf8c4;
            if (q >= 0xFFFF) {
                q = 0xFFFF;
            } else if ((unsigned short)q == 0) {
                continue;
            }
            HalfWordsMulAdd(d, (const unsigned short*)DAT_00abf5b4, (unsigned short)q, n * 2);
            if (!(*p & 0x8000)) {
                if (WordsSubWithBorrow((unsigned int*)d, (unsigned int*)d, DAT_00abf5b4, false, n)) {
                    (*p)--;
                }
            }
        }
        WordsNegate(DAT_00abf6bc, n);
        WordsDecrement(DAT_00abf6bc, n);
    }
    WordsCopy(r, DAT_00abf6bc, n);
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c8500
// r = base^exp mod mod, n words (left-to-right square and multiply).
// Returns 0, or -1..-5 for 0^0, zero modulus, base >= mod, exp >= mod and a
// failed modulus setup. Clears the modulus state afterwards.
int FUN_005c8500(unsigned int* r, unsigned int* base, unsigned int* exp, unsigned int* mod, int n)
{
    unsigned int tmp[64];
    WordsSetSmall(r, 1, n);
    if (WordsAreZero(exp, n)) {
        if (WordsAreZero(base, n)) {
            return -1;
        }
        return 0;
    }
    if (WordsAreZero(mod, n)) {
        return -2;
    }
    if (WordsCompare(base, mod, n) >= 0) {
        return -3;
    }
    if (WordsCompare(exp, mod, n) >= 0) {
        return -4;
    }
    int w = WordsUsedCount(mod, n);
    if (FUN_005c7ec0(mod, w) != 0) {
        return -5;
    }
    int bits = WordsBitLength(exp, w);
    int words = (bits + 31) / 32;
    if (words == 0) {
        return 0;
    }
    unsigned int mask;
    if (bits == 0) {
        mask = 0;
    } else {
        mask = 1 << ((bits - 1) % 32);
    }
    unsigned int* ep = &exp[words - 1];
    bits--;
    WordsCopy(r, base, w);
    mask >>= 1;
    if (mask == 0) {
        mask = 0x80000000;
        ep--;
    }
    while (bits--) {
        FUN_005c80a0(tmp, r, r, w);
        if (*ep & mask) {
            FUN_005c80a0(r, tmp, base, w);
        } else {
            WordsCopy(r, tmp, w);
        }
        mask >>= 1;
        if (mask == 0) {
            mask = 0x80000000;
            ep--;
        }
    }
    WordsSetSmall(DAT_00abf5b4, 0, w);
    DAT_00abf6b8 = 0;
    WordsSetSmall(DAT_00abf6bc, 0, w);
    DAT_00abf8c4 = 0;
    DAT_00abf5a0 = 0;
    WordsSetSmall(DAT_00abf5a4, 0, 4);
    WordsSetSmall(DAT_00abf8c8, 0, 4);
    DAT_00abf6b4 = 0;
    DAT_00abf59c = 0;
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c8980
// Fermat probable-prime test of p (n words) against the first count small
// prime bases.
bool FUN_005c8980(unsigned int* p, unsigned int count, int n)
{
    unsigned int pm1[64];
    unsigned int base[64];
    unsigned int res[64];
    WordsCopy(pm1, p, n);
    WordsDecrement(pm1, n);
    for (unsigned int i = 0; i < count; i++) {
        WordsSetSmall(base, DAT_0082e174[i], n);
        FUN_005c8500(res, base, pm1, p, n);
        if (!WordsAreOne(res, n)) {
            return false;
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c8e40
// r = random value in [lo, hi] (n words), drawn by rejection sampling from
// the byte source.
void FUN_005c8e40(unsigned int* r, ByteSource_005C8980* src, unsigned int* lo, unsigned int* hi, int n)
{
    unsigned int range[64];
    WordsSubWithBorrow(range, hi, lo, false, n);
    int bits = WordsBitLength(range, n);
    do {
        int b = bits;
        if (b >= n * 32) {
            b = n * 32;
        }
        int bytes = b / 8 + 1;
        WordsSetSmall(r, 0, n);
        src->Fill(r, bytes);
        ((unsigned char*)r)[bytes - 1] &= ~(0xFF << (b % 8));
    } while (WordsCompare(r, range, n) > 0);
    WordsAddWithCarry(r, r, lo, false, n);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005c9020
// Primality test of p (n words): table lookup for small values, trial
// division by the prime table, then two Fermat rounds.
bool FUN_005c9020(unsigned int* p, int n)
{
    unsigned int pm1[64];
    unsigned int tmp[64];
    unsigned int base[64];
    const unsigned short* q;
    if (!(*p & 1)) {
        return false;
    }
    if (WordsUsedCount(p, n) <= 1 && *p <= DAT_0082e174[3510]) {
        bool found = FindTablePrime((unsigned short)*p) != 0;
        if (found) {
            return true;
        }
    }
    for (q = DAT_0082e174; q < DAT_0082e174 + 3511; q++) {
        if (FUN_005c71e0(tmp, p, *q, n) == 0) {
            return false;
        }
    }
    WordsCopy(pm1, p, n);
    WordsDecrement(pm1, n);
    for (q = DAT_0082e174; q < DAT_0082e174 + 2; q++) {
        WordsSetSmall(base, *q, n);
        FUN_005c8500(tmp, base, pm1, p, n);
        if (!WordsAreOne(tmp, n)) {
            return false;
        }
    }
    return true;
}
