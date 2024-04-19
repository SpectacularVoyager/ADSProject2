#include"Streams.h"
#include "record.h"

int SSTableStreamNext(SSTableStream* s,record* r){
	if(fread(r,sizeof(record),1,s->f)>0){
		return 1;
	}
	r=NULL;
	return 0;
}
SSTableStream* stream(FILE* f){
	SSTableStream* ss=(SSTableStream*)malloc(sizeof(SSTableStream));
	ss->f=f;
	return ss;
}

CachedStream cache(SSTableStream* s){
	//CachedStream* stream=(CachedStream*)malloc(sizeof(CachedStream));
	CachedStream stream;
	stream.stream=s;
	stream.done=0;
	SSTableStreamNext(s,&stream.cached);
	return stream;
}

int CachedStreamPeek(CachedStream* s,record* r){
	*r=s->cached;
	return r>0;
}
int CachedStreamNext(CachedStream* s,record* r){
	if(s->done)return 0;
	record temp=s->cached;
	if(SSTableStreamNext(s->stream,&s->cached)<=0){
		s->done=1;
	}
	*r=temp;
	return r>0;
}
int CachedStreamPoll(CachedStream* s){
	return SSTableStreamNext(s->stream,&s->cached);
}

int MergeStreamNext(MergeStream* s,record* r){
	if(s->n<=0){
		r=NULL;
		return 0;
	}
	int ptr=0;
	CachedStreamPeek(&s->stream[0],r);
	for(int i=1;i<s->n;i++){
		record t;
		CachedStreamPeek(&s->stream[i],&t);
		if(RecordCompare(r,&t)>0){
			ptr=i;
			*r=t;
		}
	}
	return CachedStreamPoll(&s->stream[ptr]);
}
