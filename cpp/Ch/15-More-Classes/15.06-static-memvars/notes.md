Remember static local variables?
```cpp
#include <iostream>

int generateID()
{
    static int s_id{ 0 }; // static local variable
    return ++s_id;
}

int main()
{
    std::cout << generateID() << '\n';
    std::cout << generateID() << '\n';
    std::cout << generateID() << '\n';

    return 0;
}
```

```
1
2
3
```

See how `s_id`  has kept its value across multiple function calls? That's because it was created at the start of the program, and doesn't get reinitialized or destroyed until the end of the program.

Now let's talk about static member variables and static member functions

## Static member variables

Member variables of a class can be made static by using the `static` keyword and **static member variables** are shared by all objects of the class:
```cpp
#include <iostream>

struct Something
{
    static int s_value; // now static
};

int Something::s_value{ 1 }; // initialize s_value to 1

int main()
{
    Something first{};
    Something second{};

    first.s_value = 2;

    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    return 0;
}
```

This program surprisingly prints:
```
2
2
```

Because `s_value` is a static member variable, `s_value` is shared between all objects of the class. Consequently, `first.s_value` and `second.s_value` are the same variable. The value that we set using `first` can be accessed using `second`. Interesting...

## Static members are not associated with class objects

Because static member `s_value` exists independently of any class objects, it can be accessed directly using the class name and the scope resolution operator:
```cpp
class Something
{
public:
    static int s_value; // declares the static member variable
};

int Something::s_value{ 1 }; // defines the static member variable (we'll discuss this section below)

int main()
{
    // note: we're not instantiating any objects of type Something

    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}
```

Here, `s_value` is referenced by class name `Something` rather than through an object. We did not instantiate an object of type `Something` but are able to access and use `Something::s_value`.

- Access static members using the class name and scope resolution operator (e.g. `Something::s_value`).

## Defining and initializing static member variables

We declare static member variables inside a class type (and therefore tell the compiler about its existence), but we don't actually define it (much like a forward declaration). Because static member variables are essentially global variables, you must explicitly define and optionally initialize the static member outside of the class, in the global scope. We did so above like so:
```cpp
int Something::s_value{ 1 }; // defines the static member variable
```

This instantiates the static member variables and initializes it with 1. The default (if no initializer is provided) would be zero-initialized.

Note also that you can initialize and define it even when it's declared private (or protected).

## Initialization of static member variables inside the class definition

You can initialize static members inside the class definition when the static member is a constant integral type or a const enum:
```cpp
class Whatever
{
public:
    static const int s_value{ 4 }; // a static const int can be defined and initialized directly
};
```

You can also initialize static members inside the class definition with inline variables (C++17):
```cpp
class Whatever
{
public:
    static inline int s_value{ 4 }; // a static inline variable can be defined and initialized directly
};
```

Because `constexpr` members are implicitly inline (C++17), static `constexpr` members can also be initialized inside the class definition without explicit use of the `inline` keyword:
```cpp
#include <string_view>

class Whatever
{
public:
    static constexpr double s_value{ 2.2 }; // ok
    static constexpr std::string_view s_view{ "Hello" }; // this even works for classes that support constexpr initialization
};
```

## An example of static member variables

```cpp
#include <iostream>

class Something
{
private:
    static inline int s_idGenerator { 1 };
    int m_id {};

public:
    // grab the next value from the id generator
    Something() : m_id { s_idGenerator++ }
    {
    }

    int getID() const { return m_id; }
};

int main()
{
    Something first{};
    Something second{};
    Something third{};

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';
    return 0;
}
```

```
1
2
3
```


