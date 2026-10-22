// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot offsets derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access + virtual-call disassembly),
//   cross-checked against YRpp (every offset reconfirmed numerically against the binary below).
//
// The FileClass hierarchy (the MIX/CD/raw file stack):
//   FileClass (abstract COM-ish base) -> RawFileClass -> BufferIOFileClass
//   -> CDFileClass -> CCFileClass.
//
// Confirmed offsets (from the matched bodies):
//   RawFileClass::FileName            [ECX+0x18]  (0x401940 GetFileName)
//   BufferIOFileClass::unknown_bool_25[ECX+0x25]  (0x4325A0 GetFileSize)
//   BufferIOFileClass::unknown_bool_29[ECX+0x29]  (0x431F10 Exists / 0x4325A0)
//   BufferIOFileClass::unknown_int_48 [ECX+0x48]  (0x4325A0 GetFileSize)
//   CCFileClass::Buffer (MemoryBuffer)[ESI+0x58]  (0x473CE0 Close)
//   CCFileClass::Position             [ESI+0x64]  (0x473CE0 Close)
// vtable slots (FileClass declaration order): SetFileName @ +0x08 (slot 2),
//   Open @ +0x1C (slot 7) — confirmed from CALL [EAX+0x8] / CALL [EDX+0x1C]
//   in CCFileClass::OpenEx (0x401980) and BufferIOFileClass::OpenEx (0x431F50).
#ifndef GG_MATCH_PLATFORM_CCFILE_CLASS_H
#define GG_MATCH_PLATFORM_CCFILE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"

// FileAccessMode is an unsigned-int flag enum in YRpp; modelled as a 4-byte
// scalar here (the only property the matched code uses is its 32-bit width).
class Obj_007B4620;
typedef unsigned int FileAccessMode;

// ---------------------------------------------------------------------------
// Shared owned-buffer layout and native constructor at 0x43AD00.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// FileClass — abstract base. Virtuals declared in exact retail vtable order so
// SetFileName lands at slot +0x08 and Open at slot +0x1C. Only the slots the
// matched code dispatches through are load-bearing; the rest pin their indices.
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
    virtual bool Open(FileAccessMode access);                      // slot 7  (+0x1C)
    virtual bool OpenEx(const char* pFileName, FileAccessMode a);  // slot 8  (+0x20)
    virtual int  ReadBytes(void* pBuffer, int nBytes);            // slot 9  (+0x24)
    virtual int  Seek(int offset, int mode);                       // slot 10 (+0x28)
    virtual int  GetFileSize();                                    // slot 11 (+0x2C)
    virtual int  WriteBytes(void* pBuffer, int nBytes);           // slot 12 (+0x30)
    virtual void Close();                                          // slot 13 (+0x34)
    virtual unsigned long GetFileTime();                           // slot 14
    virtual bool SetFileTime(unsigned long fileTime);             // slot 15
    virtual void CDCheck(unsigned long code, bool b, const char* f);// slot 16

    bool SkipCDCheck;     // +0x04
private:
    char padding_5[3];    // +0x05
};

// ---------------------------------------------------------------------------
// RawFileClass — a real file in the game directory.
// ---------------------------------------------------------------------------
class RawFileClass : public FileClass
{
public:
    virtual const char* GetFileName() const;   // GAMEMD 0x401940 (matched here)
    virtual bool Exists(bool writeShared);      // GAMEMD 0x65CBF0 (decl; base call)
    virtual int  GetFileSize();                 // GAMEMD 0x65D0D0 (decl; base call)
    virtual bool HasHandle();                   // GAMEMD 0x65D420 (matched)
    virtual bool OpenEx(const char* pFileName, FileAccessMode a); // GAMEMD 0x65CB30 (matched)
    virtual void CDCheck(unsigned long code, bool b, const char* f); // GAMEMD 0x65CA70 (matched)

    // Slots 14/15 retain RawFile implementations in CDFile table 0x7E1668.
    virtual unsigned long GetFileTime(); // GAMEMD 0x65D1F0
    virtual bool SetFileTime(unsigned long fileTime); // GAMEMD 0x65D240

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
// BufferIOFileClass — a file with an in-memory read buffer.
// ---------------------------------------------------------------------------
class BufferIOFileClass : public RawFileClass
{
public:
    virtual ~BufferIOFileClass();                                 // GAMEMD 0x431B80 (decl; reloc)
    virtual bool Exists(bool writeShared);                        // GAMEMD 0x431F10 (matched)
    virtual bool Open(FileAccessMode access);                     // GAMEMD 0x431F70 (decl; base call)
    virtual bool OpenEx(const char* pFileName, FileAccessMode a); // GAMEMD 0x431F50 (matched)
    virtual int  GetFileSize();                                   // GAMEMD 0x4325A0 (matched)
    virtual void Close();                                         // GAMEMD 0x4325C0 (decl; base call)

