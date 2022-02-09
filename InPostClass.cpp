#include "InPost.h"
#include "stack.h"
#include <sstream>
#include <math.h>


using namespace std;

//Infix to Postfix

//This parses through the user infix input and organizes it using stacks
string InPost::InToPost(string exp) {
	Stack Op(exp.length());
	post = "";
	int c = 0;
	for (int i = 0; i < exp.length(); i++) {
		if (exp[i] == ' ' || exp[i] == ',') continue;
		else if (Neither(exp[i])) { //Finds invalid inputs in the sense of using improper operands
			post = "Invalid Input";
			return(post);
			break;
		}
		else if (IsOperator(exp[i])) {
			while (!Op.IsEmpty() && Op.Top() != '(' && HigherPrec(Op.Top(), exp[i])) {
				post += Op.Top();
				Op.Pop();
				post += ' ';
			}
			Op.Push(exp[i]);
		}
		else if (IsOperand(exp[i])) { //This allows the code to read in multidigit and decimal Operands
			counter = 0;
			while (true) {

				if (IsOperand(exp[i + counter]) ){//makes sure that what is being read in is the operand
					post += exp[i + counter];
					exp[i + counter] = ' '; //this clears the future exp so that the code doesn't reuse a used value
					counter++;
				}
				else break;
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
	while (!Op.IsEmpty()) {//Empties the stack which contains postfix into string
		post += Op.Top();
		post += ' ';
		Op.Pop();
	}
	
	
	return post; //returns postfix
}

bool InPost::IsOperator(char op) {

	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') return true;
	return false;
}

bool InPost::IsOperand(char op) {
	if (op >= '0' && op <= '9' || op == '.') {
		return true;
	}
	return false;
}

bool InPost::Neither(char op) {
	if (!IsOperand(op) && !IsOperator(op)) return true;
	else return false;
}

int InPost::Weight(char op) { //prioritizes the operands in PEMDAS order

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

float InPost::Perform(char op, float val1, float val2) { //performs the PEMDAS operations
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
		else if (IsOperator(exp[i])) { //takes the values and performs corresponding operator and pushes result on stack
			n2 = Op.Top();
			Op.Pop();
			n1 = Op.Top();
			Op.Pop();

			result = Perform(exp[i], n1, n2);
			Op.Push(result);
		}
		else if (IsOperand(exp[i])) {
			post = "";
			counter = 0;
			while (true) {
				if (IsOperand(exp[i + counter]) || exp[i + counter] == '.') {
					post += exp[i + counter];
					exp[i + counter] = ' '; //this clears the future exp so that the code doesn't reuse a used value
				}
				else break;
				counter++;
			}
			stringstream r(post); //Pulls Numerical value from string
			r >> result;  //Converts value to float
			Op.Push(result);
		}
	}
	return Op.Top();

}

