#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#include "spr.h"
#include "utils/LinkList.h"
#include "utils/Link.h"

static int flag_excludeDigits = 0;
static int flag_excludeChars = 0;
static int fd = 1;

void print_usage(){
	printf("%s",
		"This is the stable permutaion software\n"
		"usage: spr [Options] ... words\n\n"
		"Mandatory arguments to long options are mandatory for short options too.\n"
		"	-e  --exclude <option to exclude> :\n"
		"		option to exclude: D for digits\n"
		"				   C for english characters\n"
		"	--write-to-file : saves the data to a file, for example:\n"
		"		for spr --write-to-file aa , create a file named permutation_aa.txt\n\n");
}

void progress_data(char *str, unsigned long in, unsigned long total){
	char* bar = create_bar(in, total);
	printf("\r%s %s %lu/%lu", str, bar, in, total);
	fflush(stdout);
	free(bar);
}

char* create_bar(unsigned long in, unsigned long total){
	double dev = (long double)in/(long double)total;
	char* bar = (char*)malloc(23);
	bar[0] = '[';
	int at = 1;
	while(0.0499 < dev){
		bar[at] = '#';
		dev = dev - 0.05;
		at = at + 1;
	}
	while(at < 21){
		bar[at] = '.';
		at = at + 1;
	}
	bar[21] = ']';
	bar[22] = '\0';

	return bar;
}

void use_file(FILE *fp)
{
  fd = fileno(fp);
}

/*
	Return the number of stable permutation the string have.
*/
unsigned long number_of_options(char* str, int size){
	unsigned long op = 1;
	while(size > 0){
		op = op * get_char_number_of_options(*str);
		size = size - 1;
		str = str + 1;
	}

	return op;
}

