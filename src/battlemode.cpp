#include <sstream>
#include "logging/log.h"
#include "battlemode.h"
#include "battlestrategy.h"
#include "deadmode.h"
#include "fightaction.h"
#include "gamestate.h"
#include "levelupchooser.h"
#include "playercastspellaction.h"
#include "runaction.h"
#include "skipturnaction.h"
#include "statsdisplayer.h"
#include "useitemaction.h"
#include "util/randutils.h"

BattleMode::BattleMode(Monster monster, GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, true),
	  currMonster(monster),
	  actionQueue()
{

}

BattleMode::~BattleMode()
{
	//postcondition: battle-only statuses are removed from the player and monster
	//objects, and if there were unused actions in the queue b/c we returned
	//from executeActions() early because battle ended, they will be deleted.

	//Battle-only statuses don't last outside of battle
	gameState.getPlayer().removeStatusesFor(BATTLE_ONLY);
	currMonster.removeStatusesFor(BATTLE_ONLY);

	//Free up unused BattleActions
	while(!actionQueue.empty())
	{
		BattleAction* action = actionQueue.front();

		actionQueue.pop();
		delete action;
	}
}

void BattleMode::processStatusEffects()
{
	//postcondition: the super class processStatusEffects method is run, then
	//processStatusEffets() is called on the current monster too to process their
	//statuses too.

	GameMode::processStatusEffects();
	currMonster.processStatusEffects();
}

void BattleMode::run()
{
	//postcondition: calls super::run(), and then calls executeActions() to run
	//enqueued actions (if any).

	if(testEndConditions())
	{
		return; //Status effects processed at the start of this turn could end the battle
	}

	GameMode::run();
	executeActions();
}

void BattleMode::updateDisplay()
{
	if(gameState.getPlayer().hasStatus(STUNNED)) //TODO once combat results are displayed in the log window, don't need to check this here since always drawing the battle stats in the info window is fine.
	{
		return;
	}

	int choice;

	cout<<"*************ENEMY! You went to battle!*************"<<endl;
	StatsDisplayer::battleMainDisplayFor(gameState.getPlayer());
	cout<<endl;
	cout<<endl;
	cout<<endl;
	StatsDisplayer::battleMainDisplayFor(currMonster);
	cout<<"*****************"<<endl;
	displayFightChoice();
	displayCastSpellChoice();
	cout<<"*3)Use Item     *"<<endl;
	cout<<"*4)Run          *"<<endl;
	cout<<"*****************"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;
}

void BattleMode::displayFightChoice()
{
	if(gameState.getPlayer().hasStatus(BLIND))
	{
		cout<<"*  Blind!       *"<<endl;
	}
	else
	{
		cout<<"*1)Fight        *"<<endl;
	}
}

void BattleMode::displayCastSpellChoice()
{
	if(gameState.getPlayer().hasStatus(MUTE))
	{
		cout<<"*  Mute!        *"<<endl;
	}
	else
	{
		cout<<"*2)Cast Spell   *"<<endl;
	}
}

bool BattleMode::processInput()
{
	//postcondition: prompts the player to choose a battle action if he/she is
	//not stunned, and if not creates a BattleAction matching the his/her choice
	//and enqueues it in the proper order depending whether the player's speed
	//is greater than the monster's.  setup() is called on the action before any
	//actions are are enqueued, and if the action is aborted, this method will
	//return early to allow the player to choose a new action.
	//If the player is stunned when prompting for input, their turn is skipped.
	//Returns false if the player's BattleAction is aborted, so that turn is not
	//not advanced until a BattleAction is enqueued.  True otherwise.

	Player& player = gameState.getPlayer();
	int choice = SKIP_TURN_CHOICE;

	//If the player is stunned don't await input from them, b/c there turn should be skipped
	if(!player.hasStatus(STUNNED))
	{
		do
		{
			cout<<"Please choose an option:  "<<endl;
			cin>>choice;
		}while(!validateChoice(choice,4));
	}

	//Handle player choice, and set up action they chose.
	BattleAction* playerAction;
	switch(choice)
	{
		case SKIP_TURN_CHOICE:
			playerAction = new SkipTurnAction(player);
			break;
		case 1:
			playerAction = new FightAction(player, currMonster);
			break;
		case 2:
			playerAction = new PlayerCastSpellAction(player, currMonster);
			break;
		case 3:
			playerAction = new UseItemAction(player, currMonster);
			break;
		case 4:
			playerAction = new RunAction(gameState);
			break;
	}

	playerAction->setup();
	if(playerAction->isAborted())
	{
		return false; //player aborted action during setup, so let them go back and choose again
	}

	BattleAction* monsterAction = makeMonsterAction();

	//Enqueue actions for battle turn
	if(player.getEffectiveSP() >= currMonster.getEffectiveSP()) {
		actionQueue.push(playerAction);
		actionQueue.push(monsterAction);
	} else {
		actionQueue.push(monsterAction);
		actionQueue.push(playerAction);
	}

	return true;
}

