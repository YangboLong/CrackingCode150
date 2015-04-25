#include <iostream>
#include <vector>

struct Node {
	int key;
	Node* prev;
	Node* next;
};

class DoublyLinkedList {
public:
	DoublyLinkedList() { head = NULL; }
	void RemoveDuplicate(int);
	void ListInsert(Node&);
	Node* ListDelete(Node*);
	void ListPatition(Node*, int);
	Node* GetHead() { return head; }
private:
	Node* head;
};

struct Item {
	int key;
	Item* next;
};

class SinglyLinkedList {
public:
	SinglyLinkedList() { head = NULL; }
	Item* GetHead() { return head; }
	std::vector<int> FindK2End(Item*, int);
	void ListInsert(Item&);
	void ListDelete(Item&);
	void ListDelete(Item*);
	Item* FindBeginning(Item*);
	bool IsPalindrome(Item*);
private:
	Item* head;
};

Item* SumLists(Item*, Item*);

int main()
{
	// 2.1 Write code to remove duplicates from an unsorted linked list.
	DoublyLinkedList L1;
	Node node1 = {1, NULL, NULL};
	L1.ListInsert(node1);
	Node node2 = {4, NULL, NULL};
	L1.ListInsert(node2);
	Node node3 = {16, NULL, NULL};
	L1.ListInsert(node3);
	Node node4 = {9, NULL, NULL};
	L1.ListInsert(node4);
	Node node5 = {4, NULL, NULL};
	L1.ListInsert(node5);
	L1.RemoveDuplicate(4);
	
	// 2.2 Implement an algorithm to find the kth to last element of a singly linked list.
	SinglyLinkedList L2;
	Item item1 = {1, NULL};
	L2.ListInsert(item1);
	Item item2 = {4, NULL};
	L2.ListInsert(item2);
	Item item3 = {16, NULL};
	L2.ListInsert(item3);
	Item item4 = {9, NULL};
	L2.ListInsert(item4);
	Item item5 = {4, NULL};
	L2.ListInsert(item5);
	std::vector<int> elements = L2.FindK2End(L2.GetHead(), 3);

	// 2.3 Implement an algorithm to delete a node in the middle of a singly linked list, given only access to that node.
	L2.ListDelete(item3);
	
	// 2.4 Write code to partition a linked list around a value x, such that all nodes less than x come before all nodes greater than or equal to x.
	DoublyLinkedList L3;
	Node node6 = {1, NULL, NULL};
	L3.ListInsert(node6);
	Node node7 = {4, NULL, NULL};
	L3.ListInsert(node7);
	Node node8 = {3, NULL, NULL};
	L3.ListInsert(node8);
	Node node9 = {9, NULL, NULL};
	L3.ListInsert(node9);
	Node node10 = {4, NULL, NULL};
	L3.ListInsert(node10);
	L3.ListPatition(L3.GetHead(), 4);

	SinglyLinkedList L4, L5;
	Item x1 = {6, NULL};
	L4.ListInsert(x1);
	Item x2 = {1, NULL};
	L4.ListInsert(x2);
	Item x3 = {7, NULL};
	L4.ListInsert(x3);
	Item y1 = {2, NULL};
	L5.ListInsert(y1);
	Item y2 = {9, NULL};
	L5.ListInsert(y2);
	Item y3 = {5, NULL};
	L5.ListInsert(y3);
	Item* item = SumLists(&x3, &y3);

	SinglyLinkedList L6;
	Item z1 = {1, NULL};
	Item z2 = {2, NULL};
	Item z3 = {3, NULL};
	Item z4 = {2, NULL};
	Item z5 = {1, NULL};
	L6.ListInsert(z1);
	L6.ListInsert(z2);
	L6.ListInsert(z3);
	L6.ListInsert(z4);
	L6.ListInsert(z5);
	bool is_palin = L6.IsPalindrome(&z5);

	return 0;
}

// 2.1 Write code to remove duplicates from an unsorted linked list.
Node* SearchNode(Node* x, int key) {
	while(x != NULL && x->key != key)
		x = x->next;
	
	return x;
}
void DoublyLinkedList::RemoveDuplicate(int key) {
	Node* x;
	x = head;
	x = SearchNode(x, key); // find the first node with "key", do nothing to it
	if(x == NULL)	return; // not key found
	x = x->next; // move forward to the next
	while(x) { // iterate until the end of the linked list
		x = SearchNode(x, key); // find the duplicates
		if(x == NULL)	return;
		if(x->key == key)
			x = ListDelete(x);
	}
}
void DoublyLinkedList::ListInsert(Node& x) {
	x.next = head;
	if(head != NULL)
		head->prev = &x;
	head = &x;
	x.prev = NULL;
}
Node* DoublyLinkedList::ListDelete(Node* x){
	Node* ret = x->next;

	if(x->prev != NULL) 
		x->prev->next = x->next;
	else  // the node is head
		head = x->next;
	if(x->next != NULL) 
		x->next->prev = x->prev;
	
	return ret;
}

