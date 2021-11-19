//=========================================================
//CS 433 Assignment 4
//Your names: Jasmine Meyer & Birhane Diarra
//File type: main.cpp
//Purpose: Main driver to simulate the 
//===========================================================
#include "buffer.h"
// buffer variables
buffer_item buffer[BUFFER_SIZE]; 
int front = 0;            //front of item
int back = 0;             //back of item
int count = 0;            //number of items

// PURPOSE: displays the current items in the buffer within bounds.
void display()
{
	int start = front;
	int end = back;
	int i = 0;
	int j = 0;

	std::cout << "[ ";

	for (i = start; j < count; i = (i + 1) % BUFFER_SIZE) {
		std::cout << buffer[i] << " ";
		j++;

		if (i == (end - 1))
			break;
	}

	if (count == 0) {
		std::cout << "empty ";
	}

	std::cout << "] \n";
}

// PURPOSE: checks if the buffer is full.
// RETURN: True = if count is equal to buffer size. False otherwise.
bool isFull() {
	return (count == BUFFER_SIZE);
}

// PURPOSE: checks if the buffer is empty.
// RETURN: True = if count is equal to 0. False otherwise.
bool isEmpty() {
	return (count == 0);
}

// PURPOSE: inserts an item into the circular buffer by updating back pointer.
// PARAMETER: item = the item to insert into buffer.
// RETURN: 0 = if insert was sucessful. -1 = if insert was unsucessful.
int insert_item(buffer_item item) {

	// check if buffer is not full first.
	if (!isFull()) {
		buffer[back] = item;
		back = (back + 1) % BUFFER_SIZE;  // modulus used to wrap around.
		count++;
    display();//In order to study the behavoirs keep track and print out the content of the shared buffer during the execution of the threads when an item is added or consumed.
		return 0;
	}

	return -1;
}

// PURPOSE: removes an item from circular buffer by updating front pointer.
// PARAMETER: *item = the item removed from the buffer.
// RETURN: 0 = if insert was sucessful. -1 = if insert was unsucessful.
int remove_item(buffer_item *item) {

	// check if buffer is not empty first.
	if (!isEmpty()) {
		*item = buffer[front];
		front = (front + 1) % BUFFER_SIZE;	// modulus used to wrap around.
		count--;
    display();//In order to study the behavoirs keep track and print out the content of the shared buffer during the execution of the threads when an item is added or consumed.
		return 0;
	}

	return -1;
}