BattleAction* BattleMode::makeMonsterAction()
{
	//postcondition: asks the monster's BattleStrategy to allocate a new action
	//to be queued, and calls setup() on that action.  If the action is aborted,
	//because it can't be run for some reason (e.g. not enough MP to cast spells),
	//a fight action is chosen.
	//The SkipTurnAction will be returned if the monster has Stunned status

	if(currMonster.hasStatus(STUNNED))
	{
		return new SkipTurnAction(currMonster);
	}

	BattleStrategy* strat = currMonster.getBattleStrategy();
	return strat->makeBattleAction(currMonster, gameState.getPlayer());
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

	if(currMonster.getHP() <= 0)
		{
			onBattleWon();
			battleOver = true;
		}

	if(gameState.getPlayer().getHP() <= 0)
		{
			//if player dies, leave game
			GameMode* dead = new DeadMode(gameData, gameState);
			gameState.requestEnterMode(dead);
			battleOver = true;
		}

	return battleOver;
}

void BattleMode::onBattleWon()
{
	Player& player = gameState.getPlayer();

	std::stringstream msgs;
	msgs<<"You won the battle!  "<<endl
		<<"You gained "<<currMonster.ExpPts()<<" pts!"<<endl
		<<"Monster dropped "<<currMonster.Money()<<" gold!";
	log(msgs.str());

	//Battle spoils
	player.AddExp(currMonster.ExpPts());
	player.AddMoney(currMonster.Money());
	if(getRandIntBetween(1, 100) > (100-DROP_CHANCE_PERCENT))
	{
		addMonsterEquipment();
		learnMonsterSpells();
	}

	char cont;
	cout<<endl;
	cout<<"Press X and enter to continue:  ";
	cin>>cont;

	//Check if player should level up (possibly move to AddExp?)
	if (player.ExpPts() >= player.NumToNext())
	{
		onLevelUp();
	}

	gameState.requestExitCurrentMode();
}

void BattleMode::addMonsterEquipment()
{
	//postcondition: if monster has any Equipment, new EquipmentLines are allocated
	//for each one and added to the player's inventory.
	//The equipment added is displayed to the player.  No message is displayed
	//if the monster has no equipment.

	vector<const Equipment*>* monsterEquipment = currMonster.getAllEquipment();
	if(monsterEquipment->empty())
	{
		//If monster doesn't have anything to drop, don't need to display message
		//that they're dropping stuff and do a no-op loop
		delete monsterEquipment;
		return;
	}

	Player& player = gameState.getPlayer();

	std::stringstream equipmentMsg;
	log("Monster dropped: ");
	for(int i=0; i < monsterEquipment->size(); i++)
	{
		EquipmentLine eqLine((*monsterEquipment)[i]);
		player.AddEquipment(eqLine);

		equipmentMsg<<"  "<<eqLine.pEquipment->getName();
		log(equipmentMsg.str());
		equipmentMsg.clear();
		equipmentMsg.str("");
	}

	delete monsterEquipment;
}

void BattleMode::learnMonsterSpells()
{
	//postcondition: all spell ids the monster has are converted to spell
	//pointers and the player learns any he/she didn't alreayd know.

	std::stringstream learnedSpell;

	const set<const SpellTemplate*>& monsterSpells = currMonster.getDroppableSpells();
	for(set<const SpellTemplate*>::const_iterator it = monsterSpells.begin(); it != monsterSpells.end(); it++)
	{
		if(gameState.getPlayer().hasSpell(*it))
		{
			continue;
		}

		gameState.getPlayer().AddSpell(*it);
		learnedSpell<<"You learned '"<<(*it)->getName()<<"' from a scroll the monster was carrying!";
		log(learnedSpell.str());
		learnedSpell.clear();
		learnedSpell.str("");
	}
}

void BattleMode::onLevelUp()
{
	Player& player = gameState.getPlayer();

	std::stringstream lvlMsg;
	lvlMsg<<"Congratulations, your level is now "<<(player.Level() +1)<<"!";
	log(lvlMsg.str());

	LevelUpChooser chooser;
	chooser.run();

	const LvlUpOpt* choice = chooser.getChoice();
	player.LevelUp(*choice);
}
