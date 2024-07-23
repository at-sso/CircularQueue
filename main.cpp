#include "src/arrhandler.hh"
#include <cstdint>
#include <iostream>
#include <string>

#define doShowExtraMessage showExtraMessage = true
#define doNotShowExtraMessage showExtraMessage = false

static constexpr uint64_t SIZE = 4096ull;

using std::cout, std::cin;
using std::string;

CircularQueue q;
// In-menu message.
string extraMessage = "";
// Do you want an extra message? Maybe... I don't know, it's actually on you.
static bool showExtraMessage;

int main() {
	// Element to insert into the class.
	int16_t element = 0;
	// Selected option in the main menu.
	int16_t option = 0;

	do {
		// "Clears" the screen. How? https://en.wikipedia.org/wiki/ANSI_escape_code
		cout << "\n\x1B[2J\x1B[H";

		cout <<
			"Choose an option.\n"
			"1. Insert element.\n"
			"2. Delete the first element.\n"
			"3. Help.\n"
			"0. Exit.\n"
			<< q.status()
			<< ( showExtraMessage ? extraMessage : "\n" )
			<< "\n> " << flush;
		cin >> option;

		cout << "\n";

		switch( option ) {
		default: // Invalid option.
			doShowExtraMessage;
			extraMessage = "\nInvalid option! Please try again.";
			break;
		case 0: // Exit option.
			cout << "Bye bye!" << endl;
			break;
		case -1: // Debug option (not shown in the menu).
			doNotShowExtraMessage;
			q.debug();
			break;
		case 1: // Insert element option.
			doNotShowExtraMessage;
			cout << "Enter the element to insert\n> " << flush;
			cin >> element;
			q.insert(element);
			break;
		case 2: // Delete element option.
			doNotShowExtraMessage;
			q.del();
			break;
		case 3: // Help message.
			doShowExtraMessage;
			extraMessage =
				"- Initialization: Sets up an empty queue with 'frontValue', 'finalValue', and 'arrCount'.\n"
				"- Insertion: Adds elements to the position indicated by 'finalValue', wraps around if needed, and increments 'arrCount'.\n"
				"- Deletion : Removes elements from the position indicated by 'frontValue', wraps around if needed, and decrements 'arrCount'.\n"
				"- Status Message : Provides a string representation of the queue's current state.";
		}
	} while( option != 0 );
	return 0;
}
