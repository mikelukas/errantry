#include "statsdisplayer.h"

void StatsDisplayer::displayWeaknessesLineFor(const Character& character)
{
	//postcondition: displays the name of each Element to which the character is
	//weak, separated by spaces on one line, or None if character has no weaknesses.

	const set<Element> weaknesses = character.getWeaknesses();
	if(weaknesses.empty())
	{
		cout<<"None"<<endl;
		return;
	}

	set<Element>::const_iterator it = weaknesses.begin();
	cout<<getDisplayNameFor(*it);
	for(it++; it != weaknesses.end(); it++)
	{
		cout<<" "<<getDisplayNameFor(*it);
	}
	cout<<endl;
}

void StatsDisplayer::displayStatusesLineFor(const Character& character)
{
	vector<StatusEffect*>* statuses = character.getAllStatuses();

	cout<<(*statuses)[0]->getName();
	for(int i=1; i < statuses->size(); i++)
	{
		cout<<" "<<(*statuses)[i]->getName();
	}
	cout<<endl;

	delete statuses;
}

void StatsDisplayer::displayStatusImmunitiesLineFor(const Character& character)
{
	const set<EffectType>* immunities = character.getAllImmunities();

	set<EffectType>::const_iterator it = immunities->begin();
	cout<<getDisplayNameFor(*it);
	for(it++; it != immunities->end(); it++)
	{
		cout<<"  "<<getDisplayNameFor(*it);
	}
	cout<<endl;

	delete immunities;
}

void StatsDisplayer::fullDisplayFor(const Player& player)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<player.getHP()<<"/"<<player.getEffectiveMaxHP();

	ostringstream mpMaxMP;
	mpMaxMP<<player.getMP()<<"/"<<player.getEffectiveMaxMP();

	cout<<"HP:  "<<std::left<<setw(12)<<healthMaxhealth.str()<<" --health/max health"<<endl
		<<"MP:  "<<std::left<<setw(12)<<mpMaxMP.str()<<" --magic points/max magic points"<<endl
		<<"AP:  "<<std::left<<setw(12)<<player.getEffectiveAP()<<" --attack power"<<endl
		<<"DP:  "<<std::left<<setw(12)<<player.getEffectiveDP()<<" --defense percentage"<<endl
		<<"MDP: "<<std::left<<setw(12)<<player.getEffectiveMDP()<<" --magic defense percentage"<<endl
		<<"SP:  "<<std::left<<setw(12)<<player.getEffectiveSP()<<" --speed points"<<endl
		<<endl
		<<std::left<<setw(20)<<"Weaknesses:"<<" --1/2 MDP used against damage from these elements"<<endl
		<<"  "; displayWeaknessesLineFor(player);
	if(player.hasStatuses())
	{
		cout<<std::left<<setw(20)<<"Statuses:"<<" --persistent effects applied each turn to you."<<endl
			<<"  "; displayStatusesLineFor(player);
	}
	if(player.hasImmunities())
	{
		cout<<std::left<<setw(20)<<"Status Immunities:"<<"--Status Effects the player can't receive."<<endl
			<<"  "; displayStatusImmunitiesLineFor(player);
	}
	cout<<endl;
	cout<<"Level: "<<player.Level()<<endl
		<<"  Current experience points:    "<<player.ExpPts()<<endl
		<<"  Number needed for next level: "<<player.NumToNext()<<endl;
}

void StatsDisplayer::battleMainDisplayFor(const Player& player)
{
	cout<<player.ShowName()<<endl;
	cout<<"HP:  "<<player.getHP()<<"/"<<player.getEffectiveMaxHP()<<endl;
	cout<<"MP:  "<<player.getMP()<<"/"<<player.getEffectiveMaxMP()<<endl;
	if(player.hasStatuses())
	{
		cout<<"Statuses: "; displayStatusesLineFor(player);
	}

	cout<<endl;
}

void StatsDisplayer::battleMainDisplayFor(const Monster& monster)
{
	cout<<monster.ShowName()<<endl;
	cout<<"HP:  "<<monster.getHP()<<endl;
	if(monster.hasStatuses())
	{
		cout<<"Statuses: "; displayStatusesLineFor(monster);
	}
	cout<<endl;
}

void StatsDisplayer::battleMenuDisplayFor(const Player& player)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<player.getHP()<<"/"<<player.getEffectiveMaxHP();

	ostringstream mpMaxMP;
	mpMaxMP<<player.getMP()<<"/"<<player.getEffectiveMaxMP();

	cout<<"HP:  "<<std::left<<setw(12)<<healthMaxhealth.str()<<endl
		<<"MP:  "<<std::left<<setw(12)<<mpMaxMP.str()<<endl
		<<"AP:  "<<std::left<<setw(12)<<player.getEffectiveAP()<<endl
		<<"DP:  "<<std::left<<setw(12)<<player.getEffectiveDP()<<endl
		<<"MDP: "<<std::left<<setw(12)<<player.getEffectiveMDP()<<endl
		<<"SP:  "<<std::left<<setw(12)<<player.getEffectiveSP()<<endl
		<<endl
		<<"Weaknesses:"<<endl
		<<"  "; displayWeaknessesLineFor(player);

	if(player.hasStatuses())
	{
		cout<<"Statuses:"<<endl
			<<"  "; displayStatusesLineFor(player);
	}
	if(player.hasImmunities())
	{
		cout<<"Status Immunities:"<<endl
			<<"  "; displayStatusImmunitiesLineFor(player);
	}
}

void StatsDisplayer::battleMenuDisplayFor(const Monster& monster)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<monster.getHP()<<"/"<<monster.getEffectiveMaxHP();

	cout<<"HP: "<<std::left<<setw(12)<<healthMaxhealth.str()<<endl;
	if(monster.hasStatuses())
	{
		cout<<endl
			<<"Statuses:"<<endl
			<<"  "; displayStatusesLineFor(monster);
	}

}

void StatsDisplayer::equipDisplayFor(Player& player)
{
	//postcondition: Displays currently-equipped weapon and armor, or "Fists" and/or
	//"T-Shirt" respectively if there is nothing equipped for each type, then
	//displays the player's current attributes for determining how they'd change
	//after equipping something

	const Equipment* currWeapon = player.getCurrentEquipped(WEAPON);
	const Equipment* currArmor = player.getCurrentEquipped(ARMOR);

	cout<<"Current Weapon: "<<(currWeapon != NULL ? currWeapon->getName() : "Fists")<<endl
		<<"Current Armor:  "<<(currArmor != NULL ? currArmor->getName() : "T-Shirt")<<endl;
	if(player.hasImmunities())
	{
		cout<<"Status Immunities:"<<endl
			<<"  "; displayStatusImmunitiesLineFor(player);
	}
	cout<<endl
		<<std::left<<setw(23)<<"Current Attributes"<<"AP: "<<std::right<<setw(4)<<player.getEffectiveAP()<<" DP: "<<setw(3)<<player.getEffectiveDP()<<" MDP:"<<setw(3)<<player.getEffectiveMDP()<<" SP: "<<setw(3)<<player.getEffectiveSP()<<endl;
}
