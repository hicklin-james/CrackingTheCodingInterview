#include <iostream>
#include <stack>
#include <string>

class MyStack {

private:
	static const int stackSize = 100;
	int stacks[stackSize * 3];
	int stackTops[3];
	void push(int value, int stack);
	int pop(int stack);

public:
	MyStack() {for (int i = 0; i < 3; i++) { stackTops[i] = 0; }}
	void handlePush();
	void handlePop();
	void printStacks();
};

void MyStack::push(int value, int stack) {

	int index = (stackSize*stack) + stackTops[stack];
	
	stackTops[stack]++;
	stacks[index] = value;
	return;

}

int MyStack::pop(int stack) {

	int index = (stackSize*stack) + stackTops[stack] - 1;
	int val = stacks[index];
	stackTops[stack]--;
	return val;

}

void MyStack::handlePop() {

	int stack;
	std::cout << "Please enter the stack number - (Can be 0, 1 or 2):\n";
	std::cin >> stack;
	while (stack < 0 || stack > 2) {
		std::cout << "You entered an invalid stack number. Please try again.";
		std::cin >> stack;
	}

	pop(stack);

}

void MyStack::handlePush() {

	int stack;
	std::cout << "Please enter the stack number - (Can be 0, 1 or 2):\n";
	std::cin >> stack;
	while (stack < 0 || stack > 2) {
		std::cout << "You entered an invalid stack number. Please try again.";
		std::cin >> stack;
	}

	int value;
	std::cout << "Please enter a value to insert onto the stack:\n";
	std::cin >> value;

	push(value, stack);


}

void MyStack::printStacks() {

	std::cout << "\nStack 0:\n";
	int i;
	for (i = 0; i < stackTops[0]; i++) {
		std::cout << stacks[i] << " ";
	}
	std::cout << "\n\nStack 1:\n";
	for (i = 0; i < stackTops[1]; i++) {
		std::cout << stacks[i+stackSize] << " ";
	}
	std::cout << "\n\nStack 2:\n";
		for (i = 0; i < stackTops[2]; i++) {
		std::cout << stacks[i+(2*stackSize)] << " ";
	}
	std::cout << "\n\n";
}


int main() {

	MyStack myStack;

	std::string input = "";
	std::cout << "\nWelcome to my stack program!\n\n";
	while (input != "exit") {

		std::cout << "Please enter 'exit' to quit the program\n\nPlease enter a command: "; 
		std::cin >> input;

		if (input == "push") {
			myStack.handlePush();
			myStack.printStacks();
		}
		else if (input == "pop") {
			myStack.handlePop();
			myStack.printStacks();
		}
		else {
			std::cout << "Invalid Command\n\n";
		}
	}

	return 0;
}