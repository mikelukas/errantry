#include "statsdisplayer.h"

void StatsDisplayer::fullDisplayFor(const Player& player)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<player.Health()<<"/"<<player.MaxHealth();

	ostringstream mpMaxMP;
	mpMaxMP<<player.getMP()<<"/"<<player.MaxMP();

	cout<<"HP:  "<<std::left<<setw(12)<<healthMaxhealth.str()<<" --health/max health"<<endl
		<<"MP:  "<<std::left<<setw(12)<<mpMaxMP.str()<<" --magic points/max magic points"<<endl
		<<"AP:  "<<std::left<<setw(12)<<player.Damage()<<" --attack power"<<endl
		<<"DP:  "<<std::left<<setw(12)<<player.Defense()<<" --defense percentage"<<endl
		<<"MDP: "<<std::left<<setw(12)<<player.MagicDefense()<<" --magic defense percentage"<<endl
		<<"SP:  "<<std::left<<setw(12)<<player.Speed()<<" --speed points"<<endl
		<<endl;
	cout<<"Level: "<<player.Level()<<endl
		<<"  Current experience points:    "<<player.ExpPts()<<endl
		<<"  Number needed for next level: "<<player.NumToNext()<<endl;
}

void StatsDisplayer::battleDisplayFor(const Player& player)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<player.Health()<<"/"<<player.MaxHealth();

	ostringstream mpMaxMP;
	mpMaxMP<<player.getMP()<<"/"<<player.MaxMP();

	cout<<"HP:  "<<std::left<<setw(12)<<healthMaxhealth.str()<<endl
		<<"MP:  "<<std::left<<setw(12)<<mpMaxMP.str()<<endl
		<<"AP:  "<<std::left<<setw(12)<<player.Damage()<<endl
		<<"DP:  "<<std::left<<setw(12)<<player.Defense()<<endl
		<<"MDP: "<<std::left<<setw(12)<<player.MagicDefense()<<endl
		<<"SP:  "<<std::left<<setw(12)<<player.Speed()<<endl;
}

void StatsDisplayer::battleDisplayFor(const Monster& monster)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<monster.Health()<<"/"<<monster.MaxHealth();

	cout<<"HP: "<<std::left<<setw(12)<<healthMaxhealth.str()<<endl;
}
