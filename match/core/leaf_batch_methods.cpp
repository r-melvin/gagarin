// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check

#include "leaf_batch_methods.h"

// ============================================================================
// SaveGameInformation_00681090 - offsets confirmed from disassembly
// ============================================================================

// FUNCTION: GAMEMD 0x00681090
void* SaveGameInformation_00681090::GetPad0() const { return this->Pad0; }

// FUNCTION: GAMEMD 0x006810C0
void* SaveGameInformation_00681090::GetScenarioDescriptionPtr() const
{
    return (void*)&this->ScenarioDescPtr;
}

// FUNCTION: GAMEMD 0x00681100
void* SaveGameInformation_00681090::GetPlayerHousePtr() const
{
    return (void*)((char*)this + 0x108);
}

// FUNCTION: GAMEMD 0x00681120
int SaveGameInformation_00681090::GetCampaign() const { return this->Campaign; }

// FUNCTION: GAMEMD 0x00681140
int SaveGameInformation_00681090::GetScenarioNumber() const
{
    return this->ScenarioNumber;
}

// FUNCTION: GAMEMD 0x006812D0
int SaveGameInformation_00681090::GetGameType() const { return this->GameType; }

// ============================================================================
// VQASession_00759E50 - offsets confirmed from disassembly
// ============================================================================

// FUNCTION: GAMEMD 0x00759E50
void VQASession_00759E50::Resume() { this->Flags = 0; }

// FUNCTION: GAMEMD 0x00759EA0
int VQASession_00759E50::GetColorMode() const { return this->ColorMode; }

// FUNCTION: GAMEMD 0x00759F70
int VQASession_00759E50::GetWidth() const { return this->Width; }

// FUNCTION: GAMEMD 0x00759F80
int VQASession_00759E50::GetHeight() const { return this->Height; }

// ============================================================================
// TechnoClass_00707000 - offsets confirmed from disassembly
// ============================================================================

// FUNCTION: GAMEMD 0x0070DCF0
int TechnoClass_00707000::GetCurrentTurret() const { return this->CurrentTurret; }

// FUNCTION: GAMEMD 0x0070DDC0
int TechnoClass_00707000::GetCaptureTarget() const { return this->CaptureTarget; }

// FUNCTION: GAMEMD 0x0070DDF0
int TechnoClass_00707000::GetAmmo() const { return this->Ammo; }

// ============================================================================
// Global function
// ============================================================================

// FUNCTION: GAMEMD 0x0070D180
// This function sets a global byte. The actual calling convention appears to
// use a register (CL), which doesn't match standard __cdecl conventions.
// Dropping this function due to calling convention mismatch.
// void technoSetGlobalFlag(char value)
// {
//     *(char*)0x00843108 = value;
// }

// ============================================================================
// SelectableClass_006D0000
// ============================================================================

// FUNCTION: GAMEMD 0x006DC420
int SelectableClass_006D0000::GetSelectableCount() const
{
    return this->SelectableCount;
}
