A **default argument** is a default value provided for a function parameter.

```cpp
void print(int x, int y=10) // 10 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

If the caller provides an argument for `y`, then the called argument is used. However, if the function call doesn't provide an argument, the value of the default argument is used:

```cpp
#include <iostream>

void print(int x, int y=4) // 4 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(1, 2); // y will use user-supplied argument 2
    print(3); // y will use default argument 4, as if we had called print(3, 4)

    return 0;
}
```

```
x: 1
y: 2
x: 3
y: 4
```

* You must use the assignment operator to specify a default argument. Using parethesis or brace initialization won't work:
```cpp
void foo(int x = 5);   // ok
void goo(int x ( 5 )); // compile error
void boo(int x { 5 }); // compile error
```

## When to use default arguments

When there's a reasonable default value for a function, but for which you want to let the caller override if they wish. E.g.
```cpp
int rollDie(int sides=6);
void openLogFile(std::string filename="default.log");
```

## Multiple default arguments

A function can have multiple parameters with default arguments:
```cpp
#include <iostream>

void print(int x=10, int y=20, int z=30)
{
    std::cout << "Values: " << x << " " << y << " " << z << '\n';
}

int main()
{
    print(1, 2, 3); // all explicit arguments
    print(1, 2); // rightmost argument defaulted
    print(1); // two rightmost arguments defaulted
    print(); // all arguments defaulted

    return 0;
}
```
```
Values: 1 2 3
Values: 1 2 30
Values: 1 20 30
Values: 10 20 30
```

BEWARE! C++ does not (as of C++23) support a function call syntax such as `print(,,3)` as a way to provide an explicit value f or `z` while using the default arguments for `x` and `y`. This has 3 consequences:
1. In a function call, any explicitly provided arguments must be the leftmost arguments (arguments with defaults cannot be skipped):
```cpp
void print(std::string_view sv="Hello", double d=10.0);

int main()
{
    print();           // okay: both arguments defaulted
    print("Macaroni"); // okay: d defaults to 10.0
    print(20.0);       // error: does not match above function (cannot skip argument for sv)

    return 0;
}
```

2. If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default arguments:
```cpp
void print(int x=10, int y); // not allowed, y must be given a default
```

3. If more than one parameter has a default argument, the leftmost parameter should be the one most likely to be explicitly set by the user. This makes sense, given the previous 2 rules. The user would explicitly call the leftmost parameters and the rightmost parameters would be defaulted. It shouldn't really be the other way around due to the rules.

## Default arguments cannot be redeclared, and must be declared before use

* Note: Remember, a **translation unit** is what gets compiled and consists of the source file and any headers/included content (either directly or indirectly) associated with it.

Once declared, a default argument cannot be redeclared in the same translation unit. That means for a function with a forward declaration AND a function definition, the default argument cannot be declared in both, but only one.

```cpp
#include <iostream>

void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // compile error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

The default argument must also be declared in the translation unit before it can be used:
```cpp
#include <iostream>

void print(int x, int y); // forward declaration, no default argument

int main()
{
    print(3); // compile error: default argument for y hasn't been defined yet

    return 0;
}

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

The best practice is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by the other files and included before use (particularly if it's in a header file).

```cpp
// in foo.h
#ifndef FOO_H
#define FOO_H
void print(int x, int y=4);
#endif
```
```cpp
// in main.cpp
#include "foo.h"
#include <iostream>

void print(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(5);

    return 0;
}
```

In the above example, we're able to use the default argument for function `print()` because main.cpp #includes foo.h, which has the forward declaration that defines the default argument. Recall the definition of a **translation unit** above. It includes any headers/included content associated with it.

## Default arguments and function overloading

Functions with default arguments may be overloaded and the following is allowed:
```cpp
#include <iostream>
#include <string_view>

void print(std::string_view s)
{
    std::cout << s << '\n';
}

void print(char c = ' ')
{
    std::cout << c << '\n';
}

int main()
{
    print("Hello, world"); // resolves to print(std::string_view)
    print('a');            // resolves to print(char)
    print();               // resolves to print(char)

    return 0;
}
```

Beware of ambiguity with defaulted arguments. Consider the following:
```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)
```

Here are some function calls:
```cpp
print(1, 2); // will resolve to print(int, int)
print(1, 2.5); // will resolve to print(int, double)
print(1); // ambiguous function call
```

