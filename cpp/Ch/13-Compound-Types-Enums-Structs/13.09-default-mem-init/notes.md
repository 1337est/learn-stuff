When we define a struct (or class) type, we can provide a default initialization value for each member as part of the type definition. For members not marked as `static`, this process is sometimes called **non-static member initialization**. The initialized value is called a **default member initializer**.

```cpp
struct Something
{
    int x;       // no initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1; // s1.x is uninitialized, s1.y is 0, and s1.z is 2

    return 0;
}
```

## Explicit initialization values take precedence over default values

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s2 { 5, 6, 7 }; // use explicit initializers for s2.x, s2.y, and s2.z (no default values are used)

    return 0;
}
```

## Missing initializers in an initializer list when default values exist

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s3 {}; // value initialize s3.x, use default values for s3.y and s3.z

    return 0;
}
```

The thing worth noting above is `s3.x` (which has no default member initializer) is value initialized to `0`, `s3.y` is value initialized to default `0`, and `s3.z` is defaulted to `2`. This is because `s3` is list initialized with an empty list, so all initializers are missing. This means that a default member initializer will be used if it exists, and value initialization will occur otherwise. And value initialization will occur otherwise. That's why `s3.x` is value initialized to `0`.

## Recapping the initialization possibilities

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1;             // No initializer list: s1.x is uninitialized, s1.y and s1.z use defaults
    Something s2 { 5, 6, 7 }; // Explicit initializers: s2.x, s2.y, and s2.z use explicit values (no default values are used)
    Something s3 {};          // Missing initializers: s3.x is value initialized, s3.y and s3.z use defaults

    return 0;
}
```

- It's best practice to provide a default value for all members. This ensures that your members will be initialized even if the variable definition doesn't include an initializer list.

## Default initialization vs value initialization for aggregates

```cpp
Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
```

`f1` is default initialized and `f2` is value initialized, but both still get the same values, so which should we prefer?

- For aggregates, it's best practice to prefer value initialization (with an empty braces initializer) rather than default initialization (with no braces).
