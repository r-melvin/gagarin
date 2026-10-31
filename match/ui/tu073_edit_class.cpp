// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU073 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x4c1b80-0x4c359f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail PAVEBolt RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: EditClass vtable bodies at 0x4C30E0..0x4C3570 (shared by DropListClass's vtable).
//
//   cross-checked against an outside reference.
//
// File-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs: each stub restores the VectorClass<T> vtable,
// frees the array when it is owned, and clears the flag and capacity. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored by the
// matching initialiser. The initialisers (the __xc table entries, which also
// register these stubs with atexit) are left to the translation-unit migration;
// they compile here as a by-product and are not claimed. The globals' retail
// addresses are bound for verification through the per-TU symbol map.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "../core/vector_class_operations.h"

class EBolt;

// VTABLE: GAMEMD 0x7E86AC -- VectorClass<EBolt*>.
template class VectorClass<EBolt*>;
typedef VectorClass<EBolt*> GgEboltVectorClass;
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E868C -- DynamicVectorClass<EBolt*>.
template class DynamicVectorClass<EBolt*>;
typedef DynamicVectorClass<EBolt*> GgEboltDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(EBolt*) == 4);

#include "input_controls/lists_views.h"

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004C1E50;
struct Obj_004C1E50_20;
struct Obj_004C2C30;

struct Obj_004C1E50
{
    char unknown_00[0x20];
    Obj_004C1E50_20* unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x4C1E50
    void FUN_004C1E50();
};
GG_STATIC_ASSERT(offsetof(Obj_004C1E50, unknown_20) == 0x20);

struct Obj_004C1E50_20
{
    char unknown_00[0x6DC];
    int unknown_6DC;   // +0x06DC
};
GG_STATIC_ASSERT(offsetof(Obj_004C1E50_20, unknown_6DC) == 0x6DC);

struct Obj_004C2C30
{
    // FUNCTION: GAMEMD 0x4C2C30
    Obj_004C2C30* FUN_004C2C30();
};


#include "../core/vector_class_operations.h"

class AITriggerTypeClass;
class AbstractClass;
class AbstractTypeClass;
class AircraftClass;
class AircraftTypeClass;
class AirstrikeClass;
class AlphaShapeClass;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingLightClass;
class BuildingTypeClass;
class BulletClass;
class BulletTypeClass;
class CampaignClass;
class CaptureManagerClass;
class ColorScheme;
class CommandClass;
class DiskLaserClass;
class EBolt;
class EgoClass;
class FactoryClass;
class FootClass;
class HouseClass;
class HouseTypeClass;
class InfantryClass;
class InfantryTypeClass;
class IsometricTileClass;
class IsometricTileTypeClass;
class LightConvertClass;
class LightSourceClass;
class LineTrail;
class MixFileClass;
class MovieHandle;
class ObjectClass;
class OverlayClass;
class OverlayTypeClass;
class ParasiteClass;
class ParticleClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
class RadBeam;
class RadSiteClass;
class ScriptClass;
class ScriptTypeClass;
class SideClass;
class SlaveManagerClass;
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass;
class SpotLightClass;
class SuperClass;
class SuperWeaponTypeClass;
class TActionClass;
class TEventClass;
class TagClass;
class TaskForceClass;
class TeamClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TemporalClass;
class TerrainClass;
class TerrainTypeClass;
class TiberiumClass;
class TriggerClass;
class TriggerTypeClass;
class TubeClass;
class UnitClass;
class UnitTypeClass;
class VocClass;
class VoxClass;
class VoxelAnimClass;
class VoxelAnimTypeClass;
class WarheadTypeClass;
class WaveClass;
class WaypointPathClass;
class WeaponTypeClass;
struct HWND__;


// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E8678
extern const double DAT_007E8678;
// GLOBAL: GAMEMD 0x8A0E38
extern double DAT_008A0E38;

// SYNTHETIC: GAMEMD 0x4C1BB0
// GLOBAL: GAMEMD 0x8A0EA8
double DAT_008A0EA8 = DAT_008A0E38 / DAT_007E8678;

