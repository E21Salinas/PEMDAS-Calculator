#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack(int size /*= 10*/){
	maxTop = size - 1;
	values = new double[size];
	top = -1;
}


double Stack::Top(){
	if (IsEmpty()){
		cout << "Error: The Stack is Empty." << endl;
		return -1;
	}
	else {
		return values[top];
	}
}

void Stack::Push(const double x){
	if (IsFull()) {
		cout << "Error: Stack is Full." << endl;
	}
	else {
		values[++top] = x;
	}
}

double Stack::Pop() {
	if (IsEmpty()) {
		cout << "Error: The Stack is Empty." << endl;
		return -1;
	}
	else {
		return values[top--];
	}
}

void Stack::DisplayStack() {
	for (int i = top; i >= 0; i--) {
		cout << values[i] << endl;
	}
}