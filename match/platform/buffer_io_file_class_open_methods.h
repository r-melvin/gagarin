// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x431F70:
//     unknown_bool_25 [ESI+0x25]  (MOV byte [ESI+0x25],BL / 1)
//     unknown_bool_26 [ESI+0x26]  (CMP byte [ESI+0x26],BL; stores of 0 / 1)
//     unknown_bool_29 [ESI+0x29]  (CMP byte [ESI+0x29],BL; toggled around the
//                                  two virtual calls)
//     unknown_2C      [ESI+0x2C]  (MOV [ESI+0x2C],EAX = the access argument)
//     unknown_34      [ESI+0x34]  (CMP ECX,EDX with ECX=[ESI+0x48])
//     unknown_38/3C   [ESI+0x38]/[ESI+0x3C] zeroed on the way out
//     unknown_40/44   [ESI+0x40]/[ESI+0x44] set to -1 on the way out
//     unknown_int_48  [ESI+0x48]  zeroed when the access is 2
//     unknown_4C      [ESI+0x4C]  zeroed on the way out
//     unknown_50      [ESI+0x50]  (CMP [ESI+0x50],EBX; zeroed when access is 2)
//   vtable slots dispatched: Open +0x1C (CALL [EDX+0x1C] @0x432003) and
//     Close +0x34 (CALL [EAX+0x34] @0x431F91).
//   Direct (class-qualified) CALLs -> normalised relocs:
//     BufferIOFileClass::Commit  0x431DD0
//     RawFileClass::Open         0x65CB50
//     RawFileClass::Close        0x65CCA0
//   The first 0x44 bytes of 0x431F70 are BufferIOFileClass::Close (0x4325C0)
//   expanded inline; it is defined in-class here so cl inlines it the same way.
//   The member run mirrors match/platform/buffer_io_file_class_name_methods.h
//   (not edited; re-declared so this TU stands alone). YRpp CCFileClass.h was
//   consulted for the class/method names only; the YRpp map lists 0x431F70 as
//   CCFileClass::Open, but the bytes are the BufferIOFileClass layer (the
//   +0x24..+0x50 buffer members, the RawFileClass base calls), so it is named
//   BufferIOFileClass::Open here as the two sibling TUs already do.
#ifndef GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_OPEN_METHODS_H
#define GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_OPEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar. The matched body compares it with 1 and 2 and stores 3.
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// Open lands at slot +0x1C and Close at +0x34.
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

// ---------------------------------------------------------------------------
// RawFileClass — a real file in the game directory. Its Open/Close are the
// base implementations BufferIOFileClass::Open forwards to (direct CALLs).
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    // FUNCTION: GAMEMD 0x65CB50 (decl; reloc)
    virtual int  Open(FileAccessMode access);
    // FUNCTION: GAMEMD 0x65CCA0 (decl; reloc)
    virtual void Close();

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

// ---------------------------------------------------------------------------
// BufferIOFileClass — a file with an in-memory read buffer. Open (slot 7) is
// matched here; Close (slot 13) is defined in-class so that cl expands it
// inline at the top of Open exactly as retail did.
// ---------------------------------------------------------------------------
class BufferIOFileClass : public RawFileClass
{
public:
    // FUNCTION: GAMEMD 0x431F70
    virtual int  Open(FileAccessMode access);

    // FUNCTION: GAMEMD 0x4325C0 — BufferIOFileClass::Close, the body that
    // retail inlined into Open. With the buffer live the pending write-back
    // is committed first; an open file is then closed through the virtual
    // Close (with the buffer flag dropped around the call) when a buffer is
    // attached, or through the raw base otherwise.
    virtual void Close()
    {
        if (this->unknown_bool_29) {
            this->Commit();
            if (this->unknown_bool_26) {
                if (this->unknown_50 != 0) {
                    this->unknown_bool_29 = false;
                    this->Close();
                    this->unknown_bool_29 = true;
                    this->unknown_bool_26 = false;
                    this->unknown_bool_25 = false;
                } else {
                    RawFileClass::Close();
                    this->unknown_bool_26 = false;
                    this->unknown_bool_25 = false;
                }
            } else {
                this->unknown_bool_25 = false;
            }
        } else {
            RawFileClass::Close();
        }
    }

    // FUNCTION: GAMEMD 0x431DD0 (decl; reloc) — flush the write-back buffer.
    int Commit();

    bool unknown_bool_24;   // +0x24
    bool unknown_bool_25;   // +0x25
    bool unknown_bool_26;   // +0x26
    bool unknown_bool_27;   // +0x27
    bool unknown_bool_28;   // +0x28
    bool unknown_bool_29;   // +0x29
private:
    char padding_2A[2];     // +0x2A
public:
    unsigned int unknown_2C;   // +0x2C  the access the buffer was opened with
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

GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)              == 0x18);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_25)  == 0x25);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_26)  == 0x26);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_29)  == 0x29);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_2C)       == 0x2C);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_34)       == 0x34);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_38)       == 0x38);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_3C)       == 0x3C);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_40)       == 0x40);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_int_44)   == 0x44);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_int_48)   == 0x48);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_4C)       == 0x4C);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_50)       == 0x50);
GG_STATIC_ASSERT(sizeof(BufferIOFileClass) == 0x54);

#endif  // GG_MATCH_PLATFORM_BUFFER_IO_FILE_CLASS_OPEN_METHODS_H
