## The properties of an expression

To help determine how expressions should evaluate and where they can be used, all expressions in C++ have 2 properties: a **type** and a **value category**.

## The type of an expression

This is straight forward. The type of an expression is the evaluated type of the expression.
```cpp
int main()
{
    auto v1 { 12 / 4 }; // int / int => int
    auto v2 { 12.0 / 4 }; // double / int => double

    return 0;
}
```

## The value category of an expression

Consider the following:
```cpp
int main()
{
    int x{};

    x = 5; // valid: we can assign 5 to x
    5 = x; // error: can not assign value of x to literal value 5

    return 0;
}
```

The **value category** of an expression (or subexpression) indicates whether an expression resolves to a value, a function, or an object of some kind.

Prior to C++11, there were only 2 possible value categories: `lvalue` and `rvalue`.

In C++11, 3 additional value categories were added to support a new feature called `move semantics`: `glvalue`, `prvalue`, and `xvalue` (we'll cover these additional 3 in a later chapter)

## Lvalue and rvalue expressions

- An **lvalue** (short for "left value") is an expression that evaluates to an identifiable object or function (or bit-field).
```cpp
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression

    return 0;
}
```

In the above program, the expression `x` is an lvalue expression as it evaluates to variable `x` (which has an identifier). An entity (such as an object or function) that has an "identity" can be differentiated from similar entities (typically by comparing the addresses of the entities).

Entities with identities can be accessed via an identifier, reference, or pointer, and typically have a lifetime longer than a single expression or statement.

Since the introduction of constants into the language, lvalues come in 2 subtypes: a **modifiable lvalue** and **non-modifiable lvalue**. It's an lvalue that either can or cannot be modified (because the lvalue is const or constexpr).

```cpp
int main()
{
    int x{};
    const double d{};

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression

    return 0;
}
```

- An **rvalue** (short for "right value") is an expression that is not an lvalue (lol). Rvalue expressions evaluate to a value.
```cpp
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```

Rvalues aren't identifiable (meaning they have to be used immediately), and only exist within the scope of the expression in which they are used.

In C++11, rvalues are broken into 2 subtypes: prvalues and xvalues, so the rvalues we're talking about here are the sum of both of those categories.

**Takeaway:**
- Lvalue expressions evaluate to an identifiable object.
- Rvalue expressions evaluate to a value.

Now let's reconsider our `5 = x` scenario: an assignment operation requires the left operand of the assignment to be a modifiable lvalue expression, and the right operand to be an rvalue expression.
```cpp
int main()
{
    int x{};

    // Assignment requires the left operand to be a modifiable lvalue expression and the right operand to be an rvalue expression
    x = 5; // valid: x is a modifiable lvalue expression and 5 is an rvalue expression
    5 = x; // error: 5 is an rvalue expression and x is a modifiable lvalue expression

    return 0;
}
```

## Lvalue to rvalue conversion

```cpp
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression

    return 0;
}
```

If `x` is an lvalue expression that evaluates to variable `x`, then how does `y` get `5`?

Lvalue expressions will implicitly convert to rvalue expressions in contexts where an rvalue is expected, but an lvalue is provided.
