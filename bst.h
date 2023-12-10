#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// functions
void inorderTraversal(Tnode * head);
void print2DUtil(Tnode* root, int space);
void print2D(Tnode* root);
int max(int a, int b);
int getHeight(Tnode * head);
Tnode * rightRotation(Tnode * y);
Tnode * leftRotation(Tnode * x);
Tnode * rightleftRotation(Tnode * T);
Tnode * leftrightRotation(Tnode * T);
Tnode * readFile(char * filename, int * exitCheck);
Tnode * newNode(int key);
Tnode * insertNode(Tnode * root, int * key);
int calcBF(Tnode * root);
Tnode * inorder_pred(Tnode * root);
Tnode * deleteNode(Tnode * root, int * key);
void deleteTree(Tnode * head);
void fileOutput(Tnode * root, FILE * fptr);
void optionB(Tnode * root, char * outputFileName);
void push(int val);
int pop();
int r_sub_idx(int arr[], int l, int r, int key);
Tnode * bstFromPreorder(int arr[], int low, int high);
void optionE(char * fileInput, int * check1, int * check2, int * check3);