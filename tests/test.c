test_link_list(){

	char c = 'a';
	struct LinkList *linkList = createLinkList(c);
	c = 'b';
	append(linkList, c);
	printList(linkList);
	deleteList(linkList);
	if(linkList == NULL){
		printf("deleted the list");
	}
	return 0;
}
