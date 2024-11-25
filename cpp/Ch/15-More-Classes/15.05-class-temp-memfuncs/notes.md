This is the basic rundown of templates so far:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's a deduction guide for our Pair (required in C++17 or older)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```

Now let's combine elements of function templates and class templates.

## Type template parameters in member functions

Let's convert our struct to a class:
```cpp
#includee <ios>         // for std::boolalpha
#include <iostream>

template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    // When we define a member function inside the class definition
    // the template parameter declaration belonging to the class applies
    Pair(const T& first, const T& second)
        : m_first{ first }
        , m_second{ second }
    {
    }

    bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
    Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

    return 0;
}
```

The logic is straightforward, but there are a few noteworthy things to mention.
1. Our class has private members, therefore it is a non-aggregate and cannot use aggregate initialization. Instead, we initialize our class object using a constructor.
2. Our class data members are of type `T`, so we make the parameters of our constructor `const T&` because `T` might be expensive to copy. Therefore, it's safer to pass by const reference than by value.
3. When we define a member function inside the class template definition, we don't need to provide a template parameter declaration for the member functions, but outside you do.
4. We don't need a deduction guide for CTAD to work with non-aggregate classes. A matching constructor provides the compiler with the information it needs to deduce the template parameters from the initializers.
5. Let's look at the outside member function (outside of the class template definition):
```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
```

When we define a member function outside of the class, we need to qualify the member function name with the fully templated name of the class template `Pair<T>::isEqual`, not `Pair::isEqual`.

## Where to define member functions for class templates outside the class

When a member function template is defined outside the class definition, it should be defined immediately below the class definition.

In typical cases where the class is defined in a header file, the same convention applies.


