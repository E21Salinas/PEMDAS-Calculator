#pragma once
#include <iostream>
#include <string>

using namespace std;

class InPost {

public:
	//infix to postfix
	string InToPost(string exp);
	int HigherPrec(char op1, char op2);
	bool IsOperator(char op);
	bool IsOperand(char op);
	int Weight(char op);

	//evaluate postfix
	float Perform(char op, float val1, float val2);
	float Eval(string exp);

private:
	int weight;
	int w1;
	int w2;
	float result;
	float n1;
	float n2;
	int counter;
	int b;
	string post;
	
};