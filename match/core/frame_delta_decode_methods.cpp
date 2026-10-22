// Provenance: own-binary-via-Ghidra
//
// Decodes one frame chunk. The chunk starts with a 16-bit type: type 0 is a
// raw copy whose size must equal the destination size; type 1 is a run/skip
// stream that must end in the 0x80 0x00 0x00 terminator. Stream codes:
//   n > 0        copy n literal bytes
//   0, n, v      fill n bytes with v
//   0x80 | n     skip n destination bytes (n != 0)
//   0x80, w16    w > 0: skip w; w == 0: end; else w -= 0x8000 and
//                w >= 0x4000 fills (w - 0x4000) bytes with the next byte,
//                otherwise copies w literal bytes.
// Called (stdcall) from 0x426D7D.

#include <string.h>

// FUNCTION: GAMEMD 0x4270D0
bool __stdcall FUN_004270d0(void const* source, int length, void* dest, int dest_length)
{
    if (length == 0)
    {
        return true;
    }
    char const* src = (char const*)source;
    int type = *(short const*)src;
    src += 2;
    length -= 2;
    char* dst = (char*)dest;
    if (length == 0)
    {
        return true;
    }
    bool ok = true;
    switch (type)
    {
        case 0:
            if (length != dest_length)
            {
                return false;
            }
            memcpy(dst, src, length);
            break;

        case 1:
            if (length < 3 || (unsigned char)src[length - 3] != 0x80 || src[length - 2] != 0 || src[length - 1] != 0)
            {
                return false;
            }
            for (;;)
            {
                char code = *src++;
                if (code > 0)
                {
                    memcpy(dst, src, code);
                    dst += code;
                    src += code;
                }
                else if (code == 0)
                {
                    int count = (unsigned char)*src++;
                    memset(dst, *src++, count);
                    dst += count;
                }
                else
                {
                    code += (char)0x80;
                    if (code != 0)
                    {
                        dst += code;
                    }
                    else
                    {
                        unsigned count = *(unsigned short const*)src;
                        src += 2;
                        if ((short)count > 0)
                        {
                            dst += count;
                        }
                        else
                        {
                            if (count == 0)
                            {
                                break;
                            }
                            count -= 0x8000;
                            if (count >= 0x4000)
                            {
                                count -= 0x4000;
                                memset(dst, *src++, count);
                                dst += count;
                            }
                            else
                            {
                                memcpy(dst, src, count);
                                dst += count;
                                src += count;
                            }
                        }
                    }
                }
            }
            break;

        default:
            return false;
    }
    return ok;
}
