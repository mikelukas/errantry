#include "gamedata.h"

GameData::GameData()
	: loadedSuccessfully(false)
{
	loadedSuccessfully = loadDataFiles();
}

bool GameData::loadDataFiles()
{
	if(!loadMap())
	{
		cout<<"ERROR: "<<MAPFILE<<" not found!"<<endl;
		return false;
	}

	if(!loadMonsters(monsters, MONSTERFILE))
	{
		cout<<"ERROR: "<<MONSTERFILE<<" not found!"<<endl;
		return false;
	}

	if(!loadMonsters(bosses, BOSSFILE))
	{
		cout<<"ERROR: "<<BOSSFILE<<" not found!"<<endl;
		return false;
	}

	if(!loadEquipment(WEAPON, weapons, WEAPONFILE))
	{
		return false;
	}

	if(!loadEquipment(ARMOR, armor, ARMORFILE))
	{
		return false;
	}

	if(!loadEquipment(ITEM, items, ITEMFILE))
	{
		return false;
	}

	if(!loadTowns())
	{
		return false;
	}

	return true;
}

bool GameData::loadMap()
{
	//Postcondition:  the world map for the game is retrieved from
	//a file for use in the program.
	bool found = false;

	ifstream inFile(MAPFILE);

	if(inFile)
		{
			string mapLine;
			while(getline(inFile, mapLine))
				{
					worldMap.push_back(mapLine);
				}
			found = true;
			cout<<":  Map found."<<endl;
		}
	return found;
}

bool GameData::loadMonsters(vector<Monster>& monsters, const string& filename)
{
	//Postcondition:  the attributes of each monster are retrieved
	//from a file for use in the program

	int hp, ap, dp, sp, expPts;
	bool found = false;
	string name; //name of monster

	ifstream inFile(filename.c_str());

	if(inFile)
		{
			while(getline(inFile, name) &&
				  inFile>>hp>>ap>>dp>>sp>>expPts)
				{
					Monster monster;
					monster.SetAttributes(hp, ap, dp, sp, expPts,name);

					monsters.push_back(monster);
				}
			found = true;
			cout<<":  "<<monsters.size()<<" Monsters found."<<endl;
		}
	return found;
}

bool GameData::loadEquipment(EquipType type, vector<Equipment>& equipment, const string& filename)
{
	ifstream equipFile(filename);
	if(!equipFile)
	{
		cout<<"ERROR: "<<filename<<" not found!"<<endl;
		return false;
	}

	cout<<":  Loading equipment from "<<filename<<endl;

	while(equipFile.peek() != EOF)
		{
			string junk;
			getline(equipFile, junk); //Throw away equipment index in file

			Equipment item(type);
			equipFile>>item;

			equipment.push_back(item);

			cout<<item.getName()<<endl;
			cout<<"   "<<item.getCost()<<endl;
			cout<<"   "<<item.getType()<<endl;

			cout<<"   Mods - "<<item.getStatMod()<<endl<<endl;
		}
	equipFile.close();
	cout<<":  "<<equipment.size()<<" equipment found."<<endl;

	return true;
}

bool GameData::loadTowns()
{
	//Postcondition:  towns is populated with all towns from the town data file

	ifstream townFile(TOWNFILE);
	if(!townFile)
	{
		cout<<"ERROR: "<<TOWNFILE<<"not found!"<<endl;
		return false;
	}

	cout<<":  Loading towns..."<<endl;
	int mapWidth = worldMap[0].size();
	while(townFile.peek() != EOF)
		{
			Town town;
			townFile>>town;

			//index town into towns using its location, and draw its symbol onto the map
			Point townLoc = town.getLocation();
			towns[townLoc.as1dIndex(mapWidth)] = town;
			worldMap[townLoc.y][townLoc.x] = TOWN_SYMBOL;

			//For debugging, remove when town-loading is all done.
			cout<<town.getName()<<endl;
			cout<<"    "<<town.getLocation().as1dIndex(mapWidth)<<endl;
			cout<<"    "<<town.getShopEquipmentIds(WEAPON).size()<<" weapons loaded"<<endl;
			cout<<"    "<<town.getShopEquipmentIds(ARMOR).size()<<" armor pieces loaded"<<endl;
			cout<<"    "<<town.getShopEquipmentIds(ITEM).size()<<" items loaded"<<endl;
			cout<<town.getConversation();
			cout<<TOWN_CONVO_DELIM<<endl;
		}

	townFile.close();
	cout<<":  "<<towns.size()<<" towns found."<<endl;

	return true;
}

const bool GameData::loadSuccessful()
{
	return loadedSuccessfully;
}

vector<string>& GameData::getMap()
{
	return worldMap;
}

const Town& GameData::getTown(const Point& coord)
{
	return towns[coord.as1dIndex(worldMap[0].size())];
}

const vector<Monster>& GameData::getMonsters()
{
	return monsters;
}

const vector<Monster>& GameData::getBosses()
{
	return bosses;
}

const vector<Equipment>& GameData::getWeapons()
{
	return weapons;
}

const vector<Equipment>& GameData::getArmor()
{
	return armor;
}

const vector<Equipment>& GameData::getItems()
{
	return items;
}
