#ifndef _SPR_H_
#define _SPR_H_

#include "utils/LinkList.h"

struct CharOptions{
	char *options;
	int size;
};

void print_usage();

void progress_data(char *str, unsigned long in, unsigned long total);

char* create_bar(unsigned long in, unsigned long total);

void use_file(FILE *fp);

unsigned long number_of_options(char* str, int size);

int get_char_number_of_options(char c);

struct CharOptions *get_char_options(char c);

void init_char_list(char c, struct LinkedList* linked_List);

struct LinkedList *permutation(char *str, int size, unsigned long total);

void permutation_recursion(char* str, int size, unsigned long total_words);

void perm_rec(char* str, char* bulid_str, int at, int size, 
		unsigned long total_words, unsigned long* num_words);

void perm_rec_to_file(char* str, char* build_str, int at, int size, 
	unsigned long total_words, unsigned long* num_words, unsigned long* pace);

void stable_main(int argc, char *argv[]);

#endif

