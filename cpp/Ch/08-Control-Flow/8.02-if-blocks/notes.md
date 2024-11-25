- Prefer to put if-else statements in blocks (even if only a single statement within) to avoid tricking yourself in case you add more to it later.

As an example this code here doesn't compile and says the identifier `x` isn't defined:
```cpp
#include <iostream>

int main()
{
    if (true)
        int x{ 5 };
    else
        int x{ 6 };

    std::cout << x << '\n';

    return 0;
}
```

That's because the above program is the equivalent of:
```cpp
#include <iostream>

int main()
{
    if (true)
    {
        int x{ 5 };
    } // x destroyed here
    else
    {
        int x{ 6 };
    } // x destroyed here

    std::cout << x << '\n'; // x isn't in scope here

    return 0;
}
```

It's a slippery slope. Adding brackets removes a lot of ambiguity.

## Null statements
- A **null statement** is an expression statement that consists of just a semicolon:
```cpp
if (x > 10)
    ; // this is a null statement
```

Null statements do nothing.


