Consider the following:
```cpp
// main.cpp
#include <iostream>

template <typename T>
T addOne(T x); // function template forward declaration

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```

```cpp
// add.cpp
template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}
```

If `addOne` were a non-template function, then this program would work fine: In main.cpp, the compiler would be satisfied with the forward declaration of `addOne`, and the linker would connect the call to `addOne()` in main.cpp to the function definition in add.cpp.

HOWEVER, because `addOne` is a template, this program doesn't work, and we get a linker error:
```
1>Project6.obj : error LNK2019: unresolved external symbol "int __cdecl addOne<int>(int)" (??$addOne@H@@YAHH@Z) referenced in function _main
1>Project6.obj : error LNK2019: unresolved external symbol "double __cdecl addOne<double>(double)" (??$addOne@N@@YANN@Z) referenced in function _main
```

In main.cpp, we call `addOne<int>` and `addOne<double>`, but the compiler can't see the definition for the function template `addOne` and can't instantiate those functions inside main.cpp. It does however see the forward declaration and just assumes those functions exist elsewhere and will be linked in later.

Furthermore, when the compiler does to compile add.cpp, it will see the definition for function template `addOne`, but there aren't any uses in add.cpp, so the compiler will not instantiate anything. The end result is that the linker throws up its hands in confusion because it can't connect the calls for `addOne<int>` and `addOne<double>` in main.cpp to the actual functions, because those functions were never instantiated.

The most conventional way to address this issue is to put all your templated code into a header file (.h) instead of a source file (.cpp), that way any files that need access to the template can #include the relevant header, andthe template definition will be copied by the preprocessor into the source file. The compiler will then be able to instantiate any functions that are needed.

The reason this doesn't cause a violation of the ODR is because the ODR says that types, templates, inline functions, and inline variables are allowed to have identical definitions in different files, so long as each definition is identical. Also, function implicitly instantiated from templates are implicitly inline, meaning the instantiated functions in multiple files is alright so long as the definition is identical in each.

Here's an example:
```cpp
// max.h
#ifndef MAX_H
#define MAX_H

// Our template definition
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

#endif
```
```cpp
// foo.cpp
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo()
{
	std::cout << max(3, 2) << '\n';
}
```
```cpp
// main.cpp
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo(); // forward declaration for function foo

int main()
{
    std::cout << max(3, 5) << '\n';
    foo();

    return 0;
}
```

In the above example, main.cpp and foo.cpp `#include "max.h"` so the code in both files can make use of the function template.

- Templates that are needed in multiple files should be defined in a header file, and then #included wherever needed. This allows the compiler to see the full template definition and instantiate the template when needed.


