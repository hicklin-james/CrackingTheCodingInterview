#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <climits>

class NodeWithMin {

public:
	int value;
	int min;
	NodeWithMin(int v, int m) { value = v; min = m; }

};

// This method keeps track of the local minimums
// Inherits from std::stack<NodeWithMin> -- ie. it inherits all the usual
// stack calls
class StackWithMin :  public std::stack<NodeWithMin> {
public:
	typedef std::stack<NodeWithMin> super;

	// virtual keyword overrides super function
	virtual void push(int value) {
		int newMin = std::min(value, min());
		NodeWithMin newNode(value, newMin);
		super::push(newNode);
	}

	int min() {
		if (empty()) {
			return INT_MAX;
		}
		else {
			return super::top().min;
		}
	}

	void printStack() {
		std::cout << "The current stack is:\n";
		int totalSize = super::size();
		int ints[totalSize];

		for (int i = 0; i < totalSize; i++) {
			std::cout << super::top().value << "\n";
			ints[i] = super::top().value;
			super::pop();
		}

		for (int i = totalSize-1; i >= 0; i--) {
			push(ints[i]);
		}
		std::cout << "\n\n";
	}

};

int main() {
	StackWithMin myStack;
	myStack.push(5);
	myStack.push(6);
	myStack.push(7);
	myStack.push(1);
	myStack.push(100);
	myStack.printStack();
	std::cout << "The current minimum is: " << myStack.min() << "\n\n";
	myStack.pop();
	myStack.printStack();
}
