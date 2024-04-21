#include "list.h"
#include <stdarg.h>
#include <string.h>

void List_init(List* l,unsigned int stride){
	l->stride=stride;
	l->n=0;
	List_resize(l,DEFAULT_SIZE);
}
List list(unsigned int stride){
	List l;
	List_init(&l,stride);
	return l;
}
//TODO:Handle free
void List_resize(List* l,unsigned int capacity){
	l->capacity=capacity;
	l->data=malloc(l->stride*l->capacity);
}
//TODO:TEST
void List_add(List* l,const void* data){
	if(l->n>l->capacity){
		l->capacity*=DEFAULT_RULE;
		const void* original=l->data;
		List_resize(l,l->capacity);
		memcpy(l->data,original,l->n*l->stride);
	}

	void* ptr=l->data;
	ptr+=(l->stride*l->n);
	memcpy(ptr,data,l->stride);
	l->n++;
}
const void* List_get(List* l,unsigned int n){
	return l->data+(n*l->stride);
}

const List* List_heap(unsigned int n){
	return malloc(sizeof(List));
}
void List_free(){
}
//#define vec!(args...) 

