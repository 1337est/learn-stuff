Here we'll discuss the specific case of member functions that return data members by reference.

## Returning data members by value can be expensive

```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	std::string getName() const { return m_name; } //  getter returns by value
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}
```

Here we have the `getName()` access function returning `std::string m_name` by value. This is expensive.

## Returning data members by lvalue reference

Let's update the example above so that `getName()` returns `m_name` by const lvalue reference:
```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
```

Now when `joe.getName()` is invoked, `joe.m_name` is returned by reference to the caller. The caller then uses this reference to print `joe.m_name` to the console.

Because `joe` exists in the scope of the caller until the end of the `main()` function, the reference to `joe.m_name` is valid for the same duration.

## The return type of a member function returning a reference to a data member should match the data member's type

In the above example, `m_name` is of type `std::string`, so `getName()` return `const std::string&`.

## Using member functions that return by reference safely

Consider the following code:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e;
	e.setName(name);
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member

	return 0;
}
```

Follow these steps to use member functions that return by reference safely:

- Prefer to use the return value of a member function that returns by reference immediately. Since this works with both lvalue and rvalue objects, if you always do this you will avoid trouble.
```cpp
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();
```

- Do not "save" a returned reference to use later unless you are sure the implicit object is an lvalue. If you do this with an rvalue implicit object, undefined behavior will result when you use the now-dangling reference.
```cpp
	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior
```

- If you do need to persist a returned reference for use later and aren't sure that the implicit object is an lvalue, use the returned reference as the initializer for a non-reference local variable, which make a copy of t he member being referenced into the local variable.

## Do not return non-const references to private data members

Because a reference acts like the object being referenced, a member function that returns a non-const reference provides direct access to that member (even if the member is private, which would defeat the purpose of that member being non-modifiable by the public):
```cpp
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() { return m_value; } // returns a non-const reference (don't do this)
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value(); // prints 5

    return 0;
}
```

## Const member functions can't return non-const references to data members

This makes sense -- a const member function is not allowed to modify the state of the object, nor is it allowed to call functions that would modify the state of the object.

If a const member function was allowed to return a non-const reference to a member, it would be handing the caller a way to directly modify that member. This violates the intent of a const member function.
