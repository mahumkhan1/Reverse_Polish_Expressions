#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

class Node {

private:
	float value;
	Node* next = NULL;
	
public:
	Node(float i)
	{
		value = i;
	}

	void setNext(Node* p)
	{
		next = p;
	}

	Node* getNext()
	{
		return next;
	}

	float getValue()
	{
		return value;
	}
};

class MyStack {
private:
	Node* top = NULL;
	int length = 0;

public:
	MyStack() {}
	~MyStack() {
		while (top != NULL) {
			pop();
		}
	}

	int getLength() {
		return length;
	}

	bool  isEmpty() {
		return top == NULL;
	}

	void push(float value)
	{
		length++;

		if (top == NULL)
		{
			top = new Node(value);
		}
		else {
			auto newTop = new Node(value);
			newTop->setNext(top);
			top = newTop;
		}
	}

	float pop()
	{
		length--;
		auto temp = top;
		auto tempValue = temp->getValue();
		top = top->getNext();
		delete temp;
		return tempValue;
	}
};

int main()
{
	string input = ""; 
	do {
	 	cout << "Enter expression: ";
		getline(cin, input);


		auto stack = MyStack();
		char* charInput = new char[50];
		char* context = NULL;
		strcpy_s(charInput, 50, input.c_str());

		char* token = strtok_s(charInput, " ", &context);
		auto tokenString = string(token);

		try {
			while (token != NULL && tokenString != "=") {
				if (tokenString == "+") {
					if (stack.getLength() < 2) {
						throw runtime_error("Error: Too many operators!");
					}
					
					auto val1 = stack.pop();
					auto val2 = stack.pop();

					stack.push(val2 + val1);
				}

				else if (tokenString == "-") {
					if (stack.getLength() < 2) {
						throw runtime_error("Error: Too many operators!");
					}
					auto val1 = stack.pop();
					auto val2 = stack.pop();

					stack.push(val2 - val1);
				}

				else if (tokenString == "*") {
					if (stack.getLength() < 2) {
						throw runtime_error("Error: Too many operators!");
					}
					
					auto val1 = stack.pop();
					auto val2 = stack.pop();

					stack.push(val2 * val1);
				}
				else if (tokenString == "/")
				{
					if (stack.getLength() < 2) {
						throw runtime_error("Error: Too many operators!");
					}
					auto val1 = stack.pop();
					auto val2 = stack.pop();

					if (val1 != 0) {
						stack.push(val2 / val1);
					}

					else {
						throw runtime_error("Error: Division by zero!");
					}
				}
				else if (tokenString != "=")
				{
					stack.push(stof(tokenString));
				}

				if (tokenString != "=")
				{
					token = strtok_s(NULL, " ", &context);
					tokenString = string(token);
				}
			}

			if (stack.getLength() > 1)
				throw runtime_error("Error: Too many operands!");


			cout << "Answer: " << stack.pop() << endl << endl;
		}
		catch (const exception& ex)
		{
			cerr << ex.what() << endl << endl;
		}
	} while (input != "0");

	return 0;
}

/* 
OUTPUT:

Enter expression: 10 15 + =
Answer: 25

Enter expression: 10 15 - =
Answer: -5

Enter expression: 2.5 3.5 + =
Answer: 6

Enter expression: 10 0 / =
Error: Division by zero!

Enter expression: 10 20 * /
Error: Too many operators!

Enter expression: -10 -30 - =
Answer: 20

Enter expression: 100 10 40 25 / * - -2/ =
Error: Too many operands!

Enter expression: 0

*/