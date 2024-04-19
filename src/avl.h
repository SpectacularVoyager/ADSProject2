#pragma once

#include<stdio.h> 
#include<stdlib.h> 
#include"record.h"
  

typedef struct Node 
{ 
    record key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
} Node; 
  

int height(struct Node *N); 

int max(int a, int b) ;
struct Node* newNode(record key);
  


struct Node *rightRotate(struct Node *y);


struct Node *leftRotate(struct Node *x);

int getBalance(struct Node *N);

struct Node* insert(struct Node* node, record key);


void preOrder(struct Node *root) ;
