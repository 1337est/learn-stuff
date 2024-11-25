## Delegating constructors

Constructors are allowed to delegate (transfer responsibility for) initialization to another constructor from the same class type in a process called **constructor chaining** and such constructors are called **delegating constructors**:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};
    int m_id{ 0 };

public:
    Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {
    }

    Employee(std::string_view name, int id)
        : m_name{ name }, m_id{ id } // actually initializes the members
    {
        std::cout << "Employee " << m_name << " created\n";
    }

};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```

When `e1 { "James" }` is initialized, matching constructor `Employee(std::string_view)` is called with parameter `name` set to `"James"`. The member initializer list of this constructor delegates initialization and calls to this constructor `Employee(std::string_view, int)`. The value of `name` (`"James"`) is passed as the first argument, and literal `0` is passed as the second argument. The member initializer list of the delegated constructor (the second one) then initializes the members. Then the body of the delegated constructor runs and control return to the initial constructor, whose empty body then runs.

The downside of this method is that we had to hardcode literal `0` and that can lead to duplication of initialization values.

- If you have multiple constructors, consider whether you can use delegating constructors to reduce duplicate code.

## Reducing constructors using default arguments

You can also do something like this:
```cpp
 #include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};
    int m_id{ 0 }; // default member initializer

public:

    Employee(std::string_view name, int id = 0) // default argument for id
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```

Remember that members for which the user must provide initialization values should be defined first (leftmost side) since default values should be on the rightmost side.


