#include <iostream>
#include <utility>
#include <unordered_set>
#include <string>
#include <sstream>


typedef struct Node {
	struct Node *next;
	int value;
} Node;

// --------------------- Basic Linked List Functions --------------------- //

// Adds an element to the end of the list
void addToList(int value, Node *head) {

	Node *thisNode = head;

	Node *newNode = new Node;
	newNode->value = value;
	newNode->next = NULL;

	if (thisNode == NULL) {
		thisNode = newNode;
		return;
	}
	while (thisNode->next != NULL) {
		thisNode = thisNode->next;
	}
	thisNode->next = newNode;
	return;

}

// Remove the first occurence of this value from the list
// If it doesn't exist, do nothing
void removeFromList(int value, Node &head) {

	Node *prev = NULL;
	Node *thisNode = &head;

	while (thisNode != NULL) {

		if (thisNode->value == value) {

			// Delete from the start
			if (prev == NULL) {
				head = *thisNode->next;
				return;
			}

			// Delete from the end
			if (thisNode->next == NULL) {
				prev->next = NULL;
				return;
			}

			prev->next = thisNode->next;
			free(thisNode);
			thisNode = NULL;
			return;
		}

		prev = thisNode;
		thisNode = thisNode->next;

	}

}

void prettyPrintList(Node *head) {

	Node *thisNode = head;
	int maxCounter = 0;
	while (thisNode != NULL && maxCounter < 10) {
		std::cout << "Value: " << thisNode->value << "\n";
		thisNode = thisNode->next;
		maxCounter++;
	}
	std::cout << "\n\n";
}

// --------------------- 2.1 --------------------- //

// Removes duplicates from the linked list
void removeDuplicates(Node &head) {

	Node *thisNode = &head;
	Node *prev = NULL;
	std::unordered_set<int> set; 
	while (thisNode != NULL) {
		if (set.insert(thisNode->value).second == false) {
			prev->next = thisNode->next;
			thisNode = thisNode->next;

		}
		else {
			prev = thisNode;
			thisNode = thisNode->next;
		}
	}
}

// Removes duplicates without using a set - instead it uses
// a separate pointer to check all the previous nodes for 
// duplicates
void removeDuplicatesNoBuffer(Node &head) {

	Node *thisNode = &head;
	Node *prev = NULL;
	while (thisNode != NULL) {
		Node *checker = &head;
		int flag = 0;
		while (checker != thisNode) {
			if (checker->value == thisNode->value) {
				prev->next = thisNode->next;
				flag = 1;
				break;
			}
			checker = checker->next;
		}
		if (flag == 0) {
			prev = thisNode;
		}
		thisNode = thisNode->next;
	}
}

// --------------------- 2.2 --------------------- //
std::pair<int, bool> findNthLast(Node &head, int n) {

	Node *thisNode = &head;
	// First count the elements
	int totalCount = 0;
	std::pair <int, bool> badAccess (-1, false);
	while (thisNode != NULL) {
		totalCount++;
		thisNode = thisNode->next;
	}
	// check that n is within bounds
	if (n > totalCount || n < 0) {
		return badAccess;
	}
	// next, find the element that is n away from the end
	int counter = 0;
	thisNode = &head;
	while (thisNode != NULL) {
		if (totalCount-counter == n) {
			std::pair <int,bool> found (thisNode->value, true);
			return found;
		}
		counter++;
		thisNode = thisNode->next;
	}

	return badAccess;
}

// --------------------- 2.3 --------------------- //
void deleteNode(Node &node) {
	Node *thisNode = &node;
	node = *thisNode->next;
	return;
}

// --------------------- 2.4 --------------------- //
int addLinkedListNumbers(Node &a, Node &b) {

	Node *aNode = &a;
	Node *bNode = &b;

	std::ostringstream convert;
	std::string aString = "";

	while (aNode != NULL) {
		int aVal = aNode->value;
		convert << aVal;
		aString.insert(0,convert.str());
		convert.str("");
		convert.clear();
		aNode = aNode->next;
	}
	//aString.append(convert.str());
	int aVal = atoi(aString.c_str());

	std::string bString = "";

	while (bNode != NULL) {
		int bVal = bNode->value;
		convert << bVal;
		bString.insert(0,convert.str());
		convert.str("");
		convert.clear();
		bNode = bNode->next;
	}

	//bString.append(convert.str());
	int bVal = atoi(bString.c_str());

	return aVal+bVal;

}

// --------------------- 2.5 --------------------- //
std::pair<int,bool> findBadNode(Node &head) {

	Node *thisNode = &head;
	Node *prev = NULL;
	std::unordered_set<Node *> set; 
	while (thisNode != NULL) {
		if (set.insert(thisNode).second == false) {
			std::pair<int,bool> found (thisNode->value, true);
			return found;

		}
		else {
			prev = thisNode;
			thisNode = thisNode->next;
		}
	}

	std::pair<int,bool> allgood (-1, false);
	return allgood;
}

