#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SortedMap.h"
#include "SMIterator.h"
#include <crtdbg.h>
#include <iostream>
#include <assert.h>
using namespace std;


void testAddIfNotPresent()
{
	cout << "Test add if not present" << endl;
	SortedMap sm1(increasing), sm2(increasing);
	for (int i = 1; i <= 50; i++)
	{
		sm1.add(i, i);
		sm2.add(i, i);
	}
	for (int i = 51; i <= 100; i++)
	{
		sm2.add(i, i);
	}
	sm1.addIfNotPresent(sm2);
	SMIterator it = sm1.iterator();
	int i = 1;
	while (it.valid())
	{
		assert(it.getCurrent().first == i);
		assert(it.getCurrent().second == i);
		i++;
		it.next();
	}
}


int main() {
	testAll();
	testAllExtended();
	testAddIfNotPresent();

	cout << "That's all!" << endl;
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}


