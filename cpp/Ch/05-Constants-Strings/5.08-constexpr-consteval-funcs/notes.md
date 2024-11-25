## Constexpr functions can be used in constant expressions

Regular function:
```cpp
#include <iostream>

double calcCircumference(double radius) // returns as a double
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { calcCircumference(3.0) }; // compile error

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```
The constexpr circumference in `constexpr double circumference { calcCircumference(3.0) };` requires that the initializer be a constant expression, but `calcCircumference()` isn't a constant expression.

Constexpr function:
```cpp
#include <iostream>

constexpr double calcCircumference(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { calcCircumference(3.0) }; // now compiles

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```

## Constexpr functions can be evaluated at compile time

Since our variable `circumference` is constexpr and thus has a constant expression initializer with the constexpr function `calcCircumference()`, the function is part of the required constant expression. Therefore, the function must be evaluated at compile-time.

When a function call is evaluated at compile-time, the compiler calculates the return value and replaces the function call with the return value.

If however, we pass in a non-constexpr as arguments, the function cannot be resolved at compile-time and is therefore resolved at runtime.

## Constexpr function calls in non-constexpr's

Consider the following:
```cpp
#include <iostream>

constexpr int getValue(int x)
{
    return x;
}

int main()
{
    int x { getValue(5) }; // may evaluate at runtime or compile-time

    return 0;
}
```

Since `x` in main is not constexpr, it doesn't require a constant expression initializer. It doesn't matter that the function is constexpr. The compiler is free to choose runtime or compile-time. If you need compile-time, make sure the variables with the function call are constexpr variables to match the constexpr functions.

## Consteval C++20

C++20 introduced the `consteval` keyword, which is used to indicate that a function MUST evaluate at compile-time, otherwise... You guessed it! Compile error! These functions are called immediate functions.

```cpp
#include <iostream>

consteval int greater(int x, int y) // function is consteval
{
    return (x > y ? x : y);
}

int main()
{
    constexpr int g { greater(5, 6) }; // will evaluate at compile-time
    std::cout << g << '\n';

    std::cout << greater(5, 6) << " is greater!\n"; // will evaluate at compile-time

    int x{ 5 }; // not constexpr
    std::cout << greater(x, 6) << " is greater!\n"; // error: consteval must evaluate at compile-time

    return 0;
}
```

It's best practice to use `consteval` when you have a function that must evaluate at compile-time.

Marking a function as `constexpr` means that it CAN be used in a constant expression. It doesn't mean it will evaluate at compile-time.

- Unless you have a reason not to, a function that can evaluate as part of a constant expression should be made `constexpr`
- A function that cannot be evaluated as part of a constant expression should not be marked as `constexpr`.


