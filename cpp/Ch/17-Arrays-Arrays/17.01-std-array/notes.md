A summary of containers and arrays:
- Containers provide storage for a collection of unnamed objects (called elements).
- Arrays allocate their elements contiguously in memory, and allow fast, direct access to any element via subscripting.
- C++ has three different array types that are commonly used: `std::vector`, `std::array`, and C-style arrays.

There's fixed and dynamic arrays:
- Fixed-size arrays (also called fixed-length arrays) require that the length of the array be known at the point of instantiation, and that length cannot be changed afterward. C-style arrays and `std::array` are both fixed-size arrays.
- Dynamic arrays can be resized at runtime. `std::vector` is a dynamic array.

## So why not use dynamic arrays for everything?

- Vectors are slightly less performant than fixed-size arrays.
- Vectors only supports `constexpr` in very limited contexts

## Defining a `std::array`

`std::array` is defined in the `<array>` header file and there are more similarities than differences between vectors and arrays:
```cpp
#include <array>  // for std::array
#include <vector> // for std::vector

int main()
{
    std::array<int, 5> a {};  // a std::array of 5 ints

    std::vector<int> b(5);    // a std::vector of 5 ints (for comparison)

    return 0;
}
```

Notice how we declare a `std::array` differently. There's 2 template arguments vs vector having 1. We defined the type of the array elements (`int`) and the length of the array (`5`).

- The length of a `std::array` must also be a constant expression and the value provided is most often an integral literal, constexpr variable, or unscoped enumerator:
```cpp
#include <array>

int main()
{
    std::array<int, 7> a {}; // Using a literal constant

    constexpr int len { 8 };
    std::array<int, len> b {}; // Using a constexpr variable

    enum Colors
    {
         red,
         green,
         blue,
         max_colors
    };

    std::array<int, max_colors> c {}; // Using an enumerator

#define DAYS_PER_WEEK 7
    std::array<int, DAYS_PER_WEEK> d {}; // Using a macro (don't do this, use a constexpr variable instead)

    return 0;
}
```

This is not allowed:
```cpp
#include <array>
#include <iostream>

void foo(const int length) // length is a runtime constant
{
    std::array<int, length> e {}; // error: length is not a constant expression
}

int main()
{
    // using a non-const variable
    int numStudents{};
    std::cin >> numStudents; // numStudents is non-constant

    std::array<int, numStudents> {}; // error: numStudents is not a constant expression

    foo(7);

    return 0;
}
```

## Aggregate initialization of a `std::array`

`std::array` is an aggregate, which means it has no constructors and instead is initialized using aggregate initialization. As a quick recap, aggregate initialization allows us to directly initialize the members of aggregates. To do this, we provide an initializer list, which is a brace-enclosed list of comma-separated initialization values.

Because we generally want our elements to be initialized (to prevent undefined behavior), we want to value initialize (using empty braces) `std::array` when defined with no initializers:
```cpp
#include <array>
#include <vector>

int main()
{
    std::array<int, 5> a;   // Members default initialized (int elements are left uninitialized)
    std::array<int, 5> b{}; // Members value initialized (int elements are zero initialized) (preferred)

    std::vector<int> v(5);  // Members value initialized (int elements are zero initialized) (for comparison)

    return 0;
}
```

## Const and constexpr `std::array`

A `std::array` can be const or constexpr:
```cpp
#include <array>

int main()
{
    const std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```

```cpp
#include <array>

int main()
{
    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```

Even though the elements of `const std::array` are not explicitly marked const, they are still treated as if they are.

## Using CTAD for `std::array` (C++17)

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5>
    constexpr std::array a2 { 9.7, 7.31 };     // The type is deduced to std::array<double, 2>

    return 0;
}
```

## Accessing array elements using `operator[]`

The same way as vectors:
```cpp
#include <array> // for std::array
#include <iostream>

int main()
{
    constexpr std::array<int, 5> prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3]; // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```


