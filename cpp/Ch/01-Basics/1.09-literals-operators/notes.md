## What are literals?
- **literals**: a fixed value that has been inserted directly into the source code
```cpp
std::cout << "Hello world!";
int x { 5 };
```
Both `"Hello world!"` and `5` are literals.

Consider the following to highlight the differences between literals and variables:
```cpp
#include <iostream>

int main()
{
    std::cout << 5 << '\n'; // print the value of a literal

    int x { 5 };
    std::cout << x << '\n'; // print the value of a variable
    return 0;
}
```
Both output statements print the "value" of 5. However, the difference is how the compiler does this.
In the `std::cout << 5` instance, the value `5` is compiled into the executable and can be used directly.
In the `std::cout << x` instance, the compiler generates code that copies the literal value `5` INTO the memory location given to `x`. Therefore, when we print the value using `std::cout`, the compiler prints the value at the memory location of `x`, which is `5`.

## What are operators?
- **operators**: You operate on operands with operators. In the case of 2 + 3 = 5:
operands: 2 & 3
operator: +
operation: 2 + 3

There are operators like addition (+), subtraction (-), multiplication (*), division (/), assignment (=), insertion (<<), extraction (>>), and equality (==). However, there are also operators that are keywords (e.g. `new`, `delete`, and `throw`).

## Neat words?
- **arity**: The number of operands that an operator takes as input is an operator's arity.
- **unary**: A type of operator that acts on one operand, e.g. -5
- **binary**: A type of operator that acts on 2 operands, e.g. 3 + 4
- **ternary**: An operator that acts on 3 operands (the conditional operator)
- **nullary**: Acts on 0 operands? (the throw operator)

Operators still have the order of PEMDAS: Parenthesis, Exponents, Multiplication & Division, Addition & Subtraction

## Return values
Most operators have return values like `-5` returning `-5`, `2+3` return `5`, etc. However, there are a few operators that do not produce return values, such as `delete` and `throw`.
