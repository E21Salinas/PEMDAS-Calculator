#include <iostream>
#include <iostream>
#include "InPost.h"
#include "stack.h"
#include "Queue.h"


using namespace std;

struct Info {
	string infix;
	string postfix;
	float answer;
	int counter;
};

void printS(Info temp) {
	cout << endl;
	cout << "Input " << temp.counter << ": "  << temp.infix << endl;
	cout << "Postfix: " << temp.postfix << endl;
	cout << "Answer: " << temp.answer << endl << endl;
}

void help() {
	cout << "Current Operators are '+', '-', '/', '*', '^', '(', and ')'" << endl;
	cout << "To End Calculating type (N)" << endl;
	cout << "To Delete History type (D)" << endl;
	cout << "To View History type (H)" << endl;
	cout << "Keep in mind to use operators even if its implied by the parenthesis. The code doesn't recognize implied multiplication." << endl;
}

int main() {
	//intializing
	Info info[100];
	Queue History(100);
	InPost Input;

	int index = 0;
	int temporary;
	double value;

	string expression;
	string postfix;

	help(); //prints explanations

	while (true) {
		cout << endl;
		cout << "Enter Infix Expression" << endl;
		getline(cin, expression); //reads in infix to expression
		if (expression[0] == 'N' || expression[0] == 'n') break; //ends code
		else if (expression[0] == 'H' || expression[0] == 'h') { //prints out history
			Queue temp(100);
			while (!History.IsEmpty()) {//empties history queue into to temp while printing values
				History.Dequeue(value);
				temporary = value;
				printS(info[temporary]);
				temp.Enqueue(value);
			}
			while (!temp.IsEmpty()) {//empties temp back to history to retain info
				temp.Dequeue(value);
				History.Enqueue(value);
				index = 0;
			}
		}
		else if (expression[0] == 'D' || expression[0] == 'd') { //deletes the history queue which containes the index for the info structs
			while (!History.IsEmpty()) {
				History.Dequeue(value);
			}
		}
		else {
			postfix = Input.InToPost(expression); //finds postfix
			if (postfix == "Invalid Input") {
				cout << "PostFix = " << postfix << "\n";
				continue;
			}
			else {
				cout << "PostFix = " << postfix << "\n";
				float val = Input.Eval(postfix); //returns evaluated postfix
				cout << "Answer = " << val << endl;
				//inputs the information to the structs
				info[index].infix = expression;
				info[index].postfix = postfix;
				info[index].answer = val;
				info[index].counter = index;
				History.Enqueue(index); //index is stored in history

				index++;
			}
		}
	}

	return 0;
}
