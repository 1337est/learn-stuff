# Bit flags and bit manipulation via std::bitset

- True and false take up 1 byte (8 bits), but only use 1 bit, leaving the other 7 bits unused.
- Bit manipulation is mostly important for graphics, encryption, compression, and optimization programming contexts.

## Bit flags

Variables hold values, but they can also be understood as holding a collection of individual bits. When these individual bits  of a variable/object are used as Boolean values (true/false, on/off), the bits are called **bit flags**.

We can use `std::bitset` to define a set of bit flags, or typically an unsigned integer of the appropriate size (8, 16, 32, etc)bits.

```cpp
#include <bitset> // for std::bitset

std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags
```

- When given a sequence of bits, `1111'0000`, we typically start numbering right to left, starting with an index of 0. Therefore, the indices or the sequence above would be `[7654'3210]`.

## Manipulating bits via `std::bitset`

`std::bitset` provides 4 key member functions that are useful for doing bit manipulation:
- test() allows us to query whether a bit is 0 or 1
- set() allows us to turn a bit on (1)
- reset() allows us to turn a bit off (0)
- flip() allows us to flip a bit value from 0 to 1, or vice versa.
- size() returns the number of bits in the bitset
- count() returns the number of bits in the bitset that are set to true
- all() returns a Boolean indicating whether all bits are set to true
- any() returns a Boolean indicating whether any bits are set to true (>=1 bit on = true)
- none() returns a Boolean indicating whether no bits are set to true (all off = true)

```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    bits.set(3);   // set bit position 3 to 1 (now we have 0000 1101)
    bits.flip(4);  // flip bit 4 (now we have 0001 1101)
    bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << bits<< '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
    std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

    return 0;
}
```

```
All the bits: 00001101
Bit 3 has value: 1
Bit 4 has value: 0
```

## The size of `std::bitset`

`std::bitset` is optimized for speed, not memory savings. The size of `std::bitset` is typically the number of bytes needed to hold the bits, rounded up to the nearest sizeof(size_t), so 4 bytes on 32-bit machines, and 8 bytes on 64-bit machines.


