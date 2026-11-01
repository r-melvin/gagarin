// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
// 0x552640: __cdecl (source, destination) block decoder; returns the number
// of bytes written (`MOV EAX,ESI; SUB EAX,EBP` at 0x552816). Command bytes,
// read off the branches:
//   0x00-0x7F  copy (op>>4)+3 bytes from destination - (((op&0x0F)<<8) + next byte)
//   0x80       end of data
//   0x81-0xBF  copy op&0x3F literal bytes from the source
//   0xFE       fill: 16-bit count, then one value byte (aligned dword fill)
//   0xFF       copy a 16-bit count from destination base + 16-bit offset
//   0xC0-0xFD  copy (op&0x3F)+3 bytes from destination base + 16-bit offset
// The fill writes the head up to the next dword boundary and the tail with
// the memset expansion, and the middle as two dwords per step.
// Name descriptive.
#include <string.h>

// FUNCTION: GAMEMD 0x552640
int __cdecl LCW_Uncompress(const void* source, void* destination)
{
    const unsigned char* src;
    unsigned char* dst;
    unsigned char* copy;
    unsigned char* end;
    unsigned long* run;
    unsigned char op;
    unsigned char value;
    unsigned int count;
    unsigned long fill;
    int length;

    src = (const unsigned char*)source;
    dst = (unsigned char*)destination;

    for (;;) {
        op = *src++;
        if (!(op & 0x80)) {
            count = (op >> 4) + 3;
            copy = dst - (((op & 0x0F) << 8) + *src++);
            while (count--) {
                *dst++ = *copy++;
            }
        } else if (!(op & 0x40)) {
            if (op == 0x80) {
                return dst - (unsigned char*)destination;
            }
            count = op & 0x3F;
            while (count--) {
                *dst++ = *src++;
            }
        } else if (op == 0xFE) {
            count = (src[1] << 8) + src[0];
            value = src[2];
            fill = value;
            fill = (fill << 8) + value;
            fill = (fill << 8) + value;
            fill = (fill << 8) + value;
            src += 3;

            end = dst - ((unsigned long)dst & 3) + 4;
            count -= end - dst;
            if (dst < end) {
                length = end - dst;
                memset(dst, value, length);
                dst += length;
            }
            run = (unsigned long*)dst;
            dst += count & ~3;
            while (run < (unsigned long*)dst) {
                run[0] = fill;
                run[1] = fill;
                run += 2;
            }
            end = dst + (count & 3);
            if (dst < end) {
                length = end - dst;
                memset(dst, value, length);
                dst += length;
            }
        } else if (op == 0xFF) {
            count = (src[1] << 8) + src[0];
            copy = (unsigned char*)destination + (src[3] << 8) + src[2];
            src += 4;
            while (count--) {
                *dst++ = *copy++;
            }
        } else {
            count = (op & 0x3F) + 3;
            copy = (unsigned char*)destination + (src[1] << 8) + src[0];
            src += 2;
            while (count--) {
                *dst++ = *copy++;
            }
        }
    }
}
