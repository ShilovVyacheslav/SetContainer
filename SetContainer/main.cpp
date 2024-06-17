#include <iostream>
#include <ctime>
#include "Test.h"

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

int main() {
	Test test;

	test.testInsert(1e6);
	test.testIterate();
	test.testRemove();
	test.testIterate();
	if (test.testFind() == 0) {
		cout << "All tests are passed!" << endl;
	}

	printf("Time: %.7lf\n", test.getTime());

	//_CrtDumpMemoryLeaks();
	
	return 0;
}