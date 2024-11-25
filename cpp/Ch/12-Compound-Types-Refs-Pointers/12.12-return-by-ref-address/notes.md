The same issue of copying expensive types can be said for return types as well, since returning by value would be expensive for certain types (such as `std::string`):
```cpp
std::string returnByValue(); // returns a copy of a std::string (expensive)
```

## Return by reference

In cases where we're passing a class type back to the caller, we may (or may not) want to return by reference instead. **Return by reference** is what it sounds like, it returns a reference that is bound to the object being returned, which avoids making a copy of the return value:
```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // returns a const reference
{
    static const std::string s_programName { "Calculator" }; // has static duration, destroyed at end of program

    return s_programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName();

    return 0;
}
```
This program prints:
```
This program is named Calculator
```

## The object being returned by reference must exist after the function returns

(That's why it's static const). Otherwise, the reference being returned will be left dangling (referencing an object that has been destroyed), and use of that reference will result in undefined behavior.

Let's view an example where our function returns a dangling reference
```cpp
#include <iostream>
#include <string>

const std::string& getProgramName()
{
    const std::string programName { "Calculator" }; // now a non-static local variable, destroyed when function ends

    return programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName(); // undefined behavior

    return 0;
}
```

## Lifetime extension doesn't work across function boundaries

Let's take a look at an example where we return a temporary by reference:
```cpp
#include <iostream>

const int& returnByConstReference(const int& ref)
{
    return ref;
}

int main()
{
    // case 1: direct binding
    const int& ref1 { 5 }; // extends lifetime
    std::cout << ref1 << '\n'; // okay

    // case 2: indirect binding
    const int& ref2 { returnByConstReference(5) }; // binds to dangling reference
    std::cout << ref2 << '\n'; // undefined behavior

    return 0;
}
```

In case 2, a temporary object is created to hold value `5`, which function parameter `ref` binds to. The function simply returns the reference back to the caller, which is then used to initialize `ref2` in main(). Because this is not a direct binding to the temporary object (as the reference was bounced through a function), lifetime extension doesn't apply. This leaves `ref2` dangling, and its subsequent use is undefined behavior.

## Assigning/initializing a normal variable with a returned reference makes a copy

If a function returns a reference, and that reference is used to initialize or assign to a non-reference variable, the return value will be copied (as if returned by value):
```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 };
    ++s_x;
    return s_x;
}

int main()
{
    const int id1 { getNextId() }; // id1 is a normal variable now and receives a copy of the value returned by reference from getNextId()
    const int id2 { getNextId() }; // id2 is a normal variable now and receives a copy of the value returned by reference from getNextId()

    std::cout << id1 << id2 << '\n';

    return 0;
}
```
```
12
```

Also note that if a program returns a dangling reference, the reference is left dangling before the copy is made:
```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // will return a const reference
{
    const std::string programName{ "Calculator" };

    return programName;
}

int main()
{
    std::string name { getProgramName() }; // makes a copy of a dangling reference
    std::cout << "This program is named " << name << '\n'; // undefined behavior

    return 0;
}
```

## It's okay to return reference parameters by reference

Duh?

```cpp
#include <iostream>
#include <string>

// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int main()
{
	std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world) << '\n';

	return 0;
}
```
```
Hello
```

By using pass by reference/return by reference, we can avoid up to 3 potential copies of `std::string` (one for each parameter and one for the return value).

## The caller can modify values through the reference

Here's an illustrative example:
```cpp
#include <iostream>

// takes two integers by non-const reference, and returns the greater by reference
int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7

    std::cout << a << b << '\n';

    return 0;
}
```

This might look confusing at first, but it isn't. Let's break it down. `max(a, b) = 7` calls the `max()` function with `a` and `b` as arguments being passed into parameters `x` and `y`. Since `x` and `y` are reference parameters, `x` binds to argument `a`, and `y` binds to `b`. The function then determines if `x` (5) or `y` (6) is greater and returns `y` (which is still bound to `b`) back to the caller. Therefore, the expression `max(a, b) = 7` effectively resolves to `b = 7` and prints:
```
57
```

## Return by address

**Return by address** works almost identically to return by reference, except a pointer to an object is returned instead of a reference to an object. Return by address has the same primary caveat as return by reference -- the object being returned by address must outlive the scope of the function returning the address, otherwise the caller will receive a dangling pointer.
