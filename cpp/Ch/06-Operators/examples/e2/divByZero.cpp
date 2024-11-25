#include <iostream>

int main()
{
	constexpr int apples { 12 };
	std::cout << "You have " << apples << " apples. Enter how many servings of apples you want: ";

	double d {};
	std::cin >> d;

	std::cout << "Each serving is " << apples / d << " apples.\n"; // d is double, so this is floating point division

	return 0;
}


