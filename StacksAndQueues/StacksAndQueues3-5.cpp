#include <stack>
#include <iostream>
#include <string>
#include <climits>

class MyQueue {
private:
	std::stack<int> inStack;
	std::stack<int> outStack;
public:
	MyQueue(){};
	void push(int i);
	int pop();
};

void MyQueue::push(int i) {

	inStack.push(i);

}

int MyQueue::pop() {
	int toReturn;
	if (outStack.size() > 0) {
		toReturn = outStack.top();
		outStack.pop();
	}
	else if (inStack.size() > 0) {
		int inSize = inStack.size();
		for (int i = 0; i < inSize; i++) {
			int popped = inStack.top();
			inStack.pop();
			outStack.push(popped);
		}
		toReturn = outStack.top();
		outStack.pop();
	}
	else {
		toReturn = INT_MAX;
	}
	return toReturn;
}

int main() {
	
	MyQueue myQueue;
	myQueue.push(5);
	std::cout << "Pushed: 5\n";
	myQueue.push(6);
	std::cout << "Pushed: 6\n";
	myQueue.push(7);
	std::cout << "Pushed: 7\n";
	myQueue.push(8);
	std::cout << "Pushed: 8\n";
	std::cout << "Popped: " << myQueue.pop() << "\n";
	std::cout << "Popped: " << myQueue.pop() << "\n";
	myQueue.push(9);
	std::cout << "Pushed: 9\n";
	std::cout << "Popped: " << myQueue.pop() << "\n";

	return 0;
}