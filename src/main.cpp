#include "bridge.h"
#include <cstdio>
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
/*
#include <mpi.h>
#include <iostream>

template<class T>
class print_size_align
{
public:
    static void f(const char* t)
    {
        printf("%s: size=%zu align=%zu\n",t,sizeof(T),alignof(T));
 
    }
};
#define SZA(X) print_size_align<X>::f(#X)
int main(int nargs,char *args[])
{
    SZA(MPI_Comm);
    SZA(MPI_Request);
    SZA(MPI_Request*);
    SZA(MPI_Op);
    SZA(MPI_Datatype);
    SZA(int*);
 
 
    return 0;
}
 */
