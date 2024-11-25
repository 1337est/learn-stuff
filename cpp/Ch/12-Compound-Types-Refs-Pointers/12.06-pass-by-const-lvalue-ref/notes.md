## Pass by const lvalue reference

Unlike a reference to non-const (which can only bind to modifiable lvalues), a reference to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues.
```cpp
#include <iostream>

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printRef(x);   // ok: x is a modifiable lvalue, y binds to x

    const int z { 5 };
    printRef(z);   // ok: z is a non-modifiable lvalue, y binds to z

    printRef(5);   // ok: 5 is rvalue literal, y binds to temporary int object

    return 0;
}
```

Passing by const reference offers the same primary benefit as pass by reference (avoiding making a copy of the argument), while also gauranteeing that the function can not change the value being referenced.

In most cases, we don't want our functions modifying the value of arguments. Therefore, favor passing by const reference over passing by non-const reference unless you have a specific reason to do otherwise.

## Passing values of a different type to a const lvalue reference parameter

Since a const lvalue reference can bind to a value of a different type, as long as that value is convertible to the type of the reference, we can now pass a value as an argument to either a value parameter or const reference parameter in exactly the same way:
```cpp
#include <iostream>

void printVal(double d)
{
    std::cout << d << '\n';
}

void printRef(const double& d)
{
    std::cout << d << '\n';
}

int main()
{
    printVal(5); // 5 converted to temporary double, copied to parameter d
    printRef(5); // 5 converted to temporary double, bound to parameter d

    return 0;
}
```

## Mixing pass by value and pass by reference

```cpp
#include <string>

void foo(int a, int& b, const std::string& c)
{
}

int main()
{
    int x { 5 };
    const std::string s { "Hello, world!" };

    foo(5, x, s);

    return 0;
}
```

This is self explanatory

## When to pass by (const) reference

Because class types can be expensive to copy, class types are usually passed by const reference instead of by value to avoid making an expensive copy of the argument.

- Best practice is to pass fundamental types by value, and class (or struct) types by const reference.
- Common types to pass by value:
    - fundamental types
    - enumerated types
    - `std::string_view`
- Common types to pass by (const) reference:
    - class types
    - struct types
    - `std::string`
    - `std::array`
    - `std::vector`

## For function parameters, prefer `std::string_view` over `const std::string&` in most cases

- Prefer `std::string_view` since it can handle a wider range of argument types efficiently:
```cpp
void doSomething(const std::string&);
void doSomething(std::string_view);     // prefer in most cases
```


