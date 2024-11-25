`std::vector` has a significant difference to most other array types: it can resize itself after it has been instantiated

## Fixed-size arrays vs dynamic arrays

- A **fixed-size/fixed-length array** is an array whose length must be known at the point of instantiation, and then cannot be changed. Both `std::array` and `C-style arrays` are fixed-size arrays.
- A **dynamic/resizable array** is an array whose size can be changed after instantiation. This is what makes `std::vector` special.

## Resizing a `std::vector` at runtime

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector v{ 0, 1, 2 }; // create vector with 3 elements
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(5);              // resize to 5 elements
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```


```
The length is: 3
The length is: 5
0 1 2 0 0
```

We resize by calling the `resize()` member function with the new desired length.

2 things to note:
1. After resizing, the existing element values were preserved
2. The new elements are value-initialized (default-initialized for class types, and zero-initialized for other types).

Vectors can also be resized smaller:
```cpp
#include <iostream>
#include <vector>

void printLength(const std::vector<int>& v)
{
	std::cout << "The length is: "	<< v.size() << '\n';
}

int main()
{
    std::vector v{ 0, 1, 2, 3, 4 }; // length is initially 5
    printLength(v);

    v.resize(3);                    // resize to 3 elements
    printLength(v);

    for (int i : v)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

```
The length is: 5
The length is: 3
0 1 2
```

## The length vs capacity of a `std::vector`

In the context of a `std::vector`, **capacity** is how many elements the `std::vector` has allocated storage for, and **length** is how many elements are currently being used.

A vector can have a capacity of 5 and contains 2 elements in active use. The length (size) is 2, and the remaining 3 elements have memory allocated for them, but they are not considered to be in active use.

## Getting the capacity of a `std::vector`

We use the `capacity()` member function:
```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{
    std::vector v{ 0, 1, 2 }; // length is initially 3

    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    v.resize(5); // resize to 5 elements

    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```

```
Capacity: 3  Length: 3
0 1 2
Capacity: 5  Length: 5
0 1 2 0 0
```

## Shrinking a `std::vector`

You may have deduced that the capacity increases with the length increases, but not the other way around. If we started at Capacity 5 and wanted to go from Length 5 to Length 3, the Capacity would still be 5.

To help address this issue, `std::vector` has a member function called `shrink_to_fit()` that requests that the vector shrink its capacity to match its length:
```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{

	std::vector<int> v(1000); // allocate room for 1000 elements
	printCapLen(v);

	v.resize(0); // resize to 0 elements
	printCapLen(v);

	v.shrink_to_fit();
	printCapLen(v);

	return 0;
}
```


