#include <iostream>

int main() {
	char ar_char[] = {'a', 'b', 'c'};
	short ar_short[] = {1, 2, 3};
	int ar_int[] = {1, 2, 3};
	long ar_long[] = {1, 2, 3};
	long long ar_long_long[] = {1, 2, 3};
	std::cout << "ar_char      " << sizeof(ar_char) << std::endl;
	std::cout << "ar_short     " << sizeof(ar_short) << std::endl;
	std::cout << "ar_int       " << sizeof(ar_int) << std::endl;
	std::cout << "ar_long      " << sizeof(ar_long) << std::endl;
	std::cout << "ar_long_long " << sizeof(ar_long_long) << std::endl;
	return 0;
}
