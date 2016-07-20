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
	printf("Running the sorted-list implementation with ints (alloc).\n");
	printf("Creating sorted-list.\n");
	SortedListPtr sl;
	SortedListIteratorPtr iter;
	SortedListIteratorPtr iter2;
	sl = SLCreate(compareInts, destroyBasicTypeAlloc);
	printf("Inserting the items 2, 4, 1, 3, 2, and 5,\nin that order (notice attempted duplicate insertion)\n");
	int *a;
	a = (int *)malloc(sizeof(int));
	*a = 2;
	SLInsert(sl, a);
	int *b;
	b = (int *)malloc(sizeof(int));
	*b = 4;
	SLInsert(sl, b);
	int *c;
	c = (int *)malloc(sizeof(int));
	*c = 1;
	SLInsert(sl, c);
	int *d;
	d = (int *)malloc(sizeof(int));
	*d = 3;
	SLInsert(sl, d);
	int *e;
	e = (int *)malloc(sizeof(int));
	*e = 2;
	SLInsert(sl, e);
	int *f;
	f = (int *)malloc(sizeof(int));
	*f = 5;
	SLInsert(sl, f);
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("%d ", *(int *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Creating iterator, moving it to 3, then removing items 3 and 2.\n");
	iter = SLCreateIterator(sl);
	SLNextItem(iter);
	SLNextItem(iter);
	int *z;
	z = (int *)malloc(sizeof(int));
	*z = 3;
	SLRemove(sl, z);
	int *y;
	y = (int *)malloc(sizeof(int));
	*y = 2;
	SLRemove(sl, y);
	printf("Creating second iterator and having it run through the list's items.\n");
	iter2 = SLCreateIterator(sl);
	while (iter2->current != NULL) {
		printf("%d ", *(int *)iter2->current->content);
		iter2->current = iter2->current->next;
	}
	printf("\n");
	printf("Destroying second iterator.\n");
	SLDestroyIterator(iter2);
	printf("Asking first iterator for the current item, followed by asking it for the next item.\n");
	printf("Current: %d\n", *(int *)SLGetItem(iter));
	printf("Next: %d\n", *(int *)SLNextItem(iter));
	printf("Destroying first iterator.\n");
	SLDestroyIterator(iter);
	printf("Inserting -10 to show what happens when inserted element is smaller than the entire list.\n");
	int *g;
	g = (int *)malloc(sizeof(int));
	*g = -10;
	SLInsert(sl, g);
	printf("Inserting 10 to show what happens when inserted element is bigger than the entire list.\n");
	int *h;
	h = (int *)malloc(sizeof(int));
	*h = 10;
	SLInsert(sl, h);
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("%d ", *(int *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Attempting to remove an element that doesn't exist (15).\n");
	int *x;
	x = (int *)malloc(sizeof(int));
	*x = 15;
	if (SLRemove(sl, x) == 0) {
		printf("Remove failed. Element not found!\n");
	}
	else {
		printf("Remove succeeded!\n");
	}
	printf("Attempting to insert a duplicate element (10).\n");
	int *w;
	w = (int *)malloc(sizeof(int));
	*w = 10;
	if (SLInsert(sl, w) == 0) {
		printf("Insert failed. Element already in list!\n");
	}
	else {
		printf("Insert succeeded!\n");
	}
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("%d ", *(int *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Removing all items then creating an iterator.\n");
	SLRemove(sl, g);
	SLRemove(sl, h);
	SLRemove(sl, b);
	SLRemove(sl, c);
	SLRemove(sl, f);
	printf("Running through list with iterator, then destroying iterator.\n");
	iter = SLCreateIterator(sl);
	if (iter == NULL) {
		printf("Empty list. Cannot create iterator.\n");
	}
	else {
		while (iter->current != NULL) {
			printf("%d ", *(int *)iter->current->content);
			iter->current = iter->current->next;
		}
	}
	SLDestroyIterator(iter);
	printf("Destroying list.\n");
	SLDestroy(sl);
	return 0;
}
