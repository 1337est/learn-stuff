## Make intentional narrowing conversions explicit

**Narrowing conversions** are potentially unsafe numeric conversions where the destination type may not be able to hold all the values of the source type.

Use of `static_case` is common when you want to explicitly perform a narrowing conversion. This also suppresses any compiler warnings/errors that would otherwise result.

```cpp
void someFcn(int i)
{
}

int main()
{
    double d{ 5.0 };

    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning

    // good: we're explicitly telling the compiler this narrowing conversion is intentional
    someFcn(static_cast<int>(d)); // no warning generated

    return 0;
}
```

- Brace initialization disallows narrowing conversions. Use `static_cast` to explicitly perform a narrowing conversion when using brace initialization

```cpp
int main()
{
    int i { 3.5 }; // won't compile

    double d { 3.5 };
    // static_cast<int> converts double to int, initializes i with int result
    int i { static_cast<int>(d) };

    return 0;
}
```

## Some constexpr conversions aren't considered narrowing

Due to the nature of constexpr's being replaced by values, when the source value of a narrowing conversion is constexpr, the specific value to be converted must be known to the compiler. The compiler can perform conversion itself, and checks whether the value was preserved. If the value was not preserved, the compiler can halt compilation with an error. However, if the value is preserved, the conversion is not considered to be narrowing because the compiler can simply replace the entire conversion with the converted result/value, knowing that doing so is safe.

```cpp
#include <iostream>

int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```


