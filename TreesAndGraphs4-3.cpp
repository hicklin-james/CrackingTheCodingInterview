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

int main() {
	vector<int> sorted;
	for (int i = 0; i < 70; i++) {
		sorted.push_back(i);
	}

	Node *balancedTree = buildTree(sorted, 0, sorted.size()-1);
	displayTree(balancedTree);
}
