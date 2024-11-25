Consider the following code snippet:
```cpp
int main()
{
    int x { 5 };
    int* ptr { &x }; // ptr is a normal (non-const) pointer

    int y { 6 };
    ptr = &y; // we can point at another value

    *ptr = 7; // we can change the value at the address being held

    return 0;
}
```

However, what happens if the value we want to point at is const?
```cpp
int main()
{
    const int x { 5 }; // x is now const
    int* ptr { &x };   // compile error: cannot convert from const int* to int*

    return 0;
}
```
Obviously the solution here is to add the const identifier...

## Pointer to const value

A **pointer to a const value** (called a `pointer to const`) is a non-const pointer that points to a constant value. Let me repeat that. A pointer to a const value, is a NON-CONST pointer that POINTS to a CONST value.

To declare a pointer to a const value, just use the `const` keyword before the pointer's data type:
```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // okay: ptr is pointing to a "const int"

    *ptr = 6; // not allowed: we can't change a const value

    return 0;
}
```

In the above example, because `ptr` is pointing to a `const int`, the value being pointed to can't be changed.

However, because a pointer to a const isn't a const itself, we can still change what the pointer is pointing at by assigning the pointer a new address:
```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // ptr points to const int x

    const int y{ 6 };
    ptr = &y; // okay: ptr now points at const int y

    return 0;
}
```

Just like reference to const, a pointer to const can point to non-const variables too. A pointer to const treats the value being pointed to as constant, regardless of whether the object at the address was initially defined as const or not:
```cpp
int main()
{
    int x{ 5 }; // non-const
    const int* ptr { &x }; // ptr points to a "const int"

    *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
    x = 6; // allowed: the value is still non-const when accessed through non-const identifier x

    return 0;
}
```

## Const pointers

- This is different from pointers to const value.

To make a pointer itself constant, we use the `const` keyword after the asterisk in the pointer declaration:
```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // const after the asterisk means this is a const pointer

    return 0;
}
```

What we are making constant here, is the pointer's variable address. It will only point to x and can't point at anything else. The value can change since x is non-const, but the pointer can't point to anything else. It's stuck on x.
```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // ptr will always point to x

    *ptr = 6; // okay: the value being pointed to is non-const

    return 0;
}
```

## Const pointer to a const value

Now we can confusingly combine these 2 consts to make a **const pointer to a const value**:
```cpp
int main()
{
    int value { 5 };
    const int* const ptr { &value }; // a const pointer to a const value

    return 0;
}
```

This const pointer to a const value, cannot have its address changed, nor can the value it's pointing to be changed through the pointer (you can still change it via the variable `value` since it's non const). The const pointer to a const value can only be dereferenced to get the value it is pointing at.

## Pointer and const recap

```cpp
int main()
{
    int v{ 5 };

    int* ptr0 { &v };             // points to an "int" but is not const itself, so this is a normal pointer.
    const int* ptr1 { &v };       // points to a "const int" but is not const itself, so this is a pointer to a const value.
    int* const ptr2 { &v };       // points to an "int" and is const itself, so this is a const pointer (to a non-const value).
    const int* const ptr3 { &v }; // points to a "const int" and is const itself, so this is a const pointer to a const value.

    // if the const is on the left side of the *, the const belongs to the value
    // if the const is on the right side of the *, the const belongs to the pointer

    return 0;
}
```
