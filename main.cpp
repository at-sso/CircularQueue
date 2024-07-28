/**
 * @file main.cpp
 * @author Zperk
 * @brief Examples on how to use the circularq.hh header.
 * @version 1.0.0
 * @date 2024-07-28
 *
 * @copyright Copyright (c) zperk 2024
 *
 */

#include "src/circularq.hh"
#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <string>

#define doShowExtraMessage showExtraStatus = true
#define doNotShowExtraMessage showExtraStatus = false
#define breakCase break

using std::cout, std::cin;
using std::string;

CircularQueue q;
// In-menu status message.
static string extraStatus = "";
// Do you want an extra status message? Maybe... I don't know, it's actually on you.
static bool showExtraStatus = false;
static bool mainLoop = true;

int main() {
	// Element to insert into the class.
	int16_t element = 0;
	// Selected option in the main menu.
	int16_t option = 0;

	/// Checks for errors in the stream buffer.
	constexpr auto checkStreamErr = [] {
		if( cin.fail() ) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			doShowExtraMessage;
			extraStatus = "Invalid input!\n";
			return true;
		}
		return false;
		};

	/// Show (or reload if needed) the main menu.
	constexpr auto showMainMenu = [](const string& s = "") {
		cout << "\n\x1B[2J\x1B[H" << // < "Clears" the screen.
			"Choose an option.\n"
			"1. Insert element.\n"
			"2. Delete the first element.\n"
			"3. Delete a range of elements.\n"
			"0. Exit.\n"
			<< q.status()
			<< ( showExtraStatus ? extraStatus : "" )
			<< s << "\n> " << flush;
		};

	// Main loop
	do {
		showMainMenu();
		cin >> option;
		if( checkStreamErr() ) continue;

		switch( option ) {
		default: // Invalid option.
			doShowExtraMessage;
			q.updateStatus();
			extraStatus = "Invalid option!\n";
			breakCase;
		case 0: // Exit option.
			cout << "Bye bye!" << endl;
			mainLoop = false;
			breakCase;
		case -1: // Debug option (not shown in the menu).
			doNotShowExtraMessage;
			q.debug();
			breakCase;
		case 1: // Insert element option.
			doNotShowExtraMessage;
			q.updateStatus();
			while( true ) {
				showMainMenu("Enter the element to insert.\n");
				cin >> element;
				if( checkStreamErr() ) continue; else {
					doNotShowExtraMessage;
					break;
				}
			}
			q.insert(element);
			breakCase;
		case 2: // Delete element option.
			doNotShowExtraMessage;
			q.del();
			breakCase;
		case 3: // Delete a range of elements.
			doNotShowExtraMessage;
			q.updateStatus();
			// The del() overload function can handle this scenario, but not this implementation.
			// When using a loop, we must check if the queue is empty before attempting a deletion.
			// Otherwise, you'll be printing an error message until your computer gets mad at you.
			if( q.isQEmpty() ) {
				doShowExtraMessage;
				extraStatus = "The queue is empty!\n";
				breakCase;
			}
			while( true ) {
				showMainMenu("Enter the queue index.\n");
				cin >> element;
				if( checkStreamErr() ) continue; else {
					doNotShowExtraMessage;
					q.del(element); break;
				}
			}
			breakCase;
		}
	} while( mainLoop );
	return 0;
}
