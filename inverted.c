//
// Created by xxg20 on 18/02/2022.
//

//
// Part B - inverted
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "InvertedIdx.h"

#define MAX 1000
#define LONGESTWORD 45


char **urllst; //lst of urls
int count = 0; //#urls in collection
char* normalise(char *word);
void outputTree(Tree t);

int main(){

    FILE *collection;
    char temp[MAX];
    urllst = malloc((count+1)*sizeof(char*));
    assert(urllst != NULL);
    collection = fopen("collection.txt", "r");
    //read the urls from collection
    while (!feof(collection)){
        if ( fscanf(collection, "%s", temp) ){
            urllst[count] = malloc(strlen(temp)*sizeof(char));
            assert(urllst[count] != NULL);
            strcpy(urllst[count], temp);

            count++;
            urllst = realloc(urllst, (count+1)*sizeof(char*)); //resize
        }
    }
    fclose(collection);

    count -= 1;
    if (count == 0){
        return 0;
    }


    Tree t = newTree(); //Invertedidx.h

    FILE *urls;
    char word[LONGESTWORD];
    int i, check;
    char name[MAX];
    //reading the urls files - section 2
    for (i = 0; i < count; i++){
        strcpy(name, urllst[i]);
        strcat(name, ".txt");
        urls = fopen(name, "r");

        check = 0;
        while (!feof(urls)){

            if (fscanf(urls, "%s ", word)){
                if (strcmp(word, "Section-2") == 0){
                    check = 1;
                }

                if (strcmp(word, "#end") == 0 && check == 1){
                    check++;
                }

                if (check == 1 && strcmp(word, "Section-2") != 0){
                    normalise(word); //normalise the word

                    t = TreeInsert(t, word);
                }
            } else {
                continue;
            }

        }

        fclose(urls);
    }

    outputTree(t);

    return 0;
}


/*removing leading and trailing spaces,
converting all characters to lowercase,
remove the following punctuation marks, if they appear at the end of a word
*/
char* normalise(char *word){
    int i = 0, j = 0;
    char temp[LONGESTWORD];

    while (word[i] != '\0'){
        if (isalpha(word[i]) != 0){
            word[i] = tolower(word[i]);
            temp[j] = word[i];
            j++;
        }
        i++;
    }

    if (j != 0){
        strcpy(word, temp);
        word[j] = '\0';
    }

    return word;
}


void outputTree(Tree t) {
    if (t == NULL) {
        return;

    } else {

        outputTree(t->left);

        FILE *inverted = fopen("invertedIndex.txt", "a");
        fprintf(inverted, "%s ", t->data); //start with the word
        FILE *urls;
        char word[LONGESTWORD];
        int i, check;
        char name[MAX];
        //re - reading the urls files - section 2
        for (i = 0; i < count; i++) {
            strcpy(name, urllst[i]);
            strcat(name, ".txt");
            urls = fopen(name, "r");

            check = 0;
            while (!feof(urls)) {

                if (fscanf(urls, "%s ", word)) {
                    if (strcmp(word, "Section-2") == 0) {
                        check = 1;
                    }

                    if (strcmp(word, "#end") == 0 && check == 1) {
                        check++;
                    }

                    if (check == 1 && strcmp(word, "Section-2") != 0) {
                        normalise(word); //normalise the word
                        if (strcmp(word, t->data) == 0) {
                            fprintf(inverted, "%s ", urllst[i]);
                            break;
                        }

                    }
                }

            }

            fclose(urls);
        }
        fprintf(inverted, "\n");
        fclose(inverted);

        outputTree(t->right);
    }
}