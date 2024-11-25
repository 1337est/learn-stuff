You know about conversions right?
```cpp
#include <iostream>

void printDouble(double d) // has a double parameter
{
    std::cout << d;
}

int main()
{
    printDouble(5); // we're supplying an int argument

    return 0;
}
```

Here we have an int argument that will implicitly convert to a double since the function call's parameter is a double. That is, `5` will be converted to `5.0` and `d` will be copy initialized with this value.

## User-defined conversions

Consider this example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
public:
    Foo(int x)
        : m_x{ x }
    {
    }

    int getX() const { return m_x; }
};

void printFoo(Foo f) // has a Foo parameter
{
    std::cout << f.getX();
}

int main()
{
    printFoo(5); // we're supplying an int argument

    return 0;
}
```

Unlike the first example, the compiler will try to convert type `int` value `5` into a type `Foo` object. Since our type is program-defined, the C++ standard doesn't have a specific rule to tell the compiler how to do this.

Instead, the compiler will look to see if we have defined a **user-defined conversion** function that it can use to perform such a conversion.

## Converting constructors

Up to this point we've used constructors to explicitly construct objects with program-defined types:
```cpp
Foo x { 5 }; // Explicitly convert int value 5 to a Foo
```

This makes sense once stated aloud. Now in the context of a function call, we are trying to solve the same problem:
```cpp
printFoo(5); // Implicitly convert int value 5 into a Foo
```

Here we're providing an `int` value and want a `Foo` object returned. So in this case, when `printFoo(5)` is called, parameter `f` is copy initialized using the `Foo(int)` constructor with `5` as an argument!

- Prior to C++17, when `printFoo(5)` is called, `5` is implicitly converted to a temporary `Foo` using the `Foo(int)` constructor. This temporary `Foo` is then copy constructed into parameter `f`.
- In C++17 onward, the copy is mandatorily elided. Parameter `f` is copy initialized with value `5`, and no call to the copy constructor is required (and it will work even if the copy constructor is deleted).

A constructor that can be used to perform an implicit conversion is called a **converting constructor** and by default, all constructors are converting constructors.

## However, only one user-defined conversion may be applied

Consider the following:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};

public:
    Employee(std::string_view name)
        : m_name{ name }
    {
    }

    const std::string& getName() const { return m_name; }
};

void printEmployee(Employee e) // has an Employee parameter
{
    std::cout << e.getName();
}

int main()
{
    printEmployee("Joe"); // we're supplying an string literal argument

    return 0;
}
```

This version doesn't compile. In this version we have a C-style string `"Joe"` being converted to a `std::string_view` using a `std::string_view` converting constructor, and then our `std::string_view` has to be converted into an `Employee` using an `Employee(std::string_view)` converting constructor.

There are 2 ways to make this example work:
1. Use a `std::string_view` literal
```cpp
int main()
{
    using namespace std::literals;
    printEmployee( "Joe"sv); // now a std::string_view literal

    return 0;
}
```

This works because now a single user-defined conversion is now required (from `std::string_view` to `Employee`)

2. Explicitly construct an `Employee` rather than implicitly create one:
```cpp
int main()
{
    printEmployee(Employee{ "Joe" });

    return 0;
}
```

## When converting constructors go wrong

Consider this innocent and working program:
```cpp
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    Dollars(int d)
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5);

    return 0;
}
```

In life, things usually go the way you want right? Well, although the output is `$5`, and is probably the caller's intent, we might not have expected the compiler to silently and implicitly convert our `int` value to a `Dollars` object so that it could satisfy this function call. In a large and complex program, it's easy to be surprised by the compiler performing some implicit conversion hidden from you, resulting in unexpected behavior.

It would be better if our `print(Dollars)` function could only be called with a `Dollars` object.

## The explicit keyword

To address this issue, we can use the **explicit** keyword to tell the compiler that a constructor should not be used as a converting constructor. This has a single consequence that results in a cascading effect:
1. An explicit constructor cannot be used to do copy initialization or copy list initialization
    - Consequence of this is that an explicit constructor also cannot be used to do implicit conversions since this uses copy initialization or copy list initialization.

Let's update our example to use an explicit constructor:
```cpp
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    explicit Dollars(int d) // now explicit
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5); // compilation error because Dollars(int) is explicit

    return 0;
}
```

Because the compiler can no longer use `Dollars(int)` as a converting constructor, it cannot find a way to convert `5` to `Dollars` which produces a compiler error.

This leads to us needing to explicitly define the `Dollars` object ourselves:
```cpp
print(Dollars{5}); // ok: create Dollars and pass to print() (no conversion required)
```

Since we explicitly constructed a `Dollars` type, the argument type matches the parameter type, and no conversion is needed.

- Using explicit constructors also helps to document our intent when viewing our code

## Return by value and explicit constructors

When we return a value from a function `return abcdefg;`, if that value doesn't match the return type of the function `int alphabets()`, an implicit conversion will occur. Here's an example:
```cpp
#include <iostream>

class Foo
{
public:
    explicit Foo() // note: explicit (just for sake of example)
    {
    }

    explicit Foo(int x) // note: explicit
    {
    }
};

Foo getFoo()
{
    // explicit Foo() cases
    return Foo{ };   // ok
    return { };      // error: can't implicitly convert initializer list to Foo

    // explicit Foo(int) cases
    return 5;        // error: can't implicitly convert int to Foo
    return Foo{ 5 }; // ok
    return { 5 };    // error: can't implicitly convert initializer list to Foo
}

int main()
{
    return 0;
}
```

This just seems like common sense from what we've learned so far.

## Best practices for use of `explicit`

The following **should not** be made explicit:
- Copy (and move) constructor (as these do not perform conversions)

The following are **typically not** made explicit:
- Default constructors with no parameters as these are only used to convert `{}` to a default object, not something we typically need to restrict.
- Constructors that only accept multiple arguments (as these are typically not a candidate for conversions anyway.)

The following **should usually** be made explicit:
- Constructors that take a single argument

If the following all the following are true, you **should not** make a single argument constructor explicit:
- The constructed object is semantically equivalent to the argument value
- The conversion is performant


