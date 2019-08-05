#ifndef _LINKLIST_H_
#define _LINKLIST_H_

struct LinkedList{
	struct Link *head;
	struct Link *end;
};

struct LinkedList * create_empty_linked_list();

struct LinkedList * create_link_list(char* c, int size);

void append(struct LinkedList *list, char* c, int size);

void delete_list(struct LinkedList *linked_List);

void print_list(struct LinkedList *linked_List, int fd);

#endif
