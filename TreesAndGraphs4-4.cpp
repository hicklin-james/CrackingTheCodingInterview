/**
Given a binary search tree, design an algorithm which 
creates a linked list of all the nodes at each depth 
(i.e., if you have a tree with depth D, you’ll have D 
linked lists).
**/

/** Solution will require breadth first search, adding
a new linked list at each level **/


#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>      // std::setw
#include <math.h>       /* pow */
#include <utility>

using namespace std;

class LinkedListNode {
public:
	int value;
	LinkedListNode *next;
};

class Node {
public:
	int value;
	Node *left;
	Node *right;
};

int myheight(Node *node) {
	if (node == NULL)
		return 0;
	else
		return 1 + std::max(myheight(node->left), myheight(node->right));
}

Node* buildTree(vector<int> array, int low, int high) {
	//cout << "Array size: " << array.size() << "\n";
	if (low > high || high < 0) {
		//cout << "hit a base case\n";
		return NULL;
	}
	else {
		int mid = ((high - low) / 2) + low;
		//cout << "BEFORE: low: " << low << " high: " << high << " mid: " << mid << "\n";
		Node *newNode = new Node();
		newNode->value = array.at(mid);
		//cout << "This value: " << newNode->value << "\n";
		newNode->left = buildTree(array, low, mid-1);
		//cout << "AFTER LEFT: low: " << low << " high: " << high << " mid: " << mid << "\n";
		newNode->right = buildTree(array, mid+1, high);
		//cout << "AFTER RIGHT: low: " << low << " high: " << high << " mid: " << mid << "\n";
		return newNode;
	}
}

void displayTree(Node* root){
	const int box_size = 3;
	queue<Node*> q;
	q.push(root);
	size_t current_level_nodes = 1;
	size_t next_current_level_nodes = 0;
	size_t level = 1;
	int height = myheight(root);
	int padding = box_size * (pow(2, height - level) - 1);
	std::cout << std::setw(padding / 2) << "";
	while (level <= height)
	{
	    std::cout << std::setw(box_size);
	    if (q.front() != NULL)
	    {
	        std::cout << q.front()->value;
	        q.push(q.front()->left);
	        q.push(q.front()->right);
	    }
	    else
	    {
	        std::cout << "";
	        q.push(NULL);
	        q.push(NULL);
	    }
	    next_current_level_nodes += 2;
	    std::cout << std::setw(padding) << "";
	    q.pop();
	    --current_level_nodes;
	    if (current_level_nodes == 0)
	    {
	        current_level_nodes = next_current_level_nodes;
	        next_current_level_nodes = 0;
	        ++level;
	        padding = box_size * (pow(2, height - level) - 1);
	        std::cout << "\n" << std::setw(padding / 2) << "";
	    }
	}
}

// Main code for the question - Rest is taken from 4.3!!
vector<LinkedListNode*> createLinkedLists(Node *tree) {
	queue<pair<Node*,int> > workingNodes;
	pair<Node*,int> first(tree, 0);
	int level = 0;
	workingNodes.push(first);

	vector<LinkedListNode*> result;

	pair<LinkedListNode*, LinkedListNode*> bufferNode(NULL,NULL);

	while (!workingNodes.empty()) {
		pair<Node*,int> thisPair = workingNodes.front();
		Node *thisNode = thisPair.first;
		workingNodes.pop();
		if (thisNode != NULL) {
			if (level != thisPair.second) {
	                //std::cout << " Level " << nl.second << ": ";
	                //level = nl.second;
				// save the current vector and reset it
				result.push_back(bufferNode.first);
				bufferNode.first = NULL;
				bufferNode.second = NULL;
				level = thisPair.second;
	         }
	        LinkedListNode *newNode = new LinkedListNode();
	        newNode->value = thisNode->value;
	         if (bufferNode.first == NULL) {
	            bufferNode.first = newNode;
	            bufferNode.second = newNode;
	         }
	         else {
	            //LinkedListNode *lastNode = findLastNodeOfList(bufferNode);
	            bufferNode.second->next = newNode;
	            bufferNode.second = newNode;
	         }
	        workingNodes.push(pair<Node*, int>(thisNode->left,  1 + level));
	        workingNodes.push(pair<Node*, int>(thisNode->right, 1 + level));
	     }
	}
	
	result.push_back(bufferNode.first); // to get the last one

	return result;

}

void printLinkedLists(vector<LinkedListNode*> linkedLists) {
	for (int i = 0; i < linkedLists.size(); i++) {
		cout << "Linked List " << i << ":";
		LinkedListNode *thisNode = linkedLists.at(i);
		while (thisNode != NULL) {
			cout << "->" << thisNode->value;
			thisNode = thisNode->next;
		}
		cout << "\n";
	}
}

int main() {
	vector<int> sorted;
	for (int i = 0; i < 70; i++) {
		sorted.push_back(i);
	}

	// Using code from 4.3 to generate a largish tree
	Node *balancedTree = buildTree(sorted, 0, sorted.size()-1);
	displayTree(balancedTree);

	// creating the linked lists and printing them
	vector<LinkedListNode*> linkedLists = createLinkedLists(balancedTree);
	printLinkedLists(linkedLists);

}
