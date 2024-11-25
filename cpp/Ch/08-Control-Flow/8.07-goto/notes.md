A certain control flow statement that causes execution to jump to another spot in the code is called an unconditional jump.

In C++, and unconditional jump is implemented via a **goto statement**, and the spot to jump to is identified through use of a **statement label**.

```cpp
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
    return 0;
}
```

```
Enter a non-negative number: -4
Enter a non-negative number: 4
The square root of 4 is 2
```

Pretty straightforward.

## Statement labels have function scope

We've covered local (block) and file (global) scope. However, statement labels utilize a third type of scope: **function scope**, which means the label is visible throughout the function even before its point of declaration. Furthermore, the `goto` statement and its corresponding statement label must appear in the same function.

```cpp
#include <iostream>

void printCats(bool skip)
{
    if (skip)
        goto end; // jump forward; statement label 'end' is visible here due to it having function scope

    std::cout << "cats\n";
end:
    ; // statement labels must be associated with a statement
}

int main()
{
    printCats(true);  // jumps over the print statement and doesn't print anything
    printCats(false); // prints "cats"

    return 0;
}
```

We're able to jump to `end` before `end` was declared, because statement labels have function scope.

DON'T USE GOTO STATEMENTS UNLESS YOU WANT TO BE SHUNNED. It's considered bad practice to use `goto` statements because it creates spaghetti code.


