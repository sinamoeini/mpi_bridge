#define GENBODY(X,Y) \
X::X()\
{\
    placement_delete<IMPL_MPI<Y>>(&impl);\
    static_assert(sizeof(impl) >= sizeof(IMPL_MPI<Y>),\
    "buffer not big enough to hold IMPL");\
    static_assert(\
    std::alignment_of<aligned_storage_type>::value\
    >=\
    std::alignment_of<IMPL_MPI<Y>>::value,\
    "alignment requirements of IMPL not fulfilled");\
    placement_new<IMPL_MPI<Y>>(&impl, sizeof(impl));\
}\
X::X(const X& rhs)\
{\
    *reinterpret_cast<IMPL_MPI<Y>*>(&this->impl)=\
    *reinterpret_cast<const IMPL_MPI<Y>*>(&rhs.impl);\
}\
X::X(X&& other)\
{\
    *reinterpret_cast<IMPL_MPI<Y>*>(&this->impl)=\
    std::move(*reinterpret_cast<const IMPL_MPI<Y>*>(&other.impl));\
}\
X::~X()\
{\
    placement_delete<IMPL_MPI<Y>>(&impl);\
}\
X& X::operator=(const X& rhs)\
{\
    *reinterpret_cast<IMPL_MPI<Y>*>(&this->impl)=\
    *reinterpret_cast<const IMPL_MPI<Y>*>(&rhs.impl);\
    return *this;\
}\
X& X::operator=(X&& other)\
{\
    *reinterpret_cast<IMPL_MPI<Y>*>(&this->impl)=\
    std::move(*reinterpret_cast<const IMPL_MPI<Y>*>(&other.impl));\
    return *this;\
}\


#define GENPREDEF(X,Y,Z,W) \
const I_##X PreDefined::Z= impi_2_l<I_##X>::func(IMPL_MPI<Y>(W));




#define GENBODY1(X) GENBODY(I_##X,X)
#define GENBODY2(X,Y) GENBODY(I_##X,Y)

#define GENPREDEF3(X,Y,W) GENPREDEF(X,Y,I_##W,W)
#define GENPREDEF2(X,W) GENPREDEF(X,X,I_##W,W)

#include <mpi.h>
typedef MPI_Status* MPI_Status_ptr;
typedef MPI_Comm* MPI_Comm_ptr;
#include <cstddef>
#include "interface.h"




///create an object of type T at a given address
template<class T>
void placement_new(void* buff,std::size_t buff_sz)
{
    new(buff) T();
}

///cast a given address to a pointer to type T
template<class T>
T* placement_cast(void* buff)
{
    return reinterpret_cast<T*>(buff);
}

///call the destructor of type T at a given address
template<class T>
void placement_delete(void* buff)
{
    placement_cast<T>(buff)->~T();
}


template<class T>
class IMPL_MPI
{
public:
    T mpi_obj;
    IMPL_MPI()
    {};
    IMPL_MPI(const IMPL_MPI& rhs):
    mpi_obj(rhs.mpi_obj)
    {
        
    };
    IMPL_MPI(IMPL_MPI&& rhs):
    mpi_obj(std::move(rhs.mpi_obj))
    {
    };
    
    IMPL_MPI& operator =(const IMPL_MPI& rhs)
    {
        this->mpi_obj=rhs.mpi_obj;
        return *this;
    }
    
    IMPL_MPI& operator =(IMPL_MPI&& other)
    {
        this->mpi_obj=std::move(other.mpi_obj);
        return *this;
    }
    
    IMPL_MPI(T& __mpi_obj):mpi_obj(__mpi_obj)
    {};
    IMPL_MPI(T&& __mpi_obj):mpi_obj(std::move(__mpi_obj))
    {};
    
};

template<class I>
class impi_2_l
{
public:
    template<class IMPL>
    static I func(const IMPL& impl)
    {
        I ans;
        *reinterpret_cast<IMPL*>(&ans.impl)=impl;
        return ans;
    }
    template<class IMPL>
    static I func(IMPL&& impl)
    {
        I ans;
        *reinterpret_cast<IMPL*>(&ans.impl)=std::move(impl);
        return ans;
    }
};

template<class MPIOBJ>
class i_2_mpiobj
{
public:
    template<class I>
    static MPIOBJ& func(I& i)
    {
        return reinterpret_cast<IMPL_MPI<MPIOBJ>*>(&i.impl)->mpi_obj;
    }
};




GENBODY1(MPI_Comm)
GENBODY1(MPI_Op)
GENBODY1(MPI_Datatype)
GENBODY1(MPI_Status_ptr)





GENPREDEF2(MPI_Comm,MPI_COMM_WORLD);
GENPREDEF2(MPI_Comm,MPI_COMM_NULL);

GENPREDEF2(MPI_Op,MPI_SUM);
GENPREDEF2(MPI_Op,MPI_MIN);
GENPREDEF2(MPI_Op,MPI_MAX);


