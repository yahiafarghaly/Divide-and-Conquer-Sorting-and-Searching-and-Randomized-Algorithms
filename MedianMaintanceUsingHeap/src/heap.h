/*
 * heap.h
 *
 *  Created on: Apr 14, 2019
 *      Author: yahia
 */

#ifndef HEAP_H_
#define HEAP_H_

#include<memory>
#include<vector>
#include<algorithm>
#include <iostream>

#define EMPTY	0xDEADDEAD

class HEAP
{

protected:
	std::vector<uint32_t>* __heap;
	uint32_t __cap;
	uint32_t __heap_sz;

	/*zero Based array */
	uint32_t parent(uint32_t i) { return (i<=0 ) ? 0 : (i-1)/2;	}
	uint32_t left(uint32_t i)	{	return 2*i + 1; }
	uint32_t right(uint32_t i)	{ return 2*(i + 1); }
	void swap(uint32_t i1,uint32_t i2)	{	std::swap(__heap->at(i1),__heap->at(i2));}

public:
	explicit HEAP(uint32_t const& h_sz)
	{
		this->__cap = h_sz;
		this->__heap = new std::vector<uint32_t>(this->__cap,(uint32_t)EMPTY);
		__heap_sz = 0;
	}
	~HEAP()
	{
		delete this->__heap;
	}

	void show() {
		if(this->empty())
			return;
		for(uint32_t i = 0; i < __heap_sz; ++i)
			std::cout << __heap->at(i) << " ";
		std::cout << std::endl;
	}
	void HEAPlify(std::vector<uint32_t> arr)
	{
		for(auto v : arr)
			this->insert(v);
	}

	bool empty()
	{
		return (__heap_sz <= 0);
	}
	uint32_t size()
	{
		return this->__heap_sz;
	}
	void deleteKey(uint32_t const& key_value);


	virtual void insert(uint32_t const& key_value) = 0;
	virtual uint32_t getTop() = 0;
	virtual uint32_t extractTop() = 0;
};


void HEAP::deleteKey(uint32_t const& key_value)
{

	if(this->empty())
		return;
	auto it = std::find(__heap->begin(),__heap->end(),key_value);
	if(it != __heap->end())
	{
		/*NOT in O(log(n)) but it works in all cases.
		 * this is O(n) + O(nlog(n)) */
		std::vector<uint32_t> h_elems;
		auto keyIdx = std::distance(__heap->begin(),it);
		for(unsigned long i = 0; i < __heap_sz; ++i)
		{
			if(i != keyIdx)
				h_elems.push_back(__heap->at(i));
			__heap->at(i) = EMPTY;
		}

		__heap_sz = 0;
		for(auto e : h_elems)
			this->insert(e);
	}
}

/************************************* M I N HEAP ************************************/

class MinHeap : public HEAP
{
public:
	explicit MinHeap(uint32_t const& h_sz) : HEAP(h_sz) {}
	~MinHeap(){};

	void insert(uint32_t const& key_value);
	uint32_t getMin();
	uint32_t extractMin();
	uint32_t getTop();
	uint32_t extractTop();
};

void MinHeap::insert(uint32_t const& key_value)
{
	if(__heap_sz > this->__cap)
	{
		std::cout << "HEAP is full !\n";
		return;
	}
	(*__heap)[__heap_sz] = key_value;
	auto idx = __heap_sz;
	++__heap_sz;

	//Bubble up until heap property is restored.
	while((*__heap)[idx] < (*__heap)[parent(idx)])
	{
		this->swap(parent(idx),idx);
		idx = parent(idx);
	}
}

uint32_t MinHeap::getTop()
{
	return this->getMin();
}
uint32_t MinHeap::getMin()
{
	if(this->empty())
		return EMPTY;
	return this->__heap->at(0);
}

uint32_t MinHeap::extractTop()
{
	return this->extractMin();
}

