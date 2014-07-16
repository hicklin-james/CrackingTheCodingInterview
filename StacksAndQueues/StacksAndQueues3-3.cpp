#include <iostream>
#include <string>
#include <vector>
#include <stack>

class SetOfStacks {
private:
	int MAXSIZE;
	std::vector<std::stack<int> > stacks;
	void printStack(std::stack<int> astack);
	void shiftStacks(int i);

public:
	SetOfStacks(int maxSize) { 
		MAXSIZE = maxSize;
		std::stack<int> emptyStack;
		stacks.push_back(emptyStack);
	}

	void push(int i);
	int pop();
	int popAt(int i);
	void printStacks();
};

void SetOfStacks::push(int i) {
	std::stack<int>& backStack = stacks.back();

	if (backStack.size() >= MAXSIZE) {
		std::stack<int> newStack;
		newStack.push(i);
		stacks.push_back(newStack);
	}
	else {
		backStack.push(i);
	}
}

int SetOfStacks::popAt(int i) {
	std::stack<int>& stackToPop = stacks.at(i);
	int toReturn = stackToPop.top();
	stackToPop.pop();
	// Shift stacks after i left
	shiftStacks(i);
	return toReturn;
}

void SetOfStacks::shiftStacks(int i) {
	int totalNumberOfStacks = stacks.size();
	int q = i+1;
	while (q <= totalNumberOfStacks-1) {
		// move the bottom element from this stack
		// to the left stack
		std::stack<int>& thisStack = stacks.at(q);
		int stackSize = thisStack.size();
		int ints[stackSize-1];
		for (int s = 0; s < stackSize - 1; s++) {
			ints[s] = thisStack.top();
			thisStack.pop();
		}
		int toShift = thisStack.top();
		thisStack.pop();
		std::stack<int>& previousStack = stacks.at(q-1);
		previousStack.push(toShift);
		for (int s = stackSize-2; s >= 0; s--) {
			//std::cout << "We are pushing: " << s << "\n";
			thisStack.push(ints[s]);
		}

		q++;
	}

	std::stack<int>& finalStack = stacks.at(q-1);
	//finalStack.pop();
	//printStack(finalStack);
	if (finalStack.size() == 0) {
		stacks.pop_back();
	}
}

int SetOfStacks::pop() {
	std::stack<int>& backStack = stacks.back();
	int toReturn = backStack.top();
	std::cout << "We popped: " << toReturn << "\n\n";
	backStack.pop();
	if (stacks.size() != 1 && backStack.size() == 0) {
		stacks.pop_back();
	}
	return toReturn;
}

void SetOfStacks::printStack(std::stack<int> astack) {

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

}

void SetOfStacks::printStacks() {
	for (int i = 0; i < stacks.size(); i++) {
		std::cout << "Stack " << i+1 << "\n";
		printStack(stacks.at(i));
	}
	std::cout << "\n";
}

int main() {

	SetOfStacks stacks(2);
	stacks.push(3);
	stacks.push(5);
	stacks.push(6);
	stacks.push(7);
	stacks.push(8);
	stacks.push(9);
	stacks.push(10);
	stacks.push(11);
	stacks.printStacks();
	stacks.popAt(0);
	stacks.printStacks();

}