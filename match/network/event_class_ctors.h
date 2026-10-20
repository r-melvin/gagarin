// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | YRpp-cross-check |
//             private-ref-cross-check
//   Every offset below was read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI, from the seven constructors at 0x4C6650,
//   0x4C6780, 0x4C6800, 0x4C6860, 0x4C68E0, 0x4C6B60 and 0x4C6C50:
//     * `MOV byte ptr [ESI],BL` / `MOV byte ptr [EAX],0x4` — Type at +0x00,
//       one byte.
//     * `MOV byte ptr [ESI+0x2],AL` and the failure arm's
//       `MOV byte ptr [ESI+0x2],0xFF` — HouseIndex at +0x02, one byte, and
//       -1 is its "no house" value. +0x01 is never written by any
//       constructor: it is the executed flag the queue drain sets.
//     * `MOV dword ptr [ESI+0x3],ECX` from `[0x00A8ED84]` — Frame at +0x03,
//       four bytes, *unaligned*, which pins the whole class to pack(1).
//     * every payload store lands at +0x07 or above, so the union starts at
//       +0x07.
//   The payload offsets, all confirmed store-by-store:
//     SellCell      +0x07 X, +0x09 Y            (two 16-bit stores)
//     Archive       +0x07 Whom1, +0x0C Whom2    (dword+byte each, stride 5)
//     Animation     +0x07 AnimID, +0x0B HouseID, +0x0F/+0x13 Location
//     MegaMission   +0x07 Whom, +0x0C Mission, (+0x0D gap), +0x0E Target,
//                   +0x13 Destination, +0x18 Follow, +0x1D IsPlanningEvent
//     MegaMissionF  +0x07 Whom, +0x0C Mission, +0x0D Target,
//                   +0x12 Destination, +0x17 Speed, +0x1B MaxSpeed
//     SpecialPlace  +0x07 ID, +0x0B Location
//     AddressChange +0x07 PlayerID, +0x08 Address
//     Special       +0x07 Special                (one dword)
//     Target        +0x07 Whom                   (dword+byte, one TargetClass)
//     General       +0x07 Data                   (one dword)
//     Place         +0x07 RTTI, +0x0B ID, +0x0F Extra, +0x13 Location
//   The PLACE payload is pinned by the four-argument family at 0x4C6970,
//   0x4C69E0, 0x4C6A60, 0x4C6AE0 and 0x4C6BE0, which write the same four
//   slots in the same order and differ only in how many of them come from
//   arguments: 0x4C69E0 hard-codes `MOV dword ptr [ESI+0xB],0xFFFFFFFF` and
//   `MOV dword ptr [ESI+0xF],0x0`, 0x4C6A60 hard-codes only the second, and
//   0x4C6AE0 hard-codes neither. The cell at +0x13 is copied as two word-width
//   moves in every one of them, so it is assigned field by field.
//   The 5-byte stride of the target stores (`LEA EDX,[ESI+0x7]; MOV [EDX],EAX;
//   MOV [EDX+0x4],CL`) is what fixes TargetClass at four bytes of ID plus one
//   byte of RTTI under pack(1); a by-value TargetClass parameter therefore
//   occupies two dwords of the argument frame, which is how the 0x18 and 0x28
//   `RET` immediates decompose.
//
//   Member and payload names are cross-checked against YRpp EventClass.h and
//   TargetClass.h (consult-only, no LICENSE — names only, offsets re-derived
//   above) and against RA1 CODE/EVENT.CPP (GPLv3 + EA Section-7), whose
//   constructor overload set RA2 kept and extended with the house-index guard
//   and the debug log. The private-reference seed (consult-only) supplied the
//   `network/event_class.cpp` grouping and the parameter semantics.
//
// EventClass — one queued multiplayer command. Constructors stamp the payload,
// the originating house and the frame the command must execute on.
#ifndef GG_MATCH_NETWORK_EVENT_CLASS_CTORS_H
#define GG_MATCH_NETWORK_EVENT_CLASS_CTORS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the frame counter every
// constructor stamps into Frame on both arms.
#include "../core/frame_counter.h"

// GLOBAL: GAMEMD 0x82091C — EventClass::EventNames, the 47-entry table the
// log line indexes by event type (`MOV ECX,[EAX*4 + 0x82091C]`).
extern const char* EventNames_0082091C[47];

