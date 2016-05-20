#include <stdio.h>
#include <limits.h>
#include "common.h" 
#include <ctime>
#include <cstdlib>
int V;
 
int minDistance(int dist[], bool sptSet[])
{
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
 
   return min_index;
}


void dijkstra(int** graph, int src)
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
 
         if (!sptSet[v] && graph[u][v] && graph[u][v] != -1 && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 
}
 
int main(int argc, char **argv)
{
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
    int** dist = (int**)malloc(sizeof(int*) * V);
    for(int i=0; i<V; i++){
        dist[i] = (int*)malloc(sizeof(int) * V);
    }

    srand(time(NULL));
	
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (i==j)
                dist[i][j]=0;
            else
                dist[i][j]= (rand()%(50));
				
   double time =  read_timer();
   for(int i=0; i<V; i++){
   	 dijkstra(dist, i);
   }
   time = read_timer() - time;

   if( fsum)
        fprintf(fsum,"%d %g\n",V,time); 
   printf("Run time is %f\n", time);
 
    return 0;
}
