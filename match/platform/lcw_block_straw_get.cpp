// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Derived from the retail gamemd.exe v1.001 disassembly at 0x552490.
//   The base slot implementation called non-virtually is 0x6C98E0.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x551E50 (decl; reloc) - block compress (src ECX, dst EDX, count).
int FUN_00551E50(const void* source, void* dest, int count);
// FUNCTION: GAMEMD 0x551C60 (decl; reloc) - block uncompress (src ECX, dst EDX, 0).
int FUN_00551C60(const void* source, void* dest, int length);

#include "compression_straws.h"

// FUNCTION: GAMEMD 0x552490
// Hands out staged bytes, refilling one block at a time from the chain:
// decompressing reads a header then the packed block and uncompresses it;
// compressing reads a raw block, compresses it and prefixes the header.
int LCWStraw::FUN_006C98E0(void* dest, int length)
{
    int total = 0;

    if (dest == NULL || length < 1) {
        return 0;
    }

    while (length > 0) {
        if (Counter > 0) {
            int len = (length < Counter) ? length : Counter;
            if (Control == 1) {
                memmove(dest, &Buffer[Header.UncompCount - Counter], len);
            } else {
                memmove(dest, &Buffer2[(Header.CompCount + sizeof(Header)) - Counter], len);
            }
            dest = (char*)dest + len;
            length -= len;
            Counter -= len;
            total += len;
        }
        if (length == 0) {
            break;
        }

        if (Control == 1) {
            if (Straw::FUN_006C98E0(&Header, sizeof(Header)) != sizeof(Header)) {
                break;
            }
            char* staging = &Buffer[(BlockSize + SafetyMargin) - Header.CompCount];
            if (Straw::FUN_006C98E0(staging, Header.CompCount) != Header.CompCount) {
                break;
            }
            FUN_00551C60(staging, Buffer, 0);
            Counter = Header.UncompCount;
        } else {
            Header.UncompCount = (unsigned short)Straw::FUN_006C98E0(Buffer, BlockSize);
            if (Header.UncompCount == 0) {
                break;
            }
            Header.CompCount = (unsigned short)FUN_00551E50(Buffer, &Buffer2[sizeof(Header)], Header.UncompCount);
            memmove(Buffer2, &Header, sizeof(Header));
            Counter = Header.CompCount + sizeof(Header);
        }
    }
    return total;
}
