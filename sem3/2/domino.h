#pragma once
#include <cstdint>
#include <vector>
#include <string>

class Domino {
private:
	static inline const uint8_t q{7};
public:
	uint8_t left{};
	uint8_t right{};

	Domino();
	Domino(int a, int b);

	Domino& ChangeValues();
	void Rotate();
	int Left() const;
	int Right() const;
	std::string GetImage() const;
	int GetSum() const;

	bool operator ==(const Domino& other) const;
	Domino& operator =(const Domino& other);
};

class Dominoes {
private:
	std::vector<Domino> bunch;
public:
	Dominoes();
	Dominoes(size_t counter);
	int GetSize() const {
		return bunch.size();
	}
	Dominoes& Add();
	Dominoes& DeleteAt(size_t i);
	Dominoes& Delete();

	Domino& operator[] (size_t i);
	const Domino& operator[] (size_t i) const;

	Dominoes& operator+= (const Domino& one);
	Dominoes& operator+= (const Dominoes& other);
	
	Dominoes& Sort();
	Dominoes* GetSubbunch(int val);
};

std::ostream& operator<<(std::ostream&, const Domino&);
std::ostream& operator<<(std::ostream&, const Dominoes&);
std::istream& operator>>(std::istream& stream, Domino&);
std::istream& operator>>(std::istream& stream, Dominoes&);