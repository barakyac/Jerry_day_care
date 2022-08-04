/*
 * Jerry.c
 *
 *  Created on: Nov 15, 2020
 *      Author: ise
 */

#include "Jerry.h"
//#include "LinkedList.h"
//#include "KeyValuePair.h"

Jerry* initjerry (char* id,int happiness, Origin* origin){
	if (id==NULL || origin==NULL)
		return NULL;
	Jerry* newjerry = (Jerry*)malloc(sizeof(Jerry));
	if (newjerry==NULL)
		return NULL;
	newjerry->Jerry_id=(char*)malloc(sizeof(char)*strlen(id)+1);
	if (newjerry->Jerry_id==NULL)
		return NULL;
	strcpy(newjerry->Jerry_id,id);
	newjerry->happiness=happiness;
	newjerry->Jerry_origin=origin;
	newjerry->numofattributes=0;
	newjerry->attributes=NULL;

	return newjerry;
}

Planet* initplanet (char* name, float x, float y, float z){
	if (name == NULL){
		return NULL;
	}
	Planet* newplanet = (Planet*)malloc(sizeof(Planet));
	if (newplanet==NULL)
		return NULL;
	newplanet->Planet_name=(char*)malloc(sizeof(char)*strlen(name)+1);
	if (newplanet->Planet_name==NULL)
		return NULL;
	strcpy(newplanet->Planet_name,name);
	newplanet->x=x;
	newplanet->y=y;
	newplanet->z=z;
	return newplanet;
}

PhysicalCharacteristics* initattribute(char* name, float value){
	if(value<0 || name==NULL){
		return NULL;
	}
	PhysicalCharacteristics* newattribute = (PhysicalCharacteristics*)malloc(sizeof(PhysicalCharacteristics));
	if (newattribute==NULL)
		return NULL;
	newattribute->name=(char*)malloc(sizeof(char)*strlen(name)+1);
	if (newattribute->name==NULL)
		return NULL;
	strcpy(newattribute->name,name);
	newattribute->value=value;
	return newattribute;
}


Origin* initorigin(char* name, Planet* planet){
	if (name==NULL || planet==NULL)
		return NULL;
	Origin* neworigin = (Origin*)malloc(sizeof(Origin));
	if (neworigin==NULL)
		return NULL;
	neworigin->origin_name=(char*)malloc(sizeof(char)*strlen(name)+1);
	if (neworigin->origin_name==NULL)
		return NULL;
	strcpy(neworigin->origin_name,name);
	neworigin->origin_planet=planet;
	return neworigin;

}

result is_attribute_exist (Jerry* jerry, char* attributename){
	if (jerry==NULL || attributename==NULL)
		return false;
	for (int i=0;i<jerry->numofattributes;i++)
	{
		if (strcmp(jerry->attributes[i]->name,attributename)==0)
			return true;
	}
	return false;
}

result addattribute (Jerry* jerry, PhysicalCharacteristics* attribute){
	if (jerry==NULL || attribute==NULL)
		return false;
	if(jerry->attributes==NULL){
		jerry->attributes= (PhysicalCharacteristics**)malloc(sizeof(PhysicalCharacteristics*));
		if(jerry->attributes==NULL){
			return false;
		}
		jerry->numofattributes=1;
		jerry->attributes[0]=attribute;
		return true;
	}
	jerry->numofattributes++;
	jerry->attributes = (PhysicalCharacteristics*)realloc(jerry->attributes, jerry->numofattributes* sizeof(PhysicalCharacteristics*));
	if (jerry->attributes == NULL){
		return false;
	}

	jerry->attributes[jerry->numofattributes-1] = attribute;
	return true;
}


result removeattribute (Jerry* jerry, char* attribute_name){
	if (jerry==NULL || attribute_name==NULL)
		return false;
	for (int i=0;i<jerry->numofattributes;i++)
	{
		if (strcmp(jerry->attributes[i]->name,attribute_name)==0)
			{
				//check if it was removed correctly
				free(jerry->attributes[i]->name);
				free(jerry->attributes[i]);
				for (int j=i;j<jerry->numofattributes-1;j++){
					jerry->attributes[j]=jerry->attributes[j+1];
				}

				jerry->numofattributes--;
				jerry->attributes = (PhysicalCharacteristics**)realloc(jerry->attributes,jerry->numofattributes* sizeof(PhysicalCharacteristics*));
				if(jerry->numofattributes!=0 && jerry->attributes==NULL){
					return false;
				}
				return true;
			}
	}
	return false;
}


result jerryprint (Element elem){
	Jerry* jerry = (Jerry*) elem;
	if (jerry==NULL)
		return false;
	printf("Jerry , ID - %s : \n",jerry->Jerry_id);
	printf("Happiness level : %d \n",jerry->happiness);
	printf("Origin : %s \n",jerry->Jerry_origin->origin_name);
	planetprint(jerry->Jerry_origin->origin_planet);
	if (jerry->numofattributes>0)
	{
		printf("Jerry's physical Characteristics available : \n\t");
		for (int i=0;i<jerry->numofattributes-1;i++)
			printf("%s : %.2f , ",jerry->attributes[i]->name,jerry->attributes[i]->value);
		printf("%s : %.2f \n",jerry->attributes[jerry->numofattributes-1]->name,jerry->attributes[jerry->numofattributes-1]->value);
	}
	return true;

}

