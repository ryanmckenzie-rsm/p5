// AUTHOR: Ryan McKenzie
// FILENAME: numMixer.h
// DATE: May 29, 2018
// REVISION HISTORY: v4.0.0
// PLATFORM: GCC v7.1.0

// DESCRIPTION:
// * This class outputs a random set of integers selected either from user
// seeded input, or from an auto-generated set.
// * This class can be placed into an illegal state should the user provide a
// vector of size zero on object creation.
// * Or should the user request a parity they did not provide (i.e. even
// numbers when they did not provide even numbers).
// * This class is anticipated to be used as a data sink.

// ASSUMPTIONS: 
// * This class has one hard requirement for correct usage: the user MUST
// provide a vector of size > 0 or else the program can fail. Otherwise, this
// class protects against invalid states (i.e. requesting even/odd numbers when
// the user hasn't provided any).
// * This class will build its dataset either from a user provided vector, or
// from a pre-defined, valid vector. The vector must be size > 0, and should
// have even and odd numbers if the user wishes to ping them.
// * The user can change the output controller via a public mutator.
// * The state change counter will only increment should the state ACTUALLY
// change.
// * To ping the numMixer, the user must provide a vector of the size they
// want returned. The class protects against vectors of size = 0. Pinging the
// numMixer can fail (return false) in two cases:
//   1. The numMixer is inactive.
//   2. The user has requested even/odd integers when they did not provide any.
// * The numMixer returns integers by randomly selecting them from the set
// provided at object creation. It randomly selects indexes from the vector
// until it finds a valid number (e.g. an even number if the controller is set
// to even) and stores them in a user provided vector.
// * The "active" state of the numMixer is tracked via a counter which is
// randomly set at object creation. It is decremented everytime the user
// successfully pings the numMixer.
// * The user can check whether the numMixer is active via a public accessor
// which returns true when the counter > 0.
// * Comparison (==) operators are supported.
// * Comparison is performed on all data members.
// * Relational (<) operators are supported.
// * Relations are assessed on the countdown.
// * Addition (+) operators are supported.
// * Addition is performed on all members except the state controller.
// * The dataset of the right hand side is appended to the end of the left
// hand side.


#ifndef numMixer_INCLUDED
#define numMixer_INCLUDED


#include <vector>  // vector
#include <random>  // mt19937
#include <string>  // string


class numMixer
{
	public:
		// Types

		enum OutputController { MIX, EVEN, ODD };
		// Valid states the output controller can be set to.


		// Constructors

		numMixer();
		// Description:
		// * The no-arg constructor creates a dataset to choose from of values
		// 1-100.
		// * Calls for integers of any parity are valid.
		// * The numMixer can be called a randomly selected amount of times,
		// 10-20.
		// * The output controller defaults to "Mix".
		// 
		// Postconditions:
		// * The controller state is set to "Mix".
		// * The state change count is set to 0.
		// * The dataset is intialized with integers 1-100.
		// * The countdown is randomly set to 10-20.
		// * Calls for integers of even parity are valid.
		// * Calls for integers of odd parity are valid.

		explicit numMixer(std::vector<int> dataset);
		// Description:
		// * This constructor creates a dataset using "dataset".
		// * The validity of various parity calls are evaluated on the dataset
		// provided.
		// * The numMixer can be called a randomly selected amount of times,
		// 10-20, before transitioning to inactive.
		// * The output controller defaults to "Mix".
		//
		// Preconditions:
		// * "dataset" must be of size > 0.
		// * "dataset" must contain integers of a parity the user wishes to
		// request.
		//
		// Postconditions:
		// * The controller state is set to "Mix".
		// * The state change count is set to 0.
		// * The dataset is intialized with "dataset".
		// * The countdown is randomly set to 10-20.
		// * Calls for integers of even parity may or may not be valid.
		// * Calls for integers of odd parity may or may not be valid.


		// Constructors

		virtual ~numMixer();
		// Description:
		// * Currently just a placeholder, does nothing.


		// Functionality

		virtual bool ping(std::vector<int>& returnValues);
		// Description:
		// * Stores a random selection of integers from the dataset into
		// "returnValues".
		// * The amount of integers stored is equal to the size of
		// "returnValues".
		// * The parity of the integers is determined by the controller state.
		// * Returns true if the pinged numMixer is active and the requested
		// parity exists within the dataset.
		// * Returns false if the numMixer is inactive, or if the requested
		// parity does not exist within the dataset.
		//
		// Preconditions:
		// * The numMixer must be in an active state.
		// * The user must provide a vector of size > 0.
		// * The user must have provided integers of the requested parity at
		// object creation.
		//
		// Postconditions:
		// * If the call succeeds, the countdown is decremented.


		// Accessors

		virtual bool isActive() const;
		// Description:
		// * Returns whether the numMixer is still active.
		// * Returns true if the numMixer is active.
		// * Returns false if the numMixer is inactive.

		int stateChangeCount() const;
		// Description:
		// * Returns how many times the output controller has changed state.

		int countDown() const;
		// Description:
		// * Returns the countdown.

		std::mt19937 eng() const;
		// Description:
		// * Returns the rng.

		bool evenValid() const;
		// Description:
		// * Returns whether pings for even numbers are valid.

