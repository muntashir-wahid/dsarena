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

---

### Private Method: `is_valid_index(int index) const`

**Purpose**: Validates whether a given index corresponds to an existing element in the array.

**Implementation Details**: Returns `true` if the index is within the valid range for accessing existing elements, which includes positions from 0 to `size - 1` (inclusive). Unlike `is_valid_position()` which allows index equal to `size` for insertion purposes, this method enforces stricter bounds since you cannot access, modify, or remove an element that doesn't exist. The distinction between position validation and index validation is crucial for maintaining data integrity across different operations.

**Time Complexity**: O(1)

Performs two simple integer comparisons, both constant-time operations independent of array size.

**Valid Range**: [0, size - 1] inclusive, covering only indices of existing elements.

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

---

### `remove(int index)`

**Purpose**: Removes and returns the element at a specified index, shifting subsequent elements to fill the gap.

**Implementation Details**: The method first validates that the index corresponds to an existing element using `is_valid_index()`. If invalid, it throws an `out_of_range` exception. For valid indices, the method saves the element to be removed for return purposes, then shifts all elements after the removal point one position to the left. This is accomplished by iterating forward from the removal index to the second-to-last element, copying each element from the right. The size is decremented to reflect the removal, and the original element value is returned.

The forward iteration differs from `insert()`'s backward approach because we're moving elements left rather than right. Starting from the removal index and moving forward ensures each position receives the correct successor value without data loss.

**Time Complexity**: O(n)

Where n is the current size of the array. In the worst case (removing at index 0), all subsequent elements must be shifted one position to the left, requiring approximately n-1 move operations. The best case (removing the last element at index size-1) requires no shifting, making it O(1). On average, removing from the middle requires shifting n/2 elements, which is still O(n) asymptotically.

Operation breakdown:

- Index validation: O(1)
- Element retrieval: O(1)
- Shifting loop: O(n) in worst case, O(1) in best case
- Size decrement: O(1)

**Return Value**: The element that was removed from the array.

**Exception Safety**: Throws `std::out_of_range` when attempting to remove from an invalid index (index < 0 or index >= size).

---

### `first_index_of(int key) const`

**Purpose**: Searches for the first occurrence of a specified value in the array and returns its index.

**Implementation Details**: The method performs a linear search from the beginning of the array, comparing each element with the target key. Upon finding the first match, it immediately returns the index using a `break` statement to avoid unnecessary iterations. If the key is not found after checking all elements, the method returns `NOT_FOUND` (a constant likely defined as -1 in the header file) to indicate the absence of the element.

This is a straightforward sequential search implementation that prioritizes simplicity and clarity. The early termination via `break` is an important optimization that prevents checking remaining elements once a match is found.

**Time Complexity**: O(n)

Where n is the current size of the array. The worst case occurs when the element doesn't exist or is at the last position, requiring a complete traversal of all n elements. The best case (element at index 0) is O(1). On average, for a uniformly distributed dataset where the element exists, we'd expect to find it after checking n/2 elements, which is still O(n) asymptotically.

This linear time complexity is inherent to unsorted array searching—without ordering information, every element might need to be examined.

**Return Value**: Index of the first occurrence of the key, or `NOT_FOUND` if the key doesn't exist in the array.

---

### `at(int index) const`

**Purpose**: Retrieves the element at a specified index with bounds checking.

**Implementation Details**: This is a safe accessor method that validates the index using `is_valid_index()` before returning the element. If the index is out of bounds, it throws an `out_of_range` exception rather than causing undefined behavior. The `const` qualifier indicates this method doesn't modify the array state, making it callable on const Array objects and signaling its read-only nature to other developers.

This method provides safer alternative to direct array access (which would be operator[]) by enforcing bounds checking at runtime.

**Time Complexity**: O(1)

Array element access by index is a constant-time operation. The memory address is computed as `base_address + (index * element_size)`, which involves only arithmetic operations. The bounds check adds two comparisons but doesn't change the asymptotic complexity.

**Return Value**: The element stored at the specified index.

**Exception Safety**: Throws `std::out_of_range` when attempting to access an invalid index (index < 0 or index >= size).

---

### `set(int index, int new_element)`

**Purpose**: Updates the element at a specified index to a new value with bounds checking.

**Implementation Details**: This is a safe mutator method that validates the index using `is_valid_index()` before modifying the element. If the index is out of bounds, it throws an `out_of_range` exception to prevent undefined behavior. Unlike `insert()` which adds a new element, this method replaces an existing element, maintaining the array's size.

The method enforces data integrity by ensuring only valid positions can be modified, preventing accidental memory corruption or accessing uninitialized memory regions.

**Time Complexity**: O(1)

Direct array element assignment by index is a constant-time operation. The memory address calculation and assignment both take fixed time regardless of array size. The bounds check adds negligible constant overhead.

**Exception Safety**: Throws `std::out_of_range` when attempting to modify an invalid index (index < 0 or index >= size).

---

### `reverse()`

**Purpose**: Reverses the order of all elements in the array in-place, transforming the array so that the first element becomes the last and vice versa.

**Implementation Details**: The method uses a two-pointer technique to efficiently reverse the array without requiring additional storage. It begins with an early return optimization for arrays with zero or one element, as these are trivially already "reversed."

For arrays with multiple elements, two pointers are initialized: `left` starting at index 0 and `right` starting at index `size - 1`. The algorithm then proceeds to swap elements at these pointer positions using a temporary variable to avoid data loss during the exchange. After each swap, the `left` pointer moves forward and the `right` pointer moves backward, progressively working toward the center of the array.

The loop continues while `left < right`, ensuring that each pair of elements is swapped exactly once. When the pointers meet or cross in the middle, all elements have been properly repositioned and the array is fully reversed. This approach modifies the array in-place, requiring no additional data structure allocation.

The three-step swap using a temporary variable is the classic approach:

1. Save the left element in a temporary variable
2. Copy the right element to the left position
3. Copy the temporary (original left) to the right position

**Time Complexity**: O(n)

Where n is the current size of the array. The method performs exactly n/2 swaps (rounded down) regardless of the array's contents, visiting each element once during the reversal process. While only half the elements are explicitly swapped, each element must be accessed and moved, resulting in linear time complexity proportional to the array size.

Operation breakdown:

- Size check: O(1)
- Pointer initialization: O(1)
- Swap loop: O(n/2) which simplifies to O(n)
- Each swap operation: O(1)

**Space Complexity**: O(1)

The algorithm uses only a constant amount of extra space (three integer variables: `left`, `right`, and `temp`) regardless of array size, making it an in-place algorithm. No auxiliary data structures are allocated.

**Modification**: This method modifies the original array. If the original order needs to be preserved, a copy should be made before calling `reverse()`.

## Current Limitations

- **Fixed Capacity**: Once created, the array cannot grow beyond its initial capacity. Attempting to append beyond capacity results in an exception rather than automatic resizing.

- **Integer Only**: The current implementation only supports `int` type elements. The design is not templated for generic types.

- **Basic Display**: The display method provides simple console output but doesn't support custom formatting or output to different streams.

_Last Updated: 8th, October 2025_
