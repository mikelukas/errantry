#include "statsdisplayer.h"

void StatsDisplayer::fullDisplayFor(const Player& player)
{
	ostringstream healthMaxhealth;
	healthMaxhealth<<player.Health()<<"/"<<player.MaxHealth();

	cout<<"HP: "<<std::left<<setw(12)<<healthMaxhealth.str()<<" --health/max health"<<endl
		<<"AP: "<<std::left<<setw(12)<<player.Damage()<<" --attack power"<<endl
		<<"DP: "<<std::left<<setw(12)<<player.Defense()<<" --defense percentage"<<endl
		<<"SP: "<<std::left<<setw(12)<<player.Speed()<<" --speed points"<<endl
		<<endl;
	cout<<"Level: "<<player.Level()<<endl
		<<"  Current experience points:    "<<player.NumExpPts()<<endl
		<<"  Number needed for next level: "<<player.NumToNext()<<endl;
}
