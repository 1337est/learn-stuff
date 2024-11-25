## Null pointers

Besides memory addresses, a pointer can also have a **null value**. A null value is a special value that means something has no value. When a pointer is holding a null value, it means the pointer is not pointing at anything. Such a pointer is called a null pointer.
```cpp
int main()
{
    int* ptr {}; // ptr is now a null pointer, and is not holding an address

    return 0;
}
```

- It's best practice to initialize your pointers to be null pointers if you are not initializing them with the address of a valid object yet. We can always change the value a pointer is pointing to through assignment.
```cpp
#include <iostream>

int main()
{
    int* ptr {}; // ptr is a null pointer, and is not holding an address

    int x { 5 };
    ptr = &x; // ptr now pointing at object x (no longer a null pointer)

    std::cout << *ptr << '\n'; // print value of x through dereferenced ptr

    return 0;
}
```

## The nullptr keyword

Just like `true` and `false` represent Boolean literal values, the `nullptr` keyword represents a null pointer literal:
```cpp
int main()
{
    int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer

    int value { 5 };
    int* ptr2 { &value }; // ptr2 is a valid pointer
    ptr2 = nullptr; // Can assign nullptr to make the pointer a null pointer

    someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter

    return 0;
}
```

- Dereferencing a null pointer results in undefined behavior
- Similar to Boolean values `false` and `true` being implicitly converted to from integral values `0` or `1`, pointers will implicitly convert to Boolean values: a null pointer converts to Boolean value `false`, and a non-null pointer converts to Boolean value `true`. We can use this to check to see if a pointer is null or not:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    // pointers convert to Boolean false if they are null, and Boolean true if they are non-null
    if (ptr) // implicit conversion to Boolean
        std::cout << "ptr is non-null\n";
    else
        std::cout << "ptr is null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n"); // implicit conversion to Boolean

    return 0;
}
```

## Use nullptr to avoid dangling pointers

Since dereferencing a pointer that is either null or dangling results in undefined behavior, we need to ensure our code does not do either of these things

We can easily avoid dereferencing a null pointer by using a conditional:
```cpp
/ Assume ptr is some pointer that may or may not be a null pointer
if (ptr) // if ptr is not a null pointer
    std::cout << *ptr << '\n'; // okay to dereference
else
    // do something else that doesn't involve dereferencing ptr (print an error message, do nothing at all, etc...)
```

## Legacy null pointer literals: 0 and NULL
The old way of doing things was like this:
```cpp
int main()
{
    float* ptr { 0 };  // ptr is now a null pointer (for example only, don't do this)

    float* ptr2; // ptr2 is uninitialized
    ptr2 = 0; // ptr2 is now a null pointer (for example only, don't do this)

    return 0;
}
```
```cpp
#include <cstddef> // for NULL

int main()
{
    double* ptr { NULL }; // ptr is a null pointer

    double* ptr2; // ptr2 is uninitialized
    ptr2 = NULL; // ptr2 is now a null pointer

    return 0;
}
```

You should avoid using `0` and `NULL` in modern C++ and just use `nullptr` instead.

## Favor references over pointers whenever possible

Pointers are powerful and dangerous since they have the advantage over references to be able to change what they are pointing to, and to be pointed at null. A null pointer runs the risk of being dereferenced, and the ability to change what a pointer is pointing at can make creating dangling pointers easier:
```cpp
int main()
{
    int* ptr { };

    {
        int x{ 5 };
        ptr = &x; // assign the pointer to an object that will be destroyed (not possible with a reference)
    } // ptr is now dangling and pointing to invalid object

    if (ptr) // condition evaluates to true because ptr is not nullptr
        std::cout << *ptr; // undefined behavior

    return 0;
}
```


