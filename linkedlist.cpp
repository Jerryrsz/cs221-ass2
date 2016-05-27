#ifdef _LINKEDLIST_H_

#include <set>
#include <iostream>

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
	if (ll.Size() > 0) {
		int llsize = ll.Size();
		for (int i = 0; i < llsize ; i++) {
			this->InsertBack(ll.ElementAt(i));
			size += 1;
		}
	}
}

template <typename T>
void LinkedList<T>::DeleteList() {
	Node<T>* current = front;
	Node<T>* next = current->next;
	front = NULL;
	while (1) {
		delete current;
		current = next;
		if(current->next != NULL) {
			next = current->next;
		} else {
			break;
		}
	}
	size = 0;
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
		this->InsertFront(item);
		return;
	}

	// Case 2: in the back
	if(p == size) {
		this->InsertBack(item);
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
		Node<T>* n = front;
		front = front->next;
		front->prev = NULL;
		T val = n->data;
		delete n;
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
		Node<T>* current = front;
		int index = 0;
		while(index != p) {
			current = current->next;
			index++;
		}
		T val = current->data;
		current = current->prev;
		current->next = current->next->next;
		current = current->next->next;
		current->prev = current->prev->prev;
		delete current;
		size--;
		return val;
	}

	cout << "Something is wrong with RemoveAt" << endl;
	return front->data; // placeholder...should never return this;
}

template <typename T>
void LinkedList<T>::Append(const LinkedList& ll) {
	LinkedList<T>* toAppend = new LinkedList<T>();
	toAppend->CopyList(ll);
	back->next = toAppend->getFront();
	toAppend->getFront()->prev = back;
	back = toAppend->getBack();
	size += toAppend->Size();
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
			this->RemoveAt(i);
			size -= 1;
		}
		i--;
		//std::cout << curr->data << std::endl;
		curr = curr->prev;
	}
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
	Node<T>* curr = front;
	while(curr != NULL) {
		if(curr->data == item) {
			return true;
		}
		curr = curr->next;
	}	
	return false;
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
	return *this;
}

#endif
