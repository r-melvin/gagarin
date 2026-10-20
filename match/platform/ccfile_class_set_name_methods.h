// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x47AE10:
//     CDFileClass::IsDisabled [EBX+0x54] (MOV AL,[EBX+0x54] @0x47AE26)
//     search-path list head   [0x89E410] (MOV EAX/EBP,[0x89E410]), each node
//       being { Next @+0x00 (MOV EBP,[EBP] @0x47AEC6), Path @+0x04
//       (MOV EDI,[EBP+0x4] @0x47AE59) }
//   direct base calls: BufferIOFileClass::SetFileName 0x431E80 (three CALLs)
//     and BufferIOFileClass::Exists 0x431F10 (PUSH 0; CALL; TEST AL,AL);
//   vtable slot dispatched: GetFileName +0x04 (CALL [EDX+0x4] @0x47AEE0 /
//     [EAX+0x4] @0x47AEF4). The 0x104-byte frame is one MAX_PATH scratch
//     buffer filled by the inlined strcpy/strcat (REPNE SCASB, REP MOVSD,
//     REP MOVSB).
//   The member run mirrors the already-confirmed layout in
//   match/platform/ccfile_class.h (not edited; re-declared here so the TU
//   stands alone); YRpp CCFileClass.h consulted for names only.
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_SET_NAME_METHODS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_SET_NAME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// GetFileName lands at slot +0x04.
// ---------------------------------------------------------------------------
class FileClass
{
public:
    virtual ~FileClass();                                          // slot 0  (+0x00)
    virtual const char* GetFileName() const;                       // slot 1  (+0x04)
    virtual const char* SetFileName(const char* pFileName);        // slot 2  (+0x08)
    virtual int  CreateFile();                                     // slot 3  (+0x0C)
    virtual int  DeleteFile();                                     // slot 4  (+0x10)
    virtual bool Exists(bool writeShared);                         // slot 5  (+0x14)
    virtual bool HasHandle();                                      // slot 6  (+0x18)
    virtual int  Open(FileAccessMode access);                      // slot 7  (+0x1C)
    virtual bool OpenEx(const char* pFileName, FileAccessMode a);  // slot 8  (+0x20)
    virtual int  ReadBytes(void* pBuffer, int nBytes);             // slot 9  (+0x24)
    virtual int  Seek(int offset, int mode);                       // slot 10 (+0x28)
    virtual int  GetFileSize();                                    // slot 11 (+0x2C)
    virtual int  WriteBytes(void* pBuffer, int nBytes);            // slot 12 (+0x30)
    virtual void Close();                                          // slot 13 (+0x34)
    virtual unsigned long GetFileTime();                           // slot 14 (+0x38)
    virtual bool SetFileTime(unsigned long fileTime);              // slot 15 (+0x3C)
    virtual void CDCheck(unsigned long code, bool b, const char* f);// slot 16 (+0x40)

    bool SkipCDCheck;     // +0x04
private:
    char padding_5[3];    // +0x05
};

class RawFileClass : public FileClass
{
public:
    FileAccessMode FileAccess;   // +0x08
    int   FilePointer;           // +0x0C
    int   FileSize;              // +0x10
    void* Handle;                // +0x14
    const char* FileName;        // +0x18
    short unknown_short_1C;      // +0x1C
    short unknown_short_1E;      // +0x1E
    bool  FileNameAllocated;     // +0x20
private:
    char  padding_21[3];         // +0x21
};

class BufferIOFileClass : public RawFileClass
{
public:
    // FUNCTION: GAMEMD 0x431E80 (decl; reloc) — the buffered-IO base rename.
    virtual const char* SetFileName(const char* pFileName);
    // FUNCTION: GAMEMD 0x431F10 (decl; reloc) — the buffered-IO base probe.
    virtual bool Exists(bool writeShared);

    bool unknown_bool_24;   // +0x24
    bool unknown_bool_25;   // +0x25
    bool unknown_bool_26;   // +0x26
    bool unknown_bool_27;   // +0x27
    bool unknown_bool_28;   // +0x28
    bool unknown_bool_29;   // +0x29
private:
    char padding_2A[2];     // +0x2A
public:
    unsigned int unknown_2C;   // +0x2C
    unsigned int unknown_30;   // +0x30
    unsigned int unknown_34;   // +0x34
    unsigned int unknown_38;   // +0x38
    unsigned int unknown_3C;   // +0x3C
    unsigned int unknown_40;   // +0x40
    int unknown_int_44;        // +0x44
    int unknown_int_48;        // +0x48
    unsigned int unknown_4C;   // +0x4C
    unsigned int unknown_50;   // +0x50
};

// One entry of the CD search-path list: the next node, then the directory
// prefix that is prepended to a bare file name.
struct SearchPath_0047AE10
{
    SearchPath_0047AE10* Next;   // +0x00
    const char*          Path;   // +0x04
};
GG_STATIC_ASSERT(offsetof(SearchPath_0047AE10, Next) == 0x0);
GG_STATIC_ASSERT(offsetof(SearchPath_0047AE10, Path) == 0x4);

// GLOBAL: GAMEMD 0x89E410 — head of the CD search-path list.
extern SearchPath_0047AE10* DAT_0089E410;

class CDFileClass : public BufferIOFileClass
{
public:
    // FUNCTION: GAMEMD 0x47AE10
    virtual const char* SetFileName(const char* pFileName);

    bool IsDisabled;        // +0x54
private:
    char padding_55[3];     // +0x55
};
GG_STATIC_ASSERT(offsetof(CDFileClass, IsDisabled) == 0x54);
GG_STATIC_ASSERT(sizeof(CDFileClass) == 0x58);

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_SET_NAME_METHODS_H
