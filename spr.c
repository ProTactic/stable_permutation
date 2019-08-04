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

// return the lower or upper char
// for example for 'a' return 'A'
struct CharOptions *getLUChar(char c){

	struct CharOptions *chars = (struct CharOptions*)malloc(sizeof(struct CharOptions));
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

void init_char_list(char c, struct LinkList* linkList){

	struct CharOptions *chars = getLUChar(c);
	for(int i=0; i < chars->size-1; i=i+1){
		char str[2] = {(chars->options)[i], '\0'};
		append(linkList, str, 2);
	}
}

struct LinkList *permutation(char *str, int size){
	// options of the start char
	struct LinkList *linkList = createEmptyLinkList();

	init_char_list(*str, linkList);
	str = str + 1;
	
	for(int i=1; i < size - 1; i=i+1){
		struct CharOptions *chars = getLUChar(*(str+i-1));
		struct LinkList *tmpList = createEmptyLinkList();
		for(int j=0; j < chars->size - 1; j=j+1){
			struct Link* current = linkList->head;
			while(current != NULL){
				 // the current lenght of the linkList ithems and the added one
				// and the null byte
				char str[i+2];
				strncpy(str, current->c, i);
				char op[2] = {(chars->options)[j], '\0'};
				strncpy(str + i, op, 2);
				append(tmpList, str, i+2);
				current = current->nextLink;
			}
		}
		deleteList(linkList);
		linkList = tmpList;
	}

	return linkList;

}

void stable_main(int argc, char *argv[]){
	struct LinkList* list;
	char str[4] = {'a', 'b', '5', '\0'};
	list = permutation(str, 4);
	printList(list);
	
}
