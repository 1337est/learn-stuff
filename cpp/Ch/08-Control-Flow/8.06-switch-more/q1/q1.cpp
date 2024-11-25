#include <iostream>

int calculate(int x, int y, char c)
{
    switch (c)
    {
    case 'a':
        return x + y;
    case 's':
        return x - y;
    case 'm':
        return x * y;
    case 'd':
        return x / y;
    case 'r':
        return x % y;
    default:
        std::cout << "an error message.\n";
        return 0;
    }
}

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    std::cout << "Enter another number: ";
    int y{};
    std::cin >> y;

    std::cout << "Now enter a character representing a mathematical operation. "
        << "Valid operations include:\n"
        << "a for addition\n"
        << "s for subtraction\n"
        << "m for multiplication\n"
        << "d for division\n"
        << "r for remainder\n";
    char c{};
    std::cin >> c;

    int calculation{ calculate(x, y, c) };

    std::cout << "The result of " << x << ' ' << c << ' ' << y << " is: " << calculation << '\n';

    return 0;
}