uint32_t MinHeap::extractMin()
{
	if(this->empty())
		return EMPTY;
	auto min_key = this->getMin();
	// make last leaf be the new root.
	this->swap(__heap_sz - 1, 0);
	//delete last leaf (previously was the root)
	__heap->at(__heap_sz - 1) = EMPTY;
	__heap_sz -= 1;

	// Bubble down until heap property is restored.
	auto endIdx = __heap_sz - 1;
	unsigned long idx = 0;
	while(idx < endIdx )
	{
		auto lIdx = left(idx);
		auto rIdx = right(idx);

		if(__heap->at(lIdx) != EMPTY && __heap->at(rIdx) != EMPTY)
		{
			if(__heap->at(idx) >= __heap->at(lIdx) &&
					__heap->at(idx) >= __heap->at(rIdx))
			{
				if(__heap->at(lIdx) >= __heap->at(rIdx))
				{
					this->swap(idx,rIdx);
					idx = rIdx;
				}
				else
				{
					this->swap(idx,lIdx);
					idx = lIdx;
				}
			}
		}
		if(__heap->at(lIdx) != EMPTY && __heap->at(idx) >= __heap->at(lIdx))
		{
			this->swap(idx,lIdx);
			idx = lIdx;
		}
		else if (__heap->at(rIdx) != EMPTY && __heap->at(idx) >= __heap->at(rIdx))
		{
			this->swap(idx,rIdx);
			idx = rIdx;
		}
		else
			break;
	}

	return min_key;
}


/************************************* M A X HEAP ************************************/


class MaxHeap : public HEAP
{
public:
	explicit MaxHeap(uint32_t const& h_sz) : HEAP(h_sz) {}
	~MaxHeap(){};

	void insert(uint32_t const& key_value);
	uint32_t getMax();
	uint32_t extractMax();
	uint32_t getTop();
	uint32_t extractTop();
};

void MaxHeap::insert(uint32_t const& key_value)
{
	if(__heap_sz > this->__cap)
	{
		std::cout << "HEAP is full !\n";
		return;
	}
	(*__heap)[__heap_sz] = key_value;
	auto idx = __heap_sz;
	++__heap_sz;

	//Bubble up until heap property is restored.
	while((*__heap)[idx] > (*__heap)[parent(idx)])
	{
		this->swap(parent(idx),idx);
		idx = parent(idx);
	}
}

uint32_t MaxHeap::getTop()
{
	return this->getMax();
}
uint32_t MaxHeap::getMax()
{
	if(this->empty())
		return EMPTY;
	return this->__heap->at(0);
}

uint32_t MaxHeap::extractTop()
{
	return this->extractMax();
}

uint32_t MaxHeap::extractMax()
{
	if(this->empty())
		return EMPTY;
	auto max_key = this->getMax();
	// make last leaf be the new root.
	this->swap(__heap_sz - 1, 0);
	//delete last leaf (previously was the root)
	__heap->at(__heap_sz - 1) = EMPTY;
	__heap_sz -= 1;

	// Bubble down until heap property is restored.
	auto endIdx = __heap_sz - 1;
	unsigned long idx = 0;
	while(idx < endIdx )
	{
		auto lIdx = left(idx);
		auto rIdx = right(idx);

		if(__heap->at(lIdx) != EMPTY && __heap->at(rIdx) != EMPTY)
		{
			if(__heap->at(idx) <= __heap->at(lIdx) &&
					__heap->at(idx) <= __heap->at(rIdx))
			{
				if(__heap->at(lIdx) <= __heap->at(rIdx))
				{
					this->swap(idx,rIdx);
					idx = rIdx;
				}
				else
				{
					this->swap(idx,lIdx);
					idx = lIdx;
				}
			}
		}
		if(__heap->at(lIdx) != EMPTY && __heap->at(idx) <= __heap->at(lIdx))
		{
			this->swap(idx,lIdx);
			idx = lIdx;
		}
		else if (__heap->at(rIdx) != EMPTY && __heap->at(idx) <= __heap->at(rIdx))
		{
			this->swap(idx,rIdx);
			idx = rIdx;
		}
		else
			break;
	}

	return max_key;
}

#endif /* HEAP_H_ */
