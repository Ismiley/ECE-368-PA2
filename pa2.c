#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.c"

int main(int argc, char ** argv){

    if (argc == 4) {
        if (strcmp(argv[1], "-b") == 0){
            // read tree

            Tnode* root;
            int * exitCheck = (int *) malloc(sizeof(int));
            root = readFile(argv[2], exitCheck);
            if(*exitCheck == EXIT_FAILURE){
                deleteTree(root);
                free(exitCheck);
                return EXIT_FAILURE;
            }
            Tnode * dummy = root;

            // print tree
            //printf("TREE PRINTING STARTS HERE: \n");
            //inorderTraversal(dummy);

            dummy = root;

            // output file
            optionB(dummy, argv[3]);

            // delete tree
            deleteTree(dummy);

            free(exitCheck);

            printf("%d\n", 1);
            return EXIT_SUCCESS;
        }
        else{
            printf("%d\n", -1);
            return EXIT_FAILURE;
        }
    }

    if (argc == 3){
        if (strcmp(argv[1], "-e") == 0){
            int * check1 = (int * ) malloc(sizeof(int));
            int * check2 = (int * ) malloc(sizeof(int));
            int * check3 = (int * ) malloc(sizeof(int));
            *check1 = -2;
            *check2 = -2;
            *check3 = -2;

            optionE(argv[2], check1, check2, check3);

            printf("%d,%d,%d\n", *check1, *check2, *check3);

            free(check1);
            free(check2);
            free(check3);
        }
        else{
            printf("%d\n", -1);
            return EXIT_FAILURE;
        }
    }

    if (argc != 3 && argc != 4){
        printf("%d\n", -1);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
