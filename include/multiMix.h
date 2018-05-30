// AUTHOR: Ryan McKenzie
// FILENAME: multiMix.h
// DATE: May 29, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v7.1.0

// Class Invariant:
// * Class begins with no numMixer objects.
// * Client controls when numMixers are added/removed.
// * has-a relationship with numMixers.
// * numMixers rotate through state as numMixers are added/removed.

// Interface Invariant:
// * The main functionality is provided in ping(). Data is output depending on
// the state of a numMixer object
// * numMixer objects change state depending on how many numMixers the mutliMix
// contains.
// * ping() is invalid unless the multiMix contains numMixers.
// * The multiMix begins with no numMixers.
// * The client can check if the multiMix contains numMixers using
// hasNumMixers() and getNumMixerCount().
// * numMixers can be added/removed using addNumMixers() and removeNumMixers()

// DESCRIPTION:
// * multiMix keeps track of a user defined amount of numMixers and echoes
// output from them depending on their state.

// ASSUMPTIONS:
// * numMixer objects are tracked via a stack.
// * The client decides when and how many numMixers to add/remove.
// * When a numMixer is added, it is seeded with a dataset 2-100 and then
// pushed onto the stack.
// * When a numMixer is removed, it is popped from the stack.
// * Public accessors are provided to determine if the stack has numMixers and
// how many it contains.
// * When a client pings the multiMix, it echoes a ping from the numMixer on
// top of the stack and returns an array.
// * The state of the numMixer depends on its index in the stack.
// * For numMixers where i % 3 = 0, the state is set to "Mix".
// * For numMixers in state "Mix", 10 mixed elements are requested. The
// elements are then tested against a predefined list of prime numbers < 100.
// Prime elements are removed, and the rest are returned to the client.
// * For numMixers where i % 3 = 1, the state is set to "Even".
// For numMixers in state "Even", 10 even elements are requested and returned
// to the client.
// * For numMixers where i % 3 = 2, the state is set to "Odd".
// * For numMixers in state "Odd", 10 odd elements are requested and returned
// to the client.
// * Comparison (==) operators are supported.
// * Comparison is performed on the stack.
// * Relational (<) operators are supported.
// * Relations are asses on the size of the stack.
// * Addition (+) operators are supported.
// * Addition is performed on the stack (the stack of the right hand side is
// pushed onto the stack of the left hand side).
// * Mixed-mode addition is supported.
// * A multiMix and a numMixer can be added together, in which case the numMixer
// is pushed onto the stack.


#ifndef multiMix_INCLUDED
#define multiMix_INCLUDED


#include <stack>  // stack
#include <vector>  // vector
#include <random>  // mt19937


#include "../include/numMixer.h"


class multiMix
{
	public:
		// Constructors

		multiMix();
		// Description:
		// * Initializes the stack.
		//
		// Postconditions:
		// * The stack is intiialized, starting out empty.

		~multiMix();
		// Description:
		// * Placeholder, no-op


		// Functionality

		std::vector<int> ping();
		// Description:
		// * Pings an object and returns a vector depending on the state of the
		// numMixer.
		// * The state of a numMixer depends on its position in the stack.
		// * numMixers rotate state through "Mix -> Even -> Odd", beginning at
		// Mix and repeating every third index.
		// * numMixers in a "Mix" state have their prime elements removed,
		// before they are returned to the client.
		// 
		// Preconditions:
		// * The stack must contain at least 1 numMixer.


		// Accessors

		int getNumMixerCount() const;
		// Description:
		// * Returns the amount of numMixers on the stack.

		bool hasNumMixers() const;
		// Desctiption:
		// * Returns whether the stack contains any numMixer objects.
		// * Returns true if the stack does any contain numMixer objects.
		// * Returns false if the satck does not contain any numMixer objects.

		const std::stack<numMixer>& numMixerStack() const;
		// Description:
		// * Returns the numMixer stack.


		// Mutators

		void addNumMixers(unsigned int count);
		// Description:
		// * Seeds and pushes the requested amount, "count", of numMixers to the
		// stack.
		// 
		// Preconditions:
		// * "count" should be greater than 0.
		//
		// Postconditions:
		// * The stack contains "count" new numMixers.

		void removeNumMixers(unsigned int count);
		// Description:
		// * Pops the requested amount, "count", numMixers from the stack.
		// 
		// Preconditions:
		// * "count" should be greater than 0.
		// * The stack must contain "count" amount of numMixers.
		// 
		// Postconditions:
		// * The stack contains "count" less numMixers.


		// Comparison Operators

