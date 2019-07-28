#ifndef __pn_h__
#define __pn_h__
#include <cstddef>

///create an object of type T at a given address
template<typename T>
void placement_new(void *buffer, std::size_t buffer_size) {
    new(buffer) T();
}

///cast a given address to a pointer to type T
template<typename T>
T* placement_cast(void *buffer) {
    return reinterpret_cast<T*>(buffer);
}

///call the destructor of type T at a given address
template<typename T>
void placement_delete(void *buffer) {
    placement_cast<T>(buffer)->~T();
}

#endif
