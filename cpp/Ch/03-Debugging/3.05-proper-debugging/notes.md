## Conditionalizing your debugging code

Instead of having print statements which requires you to remove/comment them out when you're done with them, you can conditionalize using preprocessor directives:
```cpp
// wrong way with print statements
#include <iostream>

int getUserInput()
{
std::cerr << "getUserInput() called\n";
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
std::cerr << "main() called\n";
    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0;
}
```

```cpp
// Right way with preprocessor directives
#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
#ifdef ENABLE_DEBUG
std::cerr << "getUserInput() called\n";
#endif
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
#ifdef ENABLE_DEBUG
std::cerr << "main() called\n";
#endif
    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0;
}
```

Now we can simply enable/disable debugging by leaving in/commenting out the `#define ENABLE_DEBUG` statement.

Moreover, for a large multi-file program, the `#define ENABLE_DEBUG` statement would go into a separate header file that can access all the files independently from one location.

This fixes the issue of removing debug statements but still leaves a bit of clutter.

## Using a frogger.. Err, I mean logger :frog:

- A **log** is a sequential record of events that have happened, usually time-stamped. The art of generating a log is called **logging**.

C++ actually has a standard output stream named `std::clog` that is intended to be used for writing logging information. However, by default, `std::clog` writes to the standard error stream (same as `std::cerr`). AND WHILE YOU CAN redirect it to a file instead, you're probably better off using an existing 3rd party logging tool.
