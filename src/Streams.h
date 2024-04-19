#include <stdlib.h>
#include<stdio.h>
#include"record.h"

typedef struct SSTableStream{
	FILE* f;
	record* r;
} SSTableStream;




typedef struct MergeStream{
	struct CachedStream* stream;
	int n;
} MergeStream;

int SSTableStreamNext(SSTableStream* s,record* r);

SSTableStream* stream(FILE* f);


int SSTableStreamNext(SSTableStream* s,record* r);

typedef struct CachedStream{
	SSTableStream* stream;
	record cached;
	int done;
} CachedStream;

CachedStream cache(SSTableStream* s);
int CachedStreamNext(CachedStream* s,record* r);
int CachedStreamPeek(CachedStream* s,record* r);

int MergeStreamNext(MergeStream* s,record* r);
