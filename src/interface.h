#ifndef __c_h__
#define __c_h__
#include <string>
#include <cstddef>
#include <type_traits>
#define GENDCL(X,SZ,AL) \
class X\
{\
public:\
    static constexpr std::size_t c_impl_size = SZ;\
    static constexpr std::size_t c_impl_alignment = AL;\
    typedef std::aligned_storage<c_impl_size, c_impl_alignment>::type aligned_storage_type;\
    aligned_storage_type impl;\
    X();\
    X(const X&);\
    X(X&&);\
    ~X();\
    X& operator=(const X&);\
    X& operator=(X&&);\
};\

#define GENDCLPREDEF(X,Y) static const X Y;

#define GENDCL1(X,SZ,AL) GENDCL(I_##X,SZ,AL)
#define GENDCLPREDEF2(X,Y) GENDCLPREDEF(I_##X,I_##Y)

GENDCL1(MPI_Comm,8,8)
GENDCL1(MPI_Op,8,8)
GENDCL1(MPI_Datatype,8,8)
GENDCL1(MPI_Status_ptr,8,8)
GENDCL1(MPI_Comm_ptr,8,8)



class PreDefined
{
public:
    GENDCLPREDEF2(MPI_Comm,MPI_COMM_WORLD)
    GENDCLPREDEF2(MPI_Comm,MPI_COMM_NULL)
    
    GENDCLPREDEF2(MPI_Op,MPI_SUM)
    GENDCLPREDEF2(MPI_Op,MPI_MIN)
    GENDCLPREDEF2(MPI_Op,MPI_MAX)
    
    
    GENDCLPREDEF2(MPI_Datatype,MPI_BYTE)
    GENDCLPREDEF2(MPI_Datatype,MPI_CHAR)
    GENDCLPREDEF2(MPI_Datatype,MPI_SHORT)
    GENDCLPREDEF2(MPI_Datatype,MPI_INT)
    GENDCLPREDEF2(MPI_Datatype,MPI_LONG)
    GENDCLPREDEF2(MPI_Datatype,MPI_LONG_LONG)
    GENDCLPREDEF2(MPI_Datatype,MPI_UNSIGNED_CHAR)
    GENDCLPREDEF2(MPI_Datatype,MPI_UNSIGNED_SHORT)
    GENDCLPREDEF2(MPI_Datatype,MPI_UNSIGNED)
    GENDCLPREDEF2(MPI_Datatype,MPI_UNSIGNED_LONG)
    GENDCLPREDEF2(MPI_Datatype,MPI_UNSIGNED_LONG_LONG)
    GENDCLPREDEF2(MPI_Datatype,MPI_FLOAT)
    GENDCLPREDEF2(MPI_Datatype,MPI_DOUBLE)
    GENDCLPREDEF2(MPI_Datatype,MPI_LONG_DOUBLE)
    
    GENDCLPREDEF2(MPI_Status_ptr,MPI_STATUS_IGNORE)
    
    const static size_t I_MPI_MAX_PROCESSOR_NAME;
    const static int I_MPI_UNDEFINED;
};


