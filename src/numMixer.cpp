// AUTHOR: Ryan McKenzie
// FILENAME: numMixer.cpp
// DATE: May 29, 2018
// REVISION HISTORY: v4.0.0
// PLATFORM: GCC v7.1.0


#include <ctime>  // time
#include <vector>  // vector
#include <algorithm>  // copy
#include <random>  // mt19937, uniform_int_distribution
#include <string>  // string


#include "../include/numMixer.h"


std::mt19937 numMixer::_eng(time(0));


numMixer::numMixer():
	_evenValid(true),
	_oddValid(true),
	_stateChangeCount(0),
	_countDown(0),
	_dataset(0),
	_controllerState(MIX)
{
	// generate valid dataset
	const int SIZE = 100;
	_dataset.resize(SIZE);
	for (int i = 0; i < SIZE; ++i) {
		_dataset[i] = i + 1;
	}

	// calc max ping count
	const int LOWER_BOUND = 10;
	const int UPPER_BOUND = 20;
	std::uniform_int_distribution<> distr(LOWER_BOUND, UPPER_BOUND);
	_countDown = distr(_eng);
}


numMixer::numMixer(std::vector<int> dataset):
	_evenValid(false),
	_oddValid(false),
	_stateChangeCount(0),
	_countDown(0),
	_dataset(0),
	_controllerState(MIX)
{
	// copy dataset
	_dataset = dataset;

	// validate dataset
	for (auto& val : _dataset) {
		if (val % 2) {
			_oddValid = true;
		} else {
			_evenValid = true;
		}
	}
	
	// calc max ping count
	const int LOWER_BOUND = 10;
	const int UPPER_BOUND = 20;
	std::uniform_int_distribution<> distr(LOWER_BOUND, UPPER_BOUND);
	_countDown = distr(_eng);
}


numMixer::~numMixer()
{
}


bool numMixer::ping(std::vector<int>& returnValues)
{
	if (isActive() && checkStateValid()) {
		for (auto& val : returnValues) {
			val = genRandNum();
		}
		--_countDown;
		return true;
	} else {
		return false;
	}
}


std::string numMixer::getControllerStateName() const
{
	switch (_controllerState) {
		case MIX:
			return "MIX";
		case EVEN:
			return "EVEN";
		case ODD:
			return "ODD";
		default:
			return "UNKNOWN";
	}
}


void numMixer::setControllerState(OutputController state)
{
	if (getControllerState() != state) {
		_controllerState = state;
		++_stateChangeCount;
	}
}


int numMixer::genRandNum()
{
	int upperBound = _dataset.size() - 1;
	std::uniform_int_distribution<> distr(0, upperBound);
	int i = distr(_eng);

	switch (_controllerState) {
		case MIX:
			return _dataset[i];
		case EVEN:
			while (_dataset[i] % 2 != 0) {
				i = distr(_eng);
			}
			return _dataset[i];
		case ODD:
			while (_dataset[i] % 2 != 1) {
				i = distr(_eng);
			}
			return _dataset[i];
		default:
			return 0;
	}
}


bool numMixer::checkStateValid() const
{
	switch (_controllerState) {
		case MIX:
			return true;
		case EVEN:
			return _evenValid;
		case ODD:
			return _oddValid;
		default:
			return false;
	}
}