## What is pointer arithmetic?

**Pointer arithmetic** is a feature that allows us to apply certain integer arithmetic operators (addition, subtraction, increment, or decrement) to a pointer to produce a new memory address.

Given some pointer `ptr`, `ptr + 1` returns the address of the next object in memory (based on the type being pointed to).

```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << ' ' << (ptr + 1) << ' ' << (ptr + 2) << '\n';

    return 0;
}
```

Makes sense.

```
00AFFD80 00AFFD84 00AFFD88
```

The same applies for subtraction.

Applying the increment `++` and decrement `--` operators to a pointer actually modifies the address held by the pointer by pointing to a new address (+1 or -1, etc):
```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << '\n';

    ++ptr; // ptr = ptr + 1
    std::cout << ptr << '\n';

    --ptr; // ptr = ptr - 1
    std::cout << ptr << '\n';

    return 0;
}
```

Makes sense.

```
00AFFD80 00AFFD84 00AFFD80
```

## Subscripting is implemented via pointer arithmetic

The subscript `operator[]` is a concise syntax equivalent to the more verbose expression `*((ptr) + (n))`. This is just pointer arithmetic with extra parenthesis to keep our order of operations the same and an explicit dereference to get the object at that address.

```cpp
#include <iostream>

int main()
{
    const int arr[] { 3, 2, 1 };

    // First, let's use subscripting to get the address and values of our array elements
    std::cout << &arr[0] << ' ' << &arr[1] << ' ' << &arr[2] << '\n';
    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

    // Now let's do the equivalent using pointer arithmetic
    std::cout << arr<< ' ' << (arr+ 1) << ' ' << (arr+ 2) << '\n';
    std::cout << *arr<< ' ' << *(arr+ 1) << ' ' << *(arr+ 2) << '\n';

    return 0;
}
```

```
00AFFD80 00AFFD84 00AFFD88
3 2 1
00AFFD80 00AFFD84 00AFFD88
3 2 1
```

## Pointer arithmetic and subscripting are relative addresses

When we assign a pointer to an array, it takes on the first element in the array by default and if pointed at a different element in the array, pointer arithmetic will be relative to the current position of the pointer:
```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };
    const int *ptr { arr }; // arr decays into a pointer to element 0

    // Prove that we're pointing at element 0
    std::cout << *ptr << ptr[0] << '\n'; // prints 99
    // Prove that ptr[1] is element 1
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 88

    // Now set ptr to point at element 3
    ptr = &arr[3];

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[1] is element 4!
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 55

    return 0;
}
```

## Negative indices

We've covered that `*(ptr+1)` return the next object in memory and `ptr[1]` is a convenient syntax to do the same, but can be also go backwards through subtraction? Yes we can:
```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    // Set ptr to point at element 3
    const int* ptr { &arr[3] };

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[-1] is element 2!
    std::cout << *(ptr-1) << ptr[-1] << '\n'; // prints 77

    return 0;
}
```

## Pointer arithmetic can be used to traverse an array

We can use the memory addresses to traverse an array to skip passing the actual array to a function:
```cpp
#include <iostream>

void printArray(const int* begin, const int* end)
{
	for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' '; // dereference our loop variable to get the current element
	}

	std::cout << '\n';
}

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	printArray(begin, end);

	return 0;
}
```

Note how we never passed the array, just the memory addresses associated with the array. This works because our memory addresses are being dereferenced and we are getting the actual array element values associated with the addresses of the array.


