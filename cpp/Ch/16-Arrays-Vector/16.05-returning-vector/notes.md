When we pass a `std::vector` to a function, we pass it by const reference, so that we don't make an expensive copy of the array data. Therefore, it's okay to return a `std::vector` by value.

## Copy semantics

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    std::vector arr2 { arr1 };          // copies arr1 into arr2

    arr1[0] = 6; // We can continue to use arr1
    arr2[0] = 7; // and we can continue to use arr2

    std::cout << arr1[0] << arr2[0] << '\n';

    return 0;
}
```

When `arr2` is initialized with `arr1`, the copy constructor of `std::vector` is called, which copies `arr1` into `arr2`.

The term **copy semantics** refers to the rules that determine how copies of objects are made. When we say a type supports copy semantics, we mean that object of that type are copyable.

## Intro to move semantics

When ownership of data is transferred form one object to another, we say that data has been **moved** and the cost of a move is typically trivial (usually 2-3 pointer assignments, which is faster than copying an array of data).

**Move semantics** refers to the rules that determine how data from one object is moved to another object. When move semantics is invoked, any data member that can be moved is moved, and any data member that can't be moved is copied.

Consider this example:
```cpp
#include <iostream>
#include <vector>

std::vector<int> generate() // return by value
{
    // We're intentionally using a named object here so mandatory copy elision doesn't apply
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    return arr1;
}

int main()
{
    std::vector arr2 { generate() }; // the return value of generate() dies at the end of the expression

    // There is no way to use the return value of generate() here
    arr2[0] = 7; // we only have access to arr2

    std::cout << arr2[0] << '\n';

    return 0;
}
```

When we create our copy of `arr1` into `arr2`, we are creating a temporary object `arr1` from function `generate()`. Because the temporary (and its data) will be destroyed at the end of the expression, we need some way to get the data out of the temporary and into `arr2`. We could use copy semantics and make an expensive copy so `arr2` gets its own data, but why don't we use move semantics instead?

Well how do we use move semantics?

## How move semantics is invoked

Normally, when an object is being initialized with or assigned an object of the same type, copy semantics will be used. However, when all of the following is true, move semantics will be automatically invoked instead:
- The type of the object supports move semantics.
    - `std::vector` and `std::string` only
- The initializer or object being assigned from is an rvalue (temporary) object.
- The move isn't elided.

Therefore, if we return by value (which returns an rvalue), and if the returned type is `std::vector` or `std::string`, then the returned value can be moved instead of copied into the destination object which is extremely inexpensive.

