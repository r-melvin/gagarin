// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small free functions read off retail gamemd.exe v1.001, round 16. Free functions use the
//   project's default __fastcall convention.
//   Address index: 0x6B9370 0x758E10 0x763610 0x775690.

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"

// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 -- the display's colour shift operands.
extern int DAT_008A0DD0;
extern int DAT_008A0DD4;
extern int DAT_008A0DD8;
extern int DAT_008A0DDC;
extern int DAT_008A0DE0;
extern int DAT_008A0DE4;

// FUNCTION: GAMEMD 0x6B9370
// Pack a colour into the display format; the middle channel is brightened by half, capped at 255.
unsigned int __fastcall FUN_006B9370(int first, int second, int third)
{
    int boosted = (second * 15) / 10;
    int middle = boosted > 255 ? 255 : boosted;
    boosted = DAT_008A0DD0;
    return ((third / 4) >> DAT_008A0DDC << DAT_008A0DD8) | ((first >> DAT_008A0DE4) << DAT_008A0DE0) |
           ((middle >> DAT_008A0DD4) << boosted);
}

// GLOBAL: GAMEMD 0xB72654 -- the shared name buffer.
extern char DAT_00B72654[];
// GLOBAL: GAMEMD 0x847F3C / 0x847F44 -- "%c%c" and "%c".
extern const char STR_00847F3C[];
extern const char STR_00847F44[];

// FUNCTION: GAMEMD 0x763610
// The letter name of an index: A-Z, then AA, AB and so on; -1 is empty.
char* __fastcall FUN_00763610(int index)
{
    if (index == -1) {
        DAT_00B72654[0] = 0;
        return DAT_00B72654;
    }
    if (index < 26) {
        wsprintfA(DAT_00B72654, STR_00847F44, index + 'A');
        return DAT_00B72654;
    }
    wsprintfA(DAT_00B72654, STR_00847F3C, index / 26 + '@', index % 26 + 'A');
    return DAT_00B72654;
}

// GLOBAL: GAMEMD 0xB73550 -- the game window.
extern HWND DAT_00B73550;

// FUNCTION: GAMEMD 0x775690
// The window's rectangle, relative to the client area's origin on screen.
BOOL __fastcall FUN_00775690(HWND window, RECT* rect)
{
    BOOL ok = GetWindowRect(window, rect);
    if (ok == 0) {
        return 0;
    }
    RECT client;
    GetClientRect(DAT_00B73550, &client);
    ClientToScreen(DAT_00B73550, (LPPOINT)&client);
    rect->left = rect->left - client.left;
    rect->right = rect->right - client.left;
    rect->top = rect->top - client.top;
    rect->bottom = rect->bottom - client.top;
    return ok;
}

// A palette, as far as its table of RGB byte triples.
struct PaletteView_r16
{
    unsigned char FUN_00758E10(float red, float green, float blue);

    char unknown_00[0x10];
    unsigned char* Entries;   // +0x10 256 RGB triples
};

// FUNCTION: GAMEMD 0x758E10
// The palette index whose colour is closest to the given one (smallest squared distance).
unsigned char PaletteView_r16::FUN_00758E10(float red, float green, float blue)
{
    float bestDistance = 100000.0f;
    int best = 0;
    int i = 0;
    unsigned char* entry = Entries;
    do {
        float dr = red - (float)entry[0];
        float dg = green - (float)entry[1];
        float db = blue - (float)entry[2];
        float distance = dr * dr + dg * dg + db * db;
        if (distance < bestDistance) {
            best = i;
            bestDistance = distance;
        }
        i++;
        entry += 3;
    } while (i < 256);
    return (unsigned char)best;
}

// An object that tracks a list of pointers and one current pointer (list at +0xC4, current at
// +0xE0), as far as the pointer-expiry notification.
struct PointerListView_r16
{
    void FUN_00722140(void* target, bool removed);

    char unknown_00[0xE0];
    void* Current;   // +0xE0
};
GG_STATIC_ASSERT(offsetof(PointerListView_r16, Current) == 0xE0);

