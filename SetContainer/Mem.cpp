#include "Mem.h"

Mem::Mem(size_t sz) : MemoryManager(sz), _size(sz), cur_free(0) {
    memory_pool = ::new char[_size];
}

Mem::~Mem() {
    ::delete[] memory_pool;
}

size_t Mem::maxBytes() {
    return _size - cur_free;
}

void* Mem::allocMem(size_t sz) {
    if (cur_free + sz <= _size) {
        void* ptr = memory_pool + cur_free;
        cur_free += sz;
        return ptr;
    }
    return nullptr;
}

void Mem::freeMem(void* ptr) {
    if (ptr != nullptr) {
        return;
    }
}

void* operator new(size_t sz, MemoryManager& mem) {
    return mem.allocMem(sz);
}
void operator delete(void* ptr, MemoryManager& mem) {
    mem.freeMem(ptr);
}
