#include <iostream>
#include <vector>
#include <stdio.h>
#include "common.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv){

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

    int n = read_int( argc, argv, "-n", 1000);
    int** dist = (int**)malloc(sizeof(int*) * n);
    for(int i=0; i<n; i++){
        dist[i] = (int*)malloc(sizeof(int) * n);
    }

    srand(time(NULL));
    int i,j;	
	for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (i==j)
                dist[i][j]=0;
            else
                dist[i][j]= (rand()%(50));


    double time = read_timer();
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
    time = read_timer() - time;
    if( fsum)
        fprintf(fsum,"%d %g\n",n,time); 
 
    std::cout << time << std::endl;
    return 0;
}
