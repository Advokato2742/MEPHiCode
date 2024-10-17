#pragma once
#include <cstdint>
#include <string>

/*!
* @file domino.h
* file with class declarations Domino and Bunch classes
*/

/*!
* @class Domino
*/
class Domino {
private:
    uint8_t left{};
    uint8_t right{};
public:
	/*!
	* @brief creates a domino
	* creates a domino with zeros in left and right
	*/
	Domino();
	/*!
	* @brief creates a domino
	* @param a int for left value of a domino
	* @param b int for right value of a domino
	* creates a domino with zeros in left and right
	*/
	Domino(const int a, const int b);

	/*!
	* @brief changes the value of the domino
	*/
	Domino& ChangeValues();
	/*!
	* @brief swaps the left and right values ​​of a domino
	*/
	void Rotate();
	/*!
	* @brief returns the left value of a domino
	* @return int -- the left value of a domino
	*/
	int Left() const;
	/*!
	* @brief returns the right value of a domino
	* @return int -- the right value of a domino
	*/
	int Right() const;
	/*!
	* @brief returns the values ​​of a domino
	* @return std::string consists of a left and right value separated by a space
	*/
	std::string GetImage() const;
	/*!
	* @brief returns the sum of the domino values
	* @return int -- the sum of the domino values
	*/
	int GetSum() const;
	/*!
	* @brief compares two dominoes by their left and right values
	* @return bool true or false
	*/
	bool operator ==(const Domino& other) const;
	/*!
	* @brief copies the value of another domino to the current one
	* @param other -- Domino& a refrence to the other domino
	* @return a reference to the current domino
	*/
	Domino& operator =(const Domino& other);
	/*!
	* @brief compares the sum of the values ​​of the current and another domino.
	* @param other -- Domino& a refrence to the other domino
	* @return bool true if current Domino sum less than other sum, otherwise false
	*/
	bool operator <(const Domino& other) const;
	/*!
	* @brief compares the sum of the values ​​of the current and another domino.
	* @param other -- Domino& a refrence to the other domino
	* @return returns true if the sum of the current domino is greater than sum of the other, otherwise false
	*/
    bool operator >(const Domino& other) const;
	/*!
	* @brief compares two dominoes by their left and right values
	* @return bool true if Domino values ​​are different, false bool true
	*/
    bool operator !=(const Domino& other) const;
	/*!
	* @brief compares the sum of the values ​​of the current and another domino.
	* @param other -- Domino& a refrence to the other domino
	* @return returns true if the sum of the current domino is less or equal than sum of the other, otherwise false
	*/
    bool operator <=(const Domino& other) const;
	/*!
	* @brief compares the sum of the values ​​of the current and another domino.
	* @param other -- Domino& a refrence to the other domino
	* @return returns true if the sum of the current domino is greater or equal than sum of the other, otherwise false
	*/
    bool operator >=(const Domino& other) const;
};


/*!
* @class Bunch
*/
class Bunch {
private:
    size_t size;
	Domino* array;
public:
	/*!
	* @brief creates an empty bunch
	* creates a empty bunch of a Domino
	*/
	Bunch();
	/*!
	* @brief creates a bunch of counter size
	* creates a bunch of a Domino with random values in left and right
	*/
	Bunch(size_t counter);
	int GetSize() const {
		return size;
	}
	/*!
	* @brief copies a group of dominoes
	* @param other -- a refrence to the other Bunch
	* creates an empty group and copies the values ​​of another domino into it
	*/
	Bunch(const Bunch& other);
	/*!
	* @brief moving constructor
	* @param other -- a refrence to the other Bunch
	* creates an empty group and move the values ​​of another domino into it
	*/
    Bunch(Bunch&& other) noexcept;
	/*!
	* @brief destructor
	*/
	~Bunch();

	/*!
	* @brief adds a Domino with a random value to the group
	* @return refrence to the current object
	*/
	Bunch& Add();
	/*!
	* @brief removes dominoes at the specified index
	* @param i -- index of the element to be removed
	* @return refrence to the current object
	* @throw std::invalid_argument if index is greater than size or size is zero
	*/
	Bunch& DeleteAt(const size_t i);
	/*!
	* @brief removes dominoes at the random index
	* @return refrence to the current object
	* @throw std::invalid_argument if index is greater than size or size is zero
	*/
	Bunch& Delete();

	/*!
	* @brief getting domino refrence by index
	* @param i -- index of the element
	* @return refrence to the Domino
	*/
	Domino& operator[] (const size_t i);
	/*!
	* @brief getting const domino refrence by index
	* @param i -- index of the element
	* @return const refrence to Domino
	*/
	const Domino& operator[] (const size_t i) const;

	/*!
	* @brief adds a copy of the passed domino to the group
	* @param one -- const refrence to the other Domino
	* @return refrence to the current object
	*/
	Bunch& operator+= (const Domino& one);
	/*!
	* @brief adds a copy of the other group to the current group
	* @param other -- const refrence to the other Bunch
	* @return refrence to the current object
	*/
	Bunch& operator+= (const Bunch& other);
	/*!
	* @brief copy assignment operator
	* @param other -- const refrence to the current object
	* @return refrence to the current object
	* replaces the contents with a copy of the contents of other
	*/
	Bunch& operator= (const Bunch& other);
	/*!
	* @brief move assignment operator
	* @param other -- const refrence to the current object
	* @return refrence to the current object
	* Replaces the contents with those of other using move semantics, other is in a valid but unspecified state afterwards
	*/
    Bunch& operator= (Bunch&& other) noexcept;
	
	/*!
	* @brief sorts the group
	* @return refrence to the current object
	* sorts a group of dominoes in ascending order by the value of the sum of the domino values
	*/
	Bunch& Sort();
	/*!
	* @brief getting a subgroup
	* @param val -- const value to be searched for
	* @return Bunch pointer to the subgroup
	* @throw std::invalid_argument if val is less than zero or greater than 6
	* selects from a group of bones all those that contain a given value at least once
	*/
	Bunch* GetSubBunch(const int val);
};