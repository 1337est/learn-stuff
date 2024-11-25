Unscoped enumerations are distinct types in C++ and are not type safe. Consider this silly example:
```cpp
#include <iostream>

int main()
{
    enum Color
    {
        red,
        blue,
    };

    enum Fruit
    {
        banana,
        apple,
    };

    Color color { red };
    Fruit fruit { banana };

    if (color == fruit) // The compiler will compare color and fruit as integers
        std::cout << "color and fruit are equal\n"; // and find they are equal!
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```
This prints:
```
color and fruit are equal
```

Since both `color` and `fruit` are set to enumerators that convert to integer value `0`, the compiler says they are equivalent.

This is troublesome, and the C++ designers determined that a cleaner solution for enumerations would be of use.

## Scoped enumerations

That solution was **scoped enumerations** (often called **enum classes** in C++).

Scoped enumerations work similarly to unscoped enumerations, but have 2 primary differences:
1. They won't implicitly convert to integers
2. The enumerators are only placed into the scope region of the enumeration (not into the scope region where the enumeration is defined) -- making them scoped... lol

To make a scoped enumeration we use the keywords `enum class`. The rest of the scoped enumeration definition is the same as an unscoped enumeration definition:
```cpp
#include <iostream>
int main()
{
    enum class Color // "enum class" defines this as a scoped enumeration rather than an unscoped enumeration
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    enum class Fruit
    {
        banana, // banana is considered part of Fruit's scope region
        apple,
    };

    Color color { Color::red }; // note: red is not directly accessible, we have to use Color::red
    Fruit fruit { Fruit::banana }; // note: banana is not directly accessible, we have to use Fruit::banana

    if (color == fruit) // compile error: the compiler doesn't know how to compare different types Color and Fruit
        std::cout << "color and fruit are equal\n";
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```

I like his much more.

## Scoped enumerations define their own scope regions

To access a scoped enumerator, we do so just as if it was in a namespace having the same name as the scoped enumeration:
```cpp
#include <iostream>

int main()
{
    enum class Color // "enum class" defines this as a scoped enum rather than an unscoped enum
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    std::cout << red << '\n';        // compile error: red not defined in this scope region
    std::cout << Color::red << '\n'; // compile error: std::cout doesn't know how to print this (will not implicitly convert to int)

    Color color { Color::blue }; // okay

    return 0;
}
```

Because scoped enumerations offer their own implicit namespacing for enumerators, there's no need to put scoped enumerations inside another scope region unless there's some other compelling reason to do so, as it would be redundant.

## Scoped enumerations don't implicitly convert to integers

This is good, because that's dumb anyways and doesn't make sense to do (at least usually for our usages).

You can still compare enumerators from within the same scoped enumeration:
```cpp
#include <iostream>
int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color shirt { Color::red };

    if (shirt == Color::red) // this Color to Color comparison is okay
        std::cout << "The shirt is red!\n";
    else if (shirt == Color::blue)
        std::cout << "The shirt is blue!\n";

    return 0;
}
```

However, there are occasions where you might want to treat a scoped enumerator as an integral value. In these cases, you can explicitly convert a scoped enumerator to an integer by using `static_cast` or a better choice in C++23 is to use `std::to_underlying()` defined in the `<utility>` header file, which converts an enumerator to a value of the underlying type of the enumeration:
```cpp
#include <iostream>
#include <utility> // for std::to_underlying() (C++23)

int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color color { Color::blue };

    std::cout << color << '\n'; // won't work, because there's no implicit conversion to int
    std::cout << static_cast<int>(color) << '\n';   // explicit conversion to int, will print 1
    std::cout << std::to_underlying(color) << '\n'; // convert to underlying type, will print 1 (C++23)

    return 0;
}
```

Or you can `static_cast` an integer to a scoped enumerator:
```cpp
#include <iostream>

int main()
{
    enum class Pet
    {
        cat, // assigned 0
        dog,
        pig,
        whale, // assigned 3
    };

    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input{};
    std::cin >> input; // input an integer

    Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet

    return 0;
}
```

As of C++17, you can list initialize a scoped enumeration using an integral value without the static_cast (and unlike an unscoped enumeration, you don't need to specify a base):
```cpp
// using enum class Pet from prior example
Pet pet { 1 }; // okay
```

- Favor scoped enumerations over unscoped enumerations unless there's a compelling reason to do otherwise.

## `using enum` statements C++20

Introduced in C++20, a `using enum` statement imports all of the enumerators from an enum into the current scope. When used with an enum class type, this allows us to access the enum class enumerators without having to prefix each with the name of the enum class:
```cpp
#include <iostream>
#include <string_view>

enum class Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColor(Color color)
{
    using enum Color; // bring all Color enumerators into current scope (C++20)
    // We can now access the enumerators of Color without using a Color:: prefix

    switch (color)
    {
    case black: return "black"; // note: black instead of Color::black
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    Color shirt{ Color::blue };

    std::cout << "Your shirt is " << getColor(shirt) << '\n';

    return 0;
}
```

Normally we would access the enumerators using a fully qualified name (e.g. `Color::blue`). However, within funciton `getColor()`, we've added a using statement which allows access to those enumerators without the `Color::` prefix.
