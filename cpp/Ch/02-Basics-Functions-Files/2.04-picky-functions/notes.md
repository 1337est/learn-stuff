## Fickle functions have parameters and arguments

A simple way to explain parameters and arguments is through code examples:

```cpp
#include <iostream>

int getValueFromUser()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

// This function won't compile
void printDouble()
{
    std::cout << num << " doubled is: " << num * 2 << '\n';
}

int main()
{
    int num { getValueFromUser() };

    printDouble();

    return 0;
}
```

The function `printDouble()` has no way of knowing what identifier `num` is.

Even if you were to define `num` as a variable inside function `printDouble()`:
```cpp
void printDouble()
{
    int num{}; // added this
    std::cout << num << " doubled is: " << num * 2 << '\n';
}
```
The reason this won't compile either is because `printDouble()` doesn't have a way to access the value the user entered.

What we need is a way to pass t he value of variable `num` to the function `printDouble` so that `printDouble` can use the value in the function body.

- **function parameter:** is a variable value used in the header of a function, whose value is initialized by the caller of the function.

```cpp
// This function takes no parameters
// It does not rely on the caller for anything
void doPrint()
{
    std::cout << "In doPrint()\n";
}

// This funciton takes one integer parameter named x
// The caller will supply the value of x
void printValue(int x)
{
    std::cout << x << '\n';
}

// This function has 2 integer parameters, one named x, and one named y
// The caller will supply the value of both x and y
int add(int x, int y)
{
    return x + y;
}
```

- **argument:** is a value that is passed in _from_ the caller to the function when a function call is made.

```cpp
doPrint(); // this call has no arguments
printValue(6); // 6 is the argument passed to function printValue()
add(2, 3); // 2 and 3 are the arguments passed to function add(), which returns 2 + 3
```

As you can see, multiple arguments are separated by commas.

## Putting is all together

**pass by value:** The value passed in by a function call, using copy initialization to copy the value of each argument to the matching parameter.

```cpp
#include <iostream>

//This funciton has 2 integer parameters, one named x, and one named y
// The values of x and y are passed in by the caller
void printValues(int x, int y)
{
    std::cout << x << '\n';
    std::cout << y << '\n';
}

int main()
{
    printValues(6, 7); // function call with 2 arguments, 6 & 7

    return 0;
}
```

**Note:** The number of arguments must match the number of function parameters, or the compiler will throw an error.

## Rewriting our beginning program with args and params

```cpp
#include <iostream>

int getValueFromUser()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

void printDouble(int value) // This function now has an integer parameter
{
    std::cout << value << " doubled is: " << value * 2 << '\n';
}

int main()
{
    int num { getValueFromUser() };

    printDouble(num);

    return 0;
}
```

The above program is easy to follow if you start from `main()`.

There's a simpler way to write the above program as well:
```cpp
#include <iostream>

int getValueFromUser()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

void printDouble(int value)
{
    std::cout << value << " doubled is: " << value * 2 << '\n';
}

int main()
{
    printDouble(getValueFromUser());

    return 0;
}
```

The function call to `printDouble()` has an argument as another function call to `getValueFromUser()`. We use the return value from `getValueFromUser` as the argument to `printDouble`.

**Note:** Careful using this syntax. Although this isn't too compact, this can become a slippery slope to being compact for more complex code.


