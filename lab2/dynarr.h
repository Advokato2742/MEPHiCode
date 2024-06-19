#pragma once
#include <cstddef>
#include <stdexcept>

template <class T>
class DynamicArray {
private: 	
	T* elements;
	int size;
public:
	DynamicArray() {
		size = 0;
		elements = NULL;
	}
	
	DynamicArray(T* items, int quantity)
			: elements(new T [quantity]), size(quantity) {
		for (int i = 0; i < quantity; i++) {
			elements[i] = items[i];
		}
	}
	
	DynamicArray(const DynamicArray<T>& array) {
		size = array.size;
		elements = new T[size]{};
		for (int i = 0; i < size; i++) {
			elements[i] = array.elements[i];
		}
	}
	
	DynamicArray(int quantity) 
			: elements(new T[quantity]{}), size(quantity) {}

	~DynamicArray() {
		delete [] elements;
	}

	T GetElement(int index) const {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		return elements[index];
	}

	int GetLength() const {
		return size;
	}
	
	void Set(int index, T value) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		elements[index] = value;
	}
	
	DynamicArray* Resize(int newSize) {
		T* hlp = new T[newSize]{};
		
		int copies = (newSize > size) ? size : newSize;

		size = newSize;

		for (int i = 0; i < copies; i++) {
			hlp[i] = elements[i];
		}
		delete [] elements;
		
		elements = hlp;
		return this;
	}
	
	bool operator ==(const DynamicArray<T>& other) const {
		if (size != other.size) {
			return false;
		}
		for (int i = 0; i < size; i++) {
			if (elements[i] != other.elements[i]) {
				return false;
			}
		}
		return true;
	}

	DynamicArray<T>& operator =(const DynamicArray<T>& other) {
		if (*this == other) {
			return *this;
		}
		this->~DynamicArray();
		size = other.size;
		elements = new int[size];
		for (int i = 0; i < size; i++) {
			elements[i] = other.elements[i];
		}
		return *this;
	}

	class Iterator {
		friend DynamicArray;
	private:
		T* cur{};
		DynamicArray<T>* self{};
		int index{};
	public:
		Iterator() {  }
		Iterator(Iterator& other) {
			cur = other.cur;
			self = other.self;
			index = other.CurIndex();
		}
		Iterator(DynamicArray<T>* data) : self(data), index(0) {
			if (self->size == 0) {
				throw std::invalid_argument("Cannot count empty data");
			}
			cur = self->elements;
		}
		int CurIndex() {
			return index;
		}

		T* Begin() {
			cur = self->elements;
			index = 0;
			return cur;
		}

		T* End() {
			index = self->size - 1;
			cur = self->elements + index;
			return cur;
		}

		T& operator*() {
			return *cur;
		}

		Iterator& operator++(int) {
			index = (index + 1) % self->size;
			cur = self->elements + index;
			return *this;
		}

		Iterator& operator--(int) {
			index = (index - 1 + self->size) % self->size;
			cur = self->elements + index;
			return *this;
		}

		Iterator& operator +(int n) {
			index = (index + n) % self->size;
			cur = self->elements + index;
			return *this;
		}

		bool operator ==(Iterator& other) {
			if (*(other.cur) == *(this->cur)) {
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