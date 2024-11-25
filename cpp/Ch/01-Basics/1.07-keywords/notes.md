## Vocabulary

- **keywords**: Reserved words (92 of which as of C++23), that have special meaning within the C++ language.
- **identifiers**: what you call a variable, function, or other item. Eg. `int identifier = value`

## Naming Conventions

- lowercase for variable names
```c++
int value; // conventional

int Value; // unconventional (should start with lower case letter)
int VALUE; // unconventional (should start with lower case letter and be in all lower case)
int VaLuE; // unconventional (see your psychiatrist) ;)
```
- Names that start with a capital letter are generally reserved for user-defined types (structs, classes, enumerations)
- snake_case and camelCase
```cpp
int my_variable_name;   // conventional (separated by underscores/snake_case)
int my_function_name(); // conventional (separated by underscores/snake_case)

int myVariableName;     // conventional (intercapped/camelCase)
int myFunctionName();   // conventional (intercapped/camelCase)

int my variable name;   // invalid (whitespace not allowed)
int my function name(); // invalid (whitespace not allowed)

int MyVariableName;     // unconventional (should start with lower case letter)
int MyFunctionName();   // unconventional (should start with lower case letter)
```

- Avoid naming identifiers that start with an underscore since these names are typically reserved for OS, library, and/or compiler use.


