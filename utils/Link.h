#ifndef _LINK_H_
#define _LINK_H_

struct Link{
	char* c;
	struct Link *nextLink;
};

struct Link *createLink(char* c, int size);

struct Link *createLink2(char* c, int size, struct Link *next);

#endif
