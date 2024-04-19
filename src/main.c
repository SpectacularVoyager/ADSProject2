#include <stdio.h>
#include"LSMTree.h"
#include "record.h"


#define forin(n) for(int i=0;i<n;i++)
#define s(x) randStr(x,sizeof(x)/sizeof(char*))


char* groups[]={"group1","group2","group3","group4","group5","group6"};
char* users[]={"user1","user2","user3","user4","user5","user6"};
char* msgs[]={"msg1","msg2","msg3","msg4","msg5","msg6"};

char* randStr(char** arr,int n){
	return arr[rand()%n];
}

record* getRandom(int time){
	return Record(time,s(groups),s(users),s(msgs),time);
}

int main(){

	LSMTree* lsm=LSM();

	forin(1001){
		record* r=getRandom(i);
		LSMInsert(lsm,*r);
		free(r);
	}
	preOrder(lsm->root);
	LSMReadTable("res/tables/table2");
	free(lsm);

}
