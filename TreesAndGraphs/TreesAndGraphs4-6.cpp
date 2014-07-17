#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>      // std::setw
#include <math.h>       /* pow */

using namespace std;

class Node {
public:
	int value;
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

bool findEitherNode(Node *tree, Node *A, Node *B) {
	Node *head = tree;
	bool found = false;
	if (head == NULL) {
		return false;
	}
	if (head == A || head == B) {
		return true;
	}
	if (findEitherNode(head->left, A, B) || findEitherNode(head->right, A, B)) {
		return true;
	}
	else {
		return false;
	}

}

//----------------------------------4.6-------------------------------------//
int findCommonAncestor(Node *tree, Node *A, Node *B) {

	Node *head = tree;
	// if A and B are on left and right of head, we have found the first common ancestor
	while (head != NULL) {
		bool left = findEitherNode(head->left, A, B);
		bool right = findEitherNode(head->right, A, B);
		if (left && right) {
			return head->value;
		}
		else if (left) {
			// special case when a or b lies on the path to a or b
			if (head->left == A || head->left == B) {
				return head->value;
			}
			head = head->left;
		}
		else if (right) {
			// special case when a or b lies on the path to a or b
			if (head->right == A || head->right == B) {
				return head->value;
			}
			head = head->right;
		}
		else {
			return -1;
		}
	}
	return -1;
}

int main() {
	vector<int> sorted;
	for (int i = 0; i < 70; i++) {
		sorted.push_back(i);
	}

	Node *balancedTree = buildTree(sorted, 0, sorted.size()-1);
	displayTree(balancedTree);

	Node *n21 = findNthNode(balancedTree, 21);
	Node *n27 = findNthNode(balancedTree, 27);
	int ca21_27 = findCommonAncestor(balancedTree, n21, n27);
	cout << "The common ancestor of 21 and 27 is: " << ca21_27 << "\n";

	Node *n69 = findNthNode(balancedTree, 69);
	Node *n33 = findNthNode(balancedTree, 33);
	int ca69_33 = findCommonAncestor(balancedTree, n69, n33);
	cout << "The common ancestor of 69 and 33 is: " << ca69_33 << "\n";

	Node *n8 = findNthNode(balancedTree, 8);
	Node *n9 = findNthNode(balancedTree, 9);
	int ca8_9 = findCommonAncestor(balancedTree, n8, n9);
	cout << "The common ancestor of 8 and 9 is: " << ca8_9 << "\n";

	Node *n10 = findNthNode(balancedTree, 10);
	int ca10_9 = findCommonAncestor(balancedTree, n10, n9);
	cout << "The common ancestor of 10 and 9 is: " << ca10_9 << "\n";
}
