#include <iostream>

int main()
{
    [[maybe_unused]] double mat[3][4];
    int value{ 0 };

    for (int row{ 0 }; row < 3; ++row)
    {
        for (int col{ 0 }; col < 4; ++col)
        {
            mat[row][col] = ++value;
            std::cout << "Row" << row << "Col" << col << ": " << value << '\n';
        }
    }

    return 0;
}
