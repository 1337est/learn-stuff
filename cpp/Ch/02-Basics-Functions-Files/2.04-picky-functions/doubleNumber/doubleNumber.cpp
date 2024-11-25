#include <iostream>

int doubleNumber(int x)
{
    return x * 2;
}

int main()
{
    std::cout << "Enter an integer to double: ";

    int x{};
    std::cin >> x;
    std::cout << x << " doubled is " << doubleNumber(x) << '\n';

    return 0;
}
