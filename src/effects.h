#ifndef SRC_EFFECTS_H_
#define SRC_EFFECTS_H_

#include <vector>
#include "element.h"
#include "equipment.h"

using std::vector;

class Character; //Forward declaration since Spell and Character are interdependent

/* Functional interface for effects. */
typedef void (*EffectFunction)(Character& appliedBy, Character& target);

/* Contains all EffectFunctions - lets .dat files reference effect functions by an index*/
vector<EffectFunction> initEffects();
const vector<EffectFunction> EFFECTS = initEffects();

//----EffectFunctions-----------//
/* Functions below all conform to the EffectFunction interface.
 * If adding new effects, be sure to add them to the vector output by initEffects
 */

void fearFunc(Character&, Character&);
void courageFunc(Character&, Character&);
void enervate(Character&, Character&);
void drainFunc(Character&, Character&);
void channelFunc(Character&, Character&);
void meltdownFunc(Character&, Character&);

//----Monster-only EffectFunctions
void monsterFearFunc(Character&, Character&);
void monsterCourageFunc(Character&, Character&);
void monsterMeltdownFunc(Character&, Character&);

//----Effect Helper functions---//
const int BASE_MP_DROP = 10;
const int BASE_DRAIN_HP = 15;

bool validateChannelDamage(Character&, int);
void applyWeaknessTo(Character&, Element);
void removeWeaknessFrom(Character&, Element);
void meltdownEquipment(Character&, Character&, EquipmentLine&);

#endif
