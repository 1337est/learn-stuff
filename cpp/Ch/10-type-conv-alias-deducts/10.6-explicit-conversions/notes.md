## Type casting

C++ comes with a number of different **type casting operators** (commonly referred to as **casts**) that can be used by the programmer to request that the compiler perform a type conversion. Type casting is a form of explicit type conversion.

C++ supports 5 types of casts:

- C-style casts
- static casts
- const casts
- dynamic casts
- reinterpret casts

## C-style casts

These casts are done via the () operator, with the type name being surrounded by the parenthesis:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };


    double d { (double)x / y }; // convert x to a double so we get floating point division
    std::cout << d << '\n'; // prints 2.5

    return 0;
}
```

- Avoid using C-style casts

## static_cast

```cpp
#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << c << ' ' << static_cast<int>(c) << '\n'; // prints a 97

    return 0;
}
```

- Favor static_cast when you need to convert a value from one type to another.


