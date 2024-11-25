# Intro to if statements

The simplest if statement takes the following form:

`if (condition) true_statement;`. However, this would be formatted better.

A **condition** or **conditional expression** evaluates to a Boolean value.

An if statement with an else takes the form:

`if (condition) true_statement; else false_statement;`. Of course, this would be formatted better as well..

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x == 0)
        std::cout << "The value is zero\n";
    else
        std::cout << "The value is non-zero\n";

    return 0;
}
```

Depending on the input, this is the output:
```
Enter an integer: 0
The value is zero
```
```
Enter an integer: 5
The value is non-zero
```

## Chaining if statements

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x > 0)
        std::cout << "The value is positive\n";
    else if (x < 0)
        std::cout << "The value is negative\n";
    else
        std::cout << "The value is zero\n";

    return 0;
}
```

Various outputs dependant on inputs:
```
Enter an integer: 4
The value is positive
```
```
Enter an integer: -3
The value is negative
```
```
Enter an integer: 0
The value is zero
```

## Non-Boolean conditionals

THIS IS SOMETHING I NEVER UNDERSTOOD BEFORE.

Non-zero values get converted to Boolean true, and zero-values get converted to Boolean false.

I'm sure you've seen this before and didn't understand why it works, well now you do:

```cpp
#include <iostream>

int main()
{
    if (4) // nonsensical, but gets converted to true and is for the sake of example
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}
```

The above prints "hi", because 4 is a non-zero value that gets converted to Boolean true, causing the statement attached to the if block, to execute.

## If-statements and early returns

When combining if-statements with early returns, we can conditionalize the return value of our functions.
```cpp
#include <iostream>

// returns the absolute value of x
int abs(int x)
{
    if (x < 0)
        return -x; // early return (only when x < 0)

    return x;
}

int main()
{
    std::cout << abs(4) << '\n'; // prints 4
    std::cout << abs(-3) << '\n'; // prints 3, which is --3

    return 0;
}
```

**Note:** You never need an if-statement of the form:
```cpp
if (condition)
  return true;
else
  return false;
```
This can simply be replaced by the single statement `return condition`, since it'll return either true or false anyways.

Example:
```cpp
bool isAllowedToTakeFunRide()
{
  std::cout << "How tall are you? (cm)\n";

  double height{};
  std::cin >> height;

  if (height >= 140.0)
    return true;
  else
    return false;
}
```
Can be replaced by:
```cpp
bool isAllowedToTakeFunRide()
{
  std::cout << "How tall are you? (cm)\n";

  double height{};
  std::cin >> height;

  return height >= 140.0; // This either returns true or false anyways
}
```


