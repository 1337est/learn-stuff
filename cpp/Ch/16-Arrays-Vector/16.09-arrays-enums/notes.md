## Using unscoped enumerators for indexing

Unscoped enumerations will implicitly convert to a `std::size_t`, so they are perfect for use in container classes. Consider the following code:
```cpp
#include <vector>

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    testScores[2] = 76; // who does this represent?
}
```

Who is the student represented by `testScores[2]`? It's not clear.

Now consider this problem using an enum:
```cpp
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

    return 0;
}
```

Now we know who's score we're updating.

## Using a non-constexpr unscoped enumeration for indexing

Because enumerators are implicitly constexpr, and are implementation defined (thus, can either be signed or unsigned), as long as we stick to indexing with unscoped enumerators, we won't run into a sign conversion issue.

However, consider the following:
```cpp
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr

    testScores[name] = 76; // may trigger a sign conversion warning if Student::Names defaults to a signed underlying type

    return 0;
}
```

In this case we could make `name` constexpr, however it's probably best to specify the underlying type of the enumeration to be an unsigned int:
```cpp
#include <vector>

namespace Students
{
    enum Names : unsigned int // explicitly specifies the underlying type is unsigned int
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr

    testScores[name] = 76; // not a sign conversion since name is unsigned

    return 0;
}
```

Now that `name` is guaranteed to be an `unsigned int`, it can be converted to a `std::size_t` without sign conversion issues.

## Using a count enumerator

Notice how we had a `max_students` enumerator at the end of the enumerator list. When using default values (which is recommended) for our enumerators, the value will be how many prior enumerators were defined (e.g. `max_students` has value `5` and there were 5 enumerators previously defined). Informally, we'll call this a **count enumerator**, since it's value represents the count of previously defined enumerators.

```cpp
#include <iostream>
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        // add future enumerators here
        max_students // 5
    };
}

int main()
{
    std::vector<int> testScores(Students::max_students); // Create a vector with 5 elements

    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

    std::cout << "The class has " << Students::max_students << " students\n";

    return 0;
}
```

Now if we add more to our enumerator list, our code still works:
```cpp
#include <vector>
#include <iostream>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        wendy, // 5 (added)
        // add future enumerators here
        max_students // now 6
    };
}

int main()
{
    std::vector<int> testScores(Students::max_students); // will now allocate 6 elements

    testScores[Students::stan] = 76; // still works

    std::cout << "The class has " << Students::max_students << " students\n";

    return 0;
}
```


