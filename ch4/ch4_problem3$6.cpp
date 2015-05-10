#include <iostream>
#include <vector>

class Node {
public:
	Node() : key(-1), left(NULL), right(NULL), parent(NULL) {}
	Node(int value) : key(value), left(NULL), right(NULL), parent(NULL) {}
	int GetKey() { return key; }
	Node* GetLeft() { return left; }
	Node* GetRight() { return right; }
	Node* GetParent() { return parent; }
	void SetParent(Node* node) { parent = node; }
	void SetLeft(Node* node) { left = node; }
	void SetRight(Node* node) { right = node; }
	void SetKey(int value)	{ key = value; }
private:
	int key;
	Node* left;
	Node* right;
	Node* parent;
};
class Tree {
public:
	Tree() : root(NULL) {}
	void TreeInsert(Tree*, Node*);
	Node* GetRoot() { return root; }
	Node* GetLeft() { return root->GetLeft(); }
	Node* GetRight() { return root->GetRight(); }
	Node* FindSuccessor(Node*);
private:
	Node* root;
};
void Tree::TreeInsert(Tree* tree, Node* node) {
	Node* y = NULL; // trailing pointer
	Node* x = tree->root;
	while(x != NULL) {
		y = x;
		if(node->GetKey() < x->GetKey())
			x = x->GetLeft();
		else
			x = x->GetRight();
	}

	node->SetParent(y);
	if(y == NULL)
		tree->root = node; // tree was empty
	else if(node->GetKey() < y->GetKey())
		y->SetLeft(node);
	else
		y->SetRight(node);
}
// 4.3 Given a sorted (increasing order) array with unique integer elements, write an algorithm to create a binary search tree with minimal height.
void CreateBST(Tree* &tree, std::vector<int> &arr, int start, int end) {
	if(start > end)
		return;
	int mid = (start + end) / 2;
	Node* node = new Node; // save all the tree nodes in heap
	node->SetKey(arr[mid]);
	tree->TreeInsert(tree, node);
	CreateBST(tree, arr, start, mid - 1);
	CreateBST(tree, arr, mid + 1, end);
	return;
}
void DeleteBST(Node* root) {
	if(root == NULL)
		return;
	if(root->GetLeft() == NULL && root->GetRight() == NULL) {
		delete root;
		return;
	}
	DeleteBST(root->GetLeft());
	DeleteBST(root->GetRight());
	delete root;
}
// 4.6 Write an algorithm to find the 'next' node (i.e., in-order successor) of a given node in a binary search tree.
Node* Tree::FindSuccessor(Node* node) {
	if(node->GetRight() != NULL) { // node has right child/subtree
		node = node->GetRight();
		while(node->GetLeft() != NULL) { // go to the left-most node (min node) in the right subtree
			node = node->GetLeft();
		}
		return node;
	}

	Node* parent = node->GetParent();
	// go up the tree until we encounter a node that is the left child of its parent
	while(parent != NULL && node == parent->GetRight()) {
		node = parent;
		parent = parent->GetParent();
	}
	return parent;
}

int main()
{
	Tree tree;
	Tree* t = &tree;
	std::vector<int> arr;
	for(int i = 0; i < 10; i++) {
		arr.push_back(i);
	}

	CreateBST(t, arr, 0, 9); // problem 4.3
	Node* successor = tree.FindSuccessor(tree.GetRoot()); // problem 4.6

	DeleteBST(tree.GetRoot()); // free the tree nodes in heap
	
	return 0;
}

/*
// Issue with local variable, Node* n
// http://stackoverflow.com/questions/4570366/pointer-to-local-variable
// To fix the issue, need to either declare a global variable or allocate it in heap.
void CreateBST(Tree* tree, std::vector<int> &arr, int start, int end) {
	if(start > end)
		return;
	int mid = (start + end) / 2;
	Node node(arr[mid]);
	Node* n = &node;
	tree->TreeInsert(tree, n);
	CreateBST(tree, arr, start, mid - 1);
	CreateBST(tree, arr, mid + 1, end);
	return;
}
int main()
{
	Tree tree;
	Tree* t = &tree;
	std::vector<int> arr;
	for(int i = 0; i < 10; i++) {
		arr.push_back(i);
	}

	CreateBST(t, arr, 0, 9);
	
	return 0;
}
*/