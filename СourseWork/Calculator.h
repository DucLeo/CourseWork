#pragma once
#include <math.h>
#include "Queue.h"

const double pi = 3.141592653589793,
			  e = 2.718281828459045;

double equivalent_number(char& c) {
	double i = 0;
	switch (c)
	{
	case '0':
	{
		i = 0;
		break;
	}
	case '1':
	{
		i = 1;
		break;
	}
	case '2':
	{
		i = 2;
		break;
	}
	case '3':
	{
		i = 3;
		break;
	}
	case '4':
	{
		i = 4;
		break;
	}
	case '5':
	{
		i = 5;
		break;
	}
	case '6':
	{
		i = 6;
		break;
	}
	case '7':
	{
		i = 7;
		break;
	}
	case '8':
	{
		i = 8;
		break;
	}

	case '9':
	{
		i = 9;
		break;
	}
	default:
	{
		break;
	}
	}
	return i;
}


double Calculator(Queue<char>* queue) {
	queue->reverse();
	Stack<double>* stack = new Stack<double>;

	char token;
	double number;     //Used in binary math

	while (!queue->isEmpty()) {

		token = queue->deQueue();
			
		if (isDigit(token)) {
			stack->push(equivalent_number(token));
			token = queue->deQueue();
			int n = 0;
			while (isDigit(token) || token == '.' || token == '-') {
				if (isDigit(token)) {
					n++;
					stack->top->data += equivalent_number(token) * pow(10, n);
					if (queue->isEmpty()) break;
					else token = queue->deQueue();
				}
				else if (token == '.') {
					stack->top->data *= pow(10, -(n + 1));
					n = -1;
					token = queue->deQueue();
				}
				else {
					stack->top->data *= (-1);
					break;
				}
			}
		}
		else if (isOperator(token)) {
			number = stack->pop();
			if (token == '+') {
				stack->top->data += number;
			}
			else if (token == '-') {
				stack->top->data = number - stack->top->data;
			}
			else if (token == '*') {
				stack->top->data *= number;
			}
			else if (token == '/') {
				if (stack->top->data != 0) {
					stack->top->data = number / stack->top->data;
				}
				else throw invalid_argument("Divisor must be non-zero!");
			}
			else {
				stack->top->data =  pow(number, stack->top->data);
			}
		}
		else if (token == '(') {
			if (queue->isEmpty()) break;
			else {
				token = queue->deQueue();
				if (token == 'n') {
					token = queue->deQueue();
					if (token == 'l') {
						if (stack->top->data > 0) {
							stack->top->data = log(stack->top->data);
						}
						else throw invalid_argument("The argument of function ln() must be a positive real number!");
					}
					else {
						token = queue->deQueue();
						stack->top->data = sin(stack->top->data);
						if (abs(stack->top->data) < 0.00001) stack->top->data = 0;
					}
				}
				else if (token == 's') {
					token = queue->deQueue();
					if (token == 'o') {
						token = queue->deQueue();
						stack->top->data = cos(stack->top->data);
						if (abs(stack->top->data) < 0.00001) stack->top->data = 0;
					}
					else {
						token = queue->deQueue();
						stack->top->data = abs(stack->top->data);
					}	
				}
				else if (token == 'g') {
					token = queue->deQueue();
					if (token == 'o') {
						if (stack->top->data > 0) {
							token = queue->deQueue();
							stack->top->data = log10(stack->top->data);
						}
						else throw invalid_argument("The argument of function log() must be a positive real number!");
					}
					else {
						if (queue->isEmpty()) {
							if (sin(stack->top->data) != 1 && sin(stack->top->data) != -1) {
								stack->top->data = tan(stack->top->data);
							}
							else throw invalid_argument("The argument of function tg() is not valid!");
						}
						else {
							token = queue->deQueue();
							if (token == 'c') {
								if (cos(stack->top->data) != 1 && cos(stack->top->data) != -1) {
									stack->top->data = 1/tan(stack->top->data);
								}
								else throw invalid_argument("The argument of function ctg() is not valid!");
							}
							else {
								if (sin(stack->top->data) != 1 && sin(stack->top->data) != -1) {
									stack->top->data = tan(stack->top->data);
								}
								else throw invalid_argument("The argument of function tg() is not valid!");
							}
						}
					}
				}
				else if (token == 't') {
					if (stack->top->data >= 0) {
						token = queue->deQueue();
						token = queue->deQueue();
						token = queue->deQueue();
						stack->top->data = pow(stack->top->data, 0.5);
					}
					else throw invalid_argument("The argument of function sqrt() is not valid!");
				}	
			}
		}
		else if (token == 'i') {
			token = queue->deQueue();
			stack->push(pi);
			if (!queue->isEmpty()) {
				token = queue->deQueue();
				if (token == '-') stack->top->data *= (-1);
			}
		}
		else if (token == 'e') {
			stack->push(e);
			if (!queue->isEmpty()) {
				token = queue->deQueue();
				if (token == '-') stack->top->data *= (-1);
			}
		}
	}
	return stack->top->data;
	stack->pop();
	delete stack;
}