## Bits, bytes, and memory addressing

This is going to be important so pay attention here:

Quick recap that variables are names for a piece of memory that can be used to store info:
- Computers have RAM that is available for programs to use.
- When a variable is defined, a piece of that memory is set aside for that variable

Vocab:
- **binary digit:** Also called a bit, can hold a value of 0 or 1, off or on.
- **memory addresses:** Also called addresses, allows us to find and access contents of memory at a particular location. It's the memory organized in sequential units.

In modern computing architectures, each bit does not get it's own unique memory address, because memory addresses are limited. Instead, each memory address holds 1 byte of data.

- **byte:** a group of bits that are operated on as a unit. Modern standard has a byte as 8 sequential bits.

### Data types

Data types tell the compiler how to interpret the contents of memory in some meaningful way.

### Fundamental data types

C++ has built-in support for different data types called **fundamental data types** (also informally called basic types, primitive types, and built-in types).

Some data types include:
- **Floating Point:** float, double, long double.
    - These are numbers with a fractional part like 3.14159
- **Integral (Boolean):** bool
    - true or false
- **Integral (Character):** char, wchar_t, char8_t (C++20), char16_t (C++11), char32_t (C++11).
    - These are for single character texts like "c" or "e".
- **Integral (Integer):** short int, int, long int, long long int (C++11)
    - These are positive and negative whole numbers like 1337, or 69.
- **Null Pointer:** std::nullptr_t (C++11)
    - A null pointer like nullptr
- **Void:** void
    - No type. No example. Not applicable.

### The _t stuff

The newer version of C++ use a _t suffix which means "type", and is common nomenclature applied to modern types. If you see an _t, it's probably safe to assume it's a type of some sort.
