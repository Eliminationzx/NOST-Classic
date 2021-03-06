/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _SPELLENTRY_H
#define _SPELLENTRY_H

#include <array>
#include "DBCStructure.h"
#include "SharedDefines.h"

// Diminishing Returns interaction with spells
bool IsDiminishingReturnsGroupDurationLimited(DiminishingGroup group);
DiminishingReturnsType GetDiminishingReturnsGroupType(DiminishingGroup group);
float GetDiminishingRate(uint32 type);

class SpellEntry
{
    public:
        SpellEntry() = default;
        ~SpellEntry() = default;
        void InitCachedValues();


        /// DBC DATA:
        uint32    Id = 0;                                          // 0
        uint32    School = 0;                                      // 1
        uint32    Category = 0;                                    // 2
      //uint32    castUI;                                          // 3 not used
        uint32    Dispel = 0;                                      // 4
        uint32    Mechanic = 0;                                    // 5
        uint32    Attributes = 0;                                  // 6
        uint32    AttributesEx = 0;                                // 7
        uint32    AttributesEx2 = 0;                               // 8
        uint32    AttributesEx3 = 0;                               // 9
        uint32    AttributesEx4 = 0;                               // 10
        uint32    Stances = 0;                                     // 11
        uint32    StancesNot = 0;                                  // 12
        uint32    Targets = 0;                                     // 13
        uint32    TargetCreatureType = 0;                          // 14
        uint32    RequiresSpellFocus = 0;                          // 15
        uint32    CasterAuraState = 0;                             // 16
        uint32    TargetAuraState = 0;                             // 17
        uint32    CastingTimeIndex = 0;                            // 18
        uint32    RecoveryTime = 0;                                // 19
        uint32    CategoryRecoveryTime = 0;                        // 20
        uint32    InterruptFlags = 0;                              // 21
        uint32    AuraInterruptFlags = 0;                          // 22
        uint32    ChannelInterruptFlags = 0;                       // 23
        uint32    procFlags = 0;                                   // 24
        uint32    procChance = 0;                                  // 25
        uint32    procCharges = 0;                                 // 26
        uint32    maxLevel = 0;                                    // 27
        uint32    baseLevel = 0;                                   // 28
        uint32    spellLevel = 0;                                  // 29
        uint32    DurationIndex = 0;                               // 30
        uint32    powerType = 0;                                   // 31
        uint32    manaCost = 0;                                    // 32
        uint32    manaCostPerlevel = 0;                            // 33
        uint32    manaPerSecond = 0;                               // 34
        uint32    manaPerSecondPerLevel = 0;                       // 35
        uint32    rangeIndex = 1;                                  // 36
        float     speed = 0.f;                                     // 37
      //uint32    modalNextSpell;                                  // 38 not used
        uint32    StackAmount = 0;                                 // 39
        uint32    Totem[MAX_SPELL_TOTEMS] = {};                    // 40-41
        int32     Reagent[MAX_SPELL_REAGENTS] = {};                // 42-49
        uint32    ReagentCount[MAX_SPELL_REAGENTS] = {};           // 50-57
        int32     EquippedItemClass = -1;                          // 58 (value)
        int32     EquippedItemSubClassMask = 0;                    // 59 (mask)
        int32     EquippedItemInventoryTypeMask = 0;               // 60 (mask)
        uint32    Effect[MAX_EFFECT_INDEX] = {};                   // 61-63
        int32     EffectDieSides[MAX_EFFECT_INDEX] = {};           // 64-66
        uint32    EffectBaseDice[MAX_EFFECT_INDEX] = {};           // 67-69
        float     EffectDicePerLevel[MAX_EFFECT_INDEX] = {};       // 70-72
        float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX] = {}; // 73-75
        int32     EffectBasePoints[MAX_EFFECT_INDEX] = {};         // 76-78 
        uint32    EffectMechanic[MAX_EFFECT_INDEX] = {};           // 79-81
        uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX] = {};    // 82-84
        uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX] = {};    // 85-87
        uint32    EffectRadiusIndex[MAX_EFFECT_INDEX] = {};        // 88-90
        uint32    EffectApplyAuraName[MAX_EFFECT_INDEX] = {};      // 91-93
        uint32    EffectAmplitude[MAX_EFFECT_INDEX] = {};          // 94-96
        float     EffectMultipleValue[MAX_EFFECT_INDEX] = {};      // 97-99
        uint32    EffectChainTarget[MAX_EFFECT_INDEX] = {};        // 100-102
        uint32    EffectItemType[MAX_EFFECT_INDEX] = {};           // 103-105
        int32     EffectMiscValue[MAX_EFFECT_INDEX] = {};          // 106-108
        uint32    EffectTriggerSpell[MAX_EFFECT_INDEX] = {};       // 109-111
        float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX] = {};// 112-114
        uint32    SpellVisual = 0;                                 // 115
      //uint32    SpellVisual2;                                    // 116 not used
        uint32    SpellIconID = 0;                                 // 117
        uint32    activeIconID = 0;                                // 118
        uint32    spellPriority = 0;                               // 119
        std::array<std::string, MAX_DBC_LOCALE> SpellName{};       // 120-127
      //uint32    SpellNameFlag;                                   // 128     not used
        std::array<std::string, MAX_DBC_LOCALE> Rank{};            // 129-136
      //uint32    RankFlags;                                       // 137     not used
      //char*     Description[8];                                  // 138-145 not used
      //uint32    DescriptionFlags;                                // 146     not used
      //char*     ToolTip[8];                                      // 147-154 not used
      //uint32    ToolTipFlags;                                    // 155     not used
        uint32    ManaCostPercentage = 0;                          // 156
        uint32    StartRecoveryCategory = 0;                       // 157
        uint32    StartRecoveryTime = 0;                           // 158
        uint32    MaxTargetLevel = 0;                              // 160
        uint32    SpellFamilyName = 0;                             // 161
        uint64    SpellFamilyFlags = 0;                            // 162
        uint32    MaxAffectedTargets = 0;                          // 163
        uint32    DmgClass = 0;                                    // 164
        uint32    PreventionType = 0;                              // 165
      //int32     StanceBarOrder;                                  // 166 not used
        float     DmgMultiplier[MAX_EFFECT_INDEX] = {};            // 167-169
      //uint32    MinFactionId;                                    // 170 not used
      //uint32    MinReputation;                                   // 171 not used
      //uint32    RequiredAuraVision;                              // 172 not used

        /// CUSTOM FIELDS:
        uint32 MinTargetLevel = 0;                                 // 159
        uint32 Custom = 0;                                         // 173
        uint32 Internal = 0;                                       // Assigned by the core.
    protected:
        bool _isBinary = false;
        bool _isDispel = false;
        bool _isNonPeriodicDispel = false;
        void ComputeBinary();
        void ComputeNonPeriodicDispel();
        void ComputeDispel();
    public:
        bool IsBinary() const { return _isBinary; }
        bool IsDispel() const { return _isDispel; }
        bool IsNonPeriodicDispel() const { return _isNonPeriodicDispel; }
        bool IsPvEHeartBeat() const;
        bool IsCCSpell() const;
        DiminishingGroup GetDiminishingReturnsGroup(bool triggered) const;

        // helpers
        int32 CalculateSimpleValue(SpellEffectIndex eff) const { return EffectBasePoints[eff] + int32(EffectBaseDice[eff]); }

        bool IsFitToFamilyMask(uint64 familyFlags) const
        {
            return !!(SpellFamilyFlags & familyFlags);
        }

        bool IsFitToFamily(SpellFamily family, uint64 familyFlags) const
        {
            return SpellFamily(SpellFamilyName) == family && IsFitToFamilyMask(familyFlags);
        }

        template <SpellFamily family, ClassFlag... Args>
        bool IsFitToFamily() const
        {
            return SpellFamily(SpellFamilyName) == family && !!(SpellFamilyFlags & BitMask<uint64, Args...>::value);
        }

        template <ClassFlag... Args>
        bool IsFitToFamilyMask() const
        {
            return !!(SpellFamilyFlags & BitMask<uint64, Args...>::value);
        }

        bool IsAuraAddedBySpell(uint32 auraType) const
        {
            for (int i = 0; i < 3; i++)
                if (EffectApplyAuraName[i] == auraType)
                    return true;
            return false;
        }

        uint32 GetAllSpellMechanicMask() const
        {
            uint32 mask = 0;
            if (Mechanic)
                mask |= 1 << (Mechanic - 1);
            for (int i=0; i< MAX_EFFECT_INDEX; ++i)
                if (EffectMechanic[i])
                    mask |= 1 << (EffectMechanic[i]-1);
            return mask;
        }

        bool HasAttribute(SpellAttributes attribute) const { return Attributes & attribute; }
        bool HasAttribute(SpellAttributesEx attribute) const { return AttributesEx & attribute; }
        bool HasAttribute(SpellAttributesEx2 attribute) const { return AttributesEx2 & attribute; }
        bool HasAttribute(SpellAttributesEx3 attribute) const { return AttributesEx3 & attribute; }
        bool HasAttribute(SpellAttributesEx4 attribute) const { return AttributesEx4 & attribute; }

        uint32 GetMechanic() const { return Mechanic; }
        uint32 GetManaCost() const { return manaCost; }
        uint32 GetSpellFamilyName() const { return SpellFamilyName; }
        uint32 GetAuraInterruptFlags() const { return AuraInterruptFlags; }
        uint32 GetStackAmount() const { return StackAmount; }
        uint32 GetEffectImplicitTargetAByIndex(SpellEffectIndex j) const { return EffectImplicitTargetA[j];}
        uint32 GetEffectImplicitTargetBByIndex(SpellEffectIndex j) const { return EffectImplicitTargetB[j];}
        uint32 GetEffectApplyAuraNameByIndex(SpellEffectIndex j) const { return EffectApplyAuraName[j];}
        uint32 GetEffectMiscValue(SpellEffectIndex j) const { return EffectMiscValue[j];}
        uint64 GetSpellFamilyFlags() const { return SpellFamilyFlags; }
        template <typename T, int Val>
        struct Shift
        {
            static T const value = T(1) << Val;
        };
        template <typename T, int N1, int N2 = -1, int N3 = -1, int N4 = -1, int N5 = -1, int N6 = -1, int N7 = -1, int N8 = -1, int N9 = -1, int N10 = -1>
        struct BitMask
        {
            static T const value = Shift<T, N1>::value | BitMask<T, N2, N3, N4, N5, N6, N7, N8, N9, N10, -1>::value;
        };

        template <typename T>
        struct BitMask<T, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1>
        {
            static T const value = 0;
        };
};

#endif