GENPREDEF2(MPI_Datatype,MPI_BYTE);
GENPREDEF2(MPI_Datatype,MPI_CHAR);
GENPREDEF2(MPI_Datatype,MPI_SHORT);
GENPREDEF2(MPI_Datatype,MPI_INT);
GENPREDEF2(MPI_Datatype,MPI_LONG);
GENPREDEF2(MPI_Datatype,MPI_LONG_LONG);
GENPREDEF2(MPI_Datatype,MPI_UNSIGNED_CHAR);
GENPREDEF2(MPI_Datatype,MPI_UNSIGNED_SHORT);
GENPREDEF2(MPI_Datatype,MPI_UNSIGNED);
GENPREDEF2(MPI_Datatype,MPI_UNSIGNED_LONG);
GENPREDEF2(MPI_Datatype,MPI_UNSIGNED_LONG_LONG);
GENPREDEF2(MPI_Datatype,MPI_FLOAT);
GENPREDEF2(MPI_Datatype,MPI_DOUBLE);
GENPREDEF2(MPI_Datatype,MPI_LONG_DOUBLE);

//GENPREDEF3(MPI_Status_ptr,MPI_Status*,MPI_STATUS_IGNORE);
GENPREDEF2(MPI_Status_ptr,MPI_STATUS_IGNORE);


const size_t PreDefined::I_MPI_MAX_PROCESSOR_NAME(static_cast<size_t>(MPI_MAX_PROCESSOR_NAME));
const int PreDefined::I_MPI_UNDEFINED=MPI_UNDEFINED;


