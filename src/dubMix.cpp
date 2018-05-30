// AUTHOR: Ryan McKenzie
// FILENAME: dubMix.cpp
// DATE: May 29, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v7.1.0

// Implementation Invariant:
// * "_x" is set to even.
// * "_z" is set to odd.
// * ping returns values depending on "_ctl".
// * Client decides when to set "_ctl".
// * In case of "_ctl" == 4, even/odd vectors are purged of duplicates, then
// merged.


#include <vector>  // vector


#include "../include/dubMix.h"
#include "../include/numMixer.h"


dubMix::dubMix():
	_ctl(3),
	_x(),
	_z()
{
	_x.setControllerState(numMixer::EVEN);
	_z.setControllerState(numMixer::ODD);
}


dubMix::~dubMix()
{
}


std::vector<int> dubMix::ping()
{
	const unsigned int SIZE = 10;
	switch (_ctl) {
		case 1:
			return ctl1(SIZE);
		case 2:
			return ctl2(SIZE);
		case 3:
			return ctl3(SIZE);
		case 4:
			return ctl4(SIZE);
		default:
			return std::vector<int> (0);
	}
}


void dubMix::setCtl(unsigned int val)
{
	_ctl = val;
}


void dubMix::purgeDuplicates(std::vector<int>& arr)
{
	int newSize = arr.size();
	for (int i = arr.size() - 1; i >= 1; --i) {
		for (int j = i - 1; j >= 0; --j) {
			if (arr[j] == arr[i]) {
				arr[i] = arr[newSize - 1];
				--newSize;
				break;
			}
		}
	}
	arr.resize(newSize);
}


std::vector<int> dubMix::ctl1(unsigned int size)
{
	std::vector<int> xOut(size);
	_x.ping(xOut);
	return xOut;
}


std::vector<int> dubMix::ctl2(unsigned int size)
{
	std::vector<int> zOut(size);
	_z.ping(zOut);
	return zOut;
}


std::vector<int> dubMix::ctl3(unsigned int size)
{
	std::vector<int> xOut(size);
	_x.ping(xOut);

	std::vector<int> zOut(size);
	_z.ping(zOut);

	std::vector<int> mixedOut(2 * size);
	for (int i = 0; i < 2 * size; ++i) {
		if (i % 2 == 0) {
			mixedOut[i] = xOut[i / 2];
		} else {
			mixedOut[i] = zOut[i / 2];
		}
	}

	return mixedOut;
}


std::vector<int> dubMix::ctl4(unsigned int size)
{
	std::vector<int> xOut(size);
	_x.ping(xOut);
	purgeDuplicates(xOut);

	std::vector<int> zOut(size);
	_z.ping(zOut);
	purgeDuplicates(zOut);

	std::vector<int> mixedOut(xOut.size() + zOut.size());
	for (int i = 0; i < xOut.size(); ++i) {
		mixedOut[i] = xOut[i];
	}
	for (int i = 0; i < zOut.size(); ++i) {
		mixedOut[i + xOut.size()] = zOut[i];
	}

	return mixedOut;
}