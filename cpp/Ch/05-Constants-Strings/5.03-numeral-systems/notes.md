Numeral systems is a fancy name for a collection of symbols used to represent numbers. There's 4 main numeral systems in C++ which are: decimal (base 10), binary (base 2), hexadecimal (base 16), and octal (base 8).

## Octal and hexadecimal literals

To use an octal literal, prefix your literal with a 0 (zero):
```cpp
#include <iostream>

int main()
{
    int x{ 012 }; // 0 before the number means this is octal
    std::cout << x << '\n';
    return 0;
}
```

This program prints: `10` because numbers are output in decimal by default, and 12 octal = 10 decimal.

Octal isn't ever used, and we recommend you never use it.

**Hexadecimal** is base 16 and is actually used in the world.

Counting in hexadecimal is like 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, 10, 11, etc..

You can also use lowercase letters, but uppercase is more common.
To use hexadecimal literals, prefix your literal with 0x:
```cpp
#include <iostream>

int main()
{
    int x{ 0xF }; // 0x before the number means this is hexadecimal
    std::cout << x << '\n';
    return 0;
}
```

This program prints: `15`. You can also use 0X instead of 0x, but 0x is easier to read.

## Using hexadecimal to represent binary

A hexadecimal digit consists of 16 values, which can encompass 4 bits. Consequently, a pair of hexadecimal digits can be used to exactly represent a full byte:

Hexadecimal | Binary
------------|-------
0           | 0000
1           | 0001
2           | 0010
3           | 0011
4           | 0100
5           | 0101
6           | 0110
7           | 0111
8           | 1000
9           | 1001
A           | 1010
B           | 1011
C           | 1100
D           | 1101
E           | 1110
F           | 1111

## Binary literals
Prior to C++14, there was no support for binary literals. Hexadecimal literals provided a useful workaround that may still be seen today in existing code bases:

```cpp
#include <iostream>

int main()
{
    int bin{};      // assume 16-bit ints
    bin = 0x0001;   // assign binary 0000 0000 0000 0001 to the variable
    bin = 0x0002; // assign binary 0000 0000 0000 0010 to the variable
    bin = 0x0004; // assign binary 0000 0000 0000 0100 to the variable
    bin = 0x0008; // assign binary 0000 0000 0000 1000 to the variable
    bin = 0x0010; // assign binary 0000 0000 0001 0000 to the variable
    bin = 0x0020; // assign binary 0000 0000 0010 0000 to the variable
    bin = 0x0040; // assign binary 0000 0000 0100 0000 to the variable
    bin = 0x0080; // assign binary 0000 0000 1000 0000 to the variable
    bin = 0x00FF; // assign binary 0000 0000 1111 1111 to the variable
    bin = 0x00B3; // assign binary 0000 0000 1011 0011 to the variable
    bin = 0xF770; // assign binary 1111 0111 0111 0000 to the variable

    return 0;
}
```

However, in C++14 and onward, we can use the 0b prefix:
```cpp
#include <iostream>

int main()
{
    int bin{};        // assume 16-bit ints
    bin = 0b1;        // assign binary 0000 0000 0000 0001 to the variable
    bin = 0b11;       // assign binary 0000 0000 0000 0011 to the variable
    bin = 0b1010;     // assign binary 0000 0000 0000 1010 to the variable
    bin = 0b11110000; // assign binary 0000 0000 1111 0000 to the variable

    return 0;
}
```

## Digit separators

Because long literals can be hard to read, C++ 14 also added the ability to use quotation marks (') as a digit separator.

```cpp
#include <iostream>

int main()
{
    int bin { 0b1011'0010 };  // assign binary 1011 0010 to the variable
    long value { 2'132'673'462 }; // much easier to read than 2132673462
    int bin { 0b'1011'0010 };  // error: ' used before first digit of value

    return 0;
}
```

## Outputting values in decimal, octal, or hexadecimal

You can format the output via the `std::dec`, `std::oct`, and `std::hex` I/O manipulators:

```cpp
#include <iostream>

int main()
{
    int x { 12 };
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    std::cout << x << '\n'; // now hexadecimal
    std::cout << std::oct << x << '\n'; // octal
    std::cout << std::dec << x << '\n'; // return to decimal
    std::cout << x << '\n'; // decimal

    return 0;
}
```

Outputs:
```
12
c
c
14
12
12
```

## Outputting values in binary

`std::cout` doesn't come with the capability to output values in binary. C++ has `std::bitset` that will do this for us (in the <bitset> header file). The `std::bitset` can be initialized with an integral value in any format including decimal, octal, hex, or binary.

```cpp
#include <bitset> // for std::bitset
#include <iostream>

int main()
{
	// std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
	std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

	std::cout << bin1 << '\n' << bin2 << '\n';
	std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset, prints it, then discards it

	return 0;
}
```

Outputs:
```
11000101
11000101
1010
```


