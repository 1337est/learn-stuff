Many new programmers spend a ton of time writing their own loops to perform relatively simple tasks. The C++ standard library comes with extremely efficient functions that are very optimized and the functionality provided in the algorithms library generally fall into one of 3 categories:
1. **Inspectors** -- Used to view data in a container
2. **Mutators** -- Used to modify data in a container
3. **Facilitators** -- Used to generate a result based on values of the data members.

## Using `std::find` to find an element by value

`std::find` searches for the first occurrence of a value in a container, returns an iterator pointing to the element (or the end of the container if the element isn't found), and takes 3 parameters:
- An iterator to the starting element in the sequence
- An iterator to the ending element in the sequence
- The value to search for

```cpp
#include <algorithm>
#include <array>
#include <iostream>

int main()
{
    std::array arr{ 13, 90, 99, 5, 40, 80 };

    std::cout << "Enter a value to search for and replace with: ";
    int search{};
    int replace{};
    std::cin >> search >> replace;

    // Input validation omitted

    // std::find returns an iterator pointing to the found element (or the end of the container)
    // we'll store it in a variable, using type inference to deduce the type of
    // the iterator (since we don't care)
    auto found{ std::find(arr.begin(), arr.end(), search) };

    // Algorithms that don't find what they were looking for return the end iterator.
    // We can access it by using the end() member function.
    if (found == arr.end())
    {
        std::cout << "Could not find " << search << '\n';
    }
    else
    {
        // Override the found element.
        *found = replace;
    }

    for (int i : arr)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

Sample run when successfully finds element:
```
Enter a value to search for and replace with: 5 234
13 90 99 234 40 80
```

Sample run when failed to find element:
```
Enter a value to search for and replace with: 0 234
Could not find 0
13 90 99 5 40 80
```

## Using `std::count` and `std::count_if` to count occurrences of an element

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

bool containsNut(std::string_view str)
{
	return (str.find("nut") != std::string_view::npos);
}

int main()
{
	std::array<std::string_view, 5> arr{ "apple", "banana", "walnut", "lemon", "peanut" };

	auto nuts{ std::count_if(arr.begin(), arr.end(), containsNut) };

	std::cout << "Counted " << nuts << " nut(s)\n";

	return 0;
}
```

```
Counted 2 nut(s)
```

## Using `std::sort` to custom sort

Since `std::sort` sorts an array in ascending order, you can roll your own function to manipulate the output you desire:
```cpp
#include <algorithm>
#include <array>
#include <iostream>

bool greater(int a, int b)
{
    // Order @a before @b if @a is greater than @b.
    return (a > b);
}

int main()
{
    std::array arr{ 13, 90, 99, 5, 40, 80 };

    // Pass greater to std::sort
    std::sort(arr.begin(), arr.end(), greater);

    for (int i : arr)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

## Using `std::for_each` to do something to all elements of a container

This function takes a list as input and applies a custom function to every element:
```cpp
#include <algorithm>
#include <array>
#include <iostream>

void doubleNumber(int& i)
{
    i *= 2;
}

int main()
{
    std::array arr{ 1, 2, 3, 4 };

    std::for_each(arr.begin(), arr.end(), doubleNumber);

    for (int i : arr)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

## Ranges in C++20
Having to explicitly pass `arr.begin()` and `arr.end()` to every algorithm is a bit annoying. But fear not -- C++20 adds ranges, which allow us to simply pass `arr`. This will make our code even shorter and more readable.
