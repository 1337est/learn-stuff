## Introduction to type conversion

Different data types represent the "same" number differently. E.g. int `3` could be stored as binary `0000 0000 0000 0000 0000 0000 0000 0011` whereas float `3.0` might be stored as binary `0100 0000 0100 0000 0000 0000 0000 0000`.

So what happens here?
```cpp
float f{ 3 }; // initialize floating point variable with int 3
```

The compiler can't copy the bits representing the `int 3` into memory allocated for `float f`. Instead, it needs to convert the integer value `3` to the equivalent floating point value `3.0`, which can then be stored in the memory allocated for `f`.

- **conversion** is the process of producing a new value of some type from a value of a differing type.

Conversion doesn't change the value or type being converted, but a new value with the desired type is created as a result of conversion.

There's implicit and explicit type conversion, which are what they sound like: It happens automagically, or you make it happen (like a real man, lol), respectively.

## Implicit type conversion

- **Implicit type conversion** (also called **automatic type conversion** and **coercion**) is done automatically by the compiler when one data type is required, but a different data type is supplied.

```cpp
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double

float doSomething()
{
    return 3.0; // double value 3.0 implicitly converted to type float
}

double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double

if (5) // int value 5 implicitly converted to type bool
{
}

void doSomething(long l)
{
}

doSomething(3); // int value 3 implicitly converted to type long
```