/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Allreduce(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,I_MPI_Comm comm)
{
    return MPI_Allreduce(sendbuf,recvbuf,count,i_2_mpiobj<MPI_Datatype>::func(datatype),i_2_mpiobj<MPI_Op>::func(op),i_2_mpiobj<MPI_Comm>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Barrier(I_MPI_Comm comm)
{
    return MPI_Barrier(i_2_mpiobj<MPI_Comm>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Bcast(void* buffer,int count,I_MPI_Datatype datatype,int root,I_MPI_Comm comm)
{
    return MPI_Bcast(buffer,count,i_2_mpiobj<MPI_Datatype>::func(datatype),root,i_2_mpiobj<MPI_Comm>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Cart_create(I_MPI_Comm comm_old,int ndims,const int dims[],const int periods[],int reorder,I_MPI_Comm_ptr comm_cart)
{
    return MPI_Cart_create(i_2_mpiobj<MPI_Comm>::func(comm_old),ndims,dims,periods,reorder,i_2_mpiobj<MPI_Comm_ptr>::func(comm_cart));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Cart_get(I_MPI_Comm comm,int maxdims,int dims[],int periods[],int coords[])
{
    return MPI_Cart_get(i_2_mpiobj<MPI_Comm>::func(comm),maxdims,dims,periods,coords);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Cart_shift(I_MPI_Comm comm,int direction,int disp,int* rank_source,int* rank_dest)
{
    return MPI_Cart_shift(i_2_mpiobj<MPI_Comm>::func(comm),direction,disp,rank_source,rank_dest);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Comm_free(I_MPI_Comm_ptr comm)
{
    return MPI_Comm_free(i_2_mpiobj<MPI_Comm_ptr>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Comm_rank(I_MPI_Comm comm,int* rank)
{
    return MPI_Comm_rank(i_2_mpiobj<MPI_Comm>::func(comm),rank);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Comm_size(I_MPI_Comm comm,int* size)
{
    return MPI_Comm_size(i_2_mpiobj<MPI_Comm>::func(comm),size);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Comm_split(I_MPI_Comm comm,int color,int key,I_MPI_Comm_ptr newcomm)
{
    return MPI_Comm_split(i_2_mpiobj<MPI_Comm>::func(comm),color,key,i_2_mpiobj<MPI_Comm_ptr>::func(newcomm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Finalize(void)
{
    return MPI_Finalize();
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Finalized(int* flag)
{
    return MPI_Finalized(flag);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Get_processor_name(char* name,int* resultlen)
{
    return MPI_Get_processor_name(name,resultlen);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Init(int* argc,char*** argv)
{
    return MPI_Init(argc,argv);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Initialized(int* flag)
{
    return MPI_Initialized(flag);
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Recv(void* buf,int count,I_MPI_Datatype datatype,int source,int tag,I_MPI_Comm comm,I_MPI_Status_ptr status)
{
    return MPI_Recv(buf,count,i_2_mpiobj<MPI_Datatype>::func(datatype),source,tag,i_2_mpiobj<MPI_Comm>::func(comm),i_2_mpiobj<MPI_Status_ptr>::func(status));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Reduce(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,int root,I_MPI_Comm comm)
{
    return MPI_Reduce(sendbuf,recvbuf,count,i_2_mpiobj<MPI_Datatype>::func(datatype),i_2_mpiobj<MPI_Op>::func(op),root,i_2_mpiobj<MPI_Comm>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Scan(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,I_MPI_Comm comm)
{
    return MPI_Scan(sendbuf,recvbuf,count,i_2_mpiobj<MPI_Datatype>::func(datatype),i_2_mpiobj<MPI_Op>::func(op),i_2_mpiobj<MPI_Comm>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Send(const void* buf,int count,I_MPI_Datatype datatype,int dest,int tag,I_MPI_Comm comm)
{
    return MPI_Send(buf,count,i_2_mpiobj<MPI_Datatype>::func(datatype),dest,tag,i_2_mpiobj<MPI_Comm>::func(comm));
}
/*----------------------------------------------
 
 ----------------------------------------------*/
int I_MPI_Sendrecv(const void* sendbuf,int sendcount,I_MPI_Datatype sendtype,int dest,int sendtag,void* recvbuf,int recvcount,I_MPI_Datatype recvtype,int source,int recvtag,I_MPI_Comm comm,I_MPI_Status_ptr status)
{
    return MPI_Sendrecv(sendbuf,sendcount,i_2_mpiobj<MPI_Datatype>::func(sendtype),dest,sendtag,recvbuf,recvcount,i_2_mpiobj<MPI_Datatype>::func(recvtype),source,recvtag,i_2_mpiobj<MPI_Comm>::func(comm),i_2_mpiobj<MPI_Status_ptr>::func(status));
}
/*
 this is the python code that was used to generate the functions above
 
fff=['int I_MPI_Allreduce(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,I_MPI_Comm comm);',
'int I_MPI_Barrier(I_MPI_Comm comm);',
'int I_MPI_Bcast(void* buffer,int count,I_MPI_Datatype datatype,int root,I_MPI_Comm comm);',
'int I_MPI_Cart_create(I_MPI_Comm comm_old,int ndims,const int dims[],const int periods[],int reorder,I_MPI_Comm_ptr comm_cart);',
'int I_MPI_Cart_get(I_MPI_Comm comm,int maxdims,int dims[],int periods[],int coords[]);',
'int I_MPI_Cart_shift(I_MPI_Comm comm,int direction,int disp,int* rank_source,int* rank_dest);',
'int I_MPI_Comm_free(I_MPI_Comm_ptr comm);',
'int I_MPI_Comm_rank(I_MPI_Comm comm,int* rank);',
'int I_MPI_Comm_size(I_MPI_Comm comm,int* size);',
'int I_MPI_Comm_split(I_MPI_Comm comm,int color,int key,I_MPI_Comm_ptr newcomm);',
'int I_MPI_Finalize(void);',
'int I_MPI_Finalized(int* flag);',
'int I_MPI_Get_processor_name(char* name,int* resultlen);',
'int I_MPI_Init(int* argc,char*** argv);',
'int I_MPI_Initialized(int* flag);',
'int I_MPI_Recv(void* buf,int count,I_MPI_Datatype datatype,int source,int tag,I_MPI_Comm comm,I_MPI_Status_ptr status);',
'int I_MPI_Reduce(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,int root,I_MPI_Comm comm);',
'int I_MPI_Scan(const void* sendbuf,void* recvbuf,int count,I_MPI_Datatype datatype,I_MPI_Op op,I_MPI_Comm comm);',
'int I_MPI_Send(const void* buf,int count,I_MPI_Datatype datatype,int dest,int tag,I_MPI_Comm comm);',
'int I_MPI_Sendrecv(const void* sendbuf,int sendcount,I_MPI_Datatype sendtype,int dest,int sendtag,void* recvbuf,int recvcount,I_MPI_Datatype recvtype,int source,int recvtag,I_MPI_Comm comm,I_MPI_Status_ptr status);'];
def mmm(s):
    ret_n_fnm=s.replace('(',' ').replace(');','').split()[0:2]
    fnpl=s.replace('(',' ').replace(');','').split(',')
    fnpl[0]=fnpl[0].replace(ret_n_fnm[0]+' '+ret_n_fnm[1]+' ','');
    phrase='    return '+ret_n_fnm[1].replace('I_MPI','MPI')+'('
    nv=0
    for i in fnpl:
        v=(i.split()[-1]).replace('[]','');
        g=i.split()[0]
        if g.startswith('I_MPI'):
            g=g.replace('I_MPI','MPI');
            v='i_2_mpiobj<'+g+'>::func('+v+')';
        if nv> 0:
            phrase+=','
        if v!='void':
            phrase+=v;
        nv+=1
    phrase+=');';
    print(s.replace(';',''))
    print('{')
    print(phrase)
    print('}')

for i in range(0,fff.__len__()):
    mmm(fff[i])
 
 */
