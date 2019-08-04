#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkList.h"
#include "Link.h"


struct LinkList * createEmptyLinkList(){
	struct LinkList *linkList = (struct LinkList*)malloc(sizeof(struct LinkList));
	linkList->head = NULL;
	linkList->end = NULL;

	return linkList;
}

struct LinkList * createLinkList(char* c, int size){
	struct Link *link = createLink(c, size);
	struct LinkList *linkList = (struct LinkList*)malloc(sizeof(struct LinkList));
	linkList->head = link;
	linkList->end = link;

	return linkList;
}

void append(struct LinkList *list, char* c, int size){
	if(list != NULL){
		if(list->head != NULL && list->end != NULL)
		{
			struct Link *tmp = createLink(c, size);
			list->end->nextLink = tmp;
			list->end = tmp;
		}
		else if(list->head == NULL && list->end == NULL){
			struct Link *tmp = createLink(c, size);
			list->head = tmp;
			list->end = tmp;
		}
	}
}

void deleteList(struct LinkList *linkList){
	if(linkList != NULL){
		struct Link *current = linkList->head;
		while(current != NULL){
			struct Link *tmp = current;
			current = current->nextLink;
			free(tmp);
		}
		free(linkList);
	}
}

void printList(struct LinkList *linkList){
	if(linkList != NULL){
		struct Link *current = linkList->head;
		while(current != NULL){
			printf("%s\n", current->c);
			current = current->nextLink;
		}
	}
}


