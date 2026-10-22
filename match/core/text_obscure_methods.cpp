// Provenance: own-binary-via-Ghidra
//   Scrambles a text string into a 32-bit check value (CRC of a mixed copy).

#include <ctype.h>
#include <string.h>
#include "../platform/ccini_class_crc_methods.h"

// Bit masks applied per byte position (index & 7): set, then cleared.
// GLOBAL: GAMEMD 0x00832c0c
extern unsigned char DAT_00832c0c[8];
// GLOBAL: GAMEMD 0x00832c14
extern unsigned char DAT_00832c14[8];

// FUNCTION: GAMEMD 0x005f9e80
// Returns 0 for a null string. The text is upper-cased, padded with derived
// letters to a multiple of four (at least 16), whitened with a rolling CRC
// of its reverse, masked and mixed four bytes at a time, and the CRC of the
// result is returned.
int FUN_005f9e80(const char* text)
{
    char buf[128];
    int len;
    int i;

    if (text == 0) {
        return 0;
    }

    memset(buf, 0xA5, sizeof(buf));
    strncpy(buf, text, sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';
    len = strlen(buf);
    _strupr(buf);

    for (i = 0; i < len; i++) {
        if (!isgraph(buf[i])) {
            buf[i] = 'A' + i % 26;
        }
    }

    if (len < 16 || (len & 3) != 0) {
        int target = 16;
        if (((len + 3) & 0xFC) > target) {
            target = (len + 3) & 0xFC;
        }
        for (i = len; i < target; i++) {
            buf[i] = 'A' + ((buf[i - len] ^ 0x3F) + i) % 26;
        }
        buf[i] = '\0';
        len = i;
    }

    CRC_00476D80 crc;
    crc.CRC = 0;
    crc.Staging = 0;
    crc.Index = 0;
    crc.FUN_004A1DE0(buf, len);
    _strrev(buf);
    crc.CRC = 0;
    crc.Staging = 0;
    crc.Index = 0;
    int key = crc.FUN_004A1DE0(buf, len);
    _strrev(buf);

    for (i = 0; i < len; i++) {
        key ^= (unsigned char)buf[i];
        buf[i] ^= key;
        key = ((key & 0xFF) << 24) | (key >> 8);
    }

    for (i = 0; i < len; i++) {
        buf[i] = (DAT_00832c14[i & 7] | buf[i]) & ~DAT_00832c0c[i & 7];
    }

    for (i = 0; i < len; i += 4) {
        short a = buf[i];
        short b = buf[i + 1];
        short c = buf[i + 2];
        short d = buf[i + 3];
        short a2 = a * a;
        short b2 = b + b;
        short c2 = c + c;
        short d2 = d * d;
        short t1 = (c2 ^ a2) * a;
        short t2 = ((d2 ^ b2) + t1) * c;
        short t3 = t1 + t2;
        buf[i] = a2 ^ t2;
        buf[i + 1] = c2 ^ t2;
        buf[i + 2] = b2 ^ t3;
        buf[i + 3] = d2 ^ t3;
    }

    crc.CRC = 0;
    crc.Staging = 0;
    crc.Index = 0;
    return crc.FUN_004A1DE0(buf, len);
}
