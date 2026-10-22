// Provenance: own-binary-via-Ghidra
//   Bytes, globals and strings read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x797C20 and 0x798140: eight global handle
//   tables ({count, capacity, data} at the addresses below), a one-shot
//   initialiser guarded by the byte at 0xB77E10 that refills them from a
//   function-local static array of sixteen handles (guard bit 0xB76954,
//   atexit thunk 0x798120), and the matching reset.
// 0x7AE5D0 is called, never expanded, here: only its declaration is visible.
#define GG_GROW_LIST_INSERT_DECL_ONLY
#include "grow_list.h"

// STRING: GAMEMD 0x84CD60 -- "01-W024.V01"
extern const char STR_0084CD60[];
// STRING: GAMEMD 0x84CD54 -- "01-W026.V01"
extern const char STR_0084CD54[];
// STRING: GAMEMD 0x84CD48 -- "01-W028.V01"
extern const char STR_0084CD48[];
// STRING: GAMEMD 0x84CD3C -- "01-W018.V01"
extern const char STR_0084CD3C[];
// STRING: GAMEMD 0x84CD30 -- "01-W020.V01"
extern const char STR_0084CD30[];
// STRING: GAMEMD 0x84CD24 -- "01-W022.V01"
extern const char STR_0084CD24[];
// STRING: GAMEMD 0x84CD18 -- "00-W022.V00"
extern const char STR_0084CD18[];
// STRING: GAMEMD 0x84CD0C -- "00-W024.V00"
extern const char STR_0084CD0C[];
// STRING: GAMEMD 0x84CD00 -- "00-W026.V00"
extern const char STR_0084CD00[];
// STRING: GAMEMD 0x84CCF4 -- "00-W017.V00"
extern const char STR_0084CCF4[];
// STRING: GAMEMD 0x84CCE8 -- "00-W018.V00"
extern const char STR_0084CCE8[];
// STRING: GAMEMD 0x84CCDC -- "00-W020.V00"
extern const char STR_0084CCDC[];
// STRING: GAMEMD 0x84CCD0 -- "01-W032.V01"
extern const char STR_0084CCD0[];
// STRING: GAMEMD 0x84CCC4 -- "01-W030.V01"
extern const char STR_0084CCC4[];
// STRING: GAMEMD 0x84CCB8 -- "00-W031.V00"
extern const char STR_0084CCB8[];
// STRING: GAMEMD 0x84CCAC -- "00-W029.V00"
extern const char STR_0084CCAC[];

// GLOBAL: GAMEMD 0xB73BD8 -- handle table.
extern GrowList<GrowListHandle> DAT_00B73BD8;
// GLOBAL: GAMEMD 0xB736F8 -- handle table.
extern GrowList<GrowListHandle> DAT_00B736F8;
// GLOBAL: GAMEMD 0xB76B00 -- handle table.
extern GrowList<GrowListHandle> DAT_00B76B00;
// GLOBAL: GAMEMD 0xB76510 -- handle table.
extern GrowList<GrowListHandle> DAT_00B76510;
// GLOBAL: GAMEMD 0xB73AE8 -- handle table.
extern GrowList<GrowListHandle> DAT_00B73AE8;
// GLOBAL: GAMEMD 0xB77820 -- handle table.
extern GrowList<GrowListHandle> DAT_00B77820;
// GLOBAL: GAMEMD 0xB73708 -- handle table.
extern GrowList<GrowListHandle> DAT_00B73708;
// GLOBAL: GAMEMD 0xB76188 -- handle table.
extern GrowList<GrowListHandle> DAT_00B76188;
// GLOBAL: GAMEMD 0xB77E10 -- the tables have been filled.
extern bool DAT_00B77E10;

