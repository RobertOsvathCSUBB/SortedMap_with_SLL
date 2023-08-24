#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) : rel(r)
{
	this->head = nullptr;
	this->len = 0;
}

// Best case: the map is empty -> theta(1)
// Worst case: the key of the element already exists in the map and 
//				is at the end -> O(length ^ 2)
// Average case: if we assume that the probability of the key already
//				existing in the map are the same as the probability
//				of not existing in the map, it is still 
// ->O(length) + O(length ^3) = O(length ^ 3)
TValue SortedMap::add(TKey k, TValue v)
{
	Node* newNode = new Node{ TElem(k, v) };

	TValue searchResult = this->search(k);
	if (searchResult != NULL_TVALUE)
		this->remove(k);

	Node* currentNode = this->head;
	Node* previousNode = nullptr;

	while (currentNode != nullptr && this->rel(currentNode->elem.first, k))
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	newNode->next = currentNode;
	if (previousNode == nullptr)
		this->head = newNode;
	else
		previousNode->next = newNode;

	this->len++;

	return searchResult;
}

// Best case: the key is from the first element, or the map is empty 
//				-> theta(1)
// Worst case: the key is from the last element -> theta(length)
// Average case: O(length)
TValue SortedMap::search(TKey k) const 
{
	if (this->head == nullptr)
		return NULL_TVALUE;
	
	Node* currentNode = this->head;
	while (currentNode != nullptr)
	{
		if (currentNode->elem.first == k)
			return currentNode->elem.second;
		currentNode = currentNode->next;
	}
	return NULL_TVALUE;
}

// Best case: the key is from the first element, or the map is empty 
//				-> theta(1)
// Worst case: the key is from the last element -> O(length)
// Average case: O(length)
TValue SortedMap::remove(TKey k) 
{
	if (this->head == nullptr)
		return NULL_TVALUE;

	TValue returnVal;
	if (this->head->elem.first == k)
	{
		returnVal = this->head->elem.second;
		Node* aux = this->head;
		this->head = this->head->next;
		delete aux;
		this->len--;
		return returnVal;
	}
	
	Node* currentNode = this->head;
	Node* previousNode = nullptr;
	while (currentNode != nullptr && currentNode->elem.first != k)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	if (currentNode == nullptr)
		return NULL_TVALUE;

	returnVal = currentNode->elem.second;
	Node* aux = currentNode;
	previousNode->next = currentNode->next;
	currentNode = previousNode;
	delete aux;
	this->len--;
	return returnVal;
}

// Theta(1)
int SortedMap::size() const
{
	return this->len;
}

// Theta(1)
bool SortedMap::isEmpty() const
{
	return this->head == nullptr;
}

SMIterator SortedMap::iterator() const  
{
	return SMIterator(*this);
}

// Best case: the sorted map is empty, there is nothing to iterate over
//				-> theta(1)
// Worst case: every element of the sorted map is present in current 
//				object, so every search will be of theta(len)
//				-> theta(len of the current object * len of sm)
// Average case: since we have no additional information of the
//				probabilites of the elements of the sm being present 
//				in the current object
//				-> O(len of the current object * len of sm)
int SortedMap::addIfNotPresent(SortedMap& sm)
{
	SMIterator it(sm);
	TValue searchResult;
	TElem currentElem;
	int count = 0;
	while (it.valid())
	{
		currentElem = it.getCurrent();
		searchResult = this->search(currentElem.first);
		if (searchResult != NULL_TVALUE)
		{
			this->add(currentElem.first, currentElem.second);
			count++;
		}
		it.next();
	}
	return count;
}

SortedMap::~SortedMap() {
	Node* aux;
	while (this->head != nullptr)
	{
		aux = this->head;
		this->head = this->head->next;
		delete aux;
	}
}
