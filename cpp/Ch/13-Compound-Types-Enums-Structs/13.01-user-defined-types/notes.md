Fundamental types are defined as part of the core C++ language and are available for immediate use:
```cpp
int x; // define variable of fundamental type 'int'
double d; // define variable of fundamental type 'double'
```

This is also true for compound types that are simply extensions of fundamental types (including functions, pointers, references, and arrays):
```cpp
void fcn(int) {}; // define a function of type void()(int)
int* ptr; // define variable of compound type 'pointer to int'
int& ref { x }; // define variable of compound type 'reference to int' (initialized with x)
int arr[5]; // define an array of 5 integers of type int[5] (we'll cover this in a future chapter)
```

This works because C++ already knows what the type names (and symbols) for these types mean -- we don't need to provide or import any definitions.

However, consider the case of type aliases, which allows us to define a new name for an existing type. Because a type alias introduces a new identifier into the program, a type alias must be defined before it can be used:
```cpp
#include <iostream>

using length = int; // define a type alias with identifier 'length'

int main()
{
    length x { 5 }; // we can use 'length' here since we defined it above
    std::cout << x << '\n';

    return 0;
}
```
If we were to omit the definition of `length`, the compiler wouldn't know what `length` was. The definition of `length` doesn't create an object -- it just tells the compiler what a `length` is so it can be used later.

## What are user-defined / program-defined types?

C++ allows us to create entirely new, custom types for use in our programs! Such types are often called **user-defined types** (or **program-defined types**).

C++ has 2 different categories of compound types that can be used to create program-defined types:
1. Enumerated types (including unscoped and scoped enumerations)
2. Class types (including structs, classes, and unions)

## Defining program-defined types

Just like aliases, program-defined types must also be defined before they can be used.
- The definition of a program-defined type is called a **type definition**.

Although we haven't covered what a struct is yet, here's an example showing the definition of custom Fraction type and an instantiation of an object using that type:
```cpp
// Define a program-defined type named Fraction so the compiler understands what a Fraction is
// (we'll explain what a struct is and how to use them later in this chapter)
// This only defines what a Fraction type looks like, it doesn't create one
struct Fraction
{
	int numerator {};
	int denominator {};
};

// Now we can make use of our Fraction type
int main()
{
	Fraction f { 3, 4 }; // this actually instantiates a Fraction object named f

	return 0;
}
```

In this example, we're using the `struct` keyword to define a new program-defined type named `Fraction` in global scope so it can be used anywhere in the file.

- Don't forget to end your type definitions with a semicolon
- By convention, program-defined types are named starting with a capital letter and don't use a suffix.
- A program-defined type used in only one code file should be defined in that code file as close to the first usage as possible
- A program-defined type used in multiple code files should be defined in a header file with the same name as the program-defined type (e.g. a program-defined type name Fraction would be defined in Fraction.h) and then #included into each code file as needed.

Here's an example of our Fraction type in a header file named Fraction.h so it can be included into multiple code files:
```cpp
// Fraction.h
#ifndef FRACTION_H
#define FRACTION_H

// Define a new type named Fraction
// This only defines what a Fraction looks like, it doesn't create one
// Note that this is a full definition, not a forward declaration
struct Fraction
{
	int numerator {};
	int denominator {};
};

#endif
```

```cpp
// Fraction.cpp
#include "Fraction.h" // include our Fraction definition in this code file

// Now we can make use of our Fraction type
int main()
{
	Fraction f{ 3, 4 }; // this actually creates a Fraction object named f

	return 0;
}
```


