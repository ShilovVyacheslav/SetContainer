#pragma once
#include "SetAbstract.h"

using namespace std;

const size_t MOD = static_cast<size_t>(1e9 + 9);

class Set : public AbstractSet {
public:
    Set(MemoryManager& _memory) : AbstractSet(_memory) {}
    virtual ~Set() {}
    class SetIterator : public Iterator {
    private:
        const Set& set_ref;
        Iterator* it;
        int index;
    public:
        SetIterator(const Set& set_ref, int _index = 0, bool first_existing = true);
        ~SetIterator();
        void* getElement(size_t& size) override;
        bool hasNext() override;
        void goToNext() override;
        bool equals(Iterator* right) override;
        List* getList();
        void clear();
        friend class Set;
        friend class Test;
    };
    Iterator* findByKey(void* key, size_t keySize);
    int insert(void* elem, size_t size) override;
    Iterator* find(void* elem, size_t size) override;
    Iterator* newIterator() override;
    void remove(Iterator* iter) override;
    void rehash();
    friend ostream& operator<<(ostream& out, Set& st);
};