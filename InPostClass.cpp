#include "InPost.h"
#include "stack.h"
#include <sstream>
#include <math.h>


using namespace std;

//Infix to Postfix
string InPost::InToPost(string exp) {
	Stack Op(exp.length());
	post = "";
	int c = 0;
	for (int i = 0; i < exp.length(); i++) {
		if (exp[i] == ' ' || exp[i] == ',') continue;
		else if (IsOperator(exp[i])) {
			while (!Op.IsEmpty() && Op.Top() != '(' && HigherPrec(Op.Top(), exp[i])) {
				post += Op.Top();
				Op.Pop();
				post += ' ';
			}
			Op.Push(exp[i]);
		}
		else if (IsOperand(exp[i])) {
			b = 1;
			counter = 0;
			while (b != 0) {

				if (IsOperand(exp[i + counter]) || exp[i+counter] == '.') {
					post += exp[i + counter];
					exp[i + counter] = ' ';
					counter++;
				}
				else b = 0;
			}
			post += ' ';
		}
		else if (exp[i] == '(') {
			Op.Push(exp[i]);
		}
		else if (exp[i] == ')') {
			while (!Op.IsEmpty() && Op.Top() != '(') {
				post += Op.Top();
				post += ' ';
				Op.Pop();
			}
			Op.Pop();
		}
	}
	while (!Op.IsEmpty()) {
		post += Op.Top();
		post += ' ';
		Op.Pop();

	}
	
	

	return post;
}

bool InPost::IsOperator(char op) {

	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') return true;
	return false;
}

bool InPost::IsOperand(char op) {
	if (op >= '0' && op <= '9') {
		return true;
	}
	return false;
}

int InPost::Weight(char op) {

	if (op == '+' || op == '-') weight = 1;
	else if (op == '*' || op == '/') weight = 2;
	else if (op == '^') weight = 3;
	return weight;
}

int InPost::HigherPrec(char op1, char op2) {
	w1 = Weight(op1);
	w2 = Weight(op2);

	if (w1 == w2 || w1 > w2) return true;
	else if (w1 < w2) return false;
	return false;
}

//Evaluating Postfix

float InPost::Perform(char op, float val1, float val2) {
	if (op == '+') return val1 + val2;
	else if (op == '-') return val1 - val2;
	else if (op == '*') return val1 * val2;
	else if (op == '/') return val1 / val2;
	else if (op == '^') return pow(val1, val2);


	else cout << "Unexpected Error \n";
	return -1;
}


float InPost::Eval(string exp) {
	Stack Op(exp.length());
	
	for (int i = 0; i < exp.length(); i++) {
		if (exp[i] == ' ' || exp[i] == ',') continue;
		else if (IsOperator(exp[i])) {
			n2 = Op.Top();
			Op.Pop();
			n1 = Op.Top();
			Op.Pop();

			result = Perform(exp[i], n1, n2);
			Op.Push(result);
		}
		else if (IsOperand(exp[i])) {
			string answer;
			counter = 0;
			b = 1;
			while (b != 0) {
				if (exp[i + counter] == ' ') b = 0;
				else if (IsOperand(exp[i + counter]) || exp[i+counter] == '.') {
					answer += exp[i + counter];
					exp[i + counter] = ' ';
				}
				else b = 0;
				counter++;
			}
			stringstream r(answer);
			r >> result;
			Op.Push(result);
		}
	}
	return Op.Top();

}

