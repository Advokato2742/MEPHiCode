#pragma once
#include <cstdint>
#include <string>

class Domino {
private:
    uint8_t left{};
    uint8_t right{};
public:
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
	bool operator <(const Domino& other) const;
    bool operator >(const Domino& other) const;
    bool operator !=(const Domino& other) const;
    bool operator <=(const Domino& other) const;
    bool operator >=(const Domino& other) const;
};

class Bunch {
private:
    size_t size;
	Domino* array;
public:
	Bunch();
	Bunch(size_t counter);
	int GetSize() const {
		return size;
	}
	Bunch(const Bunch &other);
    Bunch(Bunch&& other) noexcept;
	~Bunch();

	Bunch& Add();
	Bunch& DeleteAt(size_t i);
	Bunch& Delete();

	Domino& operator[] (size_t i);
	const Domino& operator[] (size_t i) const;

	Bunch& operator+= (const Domino& one);
	Bunch& operator+= (const Bunch& other);
	Bunch& operator= (const Bunch& other);
    Bunch& operator= (Bunch&& other) noexcept;
	
	Bunch& Sort();
	Bunch* GetSubBunch(int val);
};