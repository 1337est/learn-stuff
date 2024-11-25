* An identifier with **external linkage** can be seen and used both from the file in which it is defined, and from other code files via a forward declaration.

## Functions have external linkage by default

In order to call a function defined in another file, you just use a forward declaration for the function in any other files that want to use the function. The forward declaration tells the compiler about the existence of the function, and the linker connects the function calls to the actual function definition.

```cpp
// a.cpp
#include <iostream>

void sayHi() // this function has external linkage, and can be seen by other files
{
    std::cout << "Hi!\n";
}
```
```cpp
// main.cpp
void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file

int main()
{
    sayHi(); // call to function defined in another file, linker will connect this call to the function definition

    return 0;
}
```

In the above example, the forward declaration for `sayHi()` in `main.cpp` allows access to the `sayHi()` function defined in `a.cpp`. This in turn satisfies the compiler, and the linker is able to do it's job and link the function call to the function definition. HOWEVER, if `sayHi()` had internal linkage instead (remember, internal linkage means identifiers aren't exposed to the linker), then the linker literally wouldn't be able to connect the function call to the function definition. A linker error would result.

## Global variables with external linkage

```cpp
int g_x { 2 }; // non-constant globals are external by default

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

## Variable forward declarations via the `extern` keyword

```cpp
// a.cpp
// global variable definitions
int g_x { 2 }; // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```
```cpp
// main.cpp
#include <iostream>

extern int g_x; // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << ' ' << g_y << '\n'; // prints 2 3

    return 0;
}
```

## Quick summary

```cpp
// External global variable definitions:
int g_x;                       // defines non-initialized external global variable (zero initialized by default)
extern const int g_x{ 1 };     // defines initialized const external global variable
extern constexpr int g_x{ 2 }; // defines initialized constexpr external global variable

// Forward declarations
extern int g_y;                // forward declaration for non-constant global variable
extern const int g_y;          // forward declaration for const global variable
extern constexpr int g_y;      // not allowed: constexpr variables can't be forward declared
```



