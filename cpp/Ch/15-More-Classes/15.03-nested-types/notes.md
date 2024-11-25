Consider this program:
```cpp
#include <iostream>

enum class FruitType
{
	apple,
	banana,
	cherry
};

class Fruit
{
private:
	FruitType m_type { };
	int m_percentageEaten { 0 };

public:
	Fruit(FruitType type) :
		m_type { type }
	{
	}

	FruitType getType() { return m_type; }
	int getPercentageEaten() { return m_percentageEaten; }

	bool isCherry() { return m_type == FruitType::cherry; }

};

int main()
{
	Fruit apple { FruitType::apple };

	if (apple.getType() == FruitType::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```

There's nothing wrong here but `enum class FruitType` is meant to be used in conjunction with the `Fruit` class, so having it exist independently leaves us to infer this.

## Nested types (member types)

Previously we've seen class types with data members and member functions.

Class types also support **nested types**, which are types nested inside a class under the appropriate access specifier:
```cpp
#include <iostream>

class Fruit
{
public:
	// FruitType has been moved inside the class, under the public access specifier
        // We've also renamed it Type and made it an enum rather than an enum class
	enum Type
	{
		apple,
		banana,
		cherry
	};

private:
	Type m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(Type type) :
		m_type { type }
	{
	}

	Type getType() { return m_type;  }
	int getPercentageEaten() { return m_percentageEaten;  }

	bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
};

int main()
{
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```

1. Note that `FruitType` is now defined inside the class as `Type` instead.
2. Nested type `Type` is also defined at the top of the class. Nested type names must be fully defined before they can be used, so they are usually defined first.
3. Nested types follow normal access rules. `Type` is defined under `public` so `Type` and its enumerators can be directly accessed by the public.
4. Class types act as a scope region for names declared within. Therefore the fully qualified name of `Type` is `Fruit::Type`, and the fully qualified name of the `apple` enumerator is `Fruit::apple`. Within the class/scope, we can simply specify without the fully qualified name. Outside the class/scope, we must specify the fully qualified name.
5. Changing to an unscoped enum means we can access enumerators as `Fruit::apple` rather than the longer `Fruit::Type::apple` that we'd have to use if the enumerators were scoped.

## Nested typedefs and type aliases

Here's an example that contains a nested typedef with the `using` keyword:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};

int main()
{
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() }; // must use fully qualified name outside class

    std::cout << john.getName() << " has id: " << id << '\n';

    return 0;
}
```

## Nested classes and access to the outer class members

This is uncommon but possible. Also, a nested class (in C++) does not have access to the `this` pointer of the outer class, so nested classes cannot "directly" access the members of the outer class. However, since nested classes are members of the outer class, they can access any private members of the outer class that are in scope:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

    class Printer
    {
    public:
        void print(const Employee& e) const
        {
            // Printer can't access Employee's `this` pointer
            // so we can't print m_name and m_id directly
            // Instead, we have to pass in an Employee object to use
            // Because Printer is a member of Employee,
            // we can access private members e.m_name and e.m_id directly
            std::cout << e.m_name << " has id: " << e.m_id << '\n';
        }
    };

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name{ name }
        , m_id{ id }
        , m_wage{ wage }
    {
    }

    // removed the access functions in this example (since they aren't used)
};

int main()
{
    const Employee john{ "John", 1, 45000 };
    const Employee::Printer p{}; // instantiate an object of the inner class
    p.print(john);

    return 0;
}
```

This prints:
```
John has id: 1
```

**Note:**
- Nested types can't be forward declared.
