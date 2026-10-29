// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// RTTI TD0x8174B0/COL0x802510 names .?AVINIClass@@, table0x7EA5F4.
// Destructor0x5256F0 confirms list+C/index+28. Entry0x5CEEF0 initializes
// the local through +3C; the adjacent live CCFile begins exactly +40 after it.
// Fields at +4/+8/+3C keep unknown names: writes alone do not establish semantics.
#ifndef GG_MATCH_LAYOUT_INI_CLASS_H
#define GG_MATCH_LAYOUT_INI_CLASS_H
#include "generic_list.h"
#include "index_class_layout.h"
class Wstring;
class FileClass;
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
    // The inline construction, as CCINIClass's constructor expands it at
    // 0x5D5C07: +0x04/+0x08 zeroed, the list (0x49E8E0) and index (0x49EA10)
    // constructors called, +0x3C zeroed.
    INIClass() : unknown_04(0), unknown_08(0), unknown_3C(0) {}
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
    // FUNCTION: GAMEMD 0x526B00
    void Reset();
    // FUNCTION: GAMEMD 0x526B10
    INIEntry* GetEntry(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526CC0
    const char* GetKeyName(const char* section, int index);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) -- read an integer, RET 0xC.
    int FUN_005276D0(const char* section, const char* key, int fallback);
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
    // Declaration: GAMEMD 0x528F00 -- full EAX length, five arguments, RET14.
    unsigned int FUN_00528F00(const char* section, const char* key, const wchar_t* fallback, wchar_t* output, int maximum);
    // Declaration: GAMEMD 0x529160 -- four stack arguments, RET10; UTF16 output.
    int FUN_00529160(const char* section, const char* key, wchar_t* output, int size);
    // Declaration: GAMEMD 0x528E00 -- boolAL, three arguments, RET0C.
    bool FUN_00528E00(const char* section, const char* key, const wchar_t* value);
    // FUNCTION: GAMEMD 0x529560
    bool WriteBool(const char* section, const char* key, bool value);
    // FUNCTION: GAMEMD 0x5295F0 (decl; reloc) -- read a bool, RET 0xC.
    bool FUN_005295F0(const char* section, const char* key, bool fallback);
    // FUNCTION: GAMEMD 0x5297E0
    bool Write2Integers(const char* section, const char* key, int* values);
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
    void* unknown_04;
    void* unknown_08;
    // RTTI table 0x7E1AFC; explicit inherited vptr view is retained.
    List<INISection*> Sections;
    IndexClassRaw SectionIndex;
    unsigned int unknown_3C;
};
GG_STATIC_ASSERT(offsetof(INIClass, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(INIClass, Sections) == 0xC);
GG_STATIC_ASSERT(offsetof(INIClass, SectionIndex) == 0x28);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(List<INIClass::INISection*>) == 0x1C);
GG_STATIC_ASSERT(sizeof(INIClass) == 0x40);
// VTABLE: GAMEMD 0x7E1AFC -- List<INIClass::INISection*>.
typedef void* (List<INIClass::INISection*>::*INISectionListDeletingSlot)(unsigned int);
extern INISectionListDeletingSlot GG_VTABLE_LISTOFINISECTION;
// Inline expansion at 0x686773/0x68677C calls the GenericList constructor
// then seats this specialization's one-slot table. Out-of-line entry 0x49E8E0.
template<> inline List<INIClass::INISection*>::List()
{
    Vtable = &GG_VTABLE_LISTOFINISECTION;
}
#endif
