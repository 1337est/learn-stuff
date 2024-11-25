## Static local variables
- Using the `static` keyword on a local variable changes its duration from automatic to static. This means the variable is created at the start of the program and destroyed at the end of the program and the static variable will retain its value even after it goes out of scope.

Automatic duration example:
```cpp
#include <iostream>

void incrementAndPrint()
{
    int value{ 1 }; // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```
```
2
2
2
```

Static duration example:
```cpp
#include <iostream>

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```
```
2
3
4
```

Just like we use "g_" to prefix global variables, we commonly use "s_" to prefix static local variables

- It's best practice to prefer const static local variables and avoid non-const static local variables.


