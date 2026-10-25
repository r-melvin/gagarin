// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TechnoClass ctor FUN_0x006F2B40 (chains RadioClass ctor
//   FUN_0x0065A750 at offset 0). EVERY offset below is read directly from a
//   field-init write in that ctor — the whole 0xF0..0x51F span is covered, and
//   the last member DisguisedAsHouse @0x51C closes the object at 0x520. Key
//   confirmations from the ctor: Owner @0x21C (=param_1, the HouseClass*),
//   Ammo @0x2FC (=-1), TargetingTimer.TimeLeft @0x188 (=45), Tiberium
//   StorageClass ctor FUN_0x006C95E0(this+0x33C), UnloadTimer TransitionTimer
//   ctor FUN_0x004A50F0(this+0x350), BarrelFacing FacingClass ctor
//   FUN_0x004C91E0(this+0x370,3), the three DynamicVectorClass vptrs
//   @0x440/0x458/0x470 (PTR_FUN_007e4e78 / PTR_FUN_007e91ec), and the four
//   AudioController ctors FUN_0x00405BE0(this+0x488/0x4A4/0x4C0/0x4DC). The four
//   COM vptrs are written last (PTR_FUN_007f4960 et al). Cross-checked vs YRpp
//   (which static_asserts sizeof==0x520).
//
// TechnoClass — base of every buildable/ownable combat object (units,
// buildings, infantry, aircraft). Derives RadioClass at offset 0 and adds the
// enormous combat/veterancy/cloak/facing/targeting state block from 0xF0.
#ifndef GG_MATCH_LAYOUT_TECHNO_CLASS_H
#define GG_MATCH_LAYOUT_TECHNO_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "flasher_class.h"
#include "radio_class.h"      // RadioClass spine + CDTimerClass + CoordStruct + AudioController
#include "vector_class.h"     // VectorClass / DynamicVectorClass

// --- TechnoClass-side leaf components ---------------------------------------
// Self-guarded so a downstream layer (FootClass and the leaf classes) can reuse
// them. CDTimerClass / CoordStruct / AudioController come from the included
// chain (mission_class.h / object_class.h).

#include "stage_class.h"

// PassengersClass — transport occupant list head (sizeof = 8). Confirmed
// anchor: NumPassengers @0, FirstPassenger @4.
#ifndef GG_MATCH_LAYOUT_PASSENGERSCLASS_DEFINED
#define GG_MATCH_LAYOUT_PASSENGERSCLASS_DEFINED
class FootClass;
struct PassengersClass
{
    FootClass* RemoveFirstPassenger();                // GAMEMD 0x473430
    FootClass* GetFirstPassenger();                   // GAMEMD 0x473450: returns FirstPassenger
    int        GetTotalSize() const;                  // GAMEMD 0x473460
    void       RemovePassenger(FootClass* passenger); // GAMEMD 0x4734B0
    int        IndexOf(FootClass* candidate) const;   // GAMEMD 0x473500

    int   NumPassengers;     // +0x00
    void* FirstPassenger;    // +0x04  FootClass*
};
GG_STATIC_ASSERT(offsetof(PassengersClass, FirstPassenger) == 0x04);
GG_STATIC_ASSERT(sizeof(PassengersClass)                   == 8);
#endif

// VeterancyStruct — single packed promotion gauge (sizeof = 4).
#ifndef GG_MATCH_LAYOUT_VETERANCYSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_VETERANCYSTRUCT_DEFINED
struct VeterancyStruct
{
    // FUNCTION: GAMEMD 0x00750030 (decl; reloc)
    // VeterancyStruct::FUN_00750030
    int FUN_00750030() const;
    float Veterancy;   // +0x00
    // FUNCTION: GAMEMD 0x750010 (decl; reloc) -- ECX receiver, no stack arguments.
    bool FUN_00750010();
};
GG_STATIC_ASSERT(sizeof(VeterancyStruct) == 4);
#endif

// Point2D — 2D integer point (sizeof = 8).
#include "geometry2d.h"
GG_STATIC_ASSERT(sizeof(Point2D) == 8);

struct SHPStruct;
struct RectangleStruct;

// StorageClass — four-tiberium-type cargo cells (sizeof = 0x10). Owns the
// matched StorageClass::GetTotalValue @0x6C9600 family.
#include "../economy/storage_class.h"

// TransitionTimer — deploy/unload cycle timer (sizeof = 0x20; 8-aligned due to
// the leading double). Ctor FUN_0x004A50F0.
#ifndef GG_MATCH_LAYOUT_TRANSITIONTIMER_DEFINED
#define GG_MATCH_LAYOUT_TRANSITIONTIMER_DEFINED
struct TransitionTimer
{
    // Query methods on the deploy/undeploy state; no stack arguments, result in AL.
    // FUNCTION: GAMEMD 0x4A5110 (decl; reloc)
    bool FUN_004A5110();
    // FUNCTION: GAMEMD 0x4A5130 (decl; reloc)
    bool FUN_004A5130();
    // FUNCTION: GAMEMD 0x4A51B0 (decl; reloc)
    bool FUN_004A51B0();
    // FUNCTION: GAMEMD 0x4A51D0 (decl; reloc)
    bool FUN_004A51D0();
    // FUNCTION: GAMEMD 0x4A52F0 (decl; reloc) -- fraction of the transition done
    double PercentageDone();

