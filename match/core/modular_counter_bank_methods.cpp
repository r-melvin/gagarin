// Provenance: own-binary-via-Ghidra
// Bank of 16-bit modular counters. Layout read off 0x632C40: a byte flag at
// +0x00 (`MOV byte ptr [ESI],0x0`) and 16-bit counters from +0x02 indexed in
// step with the word table returned by 0x5C61D0. The counter count comes from
// 0x5C61E0, which returns the constant 0xDB7. Names are placeholders.
#include "../_rt/gg_static_assert.h"
#include <stddef.h>
#include "global_getter_family_methods.h"  // FUN_005C61E0 (count), FUN_005C61D0 (word table)
#include "pk_key_pipes.h"                  // BigInt_00632740

struct ModularCounterBank_00632C40
{
    bool           AnyZero;               // +0x00
    unsigned short Values[0xDB7];         // +0x02

    ModularCounterBank_00632C40* FillFrom(unsigned long* number);
    void Advance(unsigned short step);
};

GG_STATIC_ASSERT(offsetof(ModularCounterBank_00632C40, AnyZero) == 0x00);
GG_STATIC_ASSERT(offsetof(ModularCounterBank_00632C40, Values) == 0x02);

// FUNCTION: GAMEMD 0x5C71E0 (decl; reloc) -- the remainder of the number divided by a word.
unsigned short FUN_005c71e0(unsigned long* quotient, unsigned long* number, unsigned short divisor, int precision);
// GLOBAL: GAMEMD 0xA8F7F8 -- scratch number the remainder routine writes its quotient into.
extern BigInt_00632740 DAT_00A8F7F8;

// FUNCTION: GAMEMD 0x632BE0
// Set each counter to the number's remainder modulo the matching word of the table.
ModularCounterBank_00632C40* ModularCounterBank_00632C40::FillFrom(unsigned long* number)
{
    AnyZero = false;
    int count = FUN_005C61E0();
    const unsigned short* moduli = FUN_005C61D0();
    for (int i = 0; i < count; i++) {
        Values[i] = FUN_005c71e0(DAT_00A8F7F8.Digit, number, moduli[i], 64);
    }
    return this;
}

// FUNCTION: GAMEMD 0x632C40
void ModularCounterBank_00632C40::Advance(unsigned short step)
{
    int count = FUN_005C61E0();
    const unsigned short* moduli = FUN_005C61D0();
    AnyZero = false;
    for (int i = 0; i < count; i++) {
        Values[i] += step;
        while (Values[i] >= moduli[i]) {
            Values[i] -= moduli[i];
        }
        AnyZero = AnyZero || Values[i] == 0;
    }
}
