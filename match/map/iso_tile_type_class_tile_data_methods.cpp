// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RE-findings-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm 0x544CB0
//   len 0x26, 0x5471B0 len 0x31, 0x5471F0 len 0x36).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x544CB0  IsometricTileTypeClass::GetTileData    (__thiscall)
//   FUNCTION: GAMEMD 0x5471B0  IsometricTileTypeClass::GetMorphType   (__fastcall member)
//   FUNCTION: GAMEMD 0x5471F0  IsometricTileTypeClass::GetConnectFlag (__fastcall member)
//
// The terrain draw asks a tile type for two per-sub-tile properties: the
// morph/slope byte that picks a ramp variant, and the connect flag that picks
// a LAT transition variant. Both go through the same lazily-loaded tile-set
// header, which is why the accessor for it is the vtable slot both dispatch.

#include "iso_tile_type_class_tile_data_methods.h"

// FUNCTION: GAMEMD 0x544CB0  (__thiscall)
// The loaded tile-set header, loading it on first use. Retail reads the member
// once up front and again only inside the loading arm, so the source keeps the
// first read in a local and refreshes it after the load rather than re-reading
// the member on the way out.
TileImageHeader* IsometricTileTypeClass::GetTileData()
{
    TileImageHeader* data = this->TileData;

    if (data == 0 && this->TileDataLoadable) {
        this->LoadTileData();
        data = this->TileData;
    }
    return data;
}

// FUNCTION: GAMEMD 0x5471B0  (__thiscall)
// Convention read off the binary, not assumed: the argument arrives as
// `MOV EAX,[ESP+0x8]` and the exit is `RET 4`, which is a stack-passed
// argument and a callee-cleaned frame — a plain __thiscall member. Spelled
// __fastcall (the argument in EDX) the body scores 4.3%.
// The morph/slope byte of one sub-tile. The index wraps on the sub-tile count,
// which is the header's two dimensions multiplied.
//
// The exit is `MOVSX EAX, byte ptr [ECX+0x2a]`, so the stored byte is signed
// and the return is int.
int IsometricTileTypeClass::GetMorphType(int idx)
{
    TileImageHeader* data = (this->*this->Vfptr->At_9C)();

    if (data != 0) {
        SubTileImage* tile = data->SubTiles[idx % (data->Height * data->Width)];
        if (tile != 0) {
            return tile->MorphType;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5471F0  (__thiscall)
// Bit 2 of the sub-tile's flag word: the connect/ramp flag the LAT draw uses to
// pick a transition variant.
//
// The out-of-range fall-back is not `return subtile / cellCount;`: both
// failure paths in the binary jump to 0x00547221, which is `XOR AL,AL; RET 4`.
// A quotient there would be a Ghidra artefact — EAX happens to hold the IDIV quotient at that label, so the
// decompiler attributed it as the returned value. The zeroing of AL alone (not
// EAX) is also what fixes the return width here as bool, against the int of
// its sibling at 0x5471B0.
bool IsometricTileTypeClass::GetConnectFlag(int idx)
{
    TileImageHeader* data = (this->*this->Vfptr->At_9C)();

    if (data != 0) {
        SubTileImage* tile = data->SubTiles[idx % (data->Height * data->Width)];
        if (tile != 0) {
            return tile->ConnectFlag;
        }
    }
    return false;
}