result planetprint (Planet* planet){
	if (planet != NULL)
	{
		printf("Planet : %s (%.2f,%.2f,%.2f) \n",planet->Planet_name,planet->x,planet->y,planet->z);
		return true;
	}
	return false;

}


int EqualFunction_id(Element elem1, Element elem2){
	if (elem1 == NULL || elem2 == NULL)
		return -1;
	char* id1 = (char*) elem1;
	char* id2 = (char*) elem2;
	if (strcmp(id1,id2)==0)
		return 0;
	return 1;
}


int EqualFunction_jerry(Element id, Element jerry2){
	if (id == NULL || jerry2 == NULL)
			return -1;
	char* id1= (char*)id;
	Jerry* jerry = (Jerry*)jerry2;

	if (strcmp(id1,jerry->Jerry_id)==0)
		return 0;
	return 1;
}


status FreeFunction_jerry(Element element){
	if (element == NULL)
		return failure;
	Jerry* jerry_to_free = (Jerry*)element;
	free(jerry_to_free->Jerry_id);
	jerry_to_free->Jerry_id = NULL;
	free(jerry_to_free->Jerry_origin->origin_name);
	jerry_to_free->Jerry_origin->origin_name = NULL;
	free(jerry_to_free->Jerry_origin);
	for(int j=0; j<jerry_to_free->numofattributes;j++){
		free(jerry_to_free->attributes[j]->name);
		jerry_to_free->attributes[j]->name = NULL;
		free(jerry_to_free->attributes[j]);
	}
    free(jerry_to_free->attributes);
	free(jerry_to_free);
    return success;
}


Jerry* CopyFunction_Jerry(Jerry* jerry_to_copy){
	if (jerry_to_copy == NULL)
		return NULL;
	char* newjerryid = (char*)malloc(sizeof(char)*(strlen(jerry_to_copy->Jerry_id)+1));
	if (newjerryid == NULL)
		return NULL;

	strcpy(newjerryid,jerry_to_copy->Jerry_id);
	int newjerryhappiness = jerry_to_copy->happiness;
	Origin* newjerryorigin = initorigin(jerry_to_copy->Jerry_origin->origin_name, jerry_to_copy->Jerry_origin->origin_planet);
	Jerry* new_jerry = initjerry(newjerryid,newjerryhappiness,newjerryorigin);
	for (int i=0; i<jerry_to_copy->numofattributes; i++){
		addattribute(new_jerry, initattribute(jerry_to_copy->attributes[i]->name, jerry_to_copy->attributes[i]->value));
	}
	return new_jerry;
}


int TransformIntoNumberFunction_jerry(Element elem){
	char* id = (char*) elem;
	if (id == NULL)
		return -1;
	int ascii = 0, i=0;
	while (id[i] != '\0')
	  {
		ascii+=(int)id[i];
	    i++;
	  }
	return ascii;
}

int gethappiness(Element element){
	Jerry* jerry1 = (Jerry*)element;
	return jerry1->happiness;
}


status addhappiness(Element element, int game){
	Jerry* jerry1 = (Jerry*)element;
	int jerrycurrenthappiness = jerry1->happiness;
	if (game == 1)
	{
		if (jerrycurrenthappiness >= 20 && jerrycurrenthappiness <= 80)
			jerry1->happiness += 15;
		else if (jerrycurrenthappiness > 80)
			jerry1->happiness = 100;
		else if (jerrycurrenthappiness>=5 && jerrycurrenthappiness <=19)
			jerry1->happiness -= 5;
		else
			jerry1->happiness =0;
	}
	else if (game == 2)
	{
		if (jerrycurrenthappiness >= 50 && jerrycurrenthappiness <= 90)
			jerry1->happiness += 10;
		else if (jerrycurrenthappiness > 90)
			jerry1->happiness = 100;
		else if (jerrycurrenthappiness>=10 && jerrycurrenthappiness <=49)
			jerry1->happiness -= 10;
		else
			jerry1->happiness =0;
	}
	else if (game == 3)
	{
		if (jerrycurrenthappiness <=80)
			jerry1->happiness += 20;
		else if (jerrycurrenthappiness > 80)
			jerry1->happiness = 100;

	}
	return success;
}


int EqualFunction_jerry_attribute(Element char_att, Element j){
	Jerry* jerry= (Jerry*)j;
	char* att = (char*)char_att;
	int s= jerry->numofattributes;
	for(int i=0; i<s; i++){
		if(strcmp(att, jerry->attributes[i]->name)	==0){
			return 0;
		}
	}
	return 1;
}

int getAttributeValue(Jerry* jerry, char* att){
	for(int i= 0 ; i< jerry->numofattributes; i++){
		if(strcmp(jerry->attributes[i]->name,att)==0){
			return jerry->attributes[i]->value;
		}
	}
	return 10000000000;
}



void free_str(Element c){
    char* c1 = (char*) c;
    free(c);
}