#pragma once
#include "dynarr.h"
#include "linklist.h"

template <class T> 
class Sequence {
public:
	virtual ~Sequence() {  };
	
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T GetElement(int index) const = 0;
	virtual int GetLength() const = 0;
	
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, int index) = 0;
	
	virtual Sequence<T>* ImmutableAppend(T item) const = 0;
	virtual Sequence<T>* ImmutablePrepend(T item) const = 0;
	virtual Sequence<T>* ImmutableInsertAt(T item, int index) const = 0;

	virtual void Concat(const Sequence<T> *seq) = 0;
	virtual Sequence<T>* ImmutableConcat(const Sequence<T> *seq) const = 0;

	virtual bool operator ==(Sequence<T> &seq) const {
		if (this->GetLength() != seq.GetLength()) {
			return false;
		}
		for (int i = 0; i < this->GetLength(); i++) {
			if (this->GetElement(i) != seq.GetElement(i)) {
				return false;
			}
		}
		return true;
	}
	
	virtual T operator [](int index) const{
		return this->GetElement(index);
	}
	
	virtual Sequence<T>* operator +(const Sequence<T> *other) const {
		return this->ImmutableConcat(other);
	}
	
};


template <class T> 
class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* elements = NULL;
public:
	ArraySequence(T* items, int count)
			: elements(new DynamicArray<T>(items, count)) {} 
	ArraySequence()
			: elements(new DynamicArray<T>(0)) {}
	ArraySequence(const ArraySequence<T> &arr)
			: elements(new DynamicArray<T>(*(arr.elements))) {}
	
	virtual ~ArraySequence() {
		delete elements;
	}

	virtual T GetFirst() const override {
		return this->elements->GetElement(0);
	}
	virtual T GetLast() const override {
		return this->elements->GetElement(this->elements->GetLength()-1);
	}		
	virtual T GetElement(int index) const override {
		return this->elements->GetElement(index);
	}
	virtual int GetLength() const override {
		return this->elements->GetLength();
	}

	virtual void Append(T item) override {
		this->elements->Resize(this->elements->GetLength()+1);
		this->elements->Set(this->elements->GetLength()-1, item);
	}
	virtual void Prepend(T item) override {
		this->elements->Resize(this->elements->GetLength()+1);
		for (int i = this->GetLength()-1; i > 0; i--) {
			this->elements->Set(i, this->elements->GetElement(i-1));
		}
		this->elements->Set(0, item);
	}
	virtual void InsertAt(T item, int index) override {
		if (index < 0 || index > this->elements->GetLength()) {
			throw std::out_of_range("Index is out of range.");
		}
		this->elements->Resize(this->elements->GetLength()+1);
		for (int i = this->elements->GetLength()-1; i > index; i--) {
			this->elements->Set(i, this->elements->GetElement(i-1));
		}
		this->elements->Set(index, item);
	}

	virtual ArraySequence<T>* ImmutableAppend(T item) const override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->Append(item);
		return newsequence;
	}
	virtual ArraySequence<T>* ImmutablePrepend(T item) const override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->Prepend(item);
		return newsequence;
	}
	virtual ArraySequence<T>* ImmutableInsertAt(T item, int index) const override {
		if (index < 0 || index > this->elements->GetLength()) {
			throw std::out_of_range("Index is out of range.");
		}
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->InsertAt(item, index);
		return newsequence;
	}

	virtual ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
		if (startIndex < 0 || startIndex >= this->elements->GetLength() || endIndex < 0 || endIndex >= this->elements->GetLength()) {
			throw std::out_of_range("Index is out of range.");
		}
		if (startIndex > endIndex) {
			throw std::invalid_argument("The start index must be less than the end index");
		}
		
		int subsize = endIndex - startIndex + 1;
		T items[subsize];
		
		for (int i = startIndex; i <= endIndex; i++) {
			items[i - startIndex] = this->elements->GetElement(i);
		}
		ArraySequence<T> *subseq = new ArraySequence<T>(items, subsize);
		return subseq;
	}
	
	virtual void Concat(const Sequence<T> *seq) override {
		if (!(seq->GetLength())) return;
		for (int i = 0; i < seq->GetLength(); i++) {
			this->Append(seq->GetElement(i));
		}
	}
	virtual ArraySequence<T>* ImmutableConcat(const Sequence<T> *seq) const override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->Concat(seq);
		return newsequence;
	}
	
	class Iterator {
		friend ArraySequence;
	private:
		typename DynamicArray<T>::Iterator counter;
		ArraySequence<T>* self{};

		Iterator(ArraySequence<T>* data) : self(data) {
			if (self->GetLength() == 0) {
				throw std::invalid_argument("Cannot count empty data");
			}
			counter = typename DynamicArray<T>::Iterator((self->elements->Count()) );
		}
	public:
		int CurIndex() {
			return counter.CurIndex();
		}

		T* Begin() {
			return counter.Begin();
		}

		T* End() {
			return counter.End();
		}

		T operator *() {
			return *counter;
		}

		Iterator& operator++(int) {
			counter++;
			return *this;
		}

		Iterator& operator--(int) {
			counter--;
			return *this;
		}

		Iterator& operator +(int n) {
			counter+n;
			return *this;
		}

		bool operator ==(Iterator& other) {
			return counter == other.counter;
		}

		bool operator !=(Iterator& other) {
			return !(counter == other.counter);
		}
	};

	Iterator Count() {
		return Iterator(this);
	}
	
};

