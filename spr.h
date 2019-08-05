#ifndef _SPR_H_
#define _SPR_H_

#include "utils/LinkList.h"

struct CharOptions{
	char *options;
	int size;
};

void print_usage();

struct CharOptions *get_char_options(char c);

void init_char_list(char c, struct LinkedList* linked_List);

struct LinkedList *permutation(char *str, int size);

void permutation_recursion(char* str, int size);

void perm_rec(char* str, char* bulid_str, int at, int size);



void stable_main(int argc, char *argv[]);

#endif
