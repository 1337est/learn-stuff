When we define an enumeration, each enumerator is automatically associated with an integer value based on its position in the enumerator list:
```cpp
enum Color
{
    black,   // 0
    red,     // 1
    blue,    // 2
    green,   // 3
    white,   // 4
    cyan,    // 5
    yellow,  // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue }; // shirt actually stores integral value 2

    return 0;
}
```

It's possible to explicitly define the value of enumerators. These values can be positive or negative, can share the same values as other enumerators, and non-defined enumerators are given values +1 greater than the previous enumerator:
```cpp
enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};
```

When enumerators share the same value, the enumerators become non-distinct -- they are essentially interchangeable (e.g. `horse` and `giraffe` are interchangeable).

- Avoid assigning explicit values to your enumerators unless you have a compelling reason to do so.

## Value-initializing an enumeration

If an enumeration is zero-initialized (which happens when we use value-initialization), the enumeration will be given value `0`, even when there isn't a corresponding enumerator with that value:
```cpp
#include <iostream>

enum Animal
{
    cat = -3,    // -3
    dog,         // -2
    pig,         // -1
    // note: no enumerator with value 0 in this list
    horse = 5,   // 5
    giraffe = 5, // 5
    chicken,     // 6
};

int main()
{
    Animal a {}; // value-initialization zero-initializes a to value 0
    std::cout << a; // prints 0

    return 0;
}
```

- If there is an enumerator with value 0, value-initialization defaults the enumeration to the meaning of that enumerator (`black` for our `Color` example). It's a good idea to make the enumerator with value `0` the one that represent the best default meaning:
```cpp
enum Winner
{
    winnerUnknown, // default value (0)
    player1,
    player2,
};

// somewhere later in your code
if (w == winnerUnknown) // handle case appropriately
```

## Unscoped enumerations will implicitly convert to integral values

Consider the following program:
```cpp
#include <iostream>

enum Color
{
    black, // assigned 0
    red, // assigned 1
    blue, // assigned 2
    green, // assigned 3
    white, // assigned 4
    cyan, // assigned 5
    yellow, // assigned 6
    magenta, // assigned 7
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n'; // what does this do?

    return 0;
}
```

What do you think this prints?
```
Your shirt is 2
```

Probably not what we wanted right?

When an enumerated type is used in a function call or with an operator, the compiler will try to find a function or operator that matches the enumerated type. So when the compiler sees `std::cout << shirt`, the compiler tries to see if `operator<<` knows how to print an object of type `Color`. Well, it doesn't.

Since the compiler can't find a match, it will then check if `operator<<` knows how to print an object of the integral type that the unscoped enumeration converts to. It does this and we get `2`.

## Enumeration size and underlying type (base)

Enumerations have values that are of integral types, but what integral type? In most compiler's it's `int` as the underlying type, but you shouldn't assume this across all compilers and platforms.

It's possible to explicitly specify an underlying type for an enumeration (which must be an integral type):
```cpp
#include <cstdint>  // for std::int8_t
#include <iostream>

// Use an 8-bit integer as the enum underlying type
enum Color : std::int8_t
{
    black,
    red,
    blue,
};

int main()
{
    Color c{ black };
    std::cout << sizeof(c) << '\n'; // prints 1 (byte)

    return 0;
}
```

- Specify the base type of an enumeration only when necessary.

## Integer to unscoped enumerator conversion

The compiler will implicitly convert an unscoped enumeration to an integer (i.e. first first index to 0, second index to 1, etc). But the compiler will not implicitly convert an integer to an unscoped enumeration:
```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
    pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

    return 0;
}
```

There are 2 ways to work around this:
1. You can explicitly convert an integer to an unscoped enumerator using `static_cast`:
```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
    pet = static_cast<Pet>(3);       // our pig evolved into a whale!

    return 0;
}
```

2. As of C++17, if an unscoped enumeration has an explicitly specified base, then the compiler will allow you to list initialize an unscoped enumeration using an integral value:
```cpp
enum Pet: int // we've specified a base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet1 { 2 }; // ok: can brace initialize unscoped enumeration with specified base with integer (C++17)
    Pet pet2 (2);   // compile error: cannot direct initialize with integer
    Pet pet3 = 2;   // compile error: cannot copy initialize with integer

    pet1 = 3;       // compile error: cannot assign with integer

    return 0;
}
```