    // Overrides confirmed from CDFile table 0x7E1668, slots 6/9/10/12.
    virtual bool HasHandle(); // GAMEMD 0x431F30
    virtual int ReadBytes(void* pBuffer, int nBytes); // GAMEMD 0x4322A0
    virtual int Seek(int offset, int mode); // GAMEMD 0x4324B0
    virtual int WriteBytes(void* pBuffer, int nBytes); // GAMEMD 0x432050

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

// ---------------------------------------------------------------------------
// CDFileClass — a file fetched from a CD search path.
// ---------------------------------------------------------------------------
class CDFileClass : public BufferIOFileClass
{
public:
    CDFileClass();                                          // GAMEMD 0x47AA30 (decl; reloc)
    // Inline and empty: retail seats vtable 0x7E1668 before ~BufferIOFileClass.
    virtual ~CDFileClass() {}
    virtual const char* SetFileName(const char* pFileName); // GAMEMD 0x47AE10 (decl; base call)
    virtual bool Open(FileAccessMode access);               // GAMEMD 0x47AAB0 (matched)

    // Slot 8 of table 0x7E1668, distinct from BufferIOFileClass::OpenEx.
    virtual bool OpenEx(const char* pFileName, FileAccessMode a); // GAMEMD 0x47AF10

    bool IsDisabled;        // +0x54
private:
    char padding_55[3];     // +0x55
};

// MixFileClass::Offset @0x5B4430 — the MIX directory lookup, __fastcall with
// the filename in ECX and four out-parameters (YRpp declares them as
// references; retail is called here with five literal nulls, so they are
// modelled as pointers). Declared without a body; relocation-normalised.
bool MixFileClass_Offset(const char* filename, void** data,
                         void** mixfile, int* offset, int* length);

// ---------------------------------------------------------------------------
// CCFileClass — a file inside a MIX archive (the in-memory buffered case).
// ---------------------------------------------------------------------------
class CCFileClass : public CDFileClass
{
public:
    // FUNCTION: GAMEMD 0x4739F0
    CCFileClass(const char* pFileName);
    // FUNCTION: GAMEMD 0x473A30 (decl; reloc) -- the name from a Obj_007B4620
    // (0x7B5440 on the argument), RET 4.
    CCFileClass(const Obj_007B4620& name);
    // Inline: retail expands it in the deleting destructor 0x4019A0 and at
    // each stack instance (0x537BC0). The body clears Position, releases the
    // buffer through 0x43AE50, and ~CDFileClass then seats vtable 0x7E1668
    // and calls ~BufferIOFileClass (0x431B80).
    ~CCFileClass() { Position = 0; Buffer.Clear(); }

    virtual bool Exists(bool writeShared);                        // GAMEMD 0x473C50 (matched)
    virtual const char* SetFileName(const char* pFileName);       // GAMEMD 0x473FC0 (matched)
    virtual bool Open(FileAccessMode access);                     // GAMEMD 0x473D10 (decl)
    virtual bool OpenEx(const char* pFileName, FileAccessMode a); // GAMEMD 0x401980 (matched)
    virtual void Close();                                         // GAMEMD 0x473CE0 (matched)

    // Overrides confirmed slot-for-slot from table 0x7E16B0.
    virtual bool HasHandle(); // GAMEMD 0x473CD0, slot 6
    virtual int ReadBytes(void* pBuffer, int nBytes); // GAMEMD 0x473B10, slot 9
    virtual int Seek(int offset, int mode); // GAMEMD 0x473BA0, slot 10
    virtual int GetFileSize(); // GAMEMD 0x473C00, slot 11
    virtual int WriteBytes(void* pBuffer, int nBytes); // GAMEMD 0x473AE0, slot 12
    virtual unsigned long GetFileTime(); // GAMEMD 0x473E50, slot 14
    virtual bool SetFileTime(unsigned long fileTime); // GAMEMD 0x473F00, slot 15
    virtual void CDCheck(unsigned long code, bool b, const char* f); // GAMEMD 0x473AB0, slot 16

    MemoryBuffer Buffer;      // +0x58
    unsigned int Position;    // +0x64
    unsigned int Availability;// +0x68
};

// Explicit 17-slot prefix read from tables 0x7E16B0 and 0x7E1668.
// Concrete inherited targets are checked by verify_vtable; overrides replace
// these slots and add no new slots.
struct FileClassVtableSlots
{
    void* unknown_00;
    void* unknown_04;
    void* unknown_08;
    void* unknown_0C;
    void* unknown_10;
    void* unknown_14;
    void* unknown_18;
    void* unknown_1C;
    void* unknown_20;
    void* unknown_24;
    void* unknown_28;
    void* unknown_2C;
    void* unknown_30;
    void* unknown_34;
    void* unknown_38;
    void* unknown_3C;
    void* unknown_40;
};
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(FileClassVtableSlots, unknown_40) == 0x40);
GG_STATIC_ASSERT(sizeof(FileClassVtableSlots) == 0x44);

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RawFileClass, FileName)            == 0x18);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_25) == 0x25);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_bool_29) == 0x29);
GG_STATIC_ASSERT(offsetof(BufferIOFileClass, unknown_int_48)  == 0x48);
GG_STATIC_ASSERT(offsetof(CCFileClass, Buffer)              == 0x58);
GG_STATIC_ASSERT(offsetof(CCFileClass, Position)            == 0x64);
GG_STATIC_ASSERT(offsetof(CCFileClass, Availability)        == 0x68);
GG_STATIC_ASSERT(offsetof(RawFileClass, Handle)             == 0x14);
#endif

#endif  // GG_MATCH_PLATFORM_CCFILE_CLASS_H
