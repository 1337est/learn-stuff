## Numeric promotion

C++ was designed to be portable and performant across a wide range of architectures, the language designers didn't want to assume a given CPU architecture would be able to efficiently manipulate values that were narrower than the natural data size for that CPU.

This is a pickle, but luckily we have **numeric promotions** to aid us in these type conversions. A **numeric promotion** is a type conversion that allows narrower types (e.g. `char`, which is an 8-bit value), so they can be processed efficiently/harder/better/faster/stronger.

All numeric promotions are **value-preserving**, which means the converted value will always be equivalent to the source value (just a different type).

- We can avoid redundancy with numeric promotions.
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

If type conversion didn't exist, we would have to write a print function for each type! That's too many...

- Numeric promotion categories are: **integral promotions**, and **floating point promotions**, and only these conversions are considered to be numeric promotions.

## Floating point promotions

```cpp
#include <iostream>

void printDouble(double d)
{
    std::cout << d << '\n';
}

int main()
{
    printDouble(5.0); // no conversion necessary
    printDouble(4.0f); // numeric promotion of float to double

    return 0;
}
```

Nuff said.

## Integral promotions

Now time for spicy:

- `signed char` or `signed short` can be converted to `int`
- `unsigned char`, `char8_t`, and `unsigned short` can be converted to `int` iff (stands for "if and only if") `int` can hold the entire range of the type, or `unsigned int` otherwise.
- `bool` can be converted to `int` with false being `0` and true being `1`.

Assuming 8 bit bytes and `int` being 4 bytes or more, the above means:
- `bool`, `char`, `signed char`, `unsigned char`, `signed short`, and `unsigned short` all get promoted to `int`.

This let's us write `int` parameters and use it with a wide variety of other integral types:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(2);

    short s{ 3 }; // there is no short literal suffix, so we'll use a variable for this one
    printInt(s); // numeric promotion of short to int

    printInt('a'); // numeric promotion of char to int
    printInt(true); // numeric promotion of bool to int

    return 0;
}
```

