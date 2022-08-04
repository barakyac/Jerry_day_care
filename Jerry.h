/*
 * Jerry.h
 *
 *  Created on: Nov 15, 2020
 *      Author: ise
 */

#ifndef JERRY_H_
#define JERRY_H_

#include"Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Planet_s{
	char * Planet_name;
	float x,y,z;
}Planet;

typedef struct Origin_s{
	char *origin_name;
	Planet* origin_planet;
}Origin;

typedef struct PhysicalCharacteristics_s{
	char* name;
	float value;
}PhysicalCharacteristics;

typedef struct Jerry_s{
	char *Jerry_id;
	int happiness;
	Origin* Jerry_origin;
	int numofattributes;
	PhysicalCharacteristics **attributes;

}Jerry;

Jerry* initjerry (char* id,int happiness, Origin* origin);
Planet* initplanet (char* name, float x, float y, float z);
PhysicalCharacteristics* initattribute(char* name, float value);
Origin* initorigin(char* name, Planet* planet);
result is_attribute_exist (Jerry* jerry, char* attributename);
result addattribute (Jerry* jerry, PhysicalCharacteristics* attribute);
result removeattribute (Jerry* jerry, char* attribute_name);
result jerryprint (Element elem);
result planetprint (Planet* planet);

int EqualFunction_jerry(Element id, Element jerry2);
status FreeFunction_jerry(Element jerry_to_free);
Jerry* CopyFunction_Jerry(Jerry* jerry_to_copy);
int getAttributeValue(Jerry* jerry, char* att);

int TransformIntoNumberFunction_jerry(Element elem);

int EqualFunction_jerry_attribute(Element char_att, Element j);
int gethappiness(Element element);
status addhappiness(Element element, int game);
int EqualFunction_id(Element elem1, Element elem2);
void free_str(Element c);

#endif /* JERRY_H_ */
