## Class template argument deduction (CTAD) (C++17)

Starting in C++17, when instantiating an object from a class template, the compiler can deduce the template types from the types of the object's initializer (this is called **class template argument deduction** or **CTAD** for short):
```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<int, int> p1{ 1, 2 }; // explicitly specify class template std::pair<int, int> (C++11 onward)
    std::pair p2{ 1, 2 };           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)

    return 0;
}
```

CTAD is only performed if no template argument list is present (e.g. without the `<>`):
```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<> p1 { 1, 2 };    // error: too few template arguments, both arguments not deduced
    std::pair<int> p2 { 3, 4 }; // error: too few template arguments, second argument not deduced

    return 0;
}
```

Since CTAD is a form of type deduction, we can use literal suffixes to change the deduced type:
```cpp
#include <utility> // for std::pair

int main()
{
    std::pair p1 { 3.4f, 5.6f }; // deduced to pair<float, float>
    std::pair p2 { 1u, 2u };     // deduced to pair<unsigned int, unsigned int>

    return 0;
}
```

## Template argument deduction guides (C++17 only, fixed in C++20)

You may find it surprising that the following program doesn't compile in C++17:
```cpp
// define our own Pair type
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

int main()
{
    Pair<int, int> p1{ 1, 2 }; // ok: we're explicitly specifying the template arguments
    Pair p2{ 1, 2 };           // compile error in C++17 (okay in C++20)

    return 0;
}
```

You'll likely get some error to the affect of "cannot deduce template arguments" or something similar. This is because in C++17, CTAD doesn't know how to deduce the template arguments for aggregate class templates. To address this, we can provide the compiler with a **deduction guide**, which tells the compiler how to deduce the template arguments for a given class template:
```cpp
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    return 0;
}
```

The deduction guide for our `Pair` class is simple, but let's break it down:
```cpp
// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;
```

1. First we use the same template type definition as our `Pair` class. This makes sense because we need to do this before using `T` and `U`.
2. On the right hand side (RHS) of the arrow, we have the type that we're helping the compiler to deduce.
3. On the left hand side (LHS) of the arrow, we tell the compiler what kind of declaration to look for. In this case, we're telling it to look for a declaration of some object named `Pair` with 2 arguments (of types `T` and `U`).

Putting it all together, we're telling the compiler that if it sees a declaration of a `Pair` with 2 arguments of type `T` and `U`, respectively, it should deduce the type to be a `Pair<T, U>`.

So when the compiler sees the definition `Pair p2{ 1, 2 };`, in our program, it will say, "This is a `Pair` and there are 2 arguments of type `int` and `int`, so using the deduction guide, I should deduce this to be a `Pair<int, int>`".

**Note:**
- C++20 added the ability for the compiler to automatically generate deduction guides for aggregates, so deduction guides should only be needed to provide compatibility for C++17.

## Type template parameters with default values

Just like function parameters can have default arguments, template parameters can be given default values. These will be used when the template parameter isn't explicitly specified and can't be deduced:
```cpp
template <typename T=int, typename U=int> // default T and U to type int
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    Pair p3;                   // uses default Pair<int, int>

    return 0;
}
```

## CTAD doesn't work with non-static member initialization

CTAD will not work when initializing the member of a class type using non-static member initialization. All template arguments must be explicitly specified:
```cpp
#include <utility> // for std::pair

struct Foo
{
    std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
    std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
};

int main()
{
    std::pair p3{ 1, 2 };           // ok, CTAD can be used here
    return 0;
}
```

## CTAD doesn't work with function parameters

CTAD stands for "class template argument deduction" not "class template parameter deduction". That would be CTPD (this is made up). Therefore, it will only deduce the types of template arguments, not template parameters:
```cpp
#include <iostream>
#include <utility>

void print(std::pair p) // compile error, CTAD can't be used here
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

In such a case, you should use a template instead:
```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

Here there is no deduction because we are explicitly specifying our types `T` and `U`.
