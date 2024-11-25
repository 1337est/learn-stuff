## Headers and their purpose

I've seen many a header files without knowing their purpose. I guess it's time to finally learn.

As programs grow larger (and make use of more files), it becomes annoying to forward declare every function you want to use that is defined in a different file. Instead, wouldn't it be nice to put all your forward declarations in one place and then just import them as needed?

C++ has another common file other than .cpp files called **header files**. These files usually have a .h (most common), .hpp, or no extension at all. The primary purpose of these are to propagate declarations to .cpp files.

**Note:** Header files allow us to put declarations in one locatoin and then import them wherever we need them. This can save a lot of typing in multi-file programs.

## Using standard library header files
Consider the following:
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}
```

`std::cout` has been forward declared in the "iostream" header file. When we `#include <iostream>`, we are in fact, requesting that the preprocessor copy all the contents from the file named "iostream" into the file using the #include.

**Note:** Mind = blown

Let's write a header file for add.cpp to replace these programs:
```cpp
// add.cpp
int add(int x, int y)
{
    return x + y;
}
```
```cpp
// main.cpp
#include <iostream>

int add(int x, int y); // forward declaration using function prototype

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```

Writing a header file is easy, as it only consists of these 2 parts:
1. A Header guard, which will be looked at in more detail in the next section.
2. The actual contents of the header file, which should be the forward declarations for all of the identifiers we want other files to be able to see.

Using the command line, header files shouldn't be added to your compile command since they are implicitly included with the `#include` statements and compiled as part of the source files.

It's best practice to prefer a .h suffix when naming header files. Also, if a header file is paired with a code file (e.g. add.h and add.cpp), then they should both have the same base name (add).

Here's the header file:

```cpp
//add.h
// 1) We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

// 2) This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!
```
Now in order to make use of this add.h header file, we need to `#include` it:
```cpp
// main.cpp
#include "add.h" // Insert contents of add.h at this point. Note use of double quotes here.
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```
```cpp
#include "add.h" // Insert contents of add.h at this point. Note use of double quotes here.

int add(int x, int y)
{
    return x + y;
}
```

## Don't include definitions in a header file due to violating one-definition rule (ODR)
If you have this program:
```cpp
// add.h
// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

// definition for add() in header file -- don't do this!
int add(int x, int y)
{
    return x + y;
}
```
```cpp
// main.cpp
#include "add.h" // Contents of add.h copied here
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';

    return 0;
}
```
```cpp
// add.cpp
#include "add.h" // Contents of add.h copied here
```

Now when the files compile, the `#include "add.h"` will be replaced by the contents of `add.h` due to the preprocessing. Let's look at these again with proper replacement:

```cpp
// main.cpp (after preprocessing)
// from add.h:
int add(int x, int y)
{
    return x + y;
}

// contents of iostream header here

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';

    return 0;
}
```
This compiles fine. Next:
```cpp
// add.cpp (after preprocessing)
int add(int x, int y)
{
    return x + y;
}
```
This compiles fine.

Now the linker runs and sees there are 2 definitions for function `add()`: one in main.cpp and one in add.cpp. This is a violation of the ODR which states, "Within a given program, a variable or normal function can only have one definition."

**Note for best practices:**
1. It's best practice to NOT put variable functions and variable definitions in your header files (for now).
2. It's also best practice for source files to `#include` their paired header files if one exists. E.g.
```cpp
// something.h
int something(int); // return type of forward declaration is int
```
```cpp
// something.cpp
#include "something.h"

void something(int) // error: wrong return type
{
}
```
3. Avoid `#including` .cpp files. If your project doesn't compile unless you #include your .cpp files, then that means your .cpp files are not being compiled as part of your project and you need to add them so they get compiled.

## Angled brackets vs double quotes
Another demystification waiting to happen...

It's possible that a header file with the same filename might exist in multiple directories and our use of angled brackets vs double quotets helps give the preprocessor a clue as to where it should look for header files.

Angled brackets tell the preprocessor that the header file is something we didn't write ourselves. The preprocessor will search for the header only in directories specified by the `include directories`. These directories are configured as either part of your project/IDE and defaults to the directories that come as part of your compiler, OR operating system (OS). The preprocessor, when using angled brackets WILL NOT look for header files in your project's source code directory.

When using double-quotes, we're telling the preprocessor that we wrote this header file ourselves, and that it should search for the header file in the current directory. If it can't find a matching header there, it'll then serach the `include directories` (where the angled brackets search is done).

**Mind = Explosion!!!**

**Note:** Use double quotes to include header files that either you've written yourself or expect to be found in the current directory. Use angled brackets to include headers that come with your compiler/OS/third-party libraries you've installed on your system.

## Including header files from other directories

One "bad" way to do this is using relative paths:
```cpp
#include "headers/myHeader.h"
#include "../moreHeaders/myOtherHeader.h"
```

A better method is to tell your compiler you have a bunch of header files in some other location. For GCC/G++ users, you can simply specify the -I option to specify an alternate include directory:

`g++ -o main -I/source/includes main.cpp`

This is better since now instead of changing every line of code where there is a relative path in case your directory/file structure changes, you just need to change the compiler setting.

## Headers that include other headers...

When your code file #includes the first header file, you'll get any other header files that the first header file includes (and any header files those include, etc. Makes sense, since it would just be a string of includes). These additional header files are sometimes called **transitive includes**, as they're included implicityly rather than explicitly.

Here's the catch: The contents of these **transitive includes** are available for use in your code file. HowEVER (yes the caps EVER was intentional cause I think it's funny), you shouldn't rely on these headers that are included transitively. This is because the game of detective shouldn't be relied on. Simply, the implementation of header files may either change over time, or be different across systems. Now if that happens, you're screwed and your code compiles on one system, but not another, or may compile now but not in the future. It's just bad practice.

Therefore, each file should explicitly #include all of the header files it needs to compile. Don't rely on header files included transitively from other headers. Now that's easier said than done, since it's hard to really tell if your code is actually relying on a header file that's been included by another header file... lol

## The #include order of header files

This usually shouldn't matter, BUT (heh), if a header A needs declarations from header B, but forgets to include it, then the order matters. Preferably we include A before B since that would expose the bug, but if we included B before A,  then the code will unfortunately compile... This is because the compiler will compile all the declarations from B before compiling the code from A that depends on those declarations.

- Best practice to maximize the chance that missed includes will be FLAGGED by the compiler, order your #includes as follows:
1. The paired header file
2. Other headers from your project
3. 3rd party library headers
4. Standard library headers

So glad I'm learning this. Pretty sure I didn't care what order my includes were before, but this makes a lot of sense.

## Header file best practices

- Always include header guards (covered in the next section)
- Do not define variables/functions in header files (for now)
- Give the header file's base name the same base name as the source file it's associated with.
- Each header file should have a specific job, and be as independent as possible.
- Be mindful of what headers need to be explicitly included to avoid inadvertent transitive includes.
- A header file should #include any other headers containing functionality it needs
- Only #include what you need instead of #including everything just because you can...
- Do not #include .cpp files
- Prefer putting documentation on what something does or how to use it in the header. It's more likely to be seen there. Documentation describing how something works should remain in the source files.
