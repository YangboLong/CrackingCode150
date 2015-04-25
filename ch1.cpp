#include <iostream>
#include <string>
#include <vector>

void StringChecker(std::string &); // 1.1
void Reverse(char*); // 1.2
bool IsPermutation(std::string, std::string); // 1.3
std::string ReplaceSpace(std::string &, int); // 1.4
std::string StringCompression(std::string &); // 1.5
void RotateMatrix(std::vector<std::vector<int>> &); // 1.6
void ClearRowCol(std::vector<std::vector<int>> &); // 1.7
// 1.8 Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring
bool IsRotation(std::string, std::string);

int main() 
{
	// 1.1 Implement an algorithm to determine if a string has all unique characters. 
	std::string st1 ("abccdefg");
	StringChecker(st1);

	// 1.2 Implement a function void reverse(char* str) in C or C++ which reverses a null-terminated string.
	std::string st2 ("abcd");
	st2.push_back(NULL);
	Reverse(&st2[0]);

	// 1.3 Given two strings, write a method to decide if one is a permutation of the other.
	std::string st3 ("abcde");
	std::string st4 ("aecdb");
	if(IsPermutation(st3, st4))
		std::cout << "One string is a permutation of the other." << std::endl;
	else
		std::cout << "One string is NOT a permutation of the other." << std::endl;

	// 1.4 Write a method to replace all spaces in a string with '%20'.
	std::string st5 ("Mr John Smith    ");
	std::string st6 = ReplaceSpace(st5, 11); // 11 is the "true" length of the string
	std::cout << "Spaces replaced string: " << st6 << std::endl;

	// 1.5 Implement a method to perform basic string compression using the counts of repeated characters.
	std::string st7 ("aabcccccaaa");
	std::string st8 = StringCompression(st7);
	std::cout << "Compressed string: " << st8 << std::endl;

	// 1.6 Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, 
	// write a method to rotate the image by 90 degrees. Can you do this in place?
	std::vector<std::vector<int>> image(4, std::vector<int>(4));
	image[0][0] = 1,  image[0][1] = 2,  image[0][2] = 3,  image[0][3] = 4;
	image[1][0] = 5,  image[1][1] = 6,  image[1][2] = 7,  image[1][3] = 8;
	image[2][0] = 9,  image[2][1] = 10, image[2][2] = 11, image[2][3] = 12;
	image[3][0] = 13, image[3][1] = 14, image[3][2] = 15, image[3][3] = 16;
	RotateMatrix(image);
	std::cout << "Rotated matrix: " << std::endl;
	for(unsigned int i = 0; i < image.size(); i++) {
		for(unsigned int j = 0; j < image[i].size(); j++) {
			std::cout << image[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// 1.7 Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are set to 0.
	std::vector<std::vector<int>> matrix(4, std::vector<int>(4));
	matrix[0][0] = 1,  matrix[0][1] = 2,  matrix[0][2] = 3,  matrix[0][3] = 4;
	matrix[1][0] = 5,  matrix[1][1] = 0,  matrix[1][2] = 7,  matrix[1][3] = 8;
	matrix[2][0] = 9,  matrix[2][1] = 10, matrix[2][2] = 0,  matrix[2][3] = 12;
	matrix[3][0] = 13, matrix[3][1] = 0,  matrix[3][2] = 15, matrix[3][3] = 16;
	ClearRowCol(matrix);
	std::cout << "Cleared rows and columns: " << std::endl;
	for(unsigned int i = 0; i < matrix.size(); i++) {
		for(unsigned int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}

// 1.1 Implement an algorithm to determine if a string has all unique characters. 
void StringChecker(std::string &st) {
	char *p, *q;
	for(unsigned int i = 0; i < st.size(); i++) {
		p = &(st[i]);
		for(unsigned int j = i + 1; j < st.size(); j++) {
			q = &(st[j]);
			if(*p == *q) {
				std::cout << "The string contains same elements." << std::endl;
				return;
			}
		}
	}
	std::cout << "The string has all unique characters." << std::endl;
}

// 1.2 Implement a function void reverse(char* str) in C or C++ which reverses a null-terminated string.
void Reverse(char* str) {
	std::string rev;
	char* p = str;
	while(*p != NULL)
		p++;
	p--; // go to the last valid element
	while(p != str - 1) { // reverse the elements
		rev.push_back(*p);
		p--;
	}
	rev.push_back(NULL); // add the null to the end

	std::cout << "Reversed string: " << rev << std::endl; // print the reversed string
}

// 1.3 Given two strings, write a method to decide if one is a permutation of the other.
// Copied quick sort code from before.
void Swap(char &a, char &b) {
	char tmp = a;
	a = b;
	b = tmp;
}
// quicksort clrs p171
int Partition(std::string &A, int p, int q){
	int x = A[p];
	int i = p;
	for(int j = p + 1; j <= q; j++){
		if(A[j] <= x){
			i++;
			Swap(A[i], A[j]);
		}
	}
	Swap(A[p], A[i]);
		
	return i;
}
void Quicksort(std::string &A, int p, int r){
	if(p < r){
		int q = Partition(A, p, r);
		Quicksort(A, p, q - 1);
		Quicksort(A, q + 1, r);
	}
}
bool IsPermutation(std::string a, std::string b) {
	if(a.size() != b.size())
		return false;

	if(a.empty())
		return true;

	Quicksort(a, 0, a.size() - 1);
	Quicksort(b, 0, b.size() - 1);

	for(unsigned int i = 0; i < a.size(); i++) {
		if(a[i] != b[i])
			return false;
	}

	return true;
}

// 1.4 Write a method to replace all spaces in a string with '%20'.
std::string ReplaceSpace(std::string & st, int true_length) {
	std::string ret;
	int length = st.size(), first = 0, space_count = 0;
	while(st[first] == ' ') { // deal with spaces in the beginning
		first++;
	}
	for(int i = first; i < length; i++) { // begin with the first non-space element
		if(st[i] != ' ') {
			ret.push_back(st[i]);
		}
		else { // find spaces
			while(st[++i] == ' '); // pass the spaces
			int tmp = ret.size() - space_count*3;
			if(tmp < true_length) // don't replace the last spaces in the end
				ret.append("%20");
			space_count++; // continuous space element sections
			i--; // to cancel out the i++ in the for statement
		}
	}

	return ret;
}

// 1.5 Implement a method to perform basic string compression using the counts of repeated characters.
std::string StringCompression(std::string & st) {
	std::string ret;
	char *p = &st[0], *q = &st[1];
	for(unsigned int i = 0; i < st.size(); i++) {
		while(*p == *q) {
			q++;
			i++;
		}
		ret.push_back(*p);
		ret.push_back(q - p + 48); // counts of every unique char and convert to char
		p = q; // move to the next unique char
		q++;
	}

	return ret;
}

// 1.6 Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, 
// write a method to rotate the image by 90 degrees. Can you do this in place?
void RotateMatrix(std::vector<std::vector<int>> & image) {
	int length = image.size();
	for(int i = 0; i < length / 2; i++) { // from outer layer to inner layer
		std::vector<int> tmp;
		for(int j = i; j < length - i; j++) {
			tmp.push_back(image[i][j]); // top row of each layer
		}
		int top_len = tmp.size(); // the length of top row in each layer
		// corners: up-left, bottom-left, bottom-right
		int UL = image[i][i], BL = image[length - 1 - i][i], BR = image[length - 1 - i][length - 1 - i];
		for(int k = 0; k < top_len; k++) {
			image[i][k + i] = image[length - 1 - k - i][i]; // move left column to top row
			image[length - 1 - k - i][i] = image[length - 1 - i][length - 1 - k - i]; // move bottom row to left column
			image[length - 1 - i][length - 1 - k - i] = image[k + i][length - 1 - i]; // move right column to bottom row
			image[k + i][length - 1 - i] = tmp[k]; // move top row to right column
		}
		// take care of the corner ones
		image[i][length - 1 - i] = UL;
		image[i][i] = BL;
		image[length - 1 - i][i] = BR;

		tmp.clear();
	}
}

// 1.7 Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are set to 0.
// This implementation still has duplicate row/col indexes stored, would need to scan through the vectors to avoid duplicates?
void ClearRowCol(std::vector<std::vector<int>> & matrix) {
	std::vector<int> row_index, col_index; // indexes that have 0 elements in the matrix
	for(unsigned int i = 0; i < matrix.size(); i++) {
		for(unsigned int j = 0; j < matrix[i].size(); j++) {
			if(matrix[i][j] == 0) {
				if(row_index.size() == 0) // save the first row index
					row_index.push_back(i);
				else {
					if(i != *(row_index.end() - 1)) { // don't store same row index
						row_index.push_back(i);
					}
				}
				if(col_index.size() == 0) // save the first column index
					col_index.push_back(j);
				else {
					if(j != *(col_index.end() - 1)) { // don't store same column index
						col_index.push_back(j);
					}
				}
			}
		}
	}
	// put 0's in the rows
	for(int i = 0; i < row_index.size(); i++) {
		for(int j = 0; j < matrix[0].size(); j++) {
			matrix[row_index[i]][j] = 0;
		}
	}
	// put 0's in the columns
	for(int i = 0; i < col_index.size(); i++) {
		for(int j = 0; j < matrix.size(); j++) {
			matrix[j][col_index[i]] = 0;
		}
	}
}

// 1.8 Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring
// Didn't find a way to solve this problem by myself and checked the reference solution.
bool IsRotation(std::string s1, std::string s2) {
	if(s1.size() != s2.size()) 
		return false;
	else {
		s1.append(s2);
		return isSubstring(s1, s2);
	}
}