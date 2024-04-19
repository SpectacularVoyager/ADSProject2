#pragma once
#include"avl.h"
#include"Streams.h"
#include"utils.h"

#define MAX_AVL_SIZE 10
#define SPARSE 100


typedef struct LSMTree{
	Node* root;
	int i;
} LSMTree;
void LSMInsert(LSMTree* lsm,record n);

LSMTree* LSM();

SSTableStream* LSMReadTable(char* file);

SSTableStream** LSMGetStreams();
