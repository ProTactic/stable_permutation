#ifndef _LINKLIST_H_
#define _LINKLIST_H_

struct LinkList{
	struct Link *head;
	struct Link *end;
};

struct LinkList * createEmptyLinkList();

struct LinkList * createLinkList(char* c, int size);

void append(struct LinkList *list, char* c, int size);

void deleteList(struct LinkList *linkList);

void printList(struct LinkList *linkList);

#endif
