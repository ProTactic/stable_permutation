#ifndef _SPR_H_
#define _SPR_H_

#include "utils/LinkList.h"

struct CharOptions{
	char *options;
	int size;
};

void print_usage();

void use_file(FILE *fp);

unsigned long number_of_options(char* str, int size);

int get_char_number_of_options(char c);

struct CharOptions *get_char_options(char c);

void init_char_list(char c, struct LinkedList* linked_List);

struct LinkedList *permutation(char *str, int size);

void permutation_recursion(char* str, int size);

void perm_rec(char* str, char* bulid_str, int at, int size);



void stable_main(int argc, char *argv[]);

#endif
