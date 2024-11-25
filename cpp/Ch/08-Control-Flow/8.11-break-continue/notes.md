## Break statements in context

These are the contexts depending on the syntax for break statements:

- Breaking a switch is typically for preventing fallthrough at the end of a case
```cpp
#include <iostream>

void printMath(int x, int y, char ch)
{
    switch (ch)
    {
    case '+':
        std::cout << x << " + " << y << " = " << x + y << '\n';
        break; // don't fall-through to next case
    case '-':
        std::cout << x << " - " << y << " = " << x - y << '\n';
        break; // don't fall-through to next case
    case '*':
        std::cout << x << " * " << y << " = " << x * y << '\n';
        break; // don't fall-through to next case
    case '/':
        std::cout << x << " / " << y << " = " << x / y << '\n';
        break;
    }
}

int main()
{
    printMath(2, 3, '+');

    return 0;
}
```

- Breaking a loop is typically for ending a loop early with execution continuing after the loop
```cpp
#include <iostream>

int main()
{
    int sum{ 0 };

    // Allow the user to enter up to 10 numbers
    for (int count{ 0 }; count < 10; ++count)
    {
        std::cout << "Enter a number to add, or 0 to exit: ";
        int num{};
        std::cin >> num;

        // exit loop if user enters 0
        if (num == 0)
            break; // exit the loop now

        // otherwise add number to our sum
        sum += num;
    }

    // execution will continue here after the break
    std::cout << "The sum of all the numbers you entered is: " << sum << '\n';

    return 0;
}
```

```
Enter a number to add, or 0 to exit: 5
Enter a number to add, or 0 to exit: 2
Enter a number to add, or 0 to exit: 1
Enter a number to add, or 0 to exit: 0
The sum of all the numbers you entered is: 8
```

- A break exits out of the loop while a return statement exits out of the function.

## Continue statements

The continue statement is a convenient way to end the current iteration and go to the next iteration without terminating the loop.
```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is divisible by 4, skip this iteration
        if ((count % 4) == 0)
            continue; // go to next iteration

        // If the number is not divisible by 4, keep going
        std::cout << count << '\n';

        // The continue statement jumps to here
    }

    return 0;
}
```

```
1
2
3
5
6
7
9
```

- You can use break and continue when they simplify your loop logic. Otherwise, avoid.
- Use early returns when they simplify your function's logic.


