#include <iostream>
#include <vector>
#define GIVEN_VALUE	5 // for path sum check

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
	void SumPath(Node*);
private:
	Node* root;
};

// 4.9 Design an algorithm to print all paths which sum to a given value.
void PrintPath(Node* node, int depth) {
	std::vector<int> keys;
	for(int i = depth; i >= 0; i--) { // save keys
		keys.push_back(node->GetKey());
		node = node->GetParent();
	}
	for(unsigned int i = keys.size(); i > 0; i--) { // print keys in a reversed order
		std::cout << keys[i - 1] << " ";
	}

	std::cout << std::endl;
}
void Tree::SumPath(Node* node) {
	if(node == NULL) // node is null
		return;
	if(node->GetKey() == GIVEN_VALUE) // node key is equal to given value
		PrintPath(node, 0);

	int sum = node->GetKey(), depth = 0;
	Node* n = node; // trailing pointer
	while(n != NULL) { // sum all the way back to root
		if(n->GetParent() != NULL) { // node is not root
			depth++; // for printing the path
			sum += n->GetParent()->GetKey();
			if(sum == GIVEN_VALUE)
				PrintPath(node, depth);
		}
		n = n->GetParent();
	}

	SumPath(node->GetLeft());
	SumPath(node->GetRight());
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

	tree.SumPath(n1);

	return 0;
}

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