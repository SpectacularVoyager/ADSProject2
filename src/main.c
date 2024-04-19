#include <stdio.h>
#include <string.h>
#include"LSMTree.h"
#include "record.h"
#include "utils.h"


#define forin(n) for(int i=0;i<n;i++)
#define s(x) randStr(x,sizeof(x)/sizeof(char*))
#define printInt(x) printf("%d\n",x)

char* groups[]={"group1","group2","group3","group4","group5","group6"};
char* users[]={"user1","user2","user3","user4","user5","user6"};
char* msgs[]={"msg1","msg2","msg3","msg4","msg5","msg6"};

char* randStr(char** arr,int n){
	return arr[rand()%n];
}

record* getRandom(int time){
	return Record(time,s(groups),s(users),s(msgs),time);
}
int check(record* r){
	return strcmp("group1",r->group)==0;
}
void doScanCond(){
	record r;
	int k=0;
	SSTableStream** streams= LSMGetStreams();	
	int count=0;
	for(int i=0;streams[i]!=NULL;i++){
		count++;
	}
	CachedStream cached[count];
	for(int i=0;i<count;i++){
		cached[i]=cache(streams[i]);
	}
	printInt(count);
	MergeStream stream={.stream=cached,.n=count};
	PredicatedStream pred={.stream=stream,.fun=check};
	while(PredicatedStreamNext(&pred,&r)){
		RecordPrint(&r);
	}
}
void doScan(){
	record r;
	int k=0;
	SSTableStream** streams= LSMGetStreams();	
	int count=0;
	for(int i=0;streams[i]!=NULL;i++){
		count++;
	}
	CachedStream cached[count];
	for(int i=0;i<count;i++){
		cached[i]=cache(streams[i]);
	}
	printInt(count);
	MergeStream stream={.stream=cached,.n=count};
	while(MergeStreamNext(&stream,&r)){
		RecordPrint(&r);
	}
}

int main(){

	LSMTree* lsm=LSM();

	forin(11){
		record* r=getRandom(i);
		LSMInsert(lsm,*r);
		free(r);
	}
	doScan();
	free(lsm);

}
