## Using `std::vector<bool>`

For the most part, `std::vector<bool>` works just like a normal vector:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<bool> v { true, false, false, true, true };

    for (int i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Change the Boolean value with index 4 to false
    v[4] = false;

    for (int i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```

On a 64-bit machine, this prints:
```
1 0 0 1 1
1 0 0 1 0
```

## `std::vector<bool>` tradeoffs

First, vector-bool has a high amount of overhead and `sizeof(std::vector<bool>)` is 40 bytes on the author's machine.

Second, vector-bool is highly dependent upon its implementation and a highly optimized implementation can be significantly faster than alternatives, while a poorly optimized implementation will be slower.

Third and most importantly, `std::vector<bool>` is not a vector (therefore not required to be contiguous in memory), nor does it hold `bool` values (it actually holds a collection of bits), nor does it meet C++'s definition of a container.

Avoid `std::vector<bool>` as its performance gains are unlikely to be worth the incompatibility headaches due to it not being a proper container. The recommendation instead is:

1. Use (constexpr) `std::bitset` when the number of bits you need is known at compile-time, you don't have more than a moderate number of Boolean values to store (e.g. under 64k), and the limited set of operator and member function meets your requirements.
2. Prefer `std::vector<char>` when you need a resizable container of Boolean values and space-savings isn't a necessity. This behaves like a normal container.
3. Use 3rd party implementations of a dynamic bitset when you need a dynamic bitset to do bit operations on.

The 3 points above summarized:
- Favor `constexpr std::bitset`, `std::vector<char>`, or 3rd party dynamic bitsets over `std::vector<bool>`.
