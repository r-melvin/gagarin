// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (Ghidra disasm at each
//   address below). Implemented on the canonical SlaveManagerClass.
//
// reccmp annotations (ascending by retail address):
//   FUNCTION: GAMEMD 0x6AF1A0  SlaveManagerClass::SlaveManagerClass(TechnoClass*, InfantryTypeClass*, int, int, int)
//   FUNCTION: GAMEMD 0x6AF360  SlaveManagerClass::SlaveManagerClass()
//   FUNCTION: GAMEMD 0x6AF440  SlaveManagerClass::SlaveManagerClass(NoInit)
//   FUNCTION: GAMEMD 0x6AF4A0  SlaveManagerClass::~SlaveManagerClass
//   FUNCTION: GAMEMD 0x6AF5F0  SlaveManagerClass::vf_23
//   FUNCTION: GAMEMD 0x6AF650  SlaveManagerClass::CreateSlave
//   FUNCTION: GAMEMD 0x6B0490  SlaveManagerClass::GuardAllSlaves
//   FUNCTION: GAMEMD 0x6B0750  SlaveManagerClass::FUN_006B0750
//   FUNCTION: GAMEMD 0x6B0A20  SlaveManagerClass::LostSlave
//   FUNCTION: GAMEMD 0x6B0A90  SlaveManagerClass::LostSlave(int)
//   FUNCTION: GAMEMD 0x6B0AE0  SlaveManagerClass::FUN_006B0AE0
//   FUNCTION: GAMEMD 0x6B0CC0  SlaveManagerClass::SetStateIdle1
//   FUNCTION: GAMEMD 0x6B0D10  SlaveManagerClass::SetStateIdle4

#include "FUNCTION.H"
#include "slave_manager_class_methods.h"

// GLOBAL: GAMEMD 0xB0B5B8 -- the invalid cell.
extern CellStruct DAT_00B0B5B8;

// FUNCTION: GAMEMD 0x6A46D0 (decl; reloc) -- the house type index of a name.
int FUN_006A46D0(const char* name);

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- plays a sound at a position (index in ECX, coordinate in EDX, RET 4).
void FUN_007509E0(int sound, const CoordStruct* where, void* unused);

// GLOBAL: GAMEMD 0xA8E9A0 -- the game-active byte.
extern unsigned char DAT_00A8E9A0;

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero suppresses the EVA line.
extern int DAT_00A8E7AC;

// GLOBAL: GAMEMD 0xB0B5F0 -- the slave manager array.
extern DynamicVectorClass<SlaveManagerClass*> DAT_00B0B5F0;

// FUNCTION: GAMEMD 0x6AF1A0
// Full constructor: record the owner, slave type and rates, create SlaveCount
// slave nodes (each with its slave), start the respawn timer at 10 frames and
// register in the global array.
SlaveManagerClass::SlaveManagerClass(TechnoClass* owner, InfantryTypeClass* slaveType,
                                     int slaveCount, int regenRate, int reloadRate)
    : SlaveNodes(0, 0), RespawnTimer(0)
{
    Owner = owner;
    SlaveType = slaveType;
    SlaveCount = slaveCount;
    RegenRate = regenRate;
    ReloadRate = reloadRate;
    for (int i = 0; i < SlaveCount; ++i) {
        SlaveControl* node = new SlaveControl;
        CreateSlave(node);
        SlaveNodes.AddItem(node);
    }
    RespawnTimer = CDTimerClass(10);
    State = 0;
    LastScanFrame = 0;
    DAT_00B0B5F0.AddItem(this);
}

// FUNCTION: GAMEMD 0x6AF360
// Default constructor: an unowned manager with no slaves, registered in the
// global array.
SlaveManagerClass::SlaveManagerClass()
    : SlaveNodes(0, 0), RespawnTimer(0)
{
    Owner = 0;
    SlaveType = 0;
    SlaveCount = 0;
    RegenRate = 0;
    ReloadRate = 0;
    RespawnTimer = CDTimerClass(0);
    State = 0;
    LastScanFrame = 0;
    DAT_00B0B5F0.AddItem(this);
}

