// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Event.CPP. The name is the source-file string at 0x820e44
//   in retail gamemd.exe v1.001, passed by the assert at 0x4c6e70 inside this object's
//   code range (0x4c6360-0x4c81ef). Functions are in ascending retail address order.
//
//             private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x4C65A0,
//   0x4C65E0, 0x4C6650, 0x4C66C0, 0x4C6720, 0x4C6780, 0x4C6800, 0x4C6860,
//   0x4C68E0, 0x4C6970, 0x4C69E0, 0x4C6A60, 0x4C6AE0, 0x4C6B60, 0x4C6BE0 and
//   0x4C6C50 via the local Ghidra disassembly. Layout confirmed numerically in
//   the header. Five of those (0x4C65A0, 0x4C69E0, 0x4C6A60, 0x4C6AE0 and
//   0x4C6BE0) are not in the Ghidra function list at all and were recovered by
//   decoding the raw bytes in the gaps between the listed ones.
//
//   The event-type constants are read off the name table at 0x82091C, which is
//   stored in descending order: slot 0 points at "EMPTY", slot 4 at
//   "MEGAMISSION", 0x14 at "ANIMATION", 0x18 at "SPECIAL" and 0x29 at
//   "ADDRESSCHANGE" — which is how the two constructors with a hard-coded Type
//   byte (0x4C65A0 and 0x4C6800) were named.
//
// EventClass constructors. Every one of them has the same skeleton: log the
// event, then either stamp a real event or blank the object out. The failure
// arm is reached by `TEST EAX,EAX; JL`, so the guard is a signed
// `houseIndex >= 0` test and -1 is the sentinel it writes back. Both arms end
// with their own copy of the frame stamp and their own epilogue, which is
// what the explicit else below produces.
//
// Functions ordered ascending by retail address.

#include "event_class_ctors.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E8818
extern const double DAT_007E8818;
// GLOBAL: GAMEMD 0x8A39A0
extern double DAT_008A39A0;
// GLOBAL: GAMEMD 0x8A39D8
extern double DAT_008A39D8;
// GLOBAL: GAMEMD 0x8A39E0
extern int DAT_008A39E0;
// GLOBAL: GAMEMD 0x8A39E4
extern int DAT_008A39E4;
// GLOBAL: GAMEMD 0x8A39E8
extern int DAT_008A39E8;
// GLOBAL: GAMEMD 0x8A39F0
extern double DAT_008A39F0;

// FUNCTION: GAMEMD 0x4C6390
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_004C6390()
{
    DAT_008A39F0 = DAT_008A39A0 / DAT_007E8818;
}

// FUNCTION: GAMEMD 0x4C63B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_004C63B0()
{
    DAT_008A39D8 = DAT_007E1718 / DAT_008A39F0;
}

// FUNCTION: GAMEMD 0x4C6530
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_004C6530()
{
    DAT_008A39E8 = 0;
    DAT_008A39E0 = 0x80;
    DAT_008A39E4 = 0x80;
}

