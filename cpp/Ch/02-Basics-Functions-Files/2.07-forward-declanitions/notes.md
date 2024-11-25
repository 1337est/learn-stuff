## Declanitions?
- **declanition:** A declaration and definition

The following program has a problem in it:

```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```

You would expect this program to produce: `The sum of 3 and 4 is: 7`.

But instead you get: `add.cpp(5) : error C3861: 'add': identifier not found`

This is because the compiler compiles the contents of the code files sequentially. Therefore to fix the code above we simply need to rearrange the code so that add is above main.

But what if you have a function A and B, where A calls function B, and B also calls function A? If you define A or B first, the compiler will complain either way that it doesn't know what the other one is... Luckily forward declarations is the answer!

## Forward declarations
- **forward declaration:** tells the compiler about the existence of an identifier before defining the identifier.

You use **function declaration statement** (also called **function prototypes**) like so:

```cpp
int add(int x, int y);  // function declaration includes return type, name, parameters,
                        // and a semicolon without a function body.
```

Here's the original program with a function declaration instead:

```cpp
#include <iostream>

int add(int x, int y); // forward declaration of add()
// int add(int, int); // This is also valid (void function declaration)

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // This words fine now
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```

## But what's the point really?
The point and power of forward declarations doesn't really become too apparent until the scenario of the caller and callee being in completely different files! Forward declarations can also be used to define our functions in an order-agnostic manner. Basically, without the necessity of one function **needing** to be declared before another, we can now not worry about the order. Now we can order our code to maximize organization by clustering related functions together or for reader comprehension/understanding. Also, forward declarations help when 2 functions call each other and reordering doesn't help with this circular dependency situation.

## Declaration, definition, or declanition?

There is no such thing as a declanition, i made that word up. However, you will often hear the words declaration and definition used interchangeably.

- **declaration:** tells the compiler about the existence of an identifier and its associated type information.
```cpp
// declaration examples
int add(in x, int y);   // tells the compiler about function add. No body.
int x;                  // tells compiler about integer variable x
```

- **definition:** a declaration that implements (for functions and types) or instantiates (for variables) the identifier.
```cpp
// definition examples
int add(int x, int y)
{
    int z{ x + y }; // instantiates variable z
    return z;
}
int x; // instantiates variable x
```

As you can see, all definition are declarations by definition! However, not all declaration are definitions. Basically, to declare something is to say it exists, and to define something is to say how it exists.
