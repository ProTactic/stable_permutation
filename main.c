#include <stdio.h>
#include "spr.h"

#include "utils/LinkList.h"
#include <stddef.h>
    
int main(int argc, char *argv[])
{
	if(argc < 2){
		print_usage();
	}
	else {
		stable_main(argc, argv);
	}
}
