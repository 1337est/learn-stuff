Because traversing (forwards) through an array is a common task, C++ supports another type of for-loop called a **range-based for loop** (also called a **for-each loop**) that allows traversal of a container without having to do explicit indexing. Range-based for loops are simpler, safer, and work with all the common array types in C++.

## Range-based for loops

The range-based for statement has this syntax:
```
for (element_declaration : array_object)
    statement;
```
A range-based for loop will iterate through each element in the `array_object` and for each iteration, the value of the current array element will be assigned to the variable declared in `element_declaration`, and then `statement` will execute.

Here's a simple example that uses a range-based for loop to print all the elements in an array:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (int num : fibonacci) // iterate over array fibonacci and copy each value into `num`
       std::cout << num << ' '; // print the current value of `num`

    std::cout << '\n';

    return 0;
}
```
Here the output is what you would expect:
```
0 1 1 2 3 5 8 13 21 34 55 89
```

Note that this doesn't require us to use the array's length, nor does it require us to index the array! Hallelujah!

- Favor range-based for loops over regular for-loops when traversing containers

## Range-based for loops and type deduction using the `auto` keyword

Because `element_declaration` should have the same type as the array elements (to prevent type conversion), this is the ideal scenario for the `auto` keyword, and let the compiler deduce the type of the array elements for us:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (auto num : fibonacci) // compiler will deduce type of num to be `int`
       std::cout << num << ' ';

    std::cout << '\n';

    return 0;
}
```

- Use type deduction (`auto`) with range-based for loops to have the compiler deduce the type of the array element.

## Avoid element copies by using references

Consider the following for an array of `std::string`:
```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

    for (auto word : words)
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

For each iteration, the `std::string` element from the `words` array will be copied into the variable `word` which is expensive. Pass by const reference instead:
```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

    for (const auto& word : words) // word is now a const reference
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

## When to use `auto` vs `auto&` vs `const auto&`

In general:
- `auto` for cheap-to-copy types
- `auto&` when we want to modify the elements
- `const auto&` for expensive-to-copy types

However, for range-based for loops, prefer to define the element type as:
- `auto` when you want to modify copies of the elements
- `auto&` when you want to modify the original elements
- `const auto&` otherwise (when you just need to view the original elements)

## Range-based for loops in reverse (C++20)

As of C++20, you can use the `std::views::reverse` capability of the Ranges library to create a reverse view of the elements that can be traversed:
```cpp
#include <iostream>
#include <ranges> // C++20
#include <string_view>
#include <vector>

int main()
{
    std::vector<std::string_view> words{ "Alex", "Bobby", "Chad", "Dave" }; // sorted in alphabetical order

    for (const auto& word : std::views::reverse(words)) // create a reverse view
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

```
Dave
Chad
Bobby
Alex
```


