#include "gamedata.h"

GameData::GameData()
	: loadedSuccessfully(false)
{
	loadedSuccessfully = loadDataFiles();
}

GameData::~GameData()
{
	//delete all equipment definitions
	while(!weaponPtrs.empty())
	{
		delete (weaponPtrs.back());
		weaponPtrs.pop_back();
	}

	while(!armorPtrs.empty())
	{
		delete (armorPtrs.back());
		armorPtrs.pop_back();
	}

	while(!itemsPtrs.empty())
	{
		delete (itemsPtrs.back());
		itemsPtrs.pop_back();
	}
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
		return false;
	}

	if(!loadBosses(bosses, BOSSFILE, CAVEFILE))
	{
		return false;
	}

	if(!loadEquipment(WEAPON, weaponPtrs, WEAPONFILE))
	{
		return false;
	}

	if(!loadEquipment(ARMOR, armorPtrs, ARMORFILE))
	{
		return false;
	}

	if(!loadEquipment(ITEM, itemsPtrs, ITEMFILE))
	{
		return false;
	}

	if(!loadSpells(spellPtrs, SPELLFILE))
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

	ifstream monsterFile(filename);
	if(!monsterFile)
	{
		cout<<"ERROR: "<<filename<<" not found!"<<endl;
		return false;
	}

	cout<<":  Loading monsters from "<<filename<<endl;

	while(monsterFile.peek() != EOF)
	{
		Monster monster;
		monsterFile>>monster;

		monsters.push_back(monster);
	}
	monsterFile.close();
	cout<<":  "<<monsters.size()<<" Monsters found."<<endl;

	return true;
}

bool GameData::loadBosses(map<int, Monster>& bosses, const string& bossesFilename, const string& cavesFilename)
{
	//postcondition: monster data for all bosses is loaded from the bosses file,
	//caves are placed on the world map at the locations where each boss should be
	//fought at, and the bosses map is populated with 1D cave index -> Monster
	//instance for the boss at that location.

	vector<Monster> monsters;
	if(!loadMonsters(monsters, bossesFilename))
	{
		cout<<"ERROR: Unable to load Monster data for bosses from "<<bossesFilename<<"!"<<endl;
		return false;
	}

	ifstream cavesFile(cavesFilename);
	if(!cavesFile)
	{
		cout<<"ERROR: "<<cavesFilename<<" not found!"<<endl;
		return false;
	}

	cout<<":  Loading boss caves from "<<cavesFilename<<endl;

	//Order of caves in caves is the same as order of bosses in bosses file
	int bossIndex = 0;
	while(cavesFile.peek() != EOF && bossIndex < monsters.size()) //makes sure we don't make more caves than we have bosses
	{
		Point caveLocation;
		cavesFile>>caveLocation;
		cavesFile.ignore(numeric_limits<streamsize>::max(), '\n');

		//Map boss monster instance to each cave location for lookup when player moves on the map
		bosses[caveLocation.as1dIndex(worldMap.size())] = monsters[bossIndex++];
		worldMap[caveLocation.y][caveLocation.x] = 'C';
	}
	cavesFile.close();
	cout<<":  "<<bosses.size()<<" bosses placed in caves."<<endl;

	return true;
}

bool GameData::loadEquipment(EquipType type, vector<Equipment*>& equipment, const string& filename)
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

			Equipment* item = new Equipment(type);
			equipFile>>(*item);

			equipment.push_back(item);

			cout<<item->getName()<<endl;
			cout<<"   "<<item->getCost()<<endl;
			cout<<"   "<<item->getType()<<endl;

			cout<<"   Mods - "<<item->getStatMod()<<endl<<endl;
		}
	equipFile.close();
	cout<<":  "<<equipment.size()<<" equipment found."<<endl;

	return true;
}

bool GameData::loadSpells(vector<const Spell*>& spells, const string& filename)
{
	ifstream spellFile(filename);
	if(!spellFile)
	{
		cout<<"ERROR: "<<filename<<" not found!"<<endl;
		return false;
	}

	cout<<":  Loading spells from "<<filename<<endl;

	while(spellFile.peek() != EOF)
	{
		const Spell* spell = new Spell(spellFile);
		cout<<spell->getName()<<endl
			<<"  "<<spell->getElement()<<endl
			<<"  "<<spell->getMpCost()<<endl
			<<"  "<<spell->getPurchasePrice()<<endl;
		spells.push_back(spell);

		//populate spells by category
		categorizedSpellIds[spell->getCategory()].push_back(spells.size()-1); //since we just put the spell on thend, spell id is last element index
	}
	spellFile.close();
	cout<<":  "<<spells.size()<<" spells found."<<endl;

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
			cout<<"    "<<town.getShopSpellIds().size()<<" spells loaded"<<endl;
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

Monster GameData::getBossAt(const Point& coord)
{
	return bosses[coord.as1dIndex(worldMap[0].size())];
}

const vector<Equipment*>& GameData::getWeapons()
{
	return weaponPtrs;
}

const vector<Equipment*>& GameData::getArmor()
{
	return armorPtrs;
}

const vector<Equipment*>& GameData::getItems()
{
	return itemsPtrs;
}

const vector<const Spell*>& GameData::getSpells()
{
	return spellPtrs;
}

vector<const Spell*>* GameData::getSpellsForIds(const vector<int>& spellIds) const
{
	//postcondition: Allocates a new vector of Spell ptrs matching each of the
	//Spell ids passed in, using the allSpells vector to look up the Spell ptrs
	//by id.

	vector<const Spell*>* spellsForIds = new vector<const Spell*>();
	for(int i = 0; i < spellIds.size(); i++)
	{
		const Spell* spell = spellPtrs[spellIds[i]];
		spellsForIds->push_back(spell);
	}

	return spellsForIds;
}
