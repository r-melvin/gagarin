// Provenance: own-binary-via-Ghidra
// Movie-stream player routines (audio slot pump, buffer setup, drawer
// selection, file I/O callback, chunk loaders, seek and block unpackers).
// Retail passes the handle in ECX for the internal helpers (fastcall, so
// the TU is built with /Gr); the I/O callback, audio pump and block
// unpackers are reached through function pointers and stay __cdecl.
#include <string.h>
#include "movie_stream_handle.h"


// Chunk header as read from the stream: FourCC then big-endian size.
struct ChunkHeader_007BD470
{
    unsigned long Id;
    unsigned long Size;
};

// LINH table entry: frame number in the low word.
struct MovieLinhEntry_007BD470
{
    unsigned short Frame;
    unsigned short Extra;
};

// CINH table entry (six bytes): frame number first.
struct MovieCinhEntry_007BD470
{
    unsigned short Frame;
    unsigned short Extra[2];
};

// Audio packet header: unpacked size then packed size.
struct MovieAudioFormat_007BD470
{
    unsigned short Size;
    unsigned short Packed;
};

#define SWAP32_BE(x) (((((x) & 0xff0000) | ((x) >> 16)) >> 8) | ((((x) & 0xff00) | ((x) << 16)) << 8))
#define CHUNK_LEN_BE(x) ((SWAP32_BE(x) + 1) & ~1)

// Helpers owned elsewhere.
int FUN_007bd2b0(MovieHandle_007BD470* h);
void FUN_007bd270(MovieHandle_007BD470* h);
void FUN_007bd290(MovieHandle_007BD470* h);
int FUN_007c3750(MovieHandle_007BD470* h);
int FUN_007be660(MovieHandle_007BD470* h);
int FUN_007bf470(MovieHandle_007BD470* h, int mode);
char FUN_007c04e0(MovieHandle_007BD470* h, int frame);
void FUN_007c06b0(MovieHandle_007BD470* h, int frame, int* out, int mode);
int FUN_007c0740(MovieHandle_007BD470* h, int frame, int groupSize, char audio, char reset, char* isKey);
void* __cdecl FUN_007be5d0(MovieHandle_007BD470* h, int op, void* p, int size);
void FUN_007c2c60(MovieHandle_007BD470* h);
void FUN_007bdf80(MovieHandle_007BD470* h);
int FUN_007c1130(MovieHandle_007BD470* h);
int FUN_007c12b0(MovieHandle_007BD470* h);
int FUN_007c1730(MovieHandle_007BD470* h);
int FUN_007c1d40(MovieHandle_007BD470* h, unsigned long size);
int FUN_007bd690(MovieHandle_007BD470* h);
void FUN_007c35c0(MovieHandle_007BD470* h);
int FUN_007bd170(MovieHandle_007BD470* h);
void __cdecl FUN_004125f0();
void __cdecl FUN_007c7350(int* state);
int FUN_007c3860(MovieHandle_007BD470* h, int fileLen);
int FUN_007c3430(MovieHandle_007BD470* h, int start, int end, int mode);
int FUN_007c34b0(MovieHandle_007BD470* h, int start, int end, int a, int b);
int FUN_007c19f0(MovieHandle_007BD470* h, int frame, int* keyStart, int* keyEnd);
int FUN_007c0490(MovieHandle_007BD470* h);
void FUN_007c3910(MovieHandle_007BD470* h, int ticks);
void FUN_007c3950(MovieHandle_007BD470* h, int ticks);
int FUN_007c3960(MovieHandle_007BD470* h);
void FUN_007be830(MovieHandle_007BD470* h, int frame);
int __cdecl FUN_007c81db(unsigned char* src, unsigned char* dst, int arg);
int FUN_007bee20(MovieHandle_007BD470* h, MovieConfig_007BD470* config, MovieDrawState_007BD470* drawer, MovieFrame_007BD470* node, unsigned int now);
int FUN_007c3270(MovieHandle_007BD470* h, unsigned char* buf, unsigned int w, unsigned int hgt, int x, int y);
void __cdecl FUN_007c7f20(unsigned char* src, unsigned char* dst, unsigned int size);
void __cdecl FUN_007c7371(unsigned char* src, unsigned char* dst, short a, short b, unsigned int size, int* state);
int __cdecl FUN_007d07df(int fh, void* buf, int size);
long __cdecl FUN_007d7638(int fh, long offset, int whence);
extern "C" int __cdecl _open(const char* name, int mode, ...);
extern "C" int __cdecl _close(int fh);
extern "C" long __cdecl _filelength(int fh);

