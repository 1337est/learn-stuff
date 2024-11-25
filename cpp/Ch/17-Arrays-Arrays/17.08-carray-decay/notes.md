Somehow you can do this and it works:
```cpp
#include <iostream>

void printElementZero(int arr[1000]) // doesn't make a copy
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[7] { 5 };      // define an array with 7 elements
    printElementZero(x); // somehow works!

    return 0;
}
```

We are able to pass a 7 element array to a function expecting a 1000 element array, without any copies being made. Let's discover how this works together. But first, we need to cover 2 subtopics: array decay and 

## Array to pointer conversions (array decay)

In most cases, when a C-style array is used in an expression, the array will be implicitly converted into a pointer to the element type and initialized with the address of the first element (with index 0). This kind of makes sense, since we know that the array's starting address (not it's size) will be the address of the first index of the array. Colloquially, this is called **array decay**:
```cpp
#include <iomanip> // for std::boolalpha
#include <iostream>

int main()
{
    int arr[5]{ 9, 7, 5, 3, 1 }; // our array has elements of type int

    // First, let's prove that arr decays into an int* pointer

    auto ptr{ arr }; // evaluation causes arr to decay, type deduction should deduce type int*
    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // Prints true if the type of ptr is int*

    // Now let's prove that the pointer holds the address of the first element of the array

    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

    return 0;
}
```

This returns:
```
true
true
```

It's important to note that just because an array decays when evaluated (in most circumstances), it does not mean that C-style arrays are pointers. An array object is a sequence of elements, while a pointer holds an address. The `arr` above has type `int[5]`, whereas the decayed array has type `int*`. There is a distinction between an un-decayed array and a decayed array, and that is the key takeaway here.

## Subscripting a C-style array actually applies `operator[]` to the decayed pointer

C-style arrays decay to a pointer when evaluated, so when a C-style array is subscripted, the subscript is actually operating on the decayed array pointer:
```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };
    std::cout << arr[2]; // subscript decayed array to get element 2, prints 5

    return 0;
}
```

## Array decay solves the C-style array passing issue

When passing a C-style array as an argument, the array decays into a pointer, and what actually gets passed to the function is the pointer holding the address of the first element of the array. So, although it looks like we're passing a C-style array by value, we're passing by address.

`int[5]` and `int[7]` have different lengths and are incompatible because they are distinct types. However, they decay into the same pointer type `int*` and are interchangeable for passing arrays of different lengths without a type mismatch.

This is why we're able to do this:
```cpp
#include <iostream>

void printElementZero(const int* arr) // pass by const address
{
    std::cout << arr[0];
}

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);   // prime decays to an const int* pointer
    printElementZero(squares); // squares decays to an const int* pointer

    return 0;
}
```

```
2
1
```

However, prefer this syntax instead:
```cpp
#include <iostream>

void printElementZero(const int arr[]) // treated the same as const int*
{
    std::cout << arr[0];
}

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);  // prime decays to a pointer
    printElementZero(squares); // squares decays to a pointer

    return 0;
}
```


