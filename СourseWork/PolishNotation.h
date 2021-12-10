#pragma once
#include <string>
#include "Queue.h"

using namespace std;
//Supported operators + - * / ^
bool isOperator(char token) {
	return (token == '+' || token == '-' || token == '*' || token == '/' || token == '^');
}
//Priority_level 0: ( )
//Priority_level 1: +
//Priority_level 2: -
//Priority_level 3: *
//Priority_level 4: /
//Priority_level 5: ^
int priority_level(char token) {
	if (token == '+')      return 1;
	else if (token == '-') return 2;
	else if (token == '*') return 3;
	else if (token == '/') return 4;
	else if (token == '^') return 5;
	else return 0;
}
//Supported digtits: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
bool isDigit(char token) {
	return (token >= '0' && token <= '9');
}

Queue<char>* PolishNotation(string& input) {
	
	//The last character of the expression can only be a digit, ')', 'i' or 'e'
	if (!isDigit(input[input.size() - 1]) && input[input.size() - 1] != ')' &&
		input[input.size() - 1] != 'i' && input[input.size() - 1] != 'e') throw logic_error("Expression is not correct!");
	
	//The fist character of the expression cannot be an operator, '.', ')',
	else if (isOperator(input[0]) || input[0] == '.'|| input[0] == ')') {
		if (input[0] == '-') throw logic_error("Negative numbers are required in parentheses!");
		else throw logic_error("Expression is not correct!");
	}

	else {
		Stack<char>* stack = new Stack<char>;
		Queue<char>* queue = new Queue<char>;
		int s = 0;
		
		//Scan the expression from right to left
		for (int i = input.size() - 1; i >= 0; i--) {
			
			//Token is a right parenthesis
			if (input[i] == ')')
			{
				s++;
				if (input[i - 1] == '(' || isOperator(input[i - 1])) {

					if (input[i - 1] == '(') throw logic_error("No parameters in a pair of brackets!");
					else throw logic_error("Expression is not correct!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
				queue->enfQueue(input[i]);
				stack->push(input[i]);
			}

			//Token is a digit
			else if (isDigit(input[i])) {
				queue->enfQueue(input[i]);
				bool check = true;		//Is there a digit before the decimal point?
				int NoDP = 0,		   // Number of decimal points ( can only be 0 or 1)
					digict_tail = i;
				if (i - 1 >= 0)
				{
					while (isDigit(input[i - 1]) || input[i - 1] == '.') {
						if (isdigit(input[i - 1])) {
							queue->enfQueue(input[i - 1]);
							i--;
							if (i - 1 < 0) break;
						}
						else {
							NoDP++;
							if (NoDP > 1) break;
							else if (i - 2 >= 0 && isDigit(input[i - 2])) {
								queue->enfQueue(input[i - 1]);
								i--;
							}
							else {
								check = false;
								break;
							}
						}
					}
				}
				else {
					queue->enfQueue(' ');
					break;
				}

				if (check = false || NoDP > 1) {
					throw logic_error("Numeric expression is not correct!");
					stack->~Stack();
					queue->~Queue();
					break;
				}

				else if (((i == 0) || (i - 1 >= 0 && (isOperator(input[i - 1]) || input[i - 1] == '('))) &&
					((digict_tail == input.size() - 1) || (digict_tail + 1 <= input.size() - 1 && (isOperator(input[digict_tail + 1]) || input[digict_tail + 1] == ')'))))
				{
					//Negative numbers must be enclosed in brackets, for example (-20.21)
					if (i - 2 >= 0 && input[i - 1] == '-' && input[i - 2] == '(') {
						if (digict_tail + 1 <= input.size() - 1 && input[digict_tail + 1] == ')') {
							queue->enfQueue(input[i - 1]);
							i--;
						}
						else {
							throw logic_error("Expression is not correct!");
							stack->~Stack();
							queue->~Queue();
							break;
						}
					}
					else queue->enfQueue(' ');
				}
				
				else {
					throw logic_error("Expression with number is not correct!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
			}

			//Token is a pi
			else if (i - 1 >= 0 && input[i - 1] == 'p' && input[i] == 'i') {
				queue->enfQueue(input[i]);
				queue->enfQueue(input[i-1]);

				if (((i - 1 == 0) || (i - 2 >= 0 && (isOperator(input[i - 2]) || input[i - 2] == '('))) &&
					((i == input.size() - 1) || (i + 1 <= input.size() - 1 && (isOperator(input[i + 1]) || input[i + 1] == ')'))))
				{
					//Negative pi must be enclosed in brackets, for example (-pi)
					if (i - 3 >= 0 && input[i - 2] == '-' && input[i - 3] == '(') {
						if (i + 1 <= input.size() - 1 && input[i + 1] == ')') {
							queue->enfQueue(input[i - 2]);
							i = i - 2;
						}
						else {
							throw logic_error("Expression (-pi) is not correct!");
							stack->~Stack();
							queue->~Queue();
							break;
						}
					}
					else {
						i = i - 1;
						queue->enfQueue(' ');
					}
				}
				else {
					throw logic_error("Expression with pi is not correct!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
			}

			//Token is e
			else if (input[i] == 'e') {
				queue->enfQueue(input[i]);

				//
				if (((i == 0) || (i - 1 >= 0 && (isOperator(input[i - 1]) || input[i - 1] == '('))) &&
					((i == input.size() - 1) || (i + 1 <= input.size() - 1 && (isOperator(input[i + 1]) || input[i + 1] == ')'))))
				{
					//Negative e must be enclosed in brackets, for example (-e)
					if (i - 2 >= 0 && input[i - 1] == '-' && input[i - 2] == '(') {
						if (i + 1 <= input.size() - 1 && input[i + 1] == ')') {
							queue->enfQueue(input[i - 1]);
							i = i - 1;
						}
						else {
							throw logic_error("Expression (-e) is not correct!");
							stack->~Stack();
							queue->~Queue();
							break;
						}
					}
					else queue->enfQueue(' ');
				}
				else {
					throw logic_error("Expression with e is not correct!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
			}

			//Token is a left parenthesis
			else if (input[i] == '(')
			{
				s--;
				if (s < 0) {
					throw logic_error("Missing closing parenthesis in expression!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
				while (stack->top->data != ')') {
					queue->enfQueue(stack->pop());
					queue->enfQueue(' ');
				}
				queue->enfQueue(input[i]);
				stack->pop();
				if (i - 3 >= 0 && input[i - 1] == 'n' && input[i - 2] == 'i' && input[i - 3] == 's') {
					queue->enfQueue('n');
					queue->enfQueue('i');
					queue->enfQueue('s');
					queue->enfQueue(' ');
					i = i - 3;
				}
				else if (i - 3 >= 0 && input[i - 1] == 's' && input[i - 2] == 'o' && input[i - 3] == 'c') {
					queue->enfQueue('s');
					queue->enfQueue('o');
					queue->enfQueue('c');
					queue->enfQueue(' ');
					i = i - 3;
				}
				else if (i - 2 >= 0 && input[i - 1] == 'g' && input[i - 2] == 't') {
					queue->enfQueue('g');
					queue->enfQueue('t');
					i = i - 2;
					if (i - 1 >= 0 && input[i - 1] == 'c')
					{
						
						queue->enfQueue('c');
						queue->enfQueue(' ');
						i = i - 1;
					}
					else queue->enfQueue(' ');
				}
				else if (i - 3 >= 0 && input[i - 1] == 'g' && input[i - 2] == 'o' && input[i - 3] == 'l') {
					queue->enfQueue('g');
					queue->enfQueue('o');
					queue->enfQueue('l');
					queue->enfQueue(' ');
					i = i - 3;
				}
				else if (i - 2 >= 0 && input[i - 1] == 'n' && input[i - 2] == 'l') {
					queue->enfQueue('n');
					queue->enfQueue('l');
					queue->enfQueue(' ');
					i = i - 2;
				}
				else if (i - 4 >= 0 && input[i - 1] == 't' && input[i - 2] == 'r' && input[i - 3] == 'q' && input[i - 4] == 's') {
					queue->enfQueue('t');
					queue->enfQueue('r');
					queue->enfQueue('q');
					queue->enfQueue('s');
					queue->enfQueue(' ');
					i = i - 4;
				}
				else if (i - 3 >= 0 && input[i - 1] == 's' && input[i - 2] == 'b' && input[i - 3] == 'a') {
					queue->enfQueue('s');
					queue->enfQueue('b');
					queue->enfQueue('a');
					queue->enfQueue(' ');
					i = i - 3;
				}
				else queue->enfQueue(' ');
			}

			//Token is an operator
			else if (isOperator(input[i])) {
				if (isOperator(input[i - 1])) {
					throw logic_error("There are 2 operators in the expression next to each other!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
				else if (!isDigit(input[i - 1]) && input[i - 1] != ')' && input[i - 1] != 'i' && input[i - 1] != 'e') {
					throw logic_error("The binary operator is not correct!");
					stack->~Stack();
					queue->~Queue();
					break;
				}
				else {
					if (stack->isEmpty()) stack->push(input[i]);
					else {
						while (priority_level(stack->top->data) > priority_level(input[i])) {
							queue->enfQueue(stack->pop());
							queue->enfQueue(' ');
							if (stack->isEmpty()) break;
						}
						stack->push(input[i]);
					}
				}
			}
			
			//Invalid token
			else {
				throw logic_error("Expression is not correct!");
				stack->~Stack();
				queue->~Queue();
				break;
			}
		}

		//The number of closing brackets is less than the number of opening brackets
		if (s != 0) {
			stack->~Stack();
			queue->~Queue();
			throw logic_error("The brackets are not balanced!");
		}

		//Extract all the elements in the stack to the output list
		while (!stack->isEmpty()) {
			queue->enfQueue(stack->pop());
			queue->enfQueue(' ');
		}
		delete stack;

		//Make the expression more compact
		queue->more_compact('(', ')', '-', 'g', 's', 'n', 't', ' ');

		return queue;
	}
}