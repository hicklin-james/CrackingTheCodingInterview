#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

class Node {
public:
	int val;
	string state;
	vector<Node*> siblings;

	Node(int value) {val = value;}
	vector<Node*> getAdjacent();
	void addSibling(Node* sibling);
};

class Graph {
public:
	vector<Node*> allNodes;
	
	vector<Node*> getAllNodes();
	void addNode(Node* node);
	bool findPath(Node *A, Node *B);
};

vector<Node*> Graph::getAllNodes() {
	return allNodes;
}

void Graph::addNode(Node* node) {
	allNodes.push_back(node);
}

bool Graph::findPath(Node *A, Node *B) {
	vector<Node*> allNodes = getAllNodes();
	int i;
	for (i = 0; i < allNodes.size(); i++) {
		Node *thisNode = allNodes.at(i);
		thisNode->state = "unvisited";
	}
	Node *front = A;
	queue<Node*> searchQueue;
	searchQueue.push(front);
	while (!searchQueue.empty()) {
		Node *curr = searchQueue.front();
		searchQueue.pop();
		if (curr == B) {
			return true;
		}
		else {
			if (curr->state != "visited") {
				vector<Node*> siblings = curr->getAdjacent();
				for (i = 0; i < siblings.size(); i++) {
					searchQueue.push(siblings.at(i));
				}
			}
		}
		curr->state = "visited";
	}
	return false;
}

vector<Node*> Node::getAdjacent() {
	return siblings;
}

void Node::addSibling(Node* sibling) {
	siblings.push_back(sibling);
}

int main() {

	Node A(1);
	Node B(2);
	Node C(3);
	Node D(4);
	Node E(5);
	A.addSibling(&B);
	B.addSibling(&C);
	B.addSibling(&D);
	D.addSibling(&E);
	E.addSibling(&B);

	Graph G;
	G.addNode(&A);
	G.addNode(&B);
	G.addNode(&C);
	G.addNode(&D);
	G.addNode(&E);

	bool AToE = G.findPath(&A, &E);
	bool DToB = G.findPath(&D, &B);

	cout << "A to E: " << AToE << "\n";
	cout << "G to E: " << DToB << "\n";


	return 0;
}