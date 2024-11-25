#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z)
{
    std::cout << x + (y * z) << '\n';
}

int main()
{
    // GCC compiler evaluates arguments in right to left order...
    printCalculation(getValue(), getValue(), getValue()); // this line is ambiguous

    int a{ getValue() }; // will execute first
    int b{ getValue() }; // will execute second
    int c{ getValue() }; // will execute third

    printCalculation(a, b, c); // no longer ambiguous

    return 0;
}


