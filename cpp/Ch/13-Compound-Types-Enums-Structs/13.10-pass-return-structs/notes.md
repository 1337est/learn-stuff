Consider an employee represented by 3 loose variables:
```cpp
int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    return 0;
}
```

If we want to pass this employee to a function, we'd have to pass 3 variables:
```cpp
#include <iostream>

void printEmployee(int id, int age, double wage)
{
    std::cout << "ID:   " << id << '\n';
    std::cout << "Age:  " << age << '\n';
    std::cout << "Wage: " << wage << '\n';
}

int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    printEmployee(id, age, wage);

    return 0;
}
```

## Passing structs (by reference)

To avoid passing each variable independently, we can simply use a struct passed in by reference (typically by const reference) to avoid making copies:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    Employee joe { 14, 32, 24.15 };
    Employee frank { 15, 28, 18.27 };

    // Print Joe's information
    printEmployee(joe);

    std::cout << '\n';

    // Print Frank's information
    printEmployee(frank);

    return 0;
}
```

In the above example, we pass in 2 employees (`joe` and `frank`) and the output is:
```
ID:   14
Age:  32
Wage: 24.15

ID:   15
Age:  28
Wage: 18.27
```

Because we're passing the entire struct object (rather than individual members), we only need one parameter no matter how many members the struct object has. And, in the future, if we decide to add new members to our `Employee` struct, we won't need to change the function declaration or function call. The new member will automatically be included. Wow. That's much better ain't it?

## Passing temporary structs

In the prior example, we created Employee variable `joe` prior to passing it to the `printEmployee()` function. In cases where we only use a variable once, having to give the variable a name and separate the creation and use of that variable can increase complexity. In such cases, use a temporary object instead.

Below we've replaced variables `joe` and `frank` with temporary objects:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    // Print Joe's information
    printEmployee(Employee { 14, 32, 24.15 }); // construct a temporary Employee to pass to function (type explicitly specified) (preferred)

    std::cout << '\n';

    // Print Frank's information
    printEmployee({ 15, 28, 18.27 }); // construct a temporary Employee to pass to function (type deduced from parameter) (not preferred)

    return 0;
}
```

The implementation for printing Frank's information isn't preferred and this form is considered an implicit conversion, so it will not work in cases where only explicit conversions are acceptable.

Also remember that temporary objects are created and initialized at the point of definition, and destroyed at the end of the full expression in which they are created. Also, evaluation of a temporary object is an rvalue expression, it can only be used in places where rvalues are accepted. When a temporary object is used as a function argument, it will only bind to parameters that accept rvalues. This includes pass by value and pass by const reference, and excludes pass by non-const reference and pass by address.

## Returning structs

All right, time to get fancy: Consider the classic case where we have a function that needs to return a point in 3-dimensional Cartesian space. Such a point has 3 attributes: an x-y-z-coordinate. But functions can only return 1 value. So how do we return all 3 coordinates back to the user?

We return a struct:
```cpp
#include <iostream>

struct Point3d
{
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
};

Point3d getZeroPoint()
{
    // We can create a variable and return the variable (we'll improve this below)
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}

int main()
{
    Point3d zero{ getZeroPoint() };

    if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
        std::cout << "The point is zero\n";
    else
        std::cout << "The point is not zero\n";

    return 0;
}
```

This prints:
```
The point is zero
```

We could also make our function slightly better by returning a temporary (unnamed/anonymous) object instead:
```cpp
Point3d getZeroPoint()
{
    return Point3d { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```

In this case, a temporary `Point3d` is constructed, copied back to the caller, and then destroyed at the end of the expression. This turns it from 2 lines, to 1 line, and no need to understand whether `temp` is used more than once, since it's DESTROYED!)

## Deducing the return type

In cases where the function has an explicit return type (`Point3d`), we can even omit the type and it will be implicitly converted:
```cpp
Point3d getZeroPoint()
{
    // We already specified the type at the function declaration
    // so we don't need to do so here again
    return { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```

ALSO, since we're just returning 0's, why don't we just use empty braces to return a value-initialized `Point3d`?:
```cpp
Point3d getZeroPoint()
{
    // We can use empty curly braces to value-initialize all members
    return {};
}
```

## Structs are an important building block (I like legos)

Classes (which are the heart of C++ and object oriented programming) build directly on top of the concepts we've introduced here. Having a good understanding of structs (especially data members, member selection, and default member initialization) will make your transition to classes much easier.


