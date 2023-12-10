#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hbt.h"
#include "bst.h"





void inorderTraversal(Tnode * head){
    if(head != NULL){
        inorderTraversal(head->left);
        printf("VAL: %d\n ", head->key);
        printf("BALANCE: %d\n", head->balance);
        //printf("%d ", head->key);
        inorderTraversal(head->right);
    }
}

void print2DUtil(Tnode* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Tnode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}


int getHeight(Tnode * head){  
    if(head == NULL){
        return 0;
    }
    else{
        int ret = 1 + max(getHeight(head->left), getHeight(head->right));
        return ret;
    }

}

Tnode * rightRotation(Tnode * y) {
    Tnode * x = NULL;
    x = y->left;

    y->left = x->right;
    x->right = y;

    x->balance = calcBF(x);
    
    y->balance = calcBF(y);


    return x;
}

Tnode * leftRotation(Tnode * x){
    Tnode * y = NULL;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->balance = calcBF(x);
    y->balance = calcBF(y);
    return y;
}

Tnode * rightleftRotation(Tnode * T){
    T->right = rightRotation(T->right);
    T = leftRotation(T);
    return T;
}

Tnode * leftrightRotation(Tnode * T){
    T->left = leftRotation(T->left);
    T = rightRotation(T);
    return T;
}


Tnode * readFile(char * filename, int * exitCheck){

    // read binary file
    FILE *fptr = fopen(filename, "rb");

    if(fptr == NULL){
        printf("%d\n", -1);
        *exitCheck = EXIT_FAILURE;
        fclose(fptr);
        Tnode *first = (Tnode *) malloc(sizeof(Tnode));
        return first;
    }

    Tnode * head = (Tnode *) malloc(sizeof(Tnode));
    int * tempVal = (int *) malloc(sizeof(int));

    head->left = NULL;
    head->right = NULL;
    head->balance = 0;
    fread(tempVal, sizeof(int), 1, fptr);
    head->key = *tempVal;


    Tnode * ret = head;
    
    char * tempChar = (char *) malloc(sizeof(char));

    // insert the first node

    int counter = 1;
    while(1){
        if(counter % 2 == 0){
            if (fread(tempVal, sizeof(int), 1, fptr) < 1){
                break;
            }
    
        }
        else{
            if (fread(tempChar, sizeof(char), 1, fptr) < 1){
                break;
            }
            else{
                //printf("tempChar: %c\n", *tempChar);
                if (counter != 1){
                    // insert
                    if (*tempChar == 'i'){
                        //printf("tempVal: %d\n", *tempVal);
                        ret = insertNode(ret, tempVal);                

                        //printf("\nROOT VALUE: %d\n", ret->key);
                        //print2D(ret);
                    }

                    // delete
                    if (*tempChar == 'd'){
                        //printf("tempVal: %d\n", *tempVal);
                        ret = deleteNode(ret, tempVal);                

                        //printf("\nROOT VALUE: %d\n", ret->key);
                        //print2D(ret);
                    }
                }
                
            }
            
        }

        counter += 1;
    }

    //printf("counter: %d\n", counter);

    
    free(tempVal);
    free(tempChar);
    fclose(fptr);

    return ret;



}

Tnode * newNode(int key){
    Tnode * node = (Tnode *) malloc(sizeof(Tnode));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->balance = 0;
    return node;
}

Tnode * insertNode(Tnode * root, int * key){
    if (root == NULL){
        return newNode(*key);
    }

    if (*key < root->key || *key == root->key){
        root->left = insertNode(root->left, key);
    }

    else if (*key > root->key){
        root->right = insertNode(root->right, key);
    }

    root->balance = calcBF(root);

    int balance = root->balance;

    if (balance > 1 && *key <= root->left->key){
        return rightRotation(root);
    }

    if (balance < -1 && *key >= root->right->key)
        return leftRotation(root);
 
    if (balance > 1 && *key > root->left->key)
    {
        root->left =  leftRotation(root->left);
        return rightRotation(root);
    }
 
    if (balance < -1 && *key < root->right->key)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;

}

