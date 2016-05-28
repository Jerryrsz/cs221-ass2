#ifdef _LINKEDLIST_H_

#include <set>
#include <iostream>
using namespace std;

// Constructors and Destructor
template <typename T>
LinkedList<T>::LinkedList() {
	cout << "List is being created..." << endl;
	size = 0;
	front = NULL;
	back = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& ll) {
	cout << "List is being created with deep copy of parameter list..." << endl;
	size = 0;
	front = NULL;
	back = NULL;
	CopyList(ll);
}

template <typename T>
LinkedList<T>::~LinkedList() {
	cout << "List is being destroyed..." << endl;
	DeleteList();
}

// Private
template <typename T>
void LinkedList<T>::CopyList(const LinkedList& ll) {
	if (ll.Size() > 0) {
		for (int i = 0; i < ll.Size() ; i++) {
			InsertBack(ll.ElementAt(i));
		}
	} else {
		cout << "Nothing to copy for CopyList" << endl;
	}
}

template <typename T>
void LinkedList<T>::DeleteList() {

	while(size != 0) {
		RemoveAt(size-1);
	}
	front = NULL;
	back = NULL;
}

// Mutators
template <typename T>
void LinkedList<T>::InsertFront(T item) {
	Node<T>* n = new Node<T>(item);
	if(size == 0) {
		front = n;
		back = n;
		size++;
	} else {
		front->prev = n;
		n->next = front;
		front = n;
		size++;
	}
}

template <typename T>
void LinkedList<T>::InsertBack(T item) {
	Node<T>* n = new Node<T>(item);
	if(size == 0) {
		front = n;
		back = n;
		size++;
	} else {
		n->prev = back;
		back->next = n;
		back = n;
		size++;
	}
}

template <typename T>
void LinkedList<T>::InsertAt(T item, int p) {

	// invalid index p
	if(p < 0 || p > size) {
		throw std::out_of_range("InvalidIndexException");
	}

	// Case 1: in the front
	if(p == 0) {
		InsertFront(item);
		return;
	}

	// Case 2: in the back
	if(p == size) {
		InsertBack(item);
		return;
	}

	// Case 3: somewhere in between
	if(p > 0 && p < size) {
		Node<T>* n = new Node<T>(item);
		Node<T>* current = front;
		int index = 0;
		while (index != p) {
			current = current->next;
			index++;
		}
		n->prev = current->prev;
		n->next = current;
		current->prev = n;
		current = n->prev;
		current->next = n;
		size++;
		return;
	}
	
	cout << "Something is wrong with InsertAt" << endl;
}

template <typename T>
T LinkedList<T>::RemoveAt(int p) {

	// invalid index or empty list
	if(p < 0 || p >= size) {
		throw std::out_of_range("InvalidIndexException");
	} else if (size == 0) {
		throw std::length_error("ListEmptyException");
	}

	// Case 1: in the front
	if(p == 0) {
		Node<T>* m = front;
		front = front->next;
		front->prev = NULL;
		T val = m->data;
		delete m;
		size--;
		return val;
	}

	// Case 2: in the back
	if(p == size-1) {
		Node<T>* n = back;
		back = back->prev;
		back->next = NULL;
		T val = n->data;
		delete n;
		size--;
		return val;
	}

	// Case 3: somewhere in between
	if(p > 0 && p < size-1) {
		Node<T>* o = front;
		int index = 0;
		while(index != p) {
			o = o->next;
			index++;
		}
		Node<T>* prev = o->prev;
		Node<T>* next = o->next;
		prev->next = next;
		next->prev = prev;
		T val = o->data;
		delete o;
		size--;
		return val;
	}

	cout << "Something is wrong with RemoveAt" << endl;
	return front->data; // placeholder...should never return this;
}

template <typename T>
void LinkedList<T>::Append(const LinkedList& ll) {
	CopyList(ll);
}

template <typename T>
void LinkedList<T>::RemoveDuplicates() {

	std::set<T> check;
	Node<T>* curr = back;
	int i = size - 1;
	while (curr != NULL && i >= 0) {
		int search = check.count(curr->data);
		if (search == 0) {
			check.insert(curr->data);
		} else {
			RemoveAt(i);
		}
		i--;
		curr = curr->prev;
	}
}

// Accessors

template <typename T>
int LinkedList<T>::Size() const {
	return size;
}

template <typename T>
bool LinkedList<T>::IsEmpty() const {
	return this->size == 0 ? true: false; // can be !size 
}

template <typename T>
bool  LinkedList<T>::Contains(T item) const {
	Node<T>* curr = front;
	int i = 0;
	while(1) {
		if(curr->data == item) {
			return true;
		}
		i++;
		if(i == Size()) {
			return false;
		}
		curr = curr->next;
	}
}

template <typename T>
T LinkedList<T>::ElementAt(int p) const {
	
	if(p < 0 || p >= size) {
		throw std::out_of_range("InvalidIndexException");
	} else {
		Node<T>* curr = front;
		int i = 0;
		while(i != p) {
			curr = curr->next;
			i++;
		}
		return curr->data;
	}
	return front->data; // placeholder...should never return this
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll) {
	CopyList(ll);
	return *this;
}

#endif