template <class T> 
class ListSequence : public Sequence<T> {
private: 
	LinkedList<T>* elements;
public:
	ListSequence(T* items, int count)
			: elements(new LinkedList<T>(items, count)) {}
	ListSequence()
			: elements(new LinkedList<T>()) {}
	ListSequence(const ListSequence<T> &list)
			: elements(new LinkedList<T>(*(list.elements))) {}
	ListSequence(const LinkedList<T> &list)
			: elements(new LinkedList<T>(list)) {}
	
	virtual ~ListSequence() {
		delete elements;
	}
	
	virtual T GetFirst() const override {
		return this->elements->GetFirst();
	}
	virtual T GetLast() const override {
		return this->elements->GetLast();
	}
	virtual T GetElement(int index) const override {
		return this->elements->GetElement(index);
	}
	virtual T GetLength() const override {
		return this->elements->GetLength();
	}
	
	virtual ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
		LinkedList<T>* sublist = this->elements->GetSubList(startIndex, endIndex);
		ListSequence<T>* subseq = new ListSequence(*sublist);
		delete sublist;
		return subseq;
	}
	
	virtual void Append(T item) override {
		this->elements->Append(item);	
	}
	virtual void Prepend(T item) override {
		this->elements->Prepend(item);
	}
	virtual void InsertAt(T item, int index) override {
		if (index < 0 || index > this->elements->GetLength()) {
			throw std::out_of_range("Index is out of range.");
		}
		this->elements->InsertAt(item, index);
	}

	virtual ListSequence<T>* ImmutableAppend(T item) const override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elements));
		newsequence->Append(item);
		return newsequence;
	}
	virtual ListSequence<T>* ImmutablePrepend(T item) const override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elements));
		newsequence->Prepend(item);
		return newsequence;
	}
	virtual ListSequence<T>* ImmutableInsertAt(T item, int index) const override {
		if (index < 0 || index > this->elements->GetLength()) {
			throw std::out_of_range("Index is out of range.");
		}
		ListSequence<T> *newsequence = new ListSequence(*(this->elements));
		newsequence->InsertAt(item, index);
		return newsequence;
	}

	virtual void Concat(const Sequence<T> *seq) {
		for (int i = 0; i < seq->GetLength(); i++) {
			this->Append(seq->GetElement(i));
		}
	}
	virtual ListSequence<T>* ImmutableConcat(const Sequence<T> *seq) const override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elements));
		newsequence->Concat(seq);
		return newsequence;
	}

	class Iterator {
		friend ListSequence;
	private:
		typename LinkedList<T>::Iterator counter;
		ListSequence<T>* self{};

		Iterator(ListSequence<T>* data) : self(data) {
			if (self->GetLength() == 0) {
				throw std::invalid_argument("Cannot count empty data");
			}
			counter = typename LinkedList<T>::Iterator((self->elements->Count()));
		}
	public:
		int CurIndex() {
			return counter.CurIndex();
		}

		T* Begin() {
			return counter.Begin();
		}

		T* End() {
			return counter.End();
		}

		T operator *() {
			return *counter;
		}

		Iterator& operator++(int) {
			counter++;
			return *this;
		}

		Iterator& operator--(int) {
			counter--;
			return *this;
		}

		Iterator& operator +(int n) {
			counter+n;
			return *this;
		}

		bool operator ==(Iterator& other) {
			return counter == other.counter;
		}

		bool operator !=(Iterator& other) {
			return !(counter == other.counter);
		}
	};

	Iterator Count() {
		return Iterator(this);
	}
};
