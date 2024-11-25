## Introduction to constants

C++ supports 2 different kinds of constants:
- **Named constants:** constant values that are associated with an identifier. Sometimes these are called symbolic constants, or just plainly constants.
- **Literal constants:** constant values that are not associated with an identifier

## Types and named constants

There are 3 ways to define a named constant in C++:
1. Constant variables (covered in this lesson)
2. Object-like macros with substitution text (covered in 2.10 and additional coverage here)
3. Enumerated constants (covered in lesson 13.02)

## Declaring a constant variable (oxymoronic)

A variable whose value cannot be changed is a constant variable.

To declare a constant variable, we place the `const` keyword (called a "const qualifier") adjacent to the object's type:

```cpp
const double gravity { 9.8 }; // preferred use of const before type
int const sidesInSquare { 4 }; // "east const" style, okay but not preferred
```

## Const variables must be initialized

```cpp
int main()
{
    const double gravity; // error: const variables must be initialized
    gravity = 9.9;        // error: const variables can not be changed

    return 0;
}
```

Consider also, the following:

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    const int constAge { age }; // initialize const variable using non-const value

    age = 5;      // ok: age is non-const, so we can change its value
    constAge = 6; // error: constAge is const, so we cannot change its value

    return 0;
}
```

## Object-like macros with substitution text

Object-like macros with substitution text is a constant value, so object-like macros with substitution text are also named constants
```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';

    return 0;
}
```

`MY_NAME` is a name, and the substitution text "Alex" is a constant value.

## Type qualifiers

A type qualifier (sometimes just called qualifier), is a keyword that's applied to a type that modifies how that type behaves. The `const` used to declare a constant variable is called a const type qualifier (or simply const qualifier)

As of C++23, C++ only has 2 type qualifiers: `const` and `volatile`. These are referred to as **cv-qualifiers** in technical documentation.

- A cv-unqualified type is a type with no type qualifiers (e.g. int)
- a cv-qualified type is a type with one or more type qualifiers applied (e.g. const int)
- A possibly cv-qualified type is a type that may be cv-unqualified or cv-qualified.


