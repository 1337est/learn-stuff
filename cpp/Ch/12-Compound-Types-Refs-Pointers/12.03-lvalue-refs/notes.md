- In C++, a **reference** is an alias for an existing object. Once a reference has been defined, any operation on the reference is applied to the object being referenced.

## Lvalue reference types

An **lvalue reference** (commonly just called reference) acts as an alias for an existing lvalue (such as a variable).

We use the ampersand to declare an lvalue reference type:
```cpp
int     // a normal int type
int&    // an lvalue reference to an int object
double& // an lvalue reference to a double object
```

## Lvalue reference variables

- An **lvalue reference variable** is a variable that acts as a reference to an lvalue (usually another variable).
```cpp
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    return 0;
}
```

In the above example, the type `int&` defines `ref` as an lvalue reference to an int, which we then initialize with lvalue expression `x`. Thereafter, `ref` and `x` can be used synonymously. This program outputs:
```
5
5
```

From the compiler's perspective, it doesn't matter whether the ampersand is "attached" to the type name (`int& ref`) or the variable's name (`int &ref`), and which you choose is a matter of style. Modern C++ programmers prefer attaching the ampersand to the type, since it makes clear that the reference is part of the type information, not the identifier.

## Modifying values through an lvalue reference

We can use a reference to modify the value of the object being referenced:
```cpp
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```

```
55
66
77
```

In the above example, `ref` is an alias for `x`, we we're able to change the value of `x` through either `x` or `ref`.

## Initialization of lvalue references

Much like consts, all references must be initialized:
```cpp
int main()
{
    int& invalidRef;   // error: references must be initialized

    int x { 5 };
    int& ref { x }; // okay: reference to int is bound to int variable

    return 0;
}
```

Also lvalue references must be bound to a modifiable lvalue:
```cpp
int main()
{
    int x { 5 };
    int& ref { x }; // valid: lvalue reference bound to a modifiable lvalue

    const int y { 5 };
    int& invalidRef { y };  // invalid: can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: can't bind to an rvalue

    return 0;
}
```

This is because you shouldn't be able to change those values through the reference.

Also, the type of reference must match the type of the referent:
```cpp
int main()
{
    int x { 5 };
    int& ref { x }; // okay: reference to int is bound to int variable

    double y { 6.0 };
    int& invalidRef { y }; // invalid; reference to int cannot bind to double variable
    double& invalidRef2 { x }; // invalid: reference to double cannot bind to int variable

    return 0;
}
```

## References aren't objects

In C++, references are not objects and a reference is not required to exist or occupy storage. The compiler (if possible) optimizes the references away by replacing all occurences of the reference with the referent.

Interestingly, this means the term "reference variable" is a bit of a misnomer, as variables are objects with a name, and references aren't objects.


