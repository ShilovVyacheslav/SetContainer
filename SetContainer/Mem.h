#pragma once
#include "MemoryManager.h"

using namespace std;

class Mem : public MemoryManager {
private:
    size_t _size, cur_free;
    char* memory_pool;
public:
    Mem(size_t sz);
    ~Mem();
    size_t maxBytes() override;
    void* allocMem(size_t sz) override;
    void freeMem(void* ptr) override;
};

void* operator new(size_t sz, MemoryManager& mem);
void operator delete(void* ptr, MemoryManager& mem);