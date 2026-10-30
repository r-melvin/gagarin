// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Name cross-checked
//   against YRpp (reconfirmed from the disassembly).
//
// Also read off the same binary: the constructor 0x750380, ReadAll 0x7510D0 ([Defaults] / [SoundList]),
// DeleteAll 0x7513F0 and GetPositionalVolume 0x750AC0. Every key string, default and callee was read
// off the disassembly; the setters keep their address names. The compiler expands FindIndex in place in
// ReadAll and 0x750FA0 in DeleteAll.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x00750380  VocClass::VocClass
//   FUNCTION: GAMEMD 0x00750AC0  VocClass::GetPositionalVolume
//   FUNCTION: GAMEMD 0x00750FA0  FUN_00750FA0
//   FUNCTION: GAMEMD 0x007510D0  VocClass::ReadAll
//   FUNCTION: GAMEMD 0x007513F0  VocClass::DeleteAll
//   FUNCTION: GAMEMD 0x007514D0  VocClass::FindIndex  (__fastcall, static)

#include <string.h>
#include <stdlib.h>
#include <objidl.h>
#include "voc_class_methods.h"
#include "../platform/ccini_class_methods.h"
#include "../core/small_misc39_methods.h"
#include "../core/vector_class_operations.h"
#include "../_layout/tactical.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"


// Retail _stricmp (0x007C8D20). cdecl; declared (no body) so cl emits a call.
extern "C" int __cdecl gg_voc_stricmp(const char* a, const char* b);

// FUNCTION: GAMEMD 0x4067D0 (decl; reloc) -- priority by name.
bool __fastcall FUN_004067D0(const char* name, int* value);
// FUNCTION: GAMEMD 0x406820 (decl; reloc) -- ORs a control flag in by name.
bool __fastcall FUN_00406820(int* flags, const char* name);
// FUNCTION: GAMEMD 0x406870 (decl; reloc) -- ORs a type flag in by name.
bool __fastcall FUN_00406870(int* flags, const char* name);

// STRING: GAMEMD 0x889F64 -- the shared empty default text.
extern const char STR_00889F64[];
// STRING: GAMEMD 0x846570 -- token separators " \t\n".
extern const char STR_00846570[];
// GLOBAL: GAMEMD 0x8464B0 -- default priority.
extern int DAT_008464B0;
// GLOBAL: GAMEMD 0x8464B4 -- default Volume.
extern float DAT_008464B4;
// GLOBAL: GAMEMD 0x8464B8 -- default MinVolume.
extern float DAT_008464B8;
// GLOBAL: GAMEMD 0x8464BC -- default type flags.
extern int DAT_008464BC;
// GLOBAL: GAMEMD 0x8464C0 -- default Range.
extern int DAT_008464C0;
// GLOBAL: GAMEMD 0x8464C4 -- default Limit.
extern int DAT_008464C4;
// GLOBAL: GAMEMD 0xB1D3B0 -- default control flags.
extern int DAT_00B1D3B0;
// GLOBAL: GAMEMD 0x887324 -- the tactical view.
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0x886FA8 -- view width in pixels.
extern int DAT_00886FA8;
// GLOBAL: GAMEMD 0x886FAC -- view height in pixels.
extern int DAT_00886FAC;
// GLOBAL: GAMEMD 0x7E5168 -- 0.5f.
extern const float DAT_007E5168;
// GLOBAL: GAMEMD 0x7E1748 -- 0.0f.
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E8AE8 -- 0.05 (double), the audibility floor.
extern const double DAT_007E8AE8;
// GLOBAL: GAMEMD 0x7F68E8 -- the pan scale.
extern const float DAT_007F68E8;
// GLOBAL: GAMEMD 0xB1D310 -- the cell no sound is heard from.
extern CellStruct DAT_00B1D310;
// GLOBAL: GAMEMD 0xB1D320 -- anchor of the live positional-voice list.
extern ListNode DAT_00B1D320;
// GLOBAL: GAMEMD 0xB1D3A4 -- pool of free VocVoiceNode blocks.
extern Obj_00407520* DAT_00B1D3A4;
// GLOBAL: GAMEMD 0xB1D3A8 -- live positional-voice count.
extern int DAT_00B1D3A8;
// GLOBAL: GAMEMD 0xB1D3AC -- high-water mark of that count.
extern int DAT_00B1D3AC;

