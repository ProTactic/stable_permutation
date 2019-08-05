#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "Link.h"

/*
	Create a link from the given args
	char* c - an array of chars
	size - the size of the char array
	Return : strict Link *, the pointer to the new link stracture
*/
struct Link* create_link(char* c, int size){
	struct Link* link = (struct Link*)malloc(sizeof(struct Link));
	char* tmp_c = (char*)malloc(size);
	for(int i=0; i<size; i=i+1){
		*(tmp_c+i) = c[i];
	}
	link->c = tmp_c;
	link->next_link = NULL;

	return link;
}

/*
	Simular to create_link just with the option to sent the next link
*/
struct Link* create_link2(char* c, int size, struct Link *next){
	struct Link* link = (struct Link*)malloc(sizeof(struct Link));
	char* tmp_c = (char*)malloc(size);
	for(int i=0; i<size; i=i+1){
		*(tmp_c+i) = c[i];
	}
	link->c = tmp_c;
	link->next_link = next;

	return link;
}
