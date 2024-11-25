#include <iostream>

int sumTo(int value)
{
    int result{ 0 };
    for (int i{1}; i <= value; ++i)
    {
        result += i;

        if (i == value)
            std::cout << i << " = ";
        else
        std::cout << i << " + ";
    }

    return result;
}

int main()
{
    std::cout << "Enter a value to sum all the numbers from 1 to value: ";
    int x{};
    std::cin >> x;

    std::cout << sumTo(x) << '\n';

    return 0;
}
