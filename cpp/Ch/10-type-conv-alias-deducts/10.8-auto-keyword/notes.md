There is subtle redundancy lurking in this simple variable definition:
```cpp
double d{ 5.0 };
```

C++ requires us to provide an explicit type for all objects, therefore we specify that variable `d` is of type double.

The literal value `5.0` used to initialize `d` also has type double (implicitly determined via the format of the literal)

In cases where we want a variable and its initializer to have the same type, we're effectively providing the same type information twice.

## Type deduction for initialized variables

- **Type deduction** (also called **type inference**) is a feature that allows the compiler to deduce the type of an object from the object's initializer. To use type deduction with variables, the `auto` keyword is used in place of the variable's type:

```cpp
int main()
{
    auto d{ 5.0 }; // 5.0 is a double literal, so d will be type double
    auto i{ 1 + 2 }; // 1 + 2 evaluates to an int, so i will be type int
    auto x { i }; // i is an int, so x will be type int too

    return 0;
}
```

This is useful in function calls, where we can use type deduction when our initializer is a non-void function call:

```cpp
int add(int x, int y)
{
    return x + y;
}

int main()
{
    auto sum { add(5, 6) }; // add() returns int, so sum's type is deduced to int

    return 0;
}
```

More examples:

```cpp
int main()
{
    auto a { 1.23f }; // f suffix causes a to be deduced to float
    auto b { 5u };    // u suffix causes b to be deduced to unsigned int

    return 0;
}
```

Type deduction will not work for objects that do not have initializers or have empty initializers. It also won't work when the initializer has type `void` (or other incomplete types), which makes sense.

The following is invalid:
```cpp
#include <iostream>

void foo()
{
}

int main()
{
    auto x;          // The compiler is unable to deduce the type of x
    auto y{ };       // The compiler is unable to deduce the type of y
    auto z{ foo() }; // z can't have type void, so this is invalid

    return 0;
}
```

In these simple examples, using type deduction only saves a few keystrokes/memory cells. In future lessons, we'll see lengthy examples where using `auto` can save a lot of typing (and typos (and thinking!)).

## Type deduction drops const / constexpr qualifiers

In most cases, type deduction will drop the `const` or `constexpr` qualifiers from deduced types:

```cpp
int main()
{
    const int x { 5 }; // x has type const int
    auto y { x };      // y will be type int (const is dropped)

    return 0;
}
```

If we desire a deduced type to be const or constexpr, we must supply the const / constexpr ourselves:

```cpp
int main()
{
    const int x { 5 };  // x has type const int (compile-time const)
    auto y { x };       // y will be type int (const is dropped)

    constexpr auto z { x }; // z will be type constexpr int (constexpr is reapplied)

    return 0;
}
```

## Type deduction for string literals

For historical reasons string literals in C++ have a strange type. Therefore, the following probably won't work as expected:

```cpp
auto s { "Hello, world" }; // s will be type const char*, not std::string
```


If you want the type deduced from a string literal to be `std::string` or `std::string_view`, you'll need to use the `s` or `sv` suffixes.

```cpp
#include <string>
#include <string_view>

int main()
{
    using namespace std::literals; // easiest way to access the s and sv suffixes

    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

    return 0;
}
```

## Type deduction benefits and downsides
Upsides of type deduction
1. Increases readability for 2 or more variables on sequential lines

```cpp
// harder to read
int a { 5 };
double b { 6.7 };

// easier to read
auto c { 5 };
auto d { 6.7 };
```

2. Type deduction only works on variables that have initializers
```cpp
int x; // oops, we forgot to initialize x, but the compiler may not complain
auto y; // the compiler will error out because it can't deduce a type for y
```

3. Guaranteed that there will be no unintended performance-impacting conversions:
```cpp
std::string_view getString();   // some function that returns a std::string_view

std::string s1 { getString() }; // bad: expensive conversion from std::string_view to std::string (assuming you didn't want this)
auto s2 { getString() };        // good: no conversion required
```

Downsides of type deduction
1. Type deduction obscures an object's type information in the code
```cpp
#include <iostream>

int main()
{
     auto x { 3 };
     auto y { 2 };

     std::cout << x / y << '\n'; // oops, we wanted floating point division here

     return 0;
}
```

2. If the type of an initializer changes, the type of a variable using type deduction will also change, perhaps unexpectedly.

```cpp
auto sum { add(5, 6) + gravity };
```

If the return type of `add` changes from int to double, or `gravity` changes from int to double, `sum` will also change from int to double.


