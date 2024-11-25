## The as-if rule

- **as-if rule:** states that the compiler can modify a program however it likes in order to produce more optimized code, so long as those modifications do not affect a program's "observable behavior".

But what does "observable behavior" mean? Since the compiler itself optimizes a given program, a lot is abstracted away from us, the developer. However, there are things we can do to help the compiler BETTER optimize.

## An optimization opportunity

Let's observe this simple program as our example:
```cpp
#include <iostream>

int main()
{
    int x { 3 + 4 };
    std::cout << x << '\n';

    return 0;
}
```
This simply outputs `7`. Pretty straightforward.

However, if this program were to compile a ridonkulous (way beyond ridiculous), amount of times, then the compiler would have to calculate the redundant `3 + 4` over and over again, even though the result will always be `7`.

## Compile-time evaluation of expressions

The grand solution here! Is to just replace `3 + 4` with `7`..
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```

Basically, you want to minimize the burden on the compiler. These kinds of optimization (since these things are stored in memory), save space and make our executables blazingly faster.

## Constant expressions

One suck expression that can always be evaluated at compile time is called a "constant expression". This is a complicated subject, but I'll try and explain it simply. A **constant expression** is an expression that contains only compile-time constants and operators/functions that support compile-time evaluation. WHAT DOES THIS EVEN MEAN?

Well, let's take a trip down lesson lane:

A **compile-time constant** is a constant whose value MUST be known at compile time... This includes:

1. Literals (this makes sense)
2. Constexpr variables (Dunno what that is. Discussed in 5.05)
3. Const integral variables with a constant expression initializer (e.g. `const int x { 5 };`. This is prehistorical, and modern C++ we should use constexpr variables instead)
4. Non-type template parameters (No idea. Discussed further in 11.10)
5. Enumerators (blah-blee-bloop. Discussed further in 13.02)

**Note:**
- Const variables that are NOT compile-time constants are sometimes called **runtime constants**. That makes sense.
- Runtime constants cannot be used in a constant expression. Given the above definition of a compile-time constant needing to be known at compile time (not during compile time), it would break the definition, so that makes sense too.
- Const NON-integral variables are always runtime constants (even if they have a constant expression initializer). If such a variable needs to be compile-time constant, just define them as a constexpr variable instead.

Here's an example that helps to illustrate the identification of variables that are non-constant, runtime constant, or compile-time constants.
```cpp
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y;

    return y;
}

int main()
{
    // Non-const variables:
    int a { 5 };                 // 5 is a constant expression
    double b { 1.2 + 3.4 };      // 1.2 + 3.4 is a constant expression

    // Const integral variables with a constant expression initializer
    // are compile-time constants:
    const int c { 5 };           // 5 is a constant expression
    const int d { c };           // c is a constant expression
    const long e { c + 2 };      // c + 2 is a constant expression

    // Other const variables are runtime constants:
    const int f { a };           // a is not a constant expression, but 5 is
    const int g { a + 1 };       // a + 1 is not a constant expression, but 5 + 1 is
    const long h { a + c };      // a + c is not a constant expression, due to a AND c
    const int i { getNumber() }; // getNumber() is not a constant expression

    const double j { b };        // b is not a constant expression
    const double k { 1.2 };      // 1.2 is a constant expression

    return 0;
}
```

## So what?

Why should we care about constant expressions?

1. Constant expression are ALWAYS eligible for compile-time evaluation, meaning they are more likely to be optimized at compile-time. This produces blazingly fast and smaller code.
2. Runtime expressions have the type of the expression only known at compile-time. Constant expression have the type AND value known at compile-time. This leads to more debuggable, safer, difficult to misuse code.
3. C++ also has some features that need constant expressions... Therefore you should care because it's a part of the language? lol, ok.

The KEY takeaway here, is that constant expressions help produce code that is faster, smaller, and safer. Also, some C++ features require constant expressions.

## When are constant expressions evaluated?

The compiler chooses when to evaluate constant expressions depending on context.

```cpp
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```

Due to `x` having type `const int`, which is a constant expression initializer, it is a compile-time constant. However, because `y` doesn't have the proper "constant expression initializer", the compiler can CHOOSE whether to evaluate `3 + 4` at compile-time or runtime.

Even when not required to do so, modern compilers will USUALLY evaluate a constant expression at compile-time because it's an easy and performant optimization.

## Partial optimization of constant subexpressions

```cpp
#include <iostream>

int main()
{
    std::cout << 3 + 4 << '\n';

    return 0;
}
```

The following is has a full expression `std::cout << 3 + 4 << '\n';` and is a runtime expression. However, the `3 + 4` within the full expression,  the subexpression, is optimized under the as-if rule under a process called "constant folding". The resulting optimization is:
```cpp
#include <iostream>

int main()
{
	std::cout << 7 << '\n';

	return 0;
}
```

## Optimization of non-constant expressions

There's even a potential that a smart compiler will realize that x, even though it's non-const, always evaluates to `7`, and therefore turn a program from this:
```cpp
#include <iostream>

int main()
{
	int x { 7 };            // x is non-const
	std::cout << x << '\n'; // x is a non-constant subexpression

	return 0;
}
```
To this:
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << 7 << '\n';

	return 0;
}
```
Since `x` is no longer in use, the compiler could go 1 step further:
```cpp
#include <iostream>

int main()
{
	std::cout << 7 << '\n';

	return 0;
}
```
That's one smart compiler!

## But why assume when you can bend the compiler to your will?

Consider the following change to the program:

```cpp
#include <iostream>

int main()
{
	const int x { 7 }; // x is now const
	std::cout << x << '\n';

	return 0;
}
```

Now there is no inferencing. Now there is only truth. Only optimization. The above will be optimized. Period.


