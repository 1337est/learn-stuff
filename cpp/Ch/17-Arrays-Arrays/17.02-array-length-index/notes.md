## Getting the length of a `std::array` as a constexpr value

Because the length of a `std::arrray` is constexpr, functions that return the length of a `std::array` are constexpr values.

## `std::get()` does compile-time bounds checking for constexpr indices

Since the length of a `std::array` is constexpr, if our index is also a constexpr value, then the compiler should be able to validate at compile-time that our constexpr index is within bounds of the array.

However, `operator[]` doesn't do bounds checking by definition, and the `at()` member function (the same one from vector) only does runtime bounds checking. Also, function parameters can't be constexpr, so how do we even pass a constexpr index?

To get compile-time bounds checking when we have a constexpr index, we use `std::get()` function template:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array prime{ 2, 3, 5, 7, 11 };

    std::cout << std::get<3>(prime); // print the value of element with index 3
    std::cout << std::get<9>(prime); // invalid index (compile error)

    return 0;
}
```

`std::get()` takes the index as a non-type template argument and inside `std::get()` there's also a static_assert that checks to ensure that the non-type template argument is smaller than the array length.
