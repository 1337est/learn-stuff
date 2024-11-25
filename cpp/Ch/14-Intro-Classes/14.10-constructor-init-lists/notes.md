## Member initialization via a member initialization list

To have a constructor initialize members, we do so using a **member initializer list**
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
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
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```

The member initializer list is defined after the constructor parameters and begins with a colon (:), and then lists each member to initialize along with the initialization value for that variable, separated by a comma. You must use a direct form of initialization (prefer curly braces vs parenthesis) -- using copy initialization does not work here. Also note that there is no semicolon after the member initializer list is defined.

This program prints:
```
Foo(6, 7) constructed
Foo(6, 7)
```

When `foo` is instantiated, the members in the initialization list are initialized with the specified initialization values. In this case, `m_x` gets the value of `x`, and `m_y` gets the value of `y`. Additionally, when the `print()` member function is called, you can see that the member variables still have values `6` and `7`.

## Member initializer list formatting

C++ provides a lot of freedom to format your member initializer lists as you prefer but here are 3 common ways (and valid):
```cpp
Foo(int x, int y) : m_x { x }, m_y { y }
{
}
```
```cpp
Foo(int x, int y) :
    m_x { x },
    m_y { y }
{
}
```
```cpp
Foo(int x, int y)
    : m_x { x }
    , m_y { y }
{
}
```

I like the 3rd way because it helps to see where the initializer list start, and helps to keep everything in line

## Member initialization order

The C++ standard says that the members in a member initializer list are always initialized in the order in which they are defined inside the class (not in the order they are defined in the member initializer list). Because vocabulary is hard, this is what we mean:
```cpp
#include <algorithm> // for std::max
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y{ std::max(x, y) }, m_x{ m_y } // issue on this line
    {
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```

Because `m_x` is defined first in the class, `m_x` gets initialized first and `m_x` gets initialized to the value of `m_y`, which hasn't been initialized (but has been declared). This leads to undefined behavior.

This printed:
```
Foo(-858993460, 7)
```

- Member variables in a member initializer list should be listed in the order that they are defined in the class.

## Member initializer list vs default member initializers

Members can be initialized in a few different ways:
- If a member is listed in the member initializer list, this value is used
- Otherwise, if a member has a default member initializer, this value is used
- Otherwise, a member is default initialized

```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};    // default member initializer (will be ignored)
    int m_y{ 2 }; // default member initializer (will be used)
    int m_z;      // no initializer

public:
    Foo(int x)
        : m_x{ x } // member initializer list
    {
        std::cout << "Foo constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};

int main()
{
    Foo foo{ 6 };
    foo.print();

    return 0;
}
```

```
Foo constructed
Foo(6, 2, -858993460)
```

This should be pretty self explanatory.

## Constructor function bodies

The bodies of constructors functions are most often left empty. This is because we primarily use constructor for initialization, which is done via the member initializer list. If that is all we need to do, then we don’t need any statements in the body of the constructor.

However, because the statements in the body of the constructor execute after the member initializer list has executed, we can add statements to do any other setup tasks required.

New programmers often try and do this:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
    {
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = y; // incorrect: this is an assignment, not an initialization
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```

Although this works, it isn't preferred and you should use the member initializer list to initialize your members over assigning values in the body of your constructors.


