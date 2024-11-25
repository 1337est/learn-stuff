Consider the following function:
```cpp
int add(int x, int y)
{
    return x + y;
}
```

This trivial function adds 2 integers and return an integer result. However, what if we want to add 2 floating point numbers? One way to laboriously work around this issue is to define multiple functions with slightly different names:
```cpp
int addInteger(int x, int y)
{
    return x + y;
}

double addDouble(double x, double y)
{
    return x + y;
}
```

This sucks, and we can do better.

## Introduction to function overloading

**Function overloading** allows us to create multiple functions with the same name, so long as each identically named function has different parameter types:

```cpp
int add(int x, int y) // integer version
{
    return x + y;
}

double add(double x, double y) // floating point version
{
    return x + y;
}

int main()
{
    return 0;
}
```

This doesn't resort into a naming conflict and will compile because the parameter types of these functions differ, so the compiler can differentiate these functions and treats them like separate functions that just happen to share the same name.

## Introduction to overload resolution

When a function call is made to a function that has been overloaded, an **overload resolution** is needed, where the compiler will try and match the function call to the appropriate overload based on the arguments provided in the function call.

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

double add(double x, double y)
{
    return x + y;
}

int main()
{
    std::cout << add(1, 2); // calls add(int, int)
    std::cout << '\n';
    std::cout << add(1.2, 3.4); // calls add(double, double)

    return 0;
}
```

## Making it compile

In order for a program using overloaded function to compile, 2 things must be true:

1. Each overloaded function has to be differentiated from the others.
2. Each call to an overloaded function has to resolve to an overloaded function.

If these conditions aren't met, a compiler error results. We'll explore these 2 conditions in detail in the next sections.




