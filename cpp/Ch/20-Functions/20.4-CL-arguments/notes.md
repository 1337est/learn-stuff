**Command line arguments** are optional string arguments that are passed by the OS to the program when it is launched.

## Passing command line arguments

For Unix-based OS's you would invoke a program like so:
```bash
./WordCount
```

In order to pass command line arguments to WordCount, we simply pass in the argument after the executable name:
```bash
WordCount Myfile.txt Myotherfile.txt
```

## Using command line arguments

How do we access them from within our C++ program? To do so, we use a different for of `main()` than we've seen before. This new form of `main()` uses 2 arguments (conventionally named argc and argv):
```cpp
int main(int argc, char* argv[])
```

**argc** is an integer parameter containing the count of the number of arguments passed to the program (argument count). argc will always be at least 1 since the first argument is the program itself. Every command line argument causes argc to increment by 1.

**argv** is where the actual argument values are stored (argument values/vectors). argv is just a C-style array of char pointers (each of which points to a C-style string). The length of this array is argc.


