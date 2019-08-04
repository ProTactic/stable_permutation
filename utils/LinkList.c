#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkList.h"
#include "Link.h"

/*
	Create an empty linked list, set the head,end vars from the
	LinkedList struct to be null.
	Return - a pointer to the new LinkedList struct
*/
struct LinkedList* create_empty_linked_list(){
	struct LinkedList* linked_list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
	linked_list->head = NULL;
	linked_list->end = NULL;

	return linked_list;
}

/*
	Create an empty linked list, set the head,end vars from the
	LinkedList struct to new link with the char* c variable.
	Return - a pointer to the new LinkedList struct
*/
struct LinkedList * create_link_list(char* c, int size){
	struct Link* link = create_link(c, size);
	struct LinkedList* linked_list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
	linked_list->head = link;
	linked_list->end = link;

	return linked_list;
}

/*
	Create new link with the char* c variable, and
	append it to the end of the linked list
*/
void append(struct LinkedList *list, char* c, int size){
	if(list != NULL){
		if(list->head != NULL && list->end != NULL)
		{
			struct Link* tmp = create_link(c, size);
			list->end->next_link = tmp;
			list->end = tmp;
		}
		else if(list->head == NULL && list->end == NULL){
			struct Link* tmp = create_link(c, size);
			list->head = tmp;
			list->end = tmp;
		}
	}
}

/*
	Delete all the data of the list from the memory
*/
void delete_list(struct LinkedList* linked_list){
	if(linked_list != NULL){
		struct Link* current = linked_list->head;
		while(current != NULL){
			struct Link* tmp = current;
			current = current->next_link;
			free(tmp);
		}
		free(linked_list);
	}
}

/*
	Print the char array of each link in the list by order
*/
void print_list(struct LinkedList *linked_list){
	if(linked_list != NULL){
		struct Link* current = linked_list->head;
		while(current != NULL){
			printf("%s\n", current->c);
			current = current->next_link;
		}
	}
}


