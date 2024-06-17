#pragma once
#include "GroupContainer.h"

class AbstractSet : public GroupContainer {
public:
    AbstractSet(MemoryManager& mem) : GroupContainer(mem) {}
    virtual ~AbstractSet() {}
    virtual int insert(void* elem, size_t size) = 0;
};