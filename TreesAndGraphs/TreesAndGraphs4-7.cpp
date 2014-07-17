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

//-------------------------------4.7----------------------------//
/**
You have two very large binary trees: T1, with millions of nodes, and T2, 
with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.
**/

// t1 is from the original tree, so check for null
// on t2, NOT t1
bool compareTrees(Node *t1, Node *t2) {
	if (t2 == NULL)
		return true;
	if (t1 == NULL)
		return false;
	if (t1->value == t2->value) {
		return compareTrees(t1->left, t2->left) && compareTrees(t1->right, t2->right);
	}	
	else {
		return false;
	}
}

bool isSubtree(Node *t2, Node *t1) {

	if (t1 == NULL)
		return false;
	if (t1->value == t2->value) {
		if (compareTrees(t1, t2)) {
			return true;
		}
	}
	return isSubtree(t2, t1->right) || isSubtree(t2, t1->left);

}

int main() {
	vector<int> sorted;
	for (int i = 0; i < 70; i++) {
		sorted.push_back(i);
	}

	cout << "Initial Tree:\n";
	Node *balancedTree = buildTree(sorted, 0, sorted.size()-1);
	displayTree(balancedTree);
	cout << "\n";

	vector<int> sorted1;
	for (int s = 0; s < 17; s++) {
		sorted1.push_back(s);
	}

	cout << "Check if this is a subtree of the initial tree:\n";
	Node *balancedTree1 = buildTree(sorted1, 0, sorted1.size()-1);
	displayTree(balancedTree1);
	cout << "\n";
	// tree1 is a subtree of tree
	if (isSubtree(balancedTree1, balancedTree)) {
		cout << "Tree1 is a subtree\n\n";
	}
	else {
		cout << "Tree1 is not a subtree\n\n";
	}

	vector<int> sorted2;
	for (int s = 0; s < 16; s++) {
		sorted2.push_back(s);
	}

	cout << "Check if this is a subtree of the initial tree:\n";
	Node *balancedTree2 = buildTree(sorted2, 0, sorted2.size()-1);
	displayTree(balancedTree2);

	// tree1 is a subtree of tree
	if (isSubtree(balancedTree2, balancedTree)) {
		cout << "Tree2 is a subtree\n\n";
	}
	else {
		cout << "Tree2 is not a subtree\n\n";
	}
}
