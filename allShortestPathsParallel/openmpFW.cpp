#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "common.h" 
#define LARGEINT 2<<30-1
#include <ctime>
#include <cstdlib>
int n, nt;
int** dist; 

void floyd_warshall() {
    int i, j, k;
 
    for (k = 0; k < n; ++k)
        #pragma omp parallel for private(i,j)
        for (i = 0; i < n; ++i){
	    nt = omp_get_num_threads();
            for (j = 0; j < n; ++j)
                if ((dist[i][k] * dist[k][j] != 0) && (i != j))
                    if ((dist[i][k] + dist[k][j] < dist[i][j]) || (dist[i][j] == 0))
                        dist[i][j] = dist[i][k] + dist[k][j];
        }
}
 
int main(int argc, char *argv[]) {
    double start,stop;
    int i, j;
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
	
    n = read_int( argc, argv, "-n", 1000);	
    dist = (int**)malloc(sizeof(int*) * n);
    for(i=0; i<n; i++){
	dist[i] = (int*)malloc(sizeof(int) * n);
    }

    srand(time(NULL));

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (i==j)
                dist[i][j]=0;
            else
                dist[i][j]= (rand()%(50));
    start = omp_get_wtime();
    floyd_warshall();
    stop = omp_get_wtime();
 
    if( fsum)
        fprintf(fsum,"%d %d %g\n",n,nt,stop-start);
 
    printf("time %f\n",stop-start);
 
    return 0;
}
