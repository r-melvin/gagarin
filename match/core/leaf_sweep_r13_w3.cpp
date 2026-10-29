// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   /Ob2: retail's __xc entry points straight at the initialiser body (no out-of-line _$E thunk).
//   Small functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. Receivers are placeholder views named after their address.
//   Address index: 0x6E2640, 0x71FF00,
//   0x72F330, 0x747600, 0x7500D0, 0x7500E0, 0x7515F0, 0x763700, 0x764FF0, 0x7B8C50.

#include "mathtbl_init_shapes.h"

// ---------------------------------------------------------------------------
// 0x71FF00: static initialiser of a four-word record whose constructor zeroes it.
// SYNTHETIC: GAMEMD 0x71FF00
// GLOBAL: GAMEMD 0xB0F1E8
MathTblZero4 DAT_00B0F1E8;

// ---------------------------------------------------------------------------
// 0x7515F0: whether the first word is non-zero.
struct Ptr_007515F0
{
    int Value;
    bool IsSet() const;   // 0x7515F0
};

// FUNCTION: GAMEMD 0x7515F0
bool Ptr_007515F0::IsSet() const
{
    int v = Value;
    return v != 0;
}

// ---------------------------------------------------------------------------
// 0x7B8C50: whether the second word is non-zero.
struct Ptr_007B8C50
{
    int unknown_0;
    int Value;
    bool IsSet() const;   // 0x7B8C50
};

// FUNCTION: GAMEMD 0x7B8C50
bool Ptr_007B8C50::IsSet() const
{
    bool r = Value != 0;
    return r;
}

// ---------------------------------------------------------------------------
// 0x764FF0: reads one entry of the pointer table at +0x34.
struct Table_00764FF0
{
    char unknown_0[0x34];
    void* Entries[1];
    void* Get(int index) const;   // 0x764FF0
};

// FUNCTION: GAMEMD 0x764FF0
void* Table_00764FF0::Get(int index) const
{
    return Entries[index];
}

// ---------------------------------------------------------------------------
// 0x747600: copies a pair of words into the destination and returns it (the middle argument is unused).
struct Pair_00747600
{
    int First;
    int Second;
};
// FUNCTION: GAMEMD 0x747600
Pair_00747600* __stdcall FUN_00747600(Pair_00747600* out, int unused, const Pair_00747600* src)
{
    out->First = src->First;
    out->Second = src->Second;
    return out;
}

// ---------------------------------------------------------------------------
// 0x763700: copies three words from another instance and returns the receiver.
struct Triple_00763700
{
    int A;
    int B;
    int C;
    Triple_00763700* Assign(const Triple_00763700* o);   // 0x763700
};

// FUNCTION: GAMEMD 0x763700
Triple_00763700* Triple_00763700::Assign(const Triple_00763700* o)
{
    *this = *o;
    return this;
}

// ---------------------------------------------------------------------------
// 0x7500D0 / 0x7500E0: a float scaled to and from an integer.
struct Scaled_007500D0
{
    float Value;
    int ToInt() const;   // 0x7500D0
    void FromInt(int v);   // 0x7500E0
};

// FUNCTION: GAMEMD 0x7500D0
int Scaled_007500D0::ToInt() const
{
    return (int)(Value * 100.0f);
}

// FUNCTION: GAMEMD 0x7500E0
void Scaled_007500D0::FromInt(int v)
{
    Value = (float)(v * 0.01);
}

// ---------------------------------------------------------------------------
// 0x72F330: runs three teardown steps and clears a flag.
// FUNCTION: GAMEMD 0x730100 (decl; reloc)
void __fastcall FUN_00730100();
// FUNCTION: GAMEMD 0x730400 (decl; reloc)
void __fastcall FUN_00730400();
// FUNCTION: GAMEMD 0x730530 (decl; reloc)
void __fastcall FUN_00730530();
// GLOBAL: GAMEMD 0xB0FC0C
extern char DAT_00B0FC0C;

// FUNCTION: GAMEMD 0x72F330
void FUN_0072F330()
{
    FUN_00730100();
    FUN_00730400();
    FUN_00730530();
    DAT_00B0FC0C = 0;
}

// ---------------------------------------------------------------------------
// 0x6E2640: when the first step reports ready, runs the second and succeeds.
// FUNCTION: GAMEMD 0x53A100 (decl; reloc)
bool __cdecl FUN_0053A100();
// FUNCTION: GAMEMD 0x53A090 (decl; reloc)
void __fastcall FUN_0053A090();

// FUNCTION: GAMEMD 0x6E2640
bool __stdcall FUN_006E2640(int a, int b, int c, int d)
{
    if (!FUN_0053A100()) {
        return false;
    }
    FUN_0053A090();
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0FC0C
char DAT_00B0FC0C;
// END defined globals
