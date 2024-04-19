#include"Streams.h"

int SSTableStreamNext(SSTableStream* s,record* r){
	if(fread(r,sizeof(record),1,s->f)>0){
		return 1;
	}
	return 0;
}
SSTableStream* stream(FILE* f){
	SSTableStream* ss=(SSTableStream*)malloc(sizeof(SSTableStream));
	ss->f=f;
	return ss;
}
