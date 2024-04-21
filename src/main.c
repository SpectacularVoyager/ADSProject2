#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"LSMTree.h"
#include "record.h"
#include "utils.h"


#define forin(n) for(int i=0;i<n;i++)
#define s(x) randStr(x,sizeof(x)/sizeof(char*))
#define printInt(x) printf("%d\n",x)
#define KILLSTART int ___killswitch___ =15
#define KILLSWITCH if(___killswitch___--==0)break;

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
typedef int (*checkFun)(record*);

void consume(Node* root,record* r,int* count){
	if(!root)return;
	consume(root->left,r,count);

	r[*count]=root->key;

	*count=(*count)+1;

	consume(root->right,r,count);
}



void doScanCond(LSMTree* lsm){
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
	record records[5];
	int _c=0;
	consume(lsm->root,records,&_c);
	int avlc=0;
	record* temp=&r;
	int status=MergeStreamNext(&stream,temp);
	while(status && avlc<_c){
		if(RecordCompare(temp,&records[avlc])<0){
			printf("SSTABLE:\t");
			RecordPrint(temp);
			status=MergeStreamNext(&stream,temp);
		}else{
			printf("AVL:\t\t");
			RecordPrint(&records[avlc]);
			avlc++;
		}
	}
	while(status&&MergeStreamNext(&stream,&r)){
		printf("SSTABLE:\t");
		RecordPrint(&r);
	}
	while(avlc<_c){
		printf("AVL:\t\t");
		RecordPrint(&records[avlc++]);
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
	srand(time(NULL));

	LSMTree* lsm=LSM();

	forin(5){
		record* r=getRandom(i);
		LSMInsert(lsm,*r);
		free(r);
	}

	//record r[5];
	//int _c=0;
	//consume(lsm->root,r,&_c);

	//forin(5){
	//	RecordPrint(&r[i]);
	//}

	doScanCond(lsm);
	free(lsm);

}
