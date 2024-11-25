C-style arrays were inherited from the C language, and are built-in to the core language of C++ and t therefore we don't need to #include a header file to use them.

## Declaring a C-style array

```cpp
int main()
{
    int testScore[30] {};      // Defines a C-style array named testScore that contains 30 value-initialized int elements (no include required)

//  std::array<int, 30> arr{}; // For comparison, here's a std::array of 30 value-initialized int elements (requires #including <array>)

    return 0;
}
```

The length of a C-style array must be at least 1 and the compiler will error if the array length is zero, negative, or a non-integral value.

## The array length of a c-style array must be a constant expression

Just like `std::array`, when declaring a C-style array, the length of the array must be a constant expression (of type `std::size_t`, though this typically doesn't matter).

## Subscripting a C-style array

C-style arrays can be indexed using the subscript `operator[]`:
```cpp
#include <iostream>

int main()
{
    int arr[5]; // define an array of 5 int values

    arr[1] = 7; // use subscript operator to index array element 1
    std::cout << arr[1]; // prints 7

    return 0;
}
```

C-style arrays can have a signed or unsigned integral type or an unscoped enumeration. This means C-style arrays are not subject to all of the conversion indexing issues that  the standard library container classes have:
```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    int s { 2 };
    std::cout << arr[s] << '\n'; // okay to use signed index

    unsigned int u { 2 };
    std::cout << arr[u] << '\n'; // okay to use unsigned index

    return 0;
}
```

## Aggregate initialization of C-style arrays

Quick recap of aggregate initialization:
```cpp
int main()
{
    int fibonnaci[6] = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    int prime[5] { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    return 0;
}
```

C-style arrays should be value initialized (with empty braces) when defined with no initializers:
```cpp
int main()
{
    int arr1[5];    // Members default initialized int elements are left uninitialized)
    int arr2[5] {}; // Members value initialized (int elements are zero uninitialized) (preferred)

    return 0;
}
```

Class Template Argument Deduction (CTAD) doesn't work because C-style arrays aren't class templates (remember, C++ was Bjarne's idea of making a "C with Classes". C doesn't have classes):
```cpp
int main()
{
    auto squares[5] { 1, 4, 9, 16, 25 }; // compile error: can't use type deduction on C-style arrays

    return 0;
}
```

## Omitted lengths

There's redundancy in stating the length when the compiler can deduce the length:
```cpp
int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // prime has length 5

    return 0;
}
```

We're explicitly telling the compiler that the array has length 5, but we're also initializing it with 5 elements. We can omit the length and let the compiler deduce the length of the array from the number of initializers:
```cpp
int main()
{
    const int prime1[5] { 2, 3, 5, 7, 11 }; // prime1 explicitly defined to have length 5
    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 deduced by compiler to have length 5

    return 0;
}
```

## Const and constexpr C-style arrays

C-style arrays can be `const` or `constexpr`:
```cpp
#include <iostream>

namespace ProgramData
{
    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // an array of constexpr int
}

int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // an array of const int
    prime[0] = 17; // compile error: can't change const int

    return 0;
}
```

## The sizeof a C-style array

We can use the `sizeof()` operator to get the size of an object or type in bytes:
```cpp
#include <iostream>

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 }; // the compiler will deduce prime to have length 5

    std::cout << sizeof(prime); // prints 20 (assuming 4 byte ints)

    return 0;
}
```

Considering that an int is 4 bytes, this would mean that there are 5 ints.

## Getting the length of a C-style array

In C++17, you would use `std::size()` which returns the array length as an unsigned integral value of type `std::size_t`, and in C++20 you would use `std::ssize()` which returns the array length as a signed integral value of (probably) type `std::ptrdiff_t`:
```cpp
#include <iostream>
#include <iterator> // for std::size and std::ssize

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };   // the compiler will deduce prime to have length 5

    std::cout << std::size(prime) << '\n';  // C++17, returns unsigned integral value 5
    std::cout << std::ssize(prime) << '\n'; // C++20, returns signed integral value 5

    return 0;
}
```

You should prefer the signed integral value if you're using C++20 and greater.

## C-style arrays don't support assignment

You may find this odd, but it's a feature:
```cpp
int main()
{
    int arr[] { 1, 2, 3 }; // okay: initialization is fine
    arr[0] = 4;            // assignment to individual elements is fine
    arr = { 5, 6, 7 };     // compile error: array assignment not valid

    return 0;
}
```

This is because the left-operand needs to be a modifiable lvalue, and C-style array are not considered to be modifiable lvalues.

If you need to assign a new list of values, it's best to use a `std::vector` instead, assign new values element by element (that would suck), or use `std::copy` to copy an existing C-style array:
```cpp
#include <algorithm> // for std::copy

int main()
{
    int arr[] { 1, 2, 3 };
    int src[] { 5, 6, 7 };

    // Copy src into arr
    std::copy(std::begin(src), std::end(src), std::begin(arr));

    return 0;
}
```


