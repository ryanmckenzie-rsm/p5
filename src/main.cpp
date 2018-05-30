// AUTHOR: Ryan McKenzie
// FILENAME: main.cpp
// DATE: May 29, 2018
// REVISION HISTORY: v1.0.0
// PLATFORM: GCC v7.1.0

// DESCRIPTION:
// * Uses templates to abstract a lot of the overloaded operators.
// * Mixer objects are instantiated outside the method and then passed in to
// be evaluated.
// * Prints the contents of mixer objects, then performs comparisons (==),
// relations (<), and arithmetic on the passed mixer objects.
// * Since multiMix supports mixed-mode arithmetic, a special function will
// demonstrate its capabilities.
// * Prints all output to a file "log.txt".

// ASSUMPTIONS:
// * All mixer objects support the following operators:
// * ==, !=
// * <, >, <=, >=
// * +, +=
// * multiMix supports mixed-mode addition with numMixers.


#include <cmath>  // floor, ceil
#include <ctime>  // time
#include <stack>  // stack
#include <vector>  // vector
#include <fstream>  // ofstream
#include <ostream>  // endl
#include <random>  // mt19937, uniform_int_distribution
#include <string>  // string, to_string


#include "../include/dubMix.h"
#include "../include/multiMix.h"
#include "../include/numMixer.h"


template <typename T>
struct Mixer
{
	Mixer() {}
	Mixer(T objT, std::string nameT): obj(objT), name(nameT) {}
	T obj;
	std::string name;
};
// Description:
// * Abstracts the various mixer classes so they can be templated.
// * "obj" is the mixer object.
// * "name" is the name of the object.


void writeHeader(std::vector<std::string> vec, std::ofstream& ofs);

int genRandNum();

std::vector<int> genDataset();

void printVec(const std::vector<int>& vec, std::ofstream& ofs);

template <typename T>
void testEq(Mixer<T>& lhs, Mixer<T>& rhs, std::ofstream& ofs);

template <typename T>
void testRel(Mixer<T>& lhs, Mixer<T>& rhs, std::ofstream& ofs);

template <typename T>
void testMixers(Mixer<T>& mixer1,
				Mixer<T>& mixer2,
				std::string className,
				std::ofstream& ofs);

void testMultiMixersMixArith(std::ofstream& ofs);

void printStats(const numMixer& nm,
				std::string nmName,
				std::ofstream& ofs,
				bool verbose = true);

void printStats(const dubMix& dm, std::string dmName, std::ofstream& ofs);

void printStats(const multiMix& mm, std::string mmName, std::ofstream& ofs);


inline const std::string toString(const bool b)
{
	return b ? "True" : "False";
}


int main()
{
	const char* FILE_NAME = "log.txt";
	std::ofstream ofs;
	ofs.open(FILE_NAME);

	Mixer<numMixer> nm1(numMixer(genDataset()), "nm1");
	Mixer<numMixer> nm2(numMixer(genDataset()), "nm2");
	testMixers(nm1, nm2, "numMixer", ofs);
	ofs << std::endl;

	Mixer<dubMix> dm1;
	dm1.name = "dm1";
	Mixer<dubMix> dm2;
	dm2.name = "dm2";
	testMixers(dm1, dm2, "dubMix", ofs);
	ofs << std::endl;

	Mixer<multiMix> mm1;
	mm1.obj.addNumMixers(1);
	mm1.name = "mm1";
	Mixer<multiMix> mm2;
	mm2.obj.addNumMixers(2);
	mm2.name = "mm2";
	testMixers(mm1, mm2, "multiMix", ofs);
	ofs << std::endl;

	testMultiMixersMixArith(ofs);

	ofs.close();
	return 0;
}
// Description:
// * Opens a log file to write output.
// * 
// * Closes the log file.


void writeHeader(std::vector<std::string> vec, std::ofstream& ofs)
{
	const int WIDTH = 26;
	std::string border(WIDTH, '#');
	border = "#" + border + "#";
	std::string padding(WIDTH, ' ');
	padding = "#" + padding + "#";

	ofs << border << std::endl;
	ofs << padding << std::endl;

	double dynWidth;
	int widthLeft;
	int widthRight;
	for (auto header : vec) {
		dynWidth = WIDTH - header.length();
		widthLeft = std::floor(dynWidth / 2);
		widthRight = std::ceil(dynWidth / 2);
		std::string headerLeft(widthLeft, ' ');
		std::string headerRight(widthRight, ' ');
		std::string headerLine = "#" + headerLeft + header + headerRight + "#";
		ofs << headerLine << std::endl;
	}

	ofs << padding << std::endl;
	ofs << border << std::endl;
}
// Description:
// * Writes a header using the ofstream object:
// ############################
// #                          #
// #          header          #
// #         subtext          #
// #                          #
// ############################
//
// Preconditions:
// * Supplied vector strings must be short enough to fit within header box.


int genRandNum()
{
	int MIN_ROLL = 2;
	int MAX_ROLL = 100;
	static std::mt19937 eng(time(0));
	std::uniform_int_distribution<> distr(MIN_ROLL, MAX_ROLL);
	return distr(eng);
}
// Description:
// * Returns a random number between and including the MIN_ROLL and MAX_ROLL.


std::vector<int> genDataset()
{
	const int SIZE = 10;
	std::vector<int> vec(SIZE);
	for (auto& val : vec) {
		val = genRandNum();
	}
	return vec;
}
// Description:
// * Generates of random vector with values from genRandNum() of size = "SIZE".