// SYNTHETIC: GAMEMD 0x4C1BD0
// GLOBAL: GAMEMD 0x8A0E70
double DAT_008A0E70 = DAT_007E1718 / DAT_008A0EA8;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C1E50
// Branching.
void Obj_004C1E50::FUN_004C1E50()
{
    if (unknown_20 != 0)
    {
        unknown_20->unknown_6DC = 0;
        unknown_20 = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C2C30
// Returns its receiver.
Obj_004C2C30* Obj_004C2C30::FUN_004C2C30()
{
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C2C40
// DynamicVectorClass<EBolt*>::Clear

// FUNCTION: GAMEMD 0x4C2C70
// DynamicVectorClass<EBolt*>::Slot5

// FUNCTION: GAMEMD 0x4C2C90
// VectorClass<EBolt*>::Slot6

// FUNCTION: GAMEMD 0x4C2CA0
// VectorClass<EBolt*>::operator==

// FUNCTION: GAMEMD 0x4C2CE0
// VectorClass<EBolt*>::SetCapacity

// FUNCTION: GAMEMD 0x4C2D90
// VectorClass<EBolt*>::Clear

// FUNCTION: GAMEMD 0x4C2DC0
// VectorClass<EBolt*>::FindItemIndex

// FUNCTION: GAMEMD 0x4C2E00
// VectorClass<EBolt*>::Slot5

// FUNCTION: GAMEMD 0x4C2E20
// DynamicVectorClass<EBolt*>::SetCapacity

// FUNCTION: GAMEMD 0x4C2ED0
// DynamicVectorClass<EBolt*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4C2F00
// VectorClass<EBolt*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4C2F50
// DynamicVectorClass<EBolt*>::scalar deleting destructor

// STRING: GAMEMD 0x820768 -- L"X", the width probe for an empty box
// FUNCTION: GAMEMD 0x4C2FC0
// Sets up the text box: the text buffer and its limit, the colour scheme, and a width/height taken
// from the font when the caller passes -1.
EditClass::EditClass(int id, wchar_t* text, int size, unsigned textFlags, int x, int y, int w, int h,
                     unsigned flags)
    : ControlClass(id, x, y, w, h, 1, 0)
{
    TextFlags = textFlags & ~0x100u;
    unknown_30 = flags;
    SetText(text, size);
    SchemeIndex = GadgetClass::GetColorScheme();
    if (w == -1 || h == -1) {
        Font* font = FUN_004A60D0(textFlags);
        if (h == -1) {
            Height = font->Height + 1;
        }
        if (w == -1) {
            if (wcslen(Text) > 0) {
                int textWidth = font->TextWidth(Text, 0);
                IsReadOnly = 0;
                Width = textWidth + 6;
                return;
            }
            Width = font->TextWidth(L"X", 0) * (MaxLength + 1) + 2;
        }
    }
    IsReadOnly = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C30B0
EditClass::~EditClass()
{
    if (GadgetClass::IsFocused()) {
        GadgetClass::KillFocus();
    }
}

// FUNCTION: GAMEMD 0x4C30E0
// EditClass::SetText slot (+0x88): edits `text` in place, at most size-1 characters, and redraws.
void EditClass::SetText(wchar_t* text, int size)
{
    Text = text;
    MaxLength = size - 1;
    Length = wcslen(text);
    MarkRedraw();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C3110
// EditClass::Draw slot (+0x6C): when the base draws, hides the mouse over the box and paints the frame and text.
int EditClass::Draw(int forced)
{
    if (ControlClass::Draw(forced)) {
        DAT_00887640->HideRegion(Rect(X, Y, Width, Height));
        vf_36();
        DrawText(Text);
        DAT_00887640->ShowRegion();
        return 1;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C3190
// CAPPED at 2.9% after three attempts (early return then body; inverted if(!IsReadOnly){body}; flags=0 local before the
// Escape-path base call). Remaining delta: the body is the same instruction multiset except for four instructions,
// but retail pushes esi first and then ebx and edi after the read-only test (order esi, ebx, edi, each return
// path popping only what it pushed), and pushes the zero arguments of the Escape-path base call through ebx;
// this build pushes ebx, esi, edi in its prologue and pushes immediates, which shifts every later offset.
// EditClass::Action slot (+0x7C): clicking takes the focus; while focused, Escape drops it and printable keys are
// fed to vf_38 (and swallowed when accepted).
int EditClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (IsReadOnly) {
        return 0;
    }
    if (flags & 1) {
        flags &= ~1u;
        SetFocus();
        MarkRedraw();
    }
    if ((flags & 0x100) && IsFocused()) {
        if (*key == 0x1B) {
            KillFocus();
            return ControlClass::Action(0, key, 0);
        }
        int ascii = DAT_0087F770->FUN_0054F450(*key) & 0xFF;
        if ((*key & 0x1000) && ascii >= '0' && ascii <= '9') {
            *key &= ~0x1000u;
            if (!(flags & 0x44) && vf_38(ascii)) {
                flags &= ~0x100u;
                *key = 0;
            }
        } else if ((!(*key & 0x1000) && ascii >= 0x20 && ascii < 0x100) || *key == 0xD || *key == 8) {
            if (!(flags & 0x44) && vf_38(DAT_0087F770->FUN_0054F450(*key))) {
                flags &= ~0x100u;
                *key = 0;
            }
        }
    }
    return ControlClass::Action(flags, key, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C32A0
// EditClass::vf_36 slot (+0x90): the sunken frame around the box.
void EditClass::vf_36()
{
    FUN_004A5A50(&Rect(X, Y, Width, Height), 4, 1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C32E0
// EditClass::DrawText slot (+0x94): draws `text` inside the frame and, while focused with room left, the cursor.
void EditClass::DrawText(wchar_t const* text)
{
    unsigned focusFlag = IsFocused() ? 0x2000 : 0;
    FUN_004A6500(text, DAT_00887314, &DAT_00887314->GetRect(), &Point2D(X + 1, Y + 1),
                 DAT_00B054D0[SchemeIndex], 0, TextFlags | focusFlag, Width - 2, 0);
    Font* font = FUN_004A60D0(TextFlags);
    if (IsFocused()) {
        if (wcslen(text) < MaxLength) {
            if (font->TextWidth(text, 0) + font->TextWidth(DAT_0082076C, 0) < Width - 2) {
                FUN_004A6500(DAT_0082076C, DAT_00887314, &DAT_00887314->GetRect(),
                             &Point2D(font->TextWidth(text, 0) + X + 1, Y + 1), DAT_00B054D0[SchemeIndex], 0,
                             TextFlags | focusFlag, -1, 0);
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C3420
// EditClass::vf_38 slot (+0x98): applies one typed character to the text (Backspace, Enter, or a character
// accepted by the unknown_30 filters). Returns false only when Enter ended the edit.
bool EditClass::vf_38(int ch)
{
    Font* font = FUN_004A60D0(TextFlags);
    switch (ch) {
    case 0:
        return true;
    case 8:
        if (Length) {
            Length--;
            Text[Length] = 0;
            MarkRedraw();
        }
        return true;
    case 0xD:
        KillFocus();
        return false;
    }
    if (font->TextWidth(Text, 0) + font->CharWidth(ch) >= Width - 2) {
        return true;
    }
    if (Length >= MaxLength) {
        return true;
    }
    if ((!isgraph(ch) && ch != 0x20) || (ch == 0x20 && !Length)) {
        return true;
    }
    if ((unknown_30 & 8) && isalpha(ch)) {
        ch = toupper(ch);
    }
    if (!((unknown_30 & 2) && isdigit(ch))) {
        if (!((unknown_30 & 1) && isalpha(ch))) {
            if ((!(unknown_30 & 4) || isalnum(ch)) && ch != 0x20) {
                return true;
            }
        }
    }
    Text[Length] = (wchar_t)ch;
    Length++;
    Text[Length] = 0;
    MarkRedraw();
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4C3570
// EditClass::SetFocus slot (+0x50): re-measures the text, then takes the focus.
void EditClass::SetFocus()
{
    Length = 0;
    if (Text) {
        Length = wcslen(Text);
    }
    GadgetClass::SetFocus();
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E8678
extern const double DAT_007E8678 = 60.0;
// END defined globals
