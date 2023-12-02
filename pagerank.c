//
// Created by xxg20 on 18/02/2022.
//
//
// Part A - page rank
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Graph.h" //Adjacency Matrix Representation Graph ADT interface graph.h

#define MAX 1000

char **urllst; //array used to store the index and the related url file
int count = 0; //#url files in collections
int *outurl; //array used to store #outdegree


void pageRank(Graph g, double d, double diffPR, int maxIterations); //output the PR file, "How to Implement
void insertionSort(double array[], int n); //reference: week 1 lecture a Page 32: Example Insertion sort in C


int main(int argc, char *argv[]){
    // take three arguments (damping factor,difference in PageRank sum, maximum iterations)
    if (argc == 4){
        FILE *collection;
        char temp[MAX];
        urllst = malloc((count+1)*sizeof(char*));
        assert(urllst != NULL);

        //read the urls from collection
        collection = fopen("collection.txt", "r");
        while (!feof(collection)){
            if ( fscanf(collection, "%s", temp) ){
                urllst[count] = malloc(strlen(temp)*sizeof(char));
                assert(urllst[count] != NULL);
                strcpy(urllst[count], temp); //store the urls with ordered index

                count++;
                urllst = realloc(urllst, (count+1)*sizeof(char*)); //resize
            }
        }
        fclose(collection);

        count -= 1;
        if (count == 0){
            return 0;
        }

        if (atof(argv[1]) && atof(argv[2]) && atoi(argv[3])){

            Graph g = newGraph(count); //Graph.h

            FILE *url;
            char name[MAX], temp2[MAX];
            outurl = malloc(count*sizeof(int));
            assert(outurl != NULL);

            //iteration of the urls in collection
            int i, j;
            for (i = 0; i < count; i++){
                strcpy(name, urllst[i]);
                strcat(name, ".txt");
                url = fopen(name, "r");
                int outDegree = 0;

                while (!feof(url)){
                    fscanf(url, "%s", temp2);
                    if (strcmp(temp2, "#start") == 0 || strcmp(temp2, "Section-1") == 0){
                        continue; //skip the start
                    } else if (strcmp(temp2, "#end") == 0) {
                        break; //finish
                    } else {
                        outDegree++; //count the #of outgoing urls
                    }

                    //find the related url and insert the edge
                    for (j = 0; j < count; j++){
                        if (strcmp(urllst[j], temp2) == 0){
                            Edge e; //Graph.h
                            e.v = i;
                            e.w = j;
                            insertEdge(g, e);
                            break;
                        }
                    }

                }

                outurl[i] = outDegree;
                fclose(url);
            }


            double d = atof(argv[1]); //damping factor
            double diffPR = atof(argv[2]); //difference in PageRank sum
            int maxIterations = atoi(argv[3]); //maximum iterations

            pageRank(g, d, diffPR, maxIterations) ; //calculate PageRank for every url and output

        }

    }

    return 0;
}


//calculate pagerank and output the txt
void pageRank(Graph g, double d, double diffPR, int maxIterations){

    int iteration = 0;
    double diff = diffPR;
    int N = g->nV;
    double prePR[N], currPR[N], orderedPR[N];

    //PageRank Algorithm
    int i, j;
    for (i = 0; i < N; i++){
        prePR[i] = 1.0/N;
        currPR[i] = 0;
    }


    while (iteration < maxIterations && diff >= diffPR){
        iteration ++;
        for (i = 0; i < N; i++){
            double sum = 0;
            for (j = 0; j < N; j++){
                if (g->edges[j][i]){
                    sum += prePR[j] / outurl[j];
                }
            }
            currPR[i] = (1.0 - d)/N + d*sum;  //PR(Pi;t+1)
        }

        for (i = 0; i < N; i++){
            diff += fabs(currPR[i] - prePR[i]); //update the diff
            prePR[i] = currPR[i]; //store the pr value
            currPR[i] = 0;
            orderedPR[i] = prePR[i]; //for sorting
        }
        insertionSort(orderedPR, count); //reference: week 1 lecture a Page 32: Example Insertion sort in C

    }


    //writing the file
    FILE *pr;
    pr = fopen("pagerankList.txt","w");
    i = 0;
    while (i < N){
        j = 0;
        while (j < N){
            if (prePR[j] == orderedPR[i]){ //sorting url,outdegree with the pr values
                fprintf(pr,"%s, %d, %.7lf\n", urllst[j], outurl[j], orderedPR[i]);
                break;
            }
            j++;
        }
        i++;
    }
    fclose(pr);


}


//reference: week 1 lecture a Page 32: Example Insertion sort in C
void insertionSort(double array[], int n){
    int i;
    for (i = 1; i < n; i++) {
        double element = array[i];
        int j = i-1;
        while (j >= 0 && array[j] < element) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = element;
    }

}

