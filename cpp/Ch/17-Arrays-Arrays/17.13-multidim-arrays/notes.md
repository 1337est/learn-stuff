Let's look at multidimensional `std::array` since c-style arrays should be avoided:

```cpp
std::array<std::array<int, 4>, 3> arr {{  // note double braces
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 }}};
```

It's pretty obvious what's going on here, but the syntax is verbose and ugly:
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t Row, std::size_t Col>
void printArray(const std::array<std::array<T, Col>, Row> &arr)
{
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::array<std::array<int, 4>, 3>  arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    printArray(arr);

    return 0;
}
```

Yucky.

## Making 2d `std::array` easier using an alias template

If we did something like this:
```cpp
using Array2dint34 = std::array<std::array<int, 4>, 3>;
```

We'd need to create an alias for every combination we'd want (not just for 3x4, what if we wanted 9x9 and 10x50?)

Let's use an alias template:
```cpp
// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;
```

Now we can do this:
```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

// When using Array2d as a function parameter, we need to respecify the template parameters
template <typename T, std::size_t Row, std::size_t Col>
void printArray(const Array2d<T, Row, Col> &arr)
{
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    printArray(arr);

    return 0;
}
```

## Getting the dimensional lengths of a 2d array

```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    std::cout << "Rows: " << arr.size() << '\n';    // get length of first dimension (rows)
    std::cout << "Cols: " << arr[0].size() << '\n'; // get length of second dimension (cols), undefined behavior if length of first dimension is zero!

    return 0;
}
```

This makes sense following logically.

However, what's smarter is doing this instead:
```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

// Fetch the number of rows from the Row non-type template parameter
template <typename T, std::size_t Row, std::size_t Col>
constexpr int rowLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Row;
}

// Fetch the number of cols from the Col non-type template parameter
template <typename T, std::size_t Row, std::size_t Col>
constexpr int colLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Col;
}

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    std::cout << "Rows: " << rowLength(arr) << '\n'; // get length of first dimension (rows)
    std::cout << "Cols: " << colLength(arr) << '\n'; // get length of second dimension (cols)

    return 0;
}
```

Since we know the parameters we're passing into `arr` are the Rows and Columns, we can simply use the templates Row and Col to give us the dimensions of the array we're passing.


