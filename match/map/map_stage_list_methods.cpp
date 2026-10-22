// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 across
//   0x5CEE60..0x5CF8D6. See the header for how the container's identity and
//   layout were read out of the image's runtime type information.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5CEDD0  MapStageList::Construct
//   FUNCTION: GAMEMD 0x5CEE60  MapStageList::~MapStageList
//   FUNCTION: GAMEMD 0x5CF5F0  MapStageList::ClearAll
//   FUNCTION: GAMEMD 0x5CF6B0  MapStageList::FindByName
//   FUNCTION: GAMEMD 0x5CF760  MapStageList::FindByTitle
//   FUNCTION: GAMEMD 0x5CF810  MapStageList::GetAt
//   FUNCTION: GAMEMD 0x5CF830  MapStageList::AddStage
//   FUNCTION: GAMEMD 0x5CF840  MapStageList::FindTitle
//   VTABLE:   GAMEMD 0x7EEAB4  VectorClass<MapStage*>
//   VTABLE:   GAMEMD 0x7EEAD4  VectorClass<MSAnimEntry*>  (+0x2C)
//   VTABLE:   GAMEMD 0x7EEAF4  VectorClass<MSSfxEntry*>   (+0x44)
//   GLOBAL:   GAMEMD 0x87E728  the campaign session pointer
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete (CRT; excluded from the match)

#include "map_stage_list_methods.h"

// FUNCTION: GAMEMD 0x5CEDD0
// Build an empty container. The three vectors and the name string are built
// in declaration order, and then the body empties the two the constructor
// bothers to empty -- retail leaves the third alone, which is the direct
// evidence that the body is three statements and not a call to ClearAll.
MapStageList* MapStageList::Construct()
{
    Stages.Init();
    Name.Text.Init();
    Strings.Init();
    Titles.Init();

    Stages.Clear();
    Name.Text.Reset();
    Strings.Clear();
    return this;
}

// FUNCTION: GAMEMD 0x5CEE60
// Tear the container down: empty it first, then let the three vectors and the
// name string go in reverse declaration order, which is the order retail's
// stores walk back through (+0x44, +0x2C, +0x28, +0x00).
MapStageList::~MapStageList() throw()
{
    ClearAll();
}

// FUNCTION: GAMEMD 0x5CF5F0
// Empty every list the container owns and put the drawing bounds back to the
// full 640x400 screen. Each of the three sweeps frees its elements one by one
// and then asks the vector itself to drop its block, and each walks a signed
// index against the live count reloaded every turn -- retail's `JL` on a
// reloaded `Count` is a plain indexed `for`, not a pointer walk.
void MapStageList::ClearAll()
{
    int i;

    for (i = 0; i < Titles.Count; ++i) {
        StringClass* title = Titles.Vector[i];

        if (title != 0) {
            title->Destruct();
            ::operator delete(title);
        }
    }

    Titles.Clear();

    BoundsX = 0;
    BoundsY = 0;
    BoundsW = 640;
    BoundsH = 400;

    for (i = 0; i < Strings.Count; ++i) {
        StringClass* text = Strings.Vector[i];

        if (text != 0) {
            text->Destruct();
            ::operator delete(text);
        }
    }

    Strings.Clear();

    for (i = 0; i < Stages.Count; ++i) {
        MapStage* stage = Stages.Vector[i];

        if (stage != 0) {
            stage->Destruct();
            ::operator delete(stage);
        }
    }

    Stages.Clear();
}

// FUNCTION: GAMEMD 0x5CF6B0
// Find the stage whose name matches, case-insensitively. Both sides are
// lower-cased into temporaries inside the loop, so the key is rebuilt on every
// turn exactly as retail does it; the two temporaries are released on both the
// hit and the miss path.
MapStage* MapStageList::FindByName(StringClass* key)
{
    if (key->At(0) != 0) {
        for (int i = 0; i < Stages.Count; ++i) {
            StringClass wanted;
            wanted.CopyFrom(key);
            wanted.MakeLower();

            StringClass candidate;
            candidate.CopyFrom(&Stages.Vector[i]->Name);
            candidate.MakeLower();

            if (wanted.Equals(&candidate)) {
                MapStage* hit = Stages.Vector[i];
                candidate.Destruct();
                wanted.Destruct();
                return hit;
            }

            candidate.Destruct();
            wanted.Destruct();
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x5CF760
// The same search against each stage's title rather than its name. The only
// difference in retail is the `ADD ECX,4` that steps to the second string.
MapStage* MapStageList::FindByTitle(StringClass* key)
{
    if (key->At(0) != 0) {
        for (int i = 0; i < Stages.Count; ++i) {
            StringClass wanted;
            wanted.CopyFrom(key);
            wanted.MakeLower();

            StringClass candidate;
            candidate.CopyFrom(&Stages.Vector[i]->Title);
            candidate.MakeLower();

            if (wanted.Equals(&candidate)) {
                MapStage* hit = Stages.Vector[i];
                candidate.Destruct();
                wanted.Destruct();
                return hit;
            }

            candidate.Destruct();
            wanted.Destruct();
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x5CF810
// The bounds-checked subscript. The index is a 16-bit quantity -- retail's
// `AND EAX,0xFFFF` is the parameter's own width, not a mask the source wrote --
// and the bound is the signed live count.
MapStage* MapStageList::GetAt(unsigned short index)
{
    if (Stages.Count <= index) {
        return 0;
    }

    return Stages.Vector[index];
}

// FUNCTION: GAMEMD 0x5CF830
// Append through the vector's own virtual Add, which takes its argument by
// reference; the whole body is the address of the parameter and the indirect
// call.
int MapStageList::AddStage(MapStage* stage)
{
    return Stages.Add(stage);
}

// FUNCTION: GAMEMD 0x5CF840
// Find a title line by text, but only once a campaign session exists. Unlike
// the two stage searches this one lower-cases the stored line first and the
// caller's key second, which is the order retail's two constructor calls run
// in.
StringClass* MapStageList::FindTitle(StringClass* key)
{
    if (SessionExists()) {
        int i;

    for (i = 0; i < Titles.Count; ++i) {
            StringClass* line = Titles.Vector[i];

            StringClass stored;
            stored.CopyFrom(line);
            stored.MakeLower();

            StringClass wanted;
            wanted.CopyFrom(key);
            wanted.MakeLower();

            if (stored.Equals(&wanted)) {
                wanted.Destruct();
                stored.Destruct();
                return line;
            }

            wanted.Destruct();
            stored.Destruct();
        }
    }

    return 0;
}
