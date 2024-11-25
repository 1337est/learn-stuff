#include <iostream>

void fizzbuzzpop(int x)
{
    for (int i{ 1 }; i <= x; ++i)
    {
        bool printed{ false };

        if (i % 3 == 0)
        {
            std::cout << "fizz";
            printed = true;
        }
        if (i % 5 == 0)
        {
            std::cout << "buzz";
            printed = true;
        }
        if (i % 7 == 0)
        {
            std::cout << "pop";
            printed = true;
        }
        if (!printed)
            std::cout << i;

        std::cout << '\n';
    }

    return;
}

int main()
{
    std::cout << "Enter a number for the fizzbuzz game: ";
    int x{};
    std::cin >> x;

    fizzbuzzpop(x);

    return 0;
}
