## Member selection for structs and references to structs

We've already shown how you can use the member selection operator (.) to select a member from a struct object:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 34, 65000.0 };

    // Use member selection operator (.) to select a member from struct object
    ++joe.age; // Joe had a birthday
    joe.wage = 68000.0; // Joe got a promotion

    return 0;
}
```

Since references to an object act just like the object itself, we can also use the member selection operator (.) to select a member from a reference to a struct:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

void printEmployee(const Employee& e)
{
    // Use member selection operator (.) to select member from reference to struct
    std::cout << "Id: " << e.id << '\n';
    std::cout << "Age: " << e.age << '\n';
    std::cout << "Wage: " << e.wage << '\n';
}

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    printEmployee(joe);

    return 0;
}
```

## Member selection for pointers to structs

However, the member selection operator (.) can't be used directly on a pointer to a struct:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers

    return 0;
}
```

With normal variables or references, we can access objects directly. However, because pointers hold addresses, we first need to dereference the pointer to get the object before we can do anything with it. So one way to access a member from a pointer to a struct is as follows:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << (*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection

    return 0;
}
```

However, this is ugly because we need to parenthesize the dereference operation so it will take precedence over t he member selection operation.

To make for cleaner syntax, C++ offers a **member selection from pointer operator (->)** (also sometimes called the **arrow operator**) that can be used to select members from a pointer to an object:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr->id << '\n'; // Better: use -> to select member from pointer to object

    return 0;
}
```

This member selection from pointer operator (->) works identically to the member selection operator (.) but does an implicit dereference of the pointer object before selecting the member.
- You basically use `operator->` when using pointers instead of `operator.`.
- When using a pointer to access a member, use the member selection from pointer `operator->` instead of the member selection `operator.`

## Chaining `operator->`

If the member accessed via `operator->` is a pointer to a class type, `operator->` can be applied again in the same expression to access the member of that class type:
```cpp
#include <iostream>

struct Point
{
    double x {};
    double y {};
};

struct Triangle
{
    Point* a {}; // Declaring pointer a of type Point*
    Point* b {}; // Declaring pointer b of type Point*
    Point* c {}; // Declaring pointer c of type Point*
};

int main()
{
    // Defining our points for our triangle
    Point a {1,2};
    Point b {3,7};
    Point c {10,2};

    Triangle tr { &a, &b, &c }; // tr var with dereferenced a, b, and c
    Triangle* ptr { &tr }; // ptr var with dereferenced tr

    // access via operator.
    std::cout << (*(*ptr).c).y << '\n'; // ugly
    
    // access via operator->
    std::cout << ptr -> c -> y << '\n'; // much nicer

    return 0;
}
```

## Mixing pointers and non-pointers to members

This is for when you have a mixture of pointer and normal member variables:

```cpp
#include <iostream>
#include <string>

struct Paw
{
    int claws{};
};

struct Animal
{
    std::string name{};
    Paw paw{};
};

int main()
{
    Animal puma{ "Puma", { 5 } };

    Animal* ptr{ &puma };

    // ptr is a pointer, use ->
    // paw is not a pointer, use .

    std::cout << (ptr->paw).claws << '\n';

    return 0;
}
```

