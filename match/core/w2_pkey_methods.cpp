// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// PKey_00632740 (public-key record: modulus at +0, exponent at +0x100, bit length - 1 at
// +0x200) serialisers over the bignum byte codecs at 0x5C62B0 / 0x5C6370. Layout and
// evidence: pk_key_pipes.h.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT

#include "pk_key_pipes.h"

// FUNCTION: GAMEMD 0x00631FC0
int PKey_00632740::StoreModulus(unsigned char* out) const
{
    if (out == NULL) {
        return 0;
    }
    return FUN_005c62b0(Modulus.Digit, out, 64);
}

// FUNCTION: GAMEMD 0x00631FE0
int PKey_00632740::StoreExponent(unsigned char* out) const
{
    if (out == NULL) {
        return 0;
    }
    return FUN_005c62b0(Exponent.Digit, out, 64);
}

// FUNCTION: GAMEMD 0x00632000
void PKey_00632740::LoadModulus(const unsigned char* data)
{
    FUN_005c6370(Modulus.Digit, data, 64);
    unknown_200 = FUN_005c6960(Modulus.Digit, 64) - 1;
}

// FUNCTION: GAMEMD 0x00632030
void PKey_00632740::LoadExponent(const unsigned char* data)
{
    FUN_005c6370(Exponent.Digit, data, 64);
}
