// AUTHOR: Ryan McKenzie
// FILENAME: multiMix.cpp
// DATE: May 29, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v7.1.0

// Implementation Invariant:
// * numMixers are tracked via a stack.
// * User decides when numMixers are pushed/removed from stack.
// * No guards are made against pinging an empty stack.
// * numMixers rotate through states depending on their index in the stack:
// [0] Mix -> [1] Even -> [2] Odd -> [3] Mix
// * Prime numbers are checked against a predefined list < 100.
// * numMixers must be seeded with a dataset 2-100, else prime numbers can't
// be checked.


#include <ctime>  // time
#include <stack>  // stack
#include <vector>  // vector
#include <algorithm>  // binary_search
#include <random>  // mt19937


#include "../include/multiMix.h"
#include "../include/numMixer.h"


const std::vector<int> multiMix::_PRIME_NUMBERS = { 2, 3, 5, 7, 11,
													13, 17, 19, 23, 29,
													31, 37, 41, 43, 47,
													53, 59, 61, 67, 71,
													73, 79, 83, 89, 97 };


std::mt19937 multiMix::_eng(time(0));


multiMix::multiMix():
	_numMixerStack()
{
}


multiMix::~multiMix()
{
}


std::vector<int> multiMix::ping()
{
	numMixer& rNumMixerObj = _numMixerStack.top();
	const int SIZE = 10;
	std::vector<int> returnset(SIZE);
	switch (_numMixerStack.size() - 1 % 3) {
		case 0:
			rNumMixerObj.setControllerState(numMixer::MIX);
			rNumMixerObj.ping(returnset);
			purgePrimeNumbers(returnset);
			return returnset;
		case 1:
			rNumMixerObj.setControllerState(numMixer::EVEN);
			rNumMixerObj.ping(returnset);
			return returnset;
		case 2:
			rNumMixerObj.setControllerState(numMixer::ODD);
			rNumMixerObj.ping(returnset);
			return returnset;
		default:
			return std::vector<int> (0);
	}
}


void multiMix::addNumMixers(unsigned int count)
{
	std::vector<int> dataset;
	while (count--) {
		_numMixerStack.push(numMixer(generateDataset()));
	}
}


void multiMix::removeNumMixers(unsigned int count)
{
	while (count--) {
		_numMixerStack.pop();
	}
}


std::vector<int> multiMix::generateDataset(unsigned int size)
{
	const int LOWER_BOUND = 2;
	const int UPPER_BOUND = 100;
	std::uniform_int_distribution<> distr(LOWER_BOUND, UPPER_BOUND);
	std::vector<int> dataset(size);
	for (auto& val : dataset) {
		val = distr(_eng);
	}
	return dataset;
}


bool multiMix::isPrime(int n)
{
	return std::binary_search(_PRIME_NUMBERS.begin(), _PRIME_NUMBERS.end(), n);
}


void multiMix::purgePrimeNumbers(std::vector<int>& arr)
{
	int newSize = arr.size();
	for (int i = arr.size() - 1; i >= 0; --i) {
		if (isPrime(arr[i])) {
			arr[i] = arr[newSize - 1];
			--newSize;
		}
	}
	arr.resize(newSize);
}