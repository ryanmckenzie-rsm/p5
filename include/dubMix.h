// AUTHOR: Ryan McKenzie
// FILENAME: dubMix.h
// DATE: May 29, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v7.1.0

// Class Invariant:
// * has-a relationship with numMixers.
// * "_x" is instantiated to "EVEN".
// * "_z" is instantiated to "ODD".
// * "_ctl" is instantiated 3.
// * Client can immediately ping dubMix after instantiation.

// Interface Invariant:
// * State of dubMix is tracked via "+ctl"
// * Valid range for "_ctl" is 1-4.
// * ctl == 1 returns even integers.
// * ctl == 2 returns odd integers.
// * ctl == 3 returns alternating even and odd integers.
// * ctl == 4 returns even followed by odd integers, without duplicates.

// DESCRIPTION:
// * dubMix mixes values from two numMixer objects and returns them depending on
// the value of ctl.

// ASSUMPTIONS:
// * numMixer "_x" uses the default constructor (dataset values 1-100), and is
// set to output even values only.
// * numMixer "z" uses the default constructor (dataset values 1-100), and is
// set to output odd values only.
// * The client can set the state of ctl using a public mutator. This is the
// only way ctl can change state.
// * Pinging the dubMixer returns an array of size 1-20, depending on the
// state of ctl.
// * If ctl is set to 3, then values from "x" and "z" are interleaved by
// returning alternating values from "x" and "z"
// (i.e. [0] = x, [1] = z, [2] = x, ... ).
// * If ctl is set to 4, values from "x" are followed by values from "z", within
// the same return array. Duplicates are removed.
// * Comparison (==) operators are supported.
// * Comparison is performed on all members.
// * Relational (<) operators are supported.
// * Relations are assed on _x and _z.
// * Addition (+) operators are supported.
// * Addition is performed on _x and _z.


#ifndef dubMix_INCLUDED
#define dubMix_INCLUDED


#include <vector>  // vector


#include "../include/numMixer.h"


class dubMix
{
	public:
		// Constructos

		dubMix();
		// Description:
		// * Creates two numMixer objects, "_x" and "_z".
		// * "_x" is set to output even numbers.
		// * "_z" is set out output odd numbers.
		// * "_ctl" is set to mix "_x" and "_z".
		// 
		// Postconditions:
		// * "_x" is instantiated using the default constructor (dataset values
		// 1-100).
		// * "_x" is set to output even values.
		// * "_z" is instantiated using the default constructor (dataset values
		// 1-100).
		// * "_z" is set to output odd values.
		// * "_ctl" is set to 3.

		~dubMix();
		// Description:
		// * Placeholder, no-op


		// Functionality

		std::vector<int> ping();
		// Description:
		// * Pings the numMixer objects, "_x" and "_z", and returns a vector,
		// whose values depend on the state of "_ctl".
		// * If "ctl" is 1, returns 10 values from "_x".
		// * If "ctl" is 2, returns 10 values from "_z".
		// * If "ctl" is 3, returns a mix of 20 values from "_x" and "_z", where
		// every even index is a value from "_x" and every odd index is a value
		// from "_z".
		// * If "_ctl" is 4, returns values from "_x", followed by values from
		// "_z".
		// * Duplicates are removed.
		// * The total count of values is <= 20.
		// 
		// Preconditions:
		// * "_ctl" must be set to a valid value.


		// Accessors

		int getCtl() const;
		// Description:
		// * Returns ctl.

		const numMixer& x() const;
		// Description:
		// * Returns x.

		const numMixer& z() const;
		// Description:
		// * Returns z.


		// Mutators

		void setCtl(unsigned int val);
		// Description:
		// * Sets "_ctl" to the passed value.
		// * Valid values range 1-4.
		// 
		// Preconditions:
		// * "val" must be 1-4.
		// 
		// Postconditions:
		// * "_ctl" is set to the passed value.

		
		// Comparison Operators

