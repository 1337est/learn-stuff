## We start again, with vocabulary!
**void**: a return type that tells the compiler that the function does not return a value.

A void function doesn't need a return statement because a void function will automatically return to the caller at the end of the function.
```cpp
#include <iostream>

// void means the functions doesn't return A VALUE to the caller
void printHi()
{
    std::cout << "Hi" << '\n';

    return; // tells the compiler to return to the caller (redundancy)
} // function returns to the caller here

int main()
{
    printHi();

    return 0; // here we need a return because the function expects an int returned (0 for success)
}
```

- **Note:** It's best practice to not put a return statement for a non-value returning function.

## When values are needed
Some types of expressions need values:
```cpp
#include <iostream>

int main()
{
    std::cout << 5; // 5 is a literal value we're sending to the console via std::cout
    std::cout << ; //compiler error: no value provided

    return 0;
}
```
The above program needs a value provided after std::cout <<, and if no value is provided, then that causes a syntax error. Now consider the following,
```cpp
#include <iostream>

// void means the function does not return a value to the caller
void printHi()
{
    std::cout << "Hi" << '\n';
}

int main()
{
    printHi(); // Call to printHi(), no value returned

    std::cout << printHi(); // compiler error... do you see why?
    return 0;
}
```
There is no value to the right of `std::cout <<` in `main`. The statement is trying to send the return value of `printHi` to `std::cout`, but because it's void, it has no return value.

In the opposite vein, you cannot return a value from a void function. I think this is self explanatory. `void` cannot `return value`, so don't even think about it wise guy.
