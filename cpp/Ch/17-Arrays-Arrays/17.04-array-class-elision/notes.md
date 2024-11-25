The elements of a `std::array` can be any object type, including compound types. This means you can have an array of pointers, or structs, or even classes.

## Defining and assigning to a `std::array` of structs

Let's see it in action with a struct:
```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    std::array<House, 3> houses{};

    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
```
```
House number 13 has 7 rooms.
House number 14 has 10 rooms.
House number 15 has 8 rooms.
```

## Initializing a `std::array` of structs

We can take this a step further and combine the declaration and initialization steps:
```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    constexpr std::array houses { // use CTAD to deduce template arguments <House, 3>
            House{ 13, 1, 7 },
            House{ 14, 2, 5 },
            House{ 15, 2, 4 }
        };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
            << " has " << (house.stories * house.roomsPerStory)
            << " rooms.\n";
    }

    return 0;
}
```

## Brace elision for aggregates

See this code?
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 }; // single braces

    for (const auto n : arr)
        std::cout << n << '\n';

    return 0;
}
```

You can also write it like so:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }}; // double braces

    for (const auto n : arr)
        std::cout << n << '\n';

    return 0;
}
```

The extra set of braces comes from how a `std::array` is defined as a struct that contains a single C-style array member like so:
```cpp
template<typename T, std::size_t N>
struct array
{
    T implementation_defined_name[N]; // a C-style array with N elements of type T
}
```

So if we were to try and do something like this:
```cpp
// Doesn't work
constexpr std::array<House, 3> houses { // initializer for houses
    { 13, 1, 7 }, // initializer for C-style array member with implementation_defined_name
    { 14, 2, 5 }, // ?
    { 15, 2, 4 }  // ?
};
```

The compiler basically interprets `{ 13, 1, 7 }` as the initializer for the first member of `houses`, which is the C-style array with the implementation defined name. Then the rest of the members will be zero initialized (since we said there'll be 3). Then the compiler will see that we provided 2 more initialization values (the `?`) and produce a compilation error stating we've provided too many initialization values. However, if we provided another set of curly braces:
```cpp
// This works as expected
constexpr std::array<House, 3> houses { // initializer for houses
    { // extra set of braces to initialize the C-style array member with implementation_defined_name
        { 13, 4, 30 }, // initializer for array element 0
        { 14, 3, 10 }, // initializer for array element 1
        { 15, 3, 40 }, // initializer for array element 2
     }
};
```

The reason we usually only provide a single brace is because of **brace elision**, which lays out some rules for when multiple braces may be omitted. However, we can of course, explicitly use them as well.
