#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spr.h"
#include "utils/LinkList.h"
#include "utils/Link.h"

void print_usage(){
	printf("%s ",
		"This is the stable permutaion software\n"
		"usage: spr text\n");
}

/*
	Return all the option of stable permutation of a char.
	for regualr latter, for example a is a, A
	and for any digit will be 0-9
*/
struct CharOptions* get_char_options(char c){

	struct CharOptions* chars = (struct CharOptions*)malloc(sizeof(struct CharOptions));
	char tmp_c;

	// numbers
	if(c > 47 & c < 58){
		chars->size = 11;
		chars->options = (char *)malloc(chars->size);
		for(int i=0; i < chars->size-1; i=i+1){
			(chars->options)[i] = i+48;
		}
		(chars->options)[10] = '\0';
	}
	else if(c > 96 & c < 123){
		tmp_c = c - 32;
		chars->size = 3;
		chars->options = (char *)malloc(chars->size);
		(chars->options)[0] = c; (chars->options)[1] = tmp_c; (chars->options)[2] = '\0';
	}
	else if(c > 64 & c < 91){
		tmp_c = c + 32;
		chars->size = 3;
		chars->options = (char *)malloc(chars->size);
		(chars->options)[0] = tmp_c; (chars->options)[1] = c; (chars->options)[2] = '\0';
	}

	return chars;
}

/*
	Initialize the list with a char and all of its options
*/
void init_char_list(char c, struct LinkedList* linked_List){

	struct CharOptions *chars = get_char_options(c);
	for(int i=0; i < chars->size-1; i=i+1){
		char str[2] = {(chars->options)[i], '\0'};
		append(linked_List, str, 2);
	}
}

/*
	Create a list with all the stable permutation of a string.
	Use for longer string.
	Return - linked list with all the stable permutation
*/
struct LinkedList* permutation(char *str, int size){
	// options of the start char
	struct LinkedList* linked_list = create_empty_linked_list();

	init_char_list(*str, linked_list);
	str = str + 1;
	
	for(int i=1; i < size - 1; i=i+1){
		struct CharOptions* chars = get_char_options(*(str+i-1));
		struct LinkedList* tmpList = create_empty_linked_list();
		for(int j=0; j < chars->size - 1; j=j+1){
			struct Link* current = linked_list->head;
			while(current != NULL){
				 // the current lenght of the linkList ithems and the added one
				// and the null byte
				char str[i+2];
				strncpy(str, current->c, i);
				char op[2] = {(chars->options)[j], '\0'};
				strncpy(str + i, op, 2);
				append(tmpList, str, i+2);
				current = current->next_link;
			}
		}
		delete_list(linked_list);
		linked_list = tmpList;
	}

	return linked_list;

}

/*
	The wrapper function that call to perm_rec a recursion
	function, that prints all the permutations.
	Use for shorter strings.
*/
void permutation_recursion(char* str, int size){
	char build_str[size];
	build_str[size-1] = '\0';
	perm_rec(str, build_str, size-1, size-1);
}

void perm_rec(char* str, char* build_str, int at, int size){
	if(at == 0)
	{
		printf("%s\n", build_str);
	}
	else {
		char c = *str;
		struct CharOptions* chars = get_char_options(c);
		str = str + 1;
		at = at - 1;
		for(int i=0; i< chars->size-1; i=i+1){
			build_str[size-at-1] = (chars->options)[i];
			perm_rec(str, build_str, at, size);
		}
	}

}

void stable_main(int argc, char *argv[]){
	//struct LinkedList* list;
	char str[10] = {'a', 'b', '5',
			'a', 'b', '5',
			'a', 'b', '5', '\0'};
	//list = permutation(str, 10);
	//print_list(list);
	permutation_recursion(str, 10);
	
}
