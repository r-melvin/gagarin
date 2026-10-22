//   No /GX: the by-value TypeList parameter has a destructor, and /GX would
//   wrap the body in an unwind frame retail does not have (bare `SUB ESP`).
// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x525430: __fastcall with the hidden
//   result in ECX and the INI object in EDX, three stack arguments (section,
//   key, a 0x1C-byte TypeList<int> by value; `RET 0x24`); a 0x80-byte read
//   buffer filled by 0x528A10; tokens split on "," (0x817F70) by 0x7C9CC2;
//   each token resolved by 0x751520 (name -> record) and 0x7515C0 (record ->
//   index), appended through the inlined TypeList add; returned by the
//   out-of-line copy 0x477B60, or the default copied through 0x478720.

#include "ccini_class_type_list_methods.h"

// FUNCTION: GAMEMD 0x751520 (decl; reloc) -- name -> record, or 0.
void* __fastcall FUN_00751520(const char* name);
// FUNCTION: GAMEMD 0x7515C0 (decl; reloc) -- record -> registry index.
int __fastcall FUN_007515C0(void* record);

// FUNCTION: GAMEMD 0x525430
// Read a comma-separated list of record names as registry indices. Unknown
// names are skipped; a missing key returns the caller's default list.
TypeListInt __fastcall FUN_00525430(CCINI_00475C70* ini, const char* section,
    const char* key, TypeListInt defaultValue)
{
    char buffer[128];

    if (ini->ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        TypeListInt list(0, 0);

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            void* record = FUN_00751520(token);
            if (record != 0) {
                list.AddItem(FUN_007515C0(record));
            }
        }

        return TypeListInt(list, 0);
    }

    return defaultValue;
}
