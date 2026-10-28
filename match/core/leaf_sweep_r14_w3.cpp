// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   Receivers that are not bound by RTTI keep a placeholder name derived from the
//   address.
//
// Round 14 small leaves between 0x6B0000 and 0x7C4000. Ordered ascending by retail
// address.
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84
extern int CurrentFrame;

// ---------------------------------------------------------------------------
// 0x6B8AF0: do two packed ids agree in the low 19 bits.
struct Packed_006B8AF0
{
    unsigned int Value;   // +0x00
    bool FUN_006B8AF0(const Packed_006B8AF0* other) const;
};

// FUNCTION: GAMEMD 0x6B8AF0
//
// PARTIAL: 91.7% -- retail tests the low byte with `TEST AL,0xFF`, VC6 folds
// the same mask test to `TEST AL,AL` (variants tried: unsigned/signed temp,
// byte cast, single && chain).
// True when the low byte and bits 8..18 of the two values are equal.
bool Packed_006B8AF0::FUN_006B8AF0(const Packed_006B8AF0* other) const
{
    int diff = other->Value ^ this->Value;
    if ((diff & 0xFF) != 0 || (diff & 0x7FF00) != 0) {
        return false;
    }
    return true;
}


// ---------------------------------------------------------------------------
// 0x6CFC80: release one sidebar command shape slot.
struct SidebarShapeFile;
// GLOBAL: GAMEMD 0xB0CBDC
extern bool CommandShapeOwned_00B0CBDC[];
// GLOBAL: GAMEMD 0xB0C148
extern SidebarShapeFile* CommandShapes_00B0C148[];

// FUNCTION: GAMEMD 0x6CFC80
//
// Free the shape in slot `i` when this slot owns it, then clear the slot.
void __fastcall FUN_006CFC80(int i)
{
    if (CommandShapeOwned_00B0CBDC[i]) {
        ::operator delete((void*)CommandShapes_00B0C148[i]);
        CommandShapeOwned_00B0CBDC[i] = false;
    }
    CommandShapes_00B0C148[i] = 0;
}

// ---------------------------------------------------------------------------
// 0x734640 / 0x734670 / 0x734E30: language table helpers.
struct LangEntry_00734640
{
    int         Id;      // +0x00
    const char* Name;    // +0x04
    int         Pad08;   // +0x08
    int         Pad0C;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(LangEntry_00734640) == 0x10);
// GLOBAL: GAMEMD 0x845678 -- entries, terminated by Id == 10.
extern LangEntry_00734640 DAT_00845678[];
// GLOBAL: GAMEMD 0x816210
extern char DAT_00816210[];

