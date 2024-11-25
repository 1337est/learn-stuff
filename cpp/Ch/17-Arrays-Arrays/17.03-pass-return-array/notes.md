Just like vectors, we typically pass `std::array` by const reference to avoid expensive copies:
```cpp
#include <array>
#include <iostream>

void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD deduces type std::array<int, 5>
    passByRef(arr);

    return 0;
}
```

CTAD doesn't (currently) work here so we cannot just specify `std::array` and let the compiler deduce the template argument.

## Using templates with `std::array`

Since `std::array` is defined like this:
```cpp
template<typename T, std::size_t N> // N is a non-type template parameter
struct array;
```

We can create a function template like so:
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N> // note that this template parameter declaration matches the one for std::array
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    return 0;
}
```

## Auto non-type template parameters (C++20)

Having to remember (or look up) the type of a non-type template parameter so that you can use it in a template parameter declaration for your own function template is a pain. Just use auto in C++20:
```cpp
#include <array>
#include <iostream>

template <typename T, auto N> // now using auto to deduce type of N
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    return 0;
}
```

## Returning a `std::array`

A `std::array` is not move-capable and there are 2 options you can do in order to return a `std::array`

- Return a `std::array` by value if:
    1. The array isn't huge.
    2. The element type is cheap to copy/move
    3. The code isn't being used in a performance-sensitive context

```cpp
#include <array>
#include <iostream>
#include <limits>

// return by value
template <typename T, std::size_t N>
std::array<T, N> inputArray() // return by value
{
	std::array<T, N> arr{};
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

	return arr;
}

int main()
{
	std::array<int, 5> arr { inputArray<int, 5>() };

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

## Returning a `std::array` via an out parameter

In cases where return by value is too expensive:
```cpp
#include <array>
#include <limits>
#include <iostream>

template <typename T, std::size_t N>
void inputArray(std::array<T, N>& arr) // pass by non-const reference
{
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

}

int main()
{
	std::array<int, 5> arr {};
	inputArray(arr);

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

## Returning a `std::vector` instead

Since `std::vector` is move-capable and if you're returning a `std::array` by value, then your `std::array` probably isn't constexpr and you should consider using (and returning) a `std::vector` instead.