// STRING: GAMEMD 0x820BF0 — "Adding event %s\n".
extern const char STR_00820BF0[];
// STRING: GAMEMD 0x820C04 — "Adding event ANIMATION\n".
extern const char STR_00820C04[];
// STRING: GAMEMD 0x820C1C — "Adding event MEGAMISSION_F\n".
extern const char STR_00820C1C[];

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink, __cdecl
// (the callers clean with `ADD ESP,4` / `ADD ESP,8`).
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

#pragma pack(push, 1)

// A network-portable object reference: a heap/cell id plus its RTTI tag.
struct TargetClass
{
    int           ID;     // +0x00
    unsigned char RTTI;   // +0x04
};

// Map cell coordinates as they travel inside an event payload.
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};

// The per-house special-options bitfield block. It travels as a single dword
// (`MOV dword ptr [EAX+0x7],ECX` at 0x4C65B4 from one pushed argument slot),
// so it is a struct rather than a plain int purely to keep the SPECIAL
// constructor distinguishable from the bare two-argument one at 0x4C66C0.
struct SpecialClass
{
    int Flags;   // +0x00
};

// RTTI tag as it travels inside a PLACE-family payload. An enum rather than an
// int so the four placement constructors do not collide with the SPECIAL_PLACE
// overload at 0x4C6B60; cl passes it in one dword either way.
enum RTTIType
{
    RTTI_NONE = 0
};

// A 32-bit coordinate pair (the animation payload's placement).
struct Point2D
{
    int X;   // +0x00
    int Y;   // +0x04
};

// IPXAddressClass — only the accessor the ADDRESSCHANGE constructor reaches.
// The retail body writes the four-byte network number through its first
// argument and six bytes of node address through its second.
class IPXAddressClass
{
public:
    // FUNCTION: GAMEMD 0x53EDA0 (decl; reloc) — IPXAddressClass::GetAddress.
    void GetAddress(unsigned char* net, unsigned char* node);
};

// Event type tags, named from YRpp / RA1 and valued from the immediates the
// constructors below store into Type.
#define EVENT_EMPTY            0
#define EVENT_MEGAMISSION      4
#define EVENT_MEGAMISSION_F    5
#define EVENT_ANIMATION        0x14
#define EVENT_SPECIAL          0x18
#define EVENT_ADDRESS_CHANGE   0x29

class EventClass
{
public:
    // Declared ascending by retail address.
    EventClass(int houseIndex, SpecialClass special);
    EventClass(int houseIndex, int eventType, TargetClass whom);
    EventClass(int houseIndex, int eventType, const CellStruct& cell);
    EventClass(int houseIndex, int eventType);
    EventClass(int houseIndex, int eventType, int data);
    EventClass(int houseIndex, int eventType, TargetClass src, TargetClass dest);
    EventClass(int houseIndex, int animId, void* house, const Point2D& coord);
    EventClass(int houseIndex, TargetClass src, unsigned char mission,
               TargetClass target, TargetClass destination, TargetClass follow);
    EventClass(int houseIndex, TargetClass src, unsigned char mission,
               TargetClass target, TargetClass destination, int speed,
               int maxSpeed);
    EventClass(int houseIndex, int eventType, RTTIType rtti, int id, int extra);
    EventClass(int houseIndex, int eventType, RTTIType rtti,
               const CellStruct& cell);
    EventClass(int houseIndex, int eventType, RTTIType rtti, int id,
               const CellStruct& cell);
    EventClass(int houseIndex, int eventType, RTTIType rtti, int id, int extra,
               const CellStruct& cell);
    EventClass(int houseIndex, int eventType, int id, const CellStruct& cell);
    EventClass(int houseIndex, int eventType, RTTIType rtti, int id);
    EventClass(int houseIndex, IPXAddressClass* address, char playerId);

    unsigned char Type;         // +0x00
    bool          IsExecuted;   // +0x01
    char          HouseIndex;   // +0x02
    unsigned int  Frame;        // +0x03

    union
    {
        char DataBuffer[104];

        struct SPECIAL
        {
            SpecialClass Special;        // +0x07
        } Special;

        struct TARGET_EVENT
        {
            TargetClass Whom;            // +0x07
        } Target;

        struct GENERAL
        {
            int Data;                    // +0x07
        } General;

        struct PLACE
        {
            int        RTTI;             // +0x07
            int        ID;               // +0x0B
            int        Extra;            // +0x0F
            CellStruct Location;         // +0x13
        } Place;

        struct SELLCELL
        {
            CellStruct Location;         // +0x07
        } SellCell;

        struct ARCHIVE
        {
            TargetClass Whom1;           // +0x07
            TargetClass Whom2;           // +0x0C
        } Archive;

