## Data members are not initialized by default

```cpp
#include <iostream>

struct Employee
{
    int id; // note: no initializer here
    int age;
    double wage;
};

int main()
{
    Employee joe; // note: no initializer here either
    std::cout << joe.id << '\n'; // undefined behavior

    return 0;
}
```

Because we have not provided any initializers, when `joe` is instantiated, `joe.id`, `joe.age`, and `joe.wage` will all be uninitialized. We will then get undefined behavior when we try to print the value of `joe.id`.

Before learning how to initialize a struct, let's learn about aggregate.

## What is an aggregate?

In general programming, an **aggregate data type** (also called an **aggregate**) is any type that can contain multiple data members. Some types of aggregates allow members to have different types (e.g. structs), while others require that all members must be of a single type (e.g. arrays).

In C++, the definition of an aggregate is narrower and quite a bit more complicated (of course it is).

The key thing to understand at this point is that structs with only data members are aggregates.

## Aggregate initialization of a struct

Normal variables can hold a single value:
```cpp
int x { 5 };
```

However, structs have multiple members:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```

So when we define an object with a struct type, we need some way to initialize multiple members at initialization time:
```cpp
Employee joe; // how do we initialize joe.id, joe.age, and joe.wage?
```

Aggregates use a form of initialization called **aggregate initialization**, which allows us to directly initialize the members of aggregates. To do this, we provide an **initializer list** as an initializer, which is just a braced list of comma-separated values.

There are 2 primary forms of aggregate initialization:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)

    return 0;
}
```

Each of these initialization forms does a **memberwise initialization**, which means each member in the struct is initialized in the order of declaration (e.g. `Employee joe { 2, 28, 45000.0 };` initializes `joe.id` with `2`, `joe.age` with `28`, and `joe.wage` with `45000.0`).

## Missing initializers in an initializer list

Missing initialization values (fewer than the number of members) will initialize the remaining members with an empty initializer list:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 2, 28 }; // joe.wage will be value-initialized to 0.0

    return 0;
}
```

Since the `wage` member wasn't specified for `joe` during initialization, `joe.wage` will be value-initialized to `0.0`.

This means we can generally use an empty initialization list to value-initialize all members of the struct:
```cpp
Employee joe {}; // value-initialize all members
```

## Const structs

Variables of a struct type can be const (or constexpr), and just like all const variables, they must be initialized:
```cpp
struct Rectangle
{
    double length {};
    double width {};
};

int main()
{
    const Rectangle unit { 1.0, 1.0 };
    const Rectangle zero { }; // value-initialize all members

    return 0;
}
```

## Designated initializers (C++20)

When initializing a struct from a list of values, the initializers are applied to the members in order of declaration:
```cpp
struct Foo
{
    int a {};
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // f.a = 1, f.c = 3

    return 0;
}
```
However, consider you update this struct definition to add a new member:
```cpp
struct Foo
{
    int a {};
    int b {}; // just added
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // now, f.a = 1, f.b = 3, f.c = 0

    return 0;
}
```

Now all of your initialization values have shifted, and worse, the compiler may not catch this as an error (after all, the syntax is still valid).

C++20 adds a new way to initialize struct members called **designated initializers** that allows you to explicitly define which initialization values map to which members. The members can be initialized using list or copy initialization and must be initialized in the same order in which they are declared in the struct, otherwise a warning or error will result. Members not designated an initializer will be value initialized:
```cpp
struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    return 0;
}
```

However, when adding a new member to an aggregate, it's safest just to add it to the bottom of the definition list so the initializers for other members don't shift.

## Assignment with an initializer list

As shown before we can assign values to members of structs individually:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };

    joe.age  = 33;      // Joe had a birthday
    joe.wage = 66000.0; // and got a raise

    return 0;
}
```

However, what if we wanted to update many members? Well, you can also assign values to structs using an initializer list (which does memberwise assignment):
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { joe.id, 33, 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```

Note here that because we didn't want to change `joe.id`, we simply passed in the variable value `joe.id`, which in this context does memberwise assignment to assign `joe.id` to `joe.id`. This is a bit ugly though...

## Assignment with designated initializers (C++20)

Same concept as stated with "designated initializers" (so much vocabulary):
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```

It's important to note that any members that weren't designated would be assigned the value used for value initialization. If we didn't specify a designated initializer for `joe.id`, then it would have been assigned the value `0`.

