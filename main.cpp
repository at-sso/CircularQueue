#include "src/arrhandler.hh"
#include <cstdint>
#include <iostream>
#include <string>

using std::cout, std::cin;

CircularQueue q;

int main() {
	// Element to insert into the class.
	int16_t element = 0;
	// Selected option in the main menu.
	int16_t option = 0;

	do {
		// "Clears" the screen.
		cout << "\n\x1B[2J\x1B[H";

		cout << ( char[] )
			"Choose an option.\n"
			"1. Insert element\n"
			"2. Delete element\n"
			"3. Exit\n"
			<< q.status() <<
			"\n> "
			<< flush;
		cin >> option;
		cout << "\n\n";

		switch( option ) {
		case -1:
			q.debug();
			break;
		case 1:
			cout << "Enter the element to insert\n> " << flush;
			cin >> element;
			q.insert(element);
			break;
		case 2:
			q.del();
			break;
		case 3:
			cout << "bye bye!" << endl;
			break;
		default:
			cout << "Invalid option. Please try again!" << flush;
		}
	} while( option != 4 );

	return 0;
}
