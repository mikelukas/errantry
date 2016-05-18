#include "battlemode.h"
#include "deadmode.h"
#include "gamestate.h"

BattleMode::BattleMode(Monster monster, GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  currMonster(monster),
	  actionQueue()
{

}

BattleMode::~BattleMode()
{
	//postcondition: if there were unused actions in the queue b/c we returned
	//from executeActions() early because battle ended, they will be deleted.

	while(!actionQueue.empty())
	{
		BattleAction* action = actionQueue.front();

		actionQueue.pop();
		delete action;
	}
}

void BattleMode::run()
{
	//postcondition: calls super::run(), and then calls executeActions() to run
	//enqueued actions (if any).

	MenuMode::run();
	executeActions();
}

int BattleMode::displayMenu()
{
	int choice;
	Player& player = gameState.getPlayer();

	cout<<"*************ENEMY! You went to battle!*************"<<endl;
	cout<<player.ShowName()<<endl;
	cout<<"HP:  "<<player.Health()<<"/"<<player.MaxHealth()<<endl;
	cout<<"AP:  "<<player.Damage()<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<currMonster.ShowName()<<endl;
	cout<<"HP:  "<<currMonster.Health()<<endl;
	cout<<"*****************"<<endl;
	cout<<"*1)Fight        *"<<endl;
	cout<<"*2)Use Item     *"<<endl;
	cout<<"*3)Run          *"<<endl;
	cout<<"*****************"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;
	do
	{
		cout<<"Please choose an option:  "<<endl;
		cin>>choice;
	}while(!validateChoice(choice,3));

	return choice;
}

void BattleMode::testChoice(int choice)
{
	//postcondition: a BattleAction matching the player's choice is created, and
	//enqueued in the proper order depending whether the player's speed is greater
	//than the monster's.  setup() is called on the action before any actions are
	//are enqueued, and if the action is aborted, this method will return early
	//to allow the player to choose a new action.

	Player& player = gameState.getPlayer();

	//Handle player choice, and set up action they chose.
	BattleAction* playerAction;
	switch(choice)
	{
		case 1:
			playerAction = new FightAction(player, currMonster);
			break;
		case 2:
			playerAction = new UseItemAction(player, currMonster);
			break;
		case 3:
			playerAction = new RunAction(gameState);
			break;
	}

	playerAction->setup();
	if(playerAction->isAborted())
	{
		return; //player aborted action during setup, so let them go back and choose again
	}

	BattleAction* monsterAction = new FightAction(currMonster, player);
	monsterAction->setup();

	//Enqueue actions for battle turn
	if(player.Speed() >= currMonster.Speed()) {
		actionQueue.push(playerAction);
		actionQueue.push(monsterAction);
	} else {
		actionQueue.push(monsterAction);
		actionQueue.push(playerAction);
	}
}

void BattleMode::executeActions()
{
	//postcondition: each queued BattleAction is run in FIFO order until all
	//actions are executed or the battle is over.
	//Actions are deleted after execution.
	//If method returns early, destructor will delete unexecuted actions in queue.

	while(!actionQueue.empty())
	{
		BattleAction* action = actionQueue.front();
		action->execute();

		actionQueue.pop();
		delete action;

		if(testEndConditions())
		{
			return;
		}
	}
}

bool BattleMode::testEndConditions()
{
	//postcondition: returns true if either the player or monster HP is <=0, and
	//handles post-battle processing. Returns false, and does no other processing
	//otherwise.

	bool battleOver = false;

	if(currMonster.Health() <= 0)
		{
			onBattleWon();
			battleOver = true;
		}

	if(gameState.getPlayer().Health() <= 0)
		{
			//if player dies, leave game
			GameMode* dead = new DeadMode(gameData, gameState);
			gameState.enterMode(dead);
			battleOver = true;
		}

	return battleOver;
}

void BattleMode::onBattleWon()
{
	Player& player = gameState.getPlayer();

	cout<<"You won the battle!  ";
	cout<<"You gained "<<currMonster.ExpPts()<<" pts!"<<endl;
	cout<<"Monster dropped "<<currMonster.Money()<<" gold!"<<endl;

	//Battle spoils
	player.AddExp(currMonster.ExpPts());
	player.AddMoney(currMonster.Money());
	if(gameState.getRandInt(1, 100) > (100-DROP_CHANCE_PERCENT))
	{
		addMonsterEquipment();
	}

	char cont;
	cout<<endl;
	cout<<"Press X and enter to continue:  ";
	cin>>cont;

	//Check if player should level up (possibly move to AddExp?)
	if(player.ExpPts() >= player.NumToNext())
		player.LevelUp();

	gameState.requestExitCurrentMode();
}

void BattleMode::addMonsterEquipment()
{
	//postcondition: if monster has any Equipment, new EquipmentLines are allocated
	//for each one and added to the player's inventory.
	//The equipment added is displayed to the player.  No message is displayed
	//if the monster has no equipment.

	const vector<int> monsterWeaponIds = currMonster.getEquipmentIds(WEAPON);
	const vector<int> monsterArmorIds = currMonster.getEquipmentIds(ARMOR);
	const vector<int> monsterItemIds = currMonster.getEquipmentIds(ITEM);

	//If monster doesn't have anything to drop, don't need to display message
	//that they're dropping stuff and do a bunch of no-op loops
	if(monsterWeaponIds.empty() && monsterArmorIds.empty() && monsterItemIds.empty())
	{
		return;
	}

	Player& player = gameState.getPlayer();

	cout<<"Monster dropped: "<<endl;

	const vector<Equipment*> weapons = gameData.getWeapons();
	for(int i=0; i < monsterWeaponIds.size(); i++)
	{
		EquipmentLine weaponLine(weapons[monsterWeaponIds[i]]);
		player.AddEquipment(weaponLine);

		cout<<"  "<<weaponLine.pEquipment->getName()<<endl;
	}

	const vector<Equipment*> armor = gameData.getArmor();
	for(int i=0; i < monsterArmorIds.size(); i++)
	{
		EquipmentLine armorLine(armor[monsterArmorIds[i]]);
		player.AddEquipment(armorLine);

		cout<<"  "<<armorLine.pEquipment->getName()<<endl;
	}

	const vector<Equipment*> items = gameData.getItems();
	for(int i=0; i < monsterItemIds.size(); i++)
	{
		EquipmentLine itemLine(items[monsterItemIds[i]]);
		player.AddEquipment(itemLine);

		cout<<"  "<<itemLine.pEquipment->getName()<<endl;
	}
}
