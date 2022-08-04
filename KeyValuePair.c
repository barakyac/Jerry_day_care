/*
 * KeyValuePair.c
 *
 *  Created on: Nov 29, 2020
 *      Author: ise
 */
#include "KeyValuePair.h"

struct Keyvaluepair_s {
	Element Key;
	Element Value;
	CopyFunction copy;
	FreeFunction freekey;
	FreeFunction freeValue;
	PrintFunction print;
	TransformIntoNumberFunction transform;
	EqualFunction equal;
};


KeyValuePair createKeyValuePair (CopyFunction copy_f,FreeFunction free_v,FreeFunction free_k,PrintFunction print_f,TransformIntoNumberFunction transform_f,EqualFunction equal_f, Element key, Element value){
	KeyValuePair keyvaluepair = (KeyValuePair)malloc(sizeof(struct Keyvaluepair_s));
	if (keyvaluepair == NULL)
		return NULL;
	keyvaluepair->Key = key;
	keyvaluepair->Value = value;
	keyvaluepair->copy = copy_f;
	keyvaluepair->freeValue = free_v;
	keyvaluepair->freekey = free_k;
	keyvaluepair->print = print_f;
	keyvaluepair->transform = transform_f;
	keyvaluepair->equal = equal_f;
	return keyvaluepair;
}


status destroyKeyValuePair (KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL)
		return failure;
	if (keyvaluepair->Value != NULL) {
        keyvaluepair->freeValue(keyvaluepair->Value);
        keyvaluepair->freekey(keyvaluepair->Key);
    }
	free(keyvaluepair);
	keyvaluepair = NULL;
	return success;
}
status displayValue(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL)
		return failure;
	keyvaluepair->print(keyvaluepair->Value);
	return success;
}
status displayKey(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL)
		return failure;
	keyvaluepair->print(keyvaluepair->Key);
	return success;
}
Element getValue(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL)
		return NULL;
	return (keyvaluepair->Value);
}

Element getKey(KeyValuePair keyvaluepair){
	if (keyvaluepair == NULL)
		return NULL;
	return keyvaluepair->Key;
}
result isEqualKey(KeyValuePair keyvaluepair, Element key){
	if (keyvaluepair == NULL || key == NULL)
		return false;
	if (keyvaluepair->equal(keyvaluepair->Key,key)==true)
		return true;
	return false;
}
