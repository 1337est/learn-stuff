#include <iostream>

int readNumber()
{
    std::cout << "Enter an integer to add: ";

    int input{};
    std::cin >> input;

    return input;
}

void writeAnswer(int input)
{
    std::cout << "These numbers add up to: " << input << '\n';
}

int main()
{
    int a { readNumber() };
    int b { readNumber() };

    writeAnswer(a + b);

    return 0;
}
