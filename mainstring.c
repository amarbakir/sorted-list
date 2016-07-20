/*
 * sorted-list.c
 */

#include	<string.h>
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}


int main()
{
	printf("\n------------------------------------------------------------\n");
	printf("Running the sorted-list implementation with strings (no alloc).\n");
	printf("Creating sorted-list.\n");
	SortedListPtr sl;
	SortedListIteratorPtr iter;
	SortedListIteratorPtr iter2;
	sl = SLCreate(compareStrings, destroyBasicTypeNoAlloc);
	printf("Inserting the items 'give', 'johnny', 'any', 'six', 'words', and 'johnny',\nin that order (notice attempted duplicate insertion)\n");
	char a[] = "give";
	SLInsert(sl, a);
	char b[] = "johnny";
	SLInsert(sl, b);
	char c[] = "any";
	SLInsert(sl, c);
	char d[] = "six";
	SLInsert(sl, d);
	char e[] = "words";
	SLInsert(sl, e);
	char f[] = "johnny";
	SLInsert(sl, f);
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("\"%s\" ", (char *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Creating iterator, moving it to 'johnny', then removing items 'johnny' and 'any'.\n");
	iter = SLCreateIterator(sl);
	SLNextItem(iter);
	char z[] = "johnny";
	SLRemove(sl, z);
	char y[] = "any";
	SLRemove(sl, y);
	printf("Creating second iterator and having it run through the list's items.\n");
	iter2 = SLCreateIterator(sl);
	while (iter2->current != NULL) {
		printf("\"%s\" ", (char *)iter2->current->content);
		iter2->current = iter2->current->next;
	}
	printf("\n");
	printf("Destroying second iterator.\n");
	SLDestroyIterator(iter2);
	printf("Asking first iterator for the current item, followed by asking it for the next item.\n");
	printf("Current: \"%s\"\n", (char *)SLGetItem(iter));
	printf("Next: \"%s\"\n", (char *)SLNextItem(iter));
	printf("Destroying first iterator.\n");
	SLDestroyIterator(iter);
	printf("Inserting 'aaa' to show what happens when inserted element is smaller than the entire list.\n");
	char g[] = "aaa";
	SLInsert(sl, g);
	printf("Inserting 'zzz' to show what happens when inserted element is bigger than the entire list.\n");
	char h[] = "zzz";
	SLInsert(sl, h);
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("\"%s\" ", (char *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Attempting to remove an element that doesn't exist ('mark').\n");
	char x[] = "mark";
	if (SLRemove(sl, x) == 0) {
		printf("Remove failed. Element not found!\n");
	}
	else {
		printf("Remove succeeded!\n");
	}
	printf("Attempting to insert a duplicate element ('aaa').\n");
	char w[] = "aaa";
	if (SLInsert(sl, w) == 0) {
		printf("Insert failed. Element already in list!\n");
	}
	else {
		printf("Insert succeeded!\n");
	}
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("\"%s\" ", (char *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Removing all items then creating an iterator.\n");
	SLRemove(sl, g);
	SLRemove(sl, h);
	SLRemove(sl, a);
	SLRemove(sl, d);
	SLRemove(sl, e);
	printf("Running through list with iterator, then destroying iterator.\n");
	iter = SLCreateIterator(sl);
	if (iter == NULL) {
		printf("Empty list. Cannot create iterator.\n");
	}
	else {
		while (iter->current != NULL) {
			printf("\"%s\" ", (char *)iter->current->content);
			iter->current = iter->current->next;
		}
	}
	SLDestroyIterator(iter);
	printf("Destroying list.\n");
	SLDestroy(sl);
	return 0;
}
