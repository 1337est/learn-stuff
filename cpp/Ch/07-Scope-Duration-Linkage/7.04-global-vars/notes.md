- **global variables** are variables that are defined outside of a block.
- global variables have static duration and are sometimes called static variables. Static variables are created when the program starts, and deleted when the program ends.
- Prefix global variables with "g" or "g_" e.g. "gvariable" or "g_variables" to help identify global variables from local variables.
- global variables inside a user-defined namespace don't need to be prefixed, but you still can if you want.
- Use of a non-constant global variable should generally be avoided altogether.
```cpp
// Summary
// Non-constant global variables
int g_x;                 // defines non-initialized global variable (zero initialized by default)
int g_x {};              // defines explicitly value-initialized global variable
int g_x { 1 };           // defines explicitly initialized global variable

// Const global variables
const int g_y;           // error: const variables must be initialized
const int g_y { 2 };     // defines initialized global const

// Constexpr global variables
constexpr int g_y;       // error: constexpr variables must be initialized
constexpr int g_y { 3 }; // defines initialized global constexpr
```


