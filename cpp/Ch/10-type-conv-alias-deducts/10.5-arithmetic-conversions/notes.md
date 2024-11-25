When you have:
```cpp
int x {2 + 3 };
```

there is no conversion. But when you have:
```cpp
??? y { 2 + 3.5 };
```

Is second one int? or double? When there is a mismatch like this, there is a **usual arithmetic conversion** rule that gets applied to implicitly convert differing operands.

## Operators that require operands of the same type
- binary arithmetic operators: +, -, *, /, %
- binary relational opeartors: <, >, <=, >=, ==, !=
- binary bitwise arithmetic operators: &, ^, |
- conditional operator `?:` (excluding the condition, which is of type `bool`)

## Usual arithmetic conversion rules

Compiler type rankings:

1. long double (highest rank)
2. double
3. float
4. long long
5. long
6. int (lowest rank)

This is why our ints get converted to floats, because float is ranked higher.

Let's look further by using the `typeid` operator included in the `<typeinfo>` header file to show the resulting type of some expressions:

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    int i{ 2 };
    double d{ 3.5 };
    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    return 0;
}
```

Since double has higher ranking, we get output:
```
double 5.5
```

Another example:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b

    return 0;
}
```

Because neither operand (shorts) appear in the rankings/priority list, both operands undergo integral promotion to type `int`, resulting in output:
```
int 9
```


