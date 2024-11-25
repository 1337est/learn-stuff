## What is void?

Void is an incomplete type. An incomplete type is a type that has been declared, but is not defined. Incomplete types cannot be instantiated:
```cpp
void value; // won't work, variables can't be defined with incomplete type void
```

Void is typically used for functions that don't return a value:
```cpp
void writeValue(int x) // void here means no return value
{
    std::cout << "The value of x is: " << x << '\n';
    // no return statement, because this function doesn't return a value
}
```