// FUNCTION: GAMEMD 0x750380
// PARTIAL (88.2%): the expanded AddItem schedules its grow-size add differently from retail. A local
// reference to the table reaches 100% but only steers codegen, so the direct form is kept.
VocClass::VocClass(const char* name)
{
    EventType = 0;
    DAT_00B1D378.AddItem(this);
    EventType = AudioEventType::FUN_004063B0(name);
}

// The cell a coordinate lies in: signed /256 per axis (CellClass::Coord2Cell in YRpp; inline, no retail body).
static inline CellStruct Coord2Cell(const CoordStruct* coords)
{
    CellStruct c;
    c.X = (short)(coords->X / 256);
    c.Y = (short)(coords->Y / 256);
    return c;
}

// FUNCTION: GAMEMD 0x750AC0
// PARTIAL (99.0%, 195/196): identical instruction multiset. The last expression is retail's
// `FLD pan; FMUL scale; FDIV width; FADD scale`; cl loads the scale first (`FLD scale; FMUL pan`).
// Variants tried: either operand order, a named product, a named scale, a ternary clamp (all 99.0%
// or lower).
// How loud `type` sounds from `coords` (0 when inaudible) and, in *pan, where it sits across the view:
// the distance from the view centre against the descriptor's range (60 leptons per range step), the
// descriptor's MinVolume as a floor, and a pan scaled from the horizontal offset. Descriptors flagged
// 0x800 are silent unless the cell they are in is visible (cell flags 0x18).
float VocClass::GetPositionalVolume(CoordStruct* coords, int* pan, AudioEventType* type)
{
    *pan = 0;
    float volume = 0.0f;
    float halfWidth = (float)DAT_00886FA8 * DAT_007E5168;
    float halfHeight = (float)DAT_00886FAC * DAT_007E5168;
    float width = halfWidth + halfWidth;
    float range = (float)(type->FUN_00405130() * 60);
    unsigned int flags = type->FUN_00405160();
    if (flags & 0x800) {
        CellStruct cell = Coord2Cell(coords);
        if (cell.X == DAT_00B1D310.X && cell.Y == DAT_00B1D310.Y)
            return DAT_007E1748;
        if ((DAT_0087F7E8.FUN_005657A0(&cell)->AltFlags & 0x18) == 0)
            return DAT_007E1748;
    }
    Point2D point;
    DAT_00887324->FUN_006D2140(coords, &point);
    float offset = (float)point.X - halfWidth;
    float dx = (float)abs((int)offset);
    float dy = (float)abs((int)((float)point.Y - halfHeight));
    if ((flags & 0x40) == 0) {
        dx = dx - halfWidth;
        dy = dy - halfHeight;
        if (dx < DAT_007E1748)
            dx = 0.0f;
        if (dy < DAT_007E1748)
            dy = DAT_007E1748;
    }
    dy = dy + dy;
    if (dx < range && dy < range && range > DAT_007E1748) {
        float worst = dx > dy ? dx : dy;
        volume = (range - worst) / range;
    }
    if (flags & 0x10) {
        if (type->FUN_00405140() > volume)
            volume = type->FUN_00405140();
    }
    if (volume < DAT_007E8AE8)
        return DAT_007E1748;
    if (offset < -width)
        offset = -width;
    else if (offset > width)
        offset = width;
    *pan = (int)(offset * DAT_007F68E8 / width + DAT_007F68E8);
    return volume;
}

// FUNCTION: GAMEMD 0x750FA0
// Tear down every live positional voice: stop its controller, unlink it, give it back to the pool and
// drop the live count.
void FUN_00750FA0()
{
    VocVoiceNode* node = static_cast<VocVoiceNode*>(DAT_00B1D320.FUN_004073C0());
    while (node != 0) {
        VocVoiceNode* next = node->FUN_004073E0();
        node->Handle.Stop();
        node->FUN_00407450();
        DAT_00B1D3A4->FUN_00407530(node);
        DAT_00B1D3A8--;
        node = next;
    }
}

