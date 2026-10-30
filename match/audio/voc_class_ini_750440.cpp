// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Sound entry INI reader (retail 0x750440, 0x4DE bytes). The entry's first dword is its audio event; the
//   section is named after that event ("Invalid Voc" when it is missing). Every key string, default and
//   callee was read off the user's retail gamemd.exe v1.001 disassembly; the setters are named by address.
#include <string.h>
#include <stdlib.h>
#include "../platform/ccini_class_methods.h"
#include "../_layout/voc_class.h"

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
// GLOBAL: GAMEMD 0x7E1718 -- 1.0 (double).
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E1748 -- 0.0f.
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E2AC8 -- 1.0f.
extern const float DAT_007E2AC8;
// GLOBAL: GAMEMD 0x7EAAE0 -- 0.01f.
extern const float DAT_007EAAE0;
// GLOBAL: GAMEMD 0x7EF38C -- 16384.0f.
extern const float DAT_007EF38C;

// The section name: the descriptor's name, or a placeholder when the entry has none.
static inline const char* VocSectionName(AudioEventType* event)
{
    return event ? event->FUN_00405170() : "Invalid Voc";
}

// FUNCTION: GAMEMD 0x750440
// Reads one sound entry's section: its sample list, volumes, shifts, priority, envelope, control and
// type flags, limit, loop, range and delay/frequency-shift pairs.
bool VocClass::ReadINI(CCINIClass* ini)
{
    char buffer[0x800];
    char* token;

    ini->Reset();
    if (EventType) {
        bool exists = ini->INIClass::Exists(EventType->FUN_00405170(), 0);
        if (exists) {
            // STRING: GAMEMD 0x8302CC
            ini->ReadString(VocSectionName(EventType), "Sounds", STR_00889F64, buffer, 0x800);
            for (token = strtok(buffer, STR_00846570); token; token = strtok(0, STR_00846570))
                EventType->FUN_004064A0(token);
            // STRING: GAMEMD 0x846568
            float volume = (float)ini->ReadDouble(VocSectionName(EventType), "Volume", DAT_008464B4) * DAT_007EAAE0;
            EventType->FUN_00406550((int)((volume > DAT_007E1718 ? DAT_007E2AC8 : (volume <= DAT_007E1748 ? DAT_007E1748 : volume)) * DAT_007EF38C));
            // STRING: GAMEMD 0x846560
            EventType->FUN_00406620(ini->ReadInteger(VocSectionName(EventType), "VShift", 0));
            // STRING: GAMEMD 0x846554
            float floor = (float)ini->ReadDouble(VocSectionName(EventType), "MinVolume", DAT_008464B8) * DAT_007EAAE0;
            if (floor > DAT_007E1718)
                floor = 1.0f;
            else if (floor <= DAT_007E1748)
                floor = 0.0f;
            EventType->FUN_004065F0(floor);
            // STRING: GAMEMD 0x84301C
            ini->ReadString(VocSectionName(EventType), "Priority", "NORMAL", buffer, 0x800);
            int priority = DAT_008464B0;
            FUN_004067D0(buffer, &priority);
            EventType->FUN_00406540(priority);
            // STRING: GAMEMD 0x816E64
            EventType->FUN_00406520(ini->ReadInteger(VocSectionName(EventType), "Attack", 0));
            // STRING: GAMEMD 0x84654C
            EventType->FUN_00406530(ini->ReadInteger(VocSectionName(EventType), "Decay", 0));
            // STRING: GAMEMD 0x846544
            ini->ReadString(VocSectionName(EventType), "Control", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            int control = DAT_00B1D3B0;
            if (token) {
                control = 0;
                do {
                    FUN_00406820(&control, token);
                    token = strtok(0, STR_00846570);
                } while (token);
            }
            EventType->FUN_00406570(control);
            // STRING: GAMEMD 0x824314
            ini->ReadString(VocSectionName(EventType), "Type", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            int flags = DAT_008464BC;
            if (token) {
                flags = 0x20;
                do {
                    FUN_00406870(&flags, token);
                    token = strtok(0, STR_00846570);
                } while (token);
            }
            EventType->FUN_004065C0(flags);
            // STRING: GAMEMD 0x84653C
            EventType->FUN_004065D0(ini->ReadInteger(VocSectionName(EventType), "Limit", DAT_008464C4));
            // STRING: GAMEMD 0x824238
            EventType->FUN_00406640(ini->ReadInteger(VocSectionName(EventType), "Loop", 0));
            // STRING: GAMEMD 0x842690
            EventType->FUN_004065E0(ini->ReadInteger(VocSectionName(EventType), "Range", DAT_008464C0));
            // STRING: GAMEMD 0x846534
            ini->ReadString(VocSectionName(EventType), "Delay", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            int low = 0;
            if (token) {
                low = atoi(token);
                token = strtok(0, STR_00846570);
            }
            int high = low;
            if (token)
                high = atoi(token);
            EventType->FUN_00406600(low, high);
            // STRING: GAMEMD 0x84652C
            ini->ReadString(VocSectionName(EventType), "FShift", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            low = 0;
            if (token) {
                low = atoi(token);
                token = strtok(0, STR_00846570);
            }
            high = low;
            if (token)
                high = atoi(token);
            EventType->FUN_00406610(low, high);
            return true;
        }
    }
    return false;
}
