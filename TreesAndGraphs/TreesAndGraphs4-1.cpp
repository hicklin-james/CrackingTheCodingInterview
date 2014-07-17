#include <queue>
#include <utility>
#include <iostream>
#include <algorithm>

class Node {
public:
	int value;
	Node *leftChild;
	Node *rightChild;
	Node(int val) { value = val; leftChild = NULL; rightChild = NULL;}
};

class Tree {
public:
	Node *head;
	Tree() {};
	void printTree(Node *node);
	bool isTreeBalanced(Node *node);
private:
	int minTreeLevel(Node *node);
	int maxTreeLevel(Node *node);
};

void Tree::printTree(Node *node) {
	if (node == NULL) {
		return;
	}

	int level = 0;
	typedef std::pair<Node*, int> nodeLevel;
	std::queue<nodeLevel> q;
	q.push(nodeLevel(node, 1));

	while (!q.empty()) {
		nodeLevel nl = q.front();
        q.pop();
        if (NULL != (node = nl.first)) {
            if (level != nl.second) {
                std::cout << " Level " << nl.second << ": ";
                level = nl.second;
            }
            std::cout << node->value << ' ';
            q.push(nodeLevel(node->leftChild,  1 + level));
            q.push(nodeLevel(node->rightChild, 1 + level));
        }
    }
    std::cout << "\n";
}

int Tree::minTreeLevel(Node *node) {
	if (node == NULL)
		return 0;
	else
		return 1 + std::min(minTreeLevel(node->leftChild), minTreeLevel(node->rightChild));
}

int Tree::maxTreeLevel(Node *node) {
	if (node == NULL)
		return 0;
	else
		return 1 + std::max(maxTreeLevel(node->leftChild), maxTreeLevel(node->rightChild));
}


bool Tree::isTreeBalanced(Node *node) {

	int minTreeLevel = Tree::minTreeLevel(node);
	int maxTreeLevel = Tree::maxTreeLevel(node);

	if (maxTreeLevel - minTreeLevel > 1) {
		std::cout << "The tree is not balanced\n";
		return false;
	}
	else {
		std::cout << "The tree is balanced\n";
		return true;
	}

}

int main() {

	Tree tree;
	Node head(5);
	Node another(2);
	Node third(3);
	head.leftChild = &another;
	head.rightChild = &third;
	tree.head = &head;
	std::cout << "Current Tree:\n";
	tree.printTree(tree.head);
	tree.isTreeBalanced(tree.head);
	std::cout<<"\nCurrent Tree:\n";
	head.leftChild = NULL;
	third.rightChild = &another;
	tree.printTree(tree.head);
	tree.isTreeBalanced(tree.head);

	return 0;
}


