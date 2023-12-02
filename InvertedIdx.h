//
// Created by xxg20 on 18/02/2022.
//
/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2020.
 You may need to modify the following implementation and test it properly before using
 in your program.
*/

//Reference: ass-getting-started files
#include <stdbool.h>

typedef char *Item;      // item is just a key

typedef struct Node *Tree;
typedef struct Node {
    Tree left, right;
    char  data[100];
} Node;

//Reference: ass-getting-started files
Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree

Tree TreeInsert(Tree, Item);   // insert a new item into a Tree
