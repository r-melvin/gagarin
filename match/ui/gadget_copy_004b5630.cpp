// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 entry instruction reads and field copy sequences).
#include "gadget_copy_004b5630.h"

// FUNCTION: GAMEMD 0x004B5630
GadgetCopyWideView_004B5630* GadgetCopyWideView_004B5630::FUN_004B5630(GadgetCopyWideView_004B5630* source)
{
    FUN_00556600((GadgetCopyBaseView_004B5600*)source);
    X = source->X; Y = source->Y; Width = source->Width; Height = source->Height;
    RedrawPending = source->RedrawPending; IsSticky = source->IsSticky; IsDisabled = source->IsDisabled;
    Flags = source->Flags;
    unknown_24 = source->unknown_24; unknown_28 = source->unknown_28;
    unknown_2C = source->unknown_2C; unknown_2D = source->unknown_2D;
    unknown_30 = source->unknown_30; unknown_34 = source->unknown_34;
    unknown_38 = source->unknown_38; unknown_3C = source->unknown_3C;
    unknown_40 = source->unknown_40; unknown_44 = source->unknown_44;
    unknown_48 = source->unknown_48; unknown_4C = source->unknown_4C;
    unknown_50 = source->unknown_50; unknown_54 = source->unknown_54;
    unknown_55 = source->unknown_55; unknown_58 = source->unknown_58; unknown_5C = source->unknown_5C;
    return this;
}


// FUNCTION: GAMEMD 0x004B56E0
GadgetCopyOtherView_004B56E0* GadgetCopyOtherView_004B56E0::FUN_004B56E0(GadgetCopyOtherView_004B56E0* source)
{
    FUN_00556600((GadgetCopyBaseView_004B5600*)source);
    X = source->X; Y = source->Y; Width = source->Width; Height = source->Height;
    RedrawPending = source->RedrawPending; IsSticky = source->IsSticky; IsDisabled = source->IsDisabled;
    Flags = source->Flags;
    unknown_24 = source->unknown_24; unknown_28 = source->unknown_28;
    unknown_2C = source->unknown_2C; unknown_2D = source->unknown_2D; unknown_2E = source->unknown_2E;
    unknown_30 = source->unknown_30; unknown_34 = source->unknown_34; unknown_38 = source->unknown_38;
    unknown_3C = source->unknown_3C; unknown_40 = source->unknown_40; unknown_44 = source->unknown_44;
    unknown_48 = source->unknown_48; unknown_4C = source->unknown_4C; unknown_50 = source->unknown_50;
    return this;
}


// FUNCTION: GAMEMD 0x004B5780
GadgetCopySmallView_004B5780* GadgetCopySmallView_004B5780::FUN_004B5780(GadgetCopySmallView_004B5780* source)
{
    FUN_00556600((GadgetCopyBaseView_004B5600*)source);
    X = source->X; Y = source->Y; Width = source->Width; Height = source->Height;
    RedrawPending = source->RedrawPending; IsSticky = source->IsSticky; IsDisabled = source->IsDisabled;
    Flags = source->Flags;
    return this;
}
