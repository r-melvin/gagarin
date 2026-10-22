// Provenance: own-binary-via-Ghidra
#include <string.h>
// Zero-run byte codec. The caller at 0x6C8BB7 passes ECX = a stack local and
// three stack arguments (source, destination, length); none of the three
// bodies reads ECX, so the owning object carries no state touched here.
// A zero byte is emitted as {0, run} with run capped at 0xFF (0x66155A);
// other bytes are copied through. Names are descriptive placeholders.

struct ZeroRunCodec_00661530
{
    int FUN_00661530(const unsigned char* source, unsigned char* dest, int length);
    int Encode(const unsigned char* source, unsigned char* dest, int length);
    int Decode(const unsigned char* source, unsigned char* dest, int length);
};

// FUNCTION: GAMEMD 0x661530
int ZeroRunCodec_00661530::FUN_00661530(const unsigned char* source, unsigned char* dest, int length)
{
    int written = 0;
    while (length > 0) {
        unsigned char value = *source;
        if (value == 0) {
            int run = 0;
            while (run <= length) {
                if (source[++run] != 0) break;
            }
            if (run >= 255) {
                run = 255;
            }
            if (dest != 0) {
                *dest++ = 0;
                *dest++ = (unsigned char)run;
            }
            written += 2;
            source += run;
            length -= run;
        } else {
            if (dest != 0) {
                *dest++ = value;
            }
            source++;
            written++;
            length--;
        }
    }
    return written;
}

// FUNCTION: GAMEMD 0x661590
int ZeroRunCodec_00661530::Encode(const unsigned char* source, unsigned char* dest, int length)
{
    if (dest != 0) {
        int size = FUN_00661530(source, dest + 2, length) + 2;
        *(unsigned short*)dest = (unsigned short)size;
        return size;
    }
    return FUN_00661530(source, 0, length) + 2;
}

// FUNCTION: GAMEMD 0x6615D0
int ZeroRunCodec_00661530::Decode(const unsigned char* source, unsigned char* dest, int length)
{
    unsigned char* out = dest;
    while (length > 0) {
        unsigned char value = *source++;
        length--;
        if (value == 0) {
            unsigned char count = *source++;
            length--;
            int run = count;
            if (run > 0) {
                memset(out, 0, run);
                out += run;
            }
        } else {
            *out++ = value;
        }
    }
    return out - dest;
}
