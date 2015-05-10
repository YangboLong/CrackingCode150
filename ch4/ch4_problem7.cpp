#include <iostream>

class Node {
public:
	Node() { key = -1; left = NULL; right = NULL; parent = NULL; }
	int GetKey() { return key; }
	Node* GetLeft() { return left; }
	Node* GetRight() { return right; }
	Node* GetParent() { return parent; }
	void SetKey(int value) { key = value;}
	void SetLeft(Node* node) { left = node; }
	void SetRight(Node* node) { right = node; }
	void SetParent(Node* node) { parent = node; }
private:
	int key;
	Node* left;
	Node* right;
	Node* parent;
};
class Tree {
public:
	Tree() { root = NULL; }
	Node* GetRoot() { return root; }
	void TreeInsert(Tree* &, Node*);
	Node* CommonAncestor(Node*, Node*);
private:
	Node* root;
};
void Tree::TreeInsert(Tree* &tree, Node* node) {
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

// 4.7 Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree.
Node* Tree::CommonAncestor(Node* n1, Node* n2) {
	if(n1 == NULL || n2 == NULL) // one node is null
		return NULL;
	if(n1->GetParent() == NULL) // n1 is root
		return n1;
	if(n2->GetParent() == NULL) // n2 is root
		return n2;
	Node* x = n1;
	int d1 = 0; // depth of node n1
	while(x->GetParent() != NULL) {
		x = x->GetParent();
		d1++;
	}
	Node* y = n2;
	int d2 = 0; // depth of node n2
	while(y->GetParent() != NULL) {
		y = y->GetParent();
		d2++;
	}
	if(d1 - d2 > 0) { // n1 has larger depth
		for(int i = d1 - d2; i > 0; i--) {
			n1 = n1->GetParent();
		}
		if(n1 == n2)
			return n2;
	}
	else if(d1 - d2 < 0) { // n2 has larger depth
		for(int i = d2 - d1; i > 0; i--) {
			n2 = n2->GetParent();
		}
		if(n1 == n2)
			return n1;
	}

	while(n1->GetParent() != NULL && n1->GetParent() != n2->GetParent()) { // n1 and n2 has same depth
		n1 = n1->GetParent();
		n2 = n2->GetParent();
	}
	if(n1->GetParent() == NULL) // back to the root
		return n1;
	else // came to the same ancestor
		return n1->GetParent();
}

int main()
{
	Tree tree;
	Tree* t = &tree;
	Node node1;
	node1.SetKey(5);
	Node* n1 = &node1;
	tree.TreeInsert(t, n1);
	Node node2;
	node2.SetKey(2);
	Node* n2 = &node2;
	tree.TreeInsert(t, n2);
	Node node3;
	node3.SetKey(7);
	Node* n3 = &node3;
	tree.TreeInsert(t, n3);
	Node node4;
	node4.SetKey(1);
	Node* n4 = &node4;
	tree.TreeInsert(t, n4);
	Node node5;
	node5.SetKey(3);
	Node* n5 = &node5;
	tree.TreeInsert(t, n5);

	Node* n = tree.CommonAncestor(tree.GetRoot()->GetLeft()->GetLeft(), tree.GetRoot()->GetRight());

	return 0;
}