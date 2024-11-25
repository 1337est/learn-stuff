```
do
    statement; // can be a single statement or a compound statement
while (condition);
```

Instead of writing a traditional while statement:
```cpp
#include <iostream>

int main()
{
    // selection must be declared outside while-loop, so we can use it later
    int selection{ 0 };

    while (selection != 1 && selection != 2 &&
        selection != 3 && selection != 4)
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```

We can use a do while statement to ensure that the statement always executes at least once. This makes more sense looking at the code:

```cpp
#include <iostream>

int main()
{
    // selection must be declared outside of the do-while-loop, so we can use it later
    int selection{};

    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection < 1 || selection > 4);

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```

After the `do` statement has been executed, the `while` statement checks the condition. If the condition evaluates to `true`, the path of execution jumps back to the top of  the `do-while` loop and executes it again.


## In practice

Do-while loops aren't common and having the condition at the bottom of the loop obscures the loop condition, which can lead to errors. Many devs recommend avoiding do-while loops altogether for this reason.


