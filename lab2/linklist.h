#pragma once
#include <iostream>

template <class T>
class LinkedList {
private:
	template <class N>
	class Node {
	public:
		N field;
		class Node<N>* next;
	};
protected:
	Node<T>* head;
	int size{};
public:
	LinkedList() {
		head = NULL;
		size = 0;
	}

	LinkedList(T* items, int count) {
		size = count;
		if (!count) {
			head = NULL;
			return;
		}
		head = new Node<T>;
		
		head->field = items[0];
		Node<T>* previous = head;
		for (int i = 1; i < count; i++) {
			Node<T>* ptr = new Node<T>;
			ptr->field = items[i];
			previous->next = ptr;
			previous = ptr;
		}
		previous->next = NULL;
	}
	
	LinkedList<T>(const LinkedList<T>& list) {   
		size = list.size;
		if (size) {
			head = new Node<T>;
			Node<T>* listptr = list.head;
			head->field = listptr->field;
			Node<T>* previous = head;
			for (int i = 1; i < list.size; i++) {
				listptr = listptr->next;
				Node<T>* ptr{};
				ptr = new Node<T>;
				ptr->field = listptr->field;
				previous->next = ptr;
				previous = ptr;
			}
			previous->next = NULL;
		} else {
		head = NULL;
		}
	}
	
	~LinkedList() {
		Node<T>* ptr1 = head;
		Node<T>* ptr2 = NULL;
		for (int i = 0; i < size; i++) {
			ptr2 = ptr1->next;
			delete ptr1;
			ptr1 = ptr2;
		}
	}

	T GetFirst() const {
		if (!size) {
			throw std::out_of_range("List is empty.");
		}
		return head->field;
	}
	
	T GetLast() const
	{
		if (!size) {
			throw std::out_of_range("List is empty.");
		}
		Node<T>* ptr{head};
		for (int i = 0; i < size-1; i++) {
			ptr = ptr->next;
		}
		return ptr->field;
	}
	
	T GetElement(int index) const {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		Node<T>* ptr{head};
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr->field;
	}
	
	LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
		if (startIndex < 0 || startIndex >= size || endIndex < 0 || endIndex >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		if (startIndex > endIndex) {
			throw std::invalid_argument("The start index must be less than the end index");
		}
		
		Node<T>* ptr{head};
		int subsize = endIndex - startIndex + 1;
		int elements[subsize];
		
		for (int i = 0; i < startIndex; i++)
			ptr = ptr->next;
		
		for (int i = startIndex; i < endIndex; i++) {
			elements[i - startIndex] = ptr->field;
			ptr = ptr->next;
		}
		elements[endIndex-startIndex] = ptr->field;
		LinkedList<T>* sublist = new LinkedList<T>(elements, subsize);
		return sublist;
	}
	
	int GetLength() const {			
		return size;
	}
	
	void Append(T item) {
		if (size) {
			Node<T>* ptr{head};
			for (int i = 0; i < size-1; i++) {
				ptr = ptr->next;
			}
			Node<T>* last = new Node<T>;
		
			ptr->next = last;
			last->field = item;
		} else {
			head = new Node<T>;
			head->field = item;
		}
		size++;
	}
	
	void Prepend(T item) {
		Node<T>* elem{};
		elem = new Node<T>;
		elem->field = item;
		elem->next = head;
		head = elem;
		size++;
	}
	
	void InsertAt(T item, int index)
	{
		if (index < 0 || index > size) {
			throw std::out_of_range("Index is out of range.");
			return;
		}
		if (!size || !index) {
			Prepend(item);
			return;
		}
		Node<T>* elem{};
		elem = new Node<T>;
		
		Node<T>* ptr{head};
		for (int i = 0; i < index-1; i++) {
			ptr = ptr->next;
		}
		Node<T>* ptr2{ptr->next};
		ptr->next = elem;
		elem->field = item;
		elem->next = ptr2;
		size++;
	}
	
	void Concat(LinkedList<T> list) {
		Node<T>* ptr = list.head;
		for (int i = 0; i < list.size; i++) {
			this->Append(ptr->field);
			ptr = ptr->next;
		}
		
	}
	
	bool operator ==(const LinkedList<T>& other) const {
		if (size != other.size) {
			return false;
		}
		Node<T>* ptr1 = head;
		Node<T>* ptr2 = other.head;
		while (ptr1->next) {
			if (ptr1->field != ptr2->field) {
				return false;
			}
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		return true;
	}

	LinkedList<T>& operator =(const LinkedList<T>& list) {
		if (*this == list) {
			return *this;
		}
		this->~LinkedList();
		size = list.size;
		if (size) {
			head = new Node<T>;
			Node<T>* listptr = list.head;
			head->field = listptr->field;
			Node<T>* previous = head;
			for (int i = 1; i < list.size; i++) {
				listptr = listptr->next;
				Node<T>* ptr{};
				ptr = new Node<T>;
				ptr->field = listptr->field;
				previous->next = ptr;
				previous = ptr;
			}
		} else {
		head = NULL;
		}
		return *this;
	}

	class Iterator {
		friend LinkedList;
	private:
		Node<T>* cur{};
		LinkedList<T>* self{};
		int index{};
	public:
		Iterator() { }
		Iterator(LinkedList<T>* data) : self(data), index(0) {
			if (self->size == 0) {
				throw std::invalid_argument("Cannot count empty data.");
			}
			cur = self->head;
		}
		Iterator(Iterator& other)
				: cur(other.cur), index(other.index), self(other.self){}

		int CurIndex() {
			return index;
		}

		T* Begin() {
			cur = self->head;
			index = 0;
			return &(cur->field);
		}

		T* End() {
			index = self->size - 1;
			cur = self->head;
			while (cur->next) {
				cur = cur->next;
			}
			return &(cur->field);
		}

		T& operator*() {
			return cur->field;
		}

		Iterator& operator++(int) {
			if (cur != NULL) {
				index++;
				cur = cur->next;
			}
			return *this;
		}

		Iterator& operator--(int) {
			index = (index - 1 + self->size) % self->size;
			cur = self->head;
			for (int i = 0; i < index; i++) {
				cur = cur->next;
			}
			return *this;
		}

		Iterator& operator +(int n) {
			index = (index + n) % self->size;
			cur = self->head;
			for (int i = 0; i < index; i++) {
				cur = cur->next;
			}
			return *this;
		}

		bool operator ==(Iterator& other) {
			if (other.cur->field == this->cur->field) {
				return true;
			}
			return false;
		}

		bool operator !=(Iterator& other) {
			return !(other == *this);
		}
	};

	Iterator Count() {
		return Iterator(this);
	}
};
