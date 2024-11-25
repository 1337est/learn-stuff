## Scope summary

The scope determines where the identifier can be accessed within the source code.

- A variable with **block (local) scope** can only be accessed from one point of declaration until the end of the block in which they are declared (including nested blocks). This includes:
    - local variables
    - function parameters
    - program-defined type definition (like enums and classes) declared inside the block
- A variable with **global scope** can be accessed from the point of declaration until the end of the end of the file. This includes:
    - global variables
    - functions
    - program-defined type definitions (like enums and classes) declared inside the namespace or in the global scope.

## Duration summary

Duration determines when a variable is created and destroyed

- Variables with **automatic duration** are created at definition, and destroyed when the block they were defined in has exited. This includes:
    - local variables
    * function parameters
* Variables with **static duration** are created when  the program begins and destroyed when the program ends. This includes:
    * global variables
    * static local variables
* Variables with **dynamic duration** are created and destroyed by programmer request. This includes:
    * dynamically allocated variables

## Linkage summary

An identifier's linkage determines whether a declaration of that same identifier in a different scope refers to the same entity (object, function, reference, etc...) or not.

Local variables have no linkage. Each declaration of an identifier with no linkage refers to a unique object or function.

- An identifier with **no linkage** means another declaration of the same identifier refers to a unique entity. Entities whose identifiers have no linkage include:
    - local variables
    - program-defined type identifiers (like enums and classes) declared inside a block
- An identifier with **internal linkage** means a declaration of the same identifier within the same translation unit refers to the same object or function. Entities whose identifiers have internal linkage include:
    - static global variables (initialized or uninitialized)
    - static functions
    - const global variables
    - unnamed namespaces and anything defined within them
- An identifier with **external linkage** means a declaration of the same identifier within the entire program refers to the same object or function. Entities whose identifiers have external linkage include:
    - non-static functions (regular functions)
    - non-const global variables (regular global variables)
    - extern const global variables
    - inline const global variables
    - namespaces