// FUNCTION: GAMEMD 0x722140
// Forget every reference to an expired pointer.
void PointerListView_r16::FUN_00722140(void* target, bool removed)
{
    DynamicVectorClass<void*>* list = reinterpret_cast<DynamicVectorClass<void*>*>((char*)this + 0xC4);
    for (int i = list->Count - 1; i >= 0; i--) {
        if (list->Items[i] == target) {
            list->Delete(i);
        }
    }
    if (Current == target) {
        Current = 0;
    }
}

// A record with a counted list of pairs at +0xA4 (header ints at +0x98..+0xA0).
struct PairListView_r16
{
    int First;    // +0x98
    int Count;    // +0x9C
    int Third;    // +0xA0
    struct Pair {
        int A;
        int B;
    } Pairs[1];   // +0xA4
};

class PairListOwnerView_r16
{
public:
    // FUNCTION: GAMEMD 0x6E8000 (decl; reloc) -- refresh the other object from this one.
    void FUN_006E8000(PairListOwnerView_r16* other);
    PairListOwnerView_r16* FUN_006E80F0(PairListOwnerView_r16* target, PairListOwnerView_r16* source);

    char unknown_00[0x98];
    PairListView_r16 List;   // +0x98
};
GG_STATIC_ASSERT(offsetof(PairListOwnerView_r16, List) == 0x98);

// FUNCTION: GAMEMD 0x6E80F0
// Copy the source's pair list into this one, then have the target refresh from this.
PairListOwnerView_r16* PairListOwnerView_r16::FUN_006E80F0(PairListOwnerView_r16* target,
                                                           PairListOwnerView_r16* source)
{
    if (this != source) {
        List.First = source->List.First;
        List.Count = source->List.Count;
        List.Third = source->List.Third;
        for (int i = 0; i < List.Count; i++) {
            List.Pairs[i] = source->List.Pairs[i];
        }
    }
    target->FUN_006E8000(this);
    return target;
}

// An object holding a request handle and two remembered values.
struct RemembersView_r16
{
    bool FUN_00759EB0(int first, unsigned int second, unsigned int third, int fourth, int fifth);

    char unknown_00[0x200];
    int Handle;            // +0x200
    char unknown_204[0x520 - 0x204];
    unsigned int Second;   // +0x520
    unsigned int Third;    // +0x524
};
GG_STATIC_ASSERT(offsetof(RemembersView_r16, Handle) == 0x200);
GG_STATIC_ASSERT(offsetof(RemembersView_r16, Second) == 0x520);
GG_STATIC_ASSERT(offsetof(RemembersView_r16, Third) == 0x524);

// FUNCTION: GAMEMD 0x7C3270 (decl; reloc)
int __fastcall FUN_007C3270(int handle, int first, unsigned int second, unsigned int third, int fourth, int fifth);

// FUNCTION: GAMEMD 0x759EB0
// Remember the second and third values (or reuse the remembered ones for -1) and make the request.
bool RemembersView_r16::FUN_00759EB0(int first, unsigned int second, unsigned int third, int fourth, int fifth)
{
    if (second == 0xFFFFFFFF) {
        second = Second;
    } else {
        Second = second;
    }
    if (third == 0xFFFFFFFF) {
        third = Third;
    } else {
        Third = third;
    }
    if (fourth == -1) fourth = 0;
    if (fifth == -1) fifth = 0;
    bool done = FUN_007C3270(Handle, first, second, third, fourth, fifth) == -1;
    return done;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A0DD0
int DAT_008A0DD0;
// GLOBAL: GAMEMD 0x8A0DD4
int DAT_008A0DD4;
// GLOBAL: GAMEMD 0x8A0DD8
int DAT_008A0DD8;
// GLOBAL: GAMEMD 0x8A0DDC
int DAT_008A0DDC;
// GLOBAL: GAMEMD 0x8A0DE0
int DAT_008A0DE0;
// GLOBAL: GAMEMD 0x8A0DE4
int DAT_008A0DE4;
// GLOBAL: GAMEMD 0x847F3C
extern const char STR_00847F3C[] = "%c%c";
// GLOBAL: GAMEMD 0x847F44
extern const char STR_00847F44[] = "%c";
// END defined globals