		friend bool operator==(const multiMix& lhs, const multiMix& rhs);  // 1
		friend bool operator!=(const multiMix& lhs, const multiMix& rhs);  // 2
		// Description (1-2):
		// * Checks if the contents of the stacks are the same, as well as the
		// random number generators (i.e. will they generate the same dataset?).

		friend bool operator<(const multiMix& lhs, const multiMix& rhs);  // 3
		friend bool operator>(const multiMix& lhs, const multiMix& rhs);  // 4
		friend bool operator<=(const multiMix& lhs, const multiMix& rhs);  // 5
		friend bool operator>=(const multiMix& lhs, const multiMix& rhs);  // 6
		// Description (3-6):
		// * Compares the sizes of the stacks.


		// Arithmetic Operators

		friend multiMix operator+(multiMix lhs, const multiMix& rhs);  // 1
		multiMix& operator+=(multiMix obj);  // 2
		// Description (1-2):
		// * Pushes numMixers from rhs onto lhs.
		// 
		// Postconditions:
		// * "_numMixerStack" may have increased in size.

		friend multiMix operator+(multiMix lhs, const numMixer& rhs);  // 3
		multiMix& operator+=(const numMixer& copy);  // 4
		// Description (3-4):
		// * Pushes rhs onto the stack.
		// 
		// Postconditions:
		// * "_numMixerStack" will have increased in size.


	private:
		// Utility

		std::vector<int> generateDataset(unsigned int size = 30);
		// Description:
		// * Generates a dataset of size, "size", of values 2-100.
		// * Returns a randomly generated dataset.
		// 
		// Preconditions:
		// * "size" should be > 0.

		bool isPrime(int n);
		// Description:
		// * Tests if the passed number, "n", is prime or not by comparing to a
		// predefined list of prime numbers < 100.
		// * Returns true if "n" is prime.
		// * Returns false if "n" is not prime.
		// 
		// Preconditions:
		// * "n" must be 2 <= n <= 100.

		void purgePrimeNumbers(std::vector<int>& arr);
		// Description:
		// * Removes prime values from the passed vector.
		// * Prime values are moved to the end of the vector, decrementing
		// "newSize" each time.
		// * Once the array has been parsed, it is resized to "newSize",
		// discarding prime values at the end.
		// 
		// Preconditions:
		// * "arr" should be size > 0.
		// * "arr" must contain integers 2-100.


		// Members

		static const std::vector<int> _PRIME_NUMBERS;
		// Defines all prime numbers, n, where 2 <= n < 100.

		static std::mt19937 _eng;
		// Rng used to seed datasets for numMixer objects.

		std::stack<numMixer> _numMixerStack;
		// Holds numMixes as the user adds/removes them.
};


inline int multiMix::getNumMixerCount() const
{
	return _numMixerStack.size();
}


inline bool multiMix::hasNumMixers() const
{
	return _numMixerStack.size();
}


inline const std::stack<numMixer>& multiMix::numMixerStack() const
{
	return _numMixerStack;
}


inline bool operator==(const multiMix& lhs, const multiMix& rhs)
{
	return (lhs._numMixerStack == rhs._numMixerStack);
}


inline bool operator!=(const multiMix& lhs, const multiMix& rhs)
{
	return !operator==(lhs, rhs);
}


inline bool operator<(const multiMix& lhs, const multiMix& rhs)
{
	return (lhs._numMixerStack.size() < rhs._numMixerStack.size());
}


inline bool operator>(const multiMix& lhs, const multiMix& rhs)
{
	return operator<(rhs, lhs);
}


inline bool operator<=(const multiMix& lhs, const multiMix& rhs)
{
	return !operator>(lhs, rhs);
}


inline bool operator>=(const multiMix& lhs, const multiMix& rhs)
{
	return !operator<(lhs, rhs);
}


inline multiMix operator+(multiMix lhs, const multiMix& rhs)
{
	lhs += rhs;
	return lhs;
}


inline multiMix& multiMix::operator+=(multiMix copy)
{
	// invert stack
	std::stack<numMixer> invStack;
	while (!copy._numMixerStack.empty()) {
		invStack.push(copy._numMixerStack.top());
		copy._numMixerStack.pop();
	}
	// stack the stacks
	while (!invStack.empty()) {
		_numMixerStack.push(invStack.top());
		invStack.pop();
	}
	return *this;
}


inline multiMix operator+(multiMix lhs, const numMixer& rhs)
{
	lhs += rhs;
	return lhs;
}


inline multiMix& multiMix::operator+=(const numMixer& obj)
{
	_numMixerStack.push(obj);
	return *this;
}


#endif