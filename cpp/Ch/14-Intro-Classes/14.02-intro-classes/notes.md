Structs provide a convenient package for storing and moving related data values:
```cpp
#include <iostream>

struct Date
{
    int day{};
    int month{};
    int year{};
};

void printDate(const Date& date)
{
    std::cout << date.day << '/' << date.month << '/' << date.year; // assume DMY format
}

int main()
{
    Date date{ 4, 10, 21 }; // initialize using aggregate initialization
    printDate(date);        // can pass entire struct to function

    return 0;
}
```

```
4/10/21
```

As useful as structs are, structs have a number of deficiencies that can present challenges when trying to build large, complex programs.

## The class invariant problem

Previously we've defined an invariant as, "a condition that must be true while some component is executing".

In the context of class types (which includes structs, classes, and unions), a **class invariant** is a condition that must be true throughout the lifetime of an object in order for the object to remain in a valid state. An object that has a violated class invariant is said to be in an **invalid state**, and unexpected or undefined behavior may result from further use of that object.

For example:
```cpp
#include <iostream>

struct Fraction
{
    int numerator { 0 };
    int denominator { 1 }; // class invariant: should never be 0
};

void printFractionValue(const Fraction& f)
{
     std::cout << f.numerator / f.denominator << '\n';
}

int main()
{
    Fraction f { 5, 0 };   // create a Fraction with a zero denominator
    printFractionValue(f); // cause divide by zero error

    return 0;
}
```

## Introduction to classes

Just like structs, a **class** is a program-defined compound type that can have many member variables with different types.

- We cover the differences between structs and classes in 14.5
- We cover how classes solve the invariant problem in 14.8

## Defining a class

Because a class is a program-defined type, it must be defined before usage. Classes use the `class` keyword instead of `struct`:
```cpp
class Employee
{
    int m_id {};
    int m_age {};
    double m_wage {};
};
```

- We discuss why member variables of a class are often prefixed by "m_" in 14.5.

To demonstrate how similar classes and structs can be, the following program is equivalent to the one we presented at the top of the lesson, but `Date` is now a class instead of a struct:
```cpp
#include <iostream>

class Date       // we changed struct to class
{
public:          // and added this line, which is called an access specifier
    int m_day{}; // and added "m_" prefixes to each of the member names
    int m_month{};
    int m_year{};
};

void printDate(const Date& date)
{
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year;
}

int main()
{
    Date date{ 4, 10, 21 };
    printDate(date);

    return 0;
}
```

```
4/10/21
```

## Most of the C++ standard library is classes

You've already been using class objects. Both `std::string` and `std::string_view` are defined as classes. In fact, most of the non-aliased types in the standard library are defined as classes!

Classes are really the heart and soul of C++ -- they are so foundational that C++ was originally named "C with classes"! (SO PAY ATTENTION) Once you're familiar with classes, much of your time in C++ will be spent writing, testing, and using them.
