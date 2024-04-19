#include<stdio.h>
#include"record.h"

typedef struct SSTableStream{
	FILE* f;
} SSTableStream;

int next(SSTableStream* s,record r);
