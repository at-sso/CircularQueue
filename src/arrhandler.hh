#pragma once

#include <cstdint>
#include <iostream>
#include <string>

using std::cout, std::endl, std::flush;
using std::string, std::to_string;

// A constant modulo limit.
static constexpr int16_t _ARRAY_LIMIT = 8;

class CircularQueue {
private:
	int32_t arrBuffer[_ARRAY_LIMIT];
	// Initial value of buffer -> [ 0, ... ]
	int32_t frontValue;
	// Final value of buffer -> [ ..., 0 ]
	int32_t finalValue; 
	// Number of elements in the array.
	int32_t arrCount;
	string statusMsg = ":D";

	/**!
	 * @brief Formats and updates the status message of the queue.
	 *
	 * This function updates the `statusMsg` member of the class to reflect the current state
	 * of the queue. The status message is formatted to show all elements in the buffer queue.
	 *
	 * @param s An optional string to append to the status message. Default is an empty string.
	 *
	 * @note This function does not throw exceptions.
	 */
	void formatStatus(const string& s = "") noexcept {
		// Reserve space in the string to avoid multiple reallocations
		this->statusMsg.reserve(100);

		// Start with the base status message
		this->statusMsg = "Queue status: [ ";

		for( int32_t j = 0, i = this->frontValue; j < this->arrCount; j++, i = ( i + 1 ) % _ARRAY_LIMIT ) {
			this->statusMsg += to_string(this->arrBuffer[i]);
			if( j < this->arrCount - 1 ) {
				this->statusMsg += ", ";
			}
		}

		// If the queue is empty, add "empty" to the status message
		if( this->isQEmpty() ) {
			this->statusMsg += "empty";
		}

		// Close the status message and append the optional string
		this->statusMsg += " ]\n" + s + "\n";
	}

public:
	CircularQueue() {
		this->frontValue = 0;
		this->finalValue = -1; // Don't use INT32_MAX
		this->arrCount = 0;
		for( int16_t i = 0; i < _ARRAY_LIMIT; i++ ) {
			arrBuffer[i] = 0; // Initialize all elements of the `arrBuffer` array to 0
		}
	}

	// Get status message.
	string status() const noexcept {
		return this->statusMsg;
	}

	// Check if the `arrCount` value is equal to _LIMIT
	bool isQFull() const noexcept {
		return this->arrCount == _ARRAY_LIMIT;
	}

	// Check if the `arrCount` value is equal to `0` (empty).
	bool isQEmpty() const noexcept {
		return this->arrCount == 0;
	}

	// Insert an element into the `arr`.
	void insert(const int16_t element) noexcept {
		if( this->isQFull() ) {
			this->formatStatus("Insertion error: The queue is full.");
			return;
		}
		this->finalValue = ( this->finalValue + 1 ) % _ARRAY_LIMIT;
		this->arrBuffer[this->finalValue] = element;
		this->arrCount++;
		this->formatStatus();
	}

	// Delete an element from the `arr`.
	void del() noexcept {
		if( isQEmpty() ) {
			this->formatStatus("Deletion error: The queue is empty.");
			return;
		}
		this->frontValue = ( this->frontValue + 1 ) % _ARRAY_LIMIT;
		this->arrCount--;
		this->formatStatus();
	}

	// Format debug message.
	void debug() noexcept {
		if( isQEmpty() ) {
			this->formatStatus("Debug error: The arrCount is zero.");
			return;
		}
		this->formatStatus(
			"\nfrontValue: " + to_string(this->frontValue) +
			"\nfinalValue: " + to_string(this->finalValue) + "\n"
		);
	}
};
