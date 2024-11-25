Consider the classic case where we want to calculate the maximum of 2 numbers and you write a basic function like so:
```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
```

However, this function only works for ints (or types that can be promoted to ints), and you find later on you want to find the max of 2 doubles, so you write an overloaded version of `max` with parameters of type double:
```cpp
double max(double x, double y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
```

However, having to create overloaded function with the same implementation for each set of parameter types we want to support is a maintenance headache.

Fortunately, C++ supports another feature that was designed specifically to solve this kind of problem.

## Introduction to C++ templates

Instead of manually creating a bunch of mostly-identical functions or classes, we instead create a single template. A **template** describes what a function or class looks like. Unlike a normal definition (where all types must be specified), in a template we can use one or more placeholder types, where a placeholder type represents some type that is not known at the time the template is written, but that will be provided later.

This is where learning overloaded functions comes in handy. Once a template is defined, the compiler can then use the template to generate as many overloaded functions (or classes) as needed, each using different actual types!

The end result is the same -- we end up with a bunch of mostly-identical functions or classes (one for each set of different types), but we only have to create and maintain a single template, and the compiler does all the hard work for us.

* To sum it all up: The compiler can use a single template to generate a family of related functions or classes, each using a different set of types.

## Function templates

- A **function template** is a function-like definition that is used to generate overloaded functions, each with a different set of actual types.
- Our function templates use placeholder types (called **type template parameters**, informally **template types**) for any parameter types, return types, or types used in the function body that we want to be specified later (wow, wtf. How does that work?).

Like most things, it's better to give an example. Let's revisit our `max(int, int)` function from above and transition it to a function template.

## Creating a templated max function

Here's the int version of max again:
```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
}
```

We use type `int` 3 times in this function, for `x`, `y`, and return type of the function.

To create a function template, we're going to need to do 2 things first.
1. We're going to replace our specific types with type template parameters. In this case we only have a single type to replace (`int`), so we're going to use a single template parameter (which we'll call `T`).
```cpp
T max(T x, T y) // won't compile because we haven't defined T yet. Baby steps
{
    return (x < y) ? y : x;
}
```

As you can see with the comment, the compiler doesn't know what T is. Also, this is still a normal function, not a function template.

2. Now we're going to tell the compiler that this is a function template, and that `T` is a type template parameter that is a placeholder for any type (not just `int`). This is done using a **template parameter declaration**. The scope of a template parameter declaration is limited to the function template (or class template) that follows. Therefore, each function (or class) template needs its own template parameter declaration.
```cpp
template <typename T> // this is the template parameter declaration
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}
```

For our template parameter declaration, we start with the keyword `template`, which tells the compiler that we're creating a template. Next we specify the template parameters that our template will use inside angled brackets. For each type template parameter, we'll use the keyword `typename` OR `class`, followed by the name of the type template parameter (e.g. `T`).

That's it! We're done! We've created a template version of the `max` function that can now accept arguments of different types. We'll refer to this function template with a template type name `T` as `max<T>`.

## Naming template parameters

If a type template parameter has a non-obvious usage or meaning, then a more descriptive name is warranted. There are 2 common conventions for such names:
- Starting with a capital letter (e.g. `Allocator`). The standard library uses this naming convention.
- Prefixed with a `T`, then starting with a capital letter (e.g. `TAllocator`). This makes it easier to see that the type is a type template parameter.

Which you choose is a matter of personal preference.
