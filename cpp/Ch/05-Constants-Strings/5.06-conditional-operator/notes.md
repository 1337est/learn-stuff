An if-else statement takes the format:
```
if (condition)
    statement1;
else
    statement2;
```

The conditional operator `?:` takes the following form:
```
condition ? expression1 : expression2;
```
If the condition evaluates to true, expression1 executes, otherwise expression 2 executes.

The following if-else can be rewritten:

```cpp
if (x > y)
    greater = x;
else
    greater = y;
```

Rewritten:
```cpp
greater = ((x > y) ? x : y);
```

Confused yet? Look at it more until you got it. Pretty straightforward after you've swapped things in your brain.

## An example to illustrate the use

Consider the following:
```cpp
#include <iostream>

int main()
{
    constexpr bool inBigClassroom { false };
    constexpr int classSize { inBigClassroom ? 30 : 20 };
    std::cout << "The class size is: " << classSize << '\n';

    return 0;
}
```
The "direct" if-else replacement would be this:
```cpp
#include <iostream>

int main()
{
    constexpr bool inBigClassroom { false };

    if (inBigClassroom)
        constexpr int classSize { 30 };
    else
        constexpr int classSize { 20 };

    std::cout << "The class size is: " << classSize << '\n';

    return 0;
}
```

However, this doesn't compile because `classSize` isn't defined due to the variable dying at the end of the if-else-statement. There's also a more complicated way to write this with an if-else statement, but why do that when the conditional works better.

**Note:**
- Make sure that your types match when passing in the second and third operands
```cpp
#include <iostream>

int main()
{
    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int

    std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double

    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range

    return 0;
}
```

```
1
2.2
4294967295
```

- The conditional operator is best used in less complicated expressions.
