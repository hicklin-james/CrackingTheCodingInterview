#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>      // std::setw
#include <math.h>       /* pow */

using namespace std;

class Node {
public:
	int value;
	Node *parent;
	Node *left;
	Node *right;
};

//------------------------------Setup functions from 4.3-------------------------------//

int myheight(Node *node) {
	if (node == NULL)
		return 0;
	else
		return 1 + std::max(myheight(node->left), myheight(node->right));
}

Node* buildTree(vector<int> array, int low, int high, Node *p) {
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
		newNode->parent = p;
		//cout << "This value: " << newNode->value << "\n";
		newNode->left = buildTree(array, low, mid-1, newNode);
		//cout << "AFTER LEFT: low: " << low << " high: " << high << " mid: " << mid << "\n";
		newNode->right = buildTree(array, mid+1, high, newNode);
		//cout << "AFTER RIGHT: low: " << low << " high: " << high << " mid: " << mid << "\n";
		return newNode;
	}
}

// Code to pretty print a tree
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

//------------------------------4.5-------------------------------//
int findInOrderSuccessor(Node *node) {

	Node *curr = node;

	if (curr == NULL)
		return -1;

	// If the node has a right child, it's in order successor is the leftmost child of the right subtree
	if (curr->right != NULL) {
		curr = curr->right;
		while(curr->left != NULL) {
			curr = curr->left;
		}
		return curr->value;
	}
	// if the node has no right child
	else {
		// if the node is a left child
		while (curr->parent != NULL) {
			if (curr->parent->left == curr) {
				return curr->parent->value;
			}
			else {
				curr = curr->parent;
			}
		}

		return -1;

	}

}

Node* findNthNode(Node *tree, int n) {
	Node *head = tree;

	while (head != NULL) {
		if (n == head->value) {
			return head;
		}
		if (n < head->value) {
			head = head->left;
		}
		else {
			head = head->right;
		}
	}
	return NULL;
}

int main() {
	vector<int> sorted;
	for (int i = 0; i < 70; i++) {
		sorted.push_back(i);
	}

	Node *balancedTree = buildTree(sorted, 0, sorted.size()-1, NULL);
	displayTree(balancedTree);

	Node *node26 = findNthNode(balancedTree, 26);
	int ios26 = findInOrderSuccessor(node26);
	cout << "Node 26ths in order successor: " << ios26 << "\n";
	Node *node27 = findNthNode(balancedTree, 27);
	int ios27 = findInOrderSuccessor(node27);
	cout << "Node 27ths in order successor: " << ios27 << "\n";
	Node *node51 = findNthNode(balancedTree, 51);
	int ios51 = findInOrderSuccessor(node51);
	cout << "Node 51sts in order successor: " << ios51 << "\n";
}