int main() {

	std::cout << "Starting the program\n\n";

	std::cout << "2.1\n\n";

	Node head;
	head.value = 3;
	head.next = NULL;

	addToList(5, &head);
	addToList(5, &head);
	addToList(5, &head);
	addToList(6, &head);
	addToList(6, &head);
	addToList(6, &head);
	addToList(6, &head);

	Node headcopy;
	headcopy.value = 3;
	headcopy.next = NULL;

	addToList(5, &headcopy);
	addToList(5, &headcopy);
	addToList(5, &headcopy);
	addToList(6, &headcopy);
	addToList(6, &headcopy);
	addToList(6, &headcopy);
	addToList(6, &headcopy);


	// 2.1
	// Write code to remove duplicates from an unsorted linked list.
	// How would you solve this problem if a temporary buffer is not allowed?

	std::cout << "This is the current linked list:\n";
	prettyPrintList(&head);
	std::cout << "After removing the duplicates with a buffer:\n";
	removeDuplicates(head);
	prettyPrintList(&head);
	std::cout << "After removing the duplicates without a buffer:\n";
	removeDuplicatesNoBuffer(headcopy);
	prettyPrintList(&head);

	// 2.2
	// Implement an algorithm to find the nth to last element of a singly linked list.

	std::cout << "2.2\n\n";
	addToList(7, &head);
	addToList(8, &head);
	addToList(9, &head);
	addToList(10, &head);
	addToList(11, &head);
	std::cout << "This is the current linked list:\n";
	prettyPrintList(&head);
	std::cout << "The 2nd to last element is: " << findNthLast(head, 2).first << " " << std::boolalpha << findNthLast(head, 2).second << "\n";
	std::cout << "The last element is: " << findNthLast(head, 1).first << " " << std::boolalpha << findNthLast(head, 1).second << "\n";
	std::cout << "The 8th last last element is: " << findNthLast(head, 8).first << " " << std::boolalpha << findNthLast(head, 8).second << "\n";
	std::cout << "The 9th last element is: " << findNthLast(head, 9).first << " " << std::boolalpha << findNthLast(head, 9).second << "\n";

	// 2.3
	// Implement an algorithm to delete a node in the middle of a single linked list, given only access to that node.
	// 	EXAMPLE
	// 	Input: the node ‘c’ from the linked list a->b->c->d->e
	// 	Result: nothing is returned, but the new linked list looks like a->b->d->e

	std::cout << "\n\n2.3\n\n";
	std::cout << "This is the current linked list:\n";
	prettyPrintList(&head);
	// lets go to the third node
	Node *thirdNode = &head;
	int i = 0;
	while (i != 2) {
		thirdNode = thirdNode->next;
		i++;
	}
	deleteNode(*thirdNode);
	std::cout << "This is the linked list after removing the third node\n";
	prettyPrintList(&head);

	// 2.4
	// You have two numbers represented by a linked list, where each node contains a single digit. The digits are 
	// stored in reverse order, such that the 1’s digit is at the head of the list. Write a function that adds the two 
	// numbers and returns the sum as a linked list.
	//   EXAMPLE
	//   Input: (3 -> 1 -> 5) + (5 -> 9 -> 2)
	//   Output: 8 -> 0 -> 8

	std::cout << "2.4\n\n";
	Node a;
	Node a1;
	Node a2;
	a.value = 3;
	a1.value = 1;
	a2.value = 5;
	a.next = &a1;
	a1.next = &a2;
	std::cout << "a:\n";
	prettyPrintList(&a);
	Node b;
	Node b1;
	Node b2;
	b.value = 5;
	b1.value = 9;
	b2.value = 2;
	b.next = &b1;
	b1.next = &b2;
	std::cout << "b:\n";
	prettyPrintList(&b);
	int added = addLinkedListNumbers(a, b);
	std::cout << "a + b = " << added << "\n\n";

	// 2.5
	// Given a circular linked list, implement an algorithm which returns node at the begin- ning of the loop.
	// DEFINITION
	// Circular linked list: A (corrupt) linked list in which a node’s next pointer points to an earlier node, so as to make a loop in the linked list.
	//  EXAMPLE
	//  input: A -> B -> C -> D -> E -> C [the same C as earlier]
	//  output: C

	std::cout << "2.5\n\n";
	std::cout << "This is the current Linked List\n";
	prettyPrintList(&head);

	// Setup a bad node
	Node *badNode = &head;
	i = 0;
	while (i != 2) {
		badNode = badNode->next;
		i++;
	}

	Node *headTemp = &head;
	while (headTemp->next != NULL) {
		headTemp = headTemp->next;
	}
	headTemp->next = badNode;
	std::cout << "This is the corrupt Linked List\n";
	prettyPrintList(&head);
	std::pair<int,bool> badVal = findBadNode(head);
	std::cout << "This is the bad node: ";
	std::cout << badVal.first << " " << std::boolalpha << badVal.second << "\n\n";

	std::cout << "This is a good linked list\n";
	prettyPrintList(&headcopy);
	badVal = findBadNode(headcopy);
	std::cout << "This is the bad node: ";
	std::cout << badVal.first << " " << std::boolalpha << badVal.second << "\n\n";

}