// unknown_1A0 table entries owned elsewhere.
int FUN_007bea40(MovieHandle_007BD470* h);
int FUN_007bf0b0(MovieHandle_007BD470* h);
int FUN_007bf140(MovieHandle_007BD470* h);
int FUN_007bf190(MovieHandle_007BD470* h);
int FUN_007bf230(MovieHandle_007BD470* h);
void __cdecl FUN_007bf220(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c3eb0(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c39c0(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c43a0(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c4730(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c4b80(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c4f90(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c53a0(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c57d0(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c6d40(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c6dd6(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c6e94(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c6fc8(unsigned short*, unsigned short*, unsigned short*, int, int, int);
void __cdecl FUN_007c3d60(unsigned short* blockTable, unsigned short* pointers,
                          unsigned short* dest, int blocksWide, int blocksHigh, int pitch);
void __cdecl FUN_007c4260(unsigned short* blockTable, unsigned short* pointers,
                          unsigned short* dest, int blocksWide, int blocksHigh, int pitch);

// FUNCTION: GAMEMD 0x007bd470
// Audio pump: hands the next ready slot (or silence on underrun) to the
// audio callback and advances the play cursor.
int __cdecl FUN_007bd470(MovieHandle_007BD470* h)
{
    int flags = h->unknown_7BC;
    int chunk = h->unknown_40.unknown_5C;
    if (flags & 0x200) {
        return 0;
    }
    int slot = h->unknown_7A0;
    int pos = h->unknown_7C4;
    if (h->unknown_40.unknown_44 & 0x200) {
        unsigned int next = slot + 1;
        if (next >= h->unknown_79C) {
            next = 0;
        }
        if (!(flags & 0x100) && h->unknown_794[next] == 0) {
            flags |= 0x400;
            h->unknown_7BC = flags;
        }
    }
    char silence = 0;
    if (h->unknown_794[slot] == 1) {
        if (h->unknown_7A4 == -1) {
            h->unknown_7A4 = slot;
            h->unknown_7C0 = pos;
        }
        slot++;
        h->unknown_798[slot - 1] = 0;
        int npos = pos + chunk;
        if (npos >= h->unknown_40.unknown_58) {
            npos = 0;
            slot = 0;
        }
        h->unknown_7C4 = npos;
        h->unknown_7A0 = slot;
    } else if (h->unknown_7BC & 0x100) {
        h->unknown_7BC |= 0x200;
        if ((unsigned int)pos < h->unknown_790) {
            chunk = h->unknown_790 - pos;
        } else {
            return 0;
        }
    } else {
        h->unknown_7BC |= 0x80;
        pos -= chunk;
        h->unknown_38++;
        slot--;
        silence = 1;
        if (pos < 0) {
            pos = h->unknown_40.unknown_58 - chunk;
            slot = h->unknown_79C - 1;
        }
        h->unknown_798[slot]++;
    }
    if (chunk > 0) {
        if (silence == 1) {
            h->unknown_40.unknown_18(h, 5, h->unknown_7B8, chunk);
        } else {
            h->unknown_40.unknown_18(h, 5, h->unknown_78C + pos, chunk);
        }
    }
    return chunk;
}

// FUNCTION: GAMEMD 0x007bd690
// Sizes and allocates the block table, loader ring, frame ring, audio buffers
// and frame index for an opened movie.
int FUN_007bd690(MovieHandle_007BD470* h)
{
    if (h->unknown_40.unknown_48 == 0) {
        return -8;
    }
    h->unknown_774 = (h->unknown_E8.unknown_10 * h->unknown_E8.unknown_A * h->unknown_E8.unknown_B + 4) & ~3;
    if (h->unknown_E8.unknown_20 == 1 || h->unknown_E8.unknown_20 == 4) {
        h->unknown_774 += h->unknown_774;
    }
    if (h->unknown_E8.unknown_22 > (unsigned int)h->unknown_774) {
        return -3;
    }
    if (h->unknown_E8.unknown_22 == 0) {
        h->unknown_E8.unknown_22 = h->unknown_774;
    }
    if (h->unknown_40.unknown_4C <= 0) {
        int group;
        if (h->unknown_74C > 0) {
            group = h->unknown_74E;
        } else {
            group = h->unknown_E8.unknown_D;
        }
        if (group == h->unknown_10) {
            h->unknown_40.unknown_4C = 1;
        } else {
            int extra = 0;
            if (h->unknown_40.unknown_48 > 1) {
                extra = (h->unknown_40.unknown_48 - 2) / group + 1;
                if (h->unknown_40.unknown_44 & 0x20) {
                    if (h->unknown_714 == 0) {
                        extra += 2;
                    } else {
                        MovieLinhEntry_007BD470* linh = (MovieLinhEntry_007BD470*)h->unknown_71C;
                        int gs = h->unknown_E8.unknown_D;
                        int count = h->unknown_714;
                        int i;
                        int needStart;
                        int needEnd;
                        if (gs > 0) {
                            needStart = 0;
                            needEnd = 0;
                            for (i = 0; i < count; i++) {
                                if (linh[i].Frame % gs != 0) {
                                    needStart = 1;
                                    break;
                                }
                            }
                            for (i = 0; i < count; i++) {
                                if (linh[i].Extra % gs != 0) {
                                    needEnd = 1;
                                    break;
                                }
                            }
                        } else {
                            MovieCinhEntry_007BD470* cinh = (MovieCinhEntry_007BD470*)h->unknown_754;
                            int ccount = h->unknown_74C;
                            needStart = 1;
                            needEnd = 1;
                            for (i = 0; i < count; i++, linh++) {
                                int k;
                                if (needStart) {
                                    for (k = 0; k < ccount; k++) {
                                        if (linh->Frame == cinh[k].Frame) {
                                            needStart = 0;
                                            break;
                                        }
                                    }
                                }
                                if (needEnd) {
                                    for (k = 0; k < ccount; k++) {
                                        if (linh->Extra == cinh[k].Frame) {
                                            needEnd = 0;
                                            break;
                                        }
                                    }
                                }
                                if (!needStart && !needEnd) {
                                    break;
                                }
                            }
                        }
                        if (needStart) {
                            extra++;
                        }
                        if (needEnd) {
                            extra++;
                        }
                    }
                }
            }
            h->unknown_40.unknown_4C = extra + 2;
        }
    }
    h->unknown_154 |= 1;
    h->unknown_768 = (h->unknown_E8.unknown_22 + 0x10) & ~3;
    h->unknown_6F0 = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_774);
    if (h->unknown_6F0 == 0) {
        FUN_007bdf80(h);
        return -8;
    }
    h->unknown_40.unknown_4(h, 4, h->unknown_6F0, h->unknown_774);
    h->unknown_30 += h->unknown_774;
    MovieLoadBuffer_007BD470* prev = 0;
    MovieLoadBuffer_007BD470* buf;
    int i;
    if (h->unknown_40.unknown_4C > 0) {
        for (i = 0; i < h->unknown_40.unknown_4C; i++) {
            buf = (MovieLoadBuffer_007BD470*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_768 + sizeof(MovieLoadBuffer_007BD470));
            if (buf == 0) {
                goto no_memory;
            }
            h->unknown_40.unknown_4(h, 4, buf, h->unknown_768 + sizeof(MovieLoadBuffer_007BD470));
            h->unknown_30 += h->unknown_768 + sizeof(MovieLoadBuffer_007BD470);
            memset(buf, 0, sizeof(MovieLoadBuffer_007BD470));
            buf->unknown_0 = (unsigned char*)(buf + 1);
            if (prev == 0) {
                h->unknown_6EC = buf;
            } else {
                prev->unknown_4 = buf;
                buf->unknown_8 = prev;
            }
            prev = buf;
        }
        if (buf != 0) {
            buf->unknown_4 = h->unknown_6EC;
            h->unknown_6EC->unknown_8 = buf;
        }
    }
    h->unknown_164 = h->unknown_6EC;
    h->unknown_168 = h->unknown_6EC;
    h->unknown_768 -= 4;
    h->unknown_770 = 0x3fc;
    h->unknown_778 = ((h->unknown_E8.unknown_6 / h->unknown_E8.unknown_A) * (h->unknown_E8.unknown_8 / h->unknown_E8.unknown_B) * 2 + 4) & ~3;
    int pal;
    if (h->unknown_E8.unknown_16 == 0) {
        pal = h->unknown_778;
    } else {
        pal = h->unknown_E8.unknown_16;
        if (h->unknown_E8.unknown_0 > 2) {
            pal <<= 8;
        }
    }
    h->unknown_154 |= 2;
    h->unknown_76C = (pal + 8) & ~3;
    h->unknown_6E8 = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_778);
    if (h->unknown_6E8 == 0) {
        FUN_007bdf80(h);
        return -8;
    }
    h->unknown_40.unknown_4(h, 4, h->unknown_6E8, h->unknown_778);
    h->unknown_30 += h->unknown_778;
    {
        MovieFrame_007BD470* prevNode = 0;
        MovieFrame_007BD470* node;
        if (h->unknown_40.unknown_48 > 0) {
            for (i = 0; i < h->unknown_40.unknown_48; i++) {
                node = (MovieFrame_007BD470*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_770 + h->unknown_76C + sizeof(MovieFrame_007BD470));
                if (node == 0) {
                    goto no_memory;
                }
                h->unknown_40.unknown_4(h, 4, node, h->unknown_770 + h->unknown_76C + sizeof(MovieFrame_007BD470));
                h->unknown_30 += h->unknown_770 + h->unknown_76C + sizeof(MovieFrame_007BD470);
                memset(node, 0, sizeof(MovieFrame_007BD470));
                node->unknown_0 = (unsigned char*)(node + 1);
                node->unknown_4 = 0;
                node->unknown_8 = (unsigned char*)(node + 1) + h->unknown_76C;
                if (prevNode == 0) {
                    h->unknown_6E4 = node;
                } else {
                    prevNode->unknown_C = node;
                    node->unknown_10 = prevNode;
                }
                prevNode = node;
            }
            if (node != 0) {
                node->unknown_C = h->unknown_6E4;
                h->unknown_6E4->unknown_10 = node;
            }
        }
    }
    h->unknown_170 = h->unknown_6E4;
    h->unknown_1A0.unknown_0 = h->unknown_6E4;
    h->unknown_6DC = h->unknown_6E4;
    h->unknown_770 -= 4;
    h->unknown_76C -= 4;
    if ((h->unknown_E8.unknown_2 & 1) && (h->unknown_40.unknown_44 & 1)) {
        if (h->unknown_E8.unknown_0 < 2) {
            h->unknown_3E = 1;
            h->unknown_3C = 22050;
            h->unknown_3F = 8;
            h->unknown_7CC = 22050;
        } else {
            if ((h->unknown_40.unknown_44 & 0x40) && (h->unknown_E8.unknown_2 & 2)) {
                h->unknown_3C = h->unknown_E8.unknown_1C;
                h->unknown_3E = h->unknown_E8.unknown_1E;
                h->unknown_3F = h->unknown_E8.unknown_1F;
            } else {
                h->unknown_3C = h->unknown_E8.unknown_18;
                h->unknown_3E = h->unknown_E8.unknown_1A;
                h->unknown_3F = h->unknown_E8.unknown_1B;
            }
            h->unknown_7CC = (h->unknown_3F >> 3) * h->unknown_3C * h->unknown_3E;
        }
        if (h->unknown_40.unknown_58 == -1) {
            h->unknown_40.unknown_58 = (h->unknown_7CC / 2 + h->unknown_7CC) / h->unknown_40.unknown_5C * h->unknown_40.unknown_5C;
        }
        if (h->unknown_40.unknown_58 <= 0) {
            FUN_007bdf80(h);
            return -18;
        }
        if (h->unknown_40.unknown_54 == 0) {
            h->unknown_78C = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_40.unknown_58);
            if (h->unknown_78C == 0) {
                FUN_007bdf80(h);
                return -8;
            }
            h->unknown_40.unknown_4(h, 4, h->unknown_78C, h->unknown_40.unknown_58);
            h->unknown_30 += h->unknown_40.unknown_58;
        } else {
            h->unknown_78C = h->unknown_40.unknown_54;
        }
        h->unknown_79C = h->unknown_40.unknown_58 / h->unknown_40.unknown_5C;
        h->unknown_794 = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_79C);
        if (h->unknown_794 == 0) {
            FUN_007bdf80(h);
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_794, h->unknown_79C);
        h->unknown_30 += h->unknown_79C;
        memset(h->unknown_794, 0, h->unknown_79C);
        h->unknown_798 = (unsigned short*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_79C * 2);
        if (h->unknown_798 == 0) {
            FUN_007bdf80(h);
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_798, h->unknown_79C * 2);
        h->unknown_30 += h->unknown_79C * 2;
        memset(h->unknown_798, 0, h->unknown_79C * 2);
        h->unknown_7B4 = h->unknown_7CC / h->unknown_E8.unknown_C * 2 + 100;
        h->unknown_7A8 = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_7B4);
        if (h->unknown_7A8 == 0) {
            FUN_007bdf80(h);
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_7A8, h->unknown_7B4);
        h->unknown_30 += h->unknown_7B4;
        h->unknown_7B8 = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_40.unknown_5C);
        if (h->unknown_7B8 == 0) {
            FUN_007bdf80(h);
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_7B8, h->unknown_40.unknown_5C);
        memset(h->unknown_7B8, 0, h->unknown_40.unknown_5C);
        h->unknown_30 += h->unknown_40.unknown_5C;
    }
    h->unknown_764 = (unsigned int*)h->unknown_40.unknown_4(h, 2, 0, h->unknown_E8.unknown_4 * 4);
    if (h->unknown_764 == 0) {
        goto no_memory;
    }
    h->unknown_40.unknown_4(h, 4, h->unknown_764, h->unknown_E8.unknown_4 * 4);
    h->unknown_30 += h->unknown_E8.unknown_4 * 4;
    return -1;
no_memory:
    FUN_007bdf80(h);
    return -8;
}

// FUNCTION: GAMEMD 0x007be4a0
// Ensures a draw buffer exists (allocating one when the handle owns it),
// then positions the image inside it.
int FUN_007be4a0(MovieHandle_007BD470* h)
{
    int w = h->unknown_40.unknown_20;
    int hgt;
    if (w == -1 || (hgt = h->unknown_40.unknown_24) == -1) {
        hgt = h->unknown_E8.unknown_8;
        w = h->unknown_E8.unknown_6;
        if (h->unknown_40.unknown_40 & 8) {
            w += h->unknown_E8.unknown_12;
            hgt += h->unknown_E8.unknown_14;
        }
    }
    unsigned char* buf = h->unknown_40.unknown_1C;
    if (h->unknown_40.unknown_40 & 1) {
        if (buf == 0) {
            int size = hgt * w;
            if (h->unknown_E8.unknown_20 == 1 || h->unknown_E8.unknown_20 == 4) {
                size += size;
            }
            buf = (unsigned char*)h->unknown_40.unknown_4(h, 2, 0, size);
            if (buf == 0) {
                return -8;
            }
            h->unknown_30 += size;
            h->unknown_40.unknown_4(h, 4, buf, size);
            memset(buf, 0, size);
            h->unknown_158 = buf;
            h->unknown_160 = hgt;
            h->unknown_15C = w;
            h->unknown_150 |= 0x20;
        }
    } else if (buf == 0) {
        return -9;
    }
    FUN_007c3270(h, buf, w, hgt, h->unknown_40.unknown_28, h->unknown_40.unknown_2C);
    h->unknown_150 |= 0x10;
    return -1;
}

// FUNCTION: GAMEMD 0x007be670
// Derives the block grid and picks the per-format drawer routines.
int FUN_007be670(MovieHandle_007BD470* h)
{
    h->unknown_1A0.unknown_524 = h->unknown_E8.unknown_6 / h->unknown_E8.unknown_A;
    h->unknown_1A0.unknown_528 = h->unknown_E8.unknown_8 / h->unknown_E8.unknown_B;
    h->unknown_1A0.unknown_52C = h->unknown_1A0.unknown_524 * h->unknown_1A0.unknown_528;
    unsigned short block = (unsigned short)((h->unknown_E8.unknown_A << 8) | h->unknown_E8.unknown_B);
    h->unknown_784 = FUN_007bf220;
    h->unknown_788 = FUN_007bf220;
    h->unknown_780 = FUN_007bf230;
    if (!(h->unknown_40.unknown_40 & 1)) {
        h->unknown_77C = FUN_007bea40;
        h->unknown_780 = FUN_007bf0b0;
    } else {
        h->unknown_77C = FUN_007bf140;
        h->unknown_780 = FUN_007bf190;
    }
    switch (block) {
    case 0x402:
        if (h->unknown_E8.unknown_20 == 0) {
            h->unknown_784 = FUN_007c6d40;
            if (h->unknown_E8.unknown_2 & 4) {
                if (h->unknown_40.unknown_40 & 0x80) {
                    h->unknown_788 = FUN_007c57d0;
                } else {
                    h->unknown_788 = FUN_007c53a0;
                }
            }
        } else if (h->unknown_E8.unknown_20 == 4) {
            h->unknown_784 = FUN_007c4260;
            h->unknown_788 = FUN_007c43a0;
        }
        break;
    case 0x404:
        switch (h->unknown_E8.unknown_20) {
        case 0:
            h->unknown_784 = FUN_007c6dd6;
            if (h->unknown_E8.unknown_2 & 4) {
                if (h->unknown_40.unknown_40 & 0x80) {
                    h->unknown_788 = FUN_007c4b80;
                } else if (h->unknown_40.unknown_40 & 0x40) {
                    h->unknown_788 = FUN_007c4f90;
                } else {
                    h->unknown_788 = FUN_007c4730;
                }
            } else if (h->unknown_40.unknown_40 & 0x40) {
                h->unknown_784 = FUN_007c6e94;
            }
            break;
        case 1:
            h->unknown_784 = FUN_007c6fc8;
            h->unknown_788 = FUN_007c39c0;
            break;
        case 4:
            h->unknown_784 = FUN_007c3d60;
            h->unknown_788 = FUN_007c3eb0;
            break;
        }
        break;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x007bea80
// Advances the drawer to the next decoded frame, dropping frames to catch
// up with the clock and applying palette updates on the way.
int FUN_007bea80(MovieHandle_007BD470* h)
{
    MovieDrawState_007BD470* drawer = &h->unknown_1A0;
    MovieConfig_007BD470* config = &h->unknown_40;
    MovieFrame_007BD470* node = drawer->unknown_0;
    if (!(node->unknown_14 & 1)) {
        drawer->unknown_538++;
        if (!(drawer->unknown_4 & 4) || (h->unknown_150 & 4)) {
            return -9;
        }
        drawer->unknown_0 = node->unknown_10;
        drawer->unknown_0->unknown_14 = drawer->unknown_0->unknown_18;
        if (drawer->unknown_4 & 0x10) {
            drawer->unknown_4 |= 8;
            node->unknown_14 |= 0x80;
        }
        return -1;
    }
    if (drawer->unknown_4 & 0x10) {
        drawer->unknown_530 = drawer->unknown_0->unknown_1C;
        drawer->unknown_4 |= 8;
        node->unknown_14 |= 0x80;
        return -1;
    }
    if (config->unknown_44 & 2) {
        drawer->unknown_530 = node->unknown_1C;
        FUN_007c3910(h, node->unknown_1C * 60 / config->unknown_34);
        return -1;
    }
    int now = FUN_007c3960(h);
    int next;
    if (!(drawer->unknown_4 & 2)) {
        next = drawer->unknown_530 + 1;
    } else {
        next = drawer->unknown_530 + 2;
    }
    if (now < next * 60 / config->unknown_34) {
        if (!(drawer->unknown_4 & 4)) {
            return -10;
        }
        if (FUN_007bee20(h, config, drawer, node, now) == drawer->unknown_530 && (node->unknown_14 & 0x80)) {
            drawer->unknown_530 = node->unknown_1C;
            return -1;
        }
        drawer->unknown_530 = node->unknown_1C;
        drawer->unknown_4 |= 8;
        node->unknown_14 |= 0x80;
        return -1;
    }
    int target = FUN_007bee20(h, config, drawer, node, now);
    if (config->unknown_40 & 4) {
        drawer->unknown_530 = drawer->unknown_0->unknown_1C;
        return -1;
    }
    int slack = config->unknown_30 / 3 - 1;
    if (slack < 0) {
        slack = 0;
    }
    if (node->unknown_1C != target) {
        while (!(node->unknown_14 & 2)) {
            int frame = drawer->unknown_0->unknown_1C;
            int behind;
            if (frame >= drawer->unknown_530 && frame <= h->unknown_140) {
                behind = frame - drawer->unknown_530;
            } else {
                int third = h->unknown_40.unknown_30 / 3;
                int ahead = h->unknown_140 - drawer->unknown_530;
                if (ahead < 0) {
                    behind = third;
                } else if ((frame -= h->unknown_128) < 0) {
                    behind = third;
                } else {
                    behind = frame + ahead + 1;
                }
            }
            if (behind > slack) {
                break;
            }
            if (node->unknown_14 & 4) {
                if (node->unknown_14 & 8) {
                    node->unknown_28 = FUN_007c81db(node->unknown_8 + node->unknown_24, node->unknown_8, h->unknown_770);
                    node->unknown_14 &= ~8;
                }
                memcpy(drawer->unknown_24, node->unknown_8, node->unknown_28);
                drawer->unknown_20 = node->unknown_28;
                drawer->unknown_4 |= 1;
            }
            if (h->unknown_40.unknown_8 != 0) {
                if (node->unknown_14 & 0x100) {
                    h->unknown_40.unknown_8(h, 4, node->unknown_1C, h->unknown_120);
                    node->unknown_14 &= ~0x100;
                }
                if (node->unknown_14 & 0x200) {
                    h->unknown_40.unknown_8(h, 5, node->unknown_1C, h->unknown_120);
                    node->unknown_14 &= ~0x200;
                }
                if (node->unknown_14 & 0x400) {
                    FUN_007be830(h, node->unknown_1C);
                    node->unknown_14 &= ~0x400;
                }
            }
            if (h->unknown_40.unknown_C != 0 && h->unknown_40.unknown_C(0, node->unknown_1C) != 0) {
                return -2;
            }
            node->unknown_18 = node->unknown_14;
            node->unknown_14 = 0;
            node = node->unknown_C;
            drawer->unknown_0 = node;
            h->unknown_1C++;
            if (!(node->unknown_14 & 1)) {
                drawer->unknown_538++;
                if (!(drawer->unknown_4 & 4) || (h->unknown_150 & 4)) {
                    return -9;
                }
                drawer->unknown_0 = drawer->unknown_0->unknown_10;
                drawer->unknown_0->unknown_14 = drawer->unknown_0->unknown_18;
                return -1;
            }
            if (node->unknown_1C == target) {
                break;
            }
        }
    }
    drawer->unknown_530 = drawer->unknown_0->unknown_1C;
    return -1;
}

// FUNCTION: GAMEMD 0x007bee20
// Works out which frame the clock says should be on screen, looping the
// clock back when a loop range is active, and returns it.
int FUN_007bee20(MovieHandle_007BD470* h, MovieConfig_007BD470* config, MovieDrawState_007BD470* drawer, MovieFrame_007BD470* node, unsigned int now)
{
    int rate = config->unknown_30;
    int last = node->unknown_1C;
    int frame = (unsigned int)(rate * now) / 60;
    if (drawer->unknown_4 & 2) {
        frame--;
    }
    int loopEnd = h->unknown_12C;
    char looped = 0;
    if (h->unknown_150 & 0x80) {
        if (h->unknown_150 & 0x100) {
            loopEnd = h->unknown_140;
        }
        while ((!(config->unknown_40 & 4) && frame > loopEnd) || ((config->unknown_40 & 4) && last == h->unknown_128 && !looped)) {
            int left = h->unknown_128 - loopEnd - 1;
            FUN_007c3950(h, left * 60 / rate);
            frame = FUN_007c3960(h) * rate / 60;
            looped = 1;
            if (left == 0) {
                break;
            }
        }
    }
    if (config->unknown_40 & 4) {
        if (frame > last) {
            int back = last - frame;
            if (!(h->unknown_E8.unknown_2 & 1) || !(config->unknown_44 & 1)) {
                FUN_007c3950(h, back * 60 / rate);
            }
            frame = last;
            h->unknown_150 |= 0x800;
        } else {
            h->unknown_150 &= ~0x800;
        }
    }
    if (looped) {
        if ((drawer->unknown_4 & 2) && !(config->unknown_40 & 4) && --frame < h->unknown_128) {
            frame = loopEnd;
        }
        if (h->unknown_138 != -1) {
            h->unknown_128 = h->unknown_13C;
            h->unknown_13C = -1;
            h->unknown_12C = h->unknown_138;
            h->unknown_138 = -1;
        }
        if (!(h->unknown_150 & 0x100)) {
            h->unknown_144 = h->unknown_128;
            h->unknown_140 = h->unknown_12C;
        }
        h->unknown_150 &= ~0x180;
    }
    return frame;
}

// FUNCTION: GAMEMD 0x007bf240
// Default file I/O callback: open/close/read/seek/length on a CRT handle.
int __cdecl FUN_007bf240(MovieHandle_007BD470* h, int op, void* buf, int b)
{
    int fh = h->unknown_40.unknown_78;
    int rc = 0;
    switch (op) {
    case 3:
        rc = _open((const char*)buf, 0x8000);
        if (rc != -1) {
            h->unknown_40.unknown_78 = rc;
            return 0;
        }
        break;
    case 5:
        return FUN_007d07df(fh, buf, b) != b;
    case 6:
        return 1;
    case 7:
        return FUN_007d7638(fh, b, (int)buf) == -1;
    case 8:
        if (b > 0) {
            rc = FUN_007d7638(fh, b - 1, (int)buf) == -1;
            if (rc) {
                break;
            }
            return FUN_007d07df(fh, &b, 1) != 1;
        }
        rc = FUN_007d7638(fh, b, (int)buf) == -1;
        if (rc) {
            break;
        }
        rc = FUN_007d07df(fh, &b, 1) != 1;
        if (rc) {
            break;
        }
        return FUN_007d7638(fh, -1, 1) == -1;
    case 9:
        *(long*)b = _filelength(fh);
        return 0;
    case 4:
        _close(fh);
    case 1:
    case 2:
        rc = 0;
        break;
    }
    return rc;
}

// FUNCTION: GAMEMD 0x007c0530
// Seeks the stream to the nearest key frame at or before frame.
int FUN_007c0530(MovieHandle_007BD470* h, int frame, int reset)
{
    int result = -1;
    MovieFrame_007BD470* node = h->unknown_170;
    unsigned int* index;
    if (frame <= h->unknown_11C && (index = h->unknown_764) != 0) {
        int key;
        int cur;
        if (h->unknown_760 != 0) {
            FUN_007c06b0(h, frame, &key, 0);
            if (reset == 0) {
                FUN_007c06b0(h, h->unknown_184, &cur, 0);
                if (key == cur) {
                    goto done;
                }
            }
        } else {
            int i;
            key = -1;
            for (i = frame; i >= 0; i--) {
                if (index[i] & 0x40000000) {
                    key = i;
                    break;
                }
            }
            if (reset == 0) {
                cur = -1;
                for (i = h->unknown_184; i >= 0; i--) {
                    if (index[i] & 0x40000000) {
                        cur = i;
                        break;
                    }
                }
                if (key == cur) {
                    goto done;
                }
            }
        }
        if (key >= 0) {
            if (h->unknown_40.unknown_0(h, 7, 0, (h->unknown_764[key] & 0x0fffffff) * 2) == 0) {
                if (reset != 0) {
                    h->unknown_174 = 0;
                    h->unknown_178 = 0;
                    h->unknown_168 = h->unknown_6EC;
                    h->unknown_164 = h->unknown_6EC;
                    h->unknown_180 = 0;
                    node->unknown_14 = 0;
                }
                result = FUN_007bf470(h, 0x1e);
                return result;
            }
            result = -6;
        }
    done:
        return result;
    }
    return -6;
}

// FUNCTION: GAMEMD 0x007c0740
// Loads frames from the group key frame up to frame, priming the audio
// ring so sound starts in step with the picture.
int FUN_007c0740(MovieHandle_007BD470* h, int frame, int groupSize, char audio, char reset, char* isKey)
{
    int target = frame;
    MovieFrame_007BD470* node = h->unknown_1A0.unknown_0;
    int group = 0;
    int keyStart;
    int keyEnd;
    char key;
    if (h->unknown_764 == 0) {
        return -6;
    }
    int start = frame;
    if (h->unknown_40.unknown_4C > 1) {
        int curGroup;
        key = 0;
        if (groupSize > 0) {
            group = frame / groupSize;
            keyStart = group * groupSize;
            if (keyStart >= groupSize) {
                keyStart -= groupSize;
            }
            if (group == 0) {
                keyEnd = -1;
                curGroup = h->unknown_184 / groupSize;
            } else {
                keyEnd = keyStart + groupSize - 1;
                curGroup = h->unknown_184 / groupSize;
            }
        } else {
            group = FUN_007c19f0(h, frame, &keyStart, &keyEnd);
            curGroup = FUN_007c19f0(h, h->unknown_184, 0, 0);
        }
        start = keyStart;
        if (!reset) {
            if (curGroup == group) {
                key = 1;
                start = keyEnd + 1;
                h->unknown_168 = h->unknown_16C;
                h->unknown_164 = h->unknown_16C->unknown_4;
                h->unknown_174 = 0;
                h->unknown_178 = 0;
            } else {
                if (h->unknown_174 == 0) {
                    while (h->unknown_168 != node->unknown_4 || !(node->unknown_14 & 1)) {
                        node = node->unknown_C;
                        if (h->unknown_1A0.unknown_0 == node) {
                            h->unknown_164 = h->unknown_168;
                            break;
                        }
                    }
                }
                h->unknown_174 = 0;
                h->unknown_178 = 0;
            }
        } else {
            h->unknown_168 = h->unknown_6EC;
            h->unknown_164 = h->unknown_6EC;
            h->unknown_174 = 0;
            h->unknown_178 = 0;
        }
    } else {
        key = 1;
        keyStart = frame;
        keyEnd = frame;
    }
    *isKey = key;
    int audioStart;
    if ((h->unknown_40.unknown_44 & 1) && h->unknown_78C != 0) {
        int rate = (h->unknown_3F >> 3) * h->unknown_3E * h->unknown_3C;
        int perFrame = rate / h->unknown_40.unknown_30;
        int preload = h->unknown_E8.unknown_26;
        if (!(h->unknown_E8.unknown_2 & 8) && preload == 0) {
            preload = rate / 2;
        }
        if (audio && preload > 0) {
            int frames = preload / perFrame;
            int bytes = frames * perFrame;
            if (preload > bytes) {
                frames++;
            }
            audioStart = frame - frames;
            if (audioStart < 0) {
                audioStart = 0;
                h->unknown_7AC = perFrame * frame;
            } else {
                h->unknown_7AC = bytes - preload + perFrame;
            }
            if (audioStart < start) {
                start = audioStart;
            }
        } else {
            audioStart = frame;
            h->unknown_7AC = 0;
        }
        if (reset) {
            memset(h->unknown_794, 0, h->unknown_79C);
            memset(h->unknown_78C, 0, h->unknown_40.unknown_58);
            h->unknown_7B0 = 0;
            if (audioStart == 0) {
                h->unknown_790 = 0;
            } else {
                h->unknown_790 = preload;
                int slots = (unsigned int)preload / h->unknown_40.unknown_5C;
                for (int i = 0; i < slots; i++) {
                    h->unknown_794[i] = 1;
                }
            }
        }
    } else {
        audio = 0;
        audioStart = frame;
        h->unknown_7AC = 0;
    }
    if (frame != 0) {
        int count = h->unknown_714;
        if (count > 0 && (h->unknown_716 & 3)) {
            MovieLinhEntry_007BD470* entry = (MovieLinhEntry_007BD470*)h->unknown_71C;
            for (int i = 0; i < count; i++) {
                if (frame == entry->Frame) {
                    goto direct;
                }
                entry++;
            }
        }
        if (h->unknown_40.unknown_0(h, 7, 0, (h->unknown_764[start] & 0x0fffffff) * 2) != 0) {
            return -6;
        }
        int f = start;
        int rc = -1;
        h->unknown_180 = f;
        int mode = group != 0 ? 0x15 : 5;
        if (!audio) {
            mode |= 2;
        }
        int n = frame - f;
        for (int i = 0; i < n; i++, f++) {
            if (reset) {
                h->unknown_170->unknown_14 &= ~1;
            }
            if (audio) {
                if (reset && f == audioStart) {
                    h->unknown_7B0 = 0;
                }
                if (f < audioStart) {
                    mode |= 2;
                } else {
                    mode &= ~2;
                }
            }
            if (key && f <= keyEnd) {
                mode |= 8;
            } else {
                mode &= ~8;
            }
            rc = FUN_007bf470(h, mode);
            if (rc != -1) {
                if (!reset) {
                    return rc;
                }
                if (rc != -9 && rc != -11) {
                    return rc;
                }
                rc = -1;
            }
        }
        return rc;
    }
direct:
    if (reset) {
        h->unknown_170->unknown_14 = 0;
    }
    int mode;
    if (key) {
        mode = 0x10;
    } else {
        mode = 0;
        h->unknown_168 = h->unknown_164;
    }
    char resume = 0;
    int rc = -1;
    int fr = target;
    int result;
    if ((h->unknown_154 & 4) && fr == h->unknown_708 && h->unknown_700 != 0) {
        if (h->unknown_6FC + h->unknown_700 <= (int)((h->unknown_764[h->unknown_12C] & 0x0fffffff) * 2)) {
            resume = 1;
        }
        h->unknown_704 = 0;
    } else if (h->unknown_40.unknown_0(h, 7, 0, (h->unknown_764[fr] & 0x0fffffff) * 2) != 0) {
        result = -6;
        goto done;
    }
    if (fr > 0 && (!(mode & 0x10) || !(h->unknown_E8.unknown_2 & 0x10))) {
        rc = FUN_007bf470(h, mode | 6);
        if (rc != -1) {
            result = rc;
            goto done;
        }
    }
    if (resume && h->unknown_40.unknown_0(h, 8, 0, h->unknown_700 + h->unknown_6FC) != 0) {
        result = -6;
    } else {
        result = rc;
    }
done:
    if (!reset) {
        return result;
    }
    if (result == -9 || result == -11) {
        return -1;
    }
    return result;
}

// FUNCTION: GAMEMD 0x007c1150
// Loads the LINH header chunk and its LIND table.
int FUN_007c1150(MovieHandle_007BD470* h)
{
    ChunkHeader_007BD470 chunk;
    if (h->unknown_40.unknown_0(h, 5, &chunk, 8) != 0) {
        return -2;
    }
    if (chunk.Id != 0x484e494c) {
        return -4;
    }
    unsigned short* count = &h->unknown_714;
    if (h->unknown_40.unknown_0(h, 5, count, CHUNK_LEN_BE(chunk.Size)) != 0) {
        return -4;
    }
    if (*count > 0) {
        int size = *count * 4;
        h->unknown_71C = h->unknown_40.unknown_4(h, 2, 0, size);
        if (h->unknown_71C == 0) {
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_71C, size);
        h->unknown_30 += size;
        if (h->unknown_40.unknown_0(h, 5, &chunk, 8) != 0) {
            return -2;
        }
        if (chunk.Id != 0x444e494c) {
            return -4;
        }
        if (h->unknown_40.unknown_0(h, 5, h->unknown_71C, CHUNK_LEN_BE(chunk.Size)) != 0) {
            return -4;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x007c1a70
// Loads the CINH header chunk and its CIND table.
int FUN_007c1a70(MovieHandle_007BD470* h)
{
    ChunkHeader_007BD470 chunk;
    if (h->unknown_40.unknown_0(h, 5, &chunk, 8) != 0) {
        return -2;
    }
    if (chunk.Id != 0x484e4943) {
        return -4;
    }
    unsigned short* count = &h->unknown_74C;
    if (h->unknown_40.unknown_0(h, 5, count, CHUNK_LEN_BE(chunk.Size)) != 0) {
        return -4;
    }
    if (h->unknown_E8.unknown_D == 0 && *count > 0) {
        int size = *count * 6;
        h->unknown_754 = h->unknown_40.unknown_4(h, 2, 0, size);
        if (h->unknown_754 == 0) {
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_754, size);
        h->unknown_30 += size;
        if (h->unknown_40.unknown_0(h, 5, &chunk, 8) != 0) {
            return -2;
        }
        if (chunk.Id != 0x444e4943) {
            return -4;
        }
        if (h->unknown_40.unknown_0(h, 5, h->unknown_754, CHUNK_LEN_BE(chunk.Size)) != 0) {
            return -4;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x007c1be0
// Loads the PINH header chunk and its PIND table.
int FUN_007c1be0(MovieHandle_007BD470* h)
{
    ChunkHeader_007BD470 chunk;
    if (h->unknown_40.unknown_0(h, 5, &chunk, 8) != 0) {
        return -2;
    }
    if (chunk.Id != 0x484e4950) {
        return -4;
    }
    unsigned short* count = &h->unknown_758;
    if (h->unknown_40.unknown_0(h, 5, count, CHUNK_LEN_BE(chunk.Size)) != 0) {
        return -4;
    }
    if (*count > 0) {
        int size = *count * 2;
        h->unknown_760 = h->unknown_40.unknown_4(h, 2, 0, size);
        if (h->unknown_760 == 0) {
            return -8;
        }
        h->unknown_40.unknown_4(h, 4, h->unknown_760, size);
        h->unknown_30 += size;
        if (h->unknown_40.unknown_0(h, 5, &chunk, 8) != 0) {
            return -2;
        }
        if (chunk.Id != 0x444e4950) {
            return -4;
        }
        if (h->unknown_40.unknown_0(h, 5, h->unknown_760, CHUNK_LEN_BE(chunk.Size)) != 0) {
            return -4;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x007c2250
// Reads one compressed audio packet into the ring (or the temp buffer).
int FUN_007c2250(MovieHandle_007BD470* h, int size)
{
    int len = (size + 1) & ~1;
    if (!(h->unknown_40.unknown_44 & 1) || h->unknown_78C == 0) {
        return h->unknown_40.unknown_0(h, 7, (void*)1, len) ? -6 : -1;
    }
    MovieAudioFormat_007BD470 hdr;
    if (h->unknown_40.unknown_0(h, 5, &hdr, 4) != 0) {
        return -4;
    }
    len -= 4;
    if (hdr.Size > h->unknown_7B4 && h->unknown_790 == 0) {
        if (hdr.Size == hdr.Packed) {
            if (h->unknown_40.unknown_0(h, 5, h->unknown_78C, len) != 0) {
                return -4;
            }
        } else {
            unsigned char* src = h->unknown_78C + h->unknown_40.unknown_58 - len;
            if (h->unknown_40.unknown_0(h, 5, src, len) != 0) {
                return -4;
            }
            FUN_007c7f20(src, h->unknown_78C, hdr.Size);
        }
        h->unknown_790 += hdr.Size;
        for (int i = 0; i < hdr.Size / h->unknown_40.unknown_5C; i++) {
            h->unknown_794[i] = 1;
        }
        return -1;
    }
    if (hdr.Size == hdr.Packed) {
        if (h->unknown_40.unknown_0(h, 5, h->unknown_7A8, len) != 0) {
            return -4;
        }
    } else {
        unsigned char* src = h->unknown_7A8 + h->unknown_7B4 - len;
        if (h->unknown_40.unknown_0(h, 5, src, len) != 0) {
            return -4;
        }
        FUN_007c7f20(src, h->unknown_7A8, hdr.Size);
    }
    h->unknown_7B0 = hdr.Size;
    return -1;
}

// FUNCTION: GAMEMD 0x007c2410
// Reads one compressed audio packet into the ring (or the temp buffer).
int FUN_007c2410(MovieHandle_007BD470* h, unsigned int size)
{
    int len = (size + 1) & ~1;
    if (!(h->unknown_40.unknown_44 & 1) || h->unknown_78C == 0) {
        return h->unknown_40.unknown_0(h, 7, (void*)1, len) ? -6 : -1;
    }
    unsigned int out = (h->unknown_3F >> 2) * size;
    if (out > h->unknown_7B4 && h->unknown_790 == 0) {
        unsigned char* src = h->unknown_78C + h->unknown_40.unknown_58 - len;
        if (h->unknown_40.unknown_0(h, 5, src, len) != 0) {
            return -4;
        }
        FUN_007c7371(src, h->unknown_78C, h->unknown_3F, h->unknown_3E, out, h->unknown_7D0);
        if (h->unknown_7AC != 0) {
            out -= h->unknown_7AC;
            memcpy(h->unknown_78C, h->unknown_78C + h->unknown_7AC, out);
            h->unknown_7AC = 0;
        }
        h->unknown_790 += out;
        for (unsigned int i = 0; i < out / h->unknown_40.unknown_5C; i++) {
            h->unknown_794[i] = 1;
        }
        return -1;
    }
    unsigned char* src = h->unknown_7A8 + h->unknown_7B4 - len;
    if (h->unknown_40.unknown_0(h, 5, src, len) != 0) {
        return -4;
    }
    FUN_007c7371(src, h->unknown_7A8, h->unknown_3F, h->unknown_3E, out, h->unknown_7D0);
    h->unknown_7B0 = out;
    return -1;
}

// FUNCTION: GAMEMD 0x007c2590
// Opens a movie: allocates the handle, copies the config, opens the file
// and walks the header chunks up to the frame index, then sets up audio,
// the preload cache and the drawer.
int FUN_007c2590(const char* name, MovieConfig_007BD470* config, MovieHandle_007BD470** out)
{
    *out = 0;
    if (config == 0) {
        return -17;
    }
    if (config->unknown_10 == 0) {
        return -15;
    }
    if (config->unknown_38 == 0) {
        return -16;
    }
    MovieHandle_007BD470* h;
    if (config->unknown_4 == 0) {
        h = (MovieHandle_007BD470*)FUN_007be5d0(0, 2, 0, sizeof(MovieHandle_007BD470));
        if (h == 0) {
            return -8;
        }
        FUN_007be5d0(h, 4, h, sizeof(MovieHandle_007BD470));
    } else {
        h = (MovieHandle_007BD470*)config->unknown_4(0, 2, 0, sizeof(MovieHandle_007BD470));
        if (h == 0) {
            return -8;
        }
        config->unknown_4(h, 4, h, sizeof(MovieHandle_007BD470));
    }
    memset(h, 0, sizeof(MovieHandle_007BD470));
    MovieConfig_007BD470* cfg = &h->unknown_40;
    h->unknown_30 = sizeof(MovieHandle_007BD470);
    *cfg = *config;
    if (cfg->unknown_4 == 0) {
        cfg->unknown_4 = FUN_007be5d0;
    }
    if (cfg->unknown_0 == 0) {
        cfg->unknown_0 = FUN_007bf240;
    }
    if (cfg->unknown_0(h, 3, (void*)name, 0) != 0) {
        cfg->unknown_4(h, 5, h, sizeof(MovieHandle_007BD470));
        cfg->unknown_4(h, 3, h, 0);
        return -3;
    }
    int skip = strlen(name) - 0x1f;
    if (skip < 0) {
        skip = 0;
    }
    strcpy(h->unknown_C8, name + skip);
    ChunkHeader_007BD470 chunk;
    if (cfg->unknown_0(h, 5, &chunk, 8) != 0) {
        FUN_007c2c60(h);
        return -4;
    }
    if (chunk.Id == 0x4d524f46 && chunk.Size != 0) {
        if (cfg->unknown_0(h, 5, &chunk, 4) != 0) {
            FUN_007c2c60(h);
            return -4;
        }
        if (chunk.Id == 0x41515657) {
            for (;;) {
                if (cfg->unknown_0(h, 5, &chunk, 8) != 0) {
                    goto read_error;
                }
                chunk.Size = SWAP32_BE(chunk.Size);
                switch (chunk.Id) {
                case 0x44485156: {
                    if (chunk.Size != 0x2a) {
                        goto bad_format;
                    }
                    MovieHeader_007BD470* hdr = &h->unknown_E8;
                    if (cfg->unknown_0(h, 5, hdr, chunk.Size) != 0) {
                        goto read_error;
                    }
                    h->unknown_0 = hdr->unknown_0;
                    h->unknown_10 = hdr->unknown_4;
                    h->unknown_2 = hdr->unknown_6;
                    h->unknown_4 = hdr->unknown_8;
                    h->unknown_C = hdr->unknown_20;
                    h->unknown_E = hdr->unknown_C;
                    if (cfg->unknown_30 == -1) {
                        cfg->unknown_30 = hdr->unknown_C;
                    }
                    if (cfg->unknown_34 == -1) {
                        cfg->unknown_34 = hdr->unknown_C;
                    }
                    if (cfg->unknown_34 == -1 || cfg->unknown_34 == 0) {
                        cfg->unknown_34 = hdr->unknown_C;
                    }
                    if (hdr->unknown_0 > 1 && !(hdr->unknown_2 & 2)) {
                        cfg->unknown_44 &= ~0x40;
                    }
                    break;
                }
                case 0x464e4943:
                    if (FUN_007c1a70(h) != -1) {
                        goto read_error;
                    }
                    break;
                case 0x464e494c:
                    if (FUN_007c1150(h) != -1) {
                        goto read_error;
                    }
                    break;
                case 0x464e4950:
                    if (FUN_007c1be0(h) != -1) {
                        goto read_error;
                    }
                    break;
                case 0x50494c43:
                    if (FUN_007c1130(h) != -1) {
                        goto read_error;
                    }
                    break;
                case 0x4943534d:
                    if (FUN_007c1730(h) != -1) {
                        goto read_error;
                    }
                    break;
                case 0x4943464d:
                    if (FUN_007c12b0(h) != -1) {
                        goto read_error;
                    }
                    break;
                case 0x464e4946:
                    goto frame_index;
                default:
                    if (cfg->unknown_0(h, 7, (void*)1, (chunk.Size + 1) & ~1) != 0) {
                        FUN_007c2c60(h);
                        return -6;
                    }
                    break;
                }
            }
        }
    }
bad_format:
    FUN_007c2c60(h);
    return -7;
read_error:
    FUN_007c2c60(h);
    return -4;
no_memory:
    FUN_007c2c60(h);
    return -8;
frame_index:
    if (FUN_007bd690(h) != -1) {
        goto no_memory;
    }
    if (FUN_007c1d40(h, chunk.Size) != -1) {
        goto read_error;
    }
    if (h->unknown_E8.unknown_20 == 0 && h->unknown_758 == 0) {
        unsigned short keys = 0;
        unsigned int* index = h->unknown_764;
        for (int i = h->unknown_10; i > 0; i--) {
            if (*index & 0x40000000) {
                keys++;
            }
            index++;
        }
        h->unknown_758 = keys;
    }
    FUN_007c35c0(h);
    if (!(h->unknown_E8.unknown_2 & 1)) {
        cfg->unknown_44 &= ~1;
    }
    if (cfg->unknown_44 & 1) {
        if (cfg->unknown_18 == 0) {
            FUN_007c2c60(h);
            return -21;
        }
        if (cfg->unknown_44 & 0x40) {
            h->unknown_3C = h->unknown_E8.unknown_1C;
            h->unknown_3E = h->unknown_E8.unknown_1E;
            h->unknown_3F = h->unknown_E8.unknown_1F;
        } else {
            h->unknown_3C = h->unknown_E8.unknown_18;
            h->unknown_3E = h->unknown_E8.unknown_1A;
            h->unknown_3F = h->unknown_E8.unknown_1B;
        }
        if (FUN_007bd170(h) != -1) {
            FUN_007c2c60(h);
            return -13;
        }
        FUN_004125f0();
        h->unknown_7BC |= 0x40000000;
        FUN_007c7350(h->unknown_7D0);
    } else if (cfg->unknown_18 != 0) {
        h->unknown_40.unknown_18(h, 1, 0, 0);
    }
    if (cfg->unknown_44 & 0x20) {
        if ((cfg->unknown_44 & 0x100) && h->unknown_714 > 0) {
            int fileLen;
            if (cfg->unknown_0(h, 9, &fileLen, 0) != 0) {
                fileLen = 0;
            }
            h->unknown_6F8 = FUN_007c3860(h, fileLen);
            int avail;
            cfg->unknown_4(h, 6, &avail, 0);
            if (avail < 0) {
                avail = fileLen > 0 ? fileLen : 0;
            }
            if (h->unknown_6F8 > avail) {
                h->unknown_6F8 = avail;
            }
            if (h->unknown_6F8 > 0) {
                h->unknown_6F4 = (unsigned char*)cfg->unknown_4(h, 2, 0, h->unknown_6F8);
                if (h->unknown_6F4 == 0) {
                    goto no_memory;
                }
                cfg->unknown_4(h, 4, h->unknown_6F4, h->unknown_6F8);
                h->unknown_154 |= 4;
                h->unknown_30 += h->unknown_6F8;
                h->unknown_710 = -1;
                h->unknown_708 = -1;
                h->unknown_70C = -1;
            }
        }
        if (cfg->unknown_70 >= 0) {
            if (FUN_007c3430(h, cfg->unknown_70, cfg->unknown_74, 2) != -1) {
                FUN_007c2c60(h);
                return -23;
            }
        } else if (FUN_007c34b0(h, 0, h->unknown_11C, 0, 0) != -1) {
            FUN_007c2c60(h);
            return -23;
        }
    } else {
        h->unknown_12C = h->unknown_11C;
    }
    if (FUN_007be670(h) != -1) {
        return -3;
    }
    if (!(cfg->unknown_44 & 0x20) || cfg->unknown_70 < 0) {
        if (FUN_007c0490(h) != -1) {
            FUN_007c2c60(h);
            return -4;
        }
    }
    *out = h;
    return -1;
}

// FUNCTION: GAMEMD 0x007c2d00
// Plays (mode 0/1), pauses (mode 2) or stops (mode 3) the movie: starts
// the clock on first use, then loads and draws frames until done.
int FUN_007c2d00(MovieHandle_007BD470* h, int mode, int flags)
{
    int rc = -1;
    if (!(h->unknown_150 & 8)) {
        rc = FUN_007be660(h);
        if (rc != -1) {
            return rc;
        }
        if (!(h->unknown_150 & 0x10)) {
            FUN_007be4a0(h);
        }
        if ((h->unknown_40.unknown_44 & 1) && *h->unknown_794 != 0) {
            FUN_007bd270(h);
        }
        FUN_007c3910(h, h->unknown_1A0.unknown_0->unknown_1C * 60 / h->unknown_40.unknown_34);
        h->unknown_20 = FUN_007c3960(h);
        h->unknown_150 |= 8;
    }
    int now;
    if (h->unknown_40.unknown_14 != 0) {
        now = h->unknown_40.unknown_14(h);
    } else {
        now = -1;
    }
    if (h->unknown_28 == -1) {
        h->unknown_28 = now;
        h->unknown_2C = 0;
    } else {
        int delta = now - h->unknown_28;
        h->unknown_28 = now;
        if (delta > h->unknown_2C) {
            h->unknown_2C = delta;
        }
    }
    switch (mode) {
    default:
        if (h->unknown_150 & 0x40) {
            h->unknown_150 &= ~0x40;
            if (h->unknown_40.unknown_44 & 1) {
                FUN_007bd270(h);
            }
            FUN_007c3910(h, h->unknown_24);
        }
        while ((h->unknown_150 & 6) != 6) {
            if (!(h->unknown_150 & 4)) {
                rc = FUN_007bf470(h, 0);
                if (rc == -1) {
                    h->unknown_14++;
                } else if (rc != -9 && rc != -11) {
                    h->unknown_150 |= 4;
                }
            }
            if (h->unknown_40.unknown_44 & 0x200) {
                if (rc != -9 && !(h->unknown_150 & 4)) {
                    if (h->unknown_7BC & 0x400) {
                        if (h->unknown_7BC & 0x40) {
                            FUN_007bd290(h);
                        }
                        h->unknown_150 |= 0x200;
                        h->unknown_7BC &= ~0x400;
                    }
                } else if ((h->unknown_150 & 0x200) && !(h->unknown_150 & 0x800)) {
                    h->unknown_150 |= 0x400;
                    if (h->unknown_40.unknown_44 & 1) {
                        FUN_007bd270(h);
                    }
                }
            }
            if (!(h->unknown_40.unknown_40 & 2)) {
                if ((h->unknown_40.unknown_44 & 0x200) && (h->unknown_150 & 0x200)) {
                    if (h->unknown_150 & 0x400) {
                        h->unknown_150 &= ~0x600;
                    } else if (!(h->unknown_150 & 0x800)) {
                        rc = -10;
                        break;
                    }
                }
                if (flags & 1) {
                    h->unknown_1A0.unknown_4 |= 2;
                } else if (flags & 2) {
                    h->unknown_1A0.unknown_4 |= 4;
                }
                rc = h->unknown_77C(h);
                if (rc == -1) {
                    if (!(h->unknown_1A0.unknown_4 & 8)) {
                        h->unknown_18++;
                    }
                    rc = FUN_007c3750(h);
                    if (rc != -1) {
                        h->unknown_150 |= 6;
                        h->unknown_1A0.unknown_4 &= ~6;
                    } else {
                        h->unknown_1A0.unknown_4 &= ~6;
                        rc = h->unknown_1A0.unknown_530;
                    }
                } else {
                    if (rc == -9 && (h->unknown_150 & 4)) {
                        h->unknown_150 |= 2;
                    }
                    h->unknown_1A0.unknown_4 &= ~6;
                }
            } else {
                h->unknown_150 |= 2;
                h->unknown_1A0.unknown_0->unknown_14 = 0;
                h->unknown_1A0.unknown_0 = h->unknown_1A0.unknown_0->unknown_C;
            }
            if (mode == 1) {
                break;
            }
        }
        break;
    case 2:
        if (!(h->unknown_150 & 0x40)) {
            h->unknown_150 |= 0x40;
            h->unknown_24 = FUN_007c3960(h);
            if (h->unknown_7BC & 0x40) {
                FUN_007bd290(h);
            }
        }
        if (flags & 2) {
            h->unknown_1A0.unknown_4 |= 0x14;
            rc = h->unknown_77C(h);
            if (rc == -1) {
                rc = FUN_007c3750(h);
                if (rc != -1) {
                    h->unknown_150 |= 6;
                    h->unknown_1A0.unknown_4 &= ~0x16;
                } else {
                    h->unknown_1A0.unknown_4 &= ~0x16;
                    rc = h->unknown_1A0.unknown_530;
                }
            } else {
                if (rc == -9 && (h->unknown_150 & 4)) {
                    h->unknown_150 |= 2;
                }
                h->unknown_1A0.unknown_4 &= ~0x16;
            }
        } else {
            rc = -14;
        }
        break;
    }
    if ((h->unknown_150 & 6) == 6 || mode == 3) {
        h->unknown_24 = FUN_007c3960(h);
        if (h->unknown_7BC & 0x40) {
            FUN_007bd2b0(h);
        }
        rc = -2;
    }
    return rc;
}

// FUNCTION: GAMEMD 0x007c30d0
// Seeks playback to frame, reloading from the nearest key frame.
int FUN_007c30d0(MovieHandle_007BD470* h, int frame, int arg)
{
    MovieFrame_007BD470* node = h->unknown_170;
    if (h->unknown_7BC & 0x40) {
        FUN_007bd2b0(h);
    }
    if (frame > h->unknown_11C || h->unknown_764 == 0) {
        return -6;
    }
    int rc;
    h->unknown_710 = -1;
    h->unknown_708 = -1;
    h->unknown_70C = -1;
    FUN_007be660(h);
    char keep = 0;
    if (h->unknown_E8.unknown_20 == 0 && !FUN_007c04e0(h, frame)) {
        rc = FUN_007c0530(h, frame, 1);
        if (rc != -1) {
            goto out;
        }
        if (node->unknown_14 & 4) {
            keep = 1;
        }
    }
    h->unknown_180 = frame;
    char audio;
    char isKey;
    audio = (unsigned char)~h->unknown_E8.unknown_2 >> 3 & 1;
    rc = FUN_007c0740(h, frame, h->unknown_E8.unknown_D, audio, 1, &isKey);
    if (rc != -1) {
        goto out;
    }
    h->unknown_180 = frame;
    h->unknown_170->unknown_14 = 0;
    if (keep) {
        h->unknown_170->unknown_14 |= 4;
    }
    for (node = h->unknown_170->unknown_C; node != h->unknown_170; node = node->unknown_C) {
        node->unknown_14 = 0;
    }
    h->unknown_1A0.unknown_0 = h->unknown_170;
    rc = FUN_007c0490(h);
    if (rc == -1 || rc == -2) {
        rc = frame;
        FUN_007c3910(h, frame * 60 / h->unknown_40.unknown_34);
    }
out:
    return rc;
}

// FUNCTION: GAMEMD 0x007c3270
// Places the image inside the draw buffer and records the blit geometry.
int FUN_007c3270(MovieHandle_007BD470* h, unsigned char* buf, unsigned int w, unsigned int hgt, int x, int y)
{
    int opt = h->unknown_40.unknown_40;
    int align = opt & 0x30;
    if (w == 0) {
        w = h->unknown_E8.unknown_6;
    }
    if (hgt == 0) {
        hgt = h->unknown_E8.unknown_8;
    }
    if (x < 0 && y < 0) {
        if (opt & 8) {
            if (opt & 0x40) {
                h->unknown_1A0.unknown_14 = h->unknown_E8.unknown_12 >> 1;
                h->unknown_1A0.unknown_18 = h->unknown_E8.unknown_14 >> 1;
            } else {
                h->unknown_1A0.unknown_14 = h->unknown_E8.unknown_12;
                h->unknown_1A0.unknown_18 = h->unknown_E8.unknown_14;
            }
        } else if (opt & 0x40) {
            h->unknown_1A0.unknown_14 = (w - (h->unknown_E8.unknown_6 >> 1)) >> 1;
            h->unknown_1A0.unknown_18 = (hgt - (h->unknown_E8.unknown_8 >> 1)) >> 1;
        } else {
            h->unknown_1A0.unknown_14 = (w - h->unknown_E8.unknown_6) >> 1;
            h->unknown_1A0.unknown_18 = (hgt - h->unknown_E8.unknown_8) >> 1;
        }
    } else {
        if (opt & 0x40) {
            x /= 2;
            y /= 2;
        }
        if (align == 0x20) {
            h->unknown_1A0.unknown_14 = w - x;
            h->unknown_1A0.unknown_18 = hgt - y;
        } else if (align == 0x30) {
            h->unknown_1A0.unknown_14 = x;
            h->unknown_1A0.unknown_18 = hgt - y;
        } else {
            h->unknown_1A0.unknown_14 = x;
            h->unknown_1A0.unknown_18 = y;
        }
    }
    int px = h->unknown_1A0.unknown_14;
    if (px < 0) {
        return -24;
    }
    int py = h->unknown_1A0.unknown_18;
    if (py < 0 || (unsigned int)px >= w || (unsigned int)py >= hgt) {
        return -24;
    }
    if (h->unknown_E8.unknown_20 == 1 || h->unknown_E8.unknown_20 == 4) {
        px += px;
        py += py;
    }
    h->unknown_1A0.unknown_C = w;
    h->unknown_1A0.unknown_1C = py * w + px;
    h->unknown_1A0.unknown_10 = hgt;
    if (buf != 0) {
        h->unknown_1A0.unknown_8 = buf;
        h->unknown_8 = buf;
    }
    h->unknown_150 |= 0x10;
    return -1;
}

// FUNCTION: GAMEMD 0x007c3d60
// Unpacks 4x4 blocks of 16-bit pixels from a block table and pointer stream.
void __cdecl FUN_007c3d60(unsigned short* blockTable, unsigned short* pointers,
                          unsigned short* dest, int blocksWide, int blocksHigh, int pitch)
{
    unsigned short* end = dest + blocksHigh * pitch * 4;
    unsigned short* row = dest;
    unsigned short* rowEnd = dest + blocksWide * 4;
    while (dest < end) {
        unsigned short code = *pointers++;
        unsigned short index = code & 0x1fff;
        switch (code & 0xe000) {
        case 0: {
            unsigned short* src = blockTable + index * 16;
            for (int r = 4; r != 0; r--) {
                ((unsigned long*)dest)[0] = ((unsigned long)src[1] << 16) | src[0];
                src += 2;
                ((unsigned long*)dest)[1] = ((unsigned long)src[1] << 16) | src[0];
                src += 2;
                dest += pitch;
            }
            dest += 4 - pitch * 4;
            break;
        }
        case 0x2000: {
            unsigned short* src = blockTable + index * 16;
            for (int r = 4; r != 0; r--) {
                unsigned short* d = dest;
                for (int c = 4; c != 0; c--) {
                    if (*src != 0x8000) {
                        *d = *src;
                    }
                    d++;
                    src++;
                }
                dest += pitch;
            }
            dest += 4 - pitch * 4;
            break;
        }
        case 0x4000:
            dest += 4;
            break;
        }
        if (dest == rowEnd) {
            row += pitch * 4;
            dest = row;
            rowEnd = row + blocksWide * 4;
        }
    }
}

// FUNCTION: GAMEMD 0x007c4260
// Unpacks 4x2 blocks of 16-bit pixels from a block table and pointer stream.
void __cdecl FUN_007c4260(unsigned short* blockTable, unsigned short* pointers,
                          unsigned short* dest, int blocksWide, int blocksHigh, int pitch)
{
    unsigned short* end = dest + blocksHigh * pitch * 2;
    unsigned short* row = dest;
    unsigned short* rowEnd = dest + blocksWide * 4;
    while (dest < end) {
        unsigned short code = *pointers++;
        unsigned short index = code & 0x1fff;
        switch (code & 0xe000) {
        case 0: {
            unsigned short* src = blockTable + index * 8;
            for (int r = 2; r != 0; r--) {
                ((unsigned long*)dest)[0] = ((unsigned long)src[1] << 16) | src[0];
                src += 2;
                ((unsigned long*)dest)[1] = ((unsigned long)src[1] << 16) | src[0];
                src += 2;
                dest += pitch;
            }
            dest += 4 - pitch * 2;
            break;
        }
        case 0x2000: {
            unsigned short* src = blockTable + index * 8;
            for (int r = 2; r != 0; r--) {
                unsigned short* d = dest;
                for (int c = 4; c != 0; c--) {
                    if (*src != 0x8000) {
                        *d = *src;
                    }
                    d++;
                    src++;
                }
                dest += pitch;
            }
            dest += 4 - pitch * 2;
            break;
        }
        case 0x4000:
            dest += 4;
            break;
        }
        if (dest == rowEnd) {
            row += pitch * 2;
            dest = row;
            rowEnd = row + blocksWide * 4;
        }
    }
}