// FUNCTION: GAMEMD 0x4C65A0  EventClass::EventClass(int, SpecialPayload)
// GLOBAL: GAMEMD 0xA8ED84
// SPECIAL — the per-house options block. It is the only constructor besides
// MEGAMISSION with no log call, and the prologue says so before the body does:
// no callee-saved push at all, `this` simply copied into EAX. The four-byte
// payload arrives in one argument slot and is stored with one dword move,
// which is the whole-struct assignment.
EventClass::EventClass(int houseIndex, SpecialPayload special)
{
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = EVENT_SPECIAL;
        Data.Special.Special = special;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C65E0  EventClass::EventClass(int, EventType, TargetClass)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// The single-target events (SELL, SCATTER, DEPLOY, PRIMARY and the rest). One
// TargetClass by value costs two argument dwords, so `RET 0x10` for what reads
// as three parameters, and the copy is the familiar `LEA EDX,[ESI+0x7];
// MOV [EDX],EAX; MOV [EDX+0x4],CL` dword-plus-byte pair.
EventClass::EventClass(int houseIndex, int eventType, TargetClass target)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Target.Whom = target;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6650  EventClass::EventClass(int, EventType, const CellStruct&)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// SELLCELL. The cell arrives by reference and retail copies it as two 16-bit
// moves. That is NOT what a pack(1) whole-struct assignment gives: cl copies a
// four-byte POD with a single dword move regardless of its declared alignment
// (40.0% measured that way). The two field assignments below are the only
// spelling that reproduces the word-width pair.
EventClass::EventClass(int houseIndex, int eventType, const CellStruct& cell)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.SellCell.Location.X = cell.X;
        Data.SellCell.Location.Y = cell.Y;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C66C0  EventClass::EventClass(int, EventType)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// The payload-free events (EXIT, IDLE, ALLCHEER, ABANDON_ALL...). Nothing is
// written above +0x03 on either arm, which is what makes the two arms
// otherwise identical bar the two constant bytes.
EventClass::EventClass(int houseIndex, int eventType)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6720  EventClass::EventClass(int, EventType, int)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// The one-dword events (GAMESPEED, OPTIONS, TIMING and friends). A single
// `MOV dword ptr [ESI+0x7],EDX` is the whole payload.
EventClass::EventClass(int houseIndex, int eventType, int data)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.General.Data = data;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6780  EventClass::EventClass(int, EventType, TargetClass, TargetClass)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// ARCHIVE / PLANNING_CONNECT. Both targets come by value; a 5-byte pack(1)
// struct still consumes two argument dwords each, which is where the `RET 0x18`
// comes from, and each is stored as a dword plus a byte off one `LEA` base.
EventClass::EventClass(int houseIndex, int eventType, TargetClass src,
                       TargetClass dest)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Archive.Whom1 = src;
        Data.Archive.Whom2 = dest;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6800  EventClass::EventClass(int, int, HouseClass*, const Point2D&)
// STRING: GAMEMD 0x820C04
// GLOBAL: GAMEMD 0xA8ED84
// ANIMATION. The event type is fixed here, so the log line is the literal
// message rather than a table lookup and there is no name-array read at all.
EventClass::EventClass(int houseIndex, int animId, void* house,
                       const Point2D& coord)
{
    FUN_004068E0(STR_00820C04);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = EVENT_ANIMATION;
        Data.Animation.AnimID = animId;
        Data.Animation.HouseID = (int)house;
        Data.Animation.LocationX = coord.X;
        Data.Animation.LocationY = coord.Y;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6860  EventClass::EventClass(int, TargetClass, Mission, TargetClass, TargetClass, TargetClass)
// GLOBAL: GAMEMD 0xA8ED84
// MEGAMISSION. Alone among the batch this one logs nothing, which is why it
// keeps `this` in EAX and saves no callee-saved register: with no call in the
// body there is nothing to preserve across. The planning flag at +0x1D is
// cleared explicitly.
EventClass::EventClass(int houseIndex, TargetClass src, unsigned char mission,
                       TargetClass target, TargetClass destination,
                       TargetClass follow)
{
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = EVENT_MEGAMISSION;
        Data.MegaMission.IsPlanningEvent = false;
        Data.MegaMission.Whom = src;
        Data.MegaMission.Mission = mission;
        Data.MegaMission.Target = target;
        Data.MegaMission.Destination = destination;
        Data.MegaMission.Follow = follow;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C68E0  EventClass::EventClass(int, TargetClass, Mission, TargetClass, TargetClass, int, int)
// STRING: GAMEMD 0x820C1C
// GLOBAL: GAMEMD 0xA8ED84
// MEGAMISSION_F — the formation-move variant. Its payload has no gap byte
// after Mission, so the three targets sit at +0x07, +0x0D and +0x12, five
// bytes apart, and the two speed overrides follow as plain dwords.
EventClass::EventClass(int houseIndex, TargetClass src, unsigned char mission,
                       TargetClass target, TargetClass destination, int speed,
                       int maxSpeed)
{
    FUN_004068E0(STR_00820C1C);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = EVENT_MEGAMISSION_F;
        Data.MegaMissionF.Whom = src;
        Data.MegaMissionF.Mission = mission;
        Data.MegaMissionF.Target = target;
        Data.MegaMissionF.Destination = destination;
        Data.MegaMissionF.Speed = speed;
        Data.MegaMissionF.MaxSpeed = maxSpeed;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6970  EventClass::EventClass(int, EventType, RTTIType, int, int)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// The cell-less member of the PLACE family: three plain dwords at +0x07,
// +0x0B and +0x0F and nothing at +0x13.
EventClass::EventClass(int houseIndex, int eventType, RTTIType rtti, int id,
                       int extra)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Place.RTTI = rtti;
        Data.Place.ID = id;
        Data.Place.Extra = extra;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C69E0  EventClass::EventClass(int, EventType, RTTIType, const CellStruct&)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// PLACE with only the RTTI tag and the cell supplied: the two unused payload
// slots are written anyway, as the immediates -1 and 0
// (`MOV dword ptr [ESI+0xB],0xFFFFFFFF; MOV dword ptr [ESI+0xF],0x0`), so the
// defaults belong in the body rather than in the caller.
EventClass::EventClass(int houseIndex, int eventType, RTTIType rtti,
                       const CellStruct& cell)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Place.RTTI = rtti;
        Data.Place.ID = -1;
        Data.Place.Extra = 0;
        Data.Place.Location.X = cell.X;
        Data.Place.Location.Y = cell.Y;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6A60  EventClass::EventClass(int, EventType, RTTIType, int, const CellStruct&)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// PLACE with a real object id; only the third slot keeps its zero default.
EventClass::EventClass(int houseIndex, int eventType, RTTIType rtti, int id,
                       const CellStruct& cell)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Place.RTTI = rtti;
        Data.Place.ID = id;
        Data.Place.Extra = 0;
        Data.Place.Location.X = cell.X;
        Data.Place.Location.Y = cell.Y;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6AE0  EventClass::EventClass(int, EventType, RTTIType, int, int, const CellStruct&)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// The fully-specified PLACE: every payload slot comes from an argument, which
// is what makes `RET 0x18` six argument dwords rather than five plus a
// default.
EventClass::EventClass(int houseIndex, int eventType, RTTIType rtti, int id,
                       int extra, const CellStruct& cell)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Place.RTTI = rtti;
        Data.Place.ID = id;
        Data.Place.Extra = extra;
        Data.Place.Location.X = cell.X;
        Data.Place.Location.Y = cell.Y;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6B60  EventClass::EventClass(int, EventType, int, const CellStruct&)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// SPECIAL_PLACE — an id plus a target cell, the cell again assigned field by
// field for the same reason as 0x4C6650 (48.6% as a whole-struct copy).
EventClass::EventClass(int houseIndex, int eventType, int id,
                       const CellStruct& cell)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.SpecialPlace.ID = id;
        Data.SpecialPlace.Location.X = cell.X;
        Data.SpecialPlace.Location.Y = cell.Y;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6BE0  EventClass::EventClass(int, EventType, RTTIType, int)
// STRING: GAMEMD 0x820BF0
// GLOBAL: GAMEMD 0x82091C
// GLOBAL: GAMEMD 0xA8ED84
// The shortest PLACE-family member: an RTTI tag and an id, no cell and no
// third slot, so nothing is written above +0x0E.
EventClass::EventClass(int houseIndex, int eventType, RTTIType rtti, int id)
{
    FUN_004068E0(STR_00820BF0, EventNames_0082091C[eventType & 0xFF]);
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = (unsigned char)eventType;
        Data.Place.RTTI = rtti;
        Data.Place.ID = id;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x4C6C50  EventClass::EventClass(int, IPXAddressClass*, char)
// GLOBAL: GAMEMD 0xA8ED84
// ADDRESSCHANGE. The eight bytes of frame (`SUB ESP,8`) are the node-address
// scratch buffer; the network-number argument is the address of the
// `houseIndex` parameter itself (`LEA ECX,[ESP+0x10]`), whose value the
// accessor overwrites and nobody reads again — an oddity of the retail source
// that has to be reproduced literally, because it is what keeps the parameter
// homed in its incoming slot. Only the first four bytes of the node address
// travel in the event.
EventClass::EventClass(int houseIndex, IPXAddressClass* address, char playerId)
{
    if (houseIndex >= 0) {
        HouseIndex = (char)houseIndex;
        Type = EVENT_ADDRESSCHANGE;
        unsigned char node[6];
        address->GetAddress((unsigned char*)&houseIndex, node);
        Data.AddressChange.Address = *(unsigned int*)node;
        Data.AddressChange.PlayerID = playerId;
        Frame = CurrentFrame;
    } else {
        HouseIndex = -1;
        Type = EVENT_EMPTY;
        Frame = CurrentFrame;
    }
}
