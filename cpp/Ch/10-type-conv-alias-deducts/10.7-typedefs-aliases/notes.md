## Type aliases

**using** is a keyword that creates an alias for an existing data type

When the compiler encounters a type alias name, it will sub in the aliased type:

```cpp
#include <iostream>

int main()
{
    using Distance = double; // define Distance as an alias for type double

    Distance milesToDestination{ 3.4 }; // defines a variable of type double

    std::cout << milesToDestination << '\n'; // prints a double value

    return 0;
}
```

```
3.4
```

## Naming type aliases

Historically there hasn't been a lot of consistency in how type aliases have been named. Here are a few common naming conventions:
- Type aliases that end in a "_t" suffix, e.g. `size_t` and `nullptr_t`.
- Type aliases that end in a "_type" suffix, e.g. `std::string::size_type`
- Type aliases that use NO suffix, e.g. `std::string::iterator`.

In MODERN C++, it's conventional to name type aliases that you define yourself starting with a capital letter, and using no suffix:
```cpp
void printDistance(Distance distance); // Distance is some defined type
```

- Type aliases are not distinct types, but just introduces a new identifier for an existing type.

- Because scope is a property of an identifier, and type alias identifiers follow the same scoping as variable identifiers: a type alias defined inside a block or in global space will have block or global scope, respectively.

## Typedefs

**typedef** is shorthand for "type definition" and is an older way of creating an alias for a type using the `typedef` keyword.

```cpp
// The following aliases are identical
typedef long Miles;
using Miles = long;

typedef Distance double; // incorrect (typedef name first)
typedef double Distance; // correct (aliased type name first)
```

- Prefer type aliases over typedefs

## Using type aliases to make complex types easier to read

Consider the following:

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
{
    // some code here
    return false;
}

int main()
{
     std::vector<std::pair<std::string, int>> pairlist;

     return 0;
}
```

Having to read (or type) `std::vector<std::pair<std::string, int>>` everywhere you need to use that type could be cumbersome, and it is easy to make a typing mistake. This is much easier to read:

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

using VectPairSI = std::vector<std::pair<std::string, int>>; // make VectPairSI an alias for this crazy type

bool hasDuplicates(VectPairSI pairlist) // use VectPairSI in a function parameter
{
    // some code here
    return false;
}

int main()
{
     VectPairSI pairlist; // instantiate a VectPairSI variable

     return 0;
}
```

Now that's nice. This is probably the best use case for type aliases.

## Using type aliases to document the meaning of a value

Consider the following:
```cpp
int gradeTest();
```

Hard to tell what the integer means. A letter grade, or number of questions missed, or percentage? Using a type alias could help with viewing the code better:
```cpp
using TestScore = int;
TestScore gradeTest();
```

Now it's obvious that `TestScore` is what the int refers to.

- Use type aliases judiciously, when they provide a clear benefit to code readability or code maintenance.


