## Pointers to pointers

A pointer to a pointer is exactly what you'd expect: a pointer that holds the address of another pointer.

A pointer to an int:
```cpp
int* ptr; // pointer to an int, one asterisk
```

A pointer to a pointer to an int:
```cpp
int** ptrptr; // pointer to a pointer to an int, two asterisks
```

In use:
```cpp
int value { 5 };

int* ptr { &value };
std::cout << *ptr << '\n'; // Dereference pointer to int to get int value

int** ptrptr { &ptr };
std::cout << **ptrptr << '\n'; // dereference to get pointer to int, dereference again to get int value
```

## Arrays of pointers

The most common use case of pointers to pointers is to dynamically allocate an array of pointers:
```cpp
int** array { new int*[10] }; // allocate an array of 10 int pointers
```


