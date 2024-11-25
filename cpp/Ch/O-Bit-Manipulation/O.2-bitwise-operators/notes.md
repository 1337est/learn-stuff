## The bitwise operators `<<` and `>>`

- Bitwise left shift: `x << y` means all bits in x are shifted left by y bits.
    - 0011 << 1 is 0110
    - 0011 << 2 is 1100
    - 0011 << 3 is 1000
- Bitwise right shift: `x >> y` means all bits in x are shifted right y bits.
    - 1100 >> 1 is 0110
    - 1100 >> 2 is 0011
    - 1100 >> 3 is 0001
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> x { 0b1100 };

    std::cout << x << '\n';
    std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
    std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1000

    return 0;
}
```
Important to note that the x value doesn't change, but what we're outputting does because we're sending the output to `std::cout`.

## Operator overloading `<<` and `>>`

Typically, we use operator<< for output via `std::cout`, and operator >> for input via `std::cin`. So how does the compiler tell the difference?

Simple! When the compiler sees that the left operand of operator<< is `std::cout`, it knows that it should call the version of operator<< that `std::cout` overloaded (provided an alternate definition for) to do output instead. However, if the left operand of operator<< is an integral type, it knows that operator<< should do the usual bit-shifting behavior. The same thing applies to operator>> for `std::cin`.

## The bitwise operator NOT, OR, AND, XOR

- Bitwise NOT: `~x` flips all the bits in x
    - ~0100 is 1011
```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::cout << ~std::bitset<4>{ 0b0100 } << ' ' << ~std::bitset<8>{ 0b0100 } << '\n';

	return 0;
}
```

- Bitwise OR: `x | y` produces `z` with any bits matched between `x` OR `y` as turned on
    - 0101 | 0110 is 0111
```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::cout << (std::bitset<4>{ 0b0101 } | std::bitset<4>{ 0b0110 }) << '\n';

	return 0;
}
```

- Bitwise AND: `x & y` produces `z` with any bits matched between `x` AND `y` as turned on
    - 0101 & 0110 is 0100
```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::cout << (std::bitset<4>{ 0b0101 } & std::bitset<4>{ 0b0110 }) << '\n';

	return 0;
}
```

- Bitwise XOR: `x ^ y` produces `z` with any odd number of bits turned on between `x` AND `y`
    - 0110 ^ 0011 is 0101
    - 0001 ^ 0011 ^ 0111 is 0101
    - 0001 ^ 0011 ^ 0111 ^ 1111 is 1010

## Bitwise assignment operators

You can use `<<=`, `>>=`, `|=`, `&=`, and `^=` if you want to change the variable that holds the bits in a more compact way.

Ex:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> bits { 0b0100 };
    bits >>= 1;
    std::cout << bits << '\n';

    return 0;
}
```


