#include <iostream>
#include <algorithm> // for std::swap

void sort2(int& lesser, int& greater)
{
    // if values are already sorted do nothing
    if (lesser <= greater)
        return;
    // sort values by swap
    std::swap(lesser, greater);
}

int main()
{
    int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    return 0;
}
