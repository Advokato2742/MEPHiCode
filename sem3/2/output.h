#pragma once
#include "domino.h"
/*!
* @file output.h
* file with output operator overloads for the Domino and Bunch class
*/

/*!
* @brief output operator overload for the Domino
* @param stream -- refrence to the outpur stream
* @param one -- refrence to the Domino
* @return refrence to the current stream
*/
std::ostream& operator<<(std::ostream&, const Domino&);
/*!
* @brief output operator overload for the Bunch of Domino
* @param stream -- refrence to the outpur stream
* @param one -- refrence to the Bunch
* @return refrence to the current stream
*/
std::ostream& operator<<(std::ostream&, const Bunch&);