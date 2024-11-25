In C++, structs (and classes) can have members that are other program-defined types. There are 2 ways to do this.

1. We can define one program-defined type (in global) and then use it as a member of another program-defined type:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

struct Company
{
    int numberOfEmployees {};
    Employee CEO {}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```

2. Types can be nested inside other types:
```cpp
#include <iostream>

struct Company
{
    struct Employee // accessed via Company::Employee
    {
        int id{};
        int age{};
        double wage{};
    };

    int numberOfEmployees{};
    Employee CEO{}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```

This is more often done with classes, so we'll talk more about this in a future lesson (15.3).

## Structs that are owners should have data members that are owners

There's owners and there's viewers. Owners manage their own data, and control when it is destroyed. Viewers view someone else's data, and do not control when it is altered or destroyed.

In most cases, we want our structs (and classes) to be owners of the data they contain. This provides benefits:
- The data members will be valid for as long as the struct (or class) is.
- The value of those data members won't change unexpectedly.

The easiest way to make a struct (or class) an owner is to give each data member a type that is an owner (e.g. NOT a viewer, pointer, or reference). If a struct or class has data members that are all owners, then the struct or class itself is automatically an owner.

If a struct (or class) has a data member that is a viewer, it is possible that the object being viewed by that member will be destroyed before the data member that is viewing it. If this happens, the struct will be left with a dangling member, and accessing that member will lead to undefined behavior.

This is why string data members are almost always of type `std::string` (owner) instead of `std::string_view` (viewer):
```cpp
#include <iostream>
#include <string>
#include <string_view>

struct Owner
{
    std::string name{}; // std::string is an owner
};

struct Viewer
{
    std::string_view name {}; // std::string_view is a viewer
};

// getName() returns the user-entered string as a temporary std::string
// This temporary std::string will be destroyed at the end of the full expression
// containing the function call.
std::string getName()
{
    std::cout << "Enter a name: ";
    std::string name{};
    std::cin >> name;
    return name;
}

int main()
{
    Owner o { getName() };  // The return value of getName() is destroyed just after initialization
    std::cout << "The owners name is " << o.name << '\n';  // ok

    Viewer v { getName() }; // The return value of getName() is destroyed just after initialization
    std::cout << "The viewers name is " << v.name << '\n'; // undefined behavior

    return 0;
}
```

The `getName()` function returns the name the user entered as a temporary `std::string`. This temporary return value is destroyed at the end of the full expression in which the function is called.

In the case of `o`, this `std::string` temporary is used to initialize `o.name`. Since `o.name` is a `std::string`, `o.name` makes a copy of the temporary `std::string`. This means the temporary dies, but the `o.name` isn't affected since it's a copy.

In the case of `v`, this `std::string` temporary is used to initialize `v.name`. Since `v.name` is a `std::string_view`, `v.name` is just a view of the temporary (not a copy). This means the temporary dies, leaving `v.name` dangling. We get an undefined behavior here.

## Struct size and data structure alignment

Typically, the size of a struct is the sum of the size of all its members, but not always:
```cpp
#include <iostream>

struct Foo
{
    short a {};
    int b {};
    double c {};
};

int main()
{
    std::cout << "The size of short is " << sizeof(short) << " bytes\n";
    std::cout << "The size of int is " << sizeof(int) << " bytes\n";
    std::cout << "The size of double is " << sizeof(double) << " bytes\n";

    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n";

    return 0;
}
```

```
The size of short is 2 bytes
The size of int is 4 bytes
The size of double is 8 bytes
The size of Foo is 16 bytes
```

We can simply say that the size of a struct will be at LEAST as large as the size of all the variables it contains. For performance reasons, the compiler sometimes adds gaps into structures (called **padding**).

This can have a significant impact on the size of a struct:
```cpp
#include <iostream>

struct Foo1
{
    short a{}; // will have 2 bytes of padding after a
    int b{};
    short c{}; // will have 2 bytes of padding after c
};

struct Foo2
{
    int b{};
    short a{};
    short c{};
};

int main()
{
    std::cout << sizeof(Foo1) << '\n'; // prints 12
    std::cout << sizeof(Foo2) << '\n'; // prints 8

    return 0;
}
```

```
12
8
```

Note that `Foo1` and `Foo2` have the same members, the only difference being the declaration order. Yet `Foo1` is 50% larger due to the added padding.

- You can minimize padding by defining your members in decreasing order of size. The C++ compiler isn't allowed to reorder members, so this has to be done manually.


