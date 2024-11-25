## Let's learn more about memory

An object's size can take up more than 1 byte of memory. A single object can take 1, 2, 4, 8, or MORE consecutive memory addresses. The size of the allocation is determined by the data type.

Bits can store values of 2^#bits. E.g. An object that uses 2 bytes (1 byte = 8 bits) can hold 2^16 (65536) different values.

Since computers have a finite resource of memory, it's notable to try and use the least amount of memory when possible.

## Fundamental data types and memory

Here's a list of data types and their associated byte sizes:

Category    | Type              | Minimum Size  | Typical Size  | Note
---------   |------             |-------------- |-------------- |-----
Boolean     | bool              | 1 byte        | 1 byte        |
character   | char              | 1 byte        | 1 byte        |  always exactly 1 byte
character   | wchar_t           | 1 byte        | 2 or 4 bytes  |
character   | char8_t           | 1 byte        | 1 byte        |
character   | char16_t          | 2 bytes       | 2 bytes       |
character   | char32_t          | 4 bytes       | 4 bytes       |
integer     | short             | 2 bytes       | 2 bytes       |
integer     | int               | 2 bytes       | 4 bytes       |
integer     | long              | 4 bytes       | 4 or 8 bytes  |
integer     | long long         | 8 bytes       | 8 bytes       |
floating    | float             | 4 bytes       | 4 bytes       |
floating    | double            | 8 bytes       | 8 bytes       |
floating    | long double       | 8 bytes       | 8, 12, or 16 bytes |
pointer     | std::nullptr_t    | 4 bytes       | 1 byte        |

It's best to assume the minimum size to increase maximum portability.

## `sizeof` operator

The `sizeof` operator is a unary operator that takes in either a type or variable, and returns the size in bytes.

Trying to use the `sizeof` operator on incomplete types (such as void) will result in a compilation error.

```cpp
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>

int main()
{
    std::cout << std::left; // left justify output
    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
    std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
    std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
    std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
    std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
    std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
    std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
    std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
    std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

    return 0;
}
```

```cpp
#include <iostream>

int main()
{
    int x{};
    std::cout << "x is " << sizeof(x) << " bytes\n";

    return 0;
}
```

## An interesting note:
Types that use less memory are not always faster than types that use more memory. CPUs are often optimized to process data of a certain size (like 32 bits), and types that MATCH that size, may actually be processed quicker. I.e., a 32-bit machine could process a 32-bit int faster than a 16-bit short or 8-bit char.
