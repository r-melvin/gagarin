// Provenance: own-binary-via-Ghidra
// Bank of 16-bit modular counters. Layout read off 0x632C40: a byte flag at
// +0x00 (`MOV byte ptr [ESI],0x0`) and 16-bit counters from +0x02 indexed in
// step with the word table returned by 0x5C61D0. The counter count comes from
// 0x5C61E0, which returns the constant 0xDB7. Names are placeholders.
#include "../_rt/gg_static_assert.h"
#include <stddef.h>
#include "global_getter_family_methods.h"  // FUN_005C61E0 (count), FUN_005C61D0 (word table)

struct ModularCounterBank_00632C40
{
    bool           AnyZero;               // +0x00
    unsigned short Values[0xDB7];         // +0x02

    void Advance(unsigned short step);
};

GG_STATIC_ASSERT(offsetof(ModularCounterBank_00632C40, AnyZero) == 0x00);
GG_STATIC_ASSERT(offsetof(ModularCounterBank_00632C40, Values) == 0x02);

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
