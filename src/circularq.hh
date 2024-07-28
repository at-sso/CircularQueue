/**
 * @file main.cpp
 * @author Zperk
 * @brief Circular Array implementation.
 * @version 1.0.1
 * @date 2024-07-23
 *
 * @copyright Copyright (c) zperk 2024
 *
 */


#pragma once

#include <cstdint>
#include <iostream>
#include <string>

using std::cout, std::endl, std::flush;
using std::string, std::to_string;

// A constant modulo limit.
static constexpr int16_t _ARRAY_LIMIT = 8;

/**
 * @class CircularQueue
 * @brief A circular queue implementation.
 *
 * This class implements a circular queue using a fixed-size array buffer. It provides
 * methods to insert and delete elements, check if the queue is full or empty, and
 * format a status message for debugging purposes.
 */
class CircularQueue {
private:
	int32_t arrBuffer[_ARRAY_LIMIT]; /// < The array buffer for the queue elements.
	int32_t frontValue; /// < The index of the front element in the queue.
	int32_t finalValue; /// < The index of the final element in the queue.
	int32_t arrCount; /// < The number of elements in the queue.
	string statusMsg = ""; /// < The status message for debugging.
	bool showBufferStatus = true; /// < Flag to show the status of the array buffer.


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

		// Start the status message with an empty string
		this->statusMsg = "";

		// If false, only show `statusMsg + local s`.
		if( showBufferStatus ) {
			// Start with the base status message
			this->statusMsg += "Queue status: [ ";

			for( int32_t j = 0, i = this->frontValue; j < this->arrCount; j++, i = ( i + 1 ) % _ARRAY_LIMIT ) {
				this->statusMsg += to_string(this->arrBuffer[i]);
				if( j < this->arrCount - 1 )
					this->statusMsg += ", ";
			}

			// If the queue is empty, add "empty" to the status message
			if( this->isQEmpty() )
				this->statusMsg += "empty ]\n";
			else
				this->statusMsg += " ]\n";
		}

		// Close the status message and append the optional string
		this->statusMsg += s;
	}

public:
	/**
	 * @brief Constructs a new CircularQueue object.
	 *
	 * Initializes the queue to be empty, with all buffer elements set to 0.
	 */
	CircularQueue() {
		this->frontValue = 0;
		this->finalValue = -1; // Don't use INT32_MAX
		this->arrCount = 0;
		for( int16_t i = 0; i < _ARRAY_LIMIT; i++ ) {
			arrBuffer[i] = 0; // Initialize all elements of the `arrBuffer` array to 0
		}
		// Once everything is initialized, format the status message.
		this->formatStatus();
	}

	/**
	 * @brief Gets the status message.
	 *
	 * @return The current status message.
	 */
	string status() const noexcept {
		return this->statusMsg;
	}

	/**
	 * @brief Formats and updates the status message of the queue.
	 *
	 * This function updates the `statusMsg` member of the class to reflect the current state
	 * of the queue. The status message is formatted to show all elements in the buffer queue.
	 */
	void updateStatus() noexcept {
		this->formatStatus(); // This is kinda an overload...?
	}

	/**
	 * @brief Checks if the queue is full.
	 *
	 * @return `true` if the queue is full, `false` otherwise.
	 */
	bool isQFull() const noexcept {
		return this->arrCount == _ARRAY_LIMIT;
	}

	/**
	 * @brief Checks if the queue is empty.
	 *
	 * @return `true` if the queue is empty, `false` otherwise.
	 */
	bool isQEmpty() const noexcept {
		return this->arrCount == 0;
	}

	/**
	 * @brief Inserts an element into the queue.
	 *
	 * @param element The element to insert.
	 */
	void insert(const int16_t element) noexcept {
		if( this->isQFull() ) {
			this->formatStatus("Insertion error: The queue is full.\n");
			return;
		}
		this->finalValue = ( this->finalValue + 1 ) % _ARRAY_LIMIT;
		this->arrBuffer[this->finalValue] = element;
		this->arrCount++;
		this->formatStatus();
	}

	/**
	 * @brief Deletes the front element from the queue.
	 */
	void del() noexcept {
		if( isQEmpty() ) {
			this->formatStatus("Deletion error: The queue is empty.\n");
			return;
		}
		this->frontValue = ( this->frontValue + 1 ) % _ARRAY_LIMIT;
		this->arrCount--;
		this->formatStatus();
	}

	/**
	 * @brief Deletes elements from the queue up to a specified position.
	 *
	 * @param uPos The position up to which elements should be deleted (1-based index).
	 */
	void del(const int16_t uPos) noexcept {
		// Convert user position (1-based) to index (0-based).
		int16_t index = uPos - 1;

		if( isQEmpty() ) {
			this->formatStatus("Deletion error: The queue is empty.\n");
			return;
		}

		// Check if the deleteIndex is within the valid range.
		if( index < 0 || index >= this->arrCount ) {
			this->formatStatus("Deletion error: Invalid position.\n");
			return;
		}

		// Calculate the number of elements to delete
		int16_t elementsToDelete = index + 1;

		// Update frontValue and arrCount accordingly
		this->frontValue = ( this->frontValue + elementsToDelete ) % _ARRAY_LIMIT;
		this->arrCount -= elementsToDelete;

		this->formatStatus();
	}

	/**
	 * @brief Formats and prints a debug message.
	 *
	 * If the queue is empty, a specific error message is shown. Otherwise,
	 * it prints the indices of the front and final elements.
	 */
	void debug() noexcept {
		if( isQEmpty() ) {
			this->formatStatus("Debug error: The arrCount is zero.\n");
			return;
		}
		this->formatStatus(
			"\nNOTE: These are the actual indexes."
			"\nfrontValue: " + to_string(this->frontValue) +
			"\nfinalValue: " + to_string(this->finalValue) + "\n"
		);
	}
};
