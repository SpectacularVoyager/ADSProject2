#pragma once
#include"avl.h"

#define MAX_AVL_SIZE 100
#define SPARSE 100


typedef struct LSMTree{
	Node* root;
	int i;
} LSMTree;
void LSMInsert(LSMTree* lsm,record n);

LSMTree* LSM();
