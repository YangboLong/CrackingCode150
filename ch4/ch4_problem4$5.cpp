#include<iostream>
#include<vector>
#include<list>

class Node {
public:
	int data;
	Node *left, *right;
};
void createBst(Node* &, int [], int, int);
void deleteBst(Node* &); // to free heap
// 4.4 Given a binary tree, design an algorithm which creates a linked list of all the nodes at each depth.
void CreateLevelLinkedList(std::vector<std::list<Node*>> &res, Node* &root) {
	if(root == NULL) // no node exists, return nothing
		return;
	std::list<Node*> current;
	current.push_back(root);

	while(current.size() > 0) {
		res.push_back(current); // add current level
		std::list<Node*> parents = current;
		std::list<Node*>::iterator iter = current.begin();
		while(iter != current.end()) { // clear current list to incorporate the next level nodes
			iter = current.erase(iter);
		}
		for(std::list<Node*>::iterator it = parents.begin(); it != parents.end(); it++) { // incorporate all child nodes in the next level
			if((*it)->left != NULL) {
				current.push_back((*it)->left);
			}
			if((*it)->right != NULL) {
				current.push_back((*it)->right);
			}
		}
	}
}
// 4.5 Implement a function to check if a binary tree is a binary search tree.
void IsBst(Node* &root, bool &flag) {
	if(root == NULL)
		return;
	if(root->left == NULL && root->right == NULL) 
		return;
	if(root->left != NULL) {
		if(root->left->data < root->data)
			IsBst(root->left, flag);
		else
			flag = false;
	}
	if(root->right != NULL) {
		if(root->right->data >= root->data)
			IsBst(root->right, flag);
		else
			flag = false;
	}
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Node* root;
    root = NULL;
    createBst(root, arr, 0, 8);
    std::cout<<root->left->data<<" "<<root->data<<" "<<root->right->data<<'\n';

	std::vector<std::list<Node*>> result;
	CreateLevelLinkedList(result, root);

	bool flag = true;
	IsBst(root, flag);
	if(flag)
		std::cout << "tree is binary search tree" << std::endl;
	else
		std::cout << "tree is not binary search tree" << std::endl;


	deleteBst(root);

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