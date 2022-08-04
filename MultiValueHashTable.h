#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H

#include "HashTable.h"
#include "KeyValuePair.h"
#include "Defs.h"
#include "LinkedList.h"

typedef struct MultiHach_s *MultiValueHashTable;


MultiValueHashTable createMultiValueHashTable(int numOfHash, EqualFunction DoesFit, FreeFunction Freeb, FreeFunction freeVal, EqualFunction EqualElem, CopyFunction copyVal, EqualFunction EqualVal, TransformIntoNumberFunction Trans, PrintFunction printVal);
status destroyMultiValueHashTable(MultiValueHashTable mh);

status addToMultiValueHashTable(MultiValueHashTable mh, Element val, Element key);
void displayMultiValueHashElementsByKey(MultiValueHashTable mvh, Element key);
Element lookupInMultiValueHashTable(MultiValueHashTable mh, Element key);
status removeFromMultiValueHashTable(MultiValueHashTable mvh,Element key, Element val);




#endif /* HASH_TABLE_H */
