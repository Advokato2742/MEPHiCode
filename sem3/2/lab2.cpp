#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
/*
const std::vector<std::vector<std::string>> p = {
	{
		"      ",
		"      ",
		"      ",
		"      ",
		"      ",
		"      ",
		"      ",
		"      ",
		"      "
	},
	{
		"      ",
		"   #  ",
		"  ##  ",
		" # #  ",
		"   #  ",
		"   #  ",
		"   #  ",
		" #### ",
		"      "
	},
	{
		"      ",
		"  ##  ",
		" #  # ",
		"    # ",
		"   #  ",
		"  #   ",
		" #    ",
		" #### ",
	},
	{
		"      ",
		"  ##  ",
		" #  # ",
		"    # ",
		"   #  ",
		"    # ",
		" #  # ",
		"  ##  ",
	},
		"      ",
		" #  # ",
		" #  # ",
		" #  # ",
		"  ### ",
		"    # ",
		"    # ",
		"    # ",
		"      "
	}
};*/
const int q = 7;

class Domino {
private:
	int left{};
	int right{};
public:
	Domino() : left(), right() {  }
	Domino(int a, int b) : left(a%q), right(b%q) {  }

	Domino& ChangeValues() {
		left = rand() % (q);
		right = rand() % (q);
		return *this;
	}
	void Rotate() {
		int t(left);
		left = right;
		right = t;
	}
	int Left() { return left; }
	int Right() { return right; }

	bool operator ==(Domino& other) const {
		return ((left == other.left) && (right == other.right) || (right == other.left) && (left == other.right));
	}
	Domino& operator =(Domino& other) {
		right = other.right;
		left = other.left;
		return *this;
	}
	std::string GetImage() {
		std::string s = std::to_string(left) + " " + std::to_string(right);
		return s;
	}
};

class Dominoes {
private:
	std::vector<Domino> set;
	int size;
public:
	Dominoes(int counter) : size(counter) {
		if (counter < 0) throw std::invalid_argument("size cannot be less than 1");
		set.reserve(counter);
		for (int i = 0; i < counter; i++) {
			set.push_back(Domino().ChangeValues());
		}
	}
	void Print() {
		std::cout << "your set " << set.size() << std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << set[i].GetImage() << " ";
		}
		std::cout << std::endl;
	}
	Dominoes& Add() {
		set.push_back(Domino().ChangeValues());
		return *this;
	}
	Dominoes& Delete() {
		int i = rand() % size;
		set[i] = set[size-1];
		set.pop_back();
		return *this;
	}


	Domino& operator[] (int i) {
		return set[i];
	}

	Dominoes& operator+= (Domino& one) {
		set.push_back(one);
		size++;
		return *this;
	}
	Dominoes& operator+= (Dominoes& other) {
		set.reserve(size + other.size);
		for (int i = 0; i < other.size; i++) {
			set.push_back(other[i]);
		}
		size += other.size;
		return *this;
	}
};

int main() {
	srand(time(0));
	Dominoes a = Dominoes(4);
	a.Print();
	Domino r = Domino(3, 5);
	a += r;
	a.Print();
	Dominoes b = Dominoes(3);
	a += b;
	a.Print();
	b[3] = r;
	a.Print();
	return 0;
}