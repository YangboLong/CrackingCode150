#include <iostream>
#include <stack>

class MyQueue {
public:
	void Enqueue(int);
	int Dequeue();
private:
	std::stack<int> EnqStack;
	std::stack<int> DeqStack;
};
void MyQueue::Enqueue(int item) {
	while(!DeqStack.empty()) { // move items in DeqStack to an empty EnqStack
		EnqStack.push(DeqStack.top());
		DeqStack.pop();
	}
	EnqStack.push(item); // add the last item
}
int MyQueue::Dequeue() {
	if(EnqStack.empty() && DeqStack.empty()) {
		std::cerr << "underflow";
		exit(EXIT_FAILURE);
	}
	while(!EnqStack.empty()) { // move items in EnqStack to DeqStack in a reverse order
		DeqStack.push(EnqStack.top());
		EnqStack.pop();
	}
	int ret = DeqStack.top();
	DeqStack.pop();
	
	return ret;
}
// 3.5 Implement a MyQueue class which implements a queue using two stacks.
int main()
{
	MyQueue my_queue;
	for(int i = 0; i < 10; i++) {
		my_queue.Enqueue(i);
	}
	for(int i = 0; i < 10; i++) {
		std::cout << my_queue.Dequeue() << " ";
	}

	return 0;
}