int I_MPI_Allreduce(const void*,void*,int,I_MPI_Datatype,I_MPI_Op,I_MPI_Comm);
int I_MPI_Barrier(I_MPI_Comm);
int I_MPI_Bcast(void*,int,I_MPI_Datatype,int,I_MPI_Comm);
int I_MPI_Cart_create(I_MPI_Comm,int ndims,const int [],const int [],int,I_MPI_Comm_ptr);
int I_MPI_Cart_get(I_MPI_Comm,int,int [],int [],int []);
int I_MPI_Cart_shift(I_MPI_Comm,int,int,int*,int*);
int I_MPI_Comm_free(I_MPI_Comm_ptr);
int I_MPI_Comm_rank(I_MPI_Comm,int*);
int I_MPI_Comm_size(I_MPI_Comm,int*);
int I_MPI_Comm_split(I_MPI_Comm,int,int,I_MPI_Comm_ptr);
int I_MPI_Finalize(void);
int I_MPI_Finalized(int*);
int I_MPI_Get_processor_name(char*,int*);
int I_MPI_Init(int*,char***);
int I_MPI_Initialized(int*);
int I_MPI_Recv(void*,int,I_MPI_Datatype,int,int,I_MPI_Comm,I_MPI_Status_ptr);
int I_MPI_Reduce(const void*,void*,int,I_MPI_Datatype,I_MPI_Op,int,I_MPI_Comm);
int I_MPI_Scan(const void*,void*,int,I_MPI_Datatype,I_MPI_Op,I_MPI_Comm);
int I_MPI_Send(const void*,int,I_MPI_Datatype,int,int,I_MPI_Comm);
int I_MPI_Sendrecv(const void*,int,I_MPI_Datatype,int,int,void*,int,I_MPI_Datatype,int,int,I_MPI_Comm,I_MPI_Status_ptr);
/*
signatures taken from mpich website
remeber we did this
typedef MPI_Status* MPI_Status_ptr;
typedef MPI_Comm* MPI_Comm_ptr;
 
int I_MPI_Allreduce(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,I_MPI_Comm comm);
int I_MPI_Barrier(I_MPI_Comm comm);
int I_MPI_Bcast(void* buffer,int count,I_MPI_Datatype datatype,int root,I_MPI_Comm comm);
int I_MPI_Cart_create(I_MPI_Comm comm_old,int ndims,const int dims[],const int periods[],int reorder,I_MPI_Comm_ptr comm_cart);
int I_MPI_Cart_get(I_MPI_Comm comm,int maxdims,int dims[],int periods[],int coords[]);
int I_MPI_Cart_shift(I_MPI_Comm comm,int direction,int disp,int* rank_source,int* rank_dest);
int I_MPI_Comm_free(I_MPI_Comm_ptr comm);
int I_MPI_Comm_rank(I_MPI_Comm comm,int* rank);
int I_MPI_Comm_size(I_MPI_Comm comm,int* size);
int I_MPI_Comm_split(I_MPI_Comm comm,int color,int key,I_MPI_Comm_ptr newcomm);
int I_MPI_Finalize(void);
int I_MPI_Finalized(int* flag);
int I_MPI_Get_processor_name(char* name,int* resultlen);
int I_MPI_Init(int* argc,char*** argv);
int I_MPI_Initialized(int* flag);
int I_MPI_Recv(void* buf,int count,I_MPI_Datatype datatype,int source,int tag,I_MPI_Comm comm,I_MPI_Status_ptr status);
int I_MPI_Reduce(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,int root,I_MPI_Comm comm);
int I_MPI_Scan(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,I_MPI_Comm comm);
int I_MPI_Send(const void* buf,int count,I_MPI_Datatype datatype,int dest,int tag,I_MPI_Comm comm);
int I_MPI_Sendrecv(const void* sendbuf,int sendcount,I_MPI_Datatype sendtype,int dest,int sendtag,void* recvbuf,int recvcount,I_MPI_Datatype recvtype,int source,int recvtag,I_MPI_Comm comm,I_MPI_Status_ptr status);
*/
/*
 int MPI_Allreduce(const void* sendbuf,void* recvbuf,int count,MPI_Datatype datatype,MPI_Op op,MPI_Comm comm)
 int MPI_Barrier(MPI_Comm comm)
 int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int root,MPI_Comm comm)
 int MPI_Cart_create(MPI_Comm comm_old,int ndims,const int dims[],const int periods[],int reorder,MPI_Comm* comm_cart)
 int MPI_Cart_get(MPI_Comm comm,int maxdims,int dims[],int periods[],int coords[])
 int MPI_Cart_shift(MPI_Comm comm,int direction,int disp,int* rank_source,int* rank_dest)
 int MPI_Comm_free(MPI_Comm* comm)
 int MPI_Comm_rank(MPI_Comm comm,int* rank)
 int MPI_Comm_size(MPI_Comm comm,int* size)
 int MPI_Comm_split(MPI_Comm comm,int color,int key,MPI_Comm* newcomm)
 int MPI_Finalize(void)
 int MPI_Finalized(int* flag)
 int MPI_Get_processor_name(char* name,int* resultlen)
 int MPI_Init(int* argc,char*** argv)
 int MPI_Initialized(int* flag)
 int MPI_Recv(void* buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm comm,MPI_Status_ptr status)
 int MPI_Reduce(const void* sendbuf,void* recvbuf,int count,MPI_Datatype datatype,MPI_Op op,int root,MPI_Comm comm)
 int MPI_Scan(const void* sendbuf,void* recvbuf,int count,MPI_Datatype datatype,MPI_Op op,MPI_Comm comm)
 int MPI_Send(const void* buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
 int MPI_Sendrecv(const void* sendbuf,int sendcount,MPI_Datatype sendtype,int dest,int sendtag,void* recvbuf,int recvcount,MPI_Datatype recvtype,int source,int recvtag,MPI_Comm comm,MPI_Status_ptr status)
 */
#endif

