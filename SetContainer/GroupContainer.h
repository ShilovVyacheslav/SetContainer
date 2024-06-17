#pragma once
#include "Container.h"
#include "List.h"

class GroupContainer : public Container {
protected:
	List** table;
	int table_size;
public:
    GroupContainer(MemoryManager& _memory) : Container(_memory), table(nullptr), table_size(17) {
        table = new(_memory) List * [table_size];
        if (table != nullptr) {
            for (size_t i = 0; i < table_size; ++i) {
                table[i] = new(_memory) List(_memory);
            }
        }
    }
    ~GroupContainer() {
        clear();
    }
    virtual int size() {
        int size = 0;
        if (table != nullptr) {
            for (int i = 0; i < table_size; ++i) {
                if (table[i] != nullptr) {
                    size += table[i]->size();
                }
            }
        }
        return size;
    }
    virtual size_t max_bytes() {
        return _memory.maxBytes();
    }
    virtual bool empty() {
        return size() == 0;
    }
    virtual void clear() {
        if (table != nullptr) {
            for (int i = 0; i < table_size; ++i) {
                if (table[i] != nullptr) {
                    table[i]->clear();
                    operator delete(table[i], _memory);
                    table[i] = nullptr;
                }
            }
            operator delete(table, _memory);
            table = nullptr;
        }
    }
};