# Getting starting with **cnumpy**

## How to build a new matrix with cnumpy
First of all, you need to know that. In cnumpy matrix, we have 2 things that our matrix is composed : _shape_ and _data_. So, for building our matrix, we need to declare them
```c
int shape[] = {3, 4};

float data[] = {
    1, 2, 3, 4,
    0, 1, 2, 3,
    4, 3, 2, 1
};
```
**data** is just a sample array but do this for readability. 
You can do like this -> 
`float data[] = {1, 2, 3, 4, 0, 1, 2, 3, 4, 3, 2, 1};`

