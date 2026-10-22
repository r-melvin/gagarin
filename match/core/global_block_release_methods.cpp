// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small leaf bodies that repeat byte for byte at many addresses, each bound to
// its own global: release of a counted heap block, release of a counted array
// of string objects, and address-of-global accessors. Globals are named by
// retail address and typed only as far as the instructions show (a count at
// +0x00, a heap pointer at +0x08 for the two release shapes). The same shape
// at other addresses belongs to other statics; each address here is verified
// separately against retail.
//
// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);
// FUNCTION: GAMEMD 0x007B46F0 (decl; reloc) -- string object destructor (this in ECX).
extern void __fastcall FUN_007B46F0(void* self);

struct CountedBlock {
    int count;          // +0x00
    int unknown_04;
    void* data;         // +0x08
};
struct CountedStringArray {
    int count;          // +0x00
    int unknown_04;
    unsigned char* data; // +0x08, elements of 4 bytes
};

extern CountedBlock DAT_00AC1DE0;
extern CountedBlock DAT_00B0BD50;
extern char DAT_00B2FF78;
extern CountedBlock DAT_00B72F38;
extern CountedBlock DAT_00B778D8;
extern CountedBlock DAT_00B73E10;
extern CountedBlock DAT_00B76AE0;
extern CountedBlock DAT_00B77900;
extern CountedBlock DAT_00B76520;
extern CountedStringArray DAT_00B777A0;
extern CountedStringArray DAT_00B73BD8;
extern CountedStringArray DAT_00B76510;
extern CountedStringArray DAT_00B73AE8;
extern CountedStringArray DAT_00B77820;
extern CountedStringArray DAT_00B73708;
extern CountedStringArray DAT_00B76188;
extern CountedStringArray DAT_00B73AA8;
extern CountedStringArray DAT_00B76980;
extern CountedStringArray DAT_00B779B0;
extern CountedStringArray DAT_00B76AD0;
extern CountedStringArray DAT_00B76970;
extern char DAT_00B77F70;
extern char DAT_00B77F78;
extern char DAT_0084E7C0;
extern char DAT_0084E7C4;


// FUNCTION: GAMEMD 0x006C6B60
void FUN_006C6B60()
{
    void* block = DAT_00B0BD50.data;
    DAT_00B0BD50.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x00775D90
void FUN_00775D90()
{
    void* block = DAT_00B72F38.data;
    DAT_00B72F38.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B920
void FUN_0077B920()
{
    void* block = DAT_00B778D8.data;
    DAT_00B778D8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B960
void FUN_0077B960()
{
    void* block = DAT_00B73E10.data;
    DAT_00B73E10.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B9A0
void FUN_0077B9A0()
{
    void* block = DAT_00B76AE0.data;
    DAT_00B76AE0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B9E0
void FUN_0077B9E0()
{
    void* block = DAT_00B77900.data;
    DAT_00B77900.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077BA20
void FUN_0077BA20()
{
    void* block = DAT_00B76520.data;
    DAT_00B76520.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C370
void FUN_0077C370()
{
    for (int i = 0; i < DAT_00B777A0.count; ++i)
        FUN_007B46F0(DAT_00B777A0.data + i * 4);
    void* block = DAT_00B777A0.data;
    DAT_00B777A0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C600
void FUN_0077C600()
{
    for (int i = 0; i < DAT_00B73BD8.count; ++i)
        FUN_007B46F0(DAT_00B73BD8.data + i * 4);
    void* block = DAT_00B73BD8.data;
    DAT_00B73BD8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C720
void FUN_0077C720()
{
    for (int i = 0; i < DAT_00B76510.count; ++i)
        FUN_007B46F0(DAT_00B76510.data + i * 4);
    void* block = DAT_00B76510.data;
    DAT_00B76510.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C780
void FUN_0077C780()
{
    for (int i = 0; i < DAT_00B73AE8.count; ++i)
        FUN_007B46F0(DAT_00B73AE8.data + i * 4);
    void* block = DAT_00B73AE8.data;
    DAT_00B73AE8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C7E0
void FUN_0077C7E0()
{
    for (int i = 0; i < DAT_00B77820.count; ++i)
        FUN_007B46F0(DAT_00B77820.data + i * 4);
    void* block = DAT_00B77820.data;
    DAT_00B77820.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C840
void FUN_0077C840()
{
    for (int i = 0; i < DAT_00B73708.count; ++i)
        FUN_007B46F0(DAT_00B73708.data + i * 4);
    void* block = DAT_00B73708.data;
    DAT_00B73708.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C8A0
void FUN_0077C8A0()
{
    for (int i = 0; i < DAT_00B76188.count; ++i)
        FUN_007B46F0(DAT_00B76188.data + i * 4);
    void* block = DAT_00B76188.data;
    DAT_00B76188.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C900
void FUN_0077C900()
{
    for (int i = 0; i < DAT_00B73AA8.count; ++i)
        FUN_007B46F0(DAT_00B73AA8.data + i * 4);
    void* block = DAT_00B73AA8.data;
    DAT_00B73AA8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C960
void FUN_0077C960()
{
    for (int i = 0; i < DAT_00B76980.count; ++i)
        FUN_007B46F0(DAT_00B76980.data + i * 4);
    void* block = DAT_00B76980.data;
    DAT_00B76980.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C9C0
void FUN_0077C9C0()
{
    for (int i = 0; i < DAT_00B779B0.count; ++i)
        FUN_007B46F0(DAT_00B779B0.data + i * 4);
    void* block = DAT_00B779B0.data;
    DAT_00B779B0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077CE70
void FUN_0077CE70()
{
    for (int i = 0; i < DAT_00B76AD0.count; ++i)
        FUN_007B46F0(DAT_00B76AD0.data + i * 4);
    void* block = DAT_00B76AD0.data;
    DAT_00B76AD0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077CED0
void FUN_0077CED0()
{
    for (int i = 0; i < DAT_00B76970.count; ++i)
        FUN_007B46F0(DAT_00B76970.data + i * 4);
    void* block = DAT_00B76970.data;
    DAT_00B76970.count = 0;
    gg_free(block);
}
