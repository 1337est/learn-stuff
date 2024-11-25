- A **halt** is a flow control statement that terminates the program. In C++, halts are function calls.

When our `main()` function returns, all local variables are destroyed and function parameters are destroyed as well. Then a special function called `std::exit()` is called with the return value from `main()` as the `status code` passed in as an argument.

## The std::exit() function

`std::exit()` causes the program to terminate normally. `std::exit()` cleans up by destroying objects with static storage duration first, then any other miscellaneous file cleanup is done if any files were used. Finally, control is returned back to the OS, with the argument passed to `std::exit()` used as the `status code`.

- You can call `std::exit()` explicitly to halt your program.

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    std::cout << 1 << '\n';
    cleanup();

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```
```
1
cleanup!
```

## The std::atexit() function

`std::exit()` terminates the program immediately, but you may want to do some manual cleanup before terminating right?

C++ offers `std::atexit()` function, which allows you to specify a function that will automagically be called on program termination (via `std::exit()`)
```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

Since `std::atexit()` will automatically be called on exit, we don't have to remember to call anything before calling `std::exit()`. Also, since `std::exit()` is already implicitly called at the end of `main()`, we don't need to explicitly call `std::exit()` to take advantage of `std::atexit()` since any functions registered by `std::atexit` will execute at the end of `main()`.

## The std::abort and std::terminate functions

`std::abort()` causes your program to terminate abnormally, which means the program had some kind of unusual runtime error and the program couldn't continue to run. E.g. when you divide by 0, this is an abnormal termination.

```cpp
#include <cstdlib> // for std::abort()
#include <iostream>

int main()
{
    std::cout << 1 << '\n';
    std::abort();

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

`std::abort` does not do any cleanup

`std::terminate()` function is typically used in conjunction with `exceptions`. By default, `std::terminate()` calls `std::abort()`.

- You should almost never use a halt. Exceptions are a better and safer mechanism for handling error cases. Only halt if there is no safe or reasonable way to return normally from the main function.


