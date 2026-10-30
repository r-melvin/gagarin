// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Sound entry INI reader (retail 0x750440, 0x4DE bytes). The entry's first dword is its audio event; the
//   section is named after that event ("Invalid Voc" when it is missing). Every key string, default and
//   callee was read off the user's retail gamemd.exe v1.001 disassembly; the setters are named by address.
#include <string.h>
#include <stdlib.h>
#include "../platform/ccini_class_methods.h"

// The audio event a sound entry owns at +0x00. Only handled through its setters.
struct VocEvent_00750440
{
    // FUNCTION: GAMEMD 0x405170 (decl; reloc) -- the event's name.
    const char* FUN_00405170();
    // FUNCTION: GAMEMD 0x406520 (decl; reloc)
    void __fastcall FUN_00406520(int value);
    // FUNCTION: GAMEMD 0x406530 (decl; reloc)
    void __fastcall FUN_00406530(int value);
    // FUNCTION: GAMEMD 0x406540 (decl; reloc)
    void __fastcall FUN_00406540(int value);
    // FUNCTION: GAMEMD 0x406570 (decl; reloc)
    void __fastcall FUN_00406570(int value);
    // FUNCTION: GAMEMD 0x4065C0 (decl; reloc)
    void __fastcall FUN_004065C0(int value);
    // FUNCTION: GAMEMD 0x4065D0 (decl; reloc)
    void __fastcall FUN_004065D0(int value);
    // FUNCTION: GAMEMD 0x4065E0 (decl; reloc)
    void __fastcall FUN_004065E0(int value);
    // FUNCTION: GAMEMD 0x4065F0 (decl; reloc) -- the float arrives on the stack.
    void FUN_004065F0(float value);
    // FUNCTION: GAMEMD 0x406600 (decl; reloc)
    void __fastcall FUN_00406600(int first, int second);
    // FUNCTION: GAMEMD 0x406610 (decl; reloc)
    void __fastcall FUN_00406610(int first, int second);
    // FUNCTION: GAMEMD 0x406640 (decl; reloc)
    void __fastcall FUN_00406640(int value);
};

// FUNCTION: GAMEMD 0x4064A0 (decl; reloc) -- adds a sample name to the event.
int __fastcall FUN_004064A0(VocEvent_00750440* event, const char* name);
// FUNCTION: GAMEMD 0x406550 (decl; reloc)
void __fastcall FUN_00406550(VocEvent_00750440* event, int value);
// FUNCTION: GAMEMD 0x406620 (decl; reloc)
void __fastcall FUN_00406620(VocEvent_00750440* event, int value);
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

// The sound entry: its first dword is the audio event.
struct VocReader_00750440
{
    VocEvent_00750440* Event;   // +0x00

    bool ReadINI(CCINIClass* ini);
};
GG_STATIC_ASSERT(offsetof(VocReader_00750440, Event) == 0x00);

// The section name: the event's name, or a placeholder when the entry has no event.
static inline const char* VocSectionName(VocEvent_00750440* event)
{
    return event ? event->FUN_00405170() : "Invalid Voc";
}

// FUNCTION: GAMEMD 0x750440
// Reads one sound entry's section: its sample list, volumes, shifts, priority, envelope, control and
// type flags, limit, loop, range and delay/frequency-shift pairs.
bool VocReader_00750440::ReadINI(CCINIClass* ini)
{
    char buffer[0x800];
    char* token;

    ini->Reset();
    if (Event) {
        bool exists = ini->INIClass::Exists(Event->FUN_00405170(), 0);
        if (exists) {
            // STRING: GAMEMD 0x8302CC
            ini->ReadString(VocSectionName(Event), "Sounds", STR_00889F64, buffer, 0x800);
            for (token = strtok(buffer, STR_00846570); token; token = strtok(0, STR_00846570))
                FUN_004064A0(Event, token);
            // STRING: GAMEMD 0x846568
            float volume = (float)ini->ReadDouble(VocSectionName(Event), "Volume", DAT_008464B4) * DAT_007EAAE0;
            FUN_00406550(Event, (int)((volume > DAT_007E1718 ? DAT_007E2AC8 : (volume <= DAT_007E1748 ? DAT_007E1748 : volume)) * DAT_007EF38C));
            // STRING: GAMEMD 0x846560
            FUN_00406620(Event, ini->ReadInteger(VocSectionName(Event), "VShift", 0));
            // STRING: GAMEMD 0x846554
            float floor = (float)ini->ReadDouble(VocSectionName(Event), "MinVolume", DAT_008464B8) * DAT_007EAAE0;
            if (floor > DAT_007E1718)
                floor = 1.0f;
            else if (floor <= DAT_007E1748)
                floor = 0.0f;
            Event->FUN_004065F0(floor);
            // STRING: GAMEMD 0x84301C
            ini->ReadString(VocSectionName(Event), "Priority", "NORMAL", buffer, 0x800);
            int priority = DAT_008464B0;
            FUN_004067D0(buffer, &priority);
            Event->FUN_00406540(priority);
            // STRING: GAMEMD 0x816E64
            Event->FUN_00406520(ini->ReadInteger(VocSectionName(Event), "Attack", 0));
            // STRING: GAMEMD 0x84654C
            Event->FUN_00406530(ini->ReadInteger(VocSectionName(Event), "Decay", 0));
            // STRING: GAMEMD 0x846544
            ini->ReadString(VocSectionName(Event), "Control", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            int control = DAT_00B1D3B0;
            if (token) {
                control = 0;
                do {
                    FUN_00406820(&control, token);
                    token = strtok(0, STR_00846570);
                } while (token);
            }
            Event->FUN_00406570(control);
            // STRING: GAMEMD 0x824314
            ini->ReadString(VocSectionName(Event), "Type", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            int flags = DAT_008464BC;
            if (token) {
                flags = 0x20;
                do {
                    FUN_00406870(&flags, token);
                    token = strtok(0, STR_00846570);
                } while (token);
            }
            Event->FUN_004065C0(flags);
            // STRING: GAMEMD 0x84653C
            Event->FUN_004065D0(ini->ReadInteger(VocSectionName(Event), "Limit", DAT_008464C4));
            // STRING: GAMEMD 0x824238
            Event->FUN_00406640(ini->ReadInteger(VocSectionName(Event), "Loop", 0));
            // STRING: GAMEMD 0x842690
            Event->FUN_004065E0(ini->ReadInteger(VocSectionName(Event), "Range", DAT_008464C0));
            // STRING: GAMEMD 0x846534
            ini->ReadString(VocSectionName(Event), "Delay", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            int low = 0;
            if (token) {
                low = atoi(token);
                token = strtok(0, STR_00846570);
            }
            int high = low;
            if (token)
                high = atoi(token);
            Event->FUN_00406600(low, high);
            // STRING: GAMEMD 0x84652C
            ini->ReadString(VocSectionName(Event), "FShift", STR_00889F64, buffer, 0x800);
            token = strtok(buffer, STR_00846570);
            low = 0;
            if (token) {
                low = atoi(token);
                token = strtok(0, STR_00846570);
            }
            high = low;
            if (token)
                high = atoi(token);
            Event->FUN_00406610(low, high);
            return true;
        }
    }
    return false;
}
