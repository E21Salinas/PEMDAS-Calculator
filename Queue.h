#pragma once

class Queue {

public:
	Queue(int size = 10); //constructor
	~Queue() { delete[] values; } //constructor
	bool IsEmpty(void);
	bool IsFull(void);
	bool Enqueue(double x);
	bool Dequeue(double& x);
	void DisplayQueue(void);

private:
	int front;
	int rear;
	int counter;
	int maxSize;
	double* values;
};