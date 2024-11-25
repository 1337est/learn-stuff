## Procedural programming

We previously defined an object in C++ as, "a piece of memory that can be used to store values." An object with a name is a variable. Our C++ programs thus far have consisted of sequential lists of instructions to the computer that define data (via objects) and operations performed on that data (via functions containing statements and expressions).

Basically up to now, we've been doing **procedural programming**, which focuses on creating "procedures" (which in C++ are functions) that implement our program logic. We pass data objects to these functions, those functions perform operations on the data, and then potentially return a result to be used by the caller.

In procedural programming, the functions and the data those functions operate on are separate entities. The programmer is responsible for combining the functions and data together to produce the desired result. This leads to code that looks like this:
```cpp
eat(you, apple);
```

Now, physically look around you -- everywhere you look are objects: books and buildings and food and even you. These objects have 2 major components to them:
1. Some number of associated properties (e.g. weight, color, size, shape, etc...)
2. Some number of behaviors that they can exhibit (e.g. being opened, making something else hot, etc...). These properties and behaviors are inseparable.

In programming, properties are represented by objects, and behaviors are represented by functions. Therefore, procedural programming represents reality fairly poorly, as it separates properties (objects) and behaviors (functions).

## What is object-oriented programming?

In **object-oriented programming** (abbreviated OOP), the focus is on creating program-defined data types that contain both properties and a set of well-defined behaviors. The term "object" in OOP refers to the objects that we can instantiate from such types. This leads to code that looks like this:
```cpp
you.eat(apple)
```

This makes it clearer who the subject is (`you`), what behavior is being invoked (`eat()`), and what objects are accessories to that behavior (`apple`).

## A procedural vs OOP-like example

Here's the procedural programming style that prints the name and number of legs of an animal:
```cpp
#include <iostream>
#include <string_view>

enum AnimalType
{
    cat,
    dog,
    chicken,
};

constexpr std::string_view animalName(AnimalType type)
{
    switch (type)
    {
    case cat: return "cat";
    case dog: return "dog";
    case chicken: return "chicken";
    default:  return "";
    }
}

constexpr int numLegs(AnimalType type)
{
    switch (type)
    {
    case cat: return 4;
    case dog: return 4;
    case chicken: return 2;
    default:  return 0;
    }
}


int main()
{
    constexpr AnimalType animal{ cat };
    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

    return 0;
}
```

In this program, we have written functions that allows us to do things like get the number of legs an animal has, and get the name of an animal.

While this code works fine, what if we wanted to update our program so that our animal is now a `snake`. To add a snake to our code, we'd need to modify `AnimalType`, `numLegs()`, and `animalName()`. If this was a large code base, we'd need to update any other function that uses `AnimalType` -- if `AnimalType` was used frequently, that could break something.

Now let's write this with an OOP mindset:
```cpp
#include <iostream>
#include <string_view>

struct Cat
{
    std::string_view name{ "cat" };
    int numLegs{ 4 };
};

struct Dog
{
    std::string_view name{ "dog" };
    int numLegs{ 4 };
};

struct Chicken
{
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
};

int main()
{
    constexpr Cat animal;
    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";

    return 0;
}
```

In this example, each animal is its own program-defined type, and that type manages everything related to that animal.

Now consider the same case where we want to update our program so that our animal is now a `snake`. All we do now is create a `Snake` type and use it instead of `Cat`. Very little existing code needs to be changed, which means less risk of breaking something.

## OOP brings other benefits to the table

When you submit code into a repository that's used by other developers, or into an application that's used by real users, you need you code to be able to evolve (perhaps significantly). The best way to keep your code modular and non-redundant as possible, OOP also brings a number of other useful concepts: inheritance, encapsulation, abstraction, and polymorphism.

## The term "object"

The term "object" in a traditional programming sense, means an object is a piece of memory to store values. In C++, the term "object", means that it is both an object in the traditional sense, and that it combines properties and behaviors. We will favor the traditional meaning of the term object and use the term "class object" when specifically referring to OOP objects.
