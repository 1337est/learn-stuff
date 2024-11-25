Let's expand our knowledge to include static member functions. We've covered static member variables and how they can be accessed directly using the class name and scope resolution operator:
```cpp
#include <iostream>

class Something
{
public:
    static inline int s_value { 1 };
};

int main()
{
    std::cout << Something::s_value; // s_value is public, we can access it directly
}
```

But what if the static member variables is private? We can do something like this:
```cpp
#include <iostream>

class Something
{
private:
    static inline int s_value { 1 };

public:
    int getValue() { return s_value; }
};

int main()
{
    Something s{};
    std::cout << s.getValue(); // works, but requires us to instantiate an object to call getValue()
}
```

But now we are instantiating an object of the class type to use the function. But we can do one better

## Static member functions

Let's add  the `static` keyword to our function:
```cpp
#include <iostream>

class Something
{
private:
    static inline int s_value { 1 };

public:
    static int getValue() { return s_value; } // static member function
};

int main()
{
    std::cout << Something::getValue() << '\n';
}
```

Now we're accessing the function directly by using the class name and the scope resolution operator.

## Static member functions have no `*this` pointer

Interestingly:
1. Because static member functions are not attached to an object, they have no `this` pointer. The `this` pointer always points to the object that the member function is working on. Static member functions do not work on an object, so `this` has nothing to point to.
2. Static member functions can directly access other static members (variables or functions), except non-static members. That's because non-static members must belong to a class object (they have a `this` pointer), and static member function have no class object to work with.

## Static members outside the class definition

This is pretty straightforward:
```cpp
#include <iostream>

class IDGenerator
{
private:
    static inline int s_nextID { 1 };

public:
     static int getNextID(); // Here's the declaration for a static function
};

// Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() { return s_nextID++; }

int main()
{
    for (int count{ 0 }; count < 5; ++count)
        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

    return 0;
}
```

```
The next ID is: 1
The next ID is: 2
The next ID is: 3
The next ID is: 4
The next ID is: 5
```


