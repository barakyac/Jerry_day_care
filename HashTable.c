/*
 * HashTable.c
 *
 *  Created on: Nov 29, 2020
 *      Author: ise
 */


#include "HashTable.h"


struct hashTable_s{
	LinkedList *lnk;
	int hashsize;
	CopyFunction copykey;
	FreeFunction freekey;
	PrintFunction printkey;

	CopyFunction copyvalue;
	FreeFunction freevalue;
	PrintFunction printvalue;

	TransformIntoNumberFunction transformkvp;
	EqualFunction equalkvp;
};


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	hashTable newhashtable = (hashTable)malloc(sizeof(struct hashTable_s));
	if (newhashtable == NULL)
		return NULL;
	LinkedList *linked =(LinkedList*)malloc(hashNumber * sizeof(LinkedList));
	if (linked == NULL)
		return NULL;
	newhashtable->lnk = linked;
	for (int i=0;i<hashNumber;i++)
		newhashtable->lnk[i] = 	createLinkedList ((CopyFunction)copyValue,(FreeFunction)destroyKeyValuePair,(PrintFunction)printKey,(EqualFunction)equalKey, equalKey);


	newhashtable->copykey = copyKey;
	newhashtable->freekey = freeKey;
	newhashtable->printkey = printKey;

	newhashtable->copyvalue = copyValue;
	newhashtable->freevalue = freeValue;
	newhashtable->printvalue = printValue;

	newhashtable->transformkvp = transformIntoNumber;
	newhashtable->equalkvp = equalKey;
	newhashtable->hashsize = hashNumber;


	return newhashtable;

}
status destroyHashTable(hashTable ht){
	if (ht == NULL)
		return failure;
	for (int i=0;i<ht->hashsize;i++){
        if (destroyList(ht->lnk[i]) == failure){
            return failure;
        }
	}

	free(ht->lnk);
    free(ht);

	return success;

}

//key is jerry id (char*), value is *Jerry

status addToHashTable(hashTable ht, Element key,Element value){
	if (ht == NULL || key == NULL || value == NULL)
		return failure;

	KeyValuePair kvp = createKeyValuePair((CopyFunction)ht->copykey,(FreeFunction)ht->freevalue, (FreeFunction)ht->freekey,(PrintFunction)ht->printvalue,(TransformIntoNumberFunction)ht->transformkvp,(EqualFunction)ht->equalkvp, key, value);
	int ascii = ht->transformkvp(key) % ht->hashsize;
	if (appendNode(ht->lnk[ascii],(Element)kvp) == failure)
		return failure;

	return success;



}
Element lookupInHashTable(hashTable ht, Element key){
	if (ht == NULL || key == NULL)
		return NULL;
	int ascii = ht->transformkvp(key) % ht->hashsize;
	Element elem = searchByKeyInList(ht->lnk[ascii],key);
	return elem;

}

// key is jerry id (char*)
status removeFromHashTable(hashTable ht, Element key){
	if (ht == NULL || key == NULL)
		return failure;

	int ascii = ht->transformkvp(key) % ht->hashsize;
	if( deleteNode(ht->lnk[ascii], key) == failure)
		return failure;
	return success;

}


status displayHashElements(hashTable ht){
    for(int i=0; i<ht->hashsize; i++){
        ht->printvalue(ht->lnk[i]);
    }
	return success;
}