int calcBF(Tnode * root){
    if(root == NULL){
        return 0;
    }
    else{
        int lh = getHeight(root->left);
        int rh = getHeight(root->right);
        return (lh - rh);
    }
    
}

Tnode * inorder_pred(Tnode * root){
    while(root->right != NULL){
        root = root->right;
    }

    return root;
}

Tnode * deleteNode(Tnode * root, int * key){
    if (root == NULL){
        return root;
    }

    if (*key < root->key){
        root->left = deleteNode(root->left, key);
    }

    else if (*key > root->key){
        root->right = deleteNode(root->right, key);
    }

    else{
        // one child or no child
        if (root->left == NULL || root->right == NULL){
            Tnode * temp = root->left ? root->left : root->right;

            // no child
            if (temp == NULL){
                temp = root;
                root = NULL;
            }

            // one child
            else{
                *root = *temp;
            }
            free(temp);


        }
        // two children
        else{
            // get inorder predecessor
            Tnode * temp = inorder_pred(root->left);

            root->key = temp->key;

            // delete inorder predecessor
            int retKey = temp->key;
            root->left = deleteNode(root->left, &retKey);
        }
    }

    if (root == NULL){
        return root;
    }

    

    root->balance = calcBF(root);

    int balance = root->balance;

    if (balance > 1 && *key < root->left->key){
        return rightRotation(root);
    }

    if (balance < -1 && *key > root->right->key)
        return leftRotation(root);
 
    if (balance > 1 && *key > root->left->key)
    {
        root->left =  leftRotation(root->left);
        return rightRotation(root);
    }
 
    if (balance < -1 && *key < root->right->key)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;

}



void deleteTree(Tnode * head){

    if(head == NULL){
        return;
    }
    
    deleteTree(head->left);
    deleteTree(head->right);

    free(head);
}


// open binary file before calling this function
// pass in the output file name into this function
void fileOutput(Tnode * root, FILE * fptr){

    if (root == NULL)
        return;



    // store key as temporary int
    int tempInt = root->key;

    // append temporary int to binary file
    char pattern = 0x0;

    if (root->right != NULL){
        char tempPattern = 0x1;
        pattern = pattern | tempPattern;
    }

    if (root->left != NULL){
        char tempPattern = 0x2;
        pattern = pattern | tempPattern;
    }

    // write to binary file int and char
    fwrite(&tempInt, sizeof(int), 1, fptr);
    fwrite(&pattern, sizeof(char), 1, fptr);

    // remaining preorder traversal of tree
    fileOutput(root->left, fptr);

    fileOutput(root->right, fptr);


}

void optionB(Tnode * root, char * outputFileName){
    // open file
    FILE *fptr = fopen(outputFileName, "wb");

    if(fptr == NULL){
        printf("FILE OPEN UNSUCCESSFUL!");
    }

    // file output method (writing to file)
    fileOutput(root, fptr);
    // close file
    fclose(fptr);
}

// linked list stack methods

Tnode * top = NULL;

void push(int val){
    Tnode * newNode = (Tnode * ) malloc(sizeof(Tnode));
    newNode->key = val;
    newNode->balance = 0;
    newNode->left = NULL;
    if (top == NULL){
        newNode->right = NULL;
    }
    else{
        newNode->right = top;
    }
    top = newNode;
}

int pop(){
    if(top != NULL){
        Tnode * temp = top;
        int tempVal = top->key;
        top = top->right;
        free(temp);
        return tempVal;
    }

    return INT_MIN;
}


