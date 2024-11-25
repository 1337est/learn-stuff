Humor me for a second, since this is a fun (and relevant analogy):

Let's say you're walking down the street on a brisk autumn day, eating a burrito (yup, sounds like me). You want somewhere to sit, so you look around. To your left is a park, with mowed grass, shade trees, a few uncomfortable benches, and screaming kids on the nearby playground. To your right is a stranger's residence. Through the window, you see a comfy reclining chair and a crackling fireplace.

With a heavy sigh, you choose the park.

But why? Well that's because the key determinant for your choice is that the park is a public space, whereas the residence is private. You (and anyone else) is allowed to freely access public spaces, but only the members of the residence (or those given explicit permission to enter) are permitted to access the private residence.

## Member access

A similar concept applies to the members of a class type. Each member of a class type has a property called an **access level** that determines who can access that member.

C++ has 3 different access levels: public, private, and protected. Here, we'll cover public and private (protected isn't discussed until chapter/section 24.5)

Whenever a member is accessed, the compiler checks whether the access level of the member permits that member to be accessed. If access isn't permitted, a compilation error results. This access level system is sometimes informally called **access controls**.

## The members of a struct are public by default

Members with public access level are called public members. A **public member** is a member of a class type that does not have any restrictions on how they can be accessed. They can be accessed by anyone as long as they are in scope.

Public members can be accessed by other members of the same class and **the public** (which includes non-member functions and members of other class types).

- The members of a struct are public by default.

Consider the following struct:
```cpp
#include <iostream>

struct Date
{
    // struct members are public by default, can be accessed by anyone
    int year {};       // public by default
    int month {};      // public by default
    int day {};        // public by default

    void print() const // public by default
    {
        // public members can be accessed in member functions of the class type
        std::cout << year << '/' << month << '/' << day;
    }
};

// non-member function main is part of "the public"
int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    // public members can be accessed by the public
    today.day = 16; // okay: the day member is public
    today.print();  // okay: the print() member function is public

    return 0;
}
```

In this example, members are accessed in three places:
- Within member function `print()`, we access `year`, `month`, and `day` members of the implicit object.
- In `main()`, we directly access `today.day` to set its value.
- In `main()`, we call member function `today.print()`.

## The members of a class are private by default

**Private members** are members of a class type that can only be accessed by other members of the same class:
```cpp
#include <iostream>

class Date // now a class instead of a struct
{
    // class members are private by default, can only be accessed by other members
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can be accessed in member functions
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

    // private members can not be accessed by the public
    today.m_day = 16; // compile error: the m_day member is private
    today.print();    // compile error: the print() member function is private

    return 0;
}
```

In this example, members are accessed in the same three places, but now there are compilation errors.

This is because `main()` is a part of the public, and is trying to access private members.

As you can see, the initialization of `today` actually causes a compilation error.

- We'll discuss how to properly deal with this in an upcoming lesson 14.9

## Naming your private member variables

In C++, it's common to name private data members starting with an "m_" prefix. This is done for a couple of reasons. The "m_" prefix allows us to easily differentiate data members from function parameters or local variables within a member function.
```cpp
// Some member function that sets private member m_name to the value of the name parameter
void setName(std::string_view name)
{
    m_name = name;
}
```
Here we can differentiate between "m_name" being a member, and "name" isn't. Also, the prefix helps to prevent naming collisions.

- Prefer naming your private data members starting with an "m_" prefix.

## Setting access levels via access specifiers

We can specify the access level of our members by using an **access specifier**, which is a pay to set the access level of members following the specifier. We have the `public:`, `private:`, and `protected:` access specifiers, but we'll cover protected later:
```cpp
class Date
{
// Any members defined here would default to private

public: // here's our public access specifier

    void print() const // public due to above public: specifier
    {
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }

private: // here's our private access specifier

    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main()
{
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
```

Although specifying `private:` is redundant for classes before a `public:` specifier, it makes it clearer that the following members are private without having to infer the default access level:
```cpp
class Foo
{
// private access specifier not required here since classes default to private members
    int m_something {};  // private by default
};
```

```cpp
class Foo
{
private: // redundant, but makes it clear that what follows is private
    int m_something {};  // private by default
};
```

## Access level best practices for structs and classes

- Structs should avoid access specifiers altogether.
- Classes should generally make member variables private (or protected), and member function public.

## The technical and practical differences between structs and classes

A class defaults its members to private, whereas a struct default its members to public. That's it!

However, in practice, we use structs and classes differently. As a rule of thumb, use a struct when all of the following is true:
- You have a simple collection of data that doesn't benefit from restricting access.
- Aggregate initialization is sufficient.
- You have no class invariants, setup needs, or cleanup needs

Otherwise, use a class.
