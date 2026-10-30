//   No /GX. The by-value TypeList parameters of this file carry a
//   destructor, and under /GX cl registers an unwind frame to release them
//   if a callee throws: `PUSH -1; PUSH handler; PUSH FS:[0]; MOV FS:[0],ESP`
//   ahead of the frame. Retail's bodies open with a bare `SUB ESP,imm`, so
//   the retail build of this translation unit had exception handling off.
//   Measured: with /GX the 0x475C70 writer scores 13 of 247 bytes because
//   every offset after the prologue shifts; without it, 100%.
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x475F30 and
//   0x476240.

#include "ccini_class_type_list_methods.h"
#include "ccini_class_abilities_methods.h"
#include "ccini_class_base_category_methods.h"
#include "ccini_class_crc_methods.h"
#include "../_layout/sha_pipe.h"
#include "ccini_class_read3bytes_methods.h"
#include <string.h>
#include "ccini_class_read_ccfile_methods.h"
#include "ccini_class_read_color_methods.h"
#include "ccini_class_write_ccfile_methods.h"

// FUNCTION: GAMEMD 0x4741F0
//
// Load an INI from a file through a FileStraw and, when asked, check its
// stored digest: the [Digest] block is read out and cleared, the rest of
// the file hashed through a SHAPipe into this object's digest, and a
// mismatch (or a missing block) reports status 2.
//
// The straw's members are assigned in retail's store order (links, file,
// flag, vtable) and every exit routes through one label so the explicit
// destructor call and the return value in ESI form one shared tail.
int CCINI_004741F0::ReadCCFile(File_004741F0* file, bool withDigest, bool flag)
{
    int rc;
    FileStraw_004741F0 straw;
    straw.ChainTo   = 0;
    straw.ChainFrom = 0;
    straw.File      = file;
    straw.HasOpened = 0;
    straw.Vtable    = &VT_007E4D90;

    int status = Load(&straw, flag);
    DigestValid = 0;
    if (status != 0 && withDigest) {
        unsigned char stored[0x14];
        int length = GetUUBlock(STR_0081BFE0, stored, 0x14);
        if (length == 0) {
            rc = 2;
            goto out;
        }
        if (length > 0) {
            Clear(STR_0081BFE0, 0);

            SHAPipe_004741F0 sha;
            sha.ChainTo      = 0;
            sha.ChainFrom    = 0;
            sha.IsCached     = 0;
            sha.Length       = 0;
            sha.PartialCount = 0;
            sha.Acc[0] = 0x67452301;
            sha.Acc[1] = 0xEFCDAB89;
            sha.Acc[2] = 0x98BADCFE;
            sha.Acc[3] = 0x10325476;
            sha.Acc[4] = 0xC3D2E1F0;
            sha.Vtable = &VT_007E4D78;

            Save((Pipe_004741F0*)&sha);
            ((SHAPipe*)&sha)->Result(Digest);
            DigestValid = 1;
            ((Pipe*)&sha)->Pipe::~Pipe();

            if (memcmp(stored, Digest, 0x14) != 0) {
                rc = 2;
                goto out;
            }
        }
    }
    rc = status;
out:
    straw.Destroy();
    return rc;
}

// FUNCTION: GAMEMD 0x474320
// Entry-origin bytes confirm the supplied stream call, +0x40/+0x41 digest
// fields, SHA stores and all return paths. Names and argument types retain
// this TU's call-view conventions; the original overload name is unknown.
int CCINI_004741F0::FUN_00474320(Pipe_004741F0* straw, bool withDigest, bool flag)
{
    int status = Load(straw, flag);
    DigestValid = 0;
    if (status != 0 && withDigest) {
        unsigned char stored[0x14];
        int length = GetUUBlock(STR_0081BFE0, stored, 0x14);
        if (length == 0) {
            return 2;
        }
        if (length > 0) {
            Clear(STR_0081BFE0, 0);

            SHAPipe_004741F0 sha;
            sha.ChainTo      = 0;
            sha.ChainFrom    = 0;
            sha.IsCached     = 0;
            sha.Length       = 0;
            sha.PartialCount = 0;
            sha.Acc[0] = 0x67452301;
            sha.Acc[1] = 0xEFCDAB89;
            sha.Acc[2] = 0x98BADCFE;
            sha.Acc[3] = 0x10325476;
            sha.Acc[4] = 0xC3D2E1F0;
            sha.Vtable = &VT_007E4D78;

            Save((Pipe_004741F0*)&sha);
            ((SHAPipe*)&sha)->Result(Digest);
            DigestValid = 1;
            ((Pipe*)&sha)->Pipe::~Pipe();

            if (memcmp(stored, Digest, 0x14) != 0) {
                return 2;
            }
        }
    }
    return status;
}

