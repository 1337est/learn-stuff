#include <iostream>

int main()
{
    std::cout << "Enter two numbers separated by a space: ";

    int x{}, y{}; // define var x&y to hold user input
    std::cin >> x >> y; // get two numbers and store in variables x&y

    std:: cout << "You entered " << x << " and " << y << '\n';

    return 0;
}
