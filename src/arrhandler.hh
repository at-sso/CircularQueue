#pragma once

#include <cstdint>
#include <iostream>
#include <string>

using std::cout, std::endl, std::flush;
using std::string;

constexpr int16_t _LIMIT = 8;

class CircularQueue {
private:
	int32_t arrQ[_LIMIT];
	int32_t frontValue, finalValue, arrCount;
	string statusMsg = "";

public:
	CircularQueue() {
		this->frontValue = 0;
		this->finalValue = -1; // UINT32_MAX
		this->arrCount = 0;
		for( int16_t i = 0; i < _LIMIT; i++ ) {
			arrQ[i] = 0; // Initialize all elements of the `arr` array to 0
		}
	}

	// Get status message.
	string status() const noexcept {
		return this->statusMsg;
	}

	// Check if the `arrCount` value is equal to _LIMIT
	bool isQFull() const noexcept {
		return this->arrCount == _LIMIT;
	}

	// Check if the `arrCount` value is equal to `0` (empty).
	bool isQEmpty() const noexcept {
		return this->arrCount == 0;
	}

	// Insert an element into the `arr`.
	void insert(const int16_t element) noexcept {
		if( this->isQFull() ) {
			this->statusMsg = "Insertion error: The queue is full.";
			return;
		}
		this->finalValue = ( this->finalValue + 1 ) % _LIMIT;
		this->arrQ[this->finalValue] = element;
		this->arrCount++;
	}

	// Delete an element from the `arr`.
	void del() noexcept {
		if( isQEmpty() ) {
			this->statusMsg = "Deletion error: The queue is empty.";
			return;
		}
		this->frontValue = ( this->frontValue + 1 ) % _LIMIT;
		this->arrCount--;
	}

	void debug() noexcept {
		if( isQEmpty() ) {
			this->statusMsg = "Debug error: The arrCount is zero.";
			return;
		}

		cout << "Queue status: ";
		int32_t& i = this->frontValue;
		for( int32_t j = 0; j < this->arrCount; j++ ) {
			cout << this->arrQ[i] << " ";
			i = ( i + 1 ) % _LIMIT;
		}
		cout
			<< "\nfrontValue: " << this->frontValue
			<< "\nfinalValue: " << this->finalValue << "\n";
		cout.flush();
	}
};
