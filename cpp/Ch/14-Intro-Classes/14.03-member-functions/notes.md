## Member functions

In addition to having member variables, class types (including structs, classes, and unions) can also have their own functions! Functions belonging to a class type are called **member functions**.

A **non-member function** (occasionally called **free functions**) are normal functions.

## A member function example

Here is an example with the standard non-member function:
```cpp
#include <iostream>

struct Date
{
    // here are our member variables
    int year {};
    int month {};
    int day {};
};

void print(const Date& date)
{
    // member variables accessed using member selection operator (.)
    std::cout << date.year << '/' << date.month << '/' << date.day;
}

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    print(today);   // non-member function accessed using normal calling convention

    return 0;
}
```

Now here is what it looks like when we include `print()` as a member function:
```cpp
// Member function version
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // defines a member function named print
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    return 0;
}
```

Both these programs compile and produce the same result:
```
2020/10/16
```

There are 3 key differences between the non-member and member examples:
1. Where we declare (and define) the `print()` function
2. How we call the `print()` function
3. How we access members inside the `print()` function

## Member functions are declared inside the class type definition

- In the non-member example, `print()` is global and by default has external linkage (it can be called from other source files with the appropriate forward declaration)
- In the member example, `print()` is local to the `Date` struct and therefore tells the compiler that `print()` is a member function.
- Member functions defined inside the class type definition are implicitly inline, so they will not cause violations of the ODR if the class type definition is included into multiple code files.

## Calling member functions (and the implicit object)

- In the non-member example, we call `print(today)`, where `today` is explicitly passed as an argument.
- In the member example, we call `today.print()`, which uses the member selection `operator.` to select the member function.
- All (non-static) member functions must be called using an object of that class type (e.g. `today` being type `Date`)
- Note that the member function case doesn't need to pass `today` as an argument since the object that a member function is called on is implicitly passed to the member function. For this reason, the object that a member function is called on is often called **the implicit object**. So when we call `today.print()`, `today` is the implicit object, and it is implicitly passed to the `print()` member function.

## Accessing members inside a member function uses the implicit object

Here's the non-member version of `print()` again:
```cpp
// non-member version of print
void print(const Date& date)
{
    // member variables accessed using member selection operator (.)
    std::cout << date.year << '/' << date.month << '/' << date.day;
}
```

This version of `print()` has reference parameter `const Date& date`. Within  the function, we access the members through this reference parameter `date.year`, etc. When `print(today)` is called, the `date` reference parameter is bound to the argument `today`, and get's substituted to `today.year`, etc.

Now let's look at the definition of the member version of `print()`:
```cpp
void print() // defines a member function named print()
{
    std::cout << year << '/' << month << '/' << day;
}
```

Here we access the members as `year`, etc. Inside a member function, any member identifier that isn't prefixed with the member selection operator (.) is associated with the implicit object (e.g. `today`) and `year`, etc., are all evaluated to the values of `today.year`, etc.

## Another member function example

```cpp
#include <iostream>
#include <string>

struct Person
{
    std::string name{};
    int age{};

    void kisses(const Person& person)
    {
        std::cout << name << " kisses " << person.name << '\n';
    }
};

int main()
{
    Person joe{ "Joe", 29 };
    Person kate{ "Kate", 27 };

    joe.kisses(kate);

    return 0;
}
```

```
Joe kisses Kate
```

Let's examine how this works.
1. We define 2 `Person` structs: `joe` and `kate`.
2. We call `joe.kisses(kate)` with `joe` being the implicit object, and `kate` being the explicit argument
3. When `kisses()` member function executes, `name` uses the implicit object `joe`, and `person.name` uses the function argument `kate`. Therefore, `name` and `person.name` both resolve to `joe.name` and `kate.name`, respectively.

## Member variables and functions can be defined in any order

The C++ compiler normally compiles code from top to bottom. For each name encountered, the compiler determines whether it has already seen a declaration for that name, so that it can do proper type checking. This means that inside a non-member function, you can't access a variable or call a function that hasn't at least been declared yet:
```cpp
void x()
{
    y(); // error: y not declared yet, so compiler doesn't know what it is
}

int y()
{
    return 5;
}
```

However, with member functions (and member data initializers), this limitation doesn't apply and we can define our members in any order we like:
```cpp
struct Foo
{
    int m_x{ y() };   // okay to call y() here, even though y() isn't defined until later

    void x() { y(); } // okay to call y() here, even though y() isn't defined until later
    int y()  { return 5; }
};
```

## Member functions can be overloaded

Just like non-member functions, member functions can be overloaded as long as each member function can be differentiated:
```cpp
#include <iostream>
#include <string_view>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }

    void print(std::string_view prefix)
    {
        std::cout << prefix << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 };

    today.print(); // calls Date::print()
    std::cout << '\n';

    today.print("The date is: "); // calls Date::print(std::string_view)
    std::cout << '\n';

    return 0;
}
```

```
2020/10/14
The date is: 2020/10/14
```

## Structs and member functions

In C, structs only have data members, not member functions.

In C++, while designing classes, Bjarne Stroustrup spent some amount of time considering whether structs should be granted the ability to have member functions. Upon consideration, he determined that they should.

- As an aside: For simplicity, Bjarne ultimately decided that structs and classes should have a unified ruleset (meaning structs can do everything classes can, and vice-versa). He did this because he was concerned that giving structs access to a limited subset of capabilities would end up adding complexity and edge-cases to the language.

In modern C++, it's fine for structs to have member functions.

- Structs should avoid defining constructor member functions, as doing so makes them a non-aggregate (covered further in 14.9)

## Class types with no data members

It's possible to create class types with no data members, but only member functions. It's also possible to instantiate objects of such a class type:
```cpp
#include <iostream>

struct Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo f{};
    f.printHi(); // requires object to call

    return 0;
}
```

However, this is silly. Just use a namespace instead so it's clear to the reader that no data is being manipulated and therefore, doesn't require an object to be instantiated to call functions:
```cpp
#include <iostream>

namespace Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo::printHi(); // no object needed

    return 0;
}
```

- If your class type has no data members, prefer using a namespace.