void printVec(const std::vector<int>& vec, std::ofstream& ofs)
{
	for (auto val : vec) {
		ofs << val << std::endl;
	}
}
// Description:
// * Writes the contents of the vector to the file.


template <typename T>
void testEq(Mixer<T>& lhs, Mixer<T>& rhs, std::ofstream& ofs)
{
	ofs << lhs.name << " and " << rhs.name << " are ";
	if (lhs.obj == rhs.obj) {
		ofs << "the same";
	} else {
		ofs << "different";
	}
	ofs << std::endl;
}
// Description:
// * Performs tests of equality on the passed Mixer objects, and records the
// results to the file.


template <typename T>
void testRel(Mixer<T>& lhs, Mixer<T>& rhs, std::ofstream& ofs)
{
	ofs << lhs.name << " is ";
	if (lhs.obj < rhs.obj) {
		ofs << "less than ";
	} else if (lhs.obj > rhs.obj) {
		ofs << "greater than ";
	} else {
		ofs << "not comparable to ";
	}
	ofs << rhs.name << std::endl;
}
// Description:
// * Performs relational algebra on the passed Mixer objects.
// * Relations for which "<" and ">" fails are not necessarily the same (==)
// objects, as their relational algebra isn't tied to their definition of
// equality.


template <typename T>
void testMixers(Mixer<T>& mixer1,
				Mixer<T>& mixer2,
				std::string className,
				std::ofstream& ofs)
{
	writeHeader({className, "Overloaded Operators"}, ofs);
	ofs << std::endl;

	Mixer<T> mixer2Copy = mixer2;
	mixer2Copy.name += "Copy";

	printStats(mixer1.obj, mixer1.name, ofs);
	ofs << std::endl;
	printStats(mixer2.obj, mixer2.name, ofs);
	ofs << std::endl;
	printStats(mixer2Copy.obj, mixer2Copy.name, ofs);
	ofs << std::endl;

	testEq(mixer1, mixer2, ofs);
	testEq(mixer2, mixer2Copy, ofs);
	testRel(mixer1, mixer2, ofs);
	ofs << std::endl;

	Mixer<T> mixer3(mixer1.obj + mixer2.obj, mixer1.name + " + " + mixer2.name);
	printStats(mixer3.obj, mixer3.name, ofs);
}
// Description:
// * Begins by making a copy to demonstrate the "==" operator.
// * Next displays the contents of all Mixer objects, for verification.
// * Then performs comparisons on the Mixers and prints the results.
// * Finally performs an addition operation and prints the results.


void testMultiMixersMixArith(std::ofstream& ofs)
{
	writeHeader({"multiMix", "Mixed-Mode Arithmetic"}, ofs);
	ofs << std::endl;

	multiMix mm1;
	numMixer nm1(genDataset());

	printStats(mm1, "mm1", ofs);
	ofs << std::endl;
	printStats(nm1, "nm1", ofs, false);
	ofs << std::endl;

	mm1 += nm1;
	printStats(mm1, "mm1 += nm1", ofs);
}
// Description:
// * Tests mixed-mode arithmetic for the multiMixer class.
// * Constructs an empty multiMixer and a numMixer adn prints their contents.
// * Then adds them together and prints the results.


void printStats(const numMixer& nm,
				std::string nmName,
				std::ofstream& ofs,
				bool verbose)
{
	ofs << "== \"" << nmName << "\" STATS ==\n";
	ofs << "stateChangeCount: " << nm.stateChangeCount() << std::endl;
	ofs << "countDown: " << nm.countDown() << std::endl;
	ofs << "evenValid: " << toString(nm.evenValid()) << std::endl;
	ofs << "oddValid: " << toString(nm.oddValid()) << std::endl;
	if (verbose) {
		ofs << "dataset: \n";
		printVec(nm.dataset(), ofs);
	}
	ofs << "controllerState: " << nm.getControllerStateName() << std::endl;
}
// Description:
// * Prints the states of the members variables within the given numMixer
// object.


void printStats(const dubMix& dm, std::string dmName, std::ofstream& ofs)
{
	const int SIZE = 28;
	std::string border(SIZE, '=');
	ofs << border << std::endl;
	ofs << "== \"" << dmName << "\" STATS ==\n";
	ofs << "ctl: " << dm.getCtl() << std::endl;
	ofs << std::endl;
	printStats(dm.x(), "x", ofs, false);
	ofs << std::endl;
	printStats(dm.z(), "z", ofs, false);
	ofs << border << std::endl;
}
// Description:
// * Prints the states of the member variables within the given dubMixer object.


void printStats(const multiMix& mm, std::string mmName, std::ofstream& ofs)
{
	const int SIZE = 28;
	std::string border(SIZE, '=');
	ofs << border << std::endl;
	ofs << "== \"" << mmName << "\" STATS ==\n";
	ofs << "Stack size: " << mm.getNumMixerCount() << std::endl;
	std::stack<numMixer> stackCopy = mm.numMixerStack();
	std::string index;
	while (!stackCopy.empty()) {
		ofs << std::endl;
		index = "index [" + std::to_string(stackCopy.size() - 1) + "]";
		printStats(stackCopy.top(), index, ofs, false);
		stackCopy.pop();
	}
	ofs << border << std::endl;
}
// Description:
// * Prints the states of the member variables within the given multiMixer
// object.