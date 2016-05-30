#ifndef SRC_EFFECTS_H_
#define SRC_EFFECTS_H_

#include <vector>
#include "character.h"

using std::vector;

/* Functional interface for effects. */
typedef void (*EffectFunction)(Character& appliedBy, Character& target);

/* Contains all EffectFunctions - lets .dat files reference effect functions by an index*/
vector<EffectFunction> initEffects();
const vector<EffectFunction> EFFECTS = initEffects();

//----EffectFunctions START-----//
/* Functions below all conform to the EffectFunction interface.
 * If adding new effects, be sure to add them to the vector output by initEffects
 */

void fireDamageFunc(Character&, Character&);

//----EffectFunctions END-------//


#endif