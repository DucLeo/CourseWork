#pragma once
#include "Stack.h"

template<class T>
class Queue {
private:
	class Element {
	public:
		T data;
		Element* next;
	};

public:
	Element* front;
	Element* rear;
	size_t size;

	void enfQueue(T x) {
		Element* new_element = new Element;
		new_element->data = x;
		if (isEmpty()) {
			new_element->next = NULL;
			rear = new_element;
			front = new_element;
		}
		else {
			new_element->next = front;
			front = new_element;
		}
		size++;
	}

	T deQueue() {
		if (isEmpty()) throw runtime_error("Queue is empty.");
		else {
			Element* temporary = front;
			if (temporary->next == NULL) {
				front = NULL;
				rear = NULL;
			}
			else front = front->next;
			T value = temporary->data;
			delete temporary;
			size--;
			return value;
		}
	}

	bool isEmpty() {
		if (front == NULL && rear == NULL)
			return true;
		else {
			return false;
			if (front == NULL && rear != NULL)
				front = rear;
			if (front != NULL && rear == NULL)
				rear = front;
		}
	}

	void outQueue() {
		if (isEmpty()) throw runtime_error("Queue is empty.");
		else {
			Element* temporary = front;
			while (temporary != NULL) {
				cout << temporary->data;
				temporary = temporary->next;
			}
			delete temporary;
		}
	}
	//This function complements the function PolishNotation() in the library PolishNotation.h
	void more_compact(T x1,T x2,T x3, T x4, T x5, T x6, T x7, T x8) { //more_compact('(', ')', '-', 'g', 's', 'n', 't', ' ');
		if (isEmpty()) throw runtime_error("Queue is empty.");
		else {
			Element* temp = NULL;
			Element* current2 = NULL;
			Element* prev2 = NULL;
			Element* current = front;
			Element* prev = NULL;
					 
			bool check = 1;
			while (current != NULL) {
				if (front->data == x8) {
					temp = front;
					front = front->next;
					delete temp;
					size--;
					current = front;
				}
				else if (front->data == x1 && check == 1) {
					if (front->next->data == x3 && front->next->next->data != x8)
					{
						current = current->next;
						current = current->next;
						current = current->next;
						check = 0;
					}
					else {
						if (front->next->data == x8) {
							temp = front;
							front = front->next;
							delete temp;
							size--;
							temp = front;
							front = front->next;
							delete temp;
							size--;
							current = front;
						}
						else {
							temp = front;
							front = front->next;
							delete temp;
							size--;
							current = front;
						}
						int s = 1;
						current2 = current;
						prev2 = NULL;
						while (1) {
							if (current2->data == x1)
							{
								prev2 = current2;
								current2 = current2->next;
								s++;
							}
							else if (current2->data == x2) {
								s--;
								if (s == 0) break;
								else {
									prev2 = current2;
									current2 = current2->next;
								}
							}
							else {
								prev2 = current2;
								current2 = current2->next;
							}
						}
						prev2->next = current2->next;
						if (current2 == rear) {
							rear = prev2;
						}
						delete current2;
					}
				}
				
				else if( (current->data == x4 || current->data == x5 || current->data == x6 || current->data == x7) && current->next->data == x1) {
					prev = current;
					current = current->next;
					prev = current;
					current = current->next;
				}
				else if (current->data == x1) {
					if (current->next->data == x3 && current->next->next->data != x8)
					{
						prev = current;
						current = current->next;
						prev = current;
						current = current->next;
						prev = current;
						current = current->next;
					}
					else {

						if (current->next->data == x8) {
							temp = current;
							current = current->next;
							delete temp;
							size--;
							temp = current;
							current = current->next;
							delete temp;
							size--;
							prev->next = current;
						}
						else {
							temp = current;
							current = current->next;
							delete temp;
							size--;
							prev->next = current;
						}
						int s = 1;
						current2 = current;
						prev2 = NULL;
						while (1) {
							if (current2->data == x1)
							{
								prev2 = current2;
								current2 = current2->next;
								s++;
							}
							else if (current2->data == x2) {
								s--;
								if (s == 0) break;
								else {
									prev2 = current2;
									current2 = current2->next;
								}
							}
							else {
								prev2 = current2;
								current2 = current2->next;
							}
						}
						prev2->next = current2->next;
						if (current2 == rear) {
							rear = prev2;
						}
						delete current2;
						size--;
					}	
				}
				else { 
					prev = current;
					current = current->next;
				}
			}
		}
	}
	
	void reverse()
	{
		if (isEmpty()) throw runtime_error("Queue is empty.");
		else {
			Stack<T>* stack = new Stack<T>;
			Element* temporary = front;
			while (temporary != NULL) {
				stack->push(temporary->data);
				temporary = temporary->next;
			}
			temporary = front;
			while (!stack->isEmpty()) {
				temporary->data = (stack->pop());
				temporary = temporary->next;
			}
			delete stack;
		}
	}

	Queue() {
		front = NULL;
		rear = NULL;
		size = 0;
	}

	~Queue() {
		while (size) deQueue();
	};
};