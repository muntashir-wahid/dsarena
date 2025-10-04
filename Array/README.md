# Array ADT Implementation Documentation

## Overview

This document provides a comprehensive overview of a custom Array Abstract Data Type (ADT) implemented in C++. The implementation demonstrates fundamental concepts of dynamic memory management, encapsulation, and basic array operations.

An Array ADT is a linear data structure that stores elements in contiguous memory locations with a fixed capacity. Unlike the standard C++ array, this implementation provides a clean interface with bounds checking and dynamic memory management through RAII (Resource Acquisition Is Initialization) principles.

## Design Philosophy

The Array ADT is designed with the following principles:

**Fixed Capacity, Dynamic Allocation**: The array has a predetermined maximum capacity set at construction time, but memory is allocated dynamically on the heap. This provides flexibility in capacity selection while maintaining simplicity in implementation.

**Size vs Capacity Distinction**: The implementation maintains a clear separation between `size` (current number of elements) and `capacity` (maximum possible elements). This allows the array to grow incrementally without immediate reallocation.

**Memory Safety**: The destructor ensures proper cleanup of dynamically allocated memory, preventing memory leaks. The implementation follows RAII principles where resource acquisition and release are tied to object lifetime.

**Bounds Checking**: Operations that could exceed capacity throw exceptions rather than causing undefined behavior, providing safer runtime characteristics.

## Class Structure

The Array class maintains three private member variables:

- `int* data`: Pointer to dynamically allocated array on the heap
- `int size`: Current number of elements stored in the array
- `int capacity`: Maximum number of elements the array can hold

## Constructor & Destructor

### Constructor: `Array(int capacity)`

**Purpose**: Initializes a new Array object with a specified maximum capacity.

**Implementation Details**: The constructor allocates memory on the heap for the specified capacity and initializes the size to zero. This follows a lazy initialization pattern where memory is allocated upfront but elements are added incrementally.

**Time Complexity**: O(1)

The constructor performs a constant number of operations regardless of capacity. While memory allocation occurs, the allocation operation itself is considered constant time. No iteration or element initialization is performed.

**Memory Allocation**: Allocates `capacity * sizeof(int)` bytes on the heap.

---

### Destructor: `~Array()`

**Purpose**: Cleans up dynamically allocated memory when the Array object goes out of scope.

**Implementation Details**: Uses `delete[]` to properly deallocate the array memory, preventing memory leaks. This is a critical component of the RAII pattern, ensuring deterministic resource cleanup.

**Time Complexity**: O(1)

Deallocation is a constant-time operation handled by the memory manager. While the actual deallocation process may involve internal bookkeeping, from the user's perspective it's a single operation independent of array size.

## Helper Methods

### Private Method: `has_capacity()`

**Purpose**: Checks whether the array has room for additional elements.

**Implementation Details**: Returns `true` if the current size is less than the capacity, indicating available space. This encapsulates the capacity checking logic, promoting code reuse and maintainability.

**Time Complexity**: O(1)

Performs a single integer comparison operation.

---

### Private Method: `is_valid_position(int index) const`

**Purpose**: Validates whether a given index is a valid position for insertion operations.

**Implementation Details**: Returns `true` if the index is within the valid range for insertion, which includes positions from 0 to `size` (inclusive). The upper bound is `size` rather than `size - 1` because insertion can occur at the end of the array, effectively appending a new element. The lower bound check ensures non-negative indices. This method encapsulates position validation logic, making it reusable across different operations that require bounds checking.

**Time Complexity**: O(1)

Performs two simple integer comparisons, both of which are constant-time operations regardless of array size.

**Valid Range**: [0, size] inclusive, allowing insertion from the beginning to one position past the last element.

## Core Operations

### `getLength() const`

**Purpose**: Returns the current number of elements stored in the array.

**Implementation Details**: Provides read-only access to the size member variable. The `const` qualifier ensures this method doesn't modify the object state, allowing it to be called on const Array objects.

**Time Complexity**: O(1)

Simple member variable access with no computation involved.

---

### `display() const`

**Purpose**: Prints the array contents to standard output in a formatted manner.

**Implementation Details**: Iterates through all elements currently stored in the array and prints them in a comma-separated format enclosed in curly braces (e.g., `{1, 2, 3}`). Special handling ensures no trailing comma after the last element, providing clean output formatting.

**Time Complexity**: O(n)

Where n is the current size of the array. The method must visit each element exactly once to print it, resulting in linear time complexity. The output operation itself may have additional overhead depending on I/O buffering, but asymptotically the complexity is linear in the number of elements.

**Output Format**: `{element1, element2, ..., elementN}`

---

### `append(int new_element)`

**Purpose**: Adds a new element to the end of the array.

**Implementation Details**: The method first checks if capacity is available using the `has_capacity()` helper. If capacity is exhausted, it throws an `out_of_range` exception to prevent buffer overflow. When space is available, the element is placed at index `size` and the size counter is incremented.

**Time Complexity**: O(1)

Appending to the end of the array is a constant-time operation because:

- Capacity checking is O(1)
- Array access by index is O(1)
- Size increment is O(1)

No elements need to be shifted or copied, making this one of the most efficient array operations.

**Exception Safety**: Throws `std::out_of_range` when attempting to append to a full array.

---

### `insert(int index, int new_element)`

**Purpose**: Inserts a new element at a specified position in the array, shifting subsequent elements to make room.

**Implementation Details**: The method first validates the insertion position using the `is_valid_position()` helper to ensure the index is within acceptable bounds. If the position is invalid, it throws an `out_of_range` exception. For valid positions, the method shifts all elements from the insertion point to the end of the array one position to the right, working backwards from the last element to avoid overwriting data. This creates an empty slot at the desired index where the new element is placed. Finally, the size counter is incremented to reflect the addition.

The backwards iteration is crucial for correctness—starting from `size` (the first empty position) and moving down to `index + 1` ensures each element is copied before being overwritten. If iteration were forward, elements would be lost as they're overwritten before being copied.

**Time Complexity**: O(n)

Where n is the current size of the array. In the worst case (inserting at index 0), all existing elements must be shifted one position to the right, requiring n move operations. Even in the best case (inserting at the end, equivalent to append), the loop condition is immediately false, making it effectively O(1). However, the average case requires shifting approximately n/2 elements, which is still O(n) asymptotically.

The shifting operation dominates the time complexity:

- Position validation: O(1)
- Shifting loop: O(n) in worst case, O(1) in best case
- Element assignment: O(1)
- Size increment: O(1)

**Exception Safety**: Throws `std::out_of_range` when attempting to insert at an invalid index (index < 0 or index > size).

**Capacity Consideration**: Unlike `append()`, this method does not check for available capacity before insertion. If the array is at full capacity, inserting will cause undefined behavior as it attempts to write beyond allocated memory. This is a current limitation that should be addressed in future implementations.

## Current Limitations

- **Fixed Capacity**: Once created, the array cannot grow beyond its initial capacity. Attempting to append beyond capacity results in an exception rather than automatic resizing.

- **Integer Only**: The current implementation only supports `int` type elements. The design is not templated for generic types.

- **Basic Display**: The display method provides simple console output but doesn't support custom formatting or output to different streams.

_Last Updated: 4th, October 2025_
