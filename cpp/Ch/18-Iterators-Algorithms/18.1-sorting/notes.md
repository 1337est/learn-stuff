## How sorting works

To swap 2 elements, we can use the `std::swap()` function from the C++ standard library inside the `<utility>` header file:
```cpp
#include <iostream>
#include <utility>

int main()
{
    int x{ 2 };
    int y{ 4 };
    std::cout << "Before swap: x = " << x << ", y = " << y << '\n';
    std::swap(x, y); // swap the values of x and y
    std::cout << "After swap:  x = " << x << ", y = " << y << '\n';

    return 0;
}
```

```
Before swap: x = 2, y = 4
After swap:  x = 4, y = 2
```

## Selection sort

1. Starting at array index 0, search the entire array to find the smallest value
2. Swap the smallest value found in the array with the value at index 0
3. Repeat steps 1 & 2 starting from the next index

Here is an example of this algorithm working on 5 elements. Let’s start with a sample array:

{ 30, 50, 20, 10, 40 }

First, we find the smallest element, starting from index 0:
{ 30, 50, 20, **10**, 40 }

We then swap this with the element at index 0:
{ **10**, 50, 20, **30**, 40 }

Now that the first element is sorted, we can ignore it. Now, we find the smallest element, starting from index 1:
{ 10, 50, **20**, 30, 40 }

And swap it with the element in index 1:
{ 10, **20**, **50**, 30, 40 }

Now we can ignore the first two elements. Find the smallest element starting at index 2:
{ 10, 20, 50, **30**, 40 }

And swap it with the element in index 2:
{ 10, 20, **30**, **50**, 40 }

Find the smallest element starting at index 3:
{ 10, 20, 30, 50, **40** }

And swap it with the element in index 3:
{ 10, 20, 30, **40**, **50** }

Finally, find the smallest element starting at index 4:
{ 10, 20, 30, 40, **50** }

And swap it with the element in index 4 (which doesn't do anything):
{ 10, 20, 30, 40, **50** }

Done!

{ 10, 20, 30, 40, 50 }

## Selection sort in C++

```cpp
#include <iostream>
#include <iterator>
#include <utility>

int main()
{
	int array[]{ 30, 50, 20, 10, 40 };
	constexpr int length{ static_cast<int>(std::size(array)) };

	// Step through each element of the array
	// (except the last one, which will already be sorted by the time we get there)
	for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
	{
		// smallestIndex is the index of the smallest element we’ve encountered this iteration
		// Start by assuming the smallest element is the first element of this iteration
		int smallestIndex{ startIndex };

		// Then look for a smaller element in the rest of the array
		for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
		{
			// If we've found an element that is smaller than our previously found smallest
			if (array[currentIndex] < array[smallestIndex])
				// then keep track of it
				smallestIndex = currentIndex;
		}

		// smallestIndex is now the index of the smallest element in the remaining array
                // swap our start element with our smallest element (this sorts it into the correct place)
		std::swap(array[startIndex], array[smallestIndex]);
	}

	// Now that the whole array is sorted, print our sorted array as proof it works
	for (int index{ 0 }; index < length; ++index)
		std::cout << array[index] << ' ';

	std::cout << '\n';

	return 0;
}
```

I don't think this needs further explanation beyond the comments.

## std::sort

Sorting arrays is common, and therefore C++ has a library included that includes sorting functions named `std::sort` and is in the `<algorithm>` header file:
```cpp
#include <algorithm> // for std::sort
#include <iostream>
#include <iterator> // for std::size

int main()
{
	int array[]{ 30, 50, 20, 10, 40 };

	std::sort(std::begin(array), std::end(array));

	for (int i{ 0 }; i < static_cast<int>(std::size(array)); ++i)
		std::cout << array[i] << ' ';

	std::cout << '\n';

	return 0;
}
```

By default, `std::sort` sorts in ascending order using `operator<` to compare pairs of elements and swapping them if necessary (much like our hand rolled selection sort example above).
