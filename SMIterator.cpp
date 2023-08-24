#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m)
{
	this->first();
}

void SMIterator::first() 
{
	this->current = this->map.head;
}

void SMIterator::next()
{
	if (this->valid())
		this->current = this->current->next;
	else
		throw exception();
}

bool SMIterator::valid() const 
{
	return this->current != nullptr;
}

TElem SMIterator::getCurrent() const 
{
	if (this->valid())
		return this->current->elem;
	else
		throw exception();
}


