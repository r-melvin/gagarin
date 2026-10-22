// Provenance: own-binary-via-Ghidra
//   Derived from the retail gamemd.exe v1.001 disassembly at 0x552490.
//   The base slot implementation called non-virtually is 0x6C98E0.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x551E50 (decl; reloc) - block compress (src ECX, dst EDX, count).
int __fastcall FUN_00551E50(const void* source, void* dest, int count);
// FUNCTION: GAMEMD 0x551C60 (decl; reloc) - block uncompress (src ECX, dst EDX, 0).
int __fastcall FUN_00551C60(const void* source, void* dest, int length);

// Data straw base: vptr, chain-to, chain-from.
class DataStraw_00552490
{
public:
    virtual ~DataStraw_00552490();
    virtual void GetFrom(DataStraw_00552490* straw);
    // FUNCTION: GAMEMD 0x6C98E0 (decl) - pull data from the chained straw.
    virtual int Get(void* dest, int length);

    DataStraw_00552490* ChainTo;     // +0x0004
    DataStraw_00552490* ChainFrom;   // +0x0008
};

struct BlockHeader_00552490
{
    unsigned short CompCount;     // +0x0000
    unsigned short UncompCount;   // +0x0002
};
GG_STATIC_ASSERT(offsetof(BlockHeader_00552490, UncompCount) == 2);

// Straw that compresses (Control 0) or uncompresses (Control 1) in blocks.
class BlockCompressStraw_00552490 : public DataStraw_00552490
{
public:
    virtual int Get(void* dest, int length);

    int                  Control;        // +0x000C
    int                  Counter;        // +0x0010
    char*                Buffer;         // +0x0014
    char*                Buffer2;        // +0x0018
    int                  BlockSize;      // +0x001C
    int                  SafetyMargin;   // +0x0020
    BlockHeader_00552490 Header;         // +0x0024
};
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, Control) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, Counter) == 0x10);
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, Buffer) == 0x14);
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, Buffer2) == 0x18);
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, BlockSize) == 0x1C);
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, SafetyMargin) == 0x20);
GG_STATIC_ASSERT(offsetof(BlockCompressStraw_00552490, Header) == 0x24);

// FUNCTION: GAMEMD 0x552490
// Hands out staged bytes, refilling one block at a time from the chain:
// decompressing reads a header then the packed block and uncompresses it;
// compressing reads a raw block, compresses it and prefixes the header.
int BlockCompressStraw_00552490::Get(void* dest, int length)
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
            if (DataStraw_00552490::Get(&Header, sizeof(Header)) != sizeof(Header)) {
                break;
            }
            char* staging = &Buffer[(BlockSize + SafetyMargin) - Header.CompCount];
            if (DataStraw_00552490::Get(staging, Header.CompCount) != Header.CompCount) {
                break;
            }
            FUN_00551C60(staging, Buffer, 0);
            Counter = Header.UncompCount;
        } else {
            Header.UncompCount = (unsigned short)DataStraw_00552490::Get(Buffer, BlockSize);
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
