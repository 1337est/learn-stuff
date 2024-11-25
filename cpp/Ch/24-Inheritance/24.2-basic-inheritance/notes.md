Inheritance involves an "is-a" relationship between 2 objects by creating new objects that directly acquire the attributes and behaviors of other objects and then extending or specializing them.

You can think of it like a hierarchy: domain -> kingdom -> phylum -> class -> order -> family -> genus -> species. Every sub-category takes on characteristics from the preceding hierarchy.

Imagine if you have 2 classes like so:
```cpp
#include <string>
#include <string_view>

class Person
{
// In this example, we're making our members public for simplicity
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0)
        : m_name{ name }, m_age{ age }
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }

};

class BaseballPlayer
{
// In this example, we're making our members public for simplicity
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};
```

However, what if we want to keep track of the baseball players age and name as well without duplicating our code?

## Making `BasesballPlayer` a derived class

We can have `BaseballPlayer` inherit from our Person class like so:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Person
{
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0)
        : m_name{name}, m_age{age}
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }

};

// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};

int main()
{
    // Create a new BaseballPlayer object
    BaseballPlayer joe{};
    // Assign it a name (we can do this directly because m_name is public)
    joe.m_name = "Joe";
    // Print out the name
    std::cout << joe.getName() << '\n'; // use the getName() function we've acquired from the Person base class

    return 0;
}
```
```
Joe
```

This runs fine because all `BaseballPlayer` objects (like `joe`) have a `m_name` and `getName()` inherited from the `Person` class.

You can also chain inheritance.
