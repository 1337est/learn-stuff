# Floating numbers

A floating point number is a type variable that holds a number with a fractional component.

Floating point types includes:
- float: 4 bytes
- double: 8 bytes
- long double: 8, 12, or 16 bytes

Although float and double are pretty standardized to 4 bytes and 8 bytes respectively, long double is weird. It's best to avoid.

When using floating point literals, include a decimal even if the decimal is 0.

```cpp
int a { 5 };      // 5 means integer
double b { 5.0 }; // 5.0 is a floating point literal (no suffix means double type by default)
float c { 5.0f }; // 5.0 is a floating point literal, f suffix means float type

int d { 0 }       // 0 is an integer
double e { 0.0 }  // 0.0 is a double
```

**IMPORTANT:** floating point literals default to type double. An `f` suffix is used to denote a literal of type float.

## Printing floating point numbers

```cpp
#include <iostream>

int main()
{
	std::cout << 5.0 << '\n'; // print 5 - std::cout by default doesn't print fractional parts
	std::cout << 6.7f << '\n'; // print 6.7 - expected behavior
	std::cout << 9876543.21 << '\n'; // print 9.87654e+06

	return 0;
}
```

## Floating point range

- 4 bytes range is ±1.18 x 10-38 to ±3.4 x 1038 and 0.0 with precision 6-9 significant digits, typically 7
- 8 bytes range is ±2.23 x 10-308 to ±1.80 x 10308 and 0.0 with precision 15-18 significant digits, typically 16
- 80-bits (typically uses 12 or 16 bytes) range is ±3.36 x 10-4932 to ±1.18 x 104932 and 0.0 with precision 18-21 significant digits
- 16 bytes range is ±3.36 x 10-4932 to ±1.18 x 104932 and 0.0 with precision 33-36 significant digits

## Outputting floating point values

`std::cout` has a default precision of 6.

Example:
```cpp
#include <iostream>

int main()
{
    std::cout << 9.87654321f << '\n';
    std::cout << 987.654321f << '\n';
    std::cout << 987654.321f << '\n';
    std::cout << 9876543.21f << '\n';
    std::cout << 0.0000987654321f << '\n';

    return 0;
}
```

Outputs:
```
9.87654
987.654
987654
9.87654e+006
9.87654e-005
```

We can however, override the default precision that `std::cout` shows by using an output manipulator function named `std::setprecision()` which needs the `iomanip` header file.

```cpp
#include <iomanip> // for output manipulator std::setprecision()
#include <iostream>

int main()
{
    std::cout << std::setprecision(17); // show 17 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float
    std::cout << 3.33333333333333333333333333333333333333 << '\n'; // no suffix means double

    return 0;
}
```

Outputs:
```
3.3333332538604736
3.3333333333333335
```

The float vs double difference is because floats are not as precise as doubles, leaving the float with more error.

## Rounding error

Precision issues also impact any number with too many significant digits.

```cpp
#include <iomanip> // for std::setprecision()
#include <iostream>

int main()
{
    float f { 123456789.0f }; // f has 10 significant digits
    std::cout << std::setprecision(9); // to show 9 digits in f
    std::cout << f << '\n';

    return 0;
}
```

Outputs:
```
123456792
```

123456792 is greater than 123456789.0. The value 123456789.0 has 10 significant digits, but floats are only precise to 7 digits. Therefore, we lose precision in what's known as a **rounding error**.

## NaN and Inf

There are two special categories of floating point numbers:

- **Inf:** Represents infinity and can be positive or negative.
- **NaN:** Stands for "Not a Number".

Example:
```cpp
#include <iostream>

int main()
{
    double zero {0.0};
    double posinf { 5.0 / zero }; // positive infinity
    std::cout << posinf << '\n';

    double neginf { -5.0 / zero }; // negative infinity
    std::cout << neginf << '\n';

    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << nan << '\n';

    return 0;
}
```
Outputs:
```
1.#INF
-1.#INF
1.#IND
```

Although, you should avoid division by 0 altogether.


