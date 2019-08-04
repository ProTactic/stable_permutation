#ifndef _LINK_H_
#define _LINK_H_

struct Link{
	char* c;
	struct Link* next_link;
};

struct Link *create_link(char* c, int size);

struct Link *create_link2(char* c, int size, struct Link *next);

#endif
