When a class type is an aggregate, we can use aggregate initialization to initialize the class type directly:
```cpp
struct Foo // Foo is an aggregate
{
    int x {};
    int y {};
};

int main()
{
    Foo foo { 6, 7 }; // uses aggregate initialization

    return 0;
}
```

However, as soon as we make any member variables private to hide our data our class type is no longer aggregate and we can't use aggregate initialization:
```cpp
class Foo // Foo is not an aggregate (has private members)
{
    int m_x {};
    int m_y {};
};

int main()
{
    Foo foo { 6, 7 }; // compile error: can not use aggregate initialization

    return 0;
}
```

Consider  the following:
1. Aggregate initialization requires knowing about the implementation of the class, which we're intentionally trying to avoid when hiding our data members.
2. If our class had some kind of invariant, we'd be relying on the user to initialize the class in a way that preserves the invariant.

## Constructors

A **constructor** is a special member function that is automatically called after a non-aggregate class type object is created.

When a non-aggregate class type object is defined, the compiler looks to see if it can find an accessible constructor that is a match for the initialization values provided by the caller (if any).
- If an accessible matching constructor is found, memory for the object is allocated, and then the constructor function is called.
- If no accessible matching constructor can be found, a compilation error will be generated.

Constructors don't create objects. The compiler sets up the memory allocation for the object prior to the constructor call. The constructor is then called on the uninitialized object.

Beyond how an object is created, constructors generally perform 2 functions:
1. Typically initialization of any member variables
2. May perform other setup functions like error checking the initialization values, opening a file/database, etc.

- Note that aggregates are not allowed to have constructors and if you add one to an aggregate, it ceases to be an aggregate.

## Naming constructors

- Constructors must have the same name as the class (with the same capitalization).
- Constructors have no return type (not even `void`).

## A basic constructor example

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) // here's our constructor function that takes two initializers
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();

    return 0;
}
```

This program prints:
```
Foo(6, 7) constructed
Foo(0, 0)
```

You may notice that when we call the `print` member function, that the members `m_x` and `m_y` are both 0. This is because although `Foo(int, int)` constructor function was called, it didn't actually initialize the members.

## Constructor implicit conversion of arguments

Similar to the compiler performing implicit type conversion of our arguments in a function call, constructors will also match any call whose arguments are implicitly convertible.

```cpp
class Foo
{
public:
    Foo(int x, int y)
    {
    }
};

int main()
{
    Foo foo{ 'a', true }; // will match Foo(int, int) constructor

    return 0;
}
```

## Constructors should not be const

A constructor needs to be able to initialize the object being constructed -- therefore, a constructor must not be const:
```cpp
#include <iostream>

class Something
{
private:
    int m_x{};

public:
    Something() // constructors must be non-const
    {
        m_x = 5; // okay to modify members in non-const constructor
    }

    int getX() const { return m_x; } // const
};

int main()
{
    const Something s{}; // const object, implicitly invokes (non-const) constructor

    std::cout << s.getX(); // prints 5

    return 0;
}
```

Normally a non-const member function can’t be invoked on a const object. However, because the constructor is invoked implicitly, a non-const constructor can be invoked on a const object.

## Constructors vs setters

- Constructors are designed to initialize an entire object at the point of instantiation.
- Setters are designed to assign a value to a single member of an existing object.
