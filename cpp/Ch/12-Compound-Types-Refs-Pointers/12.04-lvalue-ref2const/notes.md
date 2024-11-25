## Lvalue reference to const

When using the `const` keyword when declaring an lvalue reference, we tell an lvalue reference to treat the object it is referencing as const.

Lvalue references to const can bind to non-modifiable lvalues:
```cpp
int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is an lvalue reference to a const value

    return 0;
}
```

Because lvalue references to const treat the object they are referencing as const, they can be used to access but not modify the value being referenced:
```cpp
#include <iostream>

int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    return 0;
}
```

## Initializing an lvalue reference to const with a modifiable lvalue

This is where it gets more interesting. Lvalue references to const can also bind to modifiable lvalues:
```cpp
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we can not modify an object through a const reference

    x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    return 0;
}
```

Here, the object being referenced is treated as const when accessed through the reference, but not the un-referenced modifiable lvalue.

Favor lvalue references to const over lvalue references to non-const unless you need to modify the object being referenced.

You can even initialize an lvalue reference to const with an rvalue:
```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // okay: 5 is an rvalue

    std::cout << ref << '\n'; // prints 5

    return 0;
}
```

## Initializing an lvalue reference to const with a value of a different type

Lvalue references to const can even bind to values of a different type, so long as those values can be implicitly converted to the reference type:
```cpp
#include <iostream>

int main()
{
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    return 0;
}
```

In the first case, a temporary object of type `double` was created and initialized with int value `5`. Then `const double& r1` is bound to that temporary double object.

In case 2, a temporary object of type `int` is created and initialized with char value `a`. Then `const int& r2` is bound to that temporary int object.

This is because if you try to bind a const lvalue reference to a value of a different type, the compiler will create a temporary object of the same type as the reference, initialize it using the value, and then bind the reference to the temporary.

Also note that printing `r2` prints an int rather than a char. That's because `r2` is bound to that temporary object (the temporary int that was created) no to char `c`.

## Const references bound to temporary objects extend the lifetime of the temporary object

Temporary objects are normally destroyed at the end of the expression in which they are created.

To avoid dangling references in such cases, C++ has a special rule that state: When a const lvalue reference is directly bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference.
```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // The temporary object holding value 5 has its lifetime extended to match ref

    std::cout << ref << '\n'; // Therefore, we can safely use it here

    return 0;
} // Both ref and the temporary object die here
```

In the above example, when `ref` is initialized to rvalue `5`, a temporary object is created and `ref` is bound to that temporary object. The lifetime of the temporary object matches the lifetime of `ref`. This means we can safely print the value of `ref` in the next statement. Then both `ref` and the temporary object die (go out of scope) at the end of the block.

- Lvalue references can only bind to modifiable lvalues
- Lvalue references to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. This makes them a much more flexible type of reference.


