#include "bridge.h"
#include <iostream>

int main(int nargs,char* args[])
{
    MPI_Init(NULL,NULL);
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    printf("%d \n",r);
    MPI_Finalize();
    return 0;
}