    double        Rate1;         // +0x00
    CDTimerClass  ActionTimer;   // +0x08  (0xC)
    unsigned int  Rate2;         // +0x14
    unsigned char State1;        // +0x18  (bool)
    unsigned char State2;        // +0x19  (bool)
    unsigned char _pad_1A[6];    // +0x1A  (tail pad to the 8-byte size)
};
GG_STATIC_ASSERT(offsetof(TransitionTimer, ActionTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(TransitionTimer, Rate2)       == 0x14);
GG_STATIC_ASSERT(sizeof(TransitionTimer)                == 0x20);
#endif

#include "facing_class.h"

// TurretControl — recoil travel parameters (sizeof = 0x10).
#ifndef GG_MATCH_LAYOUT_TURRETCONTROL_DEFINED
#define GG_MATCH_LAYOUT_TURRETCONTROL_DEFINED
struct TurretControl
{
    int Travel;          // +0x00
    int CompressFrames;  // +0x04
    int RecoverFrames;   // +0x08
    int HoldFrames;      // +0x0C
};
GG_STATIC_ASSERT(sizeof(TurretControl) == 0x10);
#endif

// RecoilData — per-barrel/turret recoil animation state (sizeof = 0x20).
#ifndef GG_MATCH_LAYOUT_RECOILDATA_DEFINED
#define GG_MATCH_LAYOUT_RECOILDATA_DEFINED
struct RecoilData
{
    // FUNCTION: GAMEMD 0x70ECE0 (decl) -- starts the recoil travel (__thiscall).
    void Fire();

    TurretControl Turret;            // +0x00  (0x10)
    float         TravelPerFrame;    // +0x10
    float         TravelSoFar;       // +0x14
    unsigned int  State;             // +0x18  (RecoilState enum)
    int           TravelFramesLeft;  // +0x1C
};
GG_STATIC_ASSERT(offsetof(RecoilData, TravelPerFrame) == 0x10);
GG_STATIC_ASSERT(sizeof(RecoilData)                   == 0x20);
#endif

class PlanningTokenClass;
struct WeaponStruct;
struct CellStruct;
class CellClass;
class HouseClass;

// TechnoClass  (0xF0..0x51F, sizeof = 0x520)
// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass : public RadioClass, public FlasherClass, public StageClass
{
public:
    bool FUN_0043B150(); // ECX receiver, AL result, RET; render6D4766
    void FUN_004DC340(); // ECX receiver, RET; render6D478E
    // FUNCTION: GAMEMD 0x734270 (decl; reloc)
    // TechnoClass::ClearSidebarTabObject
    void ClearSidebarTabObject();
    // FUNCTION: GAMEMD 0x6F9E50 (decl; reloc)
    void FUN_006F9E50();
    // FUNCTION: GAMEMD 0x70DDC0 (decl; reloc)
    int FUN_0070DDC0();
    // FUNCTION: GAMEMD 0x70DDD0 (decl; reloc) -- one stack argument.
    void FUN_0070DDD0(int unknownStackArg0);
    // FUNCTION: GAMEMD 0x70DDF0 (decl; reloc)
    int FUN_0070DDF0();
    // FUNCTION: GAMEMD 0x705D20 (decl; reloc) -- the planning token this unit is on.
    PlanningTokenClass* FUN_00705D20();
    // Declaration: GAMEMD 0x6385C0 -- AL result, ordinary thiscall receiver.
    bool TryNextPlanningTokenNode();
    // FUNCTION: GAMEMD 0x70E260 (decl) -- non-virtual; true when the primary weapon slot names a type.
    int FUN_0070E260();
    // FUNCTION: GAMEMD 0x70DD00 (decl) -- non-virtual; latches CurrentTurretNumber into unknown_int_128 and reports a change.
    // FUNCTION: GAMEMD 0x70DC50 (decl) -- non-virtual; HasTurretTooltips of the type.
    bool FUN_0070DC50();
    // FUNCTION: GAMEMD 0x70DC60 (decl) -- non-virtual; the type's FUN_00717880.
    bool FUN_0070DC60();
    // FUNCTION: GAMEMD 0x70FED0 (decl) -- non-virtual; Drainable of the type.
    bool FUN_0070FED0();
    // FUNCTION: GAMEMD 0x70DE40 (decl) -- non-virtual; subtracts a1 from GattlingValue, flooring at 0.
    void FUN_0070DE40(int a1);
    // FUNCTION: GAMEMD 0x7018C0 (decl) -- non-virtual; sets Owner and the current-player flag.
    void FUN_007018C0(HouseClass* house);
    // FUNCTION: GAMEMD 0x709500 (decl) -- non-virtual; true for the listed CurrentMission values.
    int FUN_00709500();
    // FUNCTION: GAMEMD 0x70E1E0 (decl) -- non-virtual; is a1 a usable weapon index for this type.
    int FUN_0070E1E0(int a1);
    int FUN_0070DD00();
    // FUNCTION: GAMEMD 0x70F740 (decl) -- non-virtual; restarts TargetingTimer with a1 frames.
    void FUN_0070F740(int a1);
    // FUNCTION: GAMEMD 0x707CB0 (decl; reloc) -- kill the passengers (one
    // stack argument, the killer).
    void KillPassengers(TechnoClass* killer);
    void MarkPassengersAsExited();   // GAMEMD 0x7104C0
    void SetArchiveTarget(AbstractClass* target); // GAMEMD 0x70C610 (matched in core/techno_class_setters.cpp)
    // FUNCTION: GAMEMD 0x705E00 (decl; reloc) -- draws one shape at a screen
    // point inside a clip rectangle; sixteen stack arguments (RET 0x40).
    void FUN_00705E00(SHPStruct* shape, int frame, Point2D* point, RectangleStruct* clip,
                      int a5, int a6, int zAdjust, int a8, int a9, int zSort, int tint,
                      int a12, int a13, int a14, int a15, int a16);

    // Overrides of base slots (primary table 0x7F4960, 309 slots).
    virtual void vf_9();                                           // 9   0x6F3F40
    virtual bool vf_25();                                          // 25  0x6F32D0
    virtual bool vf_37();                                          // 37  0x701140 (table 0x7F4960 + 0x94)
    virtual bool vf_39();                                          // 39  0x7010D0: guarding with a live weapon
    virtual CoordStruct vf_44(int a1, int a2, int a3, int a4);     // 44  0x6F3AD0
    virtual bool vf_49();                                          // 49  0x41C010: returns Disguised
    virtual bool vf_50(HouseClass* house);                         // 50  0x41C020: returns Disguised
    virtual void vf_71();                                          // 71  0x6F4A40
    virtual void vf_86();                                          // 86  0x70E340
    virtual bool vf_88();                                          // 88  0x41BF40: IronCurtainTimer running
    virtual bool vf_102(HouseClass* house);                        // 102 0x6F4960
    virtual void vf_125(int mission, int a2, int a3);              // 125 0x7013A0

    // Slots 161-308, introduced by TechnoClass (RTTI ".?AVTechnoClass@@" on
    // 0x7F4960). Names are placeholders except where a tree row already carries
    // one; argument counts come from RET n. Return types are confirmed only for
    // slots with bodies in the tree; the rest are provisional (EAX/AL use).
    virtual bool vf_161();                                         // 161 0x41BEE0
    virtual bool IsCloakable();                                    // 162 0x70C5A0
    virtual bool FUN_006F3280();                                   // 163 0x6F3280
    virtual bool vf_164();                                         // 164 0x459D80
    virtual bool vf_165();                                         // 165 0x70BE80
    virtual bool vf_166();                                         // 166 0x6F9E10
    virtual bool vf_167();                                         // 167 0x41BEF0
    virtual bool vf_168();                                         // 168 0x6FBDC0
    virtual bool vf_169();                                         // 169 0x6FBC90
    virtual DirStruct vf_170();                                    // 170 0x4E0150
    virtual int IsArmed();                                         // 171 0x701120
    virtual void vf_172();                                         // 172 0x70C620
    virtual void vf_173();                                         // 173 0x708BC0
    virtual int vf_174();                                          // 174 0x708C30
    virtual void vf_175();                                         // 175 0x70ADA0
    virtual int vf_176();                                          // 176 0x708B40
    virtual bool vf_177(int a1);                                   // 177 0x459D90
    virtual void vf_178(int a1, int a2);                           // 178 0x6FDA00
    virtual void vf_179(int a1);                                   // 179 0x707F60
    virtual int vf_180();                                          // 180 0x6F3950
    virtual int vf_181();                                          // 181 0x41BF00
    virtual int vf_182();                                          // 182 0x41BF10
    virtual int vf_183();                                          // 183 0x41BF20
    virtual void vf_184();                                         // 184 0x70D980
    virtual int vf_185(AbstractClass* target);                         // 185 0x6F3330: the weapon index for a target
    virtual int vf_186(TechnoClass* other);                        // 186 0x6F3820
    virtual int vf_187();                                          // 187 0x704350
    virtual int vf_188();                                          // 188 0x459DA0
    virtual CellStruct vf_189();                                   // 189 0x459DB0
    virtual void vf_190(int a1);                                   // 190 0x459DC0
    virtual CellStruct vf_191(AbstractClass* target, int a2);         // 191 0x70AD50: forwards its first argument to slot 42
    virtual int vf_192(int a1, int a2);                            // 192 0x6F3D60
    virtual int vf_193(int a1, int a2);                            // 193 0x708C10
    virtual DirStruct vf_194();                                       // 194 0x708D70
    virtual int vf_195();                                          // 195 0x707D20
    virtual bool vf_196();                                          // 196 0x700D10
    virtual bool vf_197();                                         // 197 0x700D50
    virtual int vf_198(int a1);                                    // 198 0x6FCFA0
    virtual int vf_199(int a1);                                    // 199 0x707E60
    virtual bool vf_200();                                         // 200 0x459DD0
    virtual void vf_201(int a1);                                   // 201 0x70D1D0
    virtual bool vf_202();                                         // 202 0x70D420
    virtual bool vf_203(HouseClass* a1);                           // 203 0x70D460
    virtual bool vf_204();                                         // 204 0x41BF30
    virtual void vf_205();                                         // 205 0x459DE0
    virtual void vf_206(int a1, int a2, int a3);                   // 206 0x70F8F0
    virtual bool vf_207();                                         // 207 0x459DF0
    virtual bool vf_208();                                         // 208 0x459E00
    virtual bool vf_209();                                         // 209 0x459E10
    virtual bool vf_210();                                         // 210 0x459E20
    virtual bool vf_211();                                         // 211 0x459E30
    virtual bool vf_212();                                         // 212 0x701190
    virtual void vf_213(int a1);                                   // 213 0x708D90
    virtual void VoiceEnter();                                     // 214 0x709020
    virtual void VoiceHarvest();                                   // 215 0x709060
    virtual int vf_216();                                          // 216 0x708EB0
    virtual void VoiceCapture();                                   // 217 0x708DC0
    virtual int vf_218();                                          // 218 0x708FC0
    virtual void vf_219();                                         // 219 0x708E00
    virtual int vf_220(int a1);                                    // 220 0x7090A0
    virtual bool vf_221(int a1);                                   // 221 0x6FFE00
    virtual bool vf_222(int a1, AbstractClass* a2, void* a3, void* a4);            // 222 0x6FFBE0
    virtual bool IsUnderEMP();                                     // 223 0x70EFD0
    virtual bool vf_224();                                         // 224 0x459E40
    virtual bool vf_225();                                         // 225 0x41BF80
    virtual void vf_226(int a1);                                   // 226 0x41BF90
    virtual int vf_227();                                          // 227 0x70EFE0
    virtual int vf_228();                                          // 228 0x70D670
    virtual void vf_229(int a1);                                   // 229 0x710670
    virtual int vf_230(int a1);                                    // 230 0x70EF00
    virtual void vf_231(int a1, int a2);                           // 231 0x709820
    virtual void vf_232();                                         // 232 0x6FCD40
    virtual int vf_233(int a1);                                    // 233 0x6F7660
    virtual bool vf_234(AbstractClass* target, int weapon);            // 234 0x6F77B0: is the target in that weapon's range
    virtual bool IsCloseEnoughToAttack(AbstractClass* target);     // 235 0x6F7780
    virtual void vf_236(CoordStruct* a1);                                // 236 0x6F7930
    virtual void vf_237(int a1);                                   // 237 0x6F78D0
    virtual int vf_238();                                          // 238 0x4C9150
    virtual int vf_239(int a1, int a2);                            // 239 0x6FC090
    virtual bool vf_240(int a1, int a2, int a3);                   // 240 0x6FC0B0
    virtual AbstractClass* vf_241(unsigned int threat, CoordStruct* coord, bool a3); // 241 0x6F8DF0; FootClass 0x4D9920 tests the threat bits and the result pointer
    virtual void vf_242(int a1);                                   // 242 0x6FCDB0
    virtual int vf_243(int a1, int a2);                            // 243 0x6FDD50
    virtual void CancelAndGoIdle();                                // 244 0x70F850
    virtual bool vf_245(HouseClass* house, bool a2);               // 245 0x7014A0 (RET 8)
    virtual void vf_246(int a1, int a2, int a3);                   // 246 0x70B280
    virtual bool vf_247(int a1);                                   // 247 0x459E50
    virtual bool vf_248();                                         // 248 0x70DD50
    virtual int vf_249();                                          // 249 0x70DD70
    virtual int vf_250();                                          // 250 0x70DD90
    virtual int vf_251();                                          // 251 0x70DDA0
    virtual WeaponStruct* vf_252();                                      // 252 0x70E120
    virtual WeaponStruct* GetPrimaryWeapon();                      // 253 0x70E1A0
    virtual WeaponStruct* vf_254(int a1);                                 // 254 0x70E140
    virtual bool vf_255();                                         // 255 0x41BFA0
    virtual bool vf_256();                                         // 256 0x41BFB0
    virtual int vf_257();                                          // 257 0x41BFC0
    virtual int vf_258();                                          // 258 0x41BFD0
    virtual void vf_259();                                         // 259 0x701410
    virtual void vf_260(int a1);                                   // 260 0x6FB740
    virtual void vf_261();                                         // 261 0x6FB170
    virtual void vf_262();                                         // 262 0x6FB470
    virtual void vf_263();                                         // 263 0x70B570
    virtual void vf_264();                                         // 264 0x6F4EB0
    virtual void vf_265();                                         // 265 0x6FB010
    virtual void vf_266();                                         // 266 0x41BFE0
    virtual CoordStruct vf_267();                                     // 267 0x705CA0
    virtual bool vf_268();                                         // 268 0x705D50
    virtual bool vf_269(int a1);                                   // 269 0x41BFF0
    virtual void vf_270(int a1, int a2);                           // 270 0x459E60
    virtual void vf_271(int a1);                                   // 271 0x70ED80
    virtual bool vf_272(int a1);                                   // 272 0x70EE30
    virtual void vf_273(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10); // 273 0x706640
    virtual void vf_274(int a1, int a2);                           // 274 0x6F60C0
    virtual void vf_275(int a1, int a2, int a3);                   // 275 0x6F64A0
    virtual void vf_276(int a1, int a2, int a3);                   // 276 0x709A90
    virtual void vf_277(int a1, int a2);                           // 277 0x70A990
    virtual void vf_278(int a1, int a2, int a3);                   // 278 0x70AA60
    virtual void vf_279(int a1);                                   // 279 0x7036C0
    virtual void vf_280(int a1);                                   // 280 0x703770
    virtual int vf_281(int a1);                                    // 281 0x70D190
    virtual void vf_282();                                         // 282 0x41C000
    virtual unsigned long DisguiseAs(AbstractClass* target);       // 283 0x70E280
    virtual void vf_284();                                         // 284 0x41C030
    virtual bool IsTimeForIdleAction();                            // 285 0x7099E0
    virtual bool vf_286();                                         // 286 0x41C040
    virtual void vf_287(int a1);                                   // 287 0x709A20
    virtual void SetDestination(AbstractClass* target, bool a2);   // 288 0x709A30
    virtual bool EnterIdleMode(bool initial, bool a2);             // 289 0x709A40
    virtual void vf_290(int a1, int a2, int a3, int a4, int a5);   // 290 0x70AF50
    virtual void vf_291(int a1, int a2, int a3, int a4);           // 291 0x70B1D0
    virtual int vf_292();                                          // 292 0x4C9150
    virtual void vf_293();                                         // 293 0x70CC90
    virtual void vf_294();                                         // 294 0x70CCC0
    virtual void vf_295();                                         // 295 0x70CCF0
    virtual void vf_296(int a1);                                   // 296 0x70D990
    virtual int vf_297(int a1);                                    // 297 0x70F000
    virtual void vf_298();                                         // 298 0x70F010
    virtual bool vf_299();                                         // 299 0x70F020
    virtual bool vf_300();                                         // 300 0x70F030
    virtual int vf_301();                                          // 301 0x70F040
    virtual CoordStruct vf_302();                                  // 302 0x70F050
    virtual bool vf_303();                                         // 303 0x70F070
    virtual bool CanAttackOnTheMove();                             // 304 0x70F090
    virtual bool vf_305();                                         // 305 0x70F0E0
    virtual bool vf_306();                                         // 306 0x70F0F0
    virtual void vf_307();                                         // 307 0x70F100
    virtual bool vf_308();                                         // 308 0x70F110

    // +0xF0 FlasherClass base (8), +0xF8 StageClass base (0x1C): retail CHD
    // 0x80C058 lists both as non-polymorphic bases at mdisp 0xF0 / 0xF8.
    PassengersClass    Passengers;               // +0x114 (8)
    void*              Transporter;              // +0x11C TechnoClass*
    int                LastFireBulletFrame;      // +0x120 (ctor = -100)
    int                CurrentTurretNumber;      // +0x124 (ctor = -1)
    int                unknown_int_128;          // +0x128 (ctor = -1)
    void*              BehindAnim;               // +0x12C AnimClass*
    void*              DeployAnim;               // +0x130 AnimClass*
    unsigned char      InAir;                    // +0x134 (bool)
    unsigned char      align_135[3];             // +0x135
    int                CurrentWeaponNumber;      // +0x138
    int                CurrentRanking;           // +0x13C (Rank enum, ctor = -1)
    int                CurrentGattlingStage;     // +0x140
    int                GattlingValue;            // +0x144
    int                TurretAnimFrame;          // +0x148
    void*              InitialOwner;             // +0x14C HouseClass* (set late = param_1)
    VeterancyStruct    Veterancy;                // +0x150 (4; ctor FUN_0074FF30)
    unsigned int       align_154;                // +0x154 (aligns the double)
    double             ArmorMultiplier;          // +0x158 (ctor = 1.0)
    double             FirepowerMultiplier;      // +0x160 (ctor = 1.0)
    CDTimerClass       IdleActionTimer;          // +0x168 (0xC)
    CDTimerClass       RadarFlashTimer;          // +0x174 (0xC)
    CDTimerClass       TargetingTimer;           // +0x180 (0xC; TimeLeft ctor = 45)
    CDTimerClass       IronCurtainTimer;         // +0x18C (0xC)
    CDTimerClass       IronTintTimer;            // +0x198 (0xC)
    int                IronTintStage;            // +0x1A4 (ctor = 10)
    CDTimerClass       AirstrikeTimer;           // +0x1A8 (0xC)
    CDTimerClass       AirstrikeTintTimer;       // +0x1B4 (0xC)
    unsigned int       AirstrikeTintStage;       // +0x1C0
    int                ForceShielded;            // +0x1C4
    unsigned char      Deactivated;              // +0x1C8 (bool)
    unsigned char      align_1C9[3];             // +0x1C9
    void*              DrainTarget;              // +0x1CC TechnoClass*
    void*              DrainingMe;               // +0x1D0 TechnoClass*
    void*              DrainAnim;                // +0x1D4 AnimClass*
    bool               Disguised;                // +0x1D8
    unsigned char      align_1D9[3];             // +0x1D9
    unsigned int       DisguiseCreationFrame;    // +0x1DC
    CDTimerClass       InfantryBlinkTimer;       // +0x1E0 (0xC)
    CDTimerClass       DisguiseBlinkTimer;       // +0x1EC (0xC)
    unsigned char      UnlimboingInfantry;       // +0x1F8 (bool)
    unsigned char      align_1F9[3];             // +0x1F9
    CDTimerClass       ReloadTimer;              // +0x1FC (0xC)
    Point2D            RadarPosition;            // +0x208 (8)
    unsigned int       DisplayProductionTo;      // +0x210 (IndexBitfield<HouseClass*>)
    int                Group;                    // +0x214 (ctor = -1)
    AbstractClass*     ArchiveTarget;            // +0x218 (BuildingClass 0x459C20 calls its slot 11)
    HouseClass*        Owner;                    // +0x21C (ctor = param_1)
    int                CloakState;               // +0x220 (CloakState enum)
    StageClass         CloakProgress;            // +0x224 (0x1C)
    CDTimerClass       CloakDelayTimer;          // +0x240 (0xC)
    float              WarpFactor;               // +0x24C
    unsigned char      unknown_bool_250;         // +0x250 (bool)
    unsigned char      align_251[3];             // +0x251
    CoordStruct        LastSightCoords;          // +0x254 (0xC)
    int                LastSightRange;           // +0x260
    int                LastSightHeight;          // +0x264
    unsigned char      GapSuperCharged;          // +0x268 (bool)
    unsigned char      GeneratingGap;            // +0x269 (bool)
    unsigned char      align_26A[2];             // +0x26A
    int                GapRadius;                // +0x26C
    unsigned char      BeingWarpedOut;           // +0x270 (bool)
    unsigned char      WarpingOut;               // +0x271 (bool)
    unsigned char      unknown_bool_272;         // +0x272 (bool)
    unsigned char      unused_273;               // +0x273
    void*              TemporalImUsing;          // +0x274 TemporalClass*
    void*              TemporalTargetingMe;      // +0x278 TemporalClass*
    unsigned char      IsImmobilized;            // +0x27C (bool)
    unsigned char      align_27D[3];             // +0x27D
    unsigned int       unknown_280;              // +0x280
    int                ChronoLockRemaining;      // +0x284
    CoordStruct        ChronoDestCoords;         // +0x288 (0xC)
    void*              Airstrike;                // +0x294 AirstrikeClass*
    unsigned char      Berzerk;                  // +0x298 (bool)
    unsigned char      align_299[3];             // +0x299
    int                BerzerkDurationLeft;      // +0x29C
    unsigned int       SprayOffsetIndex;         // +0x2A0
    unsigned char      Uncrushable;              // +0x2A4 (bool)
    unsigned char      align_2A5[3];             // +0x2A5
    void*              DirectRockerLinkedUnit;   // +0x2A8 FootClass*
    void*              LocomotorTarget;          // +0x2AC FootClass*
    void*              LocomotorSource;          // +0x2B0 FootClass*
    AbstractClass*     Target;                   // +0x2B4
    void*              LastTarget;               // +0x2B8 AbstractClass*
    void*              CaptureManager;           // +0x2BC CaptureManagerClass*
    void*              MindControlledBy;         // +0x2C0 TechnoClass*
    unsigned char      MindControlledByAUnit;    // +0x2C4 (bool)
    unsigned char      align_2C5[3];             // +0x2C5
    void*              MindControlRingAnim;      // +0x2C8 AnimClass*
    void*              MindControlledByHouse;    // +0x2CC HouseClass*
    void*              SpawnManager;             // +0x2D0 SpawnManagerClass*
    void*              SpawnOwner;               // +0x2D4 TechnoClass*
    void*              SlaveManager;             // +0x2D8 SlaveManagerClass*
    void*              SlaveOwner;               // +0x2DC TechnoClass*
    void*              OriginallyOwnedByHouse;   // +0x2E0 HouseClass*
    TechnoClass*       BunkerLinkedItem;         // +0x2E4 (0x459470 clears the partner's own +0x2E4 link)
    float              PitchAngle;               // +0x2E8
    CDTimerClass       RearmTimer;               // +0x2EC (0xC)
    int                ChargeTurretDelay;        // +0x2F8
    int                Ammo;                     // +0x2FC (ctor = -1)
    int                Value;                    // +0x300
    void*              FireParticleSystem;       // +0x304 ParticleSystemClass*
    void*              SparkParticleSystem;      // +0x308
    void*              NaturalParticleSystem;    // +0x30C
    void*              DamageParticleSystem;     // +0x310
    void*              RailgunParticleSystem;    // +0x314
    void*              unk1ParticleSystem;       // +0x318
    void*              unk2ParticleSystem;       // +0x31C
    void*              FiringParticleSystem;     // +0x320
    void*              Wave;                     // +0x324 WaveClass*
    float              AngleRotatedSideways;     // +0x328
    float              AngleRotatedForwards;     // +0x32C
    float              RockingSidewaysPerFrame;  // +0x330
    float              RockingForwardsPerFrame;  // +0x334
    int                HijackerInfantryType;     // +0x338 (ctor = -1)
    StorageClass       Tiberium;                 // +0x33C (0x10; ctor FUN_006C95E0)
    unsigned int       unknown_34C;              // +0x34C
    TransitionTimer    UnloadTimer;              // +0x350 (0x20; ctor FUN_004A50F0)
    FacingClass        BarrelFacing;             // +0x370 (0x18)
    FacingClass        PrimaryFacing;            // +0x388 (0x18)
    FacingClass        SecondaryFacing;          // +0x3A0 (0x18)
    int                CurrentBurstIndex;        // +0x3B8
    CDTimerClass       TargetLaserTimer;         // +0x3BC (0xC)
    short              unknown_short_3C8;        // +0x3C8
    unsigned short     unknown_3CA;              // +0x3CA
    unsigned char      CountedAsOwned;           // +0x3CC (bool)
    unsigned char      IsSinking;                // +0x3CD (bool)
    unsigned char      WasSinkingAlready;        // +0x3CE (bool)
    unsigned char      unknown_bool_3CF;         // +0x3CF (bool)
    unsigned char      IsUseless;                // +0x3D0 (bool)
    unsigned char      HasBeenAttacked;          // +0x3D1 (bool)
    unsigned char      Cloakable;                // +0x3D2 (bool)
    unsigned char      IsPrimaryFactory;         // +0x3D3 (bool)
    unsigned char      Spawned;                  // +0x3D4 (bool)
    unsigned char      IsInPlayfield;            // +0x3D5 (bool)
    unsigned char      align_3D6[2];             // +0x3D6
    RecoilData         TurretRecoil;             // +0x3D8 (0x20)
    RecoilData         BarrelRecoil;             // +0x3F8 (0x20)
    unsigned char      IsTether;                 // +0x418 (bool)
    unsigned char      IsAlternativeTether;      // +0x419 (bool)
    unsigned char      IsOwnedByCurrentPlayer;   // +0x41A (bool)
    unsigned char      DiscoveredByCurrentPlayer;// +0x41B (bool)
    unsigned char      DiscoveredByComputer;     // +0x41C (bool)
    unsigned char      unknown_bool_41D;         // +0x41D (bool)
    unsigned char      unknown_bool_41E;         // +0x41E (bool)
    unsigned char      unknown_bool_41F;         // +0x41F (bool)
    char               SightIncrease;            // +0x420
    unsigned char      RecruitableA;             // +0x421 (bool, ctor = 1)
    unsigned char      RecruitableB;             // +0x422 (bool, ctor = 1)
    unsigned char      IsRadarTracked;           // +0x423 (bool)
    unsigned char      IsOnCarryall;             // +0x424 (bool)
    unsigned char      IsCrashing;               // +0x425 (bool)
    unsigned char      WasCrashingAlready;       // +0x426 (bool)
    unsigned char      IsBeingManipulated;       // +0x427 (bool)
    void*              BeingManipulatedBy;       // +0x428 TechnoClass*
    void*              ChronoWarpedByHouse;      // +0x42C HouseClass*
    unsigned char      unknown_bool_430;         // +0x430 (bool)
    unsigned char      IsMouseHovering;          // +0x431 (bool)
    unsigned char      ShouldBeReselectOnUnlimbo;// +0x432 (bool)
    unsigned char      align_433;                // +0x433
    void*              OldTeam;                  // +0x434 TeamClass*
    unsigned char      CountedAsOwnedSpecial;    // +0x438 (bool)
    unsigned char      Absorbed;                 // +0x439 (bool)
    unsigned char      unknown_bool_43A;         // +0x43A (bool)
    unsigned char      align_43B;                // +0x43B
    unsigned int       unknown_43C;              // +0x43C
    DynamicVectorClassLayout CurrentTargetThreatValues;// +0x440 (0x18; vptr 0x7E4E78)
    DynamicVectorClassLayout CurrentTargets;           // +0x458 (0x18; vptr 0x7E91EC)
    DynamicVectorClassLayout AttackedTargets;          // +0x470 (0x18; vptr 0x7E91EC)
    AudioController    TurretRotateSoundController; // +0x488 (0x14; ctor FUN_00405BE0)
    int                IsTurretRotateSoundPlaying;  // +0x49C (BOOL, ctor = 1)
    int                TurretIsRotating;            // +0x4A0 (BOOL)
    AudioController    GattlingSoundController;      // +0x4A4 (0x14; ctor FUN_00405BE0)
    unsigned char      IsGattlingSoundPlaying;       // +0x4B8 (bool)
    unsigned char      align_4B9[3];                 // +0x4B9
    unsigned int       unknown_4BC;                  // +0x4BC
    AudioController    UnusedGattlingSoundController; // +0x4C0 (0x14; ctor FUN_00405BE0)
    unsigned char      IsUnusedGattlingSoundPlaying; // +0x4D4 (bool)
    unsigned char      align_4D5[3];                 // +0x4D5
    unsigned int       unknown_4D8;                  // +0x4D8
    AudioController    QueuedVoiceSoundController;    // +0x4DC (0x14; ctor FUN_00405BE0)
    unsigned int       QueuedVoiceIndex;             // +0x4F0 (ctor = -1)
    unsigned int       unknown_4F4;                  // +0x4F4 (ctor = -1)
    unsigned char      unknown_bool_4F8;             // +0x4F8 (bool)
    unsigned char      align_4F9[3];                 // +0x4F9
    unsigned int       unknown_4FC;                  // +0x4FC
    void*              QueueUpToEnter;               // +0x500 TechnoClass*
    int                EMPLockRemaining;             // +0x504 (signed: 0x70EFD0 tests it with SETG)
    unsigned int       ThreatPosed;                  // +0x508
    unsigned int       ShouldLoseTargetNow;          // +0x50C
    void*              FiringRadBeam;                // +0x510 RadBeam*
    void*              PlanningToken;                // +0x514 PlanningTokenClass*
    ObjectTypeClass*   Disguise;                     // +0x518
    HouseClass*        DisguisedAsHouse;             // +0x51C

    // FUNCTION: GAMEMD 0x70D0D0 (decl; reloc) -- does this object have the ability (one stack argument).
    bool FUN_0070D0D0(int ability);
};

GG_STATIC_ASSERT(offsetof(TechnoClass, DurationRemaining)        == 0xF0);
GG_STATIC_ASSERT(offsetof(TechnoClass, HasChanged)               == 0xFC);
GG_STATIC_ASSERT(offsetof(TechnoClass, Passengers)               == 0x114);
GG_STATIC_ASSERT(offsetof(TechnoClass, Transporter)              == 0x11C);
GG_STATIC_ASSERT(offsetof(TechnoClass, InitialOwner)             == 0x14C);
GG_STATIC_ASSERT(offsetof(TechnoClass, Veterancy)                == 0x150);
GG_STATIC_ASSERT(offsetof(TechnoClass, ArmorMultiplier)          == 0x158);
GG_STATIC_ASSERT(offsetof(TechnoClass, TargetingTimer)           == 0x180);
GG_STATIC_ASSERT(offsetof(TechnoClass, IronTintStage)            == 0x1A4);
GG_STATIC_ASSERT(offsetof(TechnoClass, ReloadTimer)              == 0x1FC);
GG_STATIC_ASSERT(offsetof(TechnoClass, RadarPosition)            == 0x208);
GG_STATIC_ASSERT(offsetof(TechnoClass, Group)                    == 0x214);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner)                    == 0x21C);
GG_STATIC_ASSERT(offsetof(TechnoClass, CloakState)               == 0x220);
GG_STATIC_ASSERT(offsetof(TechnoClass, CloakProgress)            == 0x224);
GG_STATIC_ASSERT(offsetof(TechnoClass, LastSightCoords)          == 0x254);
GG_STATIC_ASSERT(offsetof(TechnoClass, Target)                   == 0x2B4);
GG_STATIC_ASSERT(offsetof(TechnoClass, MindControlledBy)         == 0x2C0);
GG_STATIC_ASSERT(offsetof(TechnoClass, SpawnManager)             == 0x2D0);
GG_STATIC_ASSERT(offsetof(TechnoClass, RearmTimer)               == 0x2EC);
GG_STATIC_ASSERT(offsetof(TechnoClass, Ammo)                     == 0x2FC);
GG_STATIC_ASSERT(offsetof(TechnoClass, FireParticleSystem)       == 0x304);
GG_STATIC_ASSERT(offsetof(TechnoClass, HijackerInfantryType)     == 0x338);
GG_STATIC_ASSERT(offsetof(TechnoClass, Tiberium)                 == 0x33C);
GG_STATIC_ASSERT(offsetof(TechnoClass, UnloadTimer)              == 0x350);
GG_STATIC_ASSERT(offsetof(TechnoClass, BarrelFacing)             == 0x370);
GG_STATIC_ASSERT(offsetof(TechnoClass, PrimaryFacing)            == 0x388);
GG_STATIC_ASSERT(offsetof(TechnoClass, SecondaryFacing)          == 0x3A0);
GG_STATIC_ASSERT(offsetof(TechnoClass, TargetLaserTimer)         == 0x3BC);
GG_STATIC_ASSERT(offsetof(TechnoClass, TurretRecoil)             == 0x3D8);
GG_STATIC_ASSERT(offsetof(TechnoClass, BarrelRecoil)             == 0x3F8);
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentTargetThreatValues)== 0x440);
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentTargets)           == 0x458);
GG_STATIC_ASSERT(offsetof(TechnoClass, AttackedTargets)          == 0x470);
GG_STATIC_ASSERT(offsetof(TechnoClass, TurretRotateSoundController) == 0x488);
GG_STATIC_ASSERT(offsetof(TechnoClass, GattlingSoundController)  == 0x4A4);
GG_STATIC_ASSERT(offsetof(TechnoClass, UnusedGattlingSoundController) == 0x4C0);
GG_STATIC_ASSERT(offsetof(TechnoClass, QueuedVoiceSoundController) == 0x4DC);
GG_STATIC_ASSERT(offsetof(TechnoClass, QueueUpToEnter)           == 0x500);
GG_STATIC_ASSERT(offsetof(TechnoClass, DisguisedAsHouse)         == 0x51C);
GG_STATIC_ASSERT(sizeof(TechnoClass)                             == 0x520);

#endif  // GG_MATCH_LAYOUT_TECHNO_CLASS_H
