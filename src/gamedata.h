#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "point.h"

#include "equipment.h"
#include "monster.h"
#include "town.h"

using std::cout;
using std::ifstream;
using std::endl;
using std::numeric_limits;
using std::streamsize;

using std::map;
using std::string;
using std::vector;

const string MAPFILE = "../dat/Map.dat";
const string MONSTERFILE = "../dat/Monster.dat";
const string BOSSFILE = "../dat/Bosses.dat";
const string CAVEFILE = "../dat/caves.dat";
const string TOWNFILE = "../dat/Towns.dat";
const string WEAPONFILE = "../dat/weapons.dat";
const string ARMORFILE = "../dat/armor.dat";
const string ITEMFILE = "../dat/items.dat";

/* This class tracks game resources, which don't change as the player progresses.
 */
class GameData
{
	private:
		bool loadedSuccessfully;

		vector<string> worldMap;
		map<int, Town> towns;

		vector<Monster> monsters;
		map<int, Monster> bosses; //1D coord -> Monster

		vector<Equipment*> weaponPtrs;
		vector<Equipment*> armorPtrs;
		vector<Equipment*> itemsPtrs;

		bool loadDataFiles(); //master load method

		bool loadMap();
		bool loadMonsters(vector<Monster>& monsters, const string& filename);
		bool loadBosses(map<int, Monster>&, const string&, const string&);
		bool loadEquipment(EquipType type, vector<Equipment*>& equipment, const string& filename);

		bool loadTowns();

	public:
		GameData();
		~GameData();

		const bool loadSuccessful();

	    vector<string>& getMap();
		const Town& getTown(const Point&);

		const vector<Monster>& getMonsters();
		Monster getBossAt(const Point&);

		const vector<Equipment*>& getWeapons();
		const vector<Equipment*>& getArmor();
		const vector<Equipment*>& getItems();
};


#endif
