#include <iostream>
#include <stack>

// 3.4 Write a program to move the disks from the first tower to the last using stacks.
void MoveDisks(int n, std::stack<int>* origin, std::stack<int>* destination, std::stack<int>* buffer) {
	// base case
	if(n == 0) 
		return;
	else if(n == 1) {
		destination->push(origin->top());
		origin->pop();
		return;
	}
	// move n-1 disks from origin to buffer with destination as buffer
	MoveDisks(n - 1, origin, buffer, destination);
	// move the nth disk from origin to destination
	MoveDisks(1, origin, destination, buffer);
	// move n-1 disks from buffer to destination with origin as buffer
	MoveDisks(n - 1, buffer, destination, origin);
}

int main()
{
	std::stack<int> first, second, third; // three towers
    for(int i = 10; i > 0; i--) // start with 10 disks on the first tower
        first.push(i);
	MoveDisks(10, &first, &third, &second); // move from first to third

	return 0;
}