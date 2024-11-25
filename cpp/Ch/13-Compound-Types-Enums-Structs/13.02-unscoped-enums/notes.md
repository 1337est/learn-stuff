Let's say you want to write a program that keeps track of colors so you can have colors for an apple or shirt or something.

You might store the color as an integer value like so:
```cpp
int main()
{
    int appleColor{ 0 }; // my apple is red
    int shirtColor{ 1 }; // my shirt is green

    return 0;
}
```

But we don't like magic numbers and this isn't intuitive. We can get rid of the magic numbers by creating symbolic constants:
```cpp
constexpr int red{ 0 };
constexpr int green{ 1 };
constexpr int blue{ 2 };

int main()
{
    int appleColor{ red };
    int shirtColor{ green };

    return 0;
}
```

However, now we have to deduce that `appleColor` and `shirtColor` (which are of type `int`) are meant to hold one of the values defined in the set of color symbolic constants...

We can go ahead and use type aliases to aid us here:
```cpp
using Color = int; // define a type alias named Color

// The following color values should be used for a Color
constexpr Color red{ 0 };
constexpr Color green{ 1 };
constexpr Color blue{ 2 };

int main()
{
    Color appleColor{ red };
    Color shirtColor{ green };

    return 0;
}
```

However, because `Color` is just an alias for `int`, we still have the problem that nothing enforces proper usage of these color symbolic constants.

## Enumerations
An **enumeration** (also called **enumerated type** or **enum**) is a compound data type whose values are restricted to a set of named symbolic constants (called **enumerators**).

C++ supports 2 kinds of enumerations: unscoped and scoped.

Enumerations are program-defined types and need to be fully defined before we can use them (a forward declaration is insufficient).

## Unscoped enumerations

Unscoped enumerations are defined via the `enum` keyword.

```cpp
// Define a new unscoped enumeration named Color
enum Color
{
    // Here are the enumerators
    // These symbolic constants define all the possible values this type can hold
    // Each enumerator is separated by a comma, not a semicolon
    red,
    green,
    blue, // trailing comma optional but recommended
}; // the enum definition must end with a semicolon

int main()
{
    // Define a few variables of enumerated type Color
    Color apple { red };   // my apple is red
    Color shirt { green }; // my shirt is green
    Color cup { blue };    // my cup is blue

    Color socks { white }; // error: white is not an enumerator of Color
    Color hat { 2 };       // error: 2 is not an enumerator of Color

    return 0;
}
```

Here we tell the compiler that we have an unscoped enumeration which we've named `Color`.

Inside the curly braces we define the enumerators for the `Color` type: `red`, `green`, and `blue`. These enumerators define the specific values that type `Color` is restricted to.

Inside `main()`, we instantiate 3 variables of type `Color`: `apple` is initialized with `red`, `shirt` with `green`, and `cup` with `blue`. Memory is allocated for each of these objects.

- Enumerators are implicitly constexpr.
- An enumeration or enumerated type is the program-defined type itself (e.g. `Color`)
- An enumerator is a specific named value belonging to the enumeration (e.g. `red`)

## Naming enumerations and enumerators

- Name you enumerated types starting with a capital letter.
- Name you enumerators starting with a lower case letter.

## Enumerated types are distinct types

Each enumerated type you create is considered to be a **distinct type**, meaning: The compiler can distinguish it from other types unlike typedefs or type aliases, which are considered non-distinct from the types they are aliasing.

Obviously the following is stupid and you would never do this:
```cpp
enum Pet
{
    cat,
    dog,
    pig,
    whale,
};

enum Color
{
    black,
    red,
    blue,
};

int main()
{
    Pet myPet { black }; // compile error: black is not an enumerator of Pet
    Color shirt { pig }; // compile error: pig is not an enumerator of Color

    return 0;
}
```

You probably didn't want a pig shirt anyways.

## Putting enumerations to use

Enumerations are commonly used to enhance code readability and documentation of code.

Some easy examples enumerations include days of the week, the cardinal directions, and the suits in a deck of cards:
```cpp
enum DaysOfWeek
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

enum CardinalDirections
{
    north,
    east,
    south,
    west,
};

enum CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,
};
```

Enumerated types can also be put to good use in games, to identify different types of items, or monsters, or terrain, etc etc etc:
```cpp
enum ItemType
{
	sword,
	torch,
	potion,
};

int main()
{
	ItemType holding{ torch };

	return 0;
}
```

## The scope of unscoped enumerations

```cpp
enum Color // this enum is defined in the global namespace
{
    red, // so red is put into the global namespace
    green,
    blue,
};

int main()
{
    Color apple { red }; // my apple is red

    return 0;
}
```

The `Color` enumeration is defined in the global scope. Therefore, all the enumerators also go into the global scope. This pollutes the global scope and significantly raises the change of naming collisions.

A consequence of this is that an enumerator name cannot be used in multiple enumerations within the same scope:
```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

enum Feeling
{
    happy,
    tired,
    blue, // error: naming collision with the above blue
};

int main()
{
    Color apple { red }; // my apple is red
    Feeling me { happy }; // I'm happy right now (even though my program doesn't compile)

    return 0;
}
```

Since `blue` is in the global scope twice, this leads to a naming collisions and a subsequent compile error.

Unscoped enumerations also provide a named scope region for t heir enumerators (much like a namespace acts as a named scope region for the named declared within). This means we can access the enumerators of an unscoped enumeration as follows:
```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

int main()
{
    Color apple { red }; // okay, accessing enumerator from global namespace
    Color raspberry { Color::red }; // also okay, accessing enumerator from scope of Color

    return 0;
}
```

- Unscoped enumerations are named such, because they put their enumerator names into the same scope as the enumeration definition itself (as opposed to creating a new scope region like a namespace does).

## Avoiding enumerator naming collisions

One option is to prefix each enumerator with the name of the enumeration:
```cpp
enum Color
{
    color_red,
    color_blue,
    color_green,
};

enum Feeling
{
    feeling_happy,
    feeling_tired,
    feeling_blue, // no longer has a naming collision with color_blue
};

int main()
{
    Color paint { color_blue };
    Feeling me { feeling_blue };

    return 0;
}
```

I don't like this. Too long. A better option is to put the enumerated type inside something that provides a separate scope region, such as a namespace:
```cpp
namespace Color
{
    // The names Color, red, blue, and green are defined inside namespace Color
    enum Color
    {
        red,
        green,
        blue,
    };
}

namespace Feeling
{
    enum Feeling
    {
        happy,
        tired,
        blue, // Feeling::blue doesn't collide with Color::blue
    };
}

int main()
{
    Color::Color paint{ Color::blue };
    Feeling::Feeling me{ Feeling::blue };

    return 0;
}
```

This means we have to prefix our enumeration and enumerator names with the name of the scoped region. Better than having naming conflicts. An even better option is scoped enumerations (which we'll discuss in 13.6).

- Prefer putting your enumerations inside a named scope region (such as a namespace or class) so the enumerators don't pollute the global namespace.


