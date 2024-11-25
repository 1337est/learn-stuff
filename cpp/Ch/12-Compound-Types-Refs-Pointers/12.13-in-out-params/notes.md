A function and its caller communicate with each other via 2 mechanisms: parameters and return values. When a function is called, the caller provides the arguments, which the function receives via its parameters. These arguments can be passed by value, reference, or address.

Typically, we'll pass arguments by value or const reference. But there are times when we might need to do otherwise.

## In parameters
In most cases, a function parameter is used only to receive an input from the caller. Parameters that are used only for receiving input from the caller are sometimes called **in parameters**.
```cpp
#include <iostream>

void print(int x) // x is an in parameter
{
    std::cout << x << '\n';
}

void print(const std::string& s) // s is an in parameter
{
    std::cout << s << '\n';
}

int main()
{
    print(5);
    std::string s { "Hello, world!" };
    print(s);

    return 0;
}
```

In-parameters are typically passed by value or by const reference.

## Out parameters

A function argument passed by (non-const) reference (or by address) allows the function to modify the value of an object passed as an argument.

A function parameter that is used only for the purpose of returning information back to the caller is called an **out parameter**.
```cpp
#include <cmath>    // for std::sin() and std::cos()
#include <iostream>

// sinOut and cosOut are out parameters
void getSinCos(double degrees, double& sinOut, double& cosOut)
{
    // sin() and cos() take radians, not degrees, so we need to convert
    constexpr double pi { 3.14159265358979323846 }; // the value of pi
    double radians = degrees * pi / 180.0;
    sinOut = std::sin(radians);
    cosOut = std::cos(radians);
}

int main()
{
    double sin { 0.0 };
    double cos { 0.0 };

    double degrees{};
    std::cout << "Enter the number of degrees: ";
    std::cin >> degrees;

    // getSinCos will return the sin and cos in variables sin and cos
    getSinCos(degrees, sin, cos);

    std::cout << "The sin is " << sin << '\n';
    std::cout << "The cos is " << cos << '\n';

    return 0;
}
```

This function has parameter `degrees` whose argument is passed by value as input, and "returns" 2 parameters (by reference) as output. The initial value passed to these parameters doesn't matter, and we should expect them to be overwritten. By convention, output parameters are the rightmost parameters.

Let's break it down to make more sense of this:
1. The main function creates local variables `sin` and `cos`.
2. These variables are passed into function `getSinCos()` by reference (rather than by value). This means `getSinCos()` has access to the actual `sin` and `cos` variables in `main()`, not just copies. `getSinCos()` assigns new values to `sin` and `cos`, which overwrites the old values they had.
3. Function `main()` then prints these updated values.

If `sin` and `cos` had been passed by value instead, then copies of `sin` and `cos` would have been changed and discarded at the end of the function.

## Out parameters have an unnatural syntax

There are a few downsides to out-parameters:
1. The caller must instantiate (and initialize) objects and pass them as arguments, even if it doesn't intend to use them.
2. Because the caller must pass in objects, these values can't be used as temporaries, or easily used in a single expression.

Here we illustrate both of these downsides:
```cpp
#include <iostream>

int getByValue()
{
    return 5;
}

void getByReference(int& x)
{
    x = 5;
}

int main()
{
    // return by value
    [[maybe_unused]] int x{ getByValue() }; // can use to initialize object
    std::cout << getByValue() << '\n';      // can use temporary return value in expression

    // return by out parameter
    int y{};                // must first allocate an assignable object
    getByReference(y);      // then pass to function to assign the desired value
    std::cout << y << '\n'; // and only then can we use that value

    return 0;
}
```

## Out-parameters by reference don't make it obvious the arguments will be modified

When we assign a function's return value to an object, it's clear that the value of the object is being modified:
```cpp
x = getByValue(); // obvious that x is being modified
```

However, if we look at the `getSinCos()` example again:
```cpp
getSinCos(degrees, sin, cos);
```
Here it isn't clear that this function call has `degrees` as an in parameter, but `cos` and `sin` as out parameters.

- It's best practice to avoid out-parameters (except rarely when there's no better option)
- Prefer pass by reference for non-optional out-parameters


