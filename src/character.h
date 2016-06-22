#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <map>
#include <set>
#include <string>
#include "equipment.h"
#include "spell.h"

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

            set<Element> weaknesses;	//more magical damage from these element

            string name;

            int gold;
            int expPoints;      //number of expPoints character carries

            //Inventory; maps for fast lookup of quantity
			map<const Equipment*, EquipmentLine> weapons;
			map<const Equipment*, EquipmentLine> armor;
			map<const Equipment*, EquipmentLine> items;

            set<const Spell*> spells;
			map<SpellCategory, set<const Spell*> > categorizedSpells;
                    
            void AddStats(const StatMod&);
			void SubStats(const StatMod&);

			void recalculateWeakness();

        public:
            Character(int, int, int, int, int, int, int, int);
            virtual ~Character() {};

            void ChangeHP(int);
            void ChangeMP(int);
            
            string ShowName() const;

            int Damage() const;
            int Defense() const;
            int MagicDefense() const;
            int Health() const;
            int MaxHealth() const;
            int getMP() const;
            int MaxMP() const;
            int Speed() const;
            int Money() const;
            int ExpPts() const;

            bool isWeakAgainst(Element) const;
            const set<Element>& getWeaknesses() const;

            void AddEquipment(const EquipmentLine&);
            void AddSpell(const Spell*);

            vector<const Equipment*>* getAllEquipment() const;
            map<const Equipment*, EquipmentLine>& getInventoryFor(const EquipType);

            bool hasSpell(const Spell*) const;
            bool hasSpells() const;
			vector<const Spell*>* getSpells() const;
			const set<const Spell*>& getSpellsForCategory(SpellCategory);

            virtual void apply(const Equipment*) = 0;
            int applyPhysicalDamage(int);
            int applyMagicalDamage(int, Element);

            void addWeakness(Element);
    };

#endif
