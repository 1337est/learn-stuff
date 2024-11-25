As you know, sometimes the returned/printed output isn't exactly what you would call "ordinary" or perhaps "desired".

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(5);    // okay: prints 5
    printInt('a');  // prints 97 -- does this make sense?
    printInt(true); // print 1 -- does this make sense?

    return 0;
}
```

```
5
97
1
```

Here you would expect 5 for the first function call, but the others are probably not desired (or maybe they are). Let's assume we don't think the call to `printInt()` with value of type `char` or `bool` makes much sense. What can we do?

## Deleting a function using the `= delete` specifier

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // calls to this function will halt compilation
void printInt(bool) = delete; // calls to this function will halt compilation

int main()
{
    printInt(97);   // okay

    printInt('a');  // compile error: function deleted
    printInt(true); // compile error: function deleted

    printInt(5.0);  // compile error: ambiguous match

    return 0;
}
```

Here, `= delete` means "I forbid this", not "this doesn't exist".
