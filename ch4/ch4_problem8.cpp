#include <iostream>

class Node {
public:
	int data;
	Node *left, *right;
};
void createBst(Node* &, int [], int, int);
void deleteBst(Node* &); // to free heap

// 4.8  Create an algorithm to decide if T2 is a subtree of Tl.
bool TreeMatch(Node* s1, Node* s2) {
	if(s1 == NULL && s2 == NULL) // both are null
		return true;
	if(s1 == NULL || s2 == NULL) // one is null, the other is not
		return false;
	if(s1->data != s2->data) // two nodes don't match
		return false;
	if(TreeMatch(s1->left, s2->left) && TreeMatch(s1->right, s2->right)) { // both are not null
		return true;
	}
	else
		return false;
}
bool IsSubtree(Node* t1, Node* t2) {
	if(t2 == NULL) // null tree is subtree of any other tree
		return true;
	if(t1 == NULL) // null tree has no subtree
		return false;
	if(t1->data == t2->data) { // find small tree root in larger tree
		if(TreeMatch(t1, t2)) // check if their subtrees match
			return true;
	}
	if(IsSubtree(t1->left, t2) || IsSubtree(t1->right, t2)) { // check subtrees of larger tree
		return true;
	}
	else
		return false;
}

int main()
{
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Node* r1;
    r1 = NULL;
    createBst(r1, arr1, 0, 8);
	int arr2[] = {2, 1, 3, 4};
    Node* r2;
    r2 = NULL;
    createBst(r2, arr2, 0, 3);
	if(IsSubtree(r1, r2))
		std::cout << "r2 is subtree of r1" << std::endl;
	else
		std::cout << "r2 is NOT subtree of r1" << std::endl;
	
	deleteBst(r1);
	deleteBst(r2);

	return 0;
}

void createBst(Node* &root, int arr[], int start, int end){
    if(start>end)
        return;
    if(root==NULL){
        Node *ptr = new Node;
        int ind = start + (end-start)/2;
        ptr->data = arr[ind];
        ptr->left = NULL;
        ptr->right = NULL;
        root = ptr;
        createBst(root->left, arr, start, ind-1);
        createBst(root->right, arr, ind+1, end);
    }
}
void deleteBst(Node* &root) {
	if(root == NULL)
		return;
	if(root->left == NULL && root->right == NULL) {
		delete root;
		return;
	}
	deleteBst(root->left);
	deleteBst(root->right);
	delete root;
	return;
}