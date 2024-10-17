#include "domino.h"
#include <iostream>
#include <algorithm>
#include <random>

//
//
//
//Domino
//
//
//

//number of domino values
const uint8_t q{7};
Domino::Domino() : left(), right() {  }
Domino::Domino(const int a, const int b) : left(a%q), right(b%q) {  }

Domino& Domino::ChangeValues() {
	std::mt19937 eng {std::random_device{}()};
	left = eng() % (q);
	right = eng() % (q);
	return *this;
}
void Domino::Rotate() {
	std::swap(left, right);
}
int Domino::Left() const { return left; }
int Domino::Right() const { return right; }
std::string Domino::GetImage() const {
	return std::to_string(left) + " " + std::to_string(right);
}
int Domino::GetSum() const {
	return left + right;
}

bool Domino::operator ==(const Domino& other) const {
	return ((left == other.left) && (right == other.right) || (right == other.left) && (left == other.right));
}
Domino& Domino::operator =(const Domino& other) {
	right = other.right;
	left = other.left;
	return *this;
}
bool Domino::operator <(const Domino& other) const {
    return this->GetSum() < other.GetSum();
}
bool Domino::operator >(const Domino& other) const {
    return this->GetSum() > other.GetSum();
}
bool Domino::operator !=(const Domino& other) const {
    return this->GetSum() != other.GetSum();
}
bool Domino::operator <=(const Domino& other) const {
    return this->GetSum() <= other.GetSum();
}
bool Domino::operator >=(const Domino& other) const {
    return this->GetSum() >= other.GetSum();
}

//
//
//
//Bunch
//
//
//

Bunch::Bunch() : size(0), array(nullptr) {  }
Bunch::Bunch(size_t counter) : size(counter) {
	array = new Domino[counter];
	std::for_each(array, (array+counter), [](Domino& d){ d = Domino().ChangeValues();});
}

Bunch::Bunch(const Bunch& other) {
	Domino* tmp = new Domino[other.size];
	std::copy(other.array, (other.array+other.size), tmp);
	delete [] array;
	size = other.size;
	array = tmp;
}

Bunch::Bunch(Bunch&& other) noexcept {
    array = other.array;
	size = other.size;
	other.size = 0;
	other.array = nullptr;
}
Bunch::~Bunch() {
	delete [] array;
}

Bunch& Bunch::Add() {
	Domino* tmp;
	try {
		tmp = new Domino[size+1];
	} catch (...) {
		return *this;
	}
	std::copy(array, (array+size), tmp);
	delete [] array;
	tmp[size] = Domino().ChangeValues();
	size++;
	array = tmp;
	return *this;
}

Bunch& Bunch::DeleteAt(const size_t i) {
	if (i >= size || size == 0) throw std::invalid_argument("incorrect index");
	Domino* tmp;
	try {
		tmp = new Domino[size-1];
	} catch (...) {
		return *this;
	}
	std::copy(array, (array+i), tmp);
	std::copy(array+i+1, array+size, tmp+i-1);
	delete [] array;
	size--;
	array = tmp;
	return *this;
}

Bunch& Bunch::Delete() {
	std::mt19937 eng {std::random_device{}()};
	int i = eng() % size;
	DeleteAt(i);
	return *this;
}

Domino& Bunch::operator[] (const size_t i) {
	return array[i];
}
const Domino& Bunch::operator[] (const size_t i) const {
	return array[i];
}

Bunch& Bunch::operator+= (const Domino& one) {
	Domino* tmp;
	try {
		tmp = new Domino[size+1];
	} catch (...) {
		return *this;
	}
	std::copy(array, (array+size), tmp);
	delete [] array;
	tmp[size] = one;
	size++;
	array = tmp;
	return *this;
}
Bunch& Bunch::operator+= (const Bunch& other) {
	Domino* tmp;
	try {
		tmp = new Domino[size+other.size];
	} catch (...) {
		return *this;
	}
	std::copy(array, (array+size), tmp);
	std::copy(other.array, (other.array+other.size), (tmp+size));
	delete [] array;
	size = size + other.size;
	array = tmp;
	return *this;
}

Bunch& Bunch::operator= (const Bunch& other) {
	if (this == &other)
		return *this;
	if (size != other.size) {
		Domino* tmp;
		try {
			tmp = new Domino[other.size];
		} catch (...) {
			return *this;
		}
		std::copy(other.array, (other.array+other.size), tmp);
		delete [] array;
		size = other.size;
		array = tmp;
	} else {
		std::copy(other.array, (other.array+other.size), array);
	}
	return *this;
}

Bunch& Bunch::operator= (Bunch&& other) noexcept {
    delete [] array;
    array = other.array;
	size = other.size;
	other.size = 0;
	other.array = nullptr;
    return *this;
}

Bunch& Bunch::Sort() {
	std::sort(array, (array+size), [](Domino& d1, Domino& d2) { return (d1 < d2); });
	return *this;
}

Bunch* Bunch::GetSubBunch(const int val) {
	if (val < 0 || val >= q) throw std::invalid_argument("value of a Domino cannot be less than zero or greater than 6");
	int oldLen = 0;
	bool* withVal = new bool[size]{false};
	std::transform(array, array+size, withVal, [&](Domino& d) {
					if ((d.Left() == val) || (d.Right() == val)) {
						return true;
					} else {
						oldLen++;
						return false;}});

	int newLen = size - oldLen;
	Domino* old;
	try {
		old = new Domino[oldLen];
	} catch(...) {
		delete [] old;
		throw std::bad_alloc();
	}
	Domino* tmp;
	try {
		tmp = new Domino[newLen];
	} catch(...) {
		delete [] old;
		throw std::bad_alloc();
	}
	std::copy_if(array, array+size, tmp, [&](Domino& d){return withVal[(&d - array)];});
	std::copy_if(array, array+size, old, [&](Domino& d){return !withVal[(&d - array)];});
	delete [] array;
	array = old;
	size = oldLen;
	Bunch* other = new Bunch();
	other->array = tmp;
	other->size = newLen;
	return other;
}