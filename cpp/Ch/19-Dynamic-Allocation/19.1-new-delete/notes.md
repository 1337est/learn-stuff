## The need for dynamic memory allocation

C++ supports 3 basic types of memory allocation, of which 2 you've seen:
1. **Static memory allocation** -- happens for static and global variables. Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.
2. **Automatic memory allocation** -- happens for function parameters and local variables. Memory for these types of variables is allocated when the relevant block is entered, and freed when the block is exited, as many times as necessary.
3. **Dynamic memory allocation** -- the topic of this article. Dynamic memory allocation is a way for running programs to request memory from the OS when needed. This memory does not come from the program's limited stack memory -- instead, it is allocated from a much larger pool of memory managed by the OS called the **heap** (which on modern machines can be gigabytes in size).

## Dynamically allocating single variables

To allocate a single variable dynamically, we use the scalar (non-array) form of the **new** operator:
```cpp
new int; // dynamically allocate an integer (and discard the result)
```

The `new` operator creates the object using an `int` size of memory, and returns a pointer containing the address of the memory that has been allocated.

A useful example:
```cpp
int* ptr{ new int }; // dynamically allocate an integer and assign the address to ptr so we can access it later
```

We can then dereference the pointer to access the memory:
```cpp
*ptr = 7; // assign value of 7 to allocated memory
```

It's worth noting that accessing the heap-allocated objects is slower than accessing stack-allocated objects.

Unlike static or automatic memory, the program itself is responsible for requesting and disposing of dynamically allocated memory.

## Initializing a dynamically allocated variable

```cpp
int* ptr1{ new int (5) }; // use direct initialization
int* ptr2{ new int { 6 } }; // use uniform initialization
```

## Deleting a single variable

When you are done with dynamically allocated variables, you need to explicitly remove them with the **delete** operator:
```cpp
// assume ptr has previously been allocated with operator new
delete ptr; // return the memory pointed to by ptr to the operating system
ptr = nullptr; // set ptr to be a null pointer
```

## What does it mean to delete memory?

Of course you aren't deleting anything. You are simply freeing up space so that the OS can freely assign that memory to whatever it wants.

## Memory leaks

Let's say we have a function:
```cpp
void doSomething()
{
    int* ptr{ new int{} };
}
```

This function allocates an integer dynamically, but never frees it using delete. This means the program has now "lost" the address of the dynamically allocated memory. As a result, this dynamically allocated integer can not be deleted.

This is called a **memory leak**. Memory leaks happen when your program loses the address of some bit of dynamically allocated memory before giving it back to the operating system. The program can't delete it because it doesn't know where it is. The OS can't use the memory, because the memory is still considered as "in use" by the program. Oh no =(


