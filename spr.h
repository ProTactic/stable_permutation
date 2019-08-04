#ifndef _SPR_H_
#define _SPR_H_

#include "utils/LinkList.h"

struct CharOptions{
	char *options;
	int size;
};

void print_usage();

struct CharOptions *getLUChar(char c);

void init_char_list(char c, struct LinkList* linkList);

struct LinkList *permutation(char *str, int size);

void stable_main(int argc, char *argv[]);

#endif