		friend bool operator==(const dubMix& lhs, const dubMix& rhs);  // 1
		friend bool operator!=(const dubMix& lhs, const dubMix& rhs);  // 2
		// Description (1-2):
		// * Checks if _ctl, _x, and _z are the same.

		friend bool operator<(const dubMix& lhs, const dubMix& rhs);  // 3
		friend bool operator>(const dubMix& lhs, const dubMix& rhs);  // 4
		friend bool operator<=(const dubMix& lhs, const dubMix& rhs);  // 5
		friend bool operator>=(const dubMix& lhs, const dubMix& rhs);  // 6
		// Description (3-6):
		// * Performs comparison on lhs._x, lhs._z and rhs._x, rhs._z.

		// Arithmetic Operators

		friend dubMix operator+(dubMix lhs, const dubMix& rhs);  // 1
		dubMix& operator+=(const dubMix& obj);  // 2
		// Description (1-2):
		// * Adds rhs._x, rhs._z to lhs._x, lhs._z respectively.
		// 
		// Postconditions:
		// * "_x" and "_z" will have changed.


	private:
		// Utility

		void purgeDuplicates(std::vector<int>& arr);
		// Description:
		// * Removes duplicate values from the passed vector.
		// * Duplicate values are moved to the end of the vector, decrementing
		// "newSize" each time.
		// * Once the vector has been parsed, it is resized to "newSize",
		// discarding duplicate values at the end.
		// 
		// Preconditions:
		// * "arr" should be an vector of size >= 2.

		std::vector<int> ctl1(unsigned int size);
		// Description:
		// * Returns even values from "_x" in the case "_ctl" is set to 1.
		//
		// Preconditions:
		// * "size" should be > 0.

		std::vector<int> ctl2(unsigned int size);
		// Description:
		// * Returns odd values from "_z" in the case "_ctl" is set to 2.
		//
		// Preconditions:
		// * "size" should be > 0.

		std::vector<int> ctl3(unsigned int size);
		// Description:
		// * Returns altenating even and odd values from "_x" and "_z" in the
		// case "_ctl" is set to 3.
		//
		// Preconditions:
		// * "size" should be > 1.

		std::vector<int> ctl4(unsigned int size);
		// Description:
		// * Returns even vlues from "_x", followed by odd values from "_z" in
		// the case "_ctl" is set to 4.
		//
		// Preconditions:
		// * "size" should be > 1.


		// Members

		int _ctl;
		// Used to determine the dubMix's output.

		numMixer _x;
		// Contains a dataset of even values.

		numMixer _z;
		// Contains a dataset of odd values.
};


inline int dubMix::getCtl() const
{
	return _ctl;
}


inline const numMixer& dubMix::x() const
{
	return _x;
}


inline const numMixer& dubMix::z() const
{
	return _z;
}


inline bool operator==(const dubMix& lhs, const dubMix& rhs)
{
	return (lhs._ctl == rhs._ctl &&
			lhs._x == rhs._x &&
			lhs._z == rhs._z);
}


inline bool operator!=(const dubMix& lhs, const dubMix& rhs)
{
	return !operator==(lhs, rhs);
}


inline bool operator<(const dubMix& lhs, const dubMix& rhs)
{
	return (lhs._x < rhs._x &&
			lhs._z < rhs._z);
}


inline bool operator>(const dubMix& lhs, const dubMix& rhs)
{
	return operator<(rhs, lhs);
}


inline bool operator<=(const dubMix& lhs, const dubMix& rhs)
{
	return !operator>(lhs, rhs);
}


inline bool operator>=(const dubMix& lhs, const dubMix& rhs)
{
	return !operator<(lhs, rhs);
}


inline dubMix operator+(dubMix lhs, const dubMix& rhs)
{
	lhs += rhs;
	return lhs;
}


inline dubMix& dubMix::operator+=(const dubMix& obj)
{
	_x += obj._x;
	_z += obj._z;
	return *this;
}


#endif