// FUNCTION: GAMEMD 0x7510D0
// PARTIAL (99.1%): the residual is the constructor's expanded AddItem (see 0x750380).
void VocClass::ReadAll(CCINIClass* ini)
{
    char buffer[0x800];
    char name[0x20];
    char* token;

    DAT_00B1D320.FUN_004072C0();
    DAT_00B1D3A4 = (Obj_00407520*)FUN_004074D0(200, 0x3C);
    DAT_00B1D3A8 = 0;
    DAT_00B1D3AC = 0;

    if (ini->INIClass::Exists("Defaults", 0)) {
        DAT_008464B4 = (float)ini->ReadDouble("Defaults", "Volume", DAT_008464B4);
        DAT_008464B8 = (float)ini->ReadDouble("Defaults", "MinVolume", DAT_008464B8);
        ini->ReadString("Defaults", "Priority", "NORMAL", buffer, 0x800);
        FUN_004067D0(buffer, &DAT_008464B0);
        ini->ReadString("Defaults", "Control", STR_00889F64, buffer, 0x800);
        token = strtok(buffer, STR_00846570);
        if (token) {
            DAT_00B1D3B0 = 0;
            do {
                FUN_00406820(&DAT_00B1D3B0, token);
                token = strtok(0, STR_00846570);
            } while (token);
        }
        ini->ReadString("Defaults", "Type", STR_00889F64, buffer, 0x800);
        token = strtok(buffer, STR_00846570);
        if (token) {
            DAT_008464BC = 0x20;
            do {
                FUN_00406870(&DAT_008464BC, token);
                token = strtok(0, STR_00846570);
            } while (token);
        }
        DAT_008464C4 = ini->ReadInteger("Defaults", "Limit", DAT_008464C4);
        DAT_008464C0 = ini->ReadInteger("Defaults", "Range", DAT_008464C0);
    }

    if (ini->INIClass::Exists("SoundList", 0)) {
        int count = ini->GetKeyCount("SoundList");
        for (int i = 0; i < count; ++i) {
            if (ini->ReadString("SoundList", ini->GetKeyName("SoundList", i), STR_00889F64, name, 0x20)) {
                int index = FindIndex(name);
                VocClass* voc;
                if (index == -1)
                    voc = new VocClass(name);
                else
                    voc = DAT_00B1D378.Items[index];
                voc->ReadINI(ini);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7513F0
// Delete every entry, then stop and release every live positional voice (0x750FA0, expanded in place
// by the compiler) and free the voice pool.
void VocClass::DeleteAll()
{
    while (DAT_00B1D378.Count > 0)
        delete DAT_00B1D378.Items[0];

    if (DAT_00B1D3A4 != 0) {
        FUN_00750FA0();
        DAT_00B1D3A4->FUN_00407510();
        DAT_00B1D3A4 = 0;
    }
}

// FUNCTION: GAMEMD 0x007514D0  (__fastcall, static)
// Return the index of the Array entry whose audio-event name matches pName
// (case-insensitive), or -1 when pName is null / no entry matches.
int VocClass::FindIndex(const char* pName)
{
    if (pName)
    {
        for (int i = 0; i < Array.Count; ++i)
        {
            // Reference item->EventType twice (the null test and the call) so cl
            // keeps `item` anchored in EAX and CSE-loads Event once into ECX,
            // matching retail's `mov eax,[eax+esi*4]; mov ecx,[eax]` pairing
            // (verified byte-for-byte; a single anchored event-pointer load).
            VocClass* item = ((VocClass**)Array.Items)[i];
            const char* name = item->EventType ? item->EventType->FUN_00405170() : "Invalid Voc";
            if (gg_voc_stricmp(pName, name) == 0)
                return i;
        }
    }
    return -1;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D378
DynamicVectorClassLayout VocClass::Array;
// END defined globals