// FUNCTION: GAMEMD 0x474430
//
// Write the INI out through a file pipe. Without the digest the file is simply
// saved. With it, the old [Digest] section is cleared, the whole INI is run
// through a stack SHA-1 pipe, the 20-byte digest is cached at +0x41 (flag at
// +0x40), stored back as a UU-encoded [Digest] block, the file is saved with
// it, and the section is cleared again so the in-memory copy stays clean.
// Either way the byte count of the file save comes back.
int CCINI_00474430::WriteCCFile(File_00474430* file, bool withDigest)
{
    int result;
    FilePipe_00474430 pipe;
    pipe.File      = file;
    pipe.ChainTo   = 0;
    pipe.ChainFrom = 0;
    pipe.HasOpened = 0;
    pipe.Vtable    = &VT_007E4DA0;

    if (!withDigest) {
        result = Save(&pipe);
    } else {
        Clear(STR_0081BFE0, 0);

        SHAPipe_00474430 sha;
        sha.ChainTo      = 0;
        sha.ChainFrom    = 0;
        sha.IsCached     = 0;
        sha.Length       = 0;
        sha.PartialCount = 0;
        sha.Acc[0] = 0x67452301;
        sha.Acc[1] = 0xEFCDAB89;
        sha.Acc[2] = 0x98BADCFE;
        sha.Acc[3] = 0x10325476;
        sha.Acc[4] = 0xC3D2E1F0;
        sha.Vtable = &VT_007E4D78;

        Save((Pipe_00474430*)&sha);
        ((SHAPipe*)&sha)->Result(Digest);
        DigestValid = 1;
        ((Pipe*)&sha)->Pipe::~Pipe();

        PutUUBlock(STR_0081BFE0, Digest, 0x14);
        result = Save(&pipe);
        Clear(STR_0081BFE0, 0);
    }

    pipe.Destroy();
    return result;
}

// FUNCTION: GAMEMD 0x474B50
//
// Read an "R,G,B" triple from the INI. The default is first printed into a
// text buffer so the string reader can hand it back verbatim when the key is
// absent; a present key is parsed back into three ints and narrowed to bytes.
// When the reader reports nothing the default is returned unchanged.
ColorStruct CCINIClass::Read3Bytes(const char* section, const char* key,
                                   const ColorStruct& def)
{
    char defbuf[64];
    char buffer[64];
    int  r;
    int  g;
    int  b;

    sprintf(defbuf, "%d,%d,%d", def.R, def.G, def.B);

    if (this->ReadString(section, key, defbuf, buffer, sizeof(buffer))) {
        sscanf(buffer, "%d,%d,%d", &r, &g, &b);
        return ColorStruct((unsigned char)r, (unsigned char)g, (unsigned char)b);
    }

    return def;
}

// FUNCTION: GAMEMD 0x474C70
//
// Read an "r,g,b" colour value. The default is first rendered to text so the
// string reader can hand it back when the key is missing; whatever text
// results is parsed with sscanf into three ints (zeroed first, so a short
// value leaves the tail black) and packed into the out struct. When the
// reader finds nothing at all the default is copied straight across.
ColorStruct* CCINIClass::ReadColor(ColorStruct* pOut, const char* pSection,
                                   const char* pKey, const ColorStruct& defValue)
{
    char defText[64];
    char buffer[64];

    sprintf(defText, "%d,%d,%d", defValue.R, defValue.G, defValue.B);
    if (this->ReadString(pSection, pKey, defText, buffer, sizeof(buffer))) {
        int r = 0;
        int g = 0;
        int b = 0;
        sscanf(buffer, "%d,%d,%d", &r, &g, &b);
        *pOut = ColorStruct((unsigned char)r, (unsigned char)g, (unsigned char)b);
    } else {
        *pOut = defValue;
    }
    return pOut;
}

// FUNCTION: GAMEMD 0x475A40
//
// Write an index out as its name, with no sentinel: the receiver passes
// straight through in ECX into the tail call.
bool CCINI_00475A40::FUN_00475A40(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_007E523C[index]);
}

