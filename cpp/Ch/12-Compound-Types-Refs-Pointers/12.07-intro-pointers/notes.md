Take a deep breath. It isn't hard I guarantee you. You are smart, and I'll break it down very simply.

Let's do some setup to make things easier to understand:

Consider a normal variable like this one:
```cpp
char x {}; // chars use 1 byte of memory
```

(Simplified) When the code generated for this definition is executed, a piece of memory from RAM will be assigned to this object. Let's say this variable `x` is assigned memory location `140`. Whenever we use variable `x` in an expression or statement, the program will go to memory address `140` to access the value stored there.

The nicer things about variables is the fact that we don't need to concern ourselves with the specific memory address assigned to the variable. We said `x` was in `140`, but it could be in `200` or `300` and we couldn't care less. When we call `x`, we know that the compiler will translate this name into the appropriately assigned memory address. The compiler takes care of all the addressing (this is also true with references):
```cpp
int main()
{
    char x {}; // assume this is assigned memory address 140
    char& ref { x }; // ref is an lvalue reference to x (when used with a type, & means lvalue reference)

    return 0;
}
```

Whenever we use `ref` (an alias for `x`), the program goes to memory address `140` to access the value!

## The address-of operator (&)

The memory addresses of variables by default are hidden, but we can access them using the **address-of operator** (&) which returns the memory address of its operand:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    return 0;
}
```

It should output something similar (although the memory address is probably different):
```
5
0027FEA0
```

As you can see, memory addresses are usually printed as hexadecimal values, often without the 0x prefix.

- For objects that use more than one byte of memory, the address-of operator will return the memory address of the first byte used by the object.

The `&` symbol is context dependent (which understandably causes confusion):
- When `&` follows a type name, `&` denotes an lvalue reference: `int& ref`
- When `&` is used in a unary context in an expression, `&` is the address-of operator: `std::cout << &x`
- When `&` is used in a binary context in an expression, `&` is the Bitwise AND operator: `std::cout << x & y`

## The dereference operator (*)
The most useful thing we can do with an address is access the value stored at the address. The **dereference operator** (*) (also called **indirection operator**) return the value at a given memory address as an lvalue:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but makes it easier to read)

    return 0;
}
```

The memory address should be different, and outputs something like this:
```
5
0027FEA0
5
```

The address-of and dereference operators work as opposites:
- The address-of operator (&) gets the address of an object
- The dereference operator (*) gets the object at an address

Now that we know about these 2 operators, it's time to talk about pointers

## Pointers

- Note: What we are covering here are "raw pointers" or "dumb pointers". "Smart pointers" which were introduced to C++ later, are covered in chapter 22.

A **pointer** is an object that holds a memory address as its value. This allows us to store the address of some other object to use later.

Much like reference types are declared using an ampersand (&), pointers are declared using an asterisk (*):
```cpp
int; // a normal int
int&; // an lvalue reference to an int value

int*; // a pointer to an int value (holds the address of an integer value)
```

In use this is how it looks:
```cpp
int main()
{
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)
    int* ptr;       // a pointer to an integer

    return 0;
}
```

Note here, that the asterisk is part of the declaration syntax for pointers, not a use of the dereference operator.

- Just like with references, it's best practice to place the asterisk next to the type name when declaring a pointer type.

## Pointer initialization

Like normal variables, pointers are not initialized by default and a pointer that has not been initialized is called a **wild pointer**. A wild pointer contains a garbage address and dereferencing a wild pointer will result in undefined behavior.

- Always initialize your pointers
```cpp
int main()
{
    int x{ 5 };

    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x

    return 0;
}
```

Since pointers hold addresses, when we initialize or assign a value to a pointer, that value has to be an address.

Once we have a pointer holding the address of another object, we can then use the dereference operator (*) to access the value at that address:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x

    int* ptr{ &x }; // ptr holds the value of variable x
    std::cout << *ptr << '\n'; // use dereference operator to print the value at the address that ptr is holding (which is x's address)

    return 0;
}
```

This obviously prints:
```
5
5
```

Much like the type of a reference has to match the type of object being referred to, the type of the pointer has to match the type of the object being pointed to:
```cpp
int main()
{
    int i{ 5 };
    double d{ 7.0 };

    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object

    return 0;
}
```

Initializing a pointer with a literal value is disallowed (although there is 1 exception):
```cpp
int* ptr{ 5 }; // nope
int* ptr{ 0x0012FF7C }; // not okay, since 0x0012FF7C is treated like an integer literal
```

## Pointers and assignment

We can use assignment with pointers in 2 different ways:
1. To change what the pointer is pointing at (by assigning a new address)
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr initialized to point at x

    std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

    int y{ 6 };
    ptr = &y; // change ptr to point at y

    std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)

    return 0;
}
```
```
5
6
```

