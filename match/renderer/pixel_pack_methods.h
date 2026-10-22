// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x63DAD0.
//
//   The six pixel-format shift globals at 0x8A0DD0..0x8A0DE4 are the same
//   block already confirmed in match/ui/preview_class_surface_methods.h
//   (read, not edited; re-derived here so this TU stands alone) -- but THIS
//   function reads the three right-shift counts (DD4, DDC, DE4) as single
//   bytes (`MOV CL,byte ptr [...]`) and the three left-shift counts (DD0,
//   DD8, DE0) as dwords (`MOV ECX,dword ptr [...]`). That is a different
//   width split from the other file's typing of DDC as a dword: both
//   functions read the identical four-byte-aligned BSS slot, so only the low
//   byte of any of these ever matters to a shift count, and each TU is typed
//   to reproduce its OWN function's load width, not a shared cross-file
//   struct. Do not "fix" one against the other without re-checking both
//   functions' disassembly.
#ifndef GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H
#define GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H

// GLOBAL: GAMEMD 0x8A0DD0 -- red left-shift (dword load in this function).
extern int DAT_008A0DD0;
// GLOBAL: GAMEMD 0x8A0DD4 -- red right-shift (byte load in this function).
extern unsigned char DAT_008A0DD4;
// GLOBAL: GAMEMD 0x8A0DD8 -- blue left-shift (dword load in this function).
extern int DAT_008A0DD8;
// GLOBAL: GAMEMD 0x8A0DDC -- blue right-shift (byte load in this function).
extern unsigned char DAT_008A0DDC;
// GLOBAL: GAMEMD 0x8A0DE0 -- green left-shift (dword load in this function).
extern int DAT_008A0DE0;
// GLOBAL: GAMEMD 0x8A0DE4 -- green right-shift (byte load in this function).
extern unsigned char DAT_008A0DE4;

// FUNCTION: GAMEMD 0x63DAD0
//
// Pack a raw 8-bit-per-channel {R,G,B} triple into the display's native pixel
// format using the six shift globals, __fastcall with the triple pointer in
// ECX.
unsigned int PackPixel_0063DAD0(const unsigned char* rgb);

#endif  // GG_MATCH_RENDERER_PIXEL_PACK_METHODS_H
