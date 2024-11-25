A **default constructor** is a constructor that accepts no arguments and is typically defined with no parameters:
```cpp
#include <iostream>

class Foo
{
public:
    Foo() // default constructor
    {
        std::cout << "Foo default constructed\n";
    }
};

int main()
{
    Foo foo{}; // No initialization values, calls Foo's default constructor

    return 0;
}
```

```
Foo default constructed
```

## Value initialization vs default initialization for class types

If a class type has a default constructor, then value initialization and default initialization will call the default constructor:
```cpp
Foo foo{}; // value initialization, calls Foo() default constructor
Foo foo2;  // default initialization, calls Foo() default constructor
```

- However, prefer value initialization over default initialization for all class types.

## Constructors with default arguments

We just keep building up lol

As with all functions, the rightmost parameters of constructors can have default arguments:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x { };
    int m_y { };

public:
    Foo(int x=0, int y=0) // has default arguments
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // calls Foo(int, int) constructor using default arguments
    Foo foo2{6, 7}; // calls Foo(int, int) constructor

    return 0;
}
```

```
Foo(0, 0) constructed
Foo(6, 7) constructed
```

If all parameters in a constructor have default arguments, the constructor is a default constructor because it can be called with no arguments.

## Overloading constructors

Because constructors are functions, they can be overloaded:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x, int y) // non-default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // Calls Foo() constructor
    Foo foo2{6, 7}; // Calls Foo(int, int) constructor

    return 0;
}
```

You can't have 2 default constructors because then the compiler won't know which one to use and a compiler error will result.

## An implicit default constructor

If a non-aggregate class type object has no user-declared constructor, the compiler will generate a public default constructor called an **implicit default constructor**:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

    // Note: no constructors declared
};

int main()
{
    Foo foo{};

    return 0;
}
```

The implicit default constructor will be used to instantiate `foo{}` and is equivalent to a constructor that has no parameters, no member initializer list, and no statements in the body of the constructor. The compiler generates something like this:
```cpp
public:
    Foo() // implicitly generated default constructor
    {
    }
```

## Using `= default` to generate an explicit default constructor

In cases where we would write a default constructor that is equivalent to the implicitly generated default constructor, we can instead use an **explicitly defaulted default constructor** by using the `= default` syntax:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() = default; // generates an explicitly defaulted default constructor

    Foo(int x, int y)
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // calls Foo() default constructor

    return 0;
}
```

Here an implicit default constructor would not be generated since we have a user-declared constructor `Foo(int, int)`. Therefore, we make a default constructor using the `= default` syntax.

- Prefer an explicitly defaulted default constructor (`= default`) over a default constructor with an empty body.

## Explicitly defaulted default constructor vs empty user-defined constructor

When value initializing a class, if the class has a user-defined default constructor, the object will be default initialized. However, if the class has a default constructor that is not user-defined (either implicitly-defined or defaulted via `= default`), the object will be zero initialized before being default initialized:
```cpp
#include <iostream>

class User
{
private:
    int m_a; // note: no default initialization value
    int m_b {};

public:
    User() {} // user-defined empty constructor

    int a() const { return m_a; }
    int b() const { return m_b; }
};

class Default
{
private:
    int m_a; // note: no default initialization value
    int m_b {};

public:
    Default() = default; // explicitly defaulted default constructor

    int a() const { return m_a; }
    int b() const { return m_b; }
};

class Implicit
{
private:
    int m_a; // note: no default initialization value
    int m_b {};

public:
    // implicit default constructor

    int a() const { return m_a; }
    int b() const { return m_b; }
};

int main()
{
    User user{}; // default initialized
    std::cout << user.a() << ' ' << user.b() << '\n';

    Default def{}; // zero initialized, then default initialized
    std::cout << def.a() << ' ' << def.b() << '\n';

    Implicit imp{}; // zero initialized, then default initialized
    std::cout << imp.a() << ' ' << imp.b() << '\n';

    return 0;
}
```

Note that `user.a` was not zero initialized before being default initialized, and thus was left uninitialized:
```
782510864 0
0 0
0 0
```