// FUNCTION: GAMEMD 0x734640
//
// The language table entry with the given id, or null.
LangEntry_00734640* __fastcall FUN_00734640(int id)
{
    LangEntry_00734640* p = DAT_00845678;
    while (p->Id != 10) {
        if (p->Id == id) {
            return p;
        }
        p++;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x734670
//
// The name of the language table entry with the given id, else the default
// text.
const char* __fastcall FUN_00734670(int id)
{
    LangEntry_00734640* p = DAT_00845678;
    while (p->Id != 10) {
        if (p->Id == id) {
            if (p != 0) {
                return p->Name;
            }
            break;
        }
        p++;
    }
    return DAT_00816210;
}

// FUNCTION: GAMEMD 0x734E30
//
// True when every wide character of the string fits in one byte.
int __fastcall FUN_00734E30(const unsigned short* s)
{
    unsigned short c = *s;
    while (c != 0) {
        s++;
        if (c > 0xFF) {
            return false;
        }
        c = *s;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x748360 / 0x748380: 16-bit translation table.
// GLOBAL: GAMEMD 0xB1D14C
extern unsigned short* DAT_00b1d14c;

// FUNCTION: GAMEMD 0x748360
//
// Release the translation table.
void FUN_00748360()
{
    if (DAT_00b1d14c != 0) {
        ::operator delete((void*)DAT_00b1d14c);
        DAT_00b1d14c = 0;
    }
}

// FUNCTION: GAMEMD 0x748380
//
// Translate `count` 16-bit values in place through the table.
void __fastcall FUN_00748380(unsigned short* p, int count)
{
    for (; count > 0; count--, p++) {
        *p = DAT_00b1d14c[*p];
    }
}

// ---------------------------------------------------------------------------
// 0x769490: accumulate a pair and bump a count.
struct Triple_00769490
{
    int A;       // +0x00
    int B;       // +0x04
    int Count;   // +0x08
    Triple_00769490& FUN_00769490(const Triple_00769490* o);
};
GG_STATIC_ASSERT(offsetof(Triple_00769490, Count) == 0x08);

// FUNCTION: GAMEMD 0x769490
//
// Add the other pair into this one and count the addition.
Triple_00769490& Triple_00769490::FUN_00769490(const Triple_00769490* o)
{
    A += o->A;
    B += o->B;
    Count++;
    return *this;
}

// ---------------------------------------------------------------------------
// 0x7B67C0 / 0x7B6800 / 0x7B6840 / 0x7B71B0: wide string wrapper.
struct WStr_007B67C0
{
    const wchar_t* Str;   // +0x00
    bool FUN_007B67C0(const WStr_007B67C0* o) const;
    bool FUN_007B6800(const wchar_t* s) const;
    bool FUN_007B6840(const WStr_007B67C0* o) const;
    int  FUN_007B71B0() const;
};

// FUNCTION: GAMEMD 0x7B67C0
//
// Equality with another wrapper; two empty strings are equal.
bool WStr_007B67C0::FUN_007B67C0(const WStr_007B67C0* o) const
{
    if (Str == 0 && o->Str == 0) {
        return true;
    }
    if (Str != 0 && o->Str != 0) {
        bool r = wcscmp(Str, o->Str) == 0;
        return r;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7B6800
//
// Inequality with a raw string; two empty strings are equal.
bool WStr_007B67C0::FUN_007B6800(const wchar_t* s) const
{
    if (Str == 0 && s == 0) {
        return false;
    }
    if (Str != 0 && s != 0) {
        bool r = wcscmp(Str, s) != 0;
        return r;
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B6840
//
// Inequality with another wrapper; two empty strings are equal.
bool WStr_007B67C0::FUN_007B6840(const WStr_007B67C0* o) const
{
    if (Str == 0 && o->Str == 0) {
        return false;
    }
    if (Str != 0 && o->Str != 0) {
        bool r = wcscmp(Str, o->Str) != 0;
        return r;
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B71B0
//
// Length of the string, zero when unset.
int WStr_007B67C0::FUN_007B71B0() const
{
    if (Str == 0) {
        return (int)Str;
    }
    return wcslen(Str);
}

// ---------------------------------------------------------------------------
// 0x7AEE90 / 0x7ACB90: indexed fetch from a growable list.
struct GrowRecord6C_007ACB90
{
    int Data[27];
};
GG_STATIC_ASSERT(sizeof(GrowRecord6C_007ACB90) == 0x6C);

struct GrowListRecords_007ACB90
{
    int                     Count;   // +0x00
    int                     Pad04;
    GrowRecord6C_007ACB90*  Items;   // +0x08
    bool FUN_007ACB90(GrowRecord6C_007ACB90* out, int index);
};
GG_STATIC_ASSERT(offsetof(GrowListRecords_007ACB90, Items) == 0x08);

struct GrowListInts_007AEE90
{
    int  Count;   // +0x00
    int  Pad04;
    int* Items;   // +0x08
    bool FUN_007AEE90(int* out, int index);
};
GG_STATIC_ASSERT(offsetof(GrowListInts_007AEE90, Items) == 0x08);

// FUNCTION: GAMEMD 0x7ACB90
//
// Copy the record at `index` into `out`; false when out of range.
bool GrowListRecords_007ACB90::FUN_007ACB90(GrowRecord6C_007ACB90* out, int index)
{
    if (index >= 0 && index < Count) {
        *out = Items[index];
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7AEE90
//
// Read the value at `index` into `out`; false when out of range.
bool GrowListInts_007AEE90::FUN_007AEE90(int* out, int index)
{
    if (index >= 0 && index < Count) {
        *out = Items[index];
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x7BD270 / 0x7BD290 / 0x7BD2B0: toggle a surface mode through its callback.
class Surface_007BD270
{
public:
    char  _pad000[0x58];
    void (__cdecl *Callback)(Surface_007BD270* self, int what, int a, int b);   // +0x58
    char  _pad05C[0x7BC - 0x5C];
    unsigned int Flags;   // +0x7BC

    void FUN_007BD270();
    void FUN_007BD290();
    void FUN_007BD2B0();
};
GG_STATIC_ASSERT(offsetof(Surface_007BD270, Callback) == 0x58);
GG_STATIC_ASSERT(offsetof(Surface_007BD270, Flags)    == 0x7BC);

// FUNCTION: GAMEMD 0x7BD270
//
// Ask for mode 4 and raise the 0x40 flag.
void Surface_007BD270::FUN_007BD270()
{
    Callback(this, 4, 0, 0);
    Flags |= 0x40;
}

// FUNCTION: GAMEMD 0x7BD290
//
// Ask for mode 6 and drop the 0x40 flag.
void Surface_007BD270::FUN_007BD290()
{
    Callback(this, 6, 0, 0);
    Flags &= ~0x40u;
}

// FUNCTION: GAMEMD 0x7BD2B0
//
// Ask for mode 7 and drop the 0x40 flag.
void Surface_007BD270::FUN_007BD2B0()
{
    Callback(this, 7, 0, 0);
    Flags &= ~0x40u;
}

// ---------------------------------------------------------------------------
// 0x773860 / 0x773880: web browser history navigation.
class WebBrowserIface_00773860
{
public:
    virtual long __stdcall QueryInterface();
    virtual long __stdcall AddRef();
    virtual long __stdcall Release();
    virtual long __stdcall GetTypeInfoCount();
    virtual long __stdcall GetTypeInfo();
    virtual long __stdcall GetIDsOfNames();
    virtual long __stdcall Invoke();
    virtual long __stdcall GoBack();      // slot 7
    virtual long __stdcall GoForward();   // slot 8
};

class WebBrowser_00773860
{
public:
    char                       _pad000[8];
    WebBrowserIface_00773860*  Browser;   // +0x08
    char                       _pad00C[0x40C - 0x0C];
    bool                       Flag40C;   // +0x40C

    void FUN_00773860();
    void FUN_00773880();
};
GG_STATIC_ASSERT(offsetof(WebBrowser_00773860, Browser) == 0x08);
GG_STATIC_ASSERT(offsetof(WebBrowser_00773860, Flag40C) == 0x40C);

// FUNCTION: GAMEMD 0x773860
//
// Step the embedded browser back one page and note it in the flag.
void WebBrowser_00773860::FUN_00773860()
{
    if (Browser != 0) {
        Browser->GoBack();
        Flag40C = true;
    }
}

// FUNCTION: GAMEMD 0x773880
//
// Step the embedded browser forward one page and clear the flag.
void WebBrowser_00773860::FUN_00773880()
{
    if (Browser != 0) {
        Browser->GoForward();
        Flag40C = false;
    }
}

// ---------------------------------------------------------------------------
// 0x7BE640 / 0x754BE0 / 0x755990 / 0x755C60 / 0x759760: block copies.
struct Blob88_007BE640
{
    int Data[34];
    void FUN_007BE640();
};
GG_STATIC_ASSERT(sizeof(Blob88_007BE640) == 0x88);
// GLOBAL: GAMEMD 0x84E738
extern Blob88_007BE640 DAT_0084E738;

// FUNCTION: GAMEMD 0x7BE640
//
// Reset this block from the default block at 0x84E738.
void Blob88_007BE640::FUN_007BE640()
{
    *this = DAT_0084E738;
}

struct Blob30_00754BE0
{
    int Data[12];
};
GG_STATIC_ASSERT(sizeof(Blob30_00754BE0) == 0x30);
// GLOBAL: GAMEMD 0xB44318
extern Blob30_00754BE0 DAT_00B44318;
// GLOBAL: GAMEMD 0xB43F10
extern Blob30_00754BE0 DAT_00B43F10[];
// GLOBAL: GAMEMD 0xB450B8
extern Blob30_00754BE0 DAT_00B450B8[];

// FUNCTION: GAMEMD 0x754BE0
//
// Copy the default block into `out`.
Blob30_00754BE0* __fastcall FUN_00754BE0(Blob30_00754BE0* out)
{
    *out = DAT_00B44318;
    return out;
}

// FUNCTION: GAMEMD 0x755990
//
// Copy entry `index` of the table at 0xB43F10 into `out`.
void __fastcall FUN_00755990(int index, Blob30_00754BE0* out)
{
    *out = DAT_00B43F10[index];
}

// FUNCTION: GAMEMD 0x755C60
//
// Copy entry `index` of the table at 0xB450B8 (indices from 4 up are folded
// down by 4) into `out`.
Blob30_00754BE0* __fastcall FUN_00755C60(Blob30_00754BE0* out, int index)
{
    if (index >= 4) {
        index -= 4;
    }
    *out = DAT_00B450B8[index];
    return out;
}

struct Blob300_00759760
{
    int Data[0xC0];
};
GG_STATIC_ASSERT(sizeof(Blob300_00759760) == 0x300);

class Movie_00759760
{
public:
    char             _pad000[0x204];
    Blob300_00759760 Block;     // +0x204
    char             _pad504[0x528 - 0x504];
    bool             Flag528;   // +0x528

    void FUN_00759760(const Blob300_00759760* src);
};
GG_STATIC_ASSERT(offsetof(Movie_00759760, Flag528) == 0x528);

// FUNCTION: GAMEMD 0x759760
//
// Take a copy of the block and flag it as set.
void Movie_00759760::FUN_00759760(const Blob300_00759760* src)
{
    Block = *src;
    Flag528 = true;
}

// ---------------------------------------------------------------------------
// 0x755CB0 / 0x756570: small record helpers.
struct Rec_00755CB0
{
    unsigned char Flag;   // +0x00
    int           F04;    // +0x04
    int           F08;    // +0x08
    int           F0C;    // +0x0C
    int           F10;    // +0x10
    int           F14;    // +0x14
    int           F18;    // +0x18
    Rec_00755CB0();
};
GG_STATIC_ASSERT(offsetof(Rec_00755CB0, F18) == 0x18);

// FUNCTION: GAMEMD 0x755CB0
//
// Zero the record.
Rec_00755CB0::Rec_00755CB0()
{
    Flag = 0;
    F04 = 0;
    F08 = 0;
    F0C = 0;
    F10 = 0;
    F14 = 0;
    F18 = 0;
}

struct Counts_00756570
{
    int Pad00;
    int A;    // +0x04
    int B;    // +0x08
    int C;    // +0x0C
    int FUN_00756570() const;
};
GG_STATIC_ASSERT(offsetof(Counts_00756570, C) == 0x0C);

// FUNCTION: GAMEMD 0x756570
//
// Byte size of the packed data these counts describe.
int Counts_00756570::FUN_00756570() const
{
    return A * 12 + B * 164 + C + 0x1C;
}