// FUNCTION: GAMEMD 0x797C20
//
// Fill the eight tables once: name the sixteen static handles, empty every
// table, then push the handles to the front of their tables.
void FUN_00797C20()
{
    if (!DAT_00B77E10) {
        static GrowListHandle names[16];

        names[0] = STR_0084CD60;
        names[1] = STR_0084CD54;
        names[2] = STR_0084CD48;
        names[3] = STR_0084CD3C;
        names[4] = STR_0084CD30;
        names[5] = STR_0084CD24;
        names[6] = STR_0084CD18;
        names[7] = STR_0084CD0C;
        names[8] = STR_0084CD00;
        names[9] = STR_0084CCF4;
        names[10] = STR_0084CCE8;
        names[11] = STR_0084CCDC;
        names[12] = STR_0084CCD0;
        names[13] = STR_0084CCC4;
        names[14] = STR_0084CCB8;
        names[15] = STR_0084CCAC;

        for (int iA = 0; iA < DAT_00B73BD8.Count; iA++) {
            DAT_00B73BD8.Data[iA].~GrowListHandle();
        }
        DAT_00B73BD8.Count = 0;
        for (int iB = 0; iB < DAT_00B736F8.Count; iB++) {
            DAT_00B736F8.Data[iB].~GrowListHandle();
        }
        DAT_00B736F8.Count = 0;
        for (int iC = 0; iC < DAT_00B76B00.Count; iC++) {
            DAT_00B76B00.Data[iC].~GrowListHandle();
        }
        DAT_00B76B00.Count = 0;
        for (int iD = 0; iD < DAT_00B76510.Count; iD++) {
            DAT_00B76510.Data[iD].~GrowListHandle();
        }
        DAT_00B76510.Count = 0;
        for (int iE = 0; iE < DAT_00B73AE8.Count; iE++) {
            DAT_00B73AE8.Data[iE].~GrowListHandle();
        }
        DAT_00B73AE8.Count = 0;
        for (int iF = 0; iF < DAT_00B77820.Count; iF++) {
            DAT_00B77820.Data[iF].~GrowListHandle();
        }
        DAT_00B77820.Count = 0;
        for (int iG = 0; iG < DAT_00B73708.Count; iG++) {
            DAT_00B73708.Data[iG].~GrowListHandle();
        }
        DAT_00B73708.Count = 0;
        for (int iH = 0; iH < DAT_00B76188.Count; iH++) {
            DAT_00B76188.Data[iH].~GrowListHandle();
        }
        DAT_00B76188.Count = 0;

        DAT_00B73BD8.Insert(names[0], 0);
        DAT_00B73BD8.Insert(names[1], 0);
        DAT_00B73BD8.Insert(names[2], 0);
        DAT_00B76B00.Insert(names[3], 0);
        DAT_00B76B00.Insert(names[4], 0);
        DAT_00B76B00.Insert(names[5], 0);
        DAT_00B736F8.Insert(names[6], 0);
        DAT_00B736F8.Insert(names[7], 0);
        DAT_00B736F8.Insert(names[8], 0);
        DAT_00B76510.Insert(names[9], 0);
        DAT_00B76510.Insert(names[10], 0);
        DAT_00B76510.Insert(names[11], 0);
        DAT_00B73AE8.Insert(names[12], 0);
        DAT_00B73708.InlineAdd_00797C20(names[13]);
        DAT_00B77820.InlineAdd_00797C20(names[14]);
        DAT_00B76188.InlineAdd_00797C20(names[15]);
        DAT_00B77E10 = true;
    }
}

// FUNCTION: GAMEMD 0x798140
//
// Release every handle in the eight tables and mark them unfilled.
void FUN_00798140()
{
    for (int iA = 0; iA < DAT_00B73BD8.Count; iA++) {
        DAT_00B73BD8.Data[iA].Release();
    }
    DAT_00B73BD8.Count = 0;
    for (int iB = 0; iB < DAT_00B736F8.Count; iB++) {
        DAT_00B736F8.Data[iB].Release();
    }
    DAT_00B736F8.Count = 0;
    for (int iC = 0; iC < DAT_00B76B00.Count; iC++) {
        DAT_00B76B00.Data[iC].Release();
    }
    DAT_00B76B00.Count = 0;
    for (int iD = 0; iD < DAT_00B76510.Count; iD++) {
        DAT_00B76510.Data[iD].Release();
    }
    DAT_00B76510.Count = 0;
    for (int iE = 0; iE < DAT_00B73AE8.Count; iE++) {
        DAT_00B73AE8.Data[iE].Release();
    }
    DAT_00B73AE8.Count = 0;
    for (int iF = 0; iF < DAT_00B77820.Count; iF++) {
        DAT_00B77820.Data[iF].Release();
    }
    DAT_00B77820.Count = 0;
    for (int iG = 0; iG < DAT_00B73708.Count; iG++) {
        DAT_00B73708.Data[iG].Release();
    }
    DAT_00B73708.Count = 0;
    for (int iH = 0; iH < DAT_00B76188.Count; iH++) {
        DAT_00B76188.Data[iH].Release();
    }
    DAT_00B76188.Count = 0;
    DAT_00B77E10 = false;
}
