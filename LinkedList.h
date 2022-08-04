/*
 * LinkedList.h
 *
 *  Created on: Nov 29, 2020
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"


typedef struct Node_s* Node;
typedef struct LinkedList_s* LinkedList;

Node new_node(LinkedList linkedlist,Element element);
LinkedList createLinkedList (CopyFunction copy_f,FreeFunction free_f,PrintFunction print_f,EqualFunction equal_f, EqualFunction EqulV);
status destroyList (LinkedList linkedlist);
status appendNode (LinkedList linkedlist, Element element);
status deleteNode(LinkedList linkedlist, Element element);
status displayList(LinkedList linkedlist);
Element getDataByIndex(LinkedList linkedlist,int index);
int getLengthList(LinkedList linkedlist);
Element searchByKeyInList(LinkedList linkedlist,Element element);
status remove_by_element(LinkedList linkedlist,Element element);
int get_idex(LinkedList list, Element elem);
status append_in_index_List(LinkedList list, Element elem, int index);

#endif /* LINKEDLIST_H_ */
