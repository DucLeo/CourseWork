#include "pch.h"
#include "gtest/gtest.h"
#include "../СourseWork/PolishNotation.h"
#include "../СourseWork/Calculator.h"


class Test_PolishNotation : public ::testing::Test {
public:
	string str;
	Queue<char>* queue = new Queue<char>;
};

TEST_F(Test_PolishNotation, Test_PN) {
	//When there is a space in the expression.
	str = "3 - 2";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();
	
	//When the brackets are not balanced.
	str = "sin(5+(6-3)";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When negative number is not in parentheses.
	str = "5*-1+5";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When no parameters in a pair of brackets
	str = "8+()+2";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When operands are missing, close brackets immediately after the operator
	str = "8+(8*)+2";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When numeric expression is not correct
	str = "8.23.1+2";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When the operands are contiguous
	str = "8pi+5";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When the operators are contiguous
	str = "5+1-+0";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When missing number
	str = "1+2+3+4+5+";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When the parameter of the cos, sin, tg, ctg, ln, log, sqrt, abs function is not in parentheses.
	str = "cos0*log10-sqrt9+abs5";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When there are strange characters in the expression
	str = "8=5+3";
	ASSERT_THROW(queue = PolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();
	
	//Expression with the same priority of operations
	str = "1-2-3-4";
	queue = PolishNotation(str);
	//- - - 1 2 3 4 
	ASSERT_EQ(queue->deQueue(), '-'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '-'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '-'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '1'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '2'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '3'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '4');
	ASSERT_TRUE(queue->isEmpty());
	str.clear();
	queue->~Queue();
	
	//Expression not with the same priority of operations
	str = "1-2+3*4";
	queue = PolishNotation(str);
	//+ - 1 2 * 3 4 
	ASSERT_EQ(queue->deQueue(), '+'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '-'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '1'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '2'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '*'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '3'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '4');
	ASSERT_TRUE(queue->isEmpty());
	str.clear();
	queue->~Queue();
	
	//Expressions with trigonometric functions
	str = "cos(0)-tg(pi)";
	queue = PolishNotation(str);
	//- cos( 0) tg( pi)
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'c');
	ASSERT_EQ(queue->deQueue(), 'o');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '0');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 't');
	ASSERT_EQ(queue->deQueue(), 'g');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'p');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_TRUE(queue->isEmpty());
	str.clear();
	queue->~Queue();
	
	//Expressions with logarithmic and other functions
	str = "ln(e)-abs(-1)^sqrt(3)";
	queue = PolishNotation(str);
	//- ln( e) ^ abs(-1) sqrt( 3)
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'l');
	ASSERT_EQ(queue->deQueue(), 'n');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'e');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '^');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'a');
	ASSERT_EQ(queue->deQueue(), 'b');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), '1');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), 'q');
	ASSERT_EQ(queue->deQueue(), 'r');
	ASSERT_EQ(queue->deQueue(), 't');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '3');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_TRUE(queue->isEmpty());
	str.clear();
	queue->~Queue();
	
	//Complex expressions with multiple brackets
	str = "ln(e^(sin(pi/2)-cos(-pi)))-abs(8-(7))^sqrt(3)";
	queue = PolishNotation(str);
	//- ln( ^ e - sin( / pi 2) cos(-pi)) ^ abs( - 8 7) sqrt( 3)
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'l');
	ASSERT_EQ(queue->deQueue(), 'n');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '^');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'e');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), 'n');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '/');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'p');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '2');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'c');
	ASSERT_EQ(queue->deQueue(), 'o');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), 'p');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '^');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'a');
	ASSERT_EQ(queue->deQueue(), 'b');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '-');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '8');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '7');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), 'q');
	ASSERT_EQ(queue->deQueue(), 'r');
	ASSERT_EQ(queue->deQueue(), 't');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '3');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_TRUE(queue->isEmpty());
	str.clear();
	queue->~Queue();
	
}

class Test_Calculator : public ::testing::Test {
public:
	string str;
	Queue<char>* queue = new Queue<char>;
};

TEST_F(Test_Calculator, Test_Calculator) {
	//Example of an expression
	str = "(cos(3*pi)+sin(0.5*pi))*(tg(0.25*pi)+ctg(pi/4))-ln(e)*log(10^3)-sqrt(9)+1*2*3*4*5+abs(-6.501)";//Result = 120.501
	queue = PolishNotation(str);
	ASSERT_DOUBLE_EQ(Calculator(queue), 120.501);
	str.clear();
	queue->~Queue();
	
	//When divisor of division equals 0
	str = "10/0-10";
	queue = PolishNotation(str);
	ASSERT_THROW(Calculator(queue), invalid_argument);
	str.clear();
	queue->~Queue();
	
	//When tg(x) does not exist (x = k*pi/2)
	str = "tg(pi/2)";
	queue = PolishNotation(str);
	ASSERT_THROW(Calculator(queue), invalid_argument);
	str.clear();
	queue->~Queue();
	
	//When ctg(x) does not exist (x = k*pi)
	str = "ctg(pi)";
	queue = PolishNotation(str);
	ASSERT_THROW(Calculator(queue), invalid_argument);
	str.clear();
	queue->~Queue();

	//The parameter of the function 'ln' is non-positive
	str = "ln(0)";
	queue = PolishNotation(str);
	ASSERT_THROW(Calculator(queue), invalid_argument);
	str.clear();
	queue->~Queue();

	//The parameter of the function 'log' is non-positive
	str = "log(-10)";
	queue = PolishNotation(str);
	ASSERT_THROW(Calculator(queue), invalid_argument);
	str.clear();
	queue->~Queue();

	//The parameter of the square root function is negative
	str = "sqrt(-10)";
	queue = PolishNotation(str);
	ASSERT_THROW(Calculator(queue), invalid_argument);
	str.clear();
	queue->~Queue();
	
}

