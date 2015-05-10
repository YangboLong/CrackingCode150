#include <iostream>
typedef unsigned int uint;

// 5.1 Write a method to insert M into N such that M starts at bit j and ends at bit i.
uint InsertBits(uint M, uint N, uint i, uint j) {
	uint mask = (~((1 << (j+1)) - 1)) | ((1 << i) - 1); // 0xffffff83
	N = N & mask; // clear bits from i to j in N
	M = M << i; // left shift M by i bits
	
	return N | M;
}
// 5.2 Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double, print the binary representation.
void PrintBin(double real) {
	if(real >= 1 || real <= 0) {
		std::cerr << "ERROR" << std::endl;
		exit(EXIT_FAILURE);
	}
	uint len = 0;
	std::cout << "0.";
	while(real > 0) {
		if(len > 32) { // cannot be represented accurately in binary with at most 32 character
			std::cerr << "ERROR" << std::endl;
			exit(EXIT_FAILURE);
		}
		real *= 2;
		if(real >= 1) {
			std::cout << 1;
			real -= 1;
		}
		else {
			std::cout << 0;
		}
		len++;
	}
	std::cout << std::endl;
}
// 5.3 Given a positive integer, print the next smallest and the next largest number
// that have the same number of 1 bits in their binary representation.
int Count1s(int num) {
	int len = 0;
	while(num > 0) {
		if(num & 1)
			len++;
		num >>= 1;
	}

	return len;
}
void PrintNexts(uint num) {
	int len = 0, len1 = 0, len2 = 0; // current number 1s, smaller number 1s, and larger number 1s
	len = Count1s(num);
	int tmp = num;
	do {
		len1 = Count1s(--tmp);
	} while(len1 != len);
	do {
		len2 = Count1s(++num);
	} while(len2 != len);

	std::cout << tmp << ", " << num << std::endl;
}
// 5.5 Write a function to determine the number of bits required to convert integer A to integer B.
int ConvertIntBits(int a, int b) {
	int len1 = Count1s(a);
	int len2 = Count1s(b);

	return abs(len1 - len2);
}
// 5.6 Write a program to swap odd and even bits in an integer with as few instructions as possible.
int SwapBits(int num) {
	int ret = 0;
	for(int i = 0; i < 32; i += 2) {
		int tmp1 = 0, tmp2 = 0;
		if(num & (1 << i)) { // get an even bit, 0, 2, ..., in a loop
			tmp1 = 1;
		}
		if(num & (1 << (i+1))) { // get odd bit, 1, 3, ..., in a loop
			tmp2 = 1;
		}
		ret  = (ret | (tmp2 << i)) | (tmp1 << (i+1));
	}

	return ret;
}
int main()
{
	uint N = 0x400, M = 0x13, j = 6, i = 2;
	uint res = InsertBits(M, N, i, j);

	PrintBin(0.5625); // 0.1001 (binary)
	
	PrintNexts(5); // 3, 4

	int num_bits = ConvertIntBits(31, 14);

	int swap_bits = SwapBits(6);

	return 0;
}