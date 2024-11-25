By default, type deduction will drop `const` and `constexpr` qualifiers:
```cpp
const double foo()
{
    return 5.6;
}

int main()
{
    const double cd{ 7.8 };

    auto x{ cd };    // double (const dropped)
    auto y{ foo() }; // double (const dropped)

    return 0;
}
```
Const and constexpr can be reapplied by adding the `const` or constexpr qualifiers in the definition:
```cpp
const double foo()
{
    return 5.6;
}

int main()
{
    constexpr double cd{ 7.8 };

    const auto x{ foo() };  // const double (const dropped, const reapplied)
    constexpr auto y{ cd }; // constexpr double (constexpr dropped, constexpr reapplied)
    const auto z { cd };    // const double (constexpr dropped, const applied)

    return 0;
}
```

## Type deduction drops references

```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref { getRef() }; // type deduced as std::string (not std::string&)

    return 0;
}
```

Although `getRef()` returns a `std::string&`, the reference qualifier is dropped, so the type of `ref` is deduced as `std::string`.

References can be reapplied at the point of definition:
```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref1 { getRef() };  // std::string (reference dropped)
    auto& ref2 { getRef() }; // std::string& (reference reapplied)

    return 0;
}
```

## Top-level const and low-level const

- A **top-level const** is a const qualifier that applies to an object itself:
```cpp
const int x;    // this const applies to x, so it is top-level
int* const ptr; // this const applies to ptr, so it is top-level
```

- A **low-level const** is a const qualifier that applies to the object being referenced or pointed to:
```cpp
const int& ref; // this const applies to the object being referenced, so it is low-level
const int* ptr; // this const applies to the object being pointed to, so it is low-level
```

A reference to a const value is always a low-level const. A pointer can have a top-level, low-level, or both kinds of const:
```cpp
const int* const ptr; // the left const is low-level, the right const is top-level
```

Type deduction only drops top-level consts, not low-level consts.


