## The `constexpr` keyword

A **constexpr** variable is always a compile-time constant and a constexpr variable must be initialized with a constant expression, otherwise a compilation error results:

```cpp
#include <iostream>

int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not a constant expression

    return 0;
}
```

`constexpr` has the additional benefit of working with integral AND non-integral types.

## Differentiating new vocabulary terms: `const` and `constexpr`

- `const` means the value of an object cannot be changed after initialization.
- `constexpr` means the object must have a known value at compile-time.
- `constexpr` variables are implicitly `const`. `const` variables are not implicitly `constexpr`.

## Const and constexpr function parameters

- `const` function parameters are treated as runtime constants (even if the supplied arguments are compile-time constants)
- Function parameters CANNOT be declared as `constexpr`, since their initialization value isn't determined until runtime.


