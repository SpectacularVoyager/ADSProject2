#include"LSMTree.h"
#include "avl.h"
#include "record.h"
#include <stdio.h>
#include<dirent.h>
#include <string.h>

FILE* getFile(){
	struct dirent *de;
	DIR *dr=opendir("res/tables");
	if(dr==NULL){
		printf("COULD NOT OPEN DIR res/tables\n");
		return NULL;
	}
	int count=0;
	while((de=readdir(dr))!=NULL){
		count++;
	}
	char file[200];
	sprintf(file,"res/tables/table%d",count);
	return fopen(file, "w");
}
void WriteNode(FILE* f,Node* node){
	if(node==NULL){return;}
	WriteNode(f, node->left);
	fwrite(&node->key, sizeof(record),1,f);
	WriteNode(f, node->right);
}
void freeNodes(Node* n){
	if(n==NULL)return;
	freeNodes(n->left);
	freeNodes(n->right);
	free(n);
}

void LSMFlush(LSMTree* lsm){
	printf("FLUSHING\n");
	FILE* f =getFile();
	WriteNode(f,lsm->root);
	freeNodes(lsm->root);
	fclose(f);
	lsm->i=0;
	lsm->root=NULL;
}
SSTableStream* LSMReadTable(char* file){
	FILE * f=fopen(file,"r");
	return stream(f);
}
SSTableStream** LSMGetStreams(){
	struct dirent *de;
	DIR *dr=opendir("res/tables");
	if(dr==NULL){
		printf("COULD NOT OPEN DIR res/tables\n");
		return NULL;
	}
	int count=0;
	while((de=readdir(dr))!=NULL){
		if(de->d_type!=DT_REG){continue;}
		count++;
	}

	SSTableStream **streams=malloc(sizeof(SSTableStream)*(count+1));

	dr=opendir("res/tables");
	int i=0;
	while((de=readdir(dr))!=NULL){
		if(de->d_type!=DT_REG){continue;}
		char fp[200]="res/tables/";
		strcat(fp,de->d_name);
		printf("FILE:\t%s\n",fp);
		FILE* f=fopen(fp,"r");
		streams[i++]=stream(f);
	}
	streams[i]=NULL;
	return streams;
}

void LSMInsert(LSMTree* lsm,record n){
	if(lsm->i>=MAX_AVL_SIZE){
		LSMFlush(lsm);
	}
	lsm->root=insert(lsm->root, n);
	lsm->i++;
}
LSMTree* LSM(){
	return (LSMTree*)malloc(sizeof(LSMTree));
}
