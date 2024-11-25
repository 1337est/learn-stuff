Of course you can't do something like this:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';  // compile error

    return 0;
}
```

This makes sense because `T` can't be both an `int` and a `double`.

Let's break it down:
- Because we're making a function call without using angled brackets to specify an actual type, the compiler will first look to see if there is a non-template match for `max(int, double)`, and it won't find one.
- Next, it'll try and find a function template match. This fails since `T` can only represent a single type. There's no type for `T` that would allow the compiler to instantiate the function template into a function with 2 different parameter types, since `T` itself is a placeholder and a type of itself. That's like saying an int can be a double as well. It can be converted to a double, but it can't be both, that's silly!
- Now since there weren't any non-template matches, and no template matches, the function call fails to resolve, and we get a compile error.

We can solve this problem in (at least) 3 ways.

## Use static_cast to convert the arguments to matching types

This is straight forward:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // makes this max(double, double)

    return 0;
}
```

However, this is awkward and hard to read

## Provide an explicit type template argument

If we wrote a NON-templated `max(double, double)` function, we could make an implicit type conversion convert our `int` into a `double` so the function call can be resolved:
```cpp
#include <iostream>

double max(double x, double y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // the int argument will be converted to a double

    return 0;
}
```

However, when the compiler is doing template argument deduction, it won't do any type conversions. However, we don't need to deduce if we specify an explicit type template argument to be used instead:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    // we've explicitly specified type double, so the compiler won't use template argument deduction
    std::cout << max<double>(2, 3.5) << '\n';

    return 0;
}
```

While this is more readable than using `static_cast`, it would be nicer if we didn't have to think about the types when making a function call to `max` at all.

## Function templates with multiple template type parameters

The best way to solve this problem is to rewrite our function template in such a way that our parameters can resolve to different types. We'll now use 2 template type parameters (`T` and `U`):
```cpp
#include <iostream>

template <typename T, typename U> // We're using two template type parameters named T and U
T max(T x, U y) // x can resolve to type T, and y can resolve to type U
{
    return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>

    return 0;
}
```

You see, although the problem of `max<int, double>(int, double)` being compiled and instantiated for us has now been solved, now we have a different (more hidden) issue.

Since `double` takes precedence over `int`, our return will be a double due to our arithmetic rules, but our function is defined as returning a `T`, where `T` is an `int`. We're going from `double` to `int`, which is a narrowing conversion problem (and a high potential of loss of data).

You might think, just make the return type `U`, but that doesn't resolve anything since the order of the operands in the function call (and therefore the types) can make us need to replace `U` with `T` now!

This is a good use for the `auto` return type -- we'll let the compiler deduce what the return type should be from the return statement:
```cpp
#include <iostream>

template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}
```

This version of `max` now works fine with operands of different types.

## Abbreviated function templates C++20

When the `auto` keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template type parameter. This method for creating a function template is called an **abbreviated function template**

E.g.
```cpp
auto max(auto x, auto y)
{
    return (x < y) ? y : x;
}
```
is shorthand in C++20 for:
```cpp
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}
```

- Feel free to use abbreviated function templates with a single auto parameter, or where each auto parameter should be an independent type (and you're using C++20 or newer).

## Function templates may be overloaded

Just like normal functions, function templates can be overloaded as well.
```cpp
#include <iostream>

// Add two values with matching types
template <typename T>
T add(T x, T y)
{
    return x + y;
}

// Add two values with non-matching types
// As of C++20 we could also use auto add(auto x, auto y)
template <typename T, typename U>
T add(T x, U y)
{
    return x + y;
}

// Add three values with any type
// As of C++20 we could also use auto add(auto x, auto y, auto z)
template <typename T, typename U, typename V>
T add(T x, U y, V z)
{
    return x + y + z;
}

int main()
{
    std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
    std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
    std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()

    return 0;
}
```
