#include "record.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int RecordCompare(record* r1,record* r2){
	if(r1==NULL)return 1;
	if(r2==NULL)return -1;
	int cg=strncmp(r1->group,r2->group,20);
	if(cg!=0){
		return cg;
	}
	return r1->timestamp-r2->timestamp;
}
void RecordPrint(record* r){
	printf("[%d,\"%s\",\"%s\",\"%s\",%ld]\n",r->id,r->group,r->user,r->msg,r->timestamp);
}

record* Record(
	int id,
	char group[GROUP_CHAR_ARR_LEN],
	char user[ USER_CHAR_ARR_LEN ],
	char msg[  MSG_CHAR_ARR_LEN  ],
	long timestamp
	){
	record* r=malloc(sizeof(record));
	initialize(r,id,group,user,msg,timestamp);
	return r;
}
void initialize(record* r,int id,char group[GROUP_CHAR_ARR_LEN],char user[USER_CHAR_ARR_LEN],char msg[MSG_CHAR_ARR_LEN],long timestamp){
	r->id=id;
	r->timestamp=timestamp;
	strncpy(r->group,group,20);
	strncpy(r->user,user,20);
	strncpy(r->msg,msg,100);
}
