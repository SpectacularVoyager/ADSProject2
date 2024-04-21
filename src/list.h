#pragma once

#include <stdlib.h>

#define DEFAULT_SIZE 100
#define DEFAULT_RULE 2

typedef struct List{
	void * data;
	unsigned int stride;
	unsigned int n;
	unsigned int capacity;
} List;

void List_init(List* l,unsigned int stride);
void List_add(List* l,const void* data);
const void* List_get(List* l,unsigned int n);
void List_resize(List* l,unsigned int capacity);
List list(unsigned int stride);


#define forlist(x) for(int i=0;i<x.n;i++)