		bool oddValid() const;
		// Description:
		// * Returns whether pings for odd numbers are valid.

		const std::vector<int>& dataset() const;
		// Description:
		// * Returns the dataset.

		OutputController getControllerState() const;
		// Description:
		// * Returns the state of the OutputController.

		std::string getControllerStateName() const;
		// Description:
		// * Returns the name of the controller state, for templating purposes.


		// Mutators

		void setControllerState(OutputController state);
		// Description:
		// * Changes the output controller to "state" if it is not already set.
		//
		// Preconditions:
		// * The output controller should be set to a state that is different
		// than "state".
		//
		// Postconditions:
		// * The output controller changes state.


		// Comparison Operators

		friend bool operator==(const numMixer& lhs, const numMixer& rhs);  // 1
		friend bool operator!=(const numMixer& lhs, const numMixer& rhs);  // 2
		// Description (1-2):
		// * Performs equality checks on all data members.

		friend bool operator<(const numMixer& lhs, const numMixer& rhs);  // 3
		friend bool operator>(const numMixer& lhs, const numMixer& rhs);  // 4
		friend bool operator<=(const numMixer& lhs, const numMixer& rhs);  // 5
		friend bool operator>=(const numMixer& lhs, const numMixer& rhs);  // 6
		// Description (3-6):
		// * Performs a relational check on the countdown.

		// Arithmetic Operators

		friend numMixer operator+(numMixer lhs, const numMixer& rhs);  // 1
		numMixer& operator+=(const numMixer& obj);  // 2
		// Description (1-2):
		// * Adds all data members together except for the controller state.
		// * Appends rhs._dataset onto the end of _dataset.
		// 
		// Postconditions:
		// * _stateChangeCount may have changed.
		// * _countDown may have changed.
		// * _evenValid may have changed.
		// * _oddValid may have changed.
		// * _dataset may have changed.


	protected:
		// Utility

		int genRandNum();
		// Description:
		// * Selects random values from the dataset and returns them depending
		// on the state of the output controller.
		//
		// Preconditions:
		// * The dataset must be of size > 0.
		// * The dataset must contain numbers of the requested parity.
		
		bool checkStateValid() const;
		// Description:
		// * Checks whether a ping call is valid depending on the output
		// controller state.
		// * Returns true if the call is valid.
		// * Returns false if the call is invalid.


		// Members

		int _stateChangeCount;
		// Stores how many times the OutputController has changed state.

		int _countDown;
		// Determines how many times the numMixer can be pinged.


	private:
		// Members

		static std::mt19937 _eng;
		// Used to seed the dataset, countDown, and randomly select values from
		// the dataset.

		bool _evenValid;
		// Determines whether pings for even values can be evaluated.

		bool _oddValid;
		// Determines whether pings for odd values can be evaluated.

		std::vector<int> _dataset;
		// Stores the values to be randomly returned in pings.

		OutputController _controllerState;
		// Determines the parity of the integers to be returned.
};


inline bool numMixer::isActive() const
{
	return (_countDown > 0);
}


inline int numMixer::stateChangeCount() const
{
	return _stateChangeCount;
}


inline int numMixer::countDown() const
{
	return _countDown;
}


inline std::mt19937 numMixer::eng() const
{
	return _eng;
}


inline bool numMixer::evenValid() const
{
	return _evenValid;
}


inline bool numMixer::oddValid() const
{
	return _oddValid;
}


inline const std::vector<int>& numMixer::dataset() const
{
	return _dataset;
}


inline numMixer::OutputController numMixer::getControllerState() const
{
	return _controllerState;
}


inline bool operator==(const numMixer& lhs, const numMixer& rhs)
{
	return (lhs._stateChangeCount == rhs._stateChangeCount &&
			lhs._countDown == rhs._countDown &&
			lhs._evenValid == rhs._evenValid &&
			lhs._oddValid == rhs._oddValid &&
			lhs._dataset == rhs._dataset &&
			lhs._controllerState == rhs._controllerState);
}


inline bool operator!=(const numMixer& lhs, const numMixer& rhs)
{
	return !operator==(lhs, rhs);
}


inline bool operator<(const numMixer& lhs, const numMixer& rhs)
{
	return (lhs._countDown < rhs._countDown);
}


inline bool operator>(const numMixer& lhs, const numMixer& rhs)
{
	return operator<(rhs, lhs);
}


inline bool operator<=(const numMixer& lhs, const numMixer& rhs)
{
	return !operator>(lhs, rhs);
}


inline bool operator>=(const numMixer& lhs, const numMixer& rhs)
{
	return !operator<(lhs, rhs);
}


inline numMixer operator+(numMixer lhs, const numMixer& rhs)
{
	lhs += rhs;
	return lhs;
}


inline numMixer& numMixer::operator+=(const numMixer& obj)
{
	_stateChangeCount += obj._stateChangeCount;
	_countDown += obj._countDown;
	_evenValid = (_evenValid || obj._evenValid);
	_oddValid = (_oddValid || obj._oddValid);
	_dataset.insert(_dataset.end(), obj._dataset.begin(), obj._dataset.end());
	_dataset.shrink_to_fit();
	return *this;
}


#endif