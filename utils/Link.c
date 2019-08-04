#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "Link.h"

struct Link *createLink(char* c, int size){
	struct Link *link = (struct Link*)malloc(sizeof(struct Link));
	char* tmp_c = (char*)malloc(size);
	for(int i=0; i<size; i=i+1){
		*(tmp_c+i) = c[i];
	}
	link->c = tmp_c;
	link->nextLink = NULL;

	return link;
}

struct Link *createLink2(char* c, int size, struct Link *next){
	struct Link *link = (struct Link*)malloc(sizeof(struct Link));
	char* tmp_c = (char*)malloc(size);
	for(int i=0; i<size; i=i+1){
		*(tmp_c+i) = c[i];
	}
	link->c = tmp_c;
	link->nextLink = next;
}
