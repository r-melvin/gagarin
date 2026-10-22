// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x538D40 (no arguments, plain RET):
//   the source palette pointer in the dword at 0xA8F918 read three bytes per
//   colour, the 256x256 byte table at 0xA8F91C filled row by row (row pointer
//   compared with 0xA9F91C), the 500000 (0x7A120) starting distance and the
//   byte at 0xA9F91C cleared on exit.

// GLOBAL: GAMEMD 0xA8F918
extern unsigned char* DAT_00A8F918;
// GLOBAL: GAMEMD 0xA8F91C
extern unsigned char DAT_00A8F91C[256][256];
// GLOBAL: GAMEMD 0xA9F91C
extern unsigned char DAT_00A9F91C;

// FUNCTION: GAMEMD 0x538D40
// For every pair of palette colours, store the index of the palette colour
// nearest (squared RGB distance) to their average.
void __cdecl FUN_00538D40(void)
{
    const unsigned char* src = DAT_00A8F918;
    for (int i = 0; i < 256; i++) {
        int r0 = *src++;
        int g0 = *src++;
        int b0 = *src++;
        const unsigned char* other = DAT_00A8F918;
        for (int j = 0; j < 256; j++) {
            int r = (*other++ + r0) >> 1;
            int g = (*other++ + g0) >> 1;
            int b = (*other++ + b0) >> 1;
            int best = 0;
            int bestdist = 500000;
            const unsigned char* pal = DAT_00A8F918;
            for (int k = 0; k < 256; k++) {
                int dr = *pal++ - r;
                int dg = *pal++ - g;
                int db = *pal++ - b;
                int dist = dr * dr + dg * dg + db * db;
                if (dist < bestdist) {
                    bestdist = dist;
                    best = k;
                }
            }
            DAT_00A8F91C[i][j] = best;
        }
    }
    DAT_00A9F91C = 0;
}
