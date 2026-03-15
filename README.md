# Mini NumPy in C

A small experimental library that mimics some basic ideas of NumPy using the C language.
The goal of this project is to practice pointers, dynamic memory allocation, and generic data handling in C.

# Features
- Create a 2D array structure (array)
- Dynamic memory allocation
- Support for multiple data types using `void *`
- Basic shape management (rows, cols)
- Memory-safe destruction with free_array

# Array Structure
The Array structure represents a 2D matrix.
``` c
typedef struct {
    void **lines;
    int *shape;
} Array;
```

Where:
- lines → pointers to each row
- shape → [rows, columns]
- dtype → data type stored in the array

# License
MIT License
