#pragma once
#include <math.h>

class Stack {

public:
	Stack(int size = 10); //constructor
	~Stack() { delete[] values; }//destructor
	bool IsEmpty() { return top == -1; }
	bool IsFull() { return top == maxTop; }
	double Top();
	void Push(const double x);
	double Pop();
	void DisplayStack();

private:
	int maxTop; //max stack size = size -1
	int top; //current top of stack
	double* values; //element array
};