#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <map>
#include <set>
#include <string>
#include "context.h"
#include "effecttype.h"
#include "equipment.h"
#include "spelltemplate.h"
#include "statuses/statuseffect.h"

using std::map;
using std::set;
using std::string;

//Mike Lukas -p2prog03-         - character.h -
//Class definition for a character.  This class holds all of the basic
//values a character will need; health points, magic points, attack
//points, defense points, magic defense points, speed points, and 
//money.  
    
class Character
    {
        protected:
            int HP;             //current hit points (life)
            int maxHP;          //maximum hit points
            int MP;				//current magic points (needed to cast spells)
            int maxMP;			//maximum magic points
            int AP;             //attack power
            int DP;             //defense percentage
            int MDP;			//magic defense percentage
            int SP;             //speed points

            StatMod totalStatMods;	//sum of modifications to player attributes from equipment and status effects

            set<Element> weaknesses;	//more magical damage from these element

            string name;

            int gold;
            int expPoints;      //number of expPoints character carries

            //Inventory; maps for fast lookup of quantity
			map<const Equipment*, EquipmentLine> weapons;
			map<const Equipment*, EquipmentLine> armor;
			map<const Equipment*, EquipmentLine> items;

            set<const SpellTemplate*> spells;
			map<SpellCategory, set<const SpellTemplate*> > categorizedSpells;

			map<const EffectType, StatusEffect*> statuses;
			map<const Context, set<StatusEffect*> > statusesByContext;

			map<const EffectType, set<const Equipment*> > tempStatusImmunities;
			set<const EffectType> permStatusImmunities;

			void recalculateWeakness();

        public:
            Character(int, int, int, int, int, int, int, int);
            virtual ~Character();

            void ChangeHP(int);
            void ChangeMP(int);
            
            void AddStats(const StatMod&);
			void SubStats(const StatMod&);

            string ShowName() const;

            int getHP() const;
            int getBaseMaxHP() const;
            int getEffectiveMaxHP() const;

            int getMP() const;
            int getBaseMaxMP() const;
            int getEffectiveMaxMP() const;

            int getBaseAP() const;
            int getEffectiveAP() const;

            int getBaseDP() const;
            int getEffectiveDP() const;

            int getBaseMDP() const;
            int getEffectiveMDP() const;

            int getBaseSP() const;
            int getEffectiveSP() const;

            int Money() const;
            int ExpPts() const;

            bool isWeakAgainst(Element) const;
            const set<Element>& getWeaknesses() const;

            void AddEquipment(const EquipmentLine&);
            void RemoveEquipment(const EquipmentLine*);
            void AddSpell(const SpellTemplate*);

            vector<const Equipment*>* getAllEquipment() const;
            map<const Equipment*, EquipmentLine>& getInventoryFor(const EquipType);
            vector<EquipmentLine*>* getWeaponsAndArmorAsVector();
            vector<EquipmentLine*>* getItemsAsVector();

            int getEffectiveMpCostFor(const SpellTemplate*) const;
            bool hasEnoughMpFor(const SpellTemplate*) const;
            bool hasSpell(const SpellTemplate*) const;
            bool hasSpells() const;
			const set<const SpellTemplate*>& getSpells() const;
			const set<const SpellTemplate*>& getSpellsForCategory(SpellCategory);
			const set<const SpellTemplate*>* getSpellsForCategories(const set<SpellCategory>&);
			const set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>* getSpellElementCounts(const set<SpellCategory>&);

            virtual void apply(const Equipment*) = 0;
            int applyPhysicalDamage(int);
            int applyMagicalDamage(int, Element);

            void addWeakness(Element);
            void removeWeakness(Element);

            bool addStatus(StatusEffect*);
            void removeStatus(const EffectType);
            void removeStatusesFor(const Context);

            void processStatusEffects();

            bool hasStatus(const EffectType) const;
            bool hasStatuses() const;
            vector<StatusEffect*>* getAllStatuses() const;

            bool isImmuneTo(const EffectType) const;
            void addTempImmunitiesFrom(const Equipment*);
            void addTempImmunityTo(const EffectType, const Equipment*);
            void removeTempImmunitiesFor(const Equipment*);
            void removeTempImmunityTo(const EffectType, const Equipment*);
            void addPermImmunitiesFrom(const Equipment*);
            void addPermImmunityTo(const EffectType);
            void removePermImmunitiesFor(const Equipment*);
            void removePermImmunityTo(const EffectType);
    };

#endif
