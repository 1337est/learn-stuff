## Back in my day

Back in the early days of C, computers sucked and performance was of utmost concern. C left it open so that the size of integers could be compiler implemented for an int that performs best on the target computer architecture.

As a programmer, this sucks since now we have to deal with types with uncertain ranges.

This is why it's best to assume a lower/minimum size for a data type. If you assume an int is 4 bytes because it's most likely, then when the program is run on an architecture where an int is actually 2 bytes, you'll discover overflow, and therefore undefined behavior in your program.

## Addressing the issue with C99 and C++11

To address this issue, C99 defined a set of fixed-width integers in the `stdint.h` header file.

- `std::int8_t` is 1 byte signed with range -128 to 127 and is treated like a signed char on many systems.
- `std::uint8_t` is 1 byte unsigned with range 0 to 255 and is treated like an unsigned char on many systems.
- `std::int16_t` is 2 bytes signed int
- `std::uint16_t` is 2 bytes unsigned int
- `std::int32_t` is 4 bytes signed int
- `std::uint32_t` is 4 bytes unsigned int
- `std::int64_t` is 8 bytes signed int
- `std::uint64_t` is 8 bytes unsigned int

C++ has also officially adopted these fixed-width integers as part of C++11. They can be accessed by including the `<cstdint`> header.

An example:
```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int16_t i{5};
    std::cout << i << '\n';
    return 0;
}
```

## Fast and least integers

We can go faster!

Due to system architectures, using a 32 bit integer on a 32 bit system will be faster, but depending on the program, may also eat up a bunch of RAM unnecessarily. C++ has 2 sets of alternatives that are guaranteed to be defined

- **fast types:** `std::int_fast#_t` and `std::uint_fast#_t`, where the `#` sign is replaced by 8, 16, 32, or 64.
- **least types:** `std::int_least#_t` and `std::uint_least#_t`, where the `#` sign is replaces by 8, 16, 32, or 64.

For example, `std::int_fast32_t` will give you the fastest signed integer type that's at least 32 bits. "Fastest" means the integral type that can be processed most quickly by the CPU.

`std::uint_least32_t` will give you the smallest unsigned integer type that's at least 32 bits.

Example:
```cpp
#include <cstdint> // for fast and least types
#include <iostream>

int main()
{
	std::cout << "least 8:  " << sizeof(std::int_least8_t) * 8 << " bits\n";
	std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
	std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
	std::cout << '\n';
	std::cout << "fast 8:  " << sizeof(std::int_fast8_t) * 8 << " bits\n";
	std::cout << "fast 16: " << sizeof(std::int_fast16_t) * 8 << " bits\n";
	std::cout << "fast 32: " << sizeof(std::int_fast32_t) * 8 << " bits\n";

	return 0;
}
```

Output:
```
least 8:  8 bits
least 16: 16 bits
least 32: 32 bits

fast 8:  8 bits
fast 16: 32 bits
fast 32: 32 bits
```

As you can see, `std::int_least16_t` shows 16 bits, whereas `std::int_fast16_t` produces 32 bits. This is because the author's machine processes 32-bit integers faster than 16 bit integers.

## Weird char behavior with `std::int8_t`, `std::uint8_t`, and corresponding fast/least fixed-width types

Due to an oversight in the C++ specification, most compilers define and treat `std::int8_t`, `std::uint8_t`, and the corresponding fast/least fixed-width types, as signed and unsigned chars, respectively.

It's best to use `std::int16_t` or `std::uint16_t` instead when storing integral values where the specific size is important.

## Best practices

- It's best practice to prefer `int` when the size of the integer doesn't matter.
- Prefer `std::int#_t` when storing a quantity that needs a guaranteed range
- Prefer `std::uint#_t` when doing bit manipulation or where well-defined wrap-around behavior is required.

## Avoid the following when possible
- `short` and `long` integers -- use a fixed-width type instead
- Unsigned types for holding quantities
- The 8-bit fixed-width integer type
- The fast and least fixed-width types
- Any compiler-specific fixed-width integers