// FUNCTION: GAMEMD 0x6AF440
// NoInit constructor (save-game load path): base NoInit constructor, an empty
// growable node vector (step 10), the respawn timer started at the current
// frame with no time left, and the four COM vtable pointers.
SlaveManagerClass::SlaveManagerClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), SlaveNodes(0, 0), RespawnTimer(0)
{
}

static inline void ResetNodeVector(DynamicVectorClass<SlaveManagerClass::SlaveControl*>* v)
{
    int capacity = v->Capacity;
    v->Clear();
    v->SetCapacity(capacity, 0);
}

// FUNCTION: GAMEMD 0x6AF4A0
// Destructor body: delete every slave node back to front, release the node
// vector, and leave the global slave manager array.
//
// PARTIAL: 91.8% -- instruction multiset identical; the SlaveNodes.Count load is scheduled above the four vptr stores, retail loads it after them.
SlaveManagerClass::~SlaveManagerClass()
{
    for (int i = this->SlaveNodes.Count; --i >= 0;) {
        if (this->SlaveNodes.Items[i])
            delete this->SlaveNodes.Items[i];
    }
    ResetNodeVector(&this->SlaveNodes);
    DAT_00B0B5F0.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6AF5F0
// When the respawn timer has run out, restart it for 10 frames and, if the
// manager still has an owner, run its two update passes.
void SlaveManagerClass::vf_23()
{
    if (this->RespawnTimer.GetTimeLeft() == 0) {
        this->RespawnTimer = CDTimerClass(10);
        if (this->Owner) {
            this->FUN_006AF6C0();
            this->FUN_006AFD60();
        }
    }
}


// FUNCTION: GAMEMD 0x6AF650
// Create one slave from the manager's owner house, then initialize the new
// InfantryClass and start its node timer.
void SlaveManagerClass::CreateSlave(SlaveControl* Control)
{
    Control->Slave = static_cast<InfantryClass*>(this->SlaveType->vf_35(this->Owner->vf_15()));
    if (Control->Slave) {
        Control->Slave->vf_53();
        Control->Slave->SlaveOwner = this->Owner;
        Control->State = 0;
        CDTimerClass timer(0);
        Control->RespawnTimer = timer;
    }
}

// FUNCTION: GAMEMD 0x6B0490
// Order every live slave (State != Dead(6), Slave != null) back to Guard via
// vtable+0x3D0, walking the SlaveNodes vector back-to-front.
void SlaveManagerClass::GuardAllSlaves()
{
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        ::SlaveControl* node = ((::SlaveControl**)this->SlaveNodes.Items)[i];
        int state = node->State;
        SlaveObject* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->GuardSlot();
    }
}

// FUNCTION: GAMEMD 0x6B0750
// The cell just north of the owner's cell (moved to its far foundation corner
// for a building), or the invalid cell unless the owner stands on that cell.
//
// PARTIAL: 85.9% -- retail frame is 0x18: the 0x42D510 result sits in its own temporary apart from the cell variable.
Cell SlaveManagerClass::FUN_006B0750()
{
    if (!this->Owner || this->Owner->vf_11() != 6)
        return DAT_00B0B5B8;
    CellStruct cell;
    if (this->Owner && this->Owner->vf_11() == 6) {
        BuildingClass* building = (BuildingClass*)this->Owner->KindCast_00459F40(6);
        CellStruct offset;
        offset.X = building->Type->GetFoundationWidth() - 1;
        offset.Y = building->Type->GetFoundationHeight(false) / 2;
        cell = this->Owner->vf_110().FUN_0042D510(offset);
    } else {
        cell = this->Owner->vf_110();
    }
    CellStruct probe;
    probe.X = cell.X;
    probe.Y = cell.Y - 1;
    CellStruct target = probe;
    CellClass* cellClass = DAT_0087F7E8.FUN_005657A0(&target);
    if (cellClass->GetBuilding() == (BuildingClass*)this->Owner)
        return target;
    return DAT_00B0B5B8;
}

