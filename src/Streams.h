#include <stdlib.h>
#include<stdio.h>
#include"record.h"

typedef struct SSTableStream{
	FILE* f;
} SSTableStream;

int SSTableStreamNext(SSTableStream* s,record* r);

SSTableStream* stream(FILE* f);
