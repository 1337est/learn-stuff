- Global variables with internal linkage are sometimes called internal variables
- The static keyword makes a non-constant global variable internal
- An identifier with internal linkage can be seen and used within a single translation unit and is not accessible from other translation units and therefore isn't exposed to the linker. (When the preprocessor has finished processing a code file plus all of the `#included` content, the result is called a translation unit. This translation unit is what is compiled by the compiler). This means that if two source files have identically named identifiers with internal linkage, those identifiers will be treated independently and do not result in a ODR violation (which makes sense because they aren't accessible from other translation units).

```cpp
// Internal global variables definitions:
static int g_x;          // defines non-initialized internal global variable (zero initialized by default)
static int g_x{ 1 };     // defines initialized internal global variable

const int g_y { 2 };     // defines initialized internal global const variable
constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

// Internal function definitions:
static int foo() {};     // defines internal function
```


