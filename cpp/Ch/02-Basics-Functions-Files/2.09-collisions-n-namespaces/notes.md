## Naming collisions

Names/identifiers are required to be non-ambiguous in C++. If 2 identical identifiers are introduced into the same program in a way that the compiler/linker can't tell them apart, then an error known as a **naming collision** (or **naming conflict**) will occur.

An example:
```cpp
//a.cpp
#include <iostream>

void myFcn(int x)
{
    std::cout << x;
}
```
```cpp
//main.cpp
#include <iostream>

void myFcn(int x)
{
    std::cout << 2 * x;
}

int main()
{
    return 0;
}
```

When the compiler compiles these programs, it will compile a.cpp and main.cpp independently and each will compile fine without a hitch.

However, the linker will link all definitions in a.cpp and main.cpp together, meaning the duplicate functions of `myFcn()` will cause the linker to abort with an error.

## Namespaces
- **scope regions:** an area of source code where all declared identifiers are considered distinct from names declared in other scopes.
- **namespace:** provides another scope region called **namespace scope** that allows you to declare names inside of it for the purpose of disambiguation. A name declared in a scope region (such as a namespace) won't be mistaken for an identical name declared in another scope.

In C++, any name not defined in a class, function, or namespace is a part of the implicitly-defined namespace called the **global namespace** (also called the **global scope**).

The reason the `myFcn()` function has a linker issue, is because in both instances, it is in the global namespace.

## The std namespace
When we've been using `std::cout` and `std::cin`, we are actually accessing the standard namespace (`std::`) and using the identifiers `cout` and `cin` defined in the `std::` namespace.

Here the `::` symbol is an operator called the **scope resolution operator**.

It's best practice to use explicit namespace prefixes when you can to access identifiers defined in a namespace to avoid any misunderstandings due to ambiguity.
