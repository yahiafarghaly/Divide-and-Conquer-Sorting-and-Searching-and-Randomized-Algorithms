/*
 * hashtable.h
 *
 *  Created on: May 1, 2019
 *      Author: yahia
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <type_traits>
#include <vector>
#include <string>

template<typename KeyType, typename ValueType>
class Hashtable
{
private:
	unsigned long long hashtable_sz;
	std::vector<std::vector<ValueType>*> hashtable;
	unsigned long long hashfunction(KeyType const& key);

public:
	Hashtable(unsigned long long sz);
	void insert(KeyType const& key,ValueType const& value);
	void deleteKey(KeyType const& key);
	bool lookup(KeyType const& key);
	bool lookup(KeyType const& key,ValueType const& value);
	size_t recordCount(KeyType const& key);
	void showHashTable();

};

template<typename KeyType, typename ValueType>
Hashtable<KeyType,ValueType>::Hashtable(unsigned long long sz)
{
	hashtable_sz =sz;
	hashtable.resize(sz);
	for(auto vectPtr : hashtable)
		vectPtr = nullptr;
}

template<typename KeyType, typename ValueType>
void Hashtable<KeyType,ValueType>::insert(KeyType const& key,ValueType const& value)
{
	auto pos = hashfunction(key);
	if(hashtable[pos] == nullptr)
	{
		hashtable[pos] = new std::vector<ValueType>();
		hashtable[pos]->push_back(value);
	}
	else
		hashtable[pos]->push_back(value);
}



template<typename KeyType, typename ValueType>
void Hashtable<KeyType,ValueType>::deleteKey(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos] == nullptr)
		return;

	delete  hashtable[pos];
	hashtable[pos] = nullptr;
}

template<typename KeyType, typename ValueType>
bool Hashtable<KeyType,ValueType>::lookup(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos] == nullptr)
		return false;
	else
		return true;
}


template<typename KeyType, typename ValueType>
bool Hashtable<KeyType,ValueType>::lookup(KeyType const& key,ValueType const& value)
{
	auto pos = hashfunction(key);
	if(hashtable[pos] == nullptr)
		return false;
	else
	{
		for(int i = 0; i < hashtable[pos]->size(); i++)
		{
			if(hashtable[pos]->at(i) == value)
				return true;
		}
		return false; // ? Weird at this point.
	}
}

template<typename KeyType, typename ValueType>
unsigned long long Hashtable<KeyType,ValueType>::hashfunction(KeyType const& key)
{
	if(std::is_same<KeyType,std::string>::value)
	{
		// Do some actions to convert string to integer.
	}

	auto keyValue = key;
	unsigned long long pos;

	if(keyValue < 0 )
		pos = (keyValue*2*-1) % hashtable_sz;
	else
		pos = key % hashtable_sz;

	return pos;
}


template<typename KeyType, typename ValueType>
size_t Hashtable<KeyType,ValueType>::recordCount(KeyType const& key)
{
	auto pos = hashfunction(key);
	if(hashtable[pos] == nullptr)
		return 0;

	return hashtable[pos]->size();
}

template<typename KeyType, typename ValueType>
void Hashtable<KeyType,ValueType>::showHashTable()
{
	std::cout << "keyHashed : records \n";
	unsigned long long pos = 0;
	for(auto vect : hashtable)
	{
		std::cout << "["<< pos << "]: ";
		if(vect != nullptr)
		{	for(size_t i = 0; i < vect->size();i++)
			{
				std::cout << vect->at(i) << " ";
			}
		}
		std::cout << "\n";
		pos++;
	}
}

#endif /* HASHTABLE_H_ */
