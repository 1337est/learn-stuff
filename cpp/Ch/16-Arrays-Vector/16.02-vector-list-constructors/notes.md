## Introduction to `std::vector`

`std::vector` is a container class that implements an array and is defined in the `<vector>` header file and is defined as a class template, with a template type parameter that defines the type of the elements:
```cpp
#include <vector>

int main()
{
	// Value initialization (uses default constructor)
	std::vector<int> empty{}; // vector containing 0 int elements

	return 0;
}
```

## Initializing a `std::vector` with a list of values

```cpp
#include <vector>

int main()
{
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

	return 0;
}
```

## List constructors and initializer lists

An initializer list is a braced list of comma-separated values (e.g. `{ 1, 2, 3 }` ) and containers typically have a special constructor called a **list constructor** that allows us to construct an instance of the container using an initializer list.

The list constructor does 3 things:
1. Ensures the container has enough storage to hold all the initialization values (if needed).
2. Sets the length of the container to the number of elements in the initializer list (if needed).
3. Initializes the elements to the values in the initializer list (in sequential order).

Therefore when we provide a container with an initializer list of values, the list constructor is called, and the container is constructed using that list of values.

## Accessing array elements using the subscript operator (`operator[]`)

In C++, the most common way to access array elements is by using the name of the array along with the subscript operator (`operator[]`). To select a specific element, inside the square brackets of the subscript operator, we provide an integral value that identifies which element we want to select. This integral value is called a **subscript** (or informally, an **index**).

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "The first prime number is: " << primes[0] << '\n';
    std::cout << "The second prime number is: " << primes[1] << '\n';
    std::cout << "The sum of the first 5 primes is: " << primes[0] + primes[1] + primes[2] + primes[3] + primes[4] << '\n';

    return 0;
}
```

This prints:
```
The first prime number is: 2
The second prime number is: 3
The sum of the first 5 primes is: 28
```

## Subscript out of bounds

`operator[]` does not do any kind of **bounds checking**, meaning it won't know if the index is within the bounds of 0 to N-1 (inclusive). Passing an invalid index to `operator[]` will return undefined behavior.

## Arrays are contiguous in memory

This illustrates how elements are always allocated contiguously in memory:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
```

This outputs:
```
An int is 4 bytes
00DBF720
00DBF724
00DBF728
```

## Constructing a `std::vector` of a specific length

`std::vector` has an explicit constructor `explicit std::vector<T>(std::size_t)` that takes a single `std::size_t` value defining the length of the `std::vector` to construct:
```cpp
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```

Each of the created elements are value-initialized, which for `int` is zero-initialized and for class types calls the default constructor.

## List constructors take precedence over other constructors

Consider the following snippet:
```cpp
std::vector<int> data{ 10 }; // what does this do?
```

There are 2 things that could happen:
- `{ 10 }` can be interpreted as an initializer list, and matched with the list constructor to construct a vector of length 1 with value 10.
- `{ 10 }` can be interpreted as a single braced initialization value, and matched with the `std::vector<T>(std::size_t)` constructor to construct a vector of length 10 with elements value-initialized to 0.

The compiler ends up using the first match (list constructor) since C++ has a rule that states: A matching list constructor will be selected over other matching constructors.

To help clarify, here's some other scenarios:
```cpp
// Copy init
std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error

// Direct init
std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor

// List init
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor

// Copy list init
std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor
```

- When constructing a container (or any type that has a list constructor) with initializers that are not element values, use direct initialization.

## Const and constexpr `std::vector`

Objects of type `std::vector` can be made `const`:
```cpp
#include <vector>

int main()
{
    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified

    return 0;
}
```

Of course, a `const std::vector` must be initialized, and cannot be modified.

- `std::vector` cannot be made `constexpr`. If you need a `constexpr` array, use `std::array`.
