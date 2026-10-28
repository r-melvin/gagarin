// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x5EF150 and 0x5EF170 disassembled from the user's gamemd.exe v1.001. The class is
//   NullModemConnClass (RTTI, vtable 0x7EEF90) over ConnectionClass, whose destructor (0x48BEE0)
//   and Init (0x48BF10) are called out of line.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

class ConnectionClass
{
public:
    // FUNCTION: GAMEMD 0x48BEE0 (decl; reloc)
    ~ConnectionClass();
    // FUNCTION: GAMEMD 0x48BF10 (decl; reloc)
    virtual void Init();
    virtual void* DeletingDtor(unsigned int flags);
    char unknown_04[0x48];   // +0x04
    int unknown_4C;          // +0x4C
};

// VTABLE: GAMEMD 0x7EEF90
class NullModemConnClass : public ConnectionClass
{
public:
    ~NullModemConnClass();
    void SetUnknown4C(int value);
    virtual void* DeletingDtor(unsigned int flags);
    void* Buffer;   // +0x50
};

// FUNCTION: GAMEMD 0x5EF150
// Releases the packet buffer, then destroys the connection base.
NullModemConnClass::~NullModemConnClass()
{
    operator delete(Buffer);
}

// FUNCTION: GAMEMD 0x5EF170
// Runs the base initialisation and stores the argument at +0x4C.
void NullModemConnClass::SetUnknown4C(int value)
{
    ConnectionClass::Init();
    unknown_4C = value;
}
