- **integer:** An integral type that can represent positive and negative whole numbers.

C++ has 4 primary fundamental integer types available:
1. `short int` with a minimum of 16 bits
2. `int` with a minimum of 16 bits, but typically has 32 bits on modern architectures
3. `long int` with a minimum of 32 bits
4. `long long int` with a minimum of 64 bits

An example of a number having a sign is like +3 or -3 (positive 3 or negative 3). By default, integers in C++ are signed, meaning that the number's sign is stored as part of the number.

## Defining signed integers

Here is the preferred way to define the 4 types of signed integers:
```cpp
short s; // prefer "short" over "short int"
int i;
long l; // prefer "long" over "long int"
long long ll; // prefer "long long" over "long long int"
```

An integer type can also take an optional "signed" keyword, which by convention is typically placed before the type name:
```cpp
// REDUNDANTLY REDUNDANT!
signed short ss;
signed int si;
signed long sl;
signed long long sll;
```

It is however, unconventional to use this as it is redundant since integers are signed by default.

- **range:** still holds its mathematical meaning. It's the set of values that the data type can hold.

The range is determined by 2 factors: its size (in bits), and whether it is signed or not.

- An 8-bit signed integer has a range of -128 to 127.
- A 16-bit signed integer has a range of -32,768 to 32,767
- A 32-bit signed integer has a range of -2,147,483,648 to 2,147,483,647
- A 64 bit signed integer has a range of -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
- An n-bit signed integer has a range of -(2<sup>n-1</sup>) to (2<sup>n-1</sup> - 1).

## Overflow

Overflow is when a number goes out of range.

Integer overflow example:
```cpp
#include <iostream>

int main()
{
    // assume 4 byte integers
    int x { 2'147'483'647 }; // the maximum value of a 4-byte signed integer
    std::cout << x << '\n';

    x = x + 1; // integer overflow, undefined behavior
    std::cout << x << '\n';

    return 0;
}
```

Output may be different on different machines:
```cpp
2147483647
-2147483648
```

## Integer division

Integer division will drop any remainder (not round). Therefore, 9/5 (which should be 1.8 or rounded to 2), will result in 1.

```cpp
#include <iostream>

int main()
{
    std::cout << 8 / 5 << '\n';
    return 0;
}
```
Produces:
```cpp
1
```


