#include <iostream>

void fizzbuzz(int x)
{
    for (int i{ 1 }; i <= x; ++i)
    {
        if (i % 15 == 0)
            std::cout << "fizzbuzz\n";
        else if (i % 5 == 0)
            std::cout << "buzz\n";
        else if (i % 3 == 0)
            std::cout << "fizz\n";
        else
            std::cout << i << '\n';
    }

    return;
}

int main()
{
    std::cout << "Enter a number for the fizzbuzz game: ";
    int x{};
    std::cin >> x;

    fizzbuzz(x);

    return 0;
}
