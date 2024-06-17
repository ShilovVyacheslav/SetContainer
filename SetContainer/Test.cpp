#include "Test.h"

Test::Test(size_t memory_size) : mem(::new Mem(memory_size)), st(*mem), total_time(0), elems_cnt(0) {}
Test::~Test() {
    st.clear();
    ::delete mem;
}
int Test::testInsert(int n) {
    const size_t elemSize = sizeof(int);
    elems_cnt = n;
    clock_t start;

    for (int i = 0; i < n; ++i) {
        start = clock();
        st.insert(&i, elemSize);
        total_time += double(clock() - start) / CLOCKS_PER_SEC;
    }

    for (int i = 0; i < n; ++i) {
        start = clock();
        if (dynamic_cast<Set::SetIterator*>(st.find(&i, elemSize))->it == nullptr) {
            return 1;
        }
        total_time += double(clock() - start) / CLOCKS_PER_SEC;
    }

    return 0;
}

int Test::testIterate() {
    clock_t start = clock();

    Set::SetIterator* it = dynamic_cast<Set::SetIterator*>(st.newIterator());
    if (it == nullptr) { return 1; }
    size_t data_size; void* data;
    while (it->it) {
        it->goToNext();
    }
    it->clear(); it = nullptr;

    total_time += double(clock() - start) / CLOCKS_PER_SEC;
}

int Test::testRemove() {
    clock_t start = clock();

    Set::SetIterator* it = dynamic_cast<Set::SetIterator*>(st.newIterator());
    if (it == nullptr) { return 1; }
    size_t data_size; void* data;
    while (it->it) {
        if (*(static_cast<int*>(it->getElement(data_size))) % 2) {
            st.remove(it);
        }
        it->goToNext();
    }
    it->clear(); it = nullptr;

    total_time += double(clock() - start) / CLOCKS_PER_SEC;

    return 0;
}

int Test::testFind() {
    const size_t elemSize = sizeof(int);
    clock_t start;

    for (int i = 0; i < elems_cnt; ++i) {
        clock_t start = clock();
        if ((i % 2) != (dynamic_cast<Set::SetIterator*>(st.find(&i, elemSize))->it == nullptr)) {
            return 1;
        }
        total_time += double(clock() - start) / CLOCKS_PER_SEC;
    }

    return 0;
}

double Test::getTime() {
    return total_time;
}