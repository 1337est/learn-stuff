All of the classes we've written so far have been simple enough where we implement the member functions directly inside the class itself:
```cpp
#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day)
        : m_year { year }
        , m_month { month }
        , m_day { day}
    {
    }

    void print() const { std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n"; };

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

int main()
{
    Date d { 2015, 10, 14 };
    d.print();

    return 0;
}
```

However, as classes get longer and bigger, we don't want to clutter up our class since that'll make it harder to manage in the long run.

Here is the same `Date` class as above but with the constructor and `print()` member functions defined outside the class, leaving only declarations inside the class:
```cpp
#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day); // constructor declaration

    void print() const; // print function declaration

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const  { return m_day; }
};

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};

int main()
{
    const Date d{ 2015, 10, 14 };
    d.print();

    return 0;
}
```

The only difference is how we're prefixing `Date::` so the compiler knows we're defining a member of that class type rather than a non-member.

## Putting class definition in a header file

Unlike functions, which only need a forward declaration to be used, the compiler typically needs to see the full definition of a class (or any program-defined type) in order for the type to be used. The compiler needs to know how the members are declared so that they are used properly and it needs to know how to allocate memory depending on how large the object is in order to instantiate them. So our header files usually contain the full definition of a class rather than just a forward declaration of the class.

Here's our Date class broken into a .cpp and .h file
```cpp
// Date.h includes our Class declarations
#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

#endif
```

```cpp
// Date.cpp includes our Date header and Class definitions
#include "Date.h"

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};
```

Now any other header or code file that wants to use `Date` can simply `#include "Date.h"`.


