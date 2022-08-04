/*
 * MultiValueHashTable.c
 *
 *  Created on: Nov 29, 2020
 *      Author: ise
 */
#include "MultiValueHashTable.h"


struct MultiHach_s{
	hashTable HashArray;
	int hash_size;
	EqualFunction FitFunc;
    CopyFunction copyV;
	TransformIntoNumberFunction Relevancy;
	FreeFunction FreeBird;
	FreeFunction FreeC;
    EqualFunction Equalelem;
};



MultiValueHashTable createMultiValueHashTable(int numOfHash, EqualFunction DoesFit, FreeFunction Freeb, FreeFunction freeVal, EqualFunction EqualElem, CopyFunction copyVal, EqualFunction EqualVal, TransformIntoNumberFunction Trans, PrintFunction printVal){
	MultiValueHashTable mvh = (MultiValueHashTable)malloc(sizeof(struct MultiHach_s));
	if(mvh == NULL){
		return NULL;
	}
	mvh->HashArray = createHashTable((CopyFunction)copyVal,(FreeFunction)freeVal,(PrintFunction) displayValue,(CopyFunction)copyVal,
			(FreeFunction)Freeb,(PrintFunction)printVal,(EqualFunction)EqualVal, (TransformIntoNumberFunction)Trans,numOfHash);
	mvh->FitFunc = DoesFit;
	mvh->hash_size = numOfHash;
	mvh->FreeBird = Freeb;
	mvh->FreeC = freeVal;
	mvh->Equalelem = EqualElem;
	mvh->copyV = copyVal;
	return mvh;
}


status destroyMultiValueHashTable(MultiValueHashTable mh){

	if(destroyHashTable(mh->HashArray)==failure){
		return failure;
	}

	free(mh);
	return success;
}

//key is attribute char* , value is jerry id (char*)
status addToMultiValueHashTable(MultiValueHashTable mh, Element val, Element key){
	if(mh==NULL || val==NULL){
		return failure;
	}

	if(lookupInHashTable(mh->HashArray, key)== NULL){
		LinkedList list = createLinkedList ((CopyFunction)mh->copyV,(FreeFunction) mh->FreeC,(PrintFunction) printf,(EqualFunction) strcmp, mh->Equalelem);
		if(list==NULL){
			return failure;
		}
		appendNode(list, val);
		return addToHashTable(mh->HashArray, key, list);
	}

	Element elem = lookupInHashTable(mh->HashArray, key);
	//get Linked List

	//Element list_value = getValue(elem);
	//get The linked list
    mh->FreeC(key);

	return appendNode(elem, val);

}
//
void displayMultiValueHashElementsByKey(MultiValueHashTable mvh, Element key){
	if(key==NULL || mvh == NULL){
		return;
	}

	Element elem = lookupInHashTable(mvh->HashArray, key);
	//get linked list of all the attributes of the ascii

	Element elem2 = searchByKeyInList(elem, key);
	//get the KeyValuePair of specific key (the value is Linked List)

	Element elem3= getValue(elem2);
	//get the linked list

	displayList(elem3);
	//display the linked list
}

Element lookupInMultiValueHashTable(MultiValueHashTable mh, Element key){

	return lookupInHashTable(mh->HashArray, key);

	//return getValue(KeyVal);
	//need get value
}

status removeFromMultiValueHashTable(MultiValueHashTable mvh,Element key, Element val){
	if(mvh==NULL || key==NULL || val== NULL){
		return failure;
	}
	Element bird = lookupInHashTable(mvh->HashArray, key);
	if(bird==NULL){
		return failure;
	}
	//Element Linked= getValue(KeyVal);
	if(remove_by_element(bird, val)==failure){
		return failure;
	}

	if(getLengthList(bird)==0){

		if (removeFromHashTable(mvh->HashArray,key) == failure)
			return failure;
		//return destroyList(bird);
	}


	return success;

}
