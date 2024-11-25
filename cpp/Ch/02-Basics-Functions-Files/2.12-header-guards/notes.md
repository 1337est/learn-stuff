## The duplicate definition problem

We're talking about the one definition rule (ODR) here, where a program that defines a variable identifier more than once will cause a compile error.
```cpp
int main()
{
    int x; // this is a definition for variable x
    intn x; // compile error: duplicate definition

    return 0;
}
```

Similarly the ODR for functions:
```cpp
#include <iostream>

int foo() // this is a definition for function foo
{
    return 5;
}

int foo() // compile error: duplicate definition
{
    return 5;
}

int main()
{
    std::cout << foo();
    return 0;
}
```

While these are simple problems to fix in a file, these issues can creep up when a header file #includes another header file.

Consider the obvious fault in this program:
```cpp
// square.h
int getSquareSides()
{
    return 4;
}
```
```cpp
// wave.h
#include "square.h"
```
```cpp
// main.cpp
#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}
```

As you can see, square.h get's preprocessed into main.cpp twice and then there's a duplicate definition compile error.

Now, if wave.h needs getSquareSides(), and main.cpp needs both wave.h and square.h, how do we resolve the issue?

## Header guards

We can avoid the above problem using a **header guard** (also called an **include guard**). A **header guard** is a conditional compilation directive that takes the following form:

```cpp
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```

When this header is #included, the preprocessor will check whether SOME_UNIQUE_NAME_HERE has been previously defined in this translation unit. If this is the first time we're including the header, then SOME_UNIQUE_NAME_HERE will not have been defined. CONSEQUENTLY, it #defines it and includes the contents of the file. If the header is included again into the same file, SOME_UNIQUE_NAME_HERE, will already have been defined from the first time the contents of the header were included, and the contents of the header will be ignored thanks to the #ifndef.

Basically, the first time `#ifndef` is encountered is true, so it continues evaluates the first time, and then the `#define` handles the initial defining. If a silly thing happens and the header tries to get included again from a different file, the `#ifndef` will say "You are defined. Therefore I return as false. Go to the #endif matching pair", because the declarations already happened once in the initial `#define` section.

All header files should have header guards on them. By convention the name of SOME_UNIQUE_NAME_HERE is set to the full filename of the header file, typed in call caps, using underscores for spacing or punctuation.

## Using Header guards

Now back to the previous problem but now with header guards:
```cpp
// square.h
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
        return 4;
}

#endif
```
```cpp
// wave.h
#ifndef WAVE_H
#define WAVE_H

#include "square.h"

#endif
```
```cpp
// main.cpp
#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}
```
```cpp
// main.cpp after preprocessor resolves the #include directives
// Square.h included from main.cpp
#ifndef SQUARE_H // square.h included from main.cpp
#define SQUARE_H // SQUARE_H gets defined here

// and all this content gets included
int getSquareSides()
{
        return 4;
}

#endif

#ifndef WAVE_H // wave.h included from main.cpp
#define WAVE_H
#ifndef SQUARE_H // square.h included from wave.h, SQUARE_H is already defined from above
#define SQUARE_H // so none of this content gets included

int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H
#endif // WAVE_H

int main()
{
    return 0;
}
```

## Header guards don't prevent a header file from being included once into different code files

Note that the header guards don't prevent a given header from being included (once) into separate code files.

```cpp
// square.h
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter

#endif
```
```cpp
// square.cpp
#include "square.h"  // square.h is included once here

int getSquarePerimeter(int sideLength)
{
    return sideLength * getSquareSides();
}
```
```cpp
// main.cpp
#include "square.h" // square.h is also included once here
#include <iostream>

int main()
{
    std::cout << "a square has " << getSquareSides() << " sides\n";
    std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n';

    return 0;
}
```

Follow that since you compile both main.cpp and square.cpp, and they will compile without issue since they are separate files, you will still have 2 functions of `int getSquareSides()` (I thought you weren't supposed to define functions in header files? lol ok). Basically, the linker will complain here, and  the solution to this problem is to move the function to the .cpp file instead while just leaving the forward declarations in the header file.

```cpp
// square.h
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides(); // forward declaration for getSquareSides
int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter

#endif
```
```cpp
// square.cpp
#include "square.h"

int getSquareSides() // actual definition for getSquareSides
{
    return 4;
}

int getSquarePerimeter(int sideLength)
{
    return sideLength * getSquareSides();
}
```
```cpp
// main.cpp
#include "square.h" // square.h is also included once here
#include <iostream>

int main()
{
    std::cout << "a square has " << getSquareSides() << " sides\n";
    std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n';

    return 0;
}
```

## #pragma once
Modern compilers support a simpler, alternate form of header guards using the `#pragma` preprocessor directive:
```cpp
#pragma once

// your code here
```

`#pragma once` serves the same purpose as header guards: to avoid a header file form being included multiple times. With traditional header guards, it's the developer's responsibility to guard the header. With `#pragma once`, we're asking that the compiler guard the header. How exactly it does this is an implementation-specific detail.

For most projects, `#pragma once` works fine, and many developers now prefer it because it's easier and less error-prone.

Note that since `#pragma` is compiler specific, do not expect a pragma that works on one compiler to be supported by another.

Because `#pragma once` is not defined by the C++ standard library, it is possible that some compilers may not implement it. However, support for `#pragma once` is fairly ubiquitous and it is generally accepted in modern C++.
