An unsigned int has the same range without the whole numbers, meaning they have double the positive range.

- 8 bit unsigned has 0 to 255
- 16 bit unsigned has 0 to 65,535
- 32 bit unsigned has 0 to 4,294,967,295
- 64 bit unsigned has 0 to 18,446,744,073,709,551,615
- n-bit unsigned has 0 to (2<sup>n</sup>) - 1

## Unsigned integer overflow

Unsigned integer overflow has a wrapping behavior, where if an unsigned value is out of range, the modulo/remainder after the maximum value + 1 of the type is kept.

If 280 wraps around a 1 byte integer value, then `280 - (255 + 1) = 24` is kept.

Example:
```cpp
#include <iostream>

int main()
{
    unsigned short x{ 65535 }; // largest 16-bit unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = 65536; // 65536 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = 65537; // 65537 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    return 0;
}
```

Results in:
```
x was: 65535
x is now: 0
x is now: 1
```

## Controversy: unsigned numbers

Try not to use unsigned numbers where possible (can't always be done depending on what you're working on.)

Some considerations:
- When signed and unsigned numbers are operated on together, the signed component gets implicitly converted to an unsigned number. This results in unexpected behavior.

2 examples below

```cpp
// First example
#include <iostream>

// assume int is 4 bytes
int main()
{
	unsigned int u{ 2 };
	signed int s{ 3 };

	std::cout << u - s << '\n'; // 2 - 3 = 4294967295

	return 0;
}
```

```cpp
// Second example
#include <iostream>

// assume int is 4 bytes
int main()
{
    signed int s { -1 };
    unsigned int u { 1 };

    if (s < u) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
        std::cout << "-1 is less than 1\n";
    else
        std::cout << "1 is less than -1\n"; // this statement executes

    return 0;
}
```


