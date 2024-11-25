Consider this program:
```cpp
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << m_id; }
};

int main()
{
    Simple simple{1};
    simple.setID(2);

    simple.print();

    return 0;
}
```

```
2
```

Somehow, when we call `simple.setID(2);`, C++ knows that function `setID()` should operate on object `simple`, and that `m_id` actually refers to `simple.m_id`.

This is because C++ utilizes a hidden pointer named `this`.

## The hidden `this` pointer

Inside every member function, the keyword **this** is a const pointer that holds the address of the current implicit object:
```cpp
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << this->m_id; } // use `this` pointer to access the implicit object and operator-> to select member m_id
};

int main()
{
    Simple simple{ 1 };
    simple.setID(2);

    simple.print();

    return 0;
}
```

The difference here is the implicit use and explicit use of this:
```cpp
void print() const { std::cout << m_id; }       // implicit use of this
void print() const { std::cout << this->m_id; } // explicit use of this
```

## How is `this` set?

Let's take a look at this function call:
```cpp
simple.setID(2);
```

When compiled, the compiler rewrites the expression as follows:
```cpp
Simple::setID(&simple, 2); // note that simple has been changed from an object prefix to a function argument!
```

This is a standard function call! Also `simple` which was an object prefix, is not passed by address as an argument to the function. Also, this function call has an added argument, therefore we need to rewrite our member function definition for `setId()`

Original member function for `setID()`:
```cpp
void setID(int id) { m_id = id; }
```

Compiler rewritten member function for `setID()`
```cpp
static void setID(Simple* const this, int id) { this->m_id = id; }
```

WTF?

The leftmost parameter of `setID()` is now `this` (in parenthesis, not brackets), which is a const pointer (meaning it can't be repointed, but the contents of the pointer can be modified). The `m_id` member has also been rewritten (in brackets) as `this->m_id`, utilizing the `this` pointer.

Putting it all together:
1. When we call `simple.setID(2)`, the compiler actually calls `Simple::setID(&simple, 2)`, and `simple` is passed by address to the function
2. The function `setID()` has a hidden parameter named `this` which receives the address of `simple`.
3. Member variables inside `setID()` are prefixed with `this->`, which points to `simple`. So when the compiler evaluates `this->m_id`, it resolves to `simple.m_id`.

But you don't need to know any of this really (or do you?).

## `this` always points to the object being operated on

```cpp
int main()
{
    Simple a{1}; // this = &a inside the Simple constructor
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()
    b.setID(4); // this = &b inside member function setID()

    return 0;
}
```

Because `this` is just a function parameter (and not a member), it doesn't make instances of your class larger memory-wise.

## Explicitly referencing `this`

If you have a member function that has a parameter with the same name as a data member, you can disambiguate them by using `this`:
```cpp
struct Something
{
    int data{}; // not using m_ prefix because this is a struct

    void setData(int data)
    {
        this->data = data; // this->data is the member, data is the local parameter
    }
};
```

Within the `setData()` function, uses of `data` refer to the function parameter due to the function parameter shadowing the data member), so if we want to reference the `data` member, we have to use `this->data`.

Some developers explicitly use `this->` for all class members to make it clear they are referencing a member. Just do yourself a favor and just prefix your member variables with "m_".

## Returning `*this`

Consider how `std::cout` works:
```cpp
std::cout << "Hello, " << userName;
```

The compiler evaluates:
```cpp
(std::cout << "Hello, ") << userName;
```

The first `operator<<` uses `std::cout` and the string literal `"Hello, "` is printed to console. However, since this is the first part of the expression, `opeartor<<` also needs to either return a value or `void`. It obviously returns a value since `void` would be nonsense:
```cpp
void{} << userName;
```

Instead, `operator<<` returns the stream (`ostream`) object that was passed in, which was `std::cout`:
```cpp
(std::cout) << userName;
```

This is called **function chaining** and it's how `std::cout` can chain output together.

Let's implement this with our member functions. Consider this example:
```cpp
class Calc
{
private:
    int m_value{};

public:

    void add(int value) { m_value += value; }
    void sub(int value) { m_value -= value; }
    void mult(int value) { m_value *= value; }

    int getValue() const { return m_value; }
};
```

If we wanted to add 5, subtract 3, and multiply 4, we'd have to do this:
```cpp
#include <iostream>

int main()
{
    Calc calc{};
    calc.add(5); // returns void
    calc.sub(3); // returns void
    calc.mult(4); // returns void

    std::cout << calc.getValue() << '\n';

    return 0;
}
```

However, if we make each function return `*this` by reference, we can chain the calls together:
```cpp
class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }
};
```

This allows us to do this in our `main()`:
```cpp
#include <iostream>

int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4); // method chaining

    std::cout << calc.getValue() << '\n';

    return 0;
}
```

In `calc.add(5).sub(3).mult(4);` we first have `calc.add(5)`, which adds `5` to `m_value`. `add()` then returns a reference to `*this`, which is a reference to the implicit object `calc`, so `calc` will be the object used in the subsequent evaluation when returned like so: `calc.sub(3).mult(4);`. This continues until `calc` isn't used in the return and is thus ignored. We end up getting (((0 + 5) - 3) * 4).

## Resetting a class back to default state

We can use `*this` to create a `reset()` member function that can reset a class back to the default state:
```cpp
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}
```

In use it's like this:
```cpp
#include <iostream>

class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }

    void reset() { *this = {}; }
};


int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4);

    std::cout << calc.getValue() << '\n'; // prints 8

    calc.reset();

    std::cout << calc.getValue() << '\n'; // prints 0

    return 0;
}
```


