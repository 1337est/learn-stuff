Consider the following program:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here?

    f.print();
    fCopy.print();

    return 0;
}
```

```
Fraction(5, 3)
Fraction(5, 3)
```

- The initialization of `f` is just standard brace initialization that calls the `Fraction(int, int)` constructor.
- The initialization of `fCopy` is calling the copy constructor.

## The copy constructor
A **copy constructor** is a constructor that is used to initialize an object with an existing object of the same type. After the copy constructor executes, the newly created object should be a copy of the object passed in as the initializer.

## An implicit copy constructor

If you don't provide a copy constructor for your classes, C++ will create a public **implicit copy constructor** for you. The above code has an implicit copy constructor to initialize `fCopy` with `f`.

By default, the implicit copy constructor will do memberwise initialization, which means each member will be initialized using the corresponding member of the class passed in as the initializer. In the above code, `fCopy.m_numerator` is initialized with `f.m_numerator`, and same for the denominator.

This is why `f` and `fCopy` have the same values. `fCopy` is a copy of `f`. Therefore, calling `print()` has the same result.

## Explicit copy constructor

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

    f.print();
    fCopy.print();

    return 0;
}
```

```
Copy constructor called
Fraction(5, 3)
Fraction(5, 3)
```

It makes sense why the text "Copy constructor called" is before anything else since we call the copy constructor before we `print()` anything.

- Copy constructors should have no side effects beyond copying

- Prefer the implicit copy constructor, unless you have a specific reason to create your own.

- If you write your own copy constructor, the parameter should be a const lvalue reference

## Pass by value (and return by value) and the copy constructor

When an object is passed by value, the argument is copied into the parameter. When the argument and parameter are the same class type, the copy is made by implicitly invoking the copy constructor. Similarly, when an object is returned back to the caller by value, the copy constructor is implicitly invoked to make the copy:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

void printFraction(Fraction f) // f is pass by value
{
    f.print();
}

Fraction generateFraction(int n, int d)
{
    Fraction f{ n, d };
    return f;
}

int main()
{
    Fraction f{ 5, 3 };

    printFraction(f); // f is copied into the function parameter using copy constructor

    Fraction f2{ generateFraction(1, 2) }; // Fraction is returned using copy constructor

    printFraction(f2); // f is copied into the function parameter using copy constructor

    return 0;
}
```

For the output we get:
```
Copy constructor called
Fraction(5, 3)
Copy constructor called
Copy constructor called
Fraction(1, 2)
```

- Our call to `printFraction(f)` uses the copy constructor.
- Our `generateFraction(1, 2)` return a `Fraction` type `f` and therefore calls the copy constructor.
- Our call to `printFraction(f2)` uses the copy constructor

## Using `= default` to generate a default copy constructor

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Explicitly request default copy constructor
    Fraction(const Fraction& fraction) = default;

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f };

    f.print();
    fCopy.print();

    return 0;
}
```

## Using `= delete` to prevent copies

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Delete the copy constructor so no copies can be made
    Fraction(const Fraction& fraction) = delete;

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f }; // compile error: copy constructor has been deleted

    return 0;
}
```


