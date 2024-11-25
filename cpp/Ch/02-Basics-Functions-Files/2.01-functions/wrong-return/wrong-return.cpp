// This program doesn't work
#include <iostream>

void getValueFromUser()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
}

int main()
{
    getValueFromUser();

    int num{};

    std::cout << num << " doubled is: " << num * 2 << '\n';

    return 0;
}
