#ifdef _LINKEDLIST_H_
#include "linkedlist.h"

// Constructors and Destructor
template <typename T>
LinkedList<T>::LinkedList() {
	size = 0;
	front = NULL;
	back = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& ll) {
	CopyList(ll);
}

template <typename T>
LinkedList<T>::~LinkedList() {
	DeleteList();
}

// Private
template <typename T>
void LinkedList<T>::CopyList(const LinkedList& ll) {
	//TO-DO
	return;
}

template <typename T>
void LinkedList<T>::DeleteList() {
	Node<T>* current = front;
	while (current != NULL) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	front = NULL;
}

// Mutators
template <typename T>
void LinkedList<T>::InsertFront(T item) {
	Node<T>* n = new Node<T>(item);
	front->prev = n;
	n->next = front;
	size += 1;
}

template <typename T>
void LinkedList<T>::InsertBack(T item) {
	Node<T>* n = new Node<T>(item);
	n->prev = back;
	back->next = n;
	size += 1;
}

template <typename T>
void LinkedList<T>::InsertAt(T item, int p) {
	Node<T>* n = new Node<T>(item);
	Node<T>* current = front;
	int index = 0;

	// TODO throw index bound exception here

	while (current != NULL) {
		if (index == p) break;
		current = current->next;
	}

	Node<T>* parent = current->prev;
	if (parent != NULL) {
		parent->next = n;
		n->prev = parent;
	}
	n->next = current;
	current->prev = n;
	size += 1;
}

template <typename T>
T LinkedList<T>::RemoveAt(int p) {
	Node<T>* current = front;
	int index = 0;

	// TODO throw index bound exception here

	while (current != NULL) {
		if (index == p) break;
		current = current->next;
	}

	Node<T>* parent = current->prev;
	Node<T>* nextNode = current->next;
	if (parent != NULL) {
		parent->next = nextNode;
	}
	if (nextNode != NULL) {
		nextNode->prev = parent;
	}
	T val = current->data;
	delete current;
	size -= 1;
	return val;
}

template <typename T>
void LinkedList<T>::Append(const LinkedList& ll) {
	LinkedList<T>* toAppend = new LinkedList<T>();
	toAppend->CopyList(ll);
	//TODO finish

}

template <typename T>
void LinkedList<T>::RemoveDuplicates() {
	return;
}

// Accessors

template <typename T>
int LinkedList<T>::Size() const {
	return size;
}

template <typename T>
bool LinkedList<T>::IsEmpty() const {
	return size == 0 ? true: false; // can be !size 
}

template <typename T>
bool  LinkedList<T>::Contains(T item) const {
	return false;
}

template <typename T>
T LinkedList<T>::ElementAt(int p) const {
	return front->data;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll) {
	return *this;
}

#endif
