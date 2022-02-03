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

int main() {

	Info info[100];
	Queue History(100);
	InPost Input;

	int count = 0;
	int cont = 1;
	double value;

	string expression;
	string postfix;

	cout << "Current Operators are '+', '-', '/', '*', '^', '(', and ')'" << endl;
	cout << "To End Calculating type (N)" << endl;
	cout << "To View History type (H)" << endl << endl;

	while (cont != 0) {

		cout << "Enter Infix Expression \n";
		getline(cin, expression);
		if (expression[0] == 'N' || expression[0] == 'n') cont = 0;
		else if (expression[0] == 'H' || expression[0] == 'h') {
			Queue temp(100);
			while (!History.IsEmpty()) {
				History.Dequeue(value);
				int g = value;
				printS(info[g]);
				temp.Enqueue(value);
			}
			while (!temp.IsEmpty()) {
				temp.Dequeue(value);
				History.Enqueue(value);
			}
		}
		else {
			postfix = Input.InToPost(expression);
			cout << "PostFix = " << postfix << "\n";
			float val = Input.Eval(postfix);
			cout << "Answer = " << val << endl << endl;

			info[count].infix = expression;
			info[count].postfix = postfix;
			info[count].answer = val;
			info[count].counter = count;
			History.Enqueue(count);

			count++;
		}
	}


	while (!History.IsEmpty()) {
		History.Dequeue(value);
		int g = value;
		printS(info[g]);
	}
	return 0;
}
