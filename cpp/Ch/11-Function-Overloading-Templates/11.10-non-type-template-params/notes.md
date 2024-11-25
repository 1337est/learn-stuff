## Non-type template parameters
A **non-type template parameter** is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument and is of the following types:

- An integral type
- An enumeration type
- `std::nullptr_t`
- A floating point type (C++20)
- A pointer or reference to an object
- A pointer or reference to a function
- A pointer or reference to a member function
- A literal class type (C++20)

We saw our first example of a non-type template parameter when we discussed `std::bitset`:
```cpp
#include <bitset>

int main()
{
    std::bitset<8> bits{ 0b000'0101 }; // The <8> is a non-type template parameter

    return 0;
}
```

## Defining our own non-type template parameters

Here's an example of how to use an int non-type template parameter:
```cpp
#include <iostream>

template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}

int main()
{
    print<5>(); // 5 is our non-type template argument

    return 0;
}
```

```
5
```

When the compiler sees the above function call to `print()`, it will instantiate a function that looks something like this:
```
template <>
void print<5>()
{
    std::cout << 5 << '\n';
}
```

## What are non-type template parameters useful for?

As of C++20, function parameters cannot be constexpr. This is true for normal functions, constexpr functions, and even consteval functions.

Let's say we have a function like this one below:
```cpp
#include <cassert>
#include <cmath> // for std::sqrt
#include <iostream>

double getSqrt(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");

    // The assert above will probably be compiled out in non-debug builds
    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

int main()
{
    std::cout << getSqrt(5.0) << '\n';
    std::cout << getSqrt(-5.0) << '\n';

    return 0;
}
```

When run, the call to `getSqrt(-5.0)` will runtime assert out. But wouldn't it be better if we could static_assert so that errors such as this one would be caught at compile time? However, static_assert requires a constant expression, and function parameters can't be constexpr.

However if we use our non-type template parameter instead, then we can do exactly that:
```cpp
#include <cmath> // for std::sqrt
#include <iostream>

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (D >= 0) // ignore the constexpr here for this example
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

int main()
{
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    return 0;
}
```

This version fails to compile when the compiler encounters `getSqrt<-5.0>()`. It will instantiate and call a function that looks something like this:
```cpp
template <>
double getSqrt<-5.0>()
{
    static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (-5.0 >= 0) // ignore the constexpr here for this example
        return std::sqrt(-5.0);

    return 0.0;
}
```

The static_assert condition is false, so the compiler asserts out.

## Type deducation for non-type template parameters using `auto` C++17

As of C++17, non-type template parameters may use `auto` to have the compiler deduce the non-type template parameter from the template argument:

```cpp
#include <iostream>

template <auto N> // deduce non-type template parameter from template argument
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // N deduced as int `5`
    print<'c'>(); // N deduced as char `c`

    return 0;
}
```


