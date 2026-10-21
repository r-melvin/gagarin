// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | YRpp-cross-check |
//             private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5FE470/0x5FE530/
//   0x5FE570. See the header for the RTTI derivation of the class identity.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5FE470  OverlayTypeClass::FindIndex        (__fastcall)
//   FUNCTION: GAMEMD 0x5FE530  OverlayTypeClass::SpawnAtMapCoords (__thiscall)
//   FUNCTION: GAMEMD 0x5FE570  OverlayTypeClass::CreateObject     (__thiscall)
//   FUNCTION: GAMEMD 0x5FE620  OverlayTypeClass::LoadArt          (__fastcall)
//   FUNCTION: GAMEMD 0x5FC380  OverlayClass::OverlayClass (referenced; reloc)
//   GLOBAL:   GAMEMD 0xA83D80  OverlayTypeClass::Array
//   FUNCTION: GAMEMD 0x5B40B0  image loader          (referenced; reloc)
//   FUNCTION: GAMEMD 0x5F96B0  theater-letter stamp  (referenced; reloc)
//   FUNCTION: GAMEMD 0x5F9710  theater-letter reset  (referenced; reloc)
//   FUNCTION: GAMEMD 0x7C9FF0  CRT _makepath         (referenced; reloc)
//   LIBRARY:  GAMEMD 0x7C8B3D  game-heap free        (referenced; reloc)
//   GLOBAL:   GAMEMD 0xAC1608  default CellStruct for CreateObject
//   GLOBAL:   GAMEMD 0x7E1B78  the theater table
//   GLOBAL:   GAMEMD 0xA83D84  OverlayTypeClass::Array.Items
//   GLOBAL:   GAMEMD 0xA83D90  OverlayTypeClass::Array.Count
//   STRING:   GAMEMD 0x81834C  ".SHP"

#include "overlay_type_class_methods.h"

// FUNCTION: GAMEMD 0x5FE470  OverlayTypeClass::FindIndex (__fastcall)
// Index of the overlay type whose INI ID matches `pID` case-insensitively, or
// -1 when `pID` is null or nothing matches.
//
// Two details come from the bytes rather than from what the code ought to do:
// the count is re-loaded from the global at the top of every iteration (so it
// is read through the array object, not hoisted into a local), and the
// candidate's ID is the *first* _stricmp argument while the array walk in the
// sibling VocClass::FindIndex passes the needle first.
int __fastcall OverlayTypeClass::FindIndex(const char* pID)
{
    if (pID)
    {
        for (int i = 0; i < OverlayTypeClass_Array.Count; ++i)
        {
            // The element must be subscripted inside the call rather than bound
            // to a named pointer first: naming it costs the ECX/EAX colouring of
            // the element load and holds at 90%. This is the mirror of the
            // named-element-pointer lever banked for search loops — here the
            // element feeds a call argument, not a comparison.
            if (gg_overlay_stricmp(
                    ((OverlayTypeClass**)OverlayTypeClass_Array.Items)[i]->ID,
                    pID) == 0)
                return i;
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x5FE620  OverlayTypeClass::LoadArt (__fastcall)
//
// Bring every overlay type's artwork into line with the theater being entered.
// A theater-specific type takes the theater's own file extension; a new-theater
// type keeps the .SHP extension and has the theater letter stamped into the
// second character of its name, falling back to the generic 'G' art when the
// theater-specific file is missing. Types whose art is supplied elsewhere are
// skipped on the way in and have their owned image released on the way out.
void __fastcall OverlayTypeClass::LoadArt(int idxTheater)
{
    char path[0x200];

    for (int i = 0; i < DAT_00A83D90; ++i)
    {
        OverlayTypeClass* type = DAT_00A83D84[i];

        if (type->unknown_2AF == 0)
        {
            if (type->Theater != 0)
            {
                _makepath(path, 0, 0, type->ImageFile,
                          DAT_007E1B78[idxTheater].Extension);

                // Each arm's first load is bound to its own named local. With
                // the null test re-reading `type->Image` instead, cl recognises
                // the two load-and-retry blocks as identical and cross-jumps
                // the second into the first, which retail's build did not do.
                Image_005FE620* image = FUN_005B40B0(path, 1);
                type->Image = image;
                if (image == 0)
                {
                    FUN_005F9710(path);
                    type->Image = FUN_005B40B0(path, 1);
                }
            }
            else if (type->NewTheater != 0)
            {
                _makepath(path, 0, 0, type->ImageFile, STR_0081834C);
                FUN_005F96B0(path, idxTheater);

                Image_005FE620* themedImage = FUN_005B40B0(path, 1);
                type->Image = themedImage;
                if (themedImage == 0)
                {
                    FUN_005F9710(path);
                    type->Image = FUN_005B40B0(path, 1);
                }
            }
        }
        else if ((type->Theater != 0 || type->NewTheater != 0)
                 && type->Image != 0 && type->ImageAllocated != 0)
        {
            operator delete(type->Image);
            type->Image = 0;
            type->ImageAllocated = 0;
        }
    }
}
