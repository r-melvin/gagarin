// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + behaviour derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x529560 / 0x5297E0 /
//   0x679F40), cross-checked against YRpp / INIClass (every address + convention reconfirmed below from the disasm).
//
// INIClass uses the shared binary-confirmed layout. CCINIClass::Exists
// preserves the zero-offset base receiver established by retail RTTI;
// its added fields and complete derived size remain outside this view.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/ini_class.h"


class FileClass;
template<class T> class TypeList;
class Straw;
class TechnoTypeClass;
class IniKeyBlockSource;
struct AbilitiesStruct;
#include "../_layout/color_struct.h"

// VTABLE: GAMEMD 0x7E1AF4
//   sizeof 0x58: `PUSH 0x58; CALL operator new` before the inline
//   construction at 0x5D5BD9. ReadCCFile 0x4741F0 clears and sets +0x40 and
//   writes the SHA result to +0x41.
class CCINIClass : public INIClass
{
public:
    CCINIClass() : DigestValid(false) {}
    // Declaration: GAMEMD 0x477440 -- five stackargs, RET14hex.
    // Declaration: GAMEMD 0x477510 -- five arguments, RET14; forwards WriteString bool.
    bool FUN_00477510(const char* section, const char* key, int first, int second, int third);
    void FUN_00477440(const char* section, const char* key, int* first, int* second, int* third);
    // FUNCTION: GAMEMD 0x4741F0 (decl; reloc) -- RET 0xC.
    int ReadCCFile(FileClass* file, bool withDigest, bool flag);
    // Declaration: GAMEMD 0x474320 -- three stack arguments, RET0C.
    int FUN_00474320(Straw* straw, bool withDigest, bool flag);
    int FUN_004757D0(const char* section, const char* key, int fallback); // GAMEMD 0x4757D0
    int WriteCCFile(FileClass* file, bool withDigest); // GAMEMD 0x474430
    // Declaration: GAMEMD 0x475540 -- EAX result, three arguments, RET0C.
    int FUN_00475540(const char* section, const char* key, int fallback);
    // Declaration: GAMEMD 0x475610 -- three arguments, RET0C.
    bool FUN_00475610(const char* section, const char* key, int value);
    // FUNCTION: GAMEMD 0x679F40  CCINIClass::Exists         (__thiscall)
    bool Exists(const char* pSection, const char* pKey);

    // FUNCTION: GAMEMD 0x474DA0 (decl; reloc) -- foundation enumeration, RET0C.
    int ReadFoundation(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x474A90 (decl; reloc) -- colour-scheme index, RET 0xC.
    int ReadColorScheme(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x4756F0 (decl; reloc) -- side-name index, RET 0xC.
    int FUN_004756F0(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x4753F0 (decl; reloc) -- armor enumeration, RET 0xC.
    int ReadArmor(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x474B50 (decl; reloc) -- hidden RGB result, default by reference.
    ColorStruct Read3Bytes(const char* section, const char* key, const ColorStruct& fallback);

    // The readers below sit on INIClass in retail (their addresses are the INIClass
    // members above). The TUs that call them were matched against these CCINIClass
    // spellings, whose symbols are bound separately, so they stay declared here.
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- read a string into a buffer, RET 0x14.
    int ReadString(const char* section, const char* key, const char* def, char* buffer, int size);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) -- read an integer, RET 0xC.
    int ReadInteger(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc) -- read a double, RET 0x10.
    double ReadDouble(const char* section, const char* key, double defaultValue);
    // FUNCTION: GAMEMD 0x5295F0 (decl; reloc) -- read a bool, RET 0xC.
    bool ReadBool(const char* section, const char* key, bool defaultValue);
    // FUNCTION: GAMEMD 0x474B50 (decl; reloc) -- the same reader with the result buffer explicit.
    ColorStruct* Read3Bytes(ColorStruct* pOut, const char* section, const char* key,
                            const ColorStruct& defValue);
    // FUNCTION: GAMEMD 0x474C70 (decl; reloc) -- colour reader with the result buffer explicit.
    ColorStruct* ReadColor(ColorStruct* pOut, const char* section, const char* key,
                           const ColorStruct& defValue);
    // Inline forwarding wrapper (YRpp's by-value ReadColor shape): the read buffer is the
    // wrapper's own local and the result is copied out of it.
    ColorStruct ReadColor(const char* section, const char* key, const ColorStruct& defValue)
    {
        ColorStruct out;
        return *ReadColor(&out, section, key, defValue);
    }
    // FUNCTION: GAMEMD 0x476EB0 (decl; reloc)
    TechnoTypeClass* GetTechnoType(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x526E80 (decl; reloc) -- uuencoded block writer.
    bool WriteUUBlock(const char* section, const void* block, int length);
    // FUNCTION: GAMEMD 0x52A610
    bool WriteKeyBlocks(const IniKeyBlockSource& key);
    // FUNCTION: GAMEMD 0x477640
    AbilitiesStruct ReadAbilities(const char* section, const char* key, const AbilitiesStruct& def);

    // FUNCTION: GAMEMD 0x474620 (decl; reloc) -- a fraction read as a double and scaled by 256, RET 0xC.
    int ReadFraction(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474810 (decl; reloc) -- percentage clamped to 0..100 and scaled to a byte, RET 0xC.
    int ReadPercentAsByte(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475D70 (decl; reloc) -- comma-separated integers; the default list goes by value.
    TypeList<int> ReadIntegerList(const char* section, const char* key, TypeList<int> defaultValue);
    // FUNCTION: GAMEMD 0x4759F0 (decl; reloc) -- string read through the 0x48DE70 parser, RET 0xC.
    int FUN_004759F0(const char* section, const char* key, int defaultValue);

    bool          DigestValid;     // +0x40
    unsigned char Digest[0x14];    // +0x41
};
GG_STATIC_ASSERT(offsetof(CCINIClass, DigestValid) == 0x40);
GG_STATIC_ASSERT(sizeof(CCINIClass) == 0x58);

// GLOBAL: GAMEMD 0x887048 -- native52D0FA selects a CCINIClass pointer.
// Allocations52CDF1/52CF46: size58, vtable7E1AF4 (RTTI CCINIClass).
extern CCINIClass* DAT_00887048;
GG_STATIC_ASSERT(sizeof(DAT_00887048) == 4);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
