//
// Created by xxg20 on 18/02/2022.
//

//
// Part C: search pr
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#define MAX 1000

typedef struct prNode{
    char* url; // urls
    int c;     //#appearance of a url
    double PR;  // pagerank values
} prNode;

prNode *array; //collections to store the related PR info
struct prNode sort; //for sorting

void updateArray(char* token);

int count = 0; //#urls in pagerankList

int main(int argc, char *argv[]){

    //take at least one word
    if (argc > 1){

        //reading the pagerank.txt
        FILE *pr;
        char urls[MAX], outd[MAX], prvalues[MAX];// urls, outdegree, pagerank values
        char ret = '\0';
        array = malloc((count+1)*sizeof(prNode));
        assert( array != NULL);

        pr = fopen("pagerankList.txt", "r");
        while (!feof(pr)){
            if(fscanf(pr, "%s, %s, %s", urls, outd, prvalues)){

                array[count].url = malloc(strlen(urls)*sizeof(char));
                assert(array[count].url != NULL);

                strcpy(array[count].url, urls);
                array[count].url[strlen(urls)-1] = ret;
                array[count].PR = atof(prvalues);

                count++;
                array = realloc(array, (count+1)*sizeof(prNode)); //resize
            }
        }
        fclose(pr);

        count -= 1;
        if (count == 0){
            return 0;
        }


        //initialisation of c
        int x;
        for (x = 0; x < count; x++){
            array[x].c = 0;
        }


        //reading the invertedIndex.txt
        //Reference: ass-getting-started exTKns.c
        char delim[2] = " ";
        char *token, *first;
        char line[MAX];
        FILE *inverted;

        inverted = fopen("invertedIndex.txt", "r");
        while (fgets(line, MAX, inverted) != NULL) {
            /* first token */
            token = strtok(line, delim);
            first = token;

            /* iterate over the rest of the tokens */
            int input;
            for (input = 1; input < argc; input++){
                while (token != NULL && strcmp(first, argv[input])==0) {
                    if (strcmp(token, argv[input]) != 0){ //skip the word

                        updateArray(token); //find the index of the url then add 1 into its #c
                    }
                    token = strtok(NULL, delim);
                }
            }
        }
        //Reference: ass-getting-started exTKns.c



        //sorting based on PR ranking
        int i, j;
        for (i = 1; i < count; i++) {
            for (j = 0; j < count; j++){
                if (array[j].PR < array[j+1].PR){
                    sort = array[j];
                    array[j] = array[j+1];
                    array[j+1] = sort;

                }
            }
        }
        //sorting based on counts of appearances of urls
        for (i = 1; i < count; i++) {
            for (j = 0; j < count; j++){
                if (array[j].c < array[j+1].c){
                    sort = array[j];
                    array[j] = array[j+1];
                    array[j+1] = sort;

                }
            }
        }


        //stdout the urls, max# url = 30
        int k;
        for (k = 0; k < count; k++){
            if (array[k].c > 0 && array[k].c < argc && k < 30){
                printf("%s\n", array[k].url);
            }

        }

    }


    return 0;
}


//update the #c in the array
void updateArray(char* token){
    int i;

    for (i = 0; i < count; i++ ){
        if (token[strlen(token)-1] == '\n'){
            token[strlen(token)-1] = '\0';   //modify the last url in a line
        }

        if (strcmp(token, array[i].url) == 0) {
            array[i].c ++;
        }
    }
}