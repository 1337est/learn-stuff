## What is a stack?

Analogy time! Consider a stack of plates in a cafeteria. For some unknown reason, these plates are extra heavy and can only be lifted one at a time. Because the plates are stacked and heavy, you can only modify the stack of plates in one of two ways:

1. Put a new plate on top of the stack (hiding the plate underneath, if it exists)
2. Remove the top plate from the stack (exposing the plate underneath, if it exists)

Adding or removing a plate from the middle or bottom of the stack is not allowed, as that would require lifting more than one plate at a time.

This order in which items are added to and removed from a stack is **last-in, first out (LIFO)**. The last plate added to the stack, is the first plate removed.

## Stacks in programming

Common operations include **push** and **pop**:
- **push** puts a new element on top of the stack
- **pop** removes the top element from the stack

## Stack behavior with `std::vector`

Stack behavior is implemented via the following `std::vector` member functions:
- push_back(): puts a new element on top of the stack
    - Adds element to the end of the vector
- pop_back(): removes the top element from the stacks
    - Returns void and removes element at the end of the vector
- back(): get the top element on the stack
    - Does not remove item
- emplace_back(): Alternate form of push_back() that can be more efficient
    - Adds element to the end of the vector

```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack)
{
	if (stack.empty()) // if stack.size == 0
		std::cout << "Empty";

	for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";
}

int main()
{
	std::vector<int> stack{}; // empty stack

	printStack(stack);

	stack.push_back(1); // push_back() pushes an element on the stack
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n'; // back() returns the last element

	stack.pop_back(); // pop_back() pops an element off the stack
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	return 0;
}
```

```
Empty   Capacity: 0  Length: 0
1       Capacity: 1  Length: 1
1 2     Capacity: 2  Length: 2
1 2 3   Capacity: 4  Length: 3
Top:3
1 2     Capacity: 4  Length: 2
1       Capacity: 4  Length: 1
Empty   Capacity: 4  Length: 0
```

You may have noticed the extra capacity?

## Extra capacity from pushing

Notice how capacity jumped from 2 to 4. This is because pushing triggers reallocation, and `std::vector` will typically allocate some extra capacity to allow additional elements to be added without triggering another reallocation the next time an element is added. The extra capacity allocated is compiler specific and different compilers do it differently:
- GCC and Clang doubles the current capacity. We went from 1 to 2, then 2 to 4. If it jumped again, it would go from 4 to 8.
- Visual Studio 2022 multiplies the current capacity by 1.5. When the last resize is triggered, the capacity is changed from 2 to 3.

## Resizing a vector doesn't work with stack behavior

Consider this silly example where we change the previous code that initializes our `stack` variable to use this instead:
```cpp
std::vector<int> stack(3); // parenthesis init to set vector's capacity to 3
```

Now when we run the program we get this instead:
```
0 0 0   Capacity: 3  Length: 3
0 0 0 1         Capacity: 4  Length: 4
0 0 0 1 2       Capacity: 6  Length: 5
0 0 0 1 2 3     Capacity: 6  Length: 6
Top: 3
0 0 0 1 2       Capacity: 6  Length: 5
0 0 0 1         Capacity: 6  Length: 4
0 0 0   Capacity: 6  Length: 3
```

This makes sense logically, so be careful and be sure you know what you're doing.

## The `reserve()` member function changes capacity but not length

Exactly what the title says:
```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack)
{
	if (stack.empty()) // if stack.size == 0
		std::cout << "Empty";

	for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";
}

int main()
{
	std::vector<int> stack{};

	printStack(stack);

	stack.reserve(6); // reserve space for 6 elements (but do not change length)
	printStack(stack);

	stack.push_back(1);
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n';

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	return 0;
}
```

```
Empty   Capacity: 0  Length: 0
Empty   Capacity: 6  Length: 0
1       Capacity: 6  Length: 1
1 2     Capacity: 6  Length: 2
1 2 3   Capacity: 6  Length: 3
Top: 3
1 2     Capacity: 6  Length: 2
1       Capacity: 6  Length: 1
Empty   Capacity: 6  Length: 0
```

## `push_back()` vs `emplace_back()`

They both push an element onto the stack. If the object to be pushed already exists, they do the same thing and `push_back()` is preferred.

However, when creating a temporary object for the purpose of pushing it onto the vector, `emplace_back()` can be more efficient:
```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Foo
{
private:
    std::string m_a{};
    int m_b{};

public:
    Foo(std::string_view a, int b)
        : m_a { a }, m_b { b }
        {}

    explicit Foo(int b)
        : m_a {}, m_b { b }
        {};
};

int main()
{
	std::vector<Foo> stack{};

	// When we already have an object, push_back and emplace_back are similar in efficiency
	Foo f{ "a", 2 };
	stack.push_back(f);    // prefer this one
	stack.emplace_back(f);

	// When we need to create a temporary object to push, emplace_back is more efficient
	stack.push_back({ "a", 2 }); // creates a temporary object, and then copies it into the vector
	stack.emplace_back("a", 2);  // forwards the arguments so the object can be created directly in the vector (no copy made)

	// push_back won't use explicit constructors, emplace_back will
	stack.push_back({ 2 }); // compile error: Foo(int) is explicit
	stack.emplace_back(2);  // ok

	return 0;
}
```

- Prefer `emplace_back()` when creating a new temporary object to add to the container, or when you need to access an explicit constructor.
- Otherwise, prefer `push_back()`.
