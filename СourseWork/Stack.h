#pragma once
#include <iostream>

using namespace std;

template<class T>
class Stack {
private:
	class Element {
	public:
		T data;
		Element* next;
	};

public:
	Element* top;
	size_t size;

	void push(T x) {
		if (isEmpty()) {
			Element* new_element = new Element;
			new_element->data = x;
			new_element->next = NULL;
			top = new_element;
		}
		else {
			Element* new_element = new Element;
			new_element->data = x;
			new_element->next = top;
			top = new_element;
		}
		size++;
	}

	T pop() {
		if (isEmpty()) throw runtime_error("Stack is empty.");
		else {
			Element* temporary = top;
			if (top->next == NULL) top = NULL;
			else top = temporary->next;
			T popped = temporary->data;
			delete temporary;
			size--;
			return popped;
		}
	}
	
	bool isEmpty() {
		if (top == NULL) return true;
		else return false;
	}

	Stack() {
		top = NULL;
		size = 0;
	}

	~Stack() {
		while (size) pop();
	};
};