Tnode * bstFromPreorder(int arr[], int low, int high){

    if (low > high){
        return NULL;
    }
    if (low == high){
        Tnode * ret = (Tnode *) malloc(sizeof(Tnode));
        ret->key = arr[low];
        ret->left = NULL;
        ret->right = NULL;
        ret->balance = 0;
        return ret;
    }

    Tnode * root = (Tnode *) malloc(sizeof(Tnode));
    root->key = arr[low];
    root->left = NULL;
    root->right = NULL;
    root->balance = 0;

    int idx = -1;
    for(int i = low + 1; i <= high; i++){
        if(arr[i] > arr[low]){
            idx = i;
            break;
        }
    }

    if (idx == -1){
        root->left = bstFromPreorder(arr, low + 1, high);
    }

    else{
        root->left = bstFromPreorder(arr, low + 1, idx - 1);
        root->right = bstFromPreorder(arr, idx, high);
    }

    return root;
}

void setBF(Tnode * root){
    if (root != NULL){
        root->balance = calcBF(root);
        setBF(root->left);
        setBF(root->right);
    }
}

void checkBF(Tnode * root, int * check3){
    if(root != NULL){
        if(root->balance >= 2 || root->balance <= -2){
            *check3 = 0;
        }
        checkBF(root->left, check3);
        checkBF(root->right, check3);
    }
}



void optionE(char * fileInput, int * check1, int * check2, int * check3){

    // check input file validity
    FILE * fptr = fopen(fileInput, "rb");
    
    if (fptr == NULL){
        *check1 = -1;
        fclose(fptr);
        return;
    }
    else{
        *check1 = 1;
        // include case where file opens but is invalid --> set check1 to 0.
    }

    // create linked list of vals (using Tnode)
    int * tempVal = (int * ) malloc(sizeof(int));
    Tnode * list = (Tnode * ) malloc(sizeof(Tnode));
    char * tempChar = (char *) malloc(sizeof(char));

    fread(tempVal, sizeof(int), 1, fptr);

    list->key = *tempVal;
    list->balance = 0;
    list->left = NULL;
    list->right = NULL;
    

    Tnode * head = list;

    int counter = 1;

    while(1){
        if(counter % 2 == 0){
            if (fread(tempVal, sizeof(int), 1, fptr) < 1){
                break;
            }
            else{
                Tnode * temp = (Tnode *) malloc(sizeof(Tnode));
                temp->key = *tempVal;
                temp->balance = 0;
                temp->left = NULL;
                temp->right = NULL;
                list->right = temp;
                list = list->right;
            }
    
        }
        else{
            if (fread(tempChar, sizeof(char), 1, fptr) < 1){
                break;
            }
        }
        counter += 1;
    }

    //printf("COUNTER: %d", counter);

    // check binary search tree validity from preorder traversal
    int root = INT_MIN;
    list = head;

    while(list != NULL){

        if (list->key < root){ 
            *check2 = 0;
            break;
        }
        
        while(top != NULL && list->key > top->key){
            root = top->key;
            pop();
        }

        

        push(list->key);

        list = list->right;
    }

    if( *check2 != 0){
        *check2 = 1;
    }

    while(top != NULL){
        Tnode * temp = top;
        top = top->right;
        free(temp);
    }

    // check height balances of binary search tree    
    // create array
    
    list = head;
    int size = counter / 2;
    int * arr = (int *) malloc(size * sizeof(int));
    int i = 0;
    while(list != NULL){
        arr[i] = list->key;
        list = list->right;
        i += 1;
    }
    // construct bst
    Tnode * bst = bstFromPreorder(arr, 0, size - 1);

    // check bst balances
    setBF(bst);
    checkBF(bst, check3);

    if (*check3 != 0){
        *check3 = 1;
    }

   //print2D(bst);

    deleteTree(bst);
    


    // free all the memory
    free(arr);
    free(tempVal);
    free(tempChar);
    while(head != NULL){
        Tnode * temp = head;
        head = head->right;
        free(temp);
    }
    
    fclose(fptr);
    
}