/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Undercity
SD%Complete: 95
SDComment: Quest support: 6628(Parqual Fintallas questions/'answers' might have more to it, need more info), 9180(post-event).
SDCategory: Undercity
EndScriptData */

/* ContentData
npc_lady_sylvanas_windrunner
npc_highborne_lamenter
npc_parqual_fintallas
EndContentData */

#include "scriptPCH.h"

/*######
## npc_lady_sylvanas_windrunner
######*/

#define SAY_LAMENT_END              -1000196
#define EMOTE_LAMENT_END            -1000197

#define SOUND_CREDIT                10896
#define ENTRY_HIGHBORNE_LAMENTER    21628
#define ENTRY_HIGHBORNE_BUNNY       21641

enum eSpells
{
    // Varimathras
    SPELL_SUMMONED              = 7741,
    SPELL_DRAIN_LIFE            = 20743,
    SPELL_SHADOW_BOLT_VOLLEY    = 20741,
    SPELL_MIND_CONTROL          = 20740,
    // Sylvanas
    SPELL_SUMMON_SKEL   = 20464,
    SPELL_FADE          = 20672,
    SPELL_BLACK_ARROW   = 20733,
    SPELL_MULTI_SHOT    = 20735,
    SPELL_SHOOT         = 20463,
};

struct boss_varimathrasAI : public ScriptedAI
{
public:
    boss_varimathrasAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset() override
    {
        DoCastSpellIfCan(m_creature, SPELL_SUMMONED);
        m_uiDrainLifeTimer = 15000;
        m_uiShadowBoltVolleyTimer = 25000;
        m_uiMindControlTimer = 20000;
        m_bIsCastingDrain = false;
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bIsCastingDrain)
        {
            if (m_uiDrainLifeTimer > uiDiff)
            {
                m_uiDrainLifeTimer -= uiDiff;
                return;
            }
            m_bIsCastingDrain = false;
            m_uiDrainLifeTimer = 20000;
        }

        if (m_uiDrainLifeTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_DRAIN_LIFE, CAST_TRIGGERED) == CAST_OK)
            {
                m_uiDrainLifeTimer = 5000;
                m_bIsCastingDrain = true;
            }
        }
        else
            m_uiDrainLifeTimer -= uiDiff;

        if (m_uiShadowBoltVolleyTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_SHADOW_BOLT_VOLLEY) == CAST_OK)
                m_uiShadowBoltVolleyTimer = 20000;
        }
        else
            m_uiShadowBoltVolleyTimer -= uiDiff;

        if (m_uiMindControlTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MIND_CONTROL) == CAST_OK)
                    m_uiMindControlTimer = urand(15000, 25000);
            }
        }
        else
            m_uiMindControlTimer -= uiDiff;

        DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea(uiDiff);
    }

private:
    uint32 m_uiDrainLifeTimer;
    uint32 m_uiShadowBoltVolleyTimer;
    uint32 m_uiMindControlTimer;
    bool m_bIsCastingDrain;
};

CreatureAI* GetAI_boss_varimathras(Creature* pCreature)
{
    return new boss_varimathrasAI(pCreature);
}

/*
TODO : TIMERS TO CHECK
*/

