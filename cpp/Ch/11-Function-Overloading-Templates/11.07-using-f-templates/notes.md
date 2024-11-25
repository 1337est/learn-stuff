# Using function templates

Function templates aren't exactly functions -- their code isn't compiled or executed directly, but instead they generate functions that are compiled and executed.

To use our `max<T>` function template, we can make a function call with the following syntax
```
max<actual_type>(arg1, arg2); // actual_type is some actual type, like int or double
```
This almost looks like a normal function call, but the primary difference is the addition of the type in angled brackets (called a **template argument**), which specifies the actual type that will be used in place of template type `T`.

For example:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

When the compiler encounters the function call `max<int>(1, 2)`, it will determine that a function definition for `max<int>(int, int)` does not already exist. Consequently, the compiler will implicitly use our `max<T>` function template to create one.

- The process of creating functions (with specific types) from function templates (with template types) is called **function template instantiation** (or **instantiation** for short).
- When a function is instantiated due to a function call, it's called **implicit instantiation**.
- A function that is instantiated from a template is technically called a **specialization**, but is commonly referred to as a **function instance**.
- The template from which a specialization is produced is called a **primary template**.
- Function instances are normal functions in all regards.

The process of instantiating a function is simple: the compiler essentially clones the primary template and replaces the template type (`T`) with the actual type we've specified (`int`).

Therefore, when we call `max<int>(1, 2)`, the function specialization that gets instantiated looks something like this:
```cpp
template<> // ignore this for now
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}
```

Here's an example showing what the compiler actually compiles after all instantiations are done:
```cpp
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

* Personal note: I think what's happening here, is that the function call template instantiates the function, and therefore below the `T max(T x, T y);` we get the generated function due to the function call.

Let's do another example:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```

This works similarly to the previous example, but our function template will be used to generate 2 functions this time: one time replacing `T` with `int`, and the other time replacing `T` with `double`. After all instantiations, the program looks something like this:
```cpp
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

template<>
double max<double>(double x, double y) // the generated function max<double>(double, double)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```

An interesting note: When we instantiate `max<double>`, the instantiated function has parameters of type `double`, meaning that  the `int` arguments that were provided are implicitly converted to `double`.

## Template argument deduction

In most cases, the actual types we want to use for instantiation will match the type of our function parameters. In cases where the type of the arguments match the actual type we want, we don't need to specify the actual type -- instead, we can use **template argument deduction** to have the compiler deduce the actual type that should be used from the argument types in the function call.

E.g., instead of making a function call like this:
```cpp
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
```

We can do one of these instead:
```cpp
std::cout << max<>(1, 2) << '\n';
std::cout << max(1, 2) << '\n';
```

The difference between the 2 cases has to do with how the compiler resolves the funciton call from a set of overloaded functions.
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
    std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    return 0;
}
```

In most cases, the bottom case that looks like a normal function call, is the syntax we'll use to call functions instantiated from a function template.

Why?
- The syntax is more concise
- It's rare that we'll have both a matching non-template function and a function template.
- If we do have a matching non-template function and a matching function template, we will usually prefer the non-template function to be called.

The 3rd bullet point is non-obvious right away, but a function template is by design more generic, and a non-template function can handle specific combination of types and will therefore be more optimized than the function template version.

For example:
```cpp
#include <iostream>

// This function template can handle many types, so its implementation is generic
template <typename T>
void print(T x)
{
    std::cout << x; // print T however it normally prints
}

// This function only needs to consider how to print a bool, so it can specialize how it handles
// printing of a bool
void print(bool x)
{
    std::cout << std::boolalpha << x; // print bool as true or false, not 1 or 0
}

int main()
{
    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    std::cout << '\n';

    return 0;
}
```

- Favor the normal function call syntax when making calls to a function instantiated from a function template (unless you have your reasons ofc).

## Function templates with non-template parameters

It's possible to create function templates that have a template parameter and a non-template parameter. The type template parameters can be matched to any type, and the non-template parameters work like the parameters of normal functions:
```cpp
// T is a type template parameter
// double is a non-template parameter
// We don't need to provide names for these parameters since they aren't used
template <typename T>
int someFcn(T, double)
{
    return 5;
}

int main()
{
    someFcn(1, 3.4); // matches someFcn(int, double)
    someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double
    someFcn(1.2, 3.4); // matches someFcn(double, double)
    someFcn(1.2f, 3.4); // matches someFcn(float, double)
    someFcn(1.2f, 3.4f); // matches someFcn(float, double) -- the float is promoted to a double

    return 0;
}
```

## Instantiated functions may not always compile

Consider the following program before compilation:
```cpp
#include <iostream>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```

After compilation:
```cpp
#include <iostream>

template <typename T>
T addOne(T x);

template<>
int addOne<int>(int x)
{
    return x + 1;
}

template<>
double addOne<double>(double x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne(1) << '\n';   // calls addOne<int>(int)
    std::cout << addOne(2.3) << '\n'; // calls addOne<double>(double)

    return 0;
}
```

Everything's dandy and this is the output:
```
2
3.3
```

But what if we try something like this??? Before compilation:
```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::string hello { "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```

the compiler tries to resolve the `addOne(hello)` but it doesn't find a non-template function match for `addOne(std::string)`, but it will find our function template for `addOne(T)`, and determines that it can generate an `addOne(std::string)` function from it. Therefore, the compiler generates and compiles this:
```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x);

template<>
std::string addOne<std::string>(std::string x)
{
    return x + 1;
}

int main()
{
    std::string hello{ "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```

However, obviously this generates a compile error because `x + 1` doesn't make any sense when `x` is a `std::string`. To avoid doing this, just don't do it. Why would you?

## Beware function templates with modifiable static local variables
Static local variables are local variables with static duration (they persist for the lifetime of the program).

Well, since each function instantiated from a template will have a separate version of a static local variable when a static local variable is used in the function template, we get 2 copies in separate functions!

Before compilation:
```cpp
#include <iostream>

// Here's a function template with a static local variable that is modified
template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);
    printIDAndValue(13);

    printIDAndValue(14.5);

    return 0;
}
```

This outputs:
```
1) 12
2) 13
1) 14.5
```
The reason we get `1) 14.5` instead of `3) 14.5` is because the compiler actually compiles and executes this:
```cpp
#include <iostream>

template <typename T>
void printIDAndValue(T value);

template <>
void printIDAndValue<int>(int value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

template <>
void printIDAndValue<double>(double value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);   // calls printIDAndValue<int>()
    printIDAndValue(13);   // calls printIDAndValue<int>()

    printIDAndValue(14.5); // calls printIDAndValue<double>()

    return 0;
}
```

See how `printIDAndValue<int>` and `printIDAndValue<double>` each have their own independent static local variable named `id` that isn't shared between them? Beware!

## Generic programming

Because template types can be replaced with any actual type, template types are sometimes called **generic types**, and because templates can be written agnostically of specific types, programming with templates is sometimes called **generic programming**.
