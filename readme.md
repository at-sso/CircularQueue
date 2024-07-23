# Circular Queue in C++

This project implements a circular queue (also known as a circular buffer or ring buffer) in C++.

## Index

- [Circular Queue in C++](#circular-queue-in-c)
  - [Index](#index)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Running the Program](#running-the-program)
    - [Using the Program](#using-the-program)
  - [Code Explanation](#code-explanation)
    - [CircularQueue Class](#circularqueue-class)
      - [Methods](#methods)
    - [Main Function](#main-function)
  - [Examples](#examples)
  - [License](#license)

## Features

- Insert elements into the queue.
- Remove elements from the queue.
- Display the current state of the queue.
- Handle edge cases such as queue full and queue empty.

## Getting Started

### Running the Program

1. Clone the repository or download the source code.
2. Open a terminal and navigate to the directory containing the source code.
3. Compile and run the program using a C++ compiler:

   ```bash
   g++ -std=c++20 -I src main.cpp -o main.exe && ./main
   ```

### Using the Program

Upon running the program, you will see a menu with the following options:

1. Insert element
2. Remove element
3. Display queue state
4. Exit

Choose an option by entering the corresponding number and following the prompts.

## Code Explanation

### CircularQueue Class

- `int arrBuffer[_ARRAY_LIMIT];`: Array to store the elements of the queue.
- `int frontValue;`: Index of the front of the queue.
- `int finalValue;`: Index of the rear of the queue.
- `int arrCount;`: Number of elements currently in the queue.

#### Methods

- `CircularQueue()`: Constructor to initialize the queue.
- `bool isFull()`: Check if the queue is full.
- `bool isEmpty()`: Check if the queue is empty.
- `void insert(int element)`: Insert an element into the queue.
- `void del()`: Remove an element from the queue.
- `void debug()`: Display the current state of the queue.

### Main Function

The `main` function contains a loop to display the menu and handle user input for performing operations on the circular queue.

## Examples

```bash
1. Insert element
2. Remove element
0. Exit
> 1
Enter the element to insert: 10
```

```bash
1. Insert element
2. Remove element
0. Exit
> -1
Queue state: 10
Front: 0
Rear: 0
```

```bash
1. Insert element
2. Remove element
0. Exit
Choose an option: 0
bye bye!
```

## License

This project is licensed under the MIT License - see the [license](./license) file for details.
