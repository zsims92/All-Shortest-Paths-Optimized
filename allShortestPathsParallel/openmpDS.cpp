#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <limits.h>
#include <ctime>
#include <cstdlib>
#include "common.h"
#define LARGEINT 2<<30-1
int V;
int** graph;

int minDistance(int dist[], bool sptSet[])
{
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
 
   return min_index;
}

void dijkstra(int src)
{
     int dist[V];    
 
     bool sptSet[V]; 

     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
     dist[src] = 0;
 
     for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
 
       sptSet[u] = true;
 
       for (int v = 0; v < V; v++)
 
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 
}

int main(int argc, char **argv)
{  
	int i,j;
	double timer;

	if( find_option( argc, argv, "-h" ) >= 0 )
   	{
        	printf( "Options:\n" );
        	printf( "-h to see this help\n" );
       		printf( "-n <int> to set number of vertices\n" );
        	printf( "-d <0.0-1.0> to set number of vertices\n" );
        	printf( "-s <filename> to specify a summary file name\n" );
       		return 0;
    	}

    	char *sumname = read_string( argc, argv, "-s", NULL );
    	FILE *fsum = sumname ? fopen ( sumname, "a" ) : NULL;

    	V = read_int( argc, argv, "-n", 1000);
   	graph = (int**)malloc(sizeof(int*) * V);
    	for(i=0; i<V; i++){
       		 graph[i] = (int*)malloc(sizeof(int) * V);
    	}

   	srand(time(NULL));	
	
	for (i = 0; i < V; ++i)
          	for (j = 0; j < V; ++j)
            		if (i==j)
               			graph[i][j]=0;
            		else
                		graph[i][j]= (rand()%(50));	

	timer = omp_get_wtime();
	int x;	
	#pragma omp parallel for
	for(i=0; i < V; i++){
		dijkstra(i);  
		x = omp_get_num_threads();
	}
	timer = omp_get_wtime() - timer;
	if( fsum)
        	fprintf(fsum,"%d %d %g\n",V,x,timer);
	
	printf("Time %f\n", timer);	
}
	
