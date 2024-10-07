#include "domino.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Domino::Domino() : left(), right() {  }
Domino::Domino(int a, int b) : left(a%q), right(b%q) {  }

Domino& Domino::ChangeValues() {
	left = rand() % (q);
	right = rand() % (q);
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

Dominoes::Dominoes() {  }
Dominoes::Dominoes(size_t counter) {
	bunch.reserve(counter);
	for (int i = 0; i < counter; i++) {
		bunch.push_back(Domino().ChangeValues());
	}
}
Dominoes& Dominoes::Add() {
	bunch.push_back(Domino().ChangeValues());
	return *this;
}
Dominoes& Dominoes::DeleteAt(size_t i) {
	if (i >= bunch.size()) throw std::invalid_argument("incorrect index");
	bunch[i] = bunch[bunch.size()-1];
	bunch.pop_back();
	return *this;
}

Dominoes& Dominoes::Delete() {
	int i = rand() % bunch.size();
	DeleteAt(i);
	return *this;
}

Domino& Dominoes::operator[] (size_t i) {
	return bunch[i];
}
const Domino& Dominoes::operator[] (size_t i) const {
	return bunch[i];
}

Dominoes& Dominoes::operator+= (const Domino& one) {
	bunch.push_back(one);
	return *this;
}
Dominoes& Dominoes::operator+= (const Dominoes& other) {
	bunch.reserve(bunch.size() + other.bunch.size());
	for (int i = 0; i < other.bunch.size(); i++) {
		bunch.push_back(other[i]);
	}
	return *this;
}
Dominoes& Dominoes::Sort() {
	std::sort(bunch.begin(), bunch.end(), [](auto& d1, auto& d2) { return (d1.GetSum() < d2.GetSum()); });
	return *this;
}
Dominoes* Dominoes::GetSubbunch(int val) {
	Dominoes* other = new Dominoes();
	for (int i = 0; i < bunch.size(); i++) {
		if (bunch[i].Left() == val || bunch[i].Right() == val) {
			*other += bunch[i];
			DeleteAt(i);
			i--;
		}
	}
	return other;
}

std::ostream& operator<<(std::ostream& stream, const Domino& one) {
	stream << one.GetImage();
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const Dominoes& one) {
	for (int i = 0; i < one.GetSize(); i++) {
		stream << one[i];
		if (i != one.GetSize()) {
			stream << " ";
		}
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, Domino& one) {
	int t1, t2;
	stream >> t1 >> t2;
	if(stream.good()) {
		if(t1 >= 0 && t2 >= 0) {
			one.left = t1 % 7;
			one.right = t2 % 7;
		} else {
			stream.setstate(std::ios::failbit);
		}
	}
	return stream;
};

std::istream& operator>>(std::istream& stream, Dominoes& one) {
	int i = 0;
	while (stream.good() && i < one.GetSize()) {
		int t1, t2;
		stream >> t1 >> t2;
		if(stream.good()) {
			if(t1 >= 0 && t2 >= 0) {
				one[i].left = t1 % 7;
				one[i].right = t2 % 7;
			} else {
				stream.setstate(std::ios::failbit);
				break;
			}
		}
		i++;
	}
	return stream;
};