Class type objects (struct, classes, unions) can be made const by using the `const` keyword and must be initialized at the time of creation:
```cpp
struct Date
{
    int year {};
    int month {};
    int day {};
};

int main()
{
    const Date today { 2020, 10, 14 }; // const class type object

    return 0;
}
```

- You can't modify the data members of const objects (duh)

The following is disallowed:
```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay()
    {
        ++day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.day += 1;        // compile error: can't modify member of const object
    today.incrementDay();  // compile error: can't call member function that modifies member of const object

    return 0;
}
```

## Const objects may not call non-const member functions

This is disallowed:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // compile error: can't call non-const member function

    return 0;
}
```

This is because the `print()` member function itself is not declared as const.

## Const member functions

A **const member function** is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object). Let's make `print()` a const member function:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now a const member function
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // ok: const object can call const member function

    return 0;
}
```

Here we just appended the `const` keyword to the function prototype (after the parameter list, but before the function body).

- A const member function can't change a member variable:
```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay() const // made const
    {
        ++day; // compile error: const function can't modify member
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.incrementDay();

    return 0;
}
```

## Const member functions may be called on non-const objects

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // non-const

    today.print();  // ok: can call const member function on non-const object

    return 0;
}
```

- A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on both const and non-const objects.

## Const objects via pass by const reference

Can you figure out what's wrong with the following code?
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // non-const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```

The answer is t hat inside the `doSomething()` function, `date` is treated as a const object (because it was passed by const reference). And with that const data, we're calling non-const member function `print()`.

The fix is to make `print()` const:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```

## Member function const and non-const overloading

Although it isn't done very often, it's possible to overload a member function to have a const and non-const version of the same function:
```cpp
#include <iostream>

struct Something
{
    void print()
    {
        std::cout << "non-const\n";
    }

    void print() const
    {
        std::cout << "const\n";
    }
};

int main()
{
    Something s1{};
    s1.print(); // calls print()

    const Something s2{};
    s2.print(); // calls print() const

    return 0;
}
```

This prints:
```
non-const
const
```

Overloading a function with a const and non-const version is typically done when the return value needs to differ in constness. This is pretty rare.
