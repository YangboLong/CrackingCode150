#include <iostream>
#include <stack>

// 3.6 Write a program to sort a stack in ascending order (with biggest items on top).
void SortStack(std::stack<int> &s1, std::stack<int> &s2) {
	int min, len;
	while(!s1.empty()) { // find the min item and push to s2 during each loop
		min = s1.top();
		len = s1.size();
		// find min item in the original stack and move items to the additional stack
		while(!s1.empty()) {
			if(s1.top() < min) { //  find the min item in s1
				min = s1.top();
			}
			s2.push(s1.top()); // move s1 items to s2
			s1.pop();
		}
		// move items back to the original stack, except the min item found above
		for(int i = 0; i < len; i++) { // don't touch the saved min items at the bottom of s2
			if(s2.top() != min) { // find the min item and exclude it from s1
				s1.push(s2.top());
			}
			s2.pop();
		}
		// save min items to the additional stack in an ascending order
		s2.push(min);
	}
}

int main()
{
	std::stack<int> s1, s2;
	s1.push(4);
	s1.push(5);
	s1.push(2);
	s1.push(1);
	s1.push(7);

	SortStack(s1, s2);

	while(!s2.empty()) {
		std::cout << s2.top() << " ";
		s2.pop();
	}

	return 0;
}