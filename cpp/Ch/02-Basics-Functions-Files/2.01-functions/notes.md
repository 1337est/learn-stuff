## Start with vocabulary!

- **function**: a reusable sequance of statements designed to do something.
- **user-defined functions**: Functions that you write yourself and are not predefined in the C++ standard library, or other functions defined, NOT by you. Huh, who woulda thunk it?
- **function call**: an expression that tells the CPU to STOP... go do that thing, then come back and continue doing your thing. yeh.

```cpp
// Example of a user-defined function
returnType function Name() // This is the function header (tells the compiler about the existence of the function)
{
    // This is the function body (tells the compiler what the function does)
}
```

Pretty simple and straightforward. This isn't rocket science! Although, that can probably be boiled down and easy to digest as well. You can learn anything! Wow, you're pretty smart huh?

- **function header**: tells the compiler about the existence of a function, the function's name, and other info like return type and parameter types.

**_NOTE:_** We'll use _returnType_ of _int_ or _void_ for now.

- **function body**: Everything between the curly braces and determines what the function does.

```cpp
// exmaple program
#include <iostream> // for std::cout

// user defined function
void doPrint() // doPrint() is the called function
{
    std::cout << "In doPrint()\n";
}

// Definition of function main()
int main()
{
    std::cout << "Starting main()\n";
    doPrint(); // Interrupt main() by making a function call to doPrint(). main() is the caller.
    std::cout << "Ending main()\n";

    return 0;
}
```
The output of this program would be
```
Starting main()
In doPrint()
Ending main()
```
The above program is self explanatory. You can evoke a function as many times in another function. You can imagine how multiple functions can be called in another function or a function that calls a different function, therefore a chain of function calls.

- **_NOTE:_** Nested functions are not supported. The following is not allowed:
```cpp
#include <iostream>

int main()
{
    void foo() // Illegal: This function is nested inside function main(). Straight to jail!
    {
        std::cout << "foo!\n"; // Cause you a foo for doing this!
    }

    foo(); // function call to foo()
    return 0;
}
```

The proper way to achieve the above program is:
```cpp
#include <iostream>

void foo() // moved outside of main()
{
    std::cout << "foo!\n";
}

int main()
{
    foo();
    return 0;
}
```

## Function return values (for those that do return values!)
Make sure to write a return value for functions that you want to return a value... Basically, functions are enclosed environments and definitions in said function will not transfer once the function is terminated. Make sure your function returns what you expect in the caller function.

- **return type**: the type of value that will be returned.
- **void return type**: the function has no value to return to the caller.
- **int return type**: the function returns type int to the caller.
- **return statement**: return 0 is what we've been using for main()
- **return value**: the 0 in return 0...

- **_NOTE:_** You should define your `main()` function at the bottom of your code file, below other functions, and avoid calling it explicitly.

- **status code, exit code, (rarely) return code**: return value from `main()` is sometimes called this. By definition, a status code of `0` means the program executed successfully.

- **_NOTE:_** `main()` will implicitly return 0 if no return statement is provided. Still, it's best practice to explicitly return a value from `main`.
