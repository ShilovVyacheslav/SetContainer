#pragma once
#include "ListAbstract.h"
#include "Mem.h"

using namespace std;

class Node {
private:
    void* data;
    size_t data_size;
    Node* next;
public:
    Node(void* elem, size_t elemSize);
    ~Node();
    friend class List;
};

class List : public AbstractList {
private:
    Node* head;
    int list_size;
public:
    List(MemoryManager& _memory);
    ~List();
    class ListIterator : public Iterator {
    private:
        Node* current;
    public:
        ListIterator(Node* ptr);
        ~ListIterator();
        void* getElement(size_t& size) override;
        bool hasNext() override;
        void goToNext() override;
        bool equals(Iterator* right) override;
        friend class List;
    };
    int insert(Iterator* iter, void* elem, size_t elemSize) override;
    int push_front(void* elem, size_t elemSize) override;
    void pop_front() override;
    void* front(size_t& size) override;
    int size() override;
    size_t max_bytes() override;
    Iterator* find(void* elem, size_t size) override;
    Iterator* newIterator() override;
    void remove(Iterator* iter) override;
    void clear() override;
    bool empty() override;
    friend ostream& operator<<(ostream& out, List& lst);
    friend class Table;
    friend class Set;
};