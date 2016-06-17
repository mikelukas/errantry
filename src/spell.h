#ifndef _SPELL_H
#define _SPELL_H

#include <istream>
#include <set>
#include <string>
#include <vector>
#include "effects.h"
#include "streamutils.h" //getIdLine

using std::istream;
using std::set;
using std::string;
using std::vector;

enum Element {fire, air, earth, water, none};
enum SpellCategory {ATTACK, HEALING, ASSIST};
enum SpellLocale {FIELD, BATTLE};
enum TargetType {PLAYER, MONSTER};

/* This class contains all information needed to acquire and cast a spell,
 * but it DOES NOT directly contain the actual logic for what the spell does.
 * Rather, Spells reference a 1 or more EffectFunctions (see effects.h),
 * which are applied when the spell is cast.
 * Referencing EffectFunctions allows Spells to be defined in dat files without
 * compilation, while still being able to do more complicated, reusable logic
 * that is not easily described in a standard way in dat files.
 */
class Spell
{
	protected:
		string name;                //display name of spell
		SpellCategory category;		//how the spell's effect can be summarized; used by monsters to decide on spells

		Element element;            //basic elemental type of spell

		int mpCost;   	            //cost in MP
		int purchasePrice;          //cost to learn (if learnable in a town)

		set<int> eligibleLocations; //locations where this spell can be cast
		set<int> eligibleTargets;	//targets player can choose for this spell

		vector<int> effectIds;	    //Effect IDs applied when this spell is cast, in order of application

	public:
		Spell(istream&);

		const string& getName() const;
		const SpellCategory getCategory() const;
		const Element getElement() const;
		const int getMpCost() const;
		const int getPurchasePrice() const;

		const set<int>& getEligibleLocations() const;
		const set<int>& getEligibleTargets() const;

		void cast(Character&, Character&) const;
};

string getDisplayNameFor(Element);
    
#endif
