You can do this with arrays:
```cpp
#include <array>
#include <iostream>
#include <vector>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array valarr { x, y };   // an array of int values
    [[maybe_unused]] std::vector ptrarr { &x, &y }; // a vector of int pointers

    return 0;
}
```

Arrays aren't references, and therefore you cannot make an array of references. The elements of an array must also be assignable, and references can't be reseated.
```cpp
#include <array>
#include <iostream>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // compile error: cannot define array of references

    int& ref1 { x };
    int& ref2 { y };
    [[maybe_unused]] std::array valarr { ref1, ref2 }; // ok: this is actually a std::array<int, 2>, not an array of references

    return 0;
}
```

There is a workaround.

## `std::reference_wrapper`

`std::reference_wrapper` is a standard library class that lives in the `<functional>` header file. It takes a type template argument T, andthen behaves like a modifiable lvalue reference to T.

Notable things about `std::reference_wrapper`:
- `Operator=` will reseat a `std::reference_wrapper`
- `std::reference_wrapper<T>` will implicitly convert to `T&`
- The `get()` member function can be used to get `T&`. This is useful when we want to update the value of the object being referenced.
```cpp
#include <array>
#include <functional> // for std::reference_wrapper
#include <iostream>

int main()
{
    int x { 1 };
    int y { 2 };
    int z { 3 };

    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };

    arr[1].get() = 5; // modify the object in array element 1

    std::cout << arr[1] << y << '\n'; // show that we modified arr[1] and y, prints 55

    return 0;
}
```

This example prints:
```
55
```

Note that we must use `arr[1].get() = 5` and not `arr[1] = 5`. This is because the latter is ambiguous and the compiler can't tell if we want to reseat the `std::reference_wrapper<int>` to value 5 (something that's illegal anyways) or change the value being referenced. Using `get()`, disambiguates this.

## `std::ref` and `std::cref`

Prior to CTAD, we did this:
```cpp
int x { 5 };
auto ref { std::ref(x) };   // C++11, deduces to std::reference_wrapper<int>
auto cref { std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>
```

Using CTAD to make our lives easier we can do this:
```cpp
std::reference_wrapper ref1 { x };        // C++17
auto ref2 { std::reference_wrapper{ x }}; // C++17
```

