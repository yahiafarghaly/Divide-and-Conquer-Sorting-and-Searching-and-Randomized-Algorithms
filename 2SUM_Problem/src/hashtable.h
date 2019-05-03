/*
 * hashtable.h
 *
 *  Created on: May 1, 2019
 *      Author: yahia
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <type_traits>
#include <list>
#include <iostream>
#include <string>

template<typename KeyType>
class Hashtable
{
private:
	unsigned long long hashtable_sz;
	std::list<KeyType> * hashtable;
	unsigned long long hashfunction(KeyType const& key);

public:
	Hashtable(unsigned long long sz);
	~Hashtable();
	void insert(KeyType const& key);
	void deleteKey(KeyType const& key);
	bool lookup(KeyType const& key);
	size_t recordCount(KeyType const& key);
	size_t size() const
	{
		return hashtable_sz;
	}
	void showHashTable();

};

template<typename KeyType>
Hashtable<KeyType>::Hashtable(unsigned long long sz)
{
	hashtable_sz =sz;
	hashtable = new std::list<KeyType>[hashtable_sz];
}

template<typename KeyType>
Hashtable<KeyType>::~Hashtable()
{
	delete [] hashtable;
}

template<typename KeyType>
void Hashtable<KeyType>::insert(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos].empty())
	{
		(hashtable[pos]).push_back(key);
	}
	else
		(hashtable[pos]).push_back(key);
}



template<typename KeyType>
void Hashtable<KeyType>::deleteKey(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos].empty())
		return;

	for (auto it = hashtable[pos].begin();
			it != hashtable[pos].end(); it++) {
		if (*it == key)
		{
			hashtable[pos].erase(it);
			break;
		}
	}
}



template<typename KeyType>
bool Hashtable<KeyType>::lookup(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos].empty())
		return false;
	else
	{
		for (auto it = hashtable[pos].begin();
				it != hashtable[pos].end(); it++) {
			if (*it == key)
			{
				return true;
			}
		}
		return false; // ? Weird at this point.
	}
}

template<typename KeyType>
unsigned long long Hashtable<KeyType>::hashfunction(KeyType const& key)
{
	return key % hashtable_sz;
}


template<typename KeyType>
size_t Hashtable<KeyType>::recordCount(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos].empty())
		return 0;

	return hashtable[pos].size();
}

template<typename KeyType>
void Hashtable<KeyType>::showHashTable()
{
	for (int i = 0; i < hashtable_sz; i++) {
		std::cout << i;
		for (auto x : hashtable[i])
			std::cout << " --> " << x;
		std::cout << std::endl;
	}
}

#endif /* HASHTABLE_H_ */