// FUNCTION: GAMEMD 0x6B0A20
// Search from the back of the SlaveNodes array. Clear the slave's manager
// back-link, empty the node, mark it Dead, and restart its respawn timer.
void SlaveManagerClass::LostSlave(SlaveObject* slave)
{
    for (int i = SlaveNodes.Count - 1; i >= 0; --i) {
        if (((::SlaveControl**)SlaveNodes.Items)[i]->Slave == slave) {
            ::SlaveControl* node = ((::SlaveControl**)SlaveNodes.Items)[i];
            if (node->Slave)
                node->Slave->SlaveOwner = 0;
            node->Slave = 0;
            node->State = 6;
            node->RespawnTimer = SlaveTimerClass(RegenRate);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x6B0A90
// LostSlave by node index: same detach as above without the search.
void SlaveManagerClass::LostSlave(int index)
{
    SlaveControl* node = this->SlaveNodes.Items[index];
    if (node->Slave)
        node->Slave->SlaveOwner = 0;
    node->Slave = 0;
    node->State = 6;
    node->RespawnTimer = CDTimerClass(this->RegenRate);
}

// FUNCTION: GAMEMD 0x6B0AE0
// Release every slave: dismount them to the killer's house (or the forced
// house, else Civilian) or, with no house at all, kill them with the C4
// warhead; then play the slaves-freed sound at the first freed slave and
// forget the owner.
void SlaveManagerClass::FUN_006B0AE0(TechnoClass* killer, HouseClass* forced)
{
    if (!this->Owner)
        return;
    int houseCount = HouseClass_Array.Count;
    HouseClass* civilian = 0;
    int civilianIndex = FUN_006A46D0("Civilian");
    for (int h = 0; h < houseCount; ++h) {
        if (HouseClass_Array.Items[h]->Type->SideIndex == civilianIndex) {
            civilian = HouseClass_Array.Items[h];
            break;
        }
    }
    InfantryClass* first = 0;
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        InfantryClass* slave = this->SlaveNodes.Items[i]->Slave;
        if (slave && DAT_00A8E9A0) {
            bool inLimbo = slave->InLimbo;
            slave->SlaveOwner = 0;
            if (inLimbo) {
                slave->vf_56(killer);
                slave->vf_62();
            } else {
                HouseClass* house;
                bool dismount = true;
                if (killer) {
                    house = killer->Owner;
                } else {
                    house = forced;
                    if (!house) {
                        house = civilian;
                        if (!house)
                            dismount = false;
                    }
                }
                if (dismount) {
                    slave->vf_245(house, true);
                    slave->CancelAndGoIdle();
                    slave->vf_226(1);
                    if (!first)
                        first = slave;
                } else {
                    int damage = slave->Health;
                    slave->vf_91(&damage, 0, RulesInstance->C4Warhead, 0, false, false, 0);
                }
            }
        }
    }
    if (DAT_00A8E9A0 && first && !DAT_00A8E7AC && RulesInstance->SlavesFreeSound != -1) {
        CoordStruct where = first->Location;
        FUN_007509E0(RulesInstance->SlavesFreeSound, &where, 0);
    }
    this->Owner = 0;
}

// FUNCTION: GAMEMD 0x6B0CC0
// If the manager is Ready (State 0), switch it to state 1 and send every live
// slave (State != Dead(6), Slave != null) to CancelAndGoIdle, back to front.
//
// PARTIAL: 84.6% -- same prologue scheduling as AllGuard 0x6B0C80: the
// optimiser hoists the SlaveNodes.Count load above the two stores; retail
// stores first. Instruction multiset is identical.
void SlaveManagerClass::SetStateIdle1()
{
    if (this->State != 0)
        return;
    this->State = 1;
    this->LastScanFrame = 0x7FFFFFFF;
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        SlaveControl* node = this->SlaveNodes.Items[i];
        int state = node->State;
        InfantryClass* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->CancelAndGoIdle();
    }
}

// FUNCTION: GAMEMD 0x6B0D10
// Same as SetStateIdle1 but switches the manager to state 4.
//
// PARTIAL: 84.6% -- same scheduling residual as SetStateIdle1.
void SlaveManagerClass::SetStateIdle4()
{
    if (this->State != 0)
        return;
    this->State = 4;
    this->LastScanFrame = 0x7FFFFFFF;
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        SlaveControl* node = this->SlaveNodes.Items[i];
        int state = node->State;
        InfantryClass* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->CancelAndGoIdle();
    }
}

// SYNTHETIC: GAMEMD 0x6B1390 -- SlaveManagerClass scalar deleting destructor,
// emitted by the compiler from the virtual destructor.
