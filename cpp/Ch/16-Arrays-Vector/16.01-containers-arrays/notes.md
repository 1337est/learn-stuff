## The variable scalability challenge

Let's say you want to record the test scores for 30 students and calculate the average score for the class:
```cpp
// allocate 30 integer variables (each with a different name)
int testScore1 {};
int testScore2 {};
int testScore3 {};
// ...
int testScore30 {};
```

And to calculate the average score for the class:
```cpp
int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5
     + testScore6 + testScore7 + testScore8 + testScore9 + testScore10
     + testScore11 + testScore12 + testScore13 + testScore14 + testScore15
     + testScore16 + testScore17 + testScore18 + testScore19 + testScore20
     + testScore21 + testScore22 + testScore23 + testScore24 + testScore25
     + testScore26 + testScore27 + testScore28 + testScore29 + testScore30)
     / 30; };
```

This is wrong... Let's introduce containers

## Containers

Containers also exist in programming, to make it easier to create and manage (potentially large) collections of objects. In general programming, a **container** is a data type that provides storage for a collection of unnamed objects (called **elements**).

A string is a container that provides storage for a collection of characters:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" }; // strings are a container for characters
    std::cout << name; // output our string as a sequence of characters

    return 0;
}
```

## The elements of a container are unnamed

While the container object itself has a name, the elements that make up the container are unnamed.

In the above example, our string container has name `name` but the independent characters that make up `Alex` do not have a name.

## Length of a container

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```

Here `length` is a member function of `std::string` that we use to get the number of character elements in the string container:
```
Alex has 4 characters
```

## Container operations

Containers typically implement a significant subset of the following operations:
- Create a container (e.g. empty, with storage for some initial number of elements, from a list of values).
- Access to elements (e.g. get first element, get last element, get any element).
- Insert and remove elements.
- Get the number of elements in the container.

## Element types

Containers are **homogeneous**, meaning the elements of a container are required to have the same type.

## Introduction to arrays

An **array** is a container data type that stores a sequence of values **contiguously** (meaning each element is placed in an adjacent memory location, with no gaps).

C++ has 3 primary array t ypes:
- (C-style) arrays,
- `std::vector` container class
- `std::array` container class


