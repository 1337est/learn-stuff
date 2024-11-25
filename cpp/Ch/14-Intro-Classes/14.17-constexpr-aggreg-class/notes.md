Constexpr functions may be evaluated at either compile-time or runtime:
```cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    std::cout << greater(5, 6);        // greater(5, 6) may be evaluated at compile-time or runtime

    constexpr int g { greater(5, 6) }; // greater(5, 6) must be evaluated at compile-time
    std::cout << g;                    // prints 6

    return 0;
}
```

In this example, `greater()` is a constexpr function, and `greater(5, 6)` is a constant expression which may be evaluated at compile-time or runtime. Because `std::cout << greater(5, 6)` calls `greater(5, 6)` in a non-constexpr context, the compiler is free to choose whether to evaluate `greater(5, 6)` at compile-time or runtime. However, when `greater(5, 6)` is used to initialize constexpr variable `g`, `greater(5, 6)` is called in a constexpr context and must be evaluated at compile-time.

## Constexpr member functions

Just like non-member functions, member functions may be made constexpr via use of the `constexpr` keyword. This tells the compiler that the member function can be evaluated at either compile-time or runtime:
```cpp
#include <iostream>

struct Pair
{
    int m_x {};
    int m_y {};

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    Pair p { 5, 6 };
    std::cout << p.greater();        // p.greater() evaluates at runtime

    constexpr int g { p.greater() }; // compile error: p not constexpr
    std::cout << g;

    return 0;
}
```

In this example, we've made `greater()` a constexpr function, so the compiler can evaluate it at either runtime or compile-time. Then why does it generate a compile error when `p.greater()` is used to initialize constexpr variable `g`? Although `greater()` is constexpr, `p.greater()` is not because `p` is not constexpr.

Alright, let's make `p` constexpr:
```cpp
#include <iostream>

struct Pair // Pair is an aggregate
{
    int m_x {};
    int m_y {};

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };       // now constexpr
    std::cout << p.greater();        // p.greater() evaluates at runtime or compile-time

    constexpr int g { p.greater() }; // p.greater() must evaluate at compile-time
    std::cout << g;

    return 0;
}
```

Since `Pair` is an aggregate, and aggregates implicitly support being constexpr, we're done.

## Constexpr class objects and constexpr constructors

Now let's make our `Pair` a non-aggregate:
```cpp
#include <iostream>

class Pair // Pair is no longer an aggregate
{
private:
    int m_x {};
    int m_y {};

public:
    Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };       // compile error: p is not a literal type
    std::cout << p.greater();

    constexpr int g { p.greater() };
    std::cout << g;

    return 0;
}
```

In C++, a **literal type** is any type for which it might be possible to create an object within a constant expression. Said in reverse: An object cannot be a constexpr unless the type qualifies as a literal type. This makes sense since our compiler is optimizing to turn our constant expressions into literal values, and our non-aggregate `Pair` does not qualify.

Literal types include:
- Scalar types (single values, such as fundamental types and pointers)
- Reference types
- Most aggregates
- Classes that have a constexpr constructor (Ah-ha!)

Therefore the fix is simple. We make our constructor `constexpr` as well:
```cpp
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };
    std::cout << p.greater();

    constexpr int g { p.greater() };
    std::cout << g;

    return 0;
}
```

Now this works as expected.
