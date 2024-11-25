## Defining your own namespace and ccessing a namespace with the scope resolution operator (::)

- The **scope resolution operator** `::` tells the compiler that the identifier specified by the right-hand operand should be for the scope of the left-hand operand. `std::cout` is for `cout` in the `std` namespace.
- namespace names should have the syntax:
```
namespace NamespaceIdentifier
{
    // namespace content
}
```

```cpp
#include <iostream>

namespace Foo // define a namespace named Foo
{
    // This doSomething() belongs to namespace Foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}

namespace Goo // define a namespace named Goo
{
    // This doSomething() belongs to namespace Goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}

int main()
{
    std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo
    std::cout << Goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Goo
    return 0;
}
```

## Forward declaration of content in namespaces

For identifiers inside a namespace, those forward declarations also need to be inside the same namespace:

```cpp
// add.h
#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
}

#endif
```
```cpp
// add.cpp
#include "add.h"

namespace BasicMath
{
    // define the function add() inside namespace BasicMath
    int add(int x, int y)
    {
        return x + y;
    }
}
```
```cpp
// main.cpp
#include "add.h" // for BasicMath::add()

#include <iostream>

int main()
{
    std::cout << BasicMath::add(4, 3) << '\n';

    return 0;
}
```

## You can nest namespaces

```cpp
#include <iostream>

namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Foo
{
     void someFcn() {} // This function is in Foo only
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

## Namespace aliases

```cpp
#include <iostream>

namespace Foo::Goo
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace Active = Foo::Goo; // active now refers to Foo::Goo

    std::cout << Active::add(1, 2) << '\n'; // This is really Foo::Goo::add()

    return 0;
} // The Active alias ends here
```


