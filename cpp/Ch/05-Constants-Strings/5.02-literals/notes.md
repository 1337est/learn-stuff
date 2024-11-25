Literals are simply values that are inserted directly into the code:

```cpp
return 5;                       // 5 is an integer literal
bool myNameIsAlex { true };     // true is a boolean literal
double d { 3.4 };               // 3.4 is a double literal
std::cout << "Hello, world!";   // "Hello, world!" is a C-style string literal
```

Literals are also sometimes called **literal constants** because their meaning cannot be redefined (`5` always means the integral value 5).

## The type of a literal

The type of a literal is deduced from the literal's value. E.g., a literal that is a whole number like 5, is deduced to be an int.

By default:

- integer values like 5, 0, and -3, are defaulted to int
- boolean values like true and false are defaulted to bool
- floating point values like 1.2, 0.0, and 3.4 are defaulted to double (not float)
- character values like 'a' and '\n' are defaulted to char
- C-style string values like "Hello, world!" are defaulted to const char[14]..

## Literal suffixes

If the default type of a literal is not as desired, you can change the type of a literal by adding a suffix. Here are some common suffixes:

- Integral data type for unsigned int as suffix u or U
- Integral data type for long as suffix l or L
- Integral data type for unsigned long as suffix ul, uL, Ul, UL, lu, lU, Lu, or LU
- Integral data type for long long as suffix ll or LL
- integral data type for unsigned long long as suffix ull, uLL, Ull, ULL, llu, llU, LLu, or LLU
- integral data type for signed std::size_t as suffix z or Z
- integral data type for std::size_t as suffix uz, uZ, Uz, UZ, zu, zU, Zu, or ZU
- floating point data type for float as suffix f or F
- floating point data type for long double as suffix l or L
- string data type for std::string as suffix s
- string data type for std::string_view as suffix sv

**Note:** The suffix casing of `s` and `sv` must be lowercase, and two consecutive lower-case L's can look like numberic 1's, so prefer uppercase literal suffix L over lowercase l.

## Integral literals

You generally won't need to use suffixes for integral literals, but here's some examples:
```cpp
#include <iostream>

int main()
{
    std::cout << 5 << '\n'; // 5 (no suffix) is type int (by default)
    std::cout << 5L << '\n'; // 5L is type long
    std::cout << 5u << '\n'; // 5u is type unsigned int

    return 0;
}
```

## Floating point literals

By default, floating point literals are of type `double`.

```cpp
#include <iostream>

int main()
{
    std::cout << 5.0 << '\n';  // 5.0 (no suffix) is type double (by default)
    std::cout << 5.0f << '\n'; // 5.0f is type float

    return 0;
}
```
What's wrong with this code?
```cpp
float f { 4.1 }; // warning: 4.1 is a double literal, not a float literal
```

This fixes the issue:
```cpp
float f { 4.1f }; // use 'f' suffix so the literal is a float and matches variable type of float
double d { 4.1 }; // change variable to type double so it matches the literal type double
```

## Scientific notation for floating point literals
```cpp
double pi { 3.14159 }; // 3.14159 is a double literal in standard notation
double avogadro { 6.02e23 }; // 6.02 x 10^23 is a double literal in scientific notation
double electronCharge { 1.6e-19 }; // charge on an electron is 1.6 x 10^-19
```

## String literals

There are two non-obvious things worth noting about C-style string literals

1. All C-style literals have an implicit null terminator. Consider `"hello"`. This has six, not five, characters: `h`, `e`, `l`, `l`, `o`, and `\0` (a character with ASCII code 0). This trailing character is called a **null terminator**, and is used to indicate the end of a string. The hidden null terminator counts as a character.

2. Unlike most other literals (which are values, not objects),  C-style string literals are const objects that are created at the start of the program and are guaranteed to exist for the entirety of the program.

## Magic numbers

- **magic number:** is a literal (usually a number) that either has a unclear meaning or may need to be changed later.

```cpp
const int maxStudentsPerSchool{ numClassrooms * 30 };
setMax(30);
```

Basically, a magic number is something that you should never use. What do the two 30's mean up above? Are they the same? Are they different? Just define what the numbers mean by using symbolic constants instead.

```cpp
const int maxStudentsPerClass { 30 };
const int totalStudents{ numClassrooms * maxStudentsPerClass }; // now obvious what this 30 means

const int maxNameLength{ 30 };
setMax(maxNameLength); // now obvious this 30 is used in a different context
```

If it's obvious in context, then it's not a magic number.