        struct ANIMATION
        {
            int     AnimID;              // +0x07
            int     HouseID;             // +0x0B
            Point2D Location;            // +0x0F
        } Animation;

        struct MEGAMISSION
        {
            TargetClass   Whom;              // +0x07
            unsigned char Mission;           // +0x0C
            char          _gap_;             // +0x0D
            TargetClass   Target;            // +0x0E
            TargetClass   Destination;       // +0x13
            TargetClass   Follow;            // +0x18
            bool          IsPlanningEvent;   // +0x1D
        } MegaMission;

        struct MEGAMISSION_F
        {
            TargetClass   Whom;          // +0x07
            unsigned char Mission;       // +0x0C
            TargetClass   Target;        // +0x0D
            TargetClass   Destination;   // +0x12
            int           Speed;         // +0x17
            int           MaxSpeed;      // +0x1B
        } MegaMissionF;

        struct SPECIAL_PLACE
        {
            int        ID;               // +0x07
            CellStruct Location;         // +0x0B
        } SpecialPlace;

        struct ADDRESSCHANGE
        {
            char         PlayerID;       // +0x07
            unsigned int Address;        // +0x08
        } AddressChange;
    } Data;
};

#pragma pack(pop)

GG_STATIC_ASSERT(sizeof(TargetClass) == 5 && sizeof(CellStruct) == 4 &&
                 sizeof(Point2D) == 8);
GG_STATIC_ASSERT(offsetof(EventClass, Type)       == 0x00 &&
                 offsetof(EventClass, IsExecuted) == 0x01 &&
                 offsetof(EventClass, HouseIndex) == 0x02 &&
                 offsetof(EventClass, Frame)      == 0x03 &&
                 offsetof(EventClass, Data)       == 0x07);
GG_STATIC_ASSERT(offsetof(EventClass, Data.SellCell.Location)      == 0x07 &&
                 offsetof(EventClass, Data.Archive.Whom1)          == 0x07 &&
                 offsetof(EventClass, Data.Archive.Whom2)          == 0x0C &&
                 offsetof(EventClass, Data.Animation.AnimID)       == 0x07 &&
                 offsetof(EventClass, Data.Animation.HouseID)      == 0x0B &&
                 offsetof(EventClass, Data.Animation.Location)     == 0x0F);
GG_STATIC_ASSERT(offsetof(EventClass, Data.MegaMission.Whom)            == 0x07 &&
                 offsetof(EventClass, Data.MegaMission.Mission)         == 0x0C &&
                 offsetof(EventClass, Data.MegaMission.Target)          == 0x0E &&
                 offsetof(EventClass, Data.MegaMission.Destination)     == 0x13 &&
                 offsetof(EventClass, Data.MegaMission.Follow)          == 0x18 &&
                 offsetof(EventClass, Data.MegaMission.IsPlanningEvent) == 0x1D);
GG_STATIC_ASSERT(offsetof(EventClass, Data.MegaMissionF.Whom)        == 0x07 &&
                 offsetof(EventClass, Data.MegaMissionF.Mission)     == 0x0C &&
                 offsetof(EventClass, Data.MegaMissionF.Target)      == 0x0D &&
                 offsetof(EventClass, Data.MegaMissionF.Destination) == 0x12 &&
                 offsetof(EventClass, Data.MegaMissionF.Speed)       == 0x17 &&
                 offsetof(EventClass, Data.MegaMissionF.MaxSpeed)    == 0x1B);
GG_STATIC_ASSERT(offsetof(EventClass, Data.SpecialPlace.ID)         == 0x07 &&
                 offsetof(EventClass, Data.SpecialPlace.Location)   == 0x0B &&
                 offsetof(EventClass, Data.AddressChange.PlayerID)  == 0x07 &&
                 offsetof(EventClass, Data.AddressChange.Address)   == 0x08);
GG_STATIC_ASSERT(offsetof(EventClass, Data.Special.Special) == 0x07 &&
                 offsetof(EventClass, Data.Target.Whom)      == 0x07 &&
                 offsetof(EventClass, Data.General.Data)     == 0x07 &&
                 offsetof(EventClass, Data.Place.RTTI)       == 0x07 &&
                 offsetof(EventClass, Data.Place.ID)         == 0x0B &&
                 offsetof(EventClass, Data.Place.Extra)      == 0x0F &&
                 offsetof(EventClass, Data.Place.Location)   == 0x13);
GG_STATIC_ASSERT(sizeof(SpecialClass) == 4);
GG_STATIC_ASSERT(sizeof(EventClass) == 111);

#endif  // GG_MATCH_NETWORK_EVENT_CLASS_CTORS_H
