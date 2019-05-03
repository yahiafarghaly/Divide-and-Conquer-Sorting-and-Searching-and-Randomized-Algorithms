//============================================================================
// Name        : Heap.cpp
// Author      : YF
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

//#include "heap2.h"
#include "heap.h"
using namespace std;

int main() {


	std::vector<uint32_t> vect = {
			3611, 2022, 2123, 1369, 1640, 3480, 2303, 1260, 1286, 1354, 1386, 1446, 2793, 961, 2261, 225, 625, 1274
	};
	MaxHeap h(100);
	h.HEAPlify(vect);
	h.show();
	h.extractTop();
	h.show();


	h.extractTop();
	h.show();


	return 0;
}