// 2.2 Implement an algorithm to find the kth to last element of a singly linked list.
std::vector<int> SinglyLinkedList::FindK2End(Item* list_head, int k) {
	std::vector<int> ret; // store kth to last keys
	for(int i = 1; i < k; i++) { // find the kth element
		list_head = list_head->next;
		if(list_head == NULL) // list length is smaller than k
			return ret;
	}
	while(list_head != NULL) {
		ret.push_back(list_head->key);
		list_head = list_head->next;
	}

	return ret;
}
void SinglyLinkedList::ListInsert(Item& x) {
	x.next = head;
	head = &x;
}

// 2.3 Implement an algorithm to delete a node in the middle of a singly linked list, given only access to that node.
void SinglyLinkedList::ListDelete(Item& node) {
	if(node.next == NULL) { // node is the last element in the list
		std::cerr << "Node is not in the middle of list." <<std::endl;
		exit(EXIT_FAILURE);
	}
	if(node.next->next == NULL) { // node is one before the last element in the list
		node.key = node.next->key;
		node.next = NULL;
	}
	else {
		node.key = node.next->key;
		ListDelete(*node.next);
	}
}

// 2.4 Write code to partition a linked list around a value x, such that all nodes less than x come before all nodes greater than or equal to x.
// The code doesn't work if there are more than 1 node that is smaller than given value, but it works if there is only 1 smaller value.
void DoublyLinkedList::ListPatition(Node* node, int value) {
	while(node) { 
		if(node->key >= value) {
			if(node->next) // node is not the last one
				node = node->next;
			else // node is the last one
				return;
		}
		else {
			Node tmp = {node->key, NULL, NULL};
			ListInsert(tmp); // move smaller element to the front of list
			node = ListDelete(node); // move to the next node
		}
	}
}

// 2.5 Write a function that adds the two numbers and returns the sum as a linked list.
SinglyLinkedList L;
std::vector<Item> SumRet; // global variable
Item* SumLists(Item* head1, Item* head2) {
	int num1 = 0, digit1 = 1;
	int num2 = 0, digit2 = 1;
	std::vector<int> lsb;
	Item sum_ret;
	int sum;
	while(head1 != NULL) { // compute the first number
		num1 += head1->key * digit1;
		head1 = head1->next;
		digit1 *= 10;
	}
	while(head2 != NULL) { // compute the second number
		num2 += head2->key * digit2;
		head2 = head2->next;
		digit2 *= 10;
	}
	sum = num1 + num2;
	while(sum != 0) { // store digits into a vector in the backward order
		lsb.push_back(sum % 10);
		sum /= 10;
	}
	int len = lsb.size() - 1;
	for(int i = len; i >= 0; i--) { // create linked list
		sum_ret.key = lsb[i];
		sum_ret.next = NULL;
		SumRet.push_back(sum_ret); // when inserting the second item into L, after this line the linked list L corrupted, similar issue as 2.4
		L.ListInsert(SumRet[len - i]);
	}

	return &SumRet[0];
}

// 2.6 Given a circular linked list, implement an algorithm which returns the node at the beginning of the loop.
// Read the analysis of the book's solution. How to create a looped linked list?
Item* SinglyLinkedList::FindBeginning(Item* head) {
	// 1. Create two pointers, Fast Pointer and Slow Pointer.
	Item *fast_pointer = head, *slow_pointer = head;
	// 2. Move Fast Pointer at a rate of 2 steps and Slow Pointer at a rate of 1 step.
	while(fast_pointer != slow_pointer) {
		fast_pointer = fast_pointer->next->next;
		slow_pointer = slow_pointer->next;
	}
	// 3. When they collide, move Slow Pointer to Linked List Head. Keep Fast Pointer where it it.
	slow_pointer = head;
	// 4. Move Slow Pointer and Fast Pointer at a rate of one step. Return the new collision point.
	while(slow_pointer != fast_pointer) {
		slow_pointer = slow_pointer->next;
		fast_pointer = fast_pointer->next;
	}
	return fast_pointer;
}

// 2.7 Implement a function to check if a linked list is a palindrome.
bool SinglyLinkedList::IsPalindrome(Item* head) {
	std::vector<int> values;
	while(head != NULL) {
		values.push_back(head->key);
		head = head->next;
	}
	int *p = &values[0], *q = &values[values.size() - 1];
	while(*p == *q) {
		p++;
		q--;
		if(p == q || p - q == 1)
			return true;
	}

	return false;
}
