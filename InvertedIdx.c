//
// Created by xxg20 on 18/02/2022.
//
/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2020.
 You may need to modify the following implementation and test it properly before using
 in your program.
*/

//Reference: ass-getting-started files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InvertedIdx.h"


#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

//Reference: ass-getting-started files
// make a new node containing data
Tree newNode(Item it) {
    Tree new = malloc(sizeof(Node));
    assert(new != NULL);
    strcpy(new->data, it);  // replace,   data(new) = it;
    left(new) = right(new) = NULL;
    return new;
}

//Reference: ass-getting-started files
// create a new empty Tree
Tree newTree() {
    return NULL;
}

//Reference: ass-getting-started files
// free memory associated with Tree
void freeTree(Tree t) {
    if (t != NULL) {
        freeTree(left(t));
        freeTree(right(t));
        free(t ->data);
        free(t);
    }
}


//Reference: ass-getting-started files
// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
    if (t == NULL){
        t = newNode(it);
    }

    else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
        left(t) = TreeInsert(left(t), it);

    else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
        right(t) = TreeInsert(right(t), it);

    return t;
}
