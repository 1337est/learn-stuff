- Numeric promotions are conversions of specific narrower numeric types to wider numeric types (typically `int` or `double`) that can be processed efficiently.

- There's also **numeric conversions** which cover additional type conversions between fundamental types.

There are 5 basic types of numeric conversions:

1. Converting an integral type to any other integral type (EXCLUDING integral promotions):
```cpp
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int
```

2. Converting float to floating point type (EXCLUDING floating point promotions):
```cpp
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double
```

3. Converting floating point type to any integral type
```cpp
int i = 3.5; // convert double to int
```

4. Converting an integral type to any floating point type:
```cpp
double d = 3; // convert into to double
```

5. Converting an integral type or a floating point type to a bool:
```cpp
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```

- Note that because brace initialization {} strictly disallows some types of numeric conversions, we use copy initialization in this lesson in order to keep the examples simple.

## Safe and potentially unsafe conversions

If you're going up in scale, and there isn't a chance to lose data integrity, then that's a safe conversion, vs. the other way around. E.g. going from `int` to `long` or `short` to `double` are safe conversions, since there is no potential loss of data.

This is an example of safe conversions:
```cpp
#include <iostream>

int main()
{
    int n = static_cast<int>(static_cast<long>(3)); // convert int 3 to long and back
    std::cout << n << '\n';                         // prints 3

    char c = static_cast<char>(static_cast<double>('c')); // convert 'c' to double and back
    std::cout << c << '\n';                               // prints 'c'

    return 0;
}
```

This is an example of unsafe conversions:
```cpp
int main()
{
    int n1 { 5 };
    unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

    int n2 { -5 };
    unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

    return 0;
}
```

Another example of unsafe conversions:
```cpp
#include <iostream>

int main()
{
    double d { static_cast<double>(static_cast<int>(3.5)) }; // convert double 3.5 to int and back
    std::cout << d << '\n'; // prints 3

    double d2 { static_cast<double>(static_cast<float>(1.23456789)) }; // convert double 1.23456789 to float and back
    std::cout << d2 << '\n'; // prints 1.23457

    return 0;
}
```


