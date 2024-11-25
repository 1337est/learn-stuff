## Diving into the deep end
"When you stare into the abyss, the abyss stares back at you" - Friedrich Nietzsche

When you compile your project, each .cpp file goes through a preprocessing phase where a program called **preprocessor** makes various changes to the text of the code file. Rather than modifying the original code files, the preprocessor changes are either temporarily in-memory or use temporary files.

Most of what the preprocessor does it uninteresting. It strips out comments, ensures each code file ends in a newline, etc. However, it also is what processes the `#include` directives!

The result of a preprocessor processing a code file is a **translation unit**. The **translation unit** is actually what is compiled by the compiler. The entire process of 1. preprocessing, 2. compiling, and 3. linking, is called **translation**.

## Preprocessor directives

**Preprocessor directives** (often times called "directives"), are instructions that start with a # symbol and end with a newline instead of a semicolon.

When the preprocessor runs a program that `#include's <something>`, the preprocessor replaces the `#include <something>` with the contents of  the file named "something" and  then preprocess the included content and the rest of the file.

Once the preprocessor has finished processing the code file and the #included content, the result is the **translation unit**. The **translation unit** contains both the code from the code file, and the processed code from all the #included files.

## Macro defines
There is a #define directive that can be used in C++ to create a macro. A macro is a rule that defines how input text is converted into a replacement output text.

There are 2 basic types of macros: object-like macros, and function-like macros.

- **function-like macros:** act like functions, and serve a similar purpose. These macros are considered unsafe and almost anything they can do, can also be done with a normal function.
- **object-like macros:** can be defined in 2 ways:
```cpp
#define IDENTIFIER
#define IDENTIFIER substitute_text
```

By convention, macro names are typically all upper-case, separated by underscores.

## Object-like macros with substitution text
Consider the following:
```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';
    return 0;
}
```

The preprocessor converts the above into the following:
```cpp
// The contents of iostream are inserted here

int main()
{
    std::cout << "My name is: " << "Alex" << '\n';
    return 0;
}
```

**Note:** Object-like macros with substitution text should generally now only be seen in legacy code. It's recommended to avoid using these kinds of macros altogether since there's better ways to do these things which will be learned about later.

## Object-like macros without substitution text

Consider the following:

```cpp
#define USE_YEN
```

Macros like this work as you might expect them too: any further occurences of the identifier is removed and replaced by nothing. This form is generally considered acceptable to use.

## Conditional compilation

I've seen these quite a bit before. There are a few different conditional compilation directives, but the 3 main ones used are: #ifdef, #ifndef, and #endif.

The #ifdef preprocessor directive allows the preprocessor to check whether an identifier has been previously #defined. If so, the code between #ifdef and #endif is compiled. If not, the code is ignored.

```cpp
#include <iostream>

#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif

    return 0;
}
```

#ifndef is the opposite of #ifdef, in that the check is whether it's NOT been #defined yet.
```cpp
#include <iostream>

int main()
{
#ifndef PRINT_BOB
    std::cout << "Bob\n"; // will be compiled since PRINT_BOB was never #defined
#endif

    return 0;
}
```

You may also see `#if defined(PRINT_BOB)` and `if !defined(PRINT_BOB)`. These do the same thing but use a more C++-style syntax.

## if 0

Another common usage of conditional compilation involves `#if 0` to exclude code from being compiled as if it were inside a comment block.

```cpp
#include <iostream>

int main()
{
    std::cout << "Joe\n";

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    std::cout << "Steve\n";
#endif // until this point

    return 0;
}
```

Only Joe will be printed above because Bob and Steve are in the if 0 preprocessor directive.

The `#if 0` preprocessor directive provides a convenient way to comment out code that contains multi-line comments

To temporarily re-enable code that was wrapped in an `#if 0`, you can change it to `#if 1`.

## The scope of #defines

Directives are resolved before compilation, from top to bottom, on a file-by-file basis.

Consider the following:
```cpp
#include <iostream>

void foo()
{
#define MY_NAME "Alex"
}

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n';

	return 0;
}
```

Even though `#define MY_NAME "Alex"` looks like it's defined in function foo, the preprocessor doesn't understand C++ concepts like functions, and therefore the program behaves as if the #define was either before or after function foo (but not before #include). To avoid confusion, write you #define identifiers outside of functions.

## A slight introduction to header files

Because an #include directive replaces the #include directive with the contents of the included file, and #include can copy directives from the included file into the current file, the following program can also be written:
```cpp
// Alex.h
#define MY_NAME "Alex"
```
```cpp
// main.cpp
#include "Alex.h" // copies #define MY_NAME from Alex.h here
#include <iostream>

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n'; // preprocessor replaces MY_NAME with "Alex"

    return 0;
}
```

## Understand this
Directives defined in one dile do not have any impact on other files (unless they are #included into another file).

```cpp
// function.cpp
#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!\n";
#endif
#ifndef PRINT
    std::cout << "Not printing!\n";
#endif
}
```
```cpp
// main.cpp
void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();

    return 0;
}
```

The above program will print `Not printing!` because event though PRINT was defined in main.cpp, that has no impact on any of the code in function.cpp. PRINT is only #defined from the point of definition to the end of main.cpp.
