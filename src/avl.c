#include<stdio.h> 
#include<stdlib.h> 
#include"record.h"
#include"avl.h"
  
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  

int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct Node* newNode(record key) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  
    return(node); 
} 
  


struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    
    x->right = y; 
    y->left = T2; 
  
    
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 
    x->height = max(height(x->left), 
                    height(x->right)) + 1; 
  
    
    return x; 
} 
  


struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    
    y->left = x; 
    x->right = T2; 
  
    
    x->height = max(height(x->left),    
                    height(x->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 
  
    
    return y; 
} 
  

int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  


struct Node* insert(struct Node* node, record key) 
{ 
    if (node == NULL) 
        return(newNode(key)); 
	int cmp=RecordCompare(&key,&node->key);
    if (cmp<0) 
        node->left  = insert(node->left, key); 
    else if (cmp>0) 
        node->right = insert(node->right, key); 
    else 
        return node; 
  
    node->height = 1 + max(height(node->left), 
                        height(node->right)); 
    int balance = getBalance(node); 

//    if (balance > 1 && RecordCompare(&key, &node->left->key)<0) 
//        return rightRotate(node); 
//  
//    
//    if (balance > 1 && RecordCompare(&key, &node->right->key)>0) 
//    {
//    	return leftRotate(node); 
//    }
//
//    if (balance > 1 && RecordCompare(&key, &node->left->key)>0) 
//    { 
//        node->left =  leftRotate(node->left); 
//        return rightRotate(node); 
//    } 
//  
//    if (balance < -1 && RecordCompare(&key, &node->right->key)<0) 
//    { 
//        node->right = rightRotate(node->right); 
//        return leftRotate(node); 
//    } 
    return node; 
} 
  



void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        //printf("%d ", root->key); 
        preOrder(root->left); 
		RecordPrint(&root->key);
        preOrder(root->right); 
    } 
} 
