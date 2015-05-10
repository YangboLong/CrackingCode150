#include <iostream>
#include <vector>

class Stack {
public:
	Stack(int *s, int size) {
		len = size;
		top = -1;
		items = s;
		min_ele = s;
	}
	bool IsEmpty();
	void push(int);
	int pop();
	int min();
private:
	int len;
	int top;
	int* items; // store the elements
	int* min_ele; // a pointer of the min element
	std::vector<int> save_min; // save the min elements encountered in decreasing-value order
};

int main()
{
	// 3.1 Describe how you could use a single array to implement three stacks.
	int arr[10];
	int len = 10 / 3;
	Stack s1(arr, len);
	Stack s2(&arr[len], len);
	Stack s3(&arr[len*2], len);
	s1.push(1);	s1.push(2);	s1.push(3); s1.pop();
	s2.push(4);	s2.push(5);	s2.push(6);
	s3.push(7);	s3.push(8);

	// 3.2 How would you design a stack which, in addition to push and pop, also has a function min which returns the minimum element?
	Stack s4(arr, 10);
	s4.push(4); s4.push(10); s4.push(3); s4.push(5); s4.push(4); //s4.push(2);
	int min_elem = s4.min();
	int top_elem = s4.pop();
	min_elem = s4.min();

	return 0;
}

bool Stack::IsEmpty() {
	if(top == -1)
		return true;
	else
		return false;
}

void Stack::push(int item) {
	top++;
	items[top] = item;
	
	if(top == 0) // the bottom element in stack is always saved
		save_min.push_back(item);
	if(item < *min_ele) {
		min_ele = &items[top];
		save_min.push_back(item);
	}
}

int Stack::pop() {
	if(IsEmpty()) {
		std::cerr << "Stack underflow." << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		if(min_ele == &items[top]) { // top element is min
			save_min.pop_back(); // the old second min is now the min
		}
		top--;
		return items[top + 1];
	}
}

int Stack::min() {
	return *(save_min.end() - 1); // min is always the last element
}