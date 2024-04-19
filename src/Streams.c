#include"Streams.h"

int next(SSTableStream* s,record r){
	if(fread(&r,sizeof(record),1,s->f)>0){
		return 1;
	}
	return 0;
}
