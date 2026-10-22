// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every member displacement, bit constant and relayed address below read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI at the address in each annotation. None of these classes is bound by
//   YRpp, so all keep Ghidra placeholder names.
//
// The small guarded-predicate shapes the big sweeps left behind. Three families,
// grouped because each is a single test with one small payload behind it:
//
//   NULLGATE a null-guarded relay: return false on a null first argument,
//            otherwise call a helper on it and return true. `RET 0x10`, so the
//            free __stdcall form with four arguments.
//   FLAGGET  a flag-gated out-parameter copy: if the byte at +0x6C is clear
//            return false, otherwise publish one member through the pointer.
//   FLOATSEL a bool-selected float constant stored through `this`.
//
// Phrasing note: FLAGGET and FLOATSEL load their second operand from `[ESP+4]`,
// not from EDX, so both are __thiscall members and have to be written as real
// member functions. The free `__fastcall` spelling the sweep normally uses puts
// the argument in EDX and costs 60 points on FLAGGET and the whole function on
// FLOATSEL.
#ifndef GG_MATCH_CORE_LEFTOVER_PREDICATE_SWEEP_H
#define GG_MATCH_CORE_LEFTOVER_PREDICATE_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FLAGGET: a gate byte at +0x6C and the published member at OFF.
#define GG_FLAGGET_DECL(TAG, OFF)                                         \
struct FlagGet_##TAG                                                      \
{                                                                         \
    char _pad00[OFF];                                                     \
    int  Field;                    /* +OFF */                             \
    char _pad[0x6C - (OFF) - 4];                                          \
    bool Gate;                     /* +0x6C */                            \
    bool TryGet(int* out) const;                                          \
}

#define GG_FLAGGET_BODY(TAG)                                              \
bool FlagGet_##TAG::TryGet(int* out) const                                \
{                                                                         \
    if (!this->Gate) {                                                    \
        return false;                                                     \
    }                                                                     \
    *out = this->Field;                                                   \
    return true;                                                          \
}

// FLOATSEL: one float at +0x00, set to CONST when the flag is set and to zero
// otherwise.
#define GG_FLOATSEL_DECL(TAG)                                             \
struct FloatSel_##TAG                                                     \
{                                                                         \
    float Value;                   /* +0x00 */                            \
    void Select(bool flag);                                               \
}

#define GG_FLOATSEL_BODY(TAG, CONST)                                      \
void FloatSel_##TAG::Select(bool flag)                                    \
{                                                                         \
    if (flag) {                                                           \
        this->Value = CONST;                                              \
    } else {                                                              \
        this->Value = 0.0f;                                               \
    }                                                                     \
}

// NULLGATE: the three relayed helpers, each a __fastcall taking the guarded
// pointer in ECX. Addresses read off the CALL displacements.
void __fastcall FUN_0050DA10(void* self);   // FUNCTION: GAMEMD 0x50DA10
void __fastcall FUN_0050DA50(void* self);   // FUNCTION: GAMEMD 0x50DA50
void __fastcall FUN_0050DFF0(void* self);   // FUNCTION: GAMEMD 0x50DFF0

bool __stdcall FUN_006E4440(void* p, int b, int c, int d);   // FUNCTION: GAMEMD 0x6E4440
bool __stdcall FUN_006E44C0(void* p, int b, int c, int d);   // FUNCTION: GAMEMD 0x6E44C0
bool __stdcall FUN_006E4540(void* p, int b, int c, int d);   // FUNCTION: GAMEMD 0x6E4540

GG_FLAGGET_DECL(0049BC80, 0x44);
GG_FLAGGET_DECL(0049BCA0, 0x40);
GG_FLAGGET_DECL(0049BCC0, 0x38);
GG_STATIC_ASSERT(offsetof(FlagGet_0049BC80, Field) == 0x44 &&
                 offsetof(FlagGet_0049BC80, Gate) == 0x6C &&
                 offsetof(FlagGet_0049BCA0, Field) == 0x40 &&
                 offsetof(FlagGet_0049BCA0, Gate) == 0x6C &&
                 offsetof(FlagGet_0049BCC0, Field) == 0x38 &&
                 offsetof(FlagGet_0049BCC0, Gate) == 0x6C);

GG_FLOATSEL_DECL(00750060);
GG_FLOATSEL_DECL(00750090);
GG_FLOATSEL_DECL(007500B0);
GG_STATIC_ASSERT(offsetof(FloatSel_00750060, Value) == 0x0 &&
                 sizeof(FloatSel_00750060) == 0x4);

#endif  // GG_MATCH_CORE_LEFTOVER_PREDICATE_SWEEP_H
