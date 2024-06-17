#pragma once
#include "Set.h"

using namespace std;

class Test {
private:
    Mem* mem;
    Set st;
    double total_time;
    int elems_cnt;
public:
    Test(size_t memory_size = 1e9);
    ~Test();
    int testInsert(int n);
    int testIterate();
    int testRemove();
    int testFind();
    double getTime();
};