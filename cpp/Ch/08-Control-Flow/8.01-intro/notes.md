# Control flow introduction

Consider the following program:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;

    std::cout << "You entered " << x << '\n';

    return 0;
}
```

The following program only executes lines within main that contain information linearly. This is called a **straight-line program**, and the specific sequence of statements that the CPU executes is called the program's **execution path**.

However, programs are hardly ever run linearly.

Therefore, C++ allows a number of **control flow statements**, which allows the programmer to change the normal path of execution through the program.

When a control flow statement causes point of execution to change to a non-sequential statement, this is called **branching**.

Anything that makes the program jump to a previous line or skip the next line(s) to a later line, would be considered a flow control statement.
