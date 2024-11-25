## How overloaded function are differentiated
- Number of parameters is used for differentiation
- Type of parameters is used for differentiation (excluding typedefs, type aliases, and const qualifier on value parameters. Includes ellipses.)
- Return type IS NOT a differentiating factor

## Overloading based on # parameters

```cpp
int add(int x, int y)
{
    return x + y;
}

int add(int x, int y, int z)
{
    return x + y + z;
}
```

The compiler knows that a function call with 2 integer parameters goes to `add(int, int)` and a function call with 3 integer parameters goes to `add(int, int, int)`.

## Overloading based on type of parameters

```cpp
int add(int x, int y); // integer version
double add(double x, double y); // floating point version
double add(int x, double y); // mixed version
double add(double x, int y); // mixed version
```

Because type aliases (or typedefs) are not distinct types, overloaded functions using type aliases are not distinct from overloads using the aliased type:

```cpp
typedef int Height; // typedef
using Age = int; // type alias

void print(int value);
void print(Age value); // not differentiated from print(int)
void print(Height value); // not differentiated from print(int)
```

For parameters passed by value, the const qualifier is also not considered. Therefore, the following functions are not considered differentiated:
```cpp
void print(int);
void print(const int); // not differentiated from print(int)
```

## The return type of a function is not considered for differentiation

Consider the following:
```cpp
int getRandomValue();
double getRandomValue();
```

This produces a compiler error. That's because the compiler sees `getRandomValue();`, and it isn't clear which of the 2 overloaded functions to call.

The best way to address the issue:
```cpp
int getRandomInt();
double getRandomDouble();
```

## Type signature

A function's **type signature** (commonly just called **signature**) is defined as the parts of the function header that are used for differentiation of the function. In C++, this includes the name, number of parameters, parameter types, and function-level qualifiers.
