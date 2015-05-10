#include <iostream>
#include <vector>

// 3.3  SetOfStacks should be composed of several stacks and should create a new stack once the previous one exceeds capacity.
class Stack {
public:
	Stack() : top(-1), items(new int []) {} // for the "new" statement in the constructor of SetOfStacks
	~Stack() {
		delete [] items;
	}
	bool StackEmpty();
	void push(int);
	int pop();
	int GetTop() { return top; }
private:
	int top;
	int* items;
};
bool Stack::StackEmpty(){
	if(top == -1)
		return true;
	else
		return false;
}
void Stack::push(int a){
	top++;
	items[top] = a;
}
int Stack::pop(){
	if(StackEmpty()){
		std::cerr << "underflow" << std::endl;
		exit(EXIT_FAILURE);
	}
	else{
		top--;
		return items[top + 1];
	}
}

class SetOfStacks {
public:
	SetOfStacks() : capacity(5), top(0) {
		stacks = new Stack [10]; // change the number of stacks here
	}
	~SetOfStacks() {
		// no need to delete here
	}
	int GetCapacity() { return capacity; }
	void push(int);
	int pop();
	int PopAt(int);
private:
	int capacity; // capacity of each stack
	Stack* stacks;
	int top;
};
void SetOfStacks::push(int elem) {
	if(stacks[top].GetTop() >= capacity - 1) {
		top++;
	}
	stacks[top].push(elem);
}
int SetOfStacks::pop() {
	if(stacks[top].GetTop() == -1) { // cannot call pop if there is no element stored
		std::cerr << "no elements to pop";
		exit(EXIT_FAILURE);
	}
	if(stacks[top].GetTop() == 0) { // has a single element in a stack
		top--; // stack pointer go to the previous stack
		return stacks[top + 1].pop();
	}
	else
		return stacks[top].pop(); // return the top element in stack
}
int SetOfStacks::PopAt(int index) { // perform a pop operation on a specific stack
	if(stacks[index].StackEmpty()) {
		std::cerr << "stack has no elements to pop";
		exit(EXIT_FAILURE);
	}

	return stacks[index].pop();
}

int main()
{
	SetOfStacks stack_set;
	stack_set.push(4);
	stack_set.push(10);
	stack_set.push(3);
	stack_set.push(5);
	stack_set.push(4);
	stack_set.push(2);
	int popped;
	/*
	popped = stack_set.pop();
	popped = stack_set.pop();
	popped = stack_set.pop();
	popped = stack_set.pop();
	popped = stack_set.pop();
	popped = stack_set.pop();
	*/
	//popped = stack_set.pop();
	popped = stack_set.PopAt(1);
	
	return 0;
}

