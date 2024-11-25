## Fallthrough

Execution of a switch will continue sequentially until one of the following:
1. The end of the switch block is reached.
2. Another control flow statement (like `break` or `return`) exits the block/function
3. Someone smashes your computer to bits. A common problem I'm sure.

Here is a program with a switch statement without a break or return in it:

```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }

    return 0;
}
```

```
2
3
4
5
```

This almost definitely is unintended and when an execution flows from the intended statements underneath to subsequent labels, is called **fallthrough**.

## The [[fallthrough]] attribute C++17

C++17 added the `[[fallthrough]]` attribute. **Attributes** are a modern C++ feature that allows the programmer to provide the compiler with some additional data about the code. Specifying an attribute is as simple as putting the attribute name in double brackets. Attributes are not statements and can be used almost anywhere they are contextually relevant.

The `[[fallthrough]]` attribute modifies a null statement to indicate that fallthrough is intentional:

```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }

    return 0;
}
```

```
2
3
```

## Sequential case labels

```cpp
bool isVowel(char c)
{
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        return true;
    default:
        return false;
    }
}
```

Case labels aren't statements, they're labels. If ANY CASE LABEL for our vowels match, the function will return true. Pretty neat huh? This is not considered fallthrough behavior.

## Labels do not define a new scope

Unlike if statements, switch statements do not implicitly imply a block between labels:

```cpp
switch (1)
{
case 1: // does not create an implicit block
    foo(); // this is part of the switch scope, not an implicit block to case 1
    break; // this is part of the switch scope, not an implicit block to case 1
default:
    std::cout << "default case\n";
    break;
}
```

This means you can declare or define (but not initialize) variables inside the switch, both before and after the case labels:

```cpp
switch (1)
{
    int a; // okay: definition is allowed before the case labels
    int b{ 5 }; // illegal: initialization is not allowed before the case labels

case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;

case 2:
    int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;

case 3:
    break;
}
```


