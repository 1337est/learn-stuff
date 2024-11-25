Since the compiler already has to deduce the return type from the return statement, in C++14 and greater, the `auto` keyword was extended to do function return type deduction:

```cpp
auto add(int x, int y)
{
    return x + y;
}
```

The compiler will deduce that the return type of this function is int.

However, when using an `auto` return type, all return statements within the function must return values of the same type, otherwise compiler error:

```cpp
auto someFcn(bool b)
{
    if (b)
        return 5; // return type int
    else
        return 6.7; // return type double
}
```

- A major downside of functions that use `auto` return types is that such functions must be fully defined before they can be used (a forward declaration isn't sufficient).

```cpp
#include <iostream>

auto foo();

int main()
{
    std::cout << foo() << '\n'; // the compiler has only seen a forward declaration at this point

    return 0;
}

auto foo()
{
    return 5;
}
```

- Favor explicit return types over function return type deduction for normal functions.

## Trailing return type syntax

The `auto` keyword can be used to declare functions using **trailing return syntax**, where the return type is specified after the rest of the function prototype

Normally written:
```cpp
int add(int x, int y)
{
  return (x + y);
}
```

With trailing return syntax:
```cpp
auto add(int x, int y) -> int
{
  return (x + y);
}
```

Trailing return syntax doesn't perform type deduction, but is part of the syntax to use trailing return type.

Why do this?

It makes all your function names line up and is also required for some advanced features of C++, such as lambdas:

```cpp
auto add(int x, int y) -> int;
auto divide(double x, double y) -> double;
auto printSomething() -> void;
auto generateSubstring(const std::string &s, int start, int len) -> std::string;
```

- Prefer traditional function return syntax except in situations that require the trailing return syntax.

## Type deduction can't be used for function parameter types

Prior to C++20, this would have a compiler error:

```cpp
#include <iostream>

void addAndPrint(auto x, auto y)
{
    std::cout << x + y << '\n';
}

int main()
{
    addAndPrint(2, 3); // case 1: call addAndPrint with int parameters
    addAndPrint(4.5, 6.7); // case 2: call addAndPrint with double parameters

    return 0;
}
```

In C++20, the `auto` keyword was extended so the above program would work/compile. However, `auto` here isn't invoking type deduction but is triggering a different feature called **function templates** that was designed to actually handle such cases (covered in 11.6 && 11.9).
