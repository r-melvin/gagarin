// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// RTTI TD0x8174B0/COL0x802510 names .?AVINIClass@@, table0x7EA5F4.
// Destructor0x5256F0 confirms list+C/index+28. Entry0x5CEEF0 initializes
// the local through +3C; the adjacent live CCFile begins exactly +40 after it.
// Fields at +4/+8/+3C keep unknown names: writes alone do not establish semantics.
#ifndef GG_MATCH_LAYOUT_INI_CLASS_H
#define GG_MATCH_LAYOUT_INI_CLASS_H
#include "generic_list.h"
#include "geometry2d.h"
#include "index_class_layout.h"
class Wstring;
class FileClass;
class Straw;
class Pipe;
struct IniIntQuad;
struct IniIntTriple;
struct IniFloatTriple;
// VTABLE: GAMEMD 0x7EA5F4 -- INIClass, one deleting slot.
class INIClass
{
public:
    // Retail TypeDescriptors name these nested structs.
    struct INIEntry;
    struct INISection;
    // The section index, IndexClass<int, INISection*> (out-of-line copies 0x52B390/0x52B430/0x52B620/0x52B720).
    // Retail constructs it through the call at 0x49EA10 (the INIClass constructor expanded at 0x5D5C07), which an
    // inline template constructor cannot reproduce (VC6 ignores an explicit-specialisation declaration), so this
    // thin class carries the constructor declaration only, as IndexClassRaw does.
    struct SectionIndexClass : public IndexClass<int, INISection*>
    {
        // FUNCTION: GAMEMD 0x49EA10 (decl; reloc) -- zero all five fields.
        SectionIndexClass();
        // The inline construction (five zero stores) the wolinfoMD.ini accessors at 0x779730..0x77A04C expand.
        struct InlineIndex {};
        SectionIndexClass(InlineIndex) {}
        // FUNCTION: GAMEMD 0x52B390 (decl; reloc) -- IsPresent, the out-of-line copy the lookups call. Declared here
        // as well as on the template: Ini.cpp defines the template's copy, and a body the TU can see is expanded
        // inline at the call sites, where retail calls.
        bool FUN_0052B390(const int& id);
    };
    // Retail's out-of-line copy is 0x535AA0 (ini_class_ctor_535aa0.cpp, with the list and index constructors expanded
    // inside it). The units that expand the construction themselves, as CCINIClass's constructor does at
    // 0x5D5C07 (+0x04/+0x08 zeroed, the list 0x49E8E0 and index 0x49EA10 constructors called, +0x3C zeroed), include
    // ini_class_default_ctor.h for the inline body.
    INIClass();
    // The same with the index construction expanded inline (0x779730).
    INIClass(SectionIndexClass::InlineIndex tag) : unknown_04(0), unknown_08(0), SectionIndex(tag), unknown_3C(0) {}
    // FUNCTION: GAMEMD 0x5256F0
    virtual ~INIClass();
    // Declaration: GAMEMD 0x525A10 -- file and full DWORD options, RET8; EAX ABI view.
    int FUN_00525A10(FileClass* file, unsigned long options);
    // FUNCTION: GAMEMD 0x5257C0
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526810
    INISection* GetSection(const char* section);
    // Inline native test at 0x69A4B3..0x69A505; the existing standalone
    // implementation is bound at0x679F40. The derived entry remains intact.
    bool Exists(const char* section, const char* key)
    {
        if (key == 0) return GetSection(section) != 0;
        return GetEntry(section, key) != 0;
    }
    // FUNCTION: GAMEMD 0x526960
    int GetKeyCount(const char* section);
    // FUNCTION: GAMEMD 0x526470 (decl; reloc) -- hash the whole INI into the engine.
    void FUN_00526470(struct SHAPipeLayout* sha);
    // Declaration: GAMEMD 0x526A30 -- section name as a Wstring, RET 4; key count.
    int FUN_00526A30(const Wstring& section);
    // FUNCTION: GAMEMD 0x526D90 (decl; reloc) -- the name of the entry at `index` in a section named by a Wstring;
    // hidden result pointer, two further stack words, RET 0xC.
    Wstring FUN_00526D90(const Wstring& section, int index);
    // FUNCTION: GAMEMD 0x526B00
    void Reset();
    // FUNCTION: GAMEMD 0x526B10
    INIEntry* GetEntry(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526CC0
    const char* GetKeyName(const char* section, int index);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) -- read an integer, RET 0xC.
    int FUN_005276D0(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x5278F0 (decl; reloc) -- read an integer under Wstring names, RET 0xC.
    int FUN_005278F0(const Wstring& section, const Wstring& key, int fallback);
    // FUNCTION: GAMEMD 0x528220 -- read a hexadecimal integer ("%x"), RET 0xC.
    int FUN_00528220(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc) -- section/key and double fallback, RET16.
    double FUN_005283D0(const char* section, const char* key, double fallback);
    // FUNCTION: GAMEMD 0x5275C0
    bool WriteInteger(const char* section, const char* key, int value, int format);
    // FUNCTION: GAMEMD 0x527B90 -- writes a GUID in its braced text form.
    bool FUN_00527B90(const char* section, const char* key, const struct _GUID& guid);
    // FUNCTION: GAMEMD 0x528660
    bool WriteString(const char* section, const char* key, const char* value);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- read a string into a buffer, RET 0x14.
    int FUN_00528A10(const char* section, const char* key, const char* fallback, char* buffer, int size);
    // Declaration: GAMEMD 0x528C00 -- four stack pointers, RET10, signed length in EAX.
    int FUN_00528C00(const Wstring* section, const Wstring* key,
                     const Wstring* fallback, Wstring* output);
    // FUNCTION: GAMEMD 0x529A30 (decl; reloc) -- read a point under Wstring names; the result comes back through the hidden
    // pointer (4 stack words, RET 0x10).
    Point2D FUN_00529A30(const Wstring* section, const Wstring* key, const Point2D* fallback);
    // FUNCTION: GAMEMD 0x527F20 (decl; reloc) -- read a rectangle under Wstring names; hidden result pointer, RET 0x10.
    RectangleStruct FUN_00527F20(const Wstring* section, const Wstring* key, const RectangleStruct* fallback);
    // Declaration: GAMEMD 0x528F00 -- full EAX length, five arguments, RET14.
    unsigned int FUN_00528F00(const char* section, const char* key, const wchar_t* fallback, wchar_t* output, int maximum);
    // Declaration: GAMEMD 0x529160 -- four stack arguments, RET10; UTF16 output.
    int FUN_00529160(const char* section, const char* key, wchar_t* output, int size);
    // Declaration: GAMEMD 0x528E00 -- boolAL, three arguments, RET0C.
    bool FUN_00528E00(const char* section, const char* key, const wchar_t* value);
    // Declaration: GAMEMD 0x5289E0 -- writes a string under Wstring section, key and value, RET 0xC.
    void FUN_005289E0(const Wstring& section, const Wstring& key, const Wstring& value);
    // FUNCTION: GAMEMD 0x529560
    bool WriteBool(const char* section, const char* key, bool value);
    // FUNCTION: GAMEMD 0x5295F0 (decl; reloc) -- read a bool, RET 0xC.
    bool FUN_005295F0(const char* section, const char* key, bool fallback);
    // FUNCTION: GAMEMD 0x5297E0
    bool Write2Integers(const char* section, const char* key, int* values);
    // FUNCTION: GAMEMD 0x52A760 -- read an "hh:mm:ss" time as ticks, RET 0xC.
    int FUN_0052A760(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x52AA90
    static void FUN_0052AA90(char* buffer);
    // FUNCTION: GAMEMD 0x52AAC0
    static bool FUN_0052AAC0(char* buffer);
    // Round 15: GAMEMD 0x528170 writes an integer as upper-case hex; GAMEMD 0x5295A0 is WriteBool over Wstring names.
    bool FUN_00528170(const char* section, const char* key, int value);
    bool WriteBool(const Wstring& section, const Wstring& key, bool value);
    // Round 15 (Wstring names): GAMEMD 0x529820, 0x529C40, 0x52A0A0.
    bool Write2Integers(const Wstring& section, const Wstring& key, const int* values);
    bool WriteIntTriple(const Wstring& section, const Wstring& key, const int* values);
    bool WriteFloatTriple(const Wstring& section, const Wstring& key, const float* values);
    // Round 15 (Wstring names): GAMEMD 0x527640, 0x527C60, 0x528600.
    bool WriteInteger(const Wstring& section, const Wstring& key, int value, int format);
    bool WriteIntQuad(const Wstring& section, const Wstring& key, const int* values);
    bool WriteDouble(const Wstring& section, const Wstring& key, double value);
    // FUNCTION: GAMEMD 0x5285B0 -- writes a double with "%f".
    bool WriteDouble(const char* section, const char* key, double value);
    // GAMEMD 0x5281C0: the Wstring-name twin of 0x528170.
    bool FUN_005281C0(const Wstring& section, const Wstring& key, int value);
    // GAMEMD 0x527C10 / 0x529BF0 / 0x52A040: composite writers over the narrow-name string writer.
    bool WriteIntQuad(const char* section, const char* key, const IniIntQuad& value);
    bool WriteIntTriple(const char* section, const char* key, const IniIntTriple& value);
    bool WriteFloatTriple(const char* section, const char* key, const IniFloatTriple& value);
    // GAMEMD 0x525A60 / 0x526470: load from a straw / save into a pipe; 0x526420 saves through a file pipe.
    int LoadStraw(Straw* straw, unsigned long options);
    int SavePipe(Pipe* pipe);
    int FUN_00526420(FileClass* file);
    // The one-entry section cache GetEntry and the typed readers consult first: the name
    // pointer last looked up, and the section it resolved to (both zeroed by Reset 0x526B00
    // and on a miss).
    const char* unknown_04;
    INISection* unknown_08;
    // RTTI table 0x7E1AFC.
    List<INISection*> Sections;
    // The CRC-keyed section index; its out-of-line members are at 0x52B390/0x52B430/0x52B620.
    SectionIndexClass SectionIndex;
    unsigned int unknown_3C;
};
GG_STATIC_ASSERT(offsetof(INIClass, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(INIClass, Sections) == 0xC);
GG_STATIC_ASSERT(offsetof(INIClass, SectionIndex) == 0x28);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(List<INIClass::INISection*>) == 0x1C);
GG_STATIC_ASSERT(sizeof(INIClass::SectionIndexClass) == 0x14);
GG_STATIC_ASSERT(sizeof(INIClass) == 0x40);
// VTABLE: GAMEMD 0x7E1AFC -- List<INIClass::INISection*>.
#endif
