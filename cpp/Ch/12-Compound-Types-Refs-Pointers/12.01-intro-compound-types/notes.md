Now we begin our journey as a true C++ programmer. Muahahahaha!

- **Compound data types** (also called **composite data types**) are data types that can be constructed from fundamental data types (or other compound data types).

C++ supports the following compound types:
- Functions
- Arrays
- Pointer types:
    - Pointer to object
    - Pointer to function
- Pointer to member types:
    - Pointer to data member
    - Pointer to member function
- Reference types:
    - L-value references
    - R-value references
- Enumerated types:
    - Unscoped enumerations
    - Scoped enumerations
- Class types:
    - Structs
    - Classes
    - Unions

The compound type we've been using regularly are functions:
```cpp
void doSomething(int x, double y)
{
}
```
The type of this function is `void(int, double)`. Note that this type is COMPOSED (see what we're doing here?) of fundamental types? This makes it a compound type.
