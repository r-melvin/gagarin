// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x7177C0  TechnoTypeClass::GetWeapon            (__thiscall)
//   FUNCTION: GAMEMD 0x7177E0  TechnoTypeClass::GetEliteWeapon       (__thiscall)
//   FUNCTION: GAMEMD 0x7178C0  TechnoTypeClass::GetParticleSysOffset (__thiscall)
//   FUNCTION: GAMEMD 0x6D2070  <projector>::CoordsToClient (referenced; reloc)
//   GLOBAL:   GAMEMD 0x887324  <projector instance pointer> (referenced; reloc)
//   LIBRARY:  GAMEMD 0x4CAC40  sqrt-helper (referenced; reloc)
//   LIBRARY:  GAMEMD 0x7C5F00  __ftol      (referenced; reloc)

#include "techno_type_getters.h"

// ---------------------------------------------------------------------------
// External helpers referenced only by GetParticleSysOffset (bodies matched in
// their own TUs; here they exist so cl emits the right CALL / global-load, all
// relocation-normalised by the differ).
//
// The world->client projector is a global object *pointer* at 0x00887324; its
// CoordsToClient(out, in) fills a 2-int client point and returns it.
// ---------------------------------------------------------------------------
struct ScreenProjector
{
    int* CoordsToClient(int* pOut, const int* pIn);  // GAMEMD 0x6D2070 __thiscall
};
extern ScreenProjector* TacticalProjector;           // GAMEMD 0x887324

extern double __cdecl sqrt_helper(double x);               // GAMEMD 0x4CAC40 (__cdecl)

// FUNCTION: GAMEMD 0x7177C0  (__thiscall)
// Pointer to the weaponIndex'th primary weapon slot: &this->Weapon[index].
// (Weapon stride is 0x1C, emitted as index*8 - index, then *4.)
WeaponStruct* TechnoTypeGetters::GetWeapon(int index)
{
    return &this->Weapon[index];
}

// FUNCTION: GAMEMD 0x7177E0  (__thiscall)
// Pointer to the weaponIndex'th elite weapon slot: &this->EliteWeapon[index].
WeaponStruct* TechnoTypeGetters::GetEliteWeapon(int index)
{
    return &this->EliteWeapon[index];
}

// A 2-int client point; the projector fills one and returns its address.
struct ClientPoint_007178C0 { int X; int Y; };

// FUNCTION: GAMEMD 0x7178C0  (__thiscall)
// The damage-smoke particle-system spawn offset. When DamSmkOffScrnRel is clear
// the stored DamageSmokeOffset is returned verbatim; when set, the X/Y are
// projected to client space (offset back by Z*10) and a Z is derived from the
// in-plane radius: Z = -/+ sqrt(2*(Z*10)^2) * 0.58, negated when Z >= 0.
//
// PARTIAL (12.5%, 9/72). Retail holds a literal zero in EBX from before the
// sqrt call (`XOR EDX,EDX; MOV EBX,EDX`), keeps the projected X in EBP and Y
// in EDI across both calls, and resolves the sign as `JGE; MOV EBX,EAX; JMP` /
// `SUB EBX,EAX` -- i.e. `Z = 0; if (z < 0) Z += t; else Z -= t;` with the
// zero never folded. cl 8804 folds every spelling of that to `NEG EAX` after
// `__ftol`, which also drops the EBP save and the zero. Everything up to the
// projector call and the whole x87 sequence (`FILD; FLD ST0; FMUL ST1; FADD
// ST0,ST0; FSTP; FSTP ST0`) is byte-identical. Variants tried (all 12.5%):
// ternary `(z < 0) ? t : -t`; `int iz = 0` with `+=`/`-=` and with
// `iz = iz + t`/`iz = iz - t`; the result built as a CoordStruct local with
// `Z = 0` then adjusted, stored whole and member-wise; a three-int
// constructor `Coord3(x, y, 0)`; `iz = z10 - z10`; the client point copied
// as a struct (this form) and read through the returned pointer with the
// members adjusted in place. Same class as "Zero not held in a register"
// (0x4566B0); the 8447-vs-8804 constant-register choice is the suspected
// cause. Retail's 0x14 frame is in(8) + a 12-byte slot the projector's
// out-point and the result share, which the struct-copy form reproduces.
// Lift pass 2 (2026-09-18): one more rejected - the result's Z written and
// adjusted through a taken `int* pz = &r.Z;` so the calls sit between the zero
// store and its reload (12.5%, identical stream). cl 8804 still constant-folds
// the zero and emits NEG. Confirmed as the banked 8447-vs-8804 "constant zero
// held in a callee-saved register" class; best measured form kept at 12.5%.
CoordStruct* TechnoTypeGetters::GetParticleSysOffset(CoordStruct* pBuffer) const
{
    if (this->DamSmkOffScrnRel)
    {
        ClientPoint_007178C0 in;
        in.X = this->DamageSmokeOffset.X;
        in.Y = this->DamageSmokeOffset.Y;

        ClientPoint_007178C0 out;
        ClientPoint_007178C0 client =
            *(ClientPoint_007178C0*)TacticalProjector->CoordsToClient(&out.X, &in.X);

        int z10 = this->DamageSmokeOffset.Z * 10;
        CoordStruct r;
        r.X = client.X - z10;
        r.Y = client.Y - z10;
        r.Z = 0;

        double d = (double)z10 * (double)z10;
        d = d + d;
        int t = (int)(sqrt_helper(d) * 0.58);
        if (this->DamageSmokeOffset.Z < 0)
            r.Z += t;
        else
            r.Z -= t;

        *pBuffer = r;
        return pBuffer;
    }

    *pBuffer = this->DamageSmokeOffset;
    return pBuffer;
}
