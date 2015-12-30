//Mike Lukas -p2prog03- 	-Errantry Class Test-

#include <iostream.h>
#include "chtypes.h"


int main()
	{
		char done;
		Player player;
		SpellType testSpell;
		testSpell.MAP = 15;
		testSpell.cost = 15;
		testSpell.name = "Flame";
		testSpell.element = fire;
		
		cout<<player.Damage()<<endl;
		cout<<player.Defense()<<endl;
		cout<<player.Health()<<endl;
		cout<<player.MEnergy()<<endl;
		cout<<player.MDamage(testSpell)<<endl;
		cout<<player.MDefense()<<endl;
		cout<<player.Speed()<<endl;
		cout<<player.Money()<<endl<<endl;
		cout<<player.Level()<<endl;
		cout<<player.NumExpPts()<<endl;
		cout<<player.NumToNext()<<endl;
		cin>>done;
		
		return 0;
	} 
