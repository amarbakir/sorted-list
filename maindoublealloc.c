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
	printf("Running the sorted-list implementation with doubles (alloc).\n");
	printf("Creating sorted-list.\n");
	SortedListPtr sl;
	SortedListIteratorPtr iter;
	SortedListIteratorPtr iter2;
	sl = SLCreate(compareDoubles, destroyBasicTypeAlloc);
	printf("Inserting the items 2.5, 4.3, 1.6, 3.7, 2.4, and 4.3,\nin that order (notice attempted duplicate insertion)\n");
	double *a;
	a = (double *)malloc(sizeof(double));
	*a = 2.5;
	SLInsert(sl, a);
	double *b;
	b = (double *)malloc(sizeof(double));
	*b = 4.3;
	SLInsert(sl, b);
	double *c;
	c = (double *)malloc(sizeof(double));
	*c = 1.6;
	SLInsert(sl, c);
	double *d;
	d = (double *)malloc(sizeof(double));
	*d = 3.7;
	SLInsert(sl, d);
	double *e;
	e = (double *)malloc(sizeof(double));
	*e = 2.4;
	SLInsert(sl, e);
	double *f;
	f = (double *)malloc(sizeof(double));
	*f = 4.3;
	SLInsert(sl, f);
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("%lf ", *(double *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Creating iterator, moving it to 3.7, then removing items 3.7 and 2.5.\n");
	iter = SLCreateIterator(sl);
	SLNextItem(iter);
	double *z;
	z = (double *)malloc(sizeof(double));
	*z = 3.7;
	SLRemove(sl, z);
	double *y;
	y = (double *)malloc(sizeof(double));
	*y = 2.5;
	SLRemove(sl, y);
	printf("Creating second iterator and having it run through the list's items.\n");
	iter2 = SLCreateIterator(sl);
	while (iter2->current != NULL) {
		printf("%lf ", *(double *)iter2->current->content);
		iter2->current = iter2->current->next;
	}
	printf("\n");
	printf("Destroying second iterator.\n");
	SLDestroyIterator(iter2);
	printf("Asking first iterator for the current item, followed by asking it for the next item.\n");
	printf("Current: %lf\n", *(double *)SLGetItem(iter));
	printf("Next: %lf\n", *(double *)SLNextItem(iter));
	printf("Destroying first iterator.\n");
	SLDestroyIterator(iter);
	printf("Inserting -10.1 to show what happens when inserted element is smaller than the entire list.\n");
	double *g;
	g = (double *)malloc(sizeof(double));
	*g = -10.1;
	SLInsert(sl, g);
	printf("Inserting 10.1 to show what happens when inserted element is bigger than the entire list.\n");
	double *h;
	h = (double *)malloc(sizeof(double));
	*h = 10.1;
	SLInsert(sl, h);
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("%lf ", *(double *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Attempting to remove an element that doesn't exist (15.5).\n");
	double *x;
	x = (double *)malloc(sizeof(double));
	*x = 15.5;
	if (SLRemove(sl, x) == 0) {
		printf("Remove failed. Element not found!\n");
	}
	else {
		printf("Remove succeeded!\n");
	}
	printf("Attempting to insert a duplicate element (1.6).\n");
	double *w;
	w = (double *)malloc(sizeof(double));
	*w = 1.6;
	if (SLInsert(sl, w) == 0) {
		printf("Insert failed. Element already in list!\n");
	}
	else {
		printf("Insert succeeded!\n");
	}
	printf("Creating iterator and running through the list,\noutputting elements to the console.\n");
	iter = SLCreateIterator(sl);
	while (iter->current != NULL) {
		printf("%lf ", *(double *)iter->current->content);
		iter->current = iter->current->next;
	}
	printf("\n");
	printf("Destroying iterator.\n");
	SLDestroyIterator(iter);
	printf("Removing all items then creating an iterator.\n");
	SLRemove(sl, g);
	SLRemove(sl, h);
	SLRemove(sl, c);
	SLRemove(sl, e);
	SLRemove(sl, f);
	printf("Running through list with iterator, then destroying iterator.\n");
	iter = SLCreateIterator(sl);
	if (iter == NULL) {
		printf("Empty list. Cannot create iterator.\n");
	}
	else {
		while (iter->current != NULL) {
			printf("%lf ", *(double *)iter->current->content);
			iter->current = iter->current->next;
		}
	}
	SLDestroyIterator(iter);
	printf("Destroying list.\n");
	SLDestroy(sl);
	return 0;
}
