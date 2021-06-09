//Following is a heavily edited version of ListSLT.h

#pragma once // #pragma once is a non-standard but widely supported preprocessor directive designed to cause the current source file to be included only once in a single compilation.

#include <iostream>
#include <fstream>
#include <string>
//#include <stdlib.h>//allows use of exit() and abort() but might not actually be needed



template<class T>
struct Node {
	T data[8]; //int ARRAY_SIZE = 8; c++ does not like having the struct array taking a variable, so this unfourtunately, seemingly, has to be hardcoded
	int size = 0; //keeps track of how many values are in each chunk's array
	Node *next;
};

template<class T>
class ChonkList
{
public:
	ChonkList(); //default constructor
	~ChonkList(); //default deconstructor

	void Append(T elem);  

	//void Prepend(T elem); // Adds stuff to front and is extra for this assignment

	int GetLength();
	T* GetIndex(int i);

	T* Search(T elem);
	
	void Print();
	//void ReversePrint();//Extra

	//bool InsertAfter(T before, T after); //Extra
	void Remove(T elem);

	bool IsEmpty();


private:
	Node<T>* head;
	Node<T>* tail;
	int len;//total amount of elements in all the nodes
	int nodeLen;//total amount of nodes
	int ARRAY_SIZE = 8; //the struct would not take ARRAY_SIZE, yet this value is still needed later, so here it is 
};


//default constructor, easy peasy, did not need changing
template<class T>
ChonkList<T>::ChonkList()
{
	head = nullptr;
	tail = nullptr;
	len = 0;
}

//default desconstructor, easy peasily, also didn't need changing and is not even required/used anyways
template<class T>
ChonkList<T>::~ChonkList()
{
	while (head != nullptr) {
		Node<T>* tmp = head;
		head = head->next;
		delete tmp;
	}
}

//checks if list is empty, if not empty, go to tail and figure out if full, if not add value, if yes, new tail with new value 
//for some reason, the second index is always a zero, and the intended second index value becomes the third index when a third append is called
template<class T>
void ChonkList<T>::Append(T elem)
{
	len++;
	Node<T> *current = tail; //this is probably how one gets to nodes in a linked list
	bool nodeFull = false;
	// If list is empty...
	if (IsEmpty()) {
		// Set up the new node...
		Node<T>*newNode = new Node<T>;
		newNode->data[0] = elem;
		newNode->size = 1;
		newNode->next = nullptr;
		nodeLen++;
		tail = head = newNode;
	}
	
	else {
		//moves current node to the tail node
		current = tail;
		//if current node is full, makes a new node, appends, and sets new node as the tail
		if (current->size == ARRAY_SIZE) {
				Node<T>*newNode = new Node<T>;
				newNode->data[0] = elem;
				newNode->size = 1;
				newNode->next = nullptr;
				tail->next = newNode;
				tail = newNode;
				nodeLen++;
				//abort();
		}
		//otherwise, if current node is not full, appends the value in first empty spot of array
		else {
			current->data[current->size + 1] = elem;
			current->size++;
			//for (int i = 0; i < ARRAY_SIZE; i++) {
				//if (i == current->size + 1 /*|| i == NULL (sadly, this does not work*/) {
					//current->data[i] = elem;
					//current->size++;
				//}
			}
		}
	}

//did not need any changing, just returns the total number of elements in the list
template<class T>
int ChonkList<T>::GetLength()
{
	return len;
}

//rather simple, goes through each node's array then returns the value within the index if found
template<class T>
T* ChonkList<T>::GetIndex(int i)
{
	int counter = -1;
	Node<T>* curr = head;
	for (int j = 0; j < nodeLen; j++) {
		for (int h =0; h < curr->size; h++) {
			counter++;
			if (counter == i)
				return new T(curr->data[h]);
		}
		curr = curr->next;
	}

	return nullptr;
}

//very similiar to above, except a specific element is being searched for and copied, rather than finding an index then copying what is inside the index
template<class T>
T * ChonkList<T>::Search(T elem)
{
	Node<T> *currNode = head;

	for (int i = 0; i < nodeLen; i++) {
		for (int j = 0; j < currNode->size; j++) {
			if (currNode->data[j] == elem) {
				return new T(currNode->data[j]);
			}
		}
		currNode = currNode->next;
	}

	return nullptr;
}

//simply goes through whole linked list and prints what is inside each index
//however, for some reason, there seems to be a ~50% chance of an infinite loop with the same input
template<class T>
void ChonkList<T>::Print()
{
	Node<T> *currNode = head;

	for (int i = 0; i < nodeLen; i++) {
		for (int j = 0; j < currNode->size; j++) {
			std::cout << currNode->data[j] << "\n";
		}
		if (currNode->next == nullptr)
			continue;
		currNode = currNode->next;
		int nodeSize = currNode->size;
	}
}

//searches through each node to find the desired element, if found, will delete. Then, if node becomes empty, list is updated as need be followed by the node deletion
//this might actually be doing nothing
template<class T>
void ChonkList<T>::Remove(T elem)
{
	Node<T> *prev = nullptr;
	Node<T> *currNode = head;
	
	//loop runs until the desired element is found
	for (int i = 0; i < nodeLen; i++) {
		for (int j = 0; j < currNode->size; j++) {
			// found the element in the list
			if (currNode->data[j] == elem) {
				if (len == 1) {		// only one total element...
					head = tail = nullptr;
				}
				//replaces the current value in the array's index
				else {
					//this is trying to figure out if node is not full, then moving every value after the chosen element up 1
					if (j != currNode->size) {
						for (int h = j; h < currNode->size - j; h++) {
							currNode->data[h] = currNode->data[h + 1];
						}
					}
					else {
						currNode->size--;
					}
				}
				//then, if the current node is empty, the list is changed as needed then the node is deleted
				if (currNode->size == 0) {
					if (currNode == head) {	// Adjust the head
						head = currNode->next;
					}
					else if (currNode == tail) {	// Adjust the tail
						tail = prev;
						tail->next = nullptr;
					}
					else {							// General case
						prev->next = currNode->next;
					}
					delete currNode;
					nodeLen--;

				}
				len--;
				return;
			}
		}
		prev = currNode;			// Move the node pointers forward
		currNode = currNode->next;
	}

}

//required no modification, is ez pz
template<class T>
bool ChonkList<T>::IsEmpty()
{
	return head == nullptr;
}