// FUNCTION: GAMEMD 0x475A60
//
// Read a comma-separated list of base categories into a bit mask. The four
// named categories claim the top four bits and are tested unconditionally
// one after another rather than as an exclusive chain, so a token matching
// one is still looked up as a category afterwards.
//
// The accumulator is declared above the `if` and assigned on both arms, and
// that single-exit shape is what the retail bytes require: retail saves both
// callee-saved registers at the top of the body and pops them in each of the
// two return blocks. Written with a `return flags;` inside the arm and a
// `return defaultValue;` after it, cl 8804 instead shrink-wraps the pushes
// into the success arm and leaves the cold return with no pops at all,
// shifting every byte after offset 0x0E (181 of 263 bytes). Assigning the
// default to the same variable on the else arm keeps it live on both paths,
// which restores the entry save without hoisting its zeroing above the
// ReadString call.
int CCINI_00475A40::ReadCategoryList(const char* section, const char* key,
                                     int defaultValue)
{
    char buffer[128];
    int flags;

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        flags = 0;

            for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            if (FUN_007C8D20(token, STR_0081C030) == 0) {
                flags |= 0x80000000;
            }

            if (FUN_007C8D20(token, STR_0081C028) == 0) {
                flags |= 0x40000000;
            }

            if (FUN_007C8D20(token, STR_0081C01C) == 0) {
                flags |= 0x20000000;
            }

            if (FUN_007C8D20(token, STR_0081C014) == 0) {
                flags |= 0x10000000;
            }

            int bit = FUN_0045E7B0(token);

            if (bit != -1) {
                flags |= 1 << bit;
            }
        }

    } else {
        flags = defaultValue;
    }

    return flags;
}

// FUNCTION: GAMEMD 0x475B70
//
// The writer 0x475A60 pairs with: turn a base-category bit mask back into a
// comma-separated list of category names. Only the low bits are spelled --
// the walk is capped at 32 entries, one per bit of the mask -- so the four
// named flags the reader folds into the top bits are not written back here.
// Both string appends are the /O2 inlined strcat, and the registry's Items
// pointer is hoisted out of the loop because nothing in the body calls.
bool CCINI_00475A40::WriteCategoryList(const char* section, const char* key,
                                       int mask)
{
    char buffer[128] = "";

    int total = DAT_00A83C68.Count;
    int count = total > 32 ? 32 : total;

    for (int i = 0; i < count; ++i) {
        if (mask & (1 << i)) {
            if (buffer[0] != '\0') {
                strcat(buffer, STR_00817F70);
            }

            strcat(buffer, DAT_00A83C68.Items[i]->ID);
        }
    }

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x475D70
//
// Read a comma-separated list of decimal integers. Each token is parsed and
// appended; a token that is empty ends the walk, as does a missing key,
// which returns the caller's list unchanged. Both the list built here and
// the list that arrived by value are released inline at the tail, which is
// why the body ends in two interleaved copies of the same free.
TypeListInt CCINI_00475C70::ReadIntegerList(const char* section, const char* key,
                                            TypeListInt defaultValue)
{
    char buffer[512];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        TypeListInt list(0, 0);

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            int value = FUN_007C9BFD(token);

            list.AddItem(value);
        }

        return TypeListInt(list, 0);
    }

    return defaultValue;
}

// Append one resolved record to a list as a packed identity. Retail expands
// this twice, once per registry, and cross-jumps only the constructor call
// the two copies share, which is why each copy keeps a temporary of its own.
static inline void AddTypeId(TypeListInt& list, AbstractType_006E6AB0* type)
{
    const TypeId_00476240& id = TypeId_00476240(type);

    int  value = id.ID;
    char rtti = id.RTTI;

    if (rtti != 0) {
        int packed = ((int)(unsigned char)rtti << 24) | (value & 0xFFFFFF);

        list.AddItem(packed);
    }
}

// FUNCTION: GAMEMD 0x476020
//
// Read a comma-separated list of record names into packed identities. Each
// token is looked up in the first registry and then, failing that, in the
// second; a name in neither is skipped, as is a record whose abstract-type
// tag comes back zero.
//
// PARTIAL, 132 of 540 bytes identical. The prologue, the token loop, the
// packing, the append, the return copy and both inlined releases are all
// the retail stream; the residual is one structural fact about the two
// registry arms. Retail keeps a separate identity temporary per arm (the
// two `LEA ECX` seats are eight bytes apart, which is what makes its frame
// 0x234 rather than 0x22C) and then cross-jumps everything from the shared
// `CALL 0x6E6AB0` onwards, so the body after the constructor exists once.
// cl 8804 does the opposite in both halves: it merges the two temporaries
// into one stack slot and then emits the tail twice, which shifts every
// stack displacement by eight and duplicates ninety bytes. Three materially
// different spellings were measured: the two arms written out with a
// forced-inline helper per arm (the spelling below, 132 bytes); the same
// with the append forced inline as well, which makes the two arms literally
// identical and still does not get them merged (125 bytes); and a reference
// bound to a conditional expression of two constructor temporaries, which
// is the shape that should produce two temporaries and does not (128
// bytes). The next thing to try is whether the tail can be made to end in a
// shape cl will cross-jump, since the temporary count follows from that
// rather than the other way round.
TypeListInt CCINI_00475C70::ReadTypeIdList(const char* section, const char* key,
                                           TypeListInt defaultValue)
{
    char buffer[512];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        TypeListInt list(0, 0);

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            int index = FUN_00523C90(token);

            if (index != -1) {
                AddTypeId(list, DAT_00A8E34C[index]);
            } else {
                index = FUN_00747370(token);

                if (index != -1) {
                    AddTypeId(list, DAT_00A83CE4[index]);
                }
            }
        }

        return TypeListInt(list, 0);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x475F30
