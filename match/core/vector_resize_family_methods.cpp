// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at each address below.
//
// VectorClass::Resize, 32 further instantiations, ordered ascending by retail
// address and written out longhand per the family rule. Every member's retail
// bytes are identical, so one body is repeated verbatim under each address.
//
// What the function does: give the vector a new capacity. A new size of zero
// routes to the clear virtual at slot +0x0C instead. Otherwise the buffer is
// either adopted from the caller or allocated (four bytes per element), the
// smaller of the old and new lengths is copied across, the old buffer is
// released only if this vector owned it, and the new pointer, length and
// ownership flag are stored. The re-entrancy flag at +0x0C is cleared for the
// duration of the allocation. ActiveCount is finally clamped to the new
// length. A failed allocation returns false without touching any of that.
//
// Two details visible in the bytes and easy to lose: the copy loop re-reads
// the source pointer from the object on every iteration (`MOV EDX,[ESI+4]`
// sits inside the loop), so the source indexes through the member rather than
// through a hoisted local; and the allocation is a raw `operator new` with no
// array cookie and no construction loop, so the element type is trivially
// constructible.
//
// MATCHED 100% (73/73 instructions) on all 32, byte-identical retail bodies.
//
// Two levers, both found in one pass after the shape had sat at 68.5%:
//
//   1. Block placement. The retail body is *two* functions -
//      DynamicVectorClass::Resize with VectorClass::Resize inlined into it:
//
//          if (VectorClass::Resize(newsize, array)) {
//              if (Length < ActiveCount) ActiveCount = Length;
//              return true;
//          }
//          return false;
//
//      Written that way the trailing `return false` is the outer wrapper's
//      own natural fallthrough block, and cl 8804 places it last, exactly
//      where retail has it ([stores] JMP -> [clear] -> [clamp + return true]
//      -> [return false], reached only by the far JZ). Written as one flat
//      function - every spelling tried: `else { return false; }` 67.1%, an
//      early `if (p == 0) return false;` 34.2%, `goto fail` with the label
//      after `return true` 34.2%, clamp+return-true duplicated into both arms
//      53.7%, an `ok` flag tested after the merge 69.9%, the outer test
//      inverted 11.0% - cl tail-duplicates the small block inline at its
//      branch and places it second. The earlier finding that a dummy second
//      predecessor fixes the placement at the cost of two instructions (72.0%)
//      was the right diagnosis; the free second predecessor is simply the
//      wrapper's fallthrough. The generalisable rule: when a small return
//      block will not sit last, look for a function boundary the retail source
//      had and the decomp has flattened away. See ResizeBase in
//      vector_resize_methods.h. 68.5% -> 93.2%.
//
//   2. The SETcc tail, which the block fix left as the only residual. Retail
//      emits `XOR EAX,EAX / MOV [ESI+4],EDI / TEST EBX,EBX / SETZ AL /
//      MOV [ESI+8],EBP / MOV [ESI+0xD],AL` - the zeroing hoisted above the
//      first store and the SETcc idiom split across the second. Twenty-two
//      spellings of `IsAllocated = (array == 0)` were measured across two
//      sessions (inline before/between/after the stores; hoisted into bool,
//      int, unsigned char and unsigned int locals; `!array`; `? 1 : 0`; a
//      zero-initialised local under an `if`; an `| 0` widening; an inline
//      bool-returning predicate; volatile-qualified stores in six orders) and
//      every one of them emits the idiom as an unbroken unit in ECX, 60-93%.
//      What splits it is the RA1 spelling of the assignment itself:
//
//          Vector = newptr; Length = newsize;
//          IsAllocated = (Vector != 0 && array == 0);
//
//      The short-circuit's first term - provably true here, since newptr was
//      just null-checked - is what makes cl materialise the result in EAX and
//      hoist the `XOR EAX,EAX` above the Vector store, leaving the two pointer
//      stores to fall into the gaps. Plain stores, retail source order, no
//      volatile needed. 93.2% -> 100%. Banked rule: a redundant leading
//      short-circuit term is a scheduling lever for a SETcc idiom, and the
//      original source's own spelling is worth trying verbatim before any
//      simplification of it.
//
//   The flag bisection recorded earlier (/O1, /Ox, /O2 /Os, /O2 /Ot, /O2 /Gs,
//   /O2 /Ob0, /O2 /Ob1, /Oi-, /Gf, /Za, /GB, /G5, /G6, /GR, /Ogityb1 /Gs, and
//   /Gy and /GX present and absent) moved neither delta and was not the answer;
//   the locked /O2 /DNDEBUG /Gy /GX is what matches.

#include "vector_resize_family_methods.h"

// FUNCTION: GAMEMD 0x478140
bool VectorResizeFamily::FUN_478140(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x49EA70
bool VectorResizeFamily::FUN_49EA70(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x49ED30
bool VectorResizeFamily::FUN_49ED30(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4A13C0
bool VectorResizeFamily::FUN_4A13C0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4CAA70
bool VectorResizeFamily::FUN_4CAA70(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4E04A0
bool VectorResizeFamily::FUN_4E04A0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4E95E0
bool VectorResizeFamily::FUN_4E95E0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4E9840
bool VectorResizeFamily::FUN_4E9840(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4EA1C0
bool VectorResizeFamily::FUN_4EA1C0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4EBD60
bool VectorResizeFamily::FUN_4EBD60(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4EDEA0
bool VectorResizeFamily::FUN_4EDEA0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4EE360
bool VectorResizeFamily::FUN_4EE360(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4F2A60
bool VectorResizeFamily::FUN_4F2A60(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x50EA90
bool VectorResizeFamily::FUN_50EA90(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x512E70
bool VectorResizeFamily::FUN_512E70(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x513240
bool VectorResizeFamily::FUN_513240(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x513610
bool VectorResizeFamily::FUN_513610(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5AC820
bool VectorResizeFamily::FUN_5AC820(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5AD010
bool VectorResizeFamily::FUN_5AD010(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5C0C50
bool VectorResizeFamily::FUN_5C0C50(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5C5510
bool VectorResizeFamily::FUN_5C5510(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5D0C60
bool VectorResizeFamily::FUN_5D0C60(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5D0EC0
bool VectorResizeFamily::FUN_5D0EC0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5D8730
bool VectorResizeFamily::FUN_5D8730(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x627F90
bool VectorResizeFamily::FUN_627F90(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x67ACD0
bool VectorResizeFamily::FUN_67ACD0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x67B050
bool VectorResizeFamily::FUN_67B050(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x67B3D0
bool VectorResizeFamily::FUN_67B3D0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x69C890
bool VectorResizeFamily::FUN_69C890(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x6B15F0
bool VectorResizeFamily::FUN_6B15F0(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x6B8400
bool VectorResizeFamily::FUN_6B8400(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}
