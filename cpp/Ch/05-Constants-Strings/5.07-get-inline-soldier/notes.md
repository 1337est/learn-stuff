There's generally 2 options when it comes to performing discrete tasks such as, reading input from the user, outputting something to a file, or calculating a particular value, etc...

1. Write the code as part of an existing function, known as "in-place" or "inline" code.
2. Create a function (and possibly sub-functions) to handle the task.

Writing functions provides many benefits that you'll hear of everywhere on the internet. However, for functions that are small, the overhead costs can be larger than the time needed to actually execute the function's code. In these cases, using a function can result in a significant performance penalty over just writing the code "in-place"/"inline".

## Inline expansion

The C++ compiler can perform **inline expansion**, which is a process where a function call is replaced by the code from the called function's definition.

This code:
```cpp
#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0;
}
```

Would be replaced by this with inline expansion:
```cpp
#include <iostream>

int main()
{
    std::cout << ((5 < 6) ? 5 : 6) << '\n';
    std::cout << ((3 < 2) ? 3 : 2) << '\n';
    return 0;
}
```

Inline expansion may occur, or it could not be expandable. Wishy washy.

## The inline keyword, historically

A function that is declared using the `inline` keyword is called an "inline function".

Don't use the `inline` keyword to request inline expansion for your functions.

Basically, the `inline` keyword sucks for inline expansion of functions. The compiler can just ignore it if it wants, using it is a form of premature optimization, and inline expansion is very context dependant for optimization. It's used on the function definition, but inline expansion is determined per function call. Depending on the call, it may be detrimental to expand, and there's no syntax to influence this.

**Note:**
- Modernly, the `inline` keyword is used to truncate the one definition rule (ODR). It allows multiple definitions without error. Every definition of an inline function must be identical, otherwise undefined behavior will result.
- Inline functions are typically defined in header files, where they can be #included into the top of any code file that needs to see the full definition of the identifier.
```cpp
// pi.h
#ifndef PI_H
#define PI_H

inline double pi() { return 3.14159; }

#endif
```
```cpp
// main.cpp
#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```
```cpp
// math.cpp
#include "pi.h" // will include a copy of pi() here

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

- You should not make your functions or variables inline with the keyword, unless you define them in a header file.


