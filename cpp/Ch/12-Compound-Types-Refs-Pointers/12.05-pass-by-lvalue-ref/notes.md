This is where we show how lvalue references are useful

For some context, when we discussed `pass by value` in lesson 2.4, is where an argument passed to a function is copied into the function's parameter:
```cpp
#include <iostream>

void printValue(int y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    int x { 2 };

    printValue(x); // x is passed by value (copied) into parameter y (inexpensive)

    return 0;
}
```

In the above program, when `printValue(x)` is called, the value of `x` (which is `2`) is copied into parameter `y`. Then, at the end of the function, object `y` is destroyed.

This means that when we called the function, we made a copy of our argument's value, only to use it briefly and then destroy it! Fortunately, because fundamental types are cheap to copy, this isn't a problem. However...

## Some objects are expensive to copy

Most of the types in the standard library (such as `std::string`) are `class types`. Class types are usually expensive to copy. Whenever possible, we want to avoid making unnecessary copies of objects that are expensive to copy (especially when we destroy them quickly).

Consider the following program:
```cpp
#include <iostream>
#include <string>

void printValue(std::string y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" }; // x is a std::string

    printValue(x); // x is passed by value (copied) into parameter y (expensive)

    return 0;
}
```

Although this program works, it is inefficient. What we need here is a pass by reference (vs a pass by value) to make this inexpensive.

## Pass by reference

When using a **pass by reference**, we declare a function parameter as a reference type (or const reference type) rather than a normal type.
```cpp
#include <iostream>
#include <string>

void printValue(std::string& y) // type changed to std::string&
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" };

    printValue(x); // x is now passed by reference into reference parameter y (inexpensive)

    return 0;
}
```

This is a simple 1 character change, but is much better. When the function is called, each reference parameter is bound to the appropriate argument. Because the reference acts as an alias for the argument, no copy of the argument is made. The parameter `y` has been changed from a `std::string` to a `std::string&` (an lvalue reference). Now, when `printValue(x)` is called, lvalue reference parameter `y` is bound to argument `x`. Binding a reference is always inexpensive, and no copy of `x` needs to be made. Because a reference acts as an alias for the object being referenced, when `printValue()` uses reference `y`, it's acccessing the actual argument `x` (rather than a copy of `x`). Holy crap. Mind = Blown!

## Pass by reference allows us to change the value of an argument

Look at this:
```cpp
#include <iostream>

void addOne(int y) // y is a copy of x
{
    ++y; // this modifies the copy of x, not the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has not been modified

    return 0;
}
```
Outputs:
```
value = 5
value = 5
```

HOWEVER, since a reference acts identically to the object being referenced, when using pass by reference, any changes made to the reference parameter will affect the argument:
```cpp
#include <iostream>

void addOne(int& y) // y is bound to the actual object x
{
    ++y; // this modifies the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has been modified

    return 0;
}
```
Outputs:
```
value = 5
value = 6
```

As you can see in the first example, the actual value of x wasn't modified after the function call. But, when using pass by reference, it modifies (not the copy) but the real value of x since the reference is simply an alias for the real value.

## Pass by reference can only accept modifiable lvalue arguments

Something worth noting but should be obvious: pass by referencing only works with arguments that are modifiable lvalues. This means we cannot pass const variable or literals by reference:
```cpp
#include <iostream>

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue

    const int z { 5 };
    printValue(z); // error: z is a non-modifiable lvalue

    printValue(5); // error: 5 is an rvalue

    return 0;
}
```

Fortunately, there's an easy way around this, which will be discussed next lesson. We'll also show when to "pass by value" vs "pass by reference".


