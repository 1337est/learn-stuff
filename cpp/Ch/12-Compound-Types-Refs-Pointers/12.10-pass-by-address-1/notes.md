We've already learned about pass by reference and pass by value. Here's a sample program that shows a `std::string` object being passed by value and by reference:
```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str

    return 0;
}
```

In both cases, the caller is providing the actual object (`str`) to be passed as an argument to the function call.

## Pass by address

With **pass by address**, instead of providing an object as an argument, the caller provides an object's address (via a pointer).
```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    return 0;
}
```

Let's address the pass by address version a little more in detail.

1. Because we want our `printByAddress()` function to use pass by address, we've made our function parameter a pointer named `ptr`. Since `printByAddress()` will use `ptr` in a read-only manner, `ptr` is a pointer to a const value (before the asterisk).
```cpp
void printByAddress(const std::string* ptr)
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}
```
Inside the `printByAddress()` function, we dereference `ptr` paramaeter to access the value of the object being pointed to.

2. When the function is called, we can't just pass in object `str` -- we need to pass in the address of `str`. Remember how parameters and arguments work? When we have this function with parameters: `void printByAddress(const std::string* ptr)` and we pass in the argument `printByAddress(&str)`, we are essentially initializing this way:
```cpp
const std::string* ptr{ &str }; // the passed in argument is within brackets
```

That's why we have to add in the ampersand:
```cpp
printByAddress(&str); // use address-of operator (&) to get pointer holding address of str
```

That's it. When this call is executed, `&str` will create a pointer holding the address of `str`. This address is then copied into the function parameter `ptr` as part of the function call. Since `ptr` now holds the address of `str`, when the function dereferences `ptr`, it will get t he value of `str`, which the function prints to the console.

We could also do something like this:
```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    // previous implementations
    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    // Using a pointer variable holding the address of str
    std::string* ptr { &str }; // define a pointer variable holding the address of str
    printByAddress(ptr); // pass str by address, does not make a copy of str

    return 0;
}
```

## Pass by address does not make a copy of the object being pointed to

Remember, copying a `std::string` is expensive, so that's something we want to avoid doing. Just like pass by reference, pass by address is fast, and avoids making a copy of the argument object. Since an address is typically only 4 or 8 bytes, a pointer is only 4 or 8 bytes, so copying a pointer is always fast.

## Pass by address allows the function to modify the argument's value

Consider the following:
```cpp
#include <iostream>

void changeValue(int* ptr) // note: ptr is a pointer to non-const in this example
{
    *ptr = 6; // change the value to 6
}

int main()
{
    int x{ 5 };

    std::cout << "x = " << x << '\n';

    changeValue(&x); // we're passing the address of x to the function

    std::cout << "x = " << x << '\n';

    return 0;
}
```
This prints:
```
x = 5
x = 6
```

## Null checking

Make sure to check with conditionals when passing a parameter by address. Care should be taken to ensure the pointer is not a null pointer before you dereference the value:
```cpp
#include <iostream>

void print(int* ptr)
{
    if (ptr) // if ptr is not a null pointer
    {
        std::cout << *ptr << '\n';
    }
}

int main()
{
    int x{ 5 };

    print(&x);
    print(nullptr);

    return 0;
}
```

In most cases it's best to test whether the function parameter is null as a precondition and handle the negative case immediately:
```cpp
#include <iostream>

void print(int* ptr)
{
    if (!ptr) // if ptr is a null pointer, early return back to the caller
        return;

    // if we reached this point, we can assume ptr is valid
    // so no more testing or nesting required

    std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

If a null pointer should never be passed to the function, an `assert` can be used instead (or also) since asserts are meant to document things that should never happen:
```cpp
#include <iostream>
#include <cassert>

void print(const int* ptr) // now a pointer to a const int
{
	assert(ptr); // fail the program in debug mode if a null pointer is passed (since this should never happen)

	// (optionally) handle this as an error case in production mode so we don't crash if it does happen
	if (!ptr)
		return;

	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

## Prefer pass by (const) reference

Pass by reference has the same benefits as pass by address without the risk of inadvertently dereferencing a null pointer.

Pass by const reference has a few advantages over pass by address as well.
1. Because an object being passed by address must have an address, only lvalues can be passed by address (since rvalues don't have addresses). Pass by const reference accepts lvalues and rvalues.
```cpp
#include <iostream>

void printByValue(int val) // The function parameter is a copy of the argument
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    printByValue(5);     // valid (but makes a copy)
    printByReference(5); // valid (because the parameter is a const reference)
    printByAddress(&5);  // error: can't take address of r-value

    return 0;
}
```

2. The syntax for pass by reference is natural, since we can just pass in literals or objects. With pass by addresses, our code ends up littered with ampersands (&) and asterisks (*) which don't look pretty.

- Pass by reference when you can, pass by address when you must.
