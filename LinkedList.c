/*
 * LinkedList.c
 *
 *  Created on: Nov 29, 2020
 *      Author: ise
 */


#include "LinkedList.h"
#include "KeyValuePair.h"

struct Node_s {
	Element element;
	Node next;
};


struct LinkedList_s {
	Node head;
	Node tail;
	CopyFunction copynode;
	FreeFunction free_element;
	PrintFunction printnode;
	EqualFunction equalnode;
	EqualFunction equal;

};

Node new_node(LinkedList linkedlist,Element element){
	if (linkedlist == NULL)
		return NULL;
	Node newnode = (Node)malloc(sizeof(struct Node_s));
	if (newnode == NULL)
		return NULL;
	newnode->element=element;
	newnode->next = NULL;
	return newnode;

}


LinkedList createLinkedList (CopyFunction copy_f,FreeFunction free_f,PrintFunction print_f,EqualFunction equal_f, EqualFunction EqulV){
	LinkedList newlinkedlist = (LinkedList)malloc(sizeof(struct LinkedList_s));
	if (newlinkedlist == NULL)
		return NULL;
	newlinkedlist->head=NULL;
	newlinkedlist->tail=NULL;
	newlinkedlist->copynode = copy_f;
	newlinkedlist->free_element = free_f;
	newlinkedlist->printnode = print_f;
	newlinkedlist->equalnode = equal_f;
	newlinkedlist->equal=EqulV;
	return newlinkedlist;
}


status destroyList (LinkedList linkedlist){
	if (linkedlist == NULL)
		return failure;
	Node temp_node = linkedlist->head;
	Node temp_node_next = linkedlist->head;
	while (temp_node != NULL)
	{
		temp_node_next = temp_node->next;
		linkedlist->free_element(temp_node->element);
		free(temp_node);
		temp_node = temp_node_next;
	}
	free (linkedlist);
	//free (temp_node_next);
	return success;

}

status appendNode (LinkedList linkedlist, Element element){
	if (linkedlist == NULL || element == NULL)
		return failure;
	Node node_to_add = new_node(linkedlist, element);
	if (linkedlist->head != NULL)
	{
		linkedlist->tail->next = node_to_add;
		linkedlist->tail = node_to_add;
	}
	else
	{
		linkedlist->head = node_to_add;
		linkedlist->tail = node_to_add;
	}
	return success;
}

//element is jerry id (char*)
status deleteNode(LinkedList linkedlist, Element element){
	if (linkedlist == NULL || element == NULL)
		return failure;
	Node temp_node = linkedlist->head;
	Node temp_node_next = linkedlist->head->next;

	Element elem1, elem2;
	elem1 = getKey(temp_node->element);
	if (temp_node_next != NULL)
		elem2 = getKey(temp_node_next->element);


	if (linkedlist->equalnode(element,elem1) == 0)
	{
		if (temp_node->next == NULL)
			linkedlist->tail=temp_node;
		linkedlist->head = temp_node_next;
		linkedlist->free_element(temp_node->element);
		free(temp_node);
		return success;
	}
	while (temp_node_next != NULL)
	{
		if (temp_node_next == NULL)
			return failure;
		else
		{
			if (linkedlist->equalnode(element,elem2) == 0)
				break;
			temp_node = temp_node->next;
			temp_node_next = temp_node_next->next;
			elem1 = getKey(temp_node->element);
			if (temp_node_next != NULL)
				elem2 = getKey(temp_node_next->element);
		}
	}
	if (temp_node_next->next == NULL)
		linkedlist->tail=temp_node;
	temp_node->next = temp_node_next->next;
	linkedlist->free_element(temp_node_next->element);
    free(temp_node_next);
	return success;
}


status displayList(LinkedList linkedlist){
	Node temp_node = linkedlist->head;
	Element elem;
	while (temp_node != NULL)
	{
		elem = temp_node->element;
		linkedlist->printnode(elem);
		temp_node = temp_node->next;
	}
	return success;
}


Element getDataByIndex(LinkedList linkedlist,int index){
	if (linkedlist == NULL)
		return NULL;
	Node temp_node = linkedlist->head;
	if (index == 0)
		return temp_node->element;
	int linkedindex = 0;
	for (int i=0;i<index+1;i++)
	{
		if (temp_node == NULL)
			return NULL;
		if (temp_node != NULL && index == linkedindex)
			return temp_node->element;
		temp_node = temp_node->next;
		linkedindex++;
	}
	return NULL;
}


int getLengthList(LinkedList linkedlist){
	if (linkedlist == NULL)
		return 0;
	Node temp_node = linkedlist->head;
	if (temp_node == NULL)
		return 0;

	int len = 0;
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		len++;
	}
	return len;
}







Element searchByKeyInList(LinkedList linkedlist,Element element){
	if(linkedlist==NULL || element==NULL)
		return NULL;

	Node temp = linkedlist->head;
	Element elem;
	while(temp!=NULL){
		elem = getKey(temp->element);

		if(linkedlist->equalnode(element, elem)==0)
			return getValue(temp->element);
		temp = temp->next;
	}
	return NULL;


}





status remove_by_element(LinkedList linkedlist,Element element){
	if(linkedlist==NULL || element==NULL)
		return failure;
	Node temp_node = linkedlist->head;
	Node temp_node_next = linkedlist->head->next;

	if (linkedlist->equal((char*)element,(char*)temp_node->element) == 0)
	{
		if (temp_node->next == NULL)
			linkedlist->tail=temp_node;
		linkedlist->free_element(temp_node->element);
		free(temp_node);
		linkedlist->head = temp_node_next;
		return success;
	}
	while (temp_node_next != NULL)
	{
		if (temp_node_next == NULL)
			return failure;
		else
		{
			if (strcmp((char*)element,(char*)temp_node_next->element) == 0)
				break;
			temp_node = temp_node->next;
			temp_node_next = temp_node_next->next;
		}
	}
	if (temp_node_next->next == NULL)
		linkedlist->tail=temp_node;
	temp_node->next = temp_node->next->next;
	linkedlist->free_element(temp_node_next->element);
	free(temp_node_next);
	return success;
}


int get_idex(LinkedList list, Element elem){
	if(list==NULL || elem ==NULL){
		return -1;
	}
	Node temp = list->head;
	int index =0;
	while (temp!=NULL){
		if(list->equalnode(temp->element, elem)==0){
			return index;
		}
		temp= temp->next;
		index++;
	}
	return -1;
}

status append_in_index_List(LinkedList list, Element elem, int index){
	Node newNode= new_node(list, elem);
	Node temp = list->head;
	Node Last;
	//Node next= temp->next;
	if(index==0){
		newNode->next = temp;
		list->head = newNode;
		return success;
	}
	while(temp != NULL){
		if(index  == 0){
			if(temp->next!= NULL){
				newNode->next = temp->next->next;
			}
			else{
				newNode->next=NULL;
			}
			newNode->next = temp;
			Last->next = newNode;
			return success;
		}
		Last = temp;
		temp= temp->next;
		index--;
	}
	return failure;



}


