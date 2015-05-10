#include <iostream>
#include <algorithm>

// 4.1 Implement a function to check if a binary tree is balanced.
class Node {
public:
	Node() : key(-1), left(NULL), right(NULL), parent(NULL) {}
	int GetKey() { return key; }
	Node* GetLeft() { return left; }
	Node* GetRight() { return right; }
	void SetLeft(Node* node) { left = node; }
	void SetRight(Node* node) { right = node; }
private:
	int key;
	Node* parent;
	Node* left;
	Node* right;
};
class Tree {
public:
	Tree() : root(NULL) {}
	void AddNodeLeft(Node*);
	void AddNodeRight(Node*);
private:
	Node* root;
};
void Tree::AddNodeLeft(Node* node) {
	if(root == NULL) {
		root = node;
		return;
	}
	else {
		Node* tmp = root;
		while(tmp->GetLeft()) { // go left until no left child
			tmp = tmp->GetLeft();
		}
		tmp->SetLeft(node);
	}
}
void Tree::AddNodeRight(Node* node) {
	if(root == NULL) {
		root = node;
		return;
	}
	else {
		Node* tmp = root;
		while(tmp->GetRight()) { // go right until no right child
			tmp = tmp->GetRight();
		}
		tmp->SetRight(node);
	}
}

int GetHeight(Node* root) {
	if(root == NULL)
		return 0;
	return std::max(GetHeight(root->GetLeft()), GetHeight(root->GetRight())) + 1;
}
bool IsBalanced(Node* root) {
	if(root == NULL)
		return true;
	int left_height, right_height;
	left_height = GetHeight(root->GetLeft());
	right_height = GetHeight(root->GetRight());

	if(left_height - right_height < -1 || left_height - right_height > 1)
		return false;
	else {
		if(IsBalanced(root->GetLeft()) && IsBalanced(root->GetRight())) 
			return true;
		else
			return false;
	}
}

int main()
{
	Tree tree;
	//tree.AddNodeLeft();

	return 0;
}