struct boss_sylvanasAI : public ScriptedAI
{
public:
    boss_sylvanasAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset() override
    {
        m_uiSummSkelTimer = 25000;
        m_uiFadeTimer = 50000;
        m_uiFadedTimer = 0;
        m_uiBlackArrowTimer = 15000;
        m_uiMultiShotTimer = 10000;
        m_uiShootTimer = 10000;
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_uiFadedTimer)
        {
            if (m_uiFadedTimer > uiDiff)
            {
                m_uiFadedTimer -= uiDiff;
                return;
            }
            m_uiFadedTimer = 0;
            m_creature->GetMotionMaster()->Clear();
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSummSkelTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_SKEL) == CAST_OK)
                m_uiSummSkelTimer = 25000;
        }
        else
            m_uiSummSkelTimer -= uiDiff;

        if (m_uiFadeTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FADE) == CAST_OK)
            {
                m_creature->GetMotionMaster()->MoveFollow(m_creature->getVictim(), 30.0f, m_creature->GetAngle(m_creature->getVictim()));
                m_uiFadeTimer = 50000;
                m_uiBlackArrowTimer = 0;
                m_uiMultiShotTimer = 0;
                m_uiShootTimer = 0;
                m_uiFadedTimer = 5000;
            }
        }
        else
            m_uiFadeTimer -= uiDiff;

        if (m_uiBlackArrowTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_BLACK_ARROW) == CAST_OK)
                    m_uiBlackArrowTimer = 15000;
            }
        }
        else
            m_uiBlackArrowTimer -= uiDiff;

        if (m_uiMultiShotTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MULTI_SHOT) == CAST_OK)
                    m_uiMultiShotTimer = 10000;
            }
        }
        else
            m_uiMultiShotTimer -= uiDiff;

        if (m_uiShootTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHOOT) == CAST_OK)
                m_uiShootTimer = 10000;
        }
        else
            m_uiShootTimer -= uiDiff;

        DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea(uiDiff);
    }

private:
    uint32 m_uiSummSkelTimer;
    uint32 m_uiFadeTimer;
    uint32 m_uiFadedTimer;
    uint32 m_uiBlackArrowTimer;
    uint32 m_uiMultiShotTimer;
    uint32 m_uiShootTimer;
};

CreatureAI* GetAI_boss_sylvanas(Creature* pCreature)
{
    return new boss_sylvanasAI(pCreature);
}

bool GossipHello_npc_lady_sylvanas_windrunner(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipHello_npc_estelle_gendry(Player* pPlayer, Creature* pCreature)
{
    if ((pPlayer->GetQuestStatus(1999) == QUEST_STATUS_INCOMPLETE))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,
                                 "I need the tools Mennet Carkad told me about.",
                                 GOSSIP_SENDER_MAIN,
                                 GOSSIP_ACTION_INFO_DEF + 10);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature),
                                  pCreature->GetObjectGuid());
    }
    return true;
}

bool GossipSelect_npc_estelle_gendry(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction >= GOSSIP_ACTION_INFO_DEF + 10)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (!pPlayer->HasItemCount(5060, 1, true))
        {
            uint32 noSpaceForCount = 0;
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT,
                                                 dest, 5060, 1, &noSpaceForCount);

            if (msg == EQUIP_ERR_OK)
            {
                Item* pItem = pPlayer->StoreNewItem(dest, 5060,
                                                    true, Item::GenerateItemRandomPropertyId(5060));
                pPlayer->SendNewItem(pItem, 1, true, false);
            }
        }
    }
    return true;
}



/*######
## npc_parqual_fintallas
######*/

#define SPELL_MARK_OF_SHAME 6767

bool GossipHello_npc_parqual_fintallas(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(6628) == QUEST_STATUS_INCOMPLETE && !pPlayer->HasAura(SPELL_MARK_OF_SHAME, EFFECT_INDEX_0))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Gul'dan", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Kel'Thuzad", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ner'zhul", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        pPlayer->SEND_GOSSIP_MENU(5822, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(5821, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_parqual_fintallas(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->CastSpell(pPlayer, SPELL_MARK_OF_SHAME, false);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->AreaExploredOrEventHappens(6628);
    }
    return true;
}

/*######
## AddSC
######*/

void AddSC_undercity()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_lady_sylvanas_windrunner";
    newscript->GetAI = &GetAI_boss_sylvanas;
    newscript->pGossipHello = &GossipHello_npc_lady_sylvanas_windrunner;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_parqual_fintallas";
    newscript->pGossipHello = &GossipHello_npc_parqual_fintallas;
    newscript->pGossipSelect = &GossipSelect_npc_parqual_fintallas;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_estelle_gendry";
    newscript->pGossipHello = &GossipHello_npc_estelle_gendry;
    newscript->pGossipSelect = &GossipSelect_npc_estelle_gendry;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_varimathras";
    newscript->GetAI = &GetAI_boss_varimathras;
    newscript->RegisterSelf();
}
