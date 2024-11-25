Consider this program using if-else statements:

```cpp
#include <iostream>

void printDigitName(int x)
{
    if (x == 1)
        std::cout << "One";
    else if (x == 2)
        std::cout << "Two";
    else if (x == 3)
        std::cout << "Three";
    else
        std::cout << "Unknown";
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

The above code sucks.

Above we are trying to test a variable/expression against a SET of different values. Consider using a **switch statement** instead, since that's what a switch statement is designed to be used for:

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x)
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

Each `case` above is checked against the `switch` value to see if there's a match, and the statements for a match are executed. If no match is found, the `default` labels statements are executed. Simple!

- The only restriction of switch statements is that the condition must evaluate to an integral type or an enumerated type OR be convertible to one. That means expressions that evaluate to floating types, strings, and most other non-integral types can't be used for switch statements.

## No matching case label or default case

If there's no match and no default case, then execution continues after the end of the switch block:

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 5
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    // no matching case exists and there is no default case
    } // so execution continues here

        // and "Hello" is printed
        std::cout << "Hello";
}

int main()
{
    printDigitName(5);
    std::cout << '\n';

    return 0;
}
```

## Taking a break

That sounds nice, thank you.

Instead of using a return statement, we can use a **break statement** by declaring the `break` keyword which tells the compiler we are done executing statements in the switch and continues execution with the statement after the end of the switch block.

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x evaluates to 3
    {
    case 1:
        std::cout << "One";
        break;
    case 2:
        std::cout << "Two";
        break;
    case 3:
        std::cout << "Three"; // execution starts here
        break; // jump to the end of the switch block
    default:
        std::cout << "Unknown";
        break;
    }

    // execution continues here
    std::cout << " Ah-Ah-Ah!";
}

int main()
{
    printDigitName(3);
    std::cout << '\n';

    return 0;
}
```

```
Three Ah-Ah-Ah!
```

Count Dracula? 1 Vat, 2 Vats, 3 Vats, Ah-Ah-Ah!


