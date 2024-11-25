# For statements

The most utilized loop statement in C++ is the for-statement.

There's two kinds of for-loops as of C++11, and the for-each loop will be covered in section 16.8 once we've covered some pre-requisite topics.

For-statement syntax:
```
for (init-statement; condition; end-expression)
    statement;
```

Let's look at an example for-loop:
```cpp
#include <iostream>

int main()
{
    for (int i{ 1 }; i <= 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

- Here the variable `i` is the incrementer and is initialized to 1.
- The `i <= 10` is evaluated, and since i is 1, evaluates to `true` which starts the loop.
- `i` is printed out followed by a space.
- `++i` is evaluated at the end and increments the value to 2.
- Then it checks the condition again for i <=10, which is `true` etc.

This program prints:
```
1 2 3 4 5 6 7 8 9 10
```

You can also decrement if you want with `--i`.
```cpp
#include <iostream>

int main()
{
    for (int i{ 9 }; i >= 0; --i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

Or you do any kind of iteration really:
```cpp
#include <iostream>

int main()
{
    for (int i{ 0 }; i <= 10; i += 2) // increment by 2 each iteration
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

You can swap this for multiplication, division, some modulus operator, etc.

## For-loops with multiple counters

Although for-loops typically iterate over only 1 variable, sometimes for-loops need to work with multiple variables. You can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end-expression:
```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```

This loop defines and initializes 2 new variables `x` and `y` and outputs:
```
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0
```

- Defining multiple variables (in the init-statement) and using the comma operator (in the end-expression) is acceptable inside a for-statement.





