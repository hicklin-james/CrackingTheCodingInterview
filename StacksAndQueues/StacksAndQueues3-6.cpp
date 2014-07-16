#include <stack>
#include <climits>
#include <iostream>

void printStack(std::stack<int> astack) {

	int totalSize = astack.size();
	int ints[totalSize];

	for (int i = 0; i < totalSize; i++) {
		std::cout << astack.top() << "\n";
		ints[i] = astack.top();
		astack.pop();
	}

	for (int i = totalSize-1; i >= 0; i--) {
		astack.push(ints[i]);
	}

	std::cout << "\n";
}

std::stack<int>* sortStack(std::stack<int>* myStack) {

	std::stack<int>* newStack = new std::stack<int>();
	int myStackSize = myStack->size();
	while (newStack->size() != myStackSize) {
		int localMin = INT_MAX;
		int localStackSize = myStack->size();
		int ints[localStackSize];
		int i;
		for (i = 0; i < localStackSize; i++) {
			int popped = myStack->top();
			myStack->pop();
			ints[i] = popped;
			if (popped < localMin)
				localMin = popped;
		}
		
		newStack->push(localMin);
		for (i = localStackSize-1; i >= 0; i--) {
			if (ints[i] != newStack->top()) {
				myStack->push(ints[i]);
			}
		}
	}

	return newStack;

}

int main() {

	std::stack<int> mystack;
	std::cout << "Initial Stack: \n";
	mystack.push(1);
	mystack.push(5);
	mystack.push(3);
	mystack.push(8);
	mystack.push(4);

	printStack(mystack);

	std::cout << "New Stack: \n";
	std::stack<int> *newStack = sortStack(&mystack);
	printStack(*newStack);

	return 0;
}