class Test_Stack : public ::testing::Test {
public:
	void SetStack(Stack<int>* stack) {
		for (int i = 0; i < 5; i++) stack->push(i);
	}
};

TEST_F(Test_Stack, Test_isEmpty) {
	Stack<int>* stack = new Stack<int>;
	ASSERT_TRUE(stack->isEmpty());
	ASSERT_EQ(stack->size, 0);

	SetStack(stack);
	ASSERT_FALSE(stack->isEmpty());
	ASSERT_NE(stack->size, 0);

}

TEST_F(Test_Stack, Test_push) {
	Stack<int>* stack = new Stack<int>;
	stack->push(5);
	ASSERT_EQ(stack->size, 1);
	ASSERT_EQ(stack->pop(), 5);

	SetStack(stack);
	ASSERT_EQ(stack->size, 5);
	ASSERT_EQ(stack->pop(), 4);
	ASSERT_EQ(stack->pop(), 3);
	ASSERT_EQ(stack->pop(), 2);
	ASSERT_EQ(stack->pop(), 1);
	ASSERT_EQ(stack->pop(), 0);
}

TEST_F(Test_Stack, Test_pop) {
	Stack<int>* stack = new Stack<int>;
	ASSERT_THROW(stack->pop(), runtime_error);

	SetStack(stack);
	ASSERT_EQ(stack->pop(), 4);	ASSERT_EQ(stack->size, 4);
	ASSERT_EQ(stack->pop(), 3);	ASSERT_EQ(stack->size, 3);
	ASSERT_EQ(stack->pop(), 2);	ASSERT_EQ(stack->size, 2);
	ASSERT_EQ(stack->pop(), 1);	ASSERT_EQ(stack->size, 1);
	ASSERT_EQ(stack->pop(), 0);	ASSERT_EQ(stack->size, 0);
	ASSERT_TRUE(stack->isEmpty());
}

class Test_Queue : public ::testing::Test {
public:
	void SetQueue(Queue<int>* queue) {
		for (int i = 0; i < 5; i++) queue->enfQueue(i);
	}
};

TEST_F(Test_Queue, Test_isEmpty) {
	Queue<int>* queue = new Queue<int>;
	ASSERT_TRUE(queue->isEmpty());
	ASSERT_EQ(queue->size, 0);

	SetQueue(queue);
	ASSERT_FALSE(queue->isEmpty());
	ASSERT_NE(queue->size, 0);
}

TEST_F(Test_Queue, Test_enfQueue) {
	Queue<int>* queue = new Queue<int>;
	queue->enfQueue(5);
	ASSERT_EQ(queue->size, 1);
	ASSERT_EQ(queue->deQueue(), 5);

	SetQueue(queue);
	ASSERT_EQ(queue->size, 5);
	ASSERT_EQ(queue->deQueue(), 4);
	ASSERT_EQ(queue->deQueue(), 3);
	ASSERT_EQ(queue->deQueue(), 2);
	ASSERT_EQ(queue->deQueue(), 1);
	ASSERT_EQ(queue->deQueue(), 0);
}

TEST_F(Test_Queue, Test_deQueue) {
	Queue<int>* queue = new Queue<int>;
	ASSERT_THROW(queue->deQueue(), runtime_error);

	SetQueue(queue);
	ASSERT_EQ(queue->deQueue(), 4); ASSERT_EQ(queue->size, 4);
	ASSERT_EQ(queue->deQueue(), 3); ASSERT_EQ(queue->size, 3);
	ASSERT_EQ(queue->deQueue(), 2); ASSERT_EQ(queue->size, 2);
	ASSERT_EQ(queue->deQueue(), 1); ASSERT_EQ(queue->size, 1);
	ASSERT_EQ(queue->deQueue(), 0); ASSERT_EQ(queue->size, 0);
	ASSERT_TRUE(queue->isEmpty());
}

TEST_F(Test_Queue, Test_reverse) {
	Queue<int>* queue = new Queue<int>;
	ASSERT_THROW(queue->deQueue(), runtime_error);

	SetQueue(queue);
	queue->reverse();
	
	ASSERT_EQ(queue->size, 5);
	ASSERT_EQ(queue->deQueue(), 0);
	ASSERT_EQ(queue->deQueue(), 1);
	ASSERT_EQ(queue->deQueue(), 2);
	ASSERT_EQ(queue->deQueue(), 3);
	ASSERT_EQ(queue->deQueue(), 4);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