2. To change the value being pointed at (by assigning the dereferenced pointer a new value)
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // initialize ptr with address of variable x

    std::cout << x << '\n';    // print x's value
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

    std::cout << x << '\n';
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    return 0;
}
```

We define pointer `ptr`, initialize it with address `x`, and then print the value of both `x` and `*ptr` (which is `5`). Because `*ptr` return an lvalue, we can use this on the left hand side eof an assignment statement, which we do to change the value being pointed at by `ptr` to `6`. Remember that a dereferenced pointer is  the value of the variable that the pointer is pointing at. Since we changed the value at x's memory address, we changed variable `x` as well.

## Pointers behave much like lvalue references

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int& ref { x };  // get a reference to x
    int* ptr { &x }; // get a pointer to x

    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (5)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

    ref = 6; // use the reference to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (6)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

    *ptr = 7; // use the pointer to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (7)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

    return 0;
}
```
```
555
666
777
```

Let's break down the above example a little bit:
- `x` is 5
- `ref` is an alias for `x`, and is basically just `x`
- `ptr` is the address of `x`
- `*ptr` is the value at the address `x`, which is basically just `x`.

Therefore, the above program has these steps:
1. We initialize our variable `int x` with `5`.
2. We initialize an reference variable `int& ref` referenced/aliased to `x`
3. We initialize a pointer variable `int* ptr` with address of x using the address of operator `&x`.
4. We print out the value of `x` (5)
5. We print out the value of `ref` (5)
6. We use the dereference operator (*) on our pointer `*ptr` to access the value at memory address `x`
7. We change the value of `ref`, which is the value of `x`
8. We print out the value of `x` in 3 different ways stated above in steps 4, 5, and 6.
9. We change the value of `*ptr` which is the value at the `x`'s memory address, which is just `x`'s value
10. We print out the value of `x` in 3 different ways stated above in steps 4, 5, and 6.

There are some differences between pointers and references worth mentioning:
- References must be initialized, pointers are not required to be initialized (but should be)
- References are not objects, pointers are
- References cannot be reseated (changed to reference something else), pointers can change what they are pointing at.
- References must always be bound to an object, pointers can point to nothing!
- References are "safe" (outside of dangling references), pointers are inherently dangerous

## The address-of operator returns a pointer

The address-of operator (&) doesn't return the address of its operand as a literal, but instead returns a pointer containing the address of the operand (whose type is derived from the argument).
```cpp
#include <iostream>
#include <typeinfo>

int main()
{
	int x{ 4 };
	std::cout << typeid(&x).name() << '\n'; // print the type of &x

	return 0;
}
```
This returns:
```
int *
```

## The size of pointers

The size of a pointer is dependent upon the architecture the executable is compiled for -- a 32-bit executable uses 32-bit (4 bytes) memory addresses and a 64-bit (8 bytes) executable uses 64 bit memory addresses. This is true regardless of the size of the object being pointed to:
```cpp
#include <iostream>

int main() // assume a 32-bit application
{
    char* chPtr{};        // chars are 1 byte
    int* iPtr{};          // ints are usually 4 bytes
    long double* ldPtr{}; // long doubles are usually 8 or 12 bytes

    std::cout << sizeof(chPtr) << '\n'; // prints 4
    std::cout << sizeof(iPtr) << '\n';  // prints 4
    std::cout << sizeof(ldPtr) << '\n'; // prints 4

    return 0;
}
```

## Dangling pointers

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x };

    std::cout << *ptr << '\n'; // valid

    {
        int y{ 6 };
        ptr = &y;

        std::cout << *ptr << '\n'; // valid
    } // y goes out of scope, and ptr is now dangling

    std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer

    return 0;
}
```

The above program probably prints:
```
5
6
6
```

But it may not since `ptr` is dangling at the end.