/*
	Return the number of option of a char.
*/
int get_char_number_of_options(char c){
	int op = 1;

	if(!flag_excludeDigits && (c > 47) & (c < 58)){
		op = 10;
	} else if(!flag_excludeChars && (((c > 96) & (c < 123)) || ((c > 64) & (c < 91)))){
		op = 2;
	}

	return op;
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
	if((c > 47) & (c < 58)){
		if(!flag_excludeDigits){ 
			chars->size = 11;
			chars->options = (char *)malloc(chars->size);
			for(int i=0; i < chars->size-1; i=i+1){
				(chars->options)[i] = i+48;
			}
			(chars->options)[10] = '\0';
		} else {
			chars->size = 2;
			chars->options = (char *)malloc(chars->size);
			(chars->options)[0] = c; (chars->options)[1] = '\0';
		}
	} else if(!flag_excludeChars){
		if((c > 96) & (c < 123)){
			tmp_c = c - 32;
			chars->size = 3;
			chars->options = (char *)malloc(chars->size);
			(chars->options)[0] = c; (chars->options)[1] = tmp_c; (chars->options)[2] = '\0';
		}
		else if((c > 64) & (c < 91)){
			tmp_c = c + 32;
			chars->size = 3;
			chars->options = (char *)malloc(chars->size);
			(chars->options)[0] = tmp_c; (chars->options)[1] = c; (chars->options)[2] = '\0';
		}
	} 
	else {
		chars->size = 2;
		chars->options = (char *)malloc(chars->size);
		(chars->options)[0] = c; (chars->options)[1] = '\0';
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
struct LinkedList* permutation(char *str, int size, unsigned long total){
	// options of the start char
	struct LinkedList* linked_list = create_empty_linked_list();
	unsigned long num_words = 0;
	unsigned long pace = 0.05 * total;

	init_char_list(*str, linked_list);
	str = str + 1;
	
	for(int i=1; i < size - 1; i=i+1){
		struct CharOptions* chars = get_char_options(*(str+i-1));
		struct LinkedList* tmpList = create_empty_linked_list();
		for(int j=0; j < chars->size - 1; j=j+1){
			struct Link* current = linked_list->head;
			while(current != NULL){
				 // the current lenght of the linkList items and the added one
				// and the null byte
				char str[i+2];
				strncpy(str, current->c, i);
				char op[2] = {(chars->options)[j], '\0'};
				strncpy(str + i, op, 2);
				append(tmpList, str, i+2);
				current = current->next_link;
			
				if(i == size-2){
					num_words = num_words + 1;
					if(num_words == pace){
						progress_data("Creating list:", num_words, total);
						pace = pace + 0.05 * total;
					}				
				}
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
void permutation_recursion(char* str, int size, unsigned long total_words){
	char build_str[size];
	build_str[size-1] = '\0';
	unsigned long num_words = 0;

	if(fd == 1){
		perm_rec(str, build_str, size-1, size-1, total_words, &num_words);
	} else {
		unsigned long pace = 0.05 * total_words;
		perm_rec_to_file(str, build_str, size-1, size-1, total_words, &num_words, &pace);
	}
}

void perm_rec(char* str, char* build_str, int at, int size, 
	unsigned long total_words, unsigned long* num_words){
	if(at == 0)
	{
		write(fd, build_str, size);
		write(fd, "\n", 1);
	}
	else {
		char c = *str;
		struct CharOptions* chars = get_char_options(c);
		str = str + 1;
		at = at - 1;
		for(int i=0; i< chars->size-1; i=i+1){
			build_str[size-at-1] = (chars->options)[i];
			perm_rec(str, build_str, at, size, 
					total_words, num_words);
		}
	}

}

void perm_rec_to_file(char* str, char* build_str, int at, int size, 
	unsigned long total_words, unsigned long* num_words, unsigned long* pace){
	if(at == 0)
	{
		write(fd, build_str, size);
		write(fd, "\n", 1);
		*num_words = *num_words + 1;
		if(*num_words == *pace){
			progress_data("Total words: ", *num_words, total_words);
			*pace = *pace + ( 0.05 * total_words);
		}
	}
	else {
		char c = *str;
		struct CharOptions* chars = get_char_options(c);
		str = str + 1;
		at = at - 1;
		for(int i=0; i< chars->size-1; i=i+1){
			build_str[size-at-1] = (chars->options)[i];
			perm_rec_to_file(str, build_str, at, size, 
					total_words, num_words, pace);
		}
	}

}

static int flag_save = 0;

void stable_main(int argc, char *argv[]){

	int c;
	int option_index = 0;
	char* p;

	static struct option long_options[] =
        {
		{"write-to-file", no_argument,  &flag_save, 1},
		{"exclude", required_argument,  0, 'e'},
          	{0, 0, 0, 0}
        };

  	while ((c = getopt_long (argc, argv, "e:", long_options, &option_index)))
    	{
      		if (c == -1)
        		break;

      		switch (c)
        	{
			case 'e':
			{
				p = optarg;
				while(*p){
					switch(*p){
						case 'D':
							flag_excludeDigits = 1;	
							break;
						case 'C':
							flag_excludeChars = 1;
							break;
						default:
							print_usage();
          						exit(-1);
					}
					p = p + 1;
				}
			}
			case '?':
          			break;
        		default:
				print_usage();
          			exit(-1);
        	}
	};

  	if (optind < argc)
    	{
      		while (optind < argc){
			char* str = argv[optind++];
		        int size = strlen(str) + 1;
			FILE *fp;
			if(flag_save){
  				char str2[strlen(str)+size];
				sprintf(str2, "permutation_%s.txt", str);
			  	fp = fopen(str2, "a");
  				use_file(fp);
				if(fd != 1) {
					printf("Writing to the file: %s\n", str2);
				}
			}
			// the size with the null byte
			unsigned long op = number_of_options(str, size-1);
			printf("Starting p of %s with %lu options\n", str, op);
			if(op < 1000000){
				permutation_recursion(str, size, op);
			}
			else{
				struct LinkedList* linked_list = permutation(str, size, op);
				print_list(linked_list, fd);
				delete_list(linked_list);
			}
			if(fd != 1) {
				fclose(fp);
				printf("\n");
			}
		}
		
    	}
	
}
