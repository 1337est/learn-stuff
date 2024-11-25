#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int num{ };
    std::cin >> num;

    std::cout << "Double " << num << " is: " << num * 2 << std::endl;

    std::cout << "Triple " << num << " is: " << num * 3 << std::endl;

    return 0;
}