//
// Write a list of plain integers out as a comma-separated line. The
// separator append and the value append are both the /O2 inlined strcat; the
// value itself goes through the C library formatter into a twelve-byte
// scratch buffer, which is what fixes the frame at 512 + 12 + 4 bytes.
bool CCINI_00475C70::WriteIntegerList(const char* section, const char* key,
                                      const TypeListInt* list)
{
    char temp[12];
    char buffer[512] = "";

    for (int i = 0; i < list->Count; ++i) {
        if (buffer[0] != '\0') {
            strcat(buffer, STR_00817F70);
        }

        sprintf(temp, STR_00817F6C, list->Items[i]);
        strcat(buffer, temp);
    }

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x476240
//
// Write a list of packed type identities out by name. Each element is split
// back into its abstract-type tag and its registry index, handed to the
// resolver at 0x6E7330 in ECX, and the record's inline ID text appended.
bool CCINI_00475C70::WriteTypeIdList(const char* section, const char* key,
                                     const TypeListInt* list)
{
    char buffer[512] = "";

    for (int i = 0; i < list->Count; ++i) {
        if (buffer[0] != '\0') {
            strcat(buffer, STR_00817F70);
        }

        TypeId_00476240 id;
        int packed = list->Items[i];

        id.RTTI = (char)(packed >> 24);
        id.ID = packed & 0xFFFFFF;

        ObjectType_00476240* type = FUN_006E7330(&id);

        strcat(buffer, type->ID);
    }

    return WriteString(section, key, buffer);
}


// FUNCTION: GAMEMD 0x476D80
//
// A 32-bit checksum of the INI. The 20-byte SHA-1 digest at +0x41 is computed
// once (a stack hash engine is seeded, fed the whole file, and asked for its
// result) and cached behind the flag at +0x40; the returned value is a CRC run
// over that digest by a freshly zeroed CRC engine.
int CCINI_00476D80::GetCRC()
{
    if (DigestValid == 0) {
        SHA_00476D80 sha;
        sha.ChainTo      = 0;
        sha.ChainFrom    = 0;
        sha.IsCached     = 0;
        sha.Length       = 0;
        sha.PartialCount = 0;
        sha.Acc[0] = 0x67452301;
        sha.Acc[1] = 0xEFCDAB89;
        sha.Acc[2] = 0x98BADCFE;
        sha.Acc[3] = 0x10325476;
        sha.Acc[4] = 0xC3D2E1F0;
        sha.Vtable = &VT_007E4D78;

        FUN_00526470(&sha);
        ((SHAPipe*)&sha)->Result(Digest);
        DigestValid = 1;
        ((Pipe*)&sha)->Pipe::~Pipe();
    }

    CRC_00476D80 crc;
    crc.CRC     = 0;
    crc.Staging = 0;
    crc.Index   = 0;
    return crc.FUN_004A1DE0(Digest, 0x14);
}

// FUNCTION: GAMEMD 0x477640
//
// Read a comma-separated ability list. When the key is present each token is
// looked up by name and the matching flag set in a zeroed result; an absent
// key hands back the caller's default unchanged.
AbilitiesStruct CCINIClass::ReadAbilities(const char* section, const char* key,
                                          const AbilitiesStruct& def)
{
    char buffer[0x80];

    if (this->ReadString(section, key, DAT_00889F64, buffer, 0x80) != 0) {
        AbilitiesStruct result;
        memset(&result, 0, sizeof(result));

        char* token;
        for (token = strtok(buffer, DAT_00817F70); token != 0 && *token != 0;
             token = strtok(0, DAT_00817F70)) {
            int index = FUN_0074FEF0(token);
            if (index != -1) {
                result.Flags[index] = true;
            }
        }
        return result;
    }

    return def;
}


// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x817F70
extern const char DAT_00817F70[] = ",";
// END defined globals


// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x81C014
extern const char STR_0081C014[] = "RADAR";
// GLOBAL: GAMEMD 0x81C01C
extern const char STR_0081C01C[] = "BARRACKS";
// GLOBAL: GAMEMD 0x81C028
extern const char STR_0081C028[] = "FACTORY";
// GLOBAL: GAMEMD 0x81C030
extern const char STR_0081C030[] = "POWER";
// END defined globals
