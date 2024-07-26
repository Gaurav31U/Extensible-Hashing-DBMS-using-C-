# Extensible Hashing Implementation in C++ STL
## Introduction
This project implements Extensible Hashing using C++ Standard Template Library (STL). Extensible Hashing is a dynamic hashing scheme where the hash function can adapt to the dataset's size dynamically, providing efficient handling of the dictionary operations like search, insert, and delete.

## Overview
The core idea of Extensible Hashing is to use a directory that points to buckets. The directory can grow or shrink dynamically, adapting to the number of elements. Each bucket can split into two when it overflows, and the directory can double in size when necessary. Conversely, buckets can merge, and the directory can shrink when there are too few elements.

## Implementation Details

### Files
- `main.cpp`: Contains the implementation of Extensible Hashing and the main function to execute the operations.

### Data Structures
- **Global Depth:** An integer representing the global depth of the hash table.
- **Directory (`unordered_map<string, string>`):** Maps the hash values to bucket addresses.
- **Buckets (`unordered_map<string, vector<int>>`):** Stores the actual elements, mapped by bucket addresses.

### Key Functions
1. **`hashfun(int n, int len)`**: Computes the hash value for a given integer.
2. **`intialize(int N, unordered_map<string,string> &temp)`**: Initializes the directory with global depth `N`.
3. **`splitbucket(string s, string h)`**: Splits a bucket when it overflows.
4. **`expansion(string s)`**: Expands the directory and splits buckets when necessary.
5. **`shrink()`**: Shrinks the directory if there are too few elements.
6. **`search(int val)`**: Searches for a given value in the hash table.
7. **`drop(string s, string h)`**: Merges buckets when they are underutilized.
8. **`insert(int val)`**: Inserts a new value into the hash table.
9. **`remove(int val)`**: Removes a value from the hash table.
10. **`showall()`**: Displays all the current elements in the hash table along with the directory and bucket structure.

### Usage
1. **Insert Data**
   - Command: `1`
   - Input: Integer value to be inserted.
2. **Delete Data**
   - Command: `2`
   - Input: Integer value to be deleted.
3. **Show Data**
   - Command: `3`
   - Displays the current state of the hash table, including the global depth, number of buckets, and elements in each bucket.
4. **Exit**
   - Command: `0`
   - Terminates the program.

