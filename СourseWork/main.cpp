#include "PolishNotation.h"
#include "Calculator.h"


int main() {
	string input = "(cos(3*pi)+sin(0.5*pi))*(tg(0.25*pi)+ctg(pi/4))-ln(e)*log(10^3)-sqrt(9)+2*3*4*5+abs(-6)+sin(pi)+5";
	Queue<char>* queue = new Queue<char>();
	cout << "The expression before reversing: " << input << endl;

	queue = PolishNotation(input);
	if (!queue->isEmpty()) {
		cout << "\nThe expression after  reversing: ";
		queue->outQueue();
		cout << "\n\nResult of the expression: " << Calculator(queue) << endl;
	}
	
	return 0;
}
