#ifndef SRC_EFFECTS_H_
#define SRC_EFFECTS_H_

#include <vector>

using std::vector;

class Character; //Forward declaration since Spell and Character are interdependent

enum Element {fire, air, earth, water, none};

/* Functional interface for effects. */
typedef void (*EffectFunction)(Character& appliedBy, Character& target);

/* Contains all EffectFunctions - lets .dat files reference effect functions by an index*/
vector<EffectFunction> initEffects();
const vector<EffectFunction> EFFECTS = initEffects();

//----EffectFunctions-----------//
/* Functions below all conform to the EffectFunction interface.
 * If adding new effects, be sure to add them to the vector output by initEffects
 */

void fireDamageFunc(Character&, Character&);
void healFunc(Character&, Character&);

//----Effect Helper functions---//
const int BASE_ELEMENTAL_DAMAGE = 20;

void elementalDamage(Character&, Character&, int, Element);

#endif
