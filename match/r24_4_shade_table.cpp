// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x758670 disassembled from its entry point in the user's gamemd.exe v1.001; the normal
//   tables at 0x8469E0 / 0x8469F4 read with the local Ghidra CLI.
//   Address index: 0x758670.

// GLOBAL: GAMEMD 0x8469E0
struct Normal_r24 { float x, y, z; };
extern const Normal_r24* const DAT_008469E0[5];
// GLOBAL: GAMEMD 0x8469F4
extern const int DAT_008469F4[5];
// GLOBAL: GAMEMD 0xB45990
extern unsigned char DAT_00B45990[256];
// GLOBAL: GAMEMD 0xB45A8D
extern unsigned char DAT_00B45A8D;
// GLOBAL: GAMEMD 0xB45A8E
extern unsigned char DAT_00B45A8E;
// GLOBAL: GAMEMD 0xB45A8F
extern unsigned char DAT_00B45A8F;

// FUNCTION: GAMEMD 0x758670
// PARTIAL: 95.2%. Retail loads light.y before the normal's y component in the last product; every operand order tried loads the normal first.
// Builds the shade table for a light direction: each normal of the chosen set is dotted with
// the direction, negative results shade to 0 and the rest scale by 16. The last three table
// bytes are set to the default shade 0x10.
void __fastcall FUN_00758670(const Normal_r24& light, int set)
{
    const Normal_r24* normals = DAT_008469E0[set];
    int count = DAT_008469F4[set];
    for (int i = 0; i < count; ++i) {
        float dot = normals[i].x * light.x + normals[i].z * light.z + light.y * normals[i].y;
        if (dot < 0.0) {
            DAT_00B45990[i] = 0;
        } else {
            DAT_00B45990[i] = (unsigned char)(int)(dot * 16.0f);
        }
    }
    DAT_00B45A8F = 0x10;
    DAT_00B45A8E = 0x10;
    DAT_00B45A8D = 0x10;
}
