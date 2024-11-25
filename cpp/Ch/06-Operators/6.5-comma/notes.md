- (x, y) evaluates x then y, and returns the value of y.

```cpp
#include <iostream>

int main()
{
    int x{ 1 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand

    return 0;
}
```

The above program will print 3 to the console, because the rightmost operand after evaluation is 3.

- The comma operator also has the lowest precedence. That makes code like this different:
```cpp
z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.
```

- It's best to avoid using the comma operator, except within for loops.

## The comma as a separator

C++ commonly uses the comma symbol as a separator vs the operator. Some examples of the comma separator:
```cpp
void foo(int x, int y) // Separator comma used for function parameters
{
    add(x, y); // Separator comma used for function call arguments
    constexpr int z{ 3 }, w{ 5 }; // Separator comma used to separate multiple variables being defined on the same line (don't do this)
}
```


