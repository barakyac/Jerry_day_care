/*FreeFunction free_v,
 * KeyValuePair.h
 *
 *  Created on: Nov 29, 2020
 *      Author: ise
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"


typedef struct Keyvaluepair_s* KeyValuePair;

KeyValuePair createKeyValuePair (CopyFunction copy_f,FreeFunction free_v,FreeFunction free_k,PrintFunction print_f,TransformIntoNumberFunction transform_f,EqualFunction equal_f, Element key, Element value);
status destroyKeyValuePair (KeyValuePair keyvaluepair);
status displayValue(KeyValuePair keyvaluepair);
status displayKey(KeyValuePair keyvaluepair);
Element getValue(KeyValuePair keyvaluepair);
Element getKey(KeyValuePair keyvaluepair);
result isEqualKey(KeyValuePair keyvaluepair, Element key);

#endif /* KEYVALUEPAIR_H_ */
