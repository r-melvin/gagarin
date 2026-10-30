// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x5EF100..0x5EF2BF disassembled from the user's gamemd.exe v1.001. NullModemConnClass
//   (RTTI, vtable 0x7EEF90) derives from ConnectionClass (conn_types.h): the constructor chains to
//   0x48BE60 and allocates the packet buffer, the destructor frees it, and the compiler emits the
//   scalar deleting destructor 0x5EF290 and the vtable from them.

#include "../FUNCTION.H"
#include "transport/conn_types.h"

// VTABLE: GAMEMD 0x7EEF90
class NullModemConnClass : public ConnectionClass
{
public:
    NullModemConnClass(int sendSlots, int receiveSlots, int maxlen, unsigned short magic);
    virtual ~NullModemConnClass();
    void SetUnknown4C(int value);
    virtual void Init();
    // 0x5EF190 (slot 9, serial framing writer) is not matched; declared so the vtable references it.
    virtual int vf_9(void* buf, int buflen, void* extra, int extraLength,
                     bool is_global, unsigned short unknown_6);
    int   unknown_4C;   // +0x4C
    void* Buffer;       // +0x50
};

GG_STATIC_ASSERT(offsetof(NullModemConnClass, Buffer) == 0x50);

// FUNCTION: GAMEMD 0x5EF100
// Chains to the connection base (retry 60, -1, timeout 0x4B0) and allocates the packet buffer.
NullModemConnClass::NullModemConnClass(int sendSlots, int receiveSlots, int maxlen, unsigned short magic)
    : ConnectionClass(sendSlots, receiveSlots, maxlen, magic, 0x3C, -1, 0x4B0, 0)
{
    unknown_4C = -1;
    Buffer = operator new(MaxPacketLen + 0xB);
}

// SYNTHETIC: GAMEMD 0x5EF290
// The scalar deleting destructor is emitted by the compiler with the vtable; /Ob2 inlines the body below.

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

// FUNCTION: GAMEMD 0x5EF280
void NullModemConnClass::Init()
{
    ConnectionClass::Init();
}
