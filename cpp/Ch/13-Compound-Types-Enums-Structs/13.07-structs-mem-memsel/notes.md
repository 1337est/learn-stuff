There are many instances in programming where we need more than one variable in order to represent something of interest.

Let's say we wanted a program that stores information about employees in a company. We might be interested in keeping track of attributes like so:
```cpp
std::string name;
std::string title;
int age;
int id;
int managerId;
double wage;
int birthdayYear;
int birthdayMonth;
int birthdayDay;
int hireYear;
int hireMonth;
int hireDay;
```

However, it isn't clear whether these variables are actually related or not without proper documentation and there are now 12 variables to manage. If we wanted to pass this employee to a function, we would have to pass 12 arguments... (an in the correct order), which sucks.

Fortunately C++ comes with 2 compound types designed to solve such challenges:
1. structs
2. classes

A **struct** (short for **structure**) is a program-defined data type that allows us to bundle multiple variables together into a single type.

## Defining structs

Because structs are program-defined types, we need to tell the compiler what our struct type looks like before we can begin using it:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```

The `struct` keyword is used to tell the compiler that we're defining a struct, which we've named `Employee`.

Then inside a pair of curly braces, we define the variables that each Employee object will contain. The variables that are part of the struct are called **data members** (or **member variables**).

- In everyday language, a "member" is an individual who belongs to a group.
- In C++, a **member** is a variable, function, or type that belongs to a struct (or class). All members must be declared within the struct (or class) definition.

As a reminder, `Employee` is just a type definition -- no objects are actually created at this point.

## Defining struct objects

In order to use the `Employee` type, we simply define a variable of type `Employee`:
```cpp
Employee joe {}; // Employee is the type, joe is the variable name
```

When the code is executed, an Employee object is instantiated that contains the 3 data members (id, age, wage). The empty braces ensures our object is value-initialized.

Now we can create multiple variables using the same struct type easily:
```cpp
Employee joe {};
Employee frank {};
```

## Accessing members

Consider the following:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    return 0;
}
```

To access a specific member variable, we use the **member selection operator** (`operator.`) in between the struct variable name and the member name. To access Joe's age, we'd use `joe.age`.

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    joe.age = 32;  // use member selection operator (.) to select the age member of variable joe

    std::cout << joe.age << '\n'; // print joe's age

    return 0;
}
```

This prints:
```
32
```

Below is the power of structs:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};
    joe.id = 14;
    joe.age = 32;
    joe.wage = 60000.0;

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int totalAge { joe.age + frank.age };

    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage < frank.wage)
        std::cout << "Joe makes less than Frank\n";
    else
        std::cout << "Joe and Frank make the same amount\n";

    // Frank got a promotion
    frank.wage += 5000.0;

    // Today is Joe's birthday
    ++joe.age; // use pre-increment to increment Joe's age by 1

    return 0;
}
```

Everything is easy to read and understand, and is very organizational.
