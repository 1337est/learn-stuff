## Incrementing and decrementing variables

* ++x is the prefix increment (pre-increment) and increments x, THEN returns x
* --x is the prefix decrement (pre-decrement) and decrements x, THEN returns x
* x++ is the postfix increment (post-increment) and copies x, increments x, then returns the COPY
* x-- is the postfix decrement (post-decrement) and copies x, decrements x, then return the COPY

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { 5 };
    std::cout << x << ' ' << y << '\n'; // outputs 5 5
    std::cout << ++x << ' ' << --y << '\n'; // prefix outputs 6 4
    std::cout << x << ' ' << y << '\n'; // outputs 6 4
    std::cout << x++ << ' ' << y-- << '\n'; // postfix outputs 6 4 (initial copy returned)
    std::cout << x << ' ' << y << '\n'; // operation still happened, ouputs 7 3

    return 0;
}
```


