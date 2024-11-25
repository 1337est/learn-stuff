## Implementation and interfaces in class types

The **interface** of a class type defines how a user of the class type will interact with objects of the class type. Only public members can be accessed from outside the class type. Therefore, the public members of a class type are its interface and is sometimes called a **public interface**.

An interface is an implicit contract between the author of a class and the user of a class. If the interface changes, any code that uses it may break. Therefore, it's vital that the interface design is stable.

The **implementation** of a class type consists of the code that makes the class behave as intended. This includes the member variables that store data, and the bodies of the member functions that contain the program logic and manipulate the member variables.

## Data hiding (encapsulation)

In programming, **data hiding** (also called **information hiding** or **data abstraction**) is a technique used to enforce the separation of interface and implementation by hiding the implementation of a program-defined data type from users.

The term **encapsulation** is also sometimes used to refer to data hiding, and we'll assume all encapsulated classes implement data hiding.

## How to implement data hiding

- We ensure the data members of the class type are private, so the user can't directly access them.
- We ensure the member functions are public, so the user can call them.

- Classes defined in C++ should use data hiding.
- Structs should not use data hiding.

Is this more work? Yes, but like with most things in life, the hard work will yield bountiful fruits of your labor.

## Data hiding makes classes easier to use, and reduces complexity

To use an encapsulated class, you don't need to know how it is implemented. You only need to understand its interface: what member functions are publicly available, what arguments they take, and what values they return.
```cpp
#include <iostream>
#include <string_view>

int main()
{
    std::string_view sv{ "Hello, world!" };
    std::cout << sv.length();

    return 0;
}
```

Here we don't need to know the details of how `std::string_view` is implemented and those details are hidden from us. Also, we don't have to know! Imagine how much more complicated C++ would be if we had to understand how `std::string`, `std::vector`, or `std::cout` were implemented in order to use them. Blegh!

## The order of class member declaration

- Declare public members first, protected members next, and private members last. This spotlights the public interface and de-emphasizes implementation details.

