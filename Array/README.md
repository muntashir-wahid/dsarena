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

### `get_length() const`

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

### `is_sorted(bool ascending = true) const`

**Purpose**: Checks whether the array is sorted in either ascending or descending order based on the specified parameter.

**Implementation Details**: The method performs a single pass through the array, comparing each element with its successor to verify the ordering constraint. The boolean parameter `ascending` determines which ordering to check: when `true`, it verifies ascending order (each element ≤ next element), and when `false`, it verifies descending order (each element ≥ next element).

The algorithm iterates through indices 0 to `size - 2`, comparing `data[i]` with `data[i + 1]`. For ascending order, if any element is greater than its successor, the array violates the sorted property and the method immediately returns `false`. For descending order, if any element is less than its successor, the same violation occurs. The early return optimization prevents unnecessary comparisons once a violation is detected.

If the loop completes without finding any violations, the array satisfies the ordering constraint and the method returns `true`. Arrays with zero or one element are trivially considered sorted, as the loop body never executes.

The method uses the `const` qualifier since it only reads array elements without modification, allowing it to be called on const Array objects and clearly communicating its read-only nature.

**Time Complexity**: O(n)

Where n is the current size of the array. In the worst case (when the array is perfectly sorted), the method must compare all n-1 adjacent pairs, visiting every element exactly once. The best case occurs when the first pair violates the ordering, resulting in O(1) with immediate return. On average, for randomly ordered arrays, a violation is typically found early, but the worst-case linear complexity must be considered for algorithm analysis.

Operation breakdown:

- Loop iteration: O(n) in worst case
- Each comparison: O(1)
- Early return: O(1) when triggered

**Return Value**: `true` if the array is sorted according to the specified order, `false` otherwise.

**Parameters**:

- `ascending` (bool): Determines the sort order to check. `true` checks for ascending order (default), `false` checks for descending order.

**Edge Cases**:

- Empty arrays (size = 0): Returns `true` (trivially sorted)
- Single-element arrays (size = 1): Returns `true` (trivially sorted)
- Arrays with duplicate values: Considered sorted if all duplicates maintain the order (non-strict ordering)

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

---

### `left_shift()`

**Purpose**: Shifts all elements in the array one position to the left, with the rightmost position filled with zero.

**Implementation Details**: The method performs a linear shift operation where each element moves to the position of its predecessor. Starting from index 0, each element is replaced by the element at the next position (index + 1). The iteration continues through `size - 1` elements, effectively moving every element except the last one position to the left. After the shifting is complete, the rightmost position (index `size - 1`) is explicitly set to zero, maintaining the array's size while introducing a zero value at the end.

This operation is destructive—the leftmost element is permanently lost and cannot be recovered. Unlike rotation operations, left shift does not preserve all original values, making it useful for scenarios where elements need to be discarded from the beginning of the array while maintaining a fixed size.

**Time Complexity**: O(n)

Where n is the current size of the array. The method must visit and modify each element exactly once during the shifting process, except for the last element which receives a zero value. The loop performs n-1 assignments for the shifting operation, plus one additional assignment to set the final position to zero, resulting in linear time complexity proportional to the array size.

Operation breakdown:

- Shifting loop: O(n-1) which simplifies to O(n)
- Each assignment: O(1)
- Final zero assignment: O(1)

**Space Complexity**: O(1)

The algorithm uses only a constant amount of extra space (the loop variable `i`) regardless of array size, making it an in-place operation. No temporary storage or auxiliary data structures are required.

**Modification**: This method modifies the original array and permanently loses the leftmost element. The array size remains unchanged, but the content is altered.

**Use Cases**: Useful for implementing queue-like behavior where elements are processed from the left, or for sliding window operations where the oldest data needs to be discarded.

---

### `left_rotate()`

**Purpose**: Rotates all elements in the array one position to the left, with the leftmost element moving to the rightmost position.

**Implementation Details**: The method performs a cyclic rotation where no elements are lost—each element moves to the position of its predecessor, and the first element wraps around to become the last element. The algorithm begins with an early return optimization for arrays with zero or one element, as rotation has no effect on such arrays.

For arrays with multiple elements, the method first saves the leftmost element (at index 0) in a temporary variable to prevent it from being overwritten during the shifting process. Then, it performs a left shift operation similar to `left_shift()`, moving each element from position i+1 to position i, starting from index 0 and continuing through `size - 2`. Finally, the saved first element is placed at the last position (index `size - 1`), completing the rotation.

Unlike `left_shift()` which discards the leftmost element, `left_rotate()` preserves all elements by moving the first element to the end. This maintains the same set of values while changing their relative positions, making it a true rotation operation.

**Time Complexity**: O(n)

Where n is the current size of the array. The method must visit and modify each element exactly once during the rotation process. The algorithm performs one element save operation, n-1 shift assignments, and one final placement, all of which contribute to linear time complexity proportional to the array size.

Operation breakdown:

- Size check: O(1)
- First element save: O(1)
- Shifting loop: O(n-1) which simplifies to O(n)
- Each assignment: O(1)
- Final placement: O(1)

**Space Complexity**: O(1)

The algorithm uses only a constant amount of extra space (two integer variables: the loop variable and the temporary storage for the first element) regardless of array size, making it an in-place operation. No auxiliary data structures are allocated.

**Modification**: This method modifies the original array but preserves all elements. The array size remains unchanged, and no data is lost—only the positions of elements change.

**Use Cases**: Useful for implementing circular buffer operations, rotating through a sequence of values, or shifting data in cyclic patterns where all elements must be preserved.

---

### `right_shift()`

**Purpose**: Shifts all elements in the array one position to the right, with the leftmost position filled with zero.

**Implementation Details**: The method performs a linear shift operation where each element moves to the position of its successor. The algorithm begins with an early return optimization for empty arrays, as shifting has no effect when size is zero. Starting from the rightmost element (index `size - 1`) and working backwards to index 1, each element is replaced by the element at the previous position (index - 1). The iteration continues through all elements except the first, effectively moving every element except the leftmost one position to the right. After the shifting is complete, the leftmost position (index 0) is explicitly set to zero, maintaining the array's size while introducing a zero value at the beginning.

This operation is destructive—the rightmost element is permanently lost and cannot be recovered. Unlike rotation operations, right shift does not preserve all original values, making it useful for scenarios where elements need to be discarded from the end of the array while maintaining a fixed size. The backwards iteration is crucial to prevent data corruption, as moving elements forward from left to right would overwrite values before they could be copied.

**Time Complexity**: O(n)

Where n is the current size of the array. The method must visit and modify each element exactly once during the shifting process, except for the first element which receives a zero value. The loop performs n-1 assignments for the shifting operation, plus one additional assignment to set the initial position to zero, resulting in linear time complexity proportional to the array size.

Operation breakdown:

- Size check: O(1)
- Shifting loop: O(n-1) which simplifies to O(n)
- Each assignment: O(1)
- Final zero assignment: O(1)

**Space Complexity**: O(1)

The algorithm uses only a constant amount of extra space (the loop variable `i`) regardless of array size, making it an in-place operation. No temporary storage or auxiliary data structures are required.

**Modification**: This method modifies the original array and permanently loses the rightmost element. The array size remains unchanged, but the content is altered.

**Use Cases**: Useful for implementing stack-like behavior where elements are processed from the right, prepending operations where new data will be inserted at the beginning, or for sliding window operations where the newest data needs to be discarded.

---

### `right_rotate()`

**Purpose**: Rotates all elements in the array one position to the right, with the rightmost element moving to the leftmost position.

**Implementation Details**: The method performs a cyclic rotation where no elements are lost—each element moves to the position of its successor, and the last element wraps around to become the first element. The algorithm begins with an early return optimization for arrays with zero or one element, as rotation has no effect on such arrays.

For arrays with multiple elements, the method first calculates the last index using a constant `LAST_INDEX = size - 1` for clarity and saves the rightmost element (at this last index) in a temporary variable to prevent it from being overwritten during the shifting process. Then, it performs a right shift operation similar to `right_shift()`, moving each element from position i-1 to position i, starting from the last index and working backwards to index 1. Finally, the saved last element is placed at the first position (index 0), completing the rotation.

Unlike `right_shift()` which discards the rightmost element, `right_rotate()` preserves all elements by moving the last element to the beginning. This maintains the same set of values while changing their relative positions, making it a true rotation operation. The use of a named constant for the last index improves code readability and makes the algorithm's intent clearer.

**Time Complexity**: O(n)

Where n is the current size of the array. The method must visit and modify each element exactly once during the rotation process. The algorithm performs one element save operation, n-1 shift assignments, and one final placement, all of which contribute to linear time complexity proportional to the array size.

Operation breakdown:

- Size check: O(1)
- Last index calculation: O(1)
- Last element save: O(1)
- Shifting loop: O(n-1) which simplifies to O(n)
- Each assignment: O(1)
- Final placement: O(1)

**Space Complexity**: O(1)

The algorithm uses only a constant amount of extra space (three integer variables: the loop variable, the last index constant, and the temporary storage for the last element) regardless of array size, making it an in-place operation. No auxiliary data structures are allocated.

**Modification**: This method modifies the original array but preserves all elements. The array size remains unchanged, and no data is lost—only the positions of elements change.

**Use Cases**: Useful for implementing circular buffer operations in reverse direction, rotating through a sequence of values backwards, or shifting data in cyclic patterns where all elements must be preserved and the rotation direction matters for the application logic.

---

### `merge(const Array &new_array)`

**Purpose**: Merges two sorted arrays into a single sorted array, combining elements from both arrays while maintaining ascending order.

**Implementation Details**: The method implements a classic merge operation that combines two pre-sorted arrays into a single sorted result. The algorithm begins by validating that both the current array (`this`) and the parameter array (`new_array`) are sorted in ascending order using the `is_sorted()` method. If either array is not sorted, it throws a `runtime_error` to ensure the merge operation's correctness, as the algorithm relies on the sorted property for efficiency.

The method calculates the required capacity by summing the sizes of both arrays and determines the final capacity as the maximum between this required capacity and the current array's capacity. This ensures sufficient space for all elements while potentially preserving existing capacity for future operations. A new temporary array (`merged_data`) is allocated with this calculated capacity.

The core merging logic uses a three-pointer technique with variables `i`, `j`, and `k` representing indices for the current array, the new array, and the merged result respectively. The algorithm compares elements from both arrays and places the smaller element into the merged array, advancing the corresponding source pointer and the result pointer. This continues until one array is exhausted.

After the main comparison loop, two cleanup loops handle any remaining elements from either array, ensuring all elements are included in the final result. Finally, the method updates the current array's properties: it deallocates the old data array, updates the capacity and size, and assigns the new merged data pointer. This effectively transforms the current array into the merged result while properly managing memory.

**Time Complexity**: O(m + n)

Where m is the size of the current array and n is the size of the parameter array. The algorithm performs exactly one comparison per element placement and visits each element from both arrays exactly once. The three distinct phases each contribute linear time:

- Sorting validation: O(m) + O(n) for checking both arrays
- Main merge loop: O(min(m, n)) comparisons
- Cleanup loops: O(max(m, n) - min(m, n)) for remaining elements
- Total element processing: O(m + n)

The memory allocation and deallocation operations are considered constant time in the context of the algorithm's overall complexity.

**Space Complexity**: O(m + n)

The algorithm requires additional space proportional to the combined size of both arrays for the temporary merged array. This is not an in-place operation, as it needs to maintain the original arrays during the merge process before replacing the current array's data.

**Exception Safety**: Throws `std::runtime_error` when either array is not sorted in ascending order. The method provides strong exception safety—if an exception is thrown during validation, the original array remains unchanged.

**Modification**: This method modifies the current array by replacing its contents with the merged result. The original data is lost, and the array's capacity may increase if needed to accommodate the combined elements.

**Memory Management**: The method handles dynamic memory allocation and deallocation carefully. It allocates new memory for the merged result, copies all elements, then properly deallocates the original array memory before updating the pointer, preventing memory leaks.

**Parameters**:

- `new_array` (const Array&): The second sorted array to merge with the current array. Passed by const reference for efficiency and to prevent modification of the source array.

**Preconditions**: Both arrays must be sorted in ascending order. This is enforced at runtime with exception throwing.

**Use Cases**: Essential for merge sort implementations, combining sorted datasets, merging sorted streams of data, or any scenario where two ordered collections need to be combined while preserving order. Particularly useful in divide-and-conquer algorithms and external sorting operations.

---

### `swap(int index_one, int index_two)`

**Purpose**: Exchanges the values of two elements at specified indices in the array, providing a fundamental building block for sorting algorithms and array manipulation operations.

**Implementation Details**: The method performs a safe element exchange operation using the classic three-step swap technique with a temporary variable. Before any swapping occurs, both indices are validated using the `is_valid_index()` helper method to ensure they correspond to existing elements in the array. If either index is invalid, the method throws an `out_of_range` exception to prevent undefined behavior.

The swapping process follows the standard approach: first, the value at `index_one` is stored in a temporary variable to preserve it during the exchange. Then, the value from `index_two` is copied to `index_one`, effectively overwriting the original value (which is safely stored in the temporary variable). Finally, the temporary variable's value (original value from `index_one`) is assigned to `index_two`, completing the exchange.

This implementation prioritizes safety and clarity over performance micro-optimizations like XOR swapping, making it reliable for all integer values including edge cases like identical indices or special values. The method maintains all array invariants and leaves the array in a consistent state regardless of the input indices.

**Time Complexity**: O(1)

The swap operation performs a constant number of operations regardless of array size or the specific indices being swapped. The complexity breakdown includes:

- Index validation: O(1) for each index check
- Temporary variable assignment: O(1)
- Two element assignments: O(1) each
- Total operations: Fixed number independent of array size

**Space Complexity**: O(1)

The algorithm uses only a single temporary integer variable for the swap operation, requiring constant additional space regardless of array size.

**Exception Safety**: Throws `std::out_of_range` when either `index_one` or `index_two` is invalid (less than 0 or greater than or equal to size). The method provides strong exception safety—if an exception is thrown, the array remains unchanged.

**Parameters**:

- `index_one` (int): The index of the first element to swap
- `index_two` (int): The index of the second element to swap

**Edge Cases**:

- **Identical indices**: When `index_one == index_two`, the method safely performs a no-op swap
- **Boundary indices**: Works correctly for indices at array boundaries (0 and size-1)
- **Single-element arrays**: Functions properly even with arrays containing only one element

**Use Cases**: Essential for sorting algorithm implementations, array randomization, element repositioning, and general array manipulation tasks where safe element exchange is required.

---

### `selection_sort()`

**Purpose**: Sorts the array elements in ascending order using the selection sort algorithm, providing an in-place sorting solution with predictable O(n²) performance characteristics.

**Implementation Details**: The method implements the classic selection sort algorithm through a two-phase approach for each position in the array. The outer loop iterates through each position from 0 to `size - 2`, treating each position as the target for placing the next smallest element. For each position, the inner loop scans the remaining unsorted portion of the array to find the minimum element.

The algorithm maintains a `min_index` variable initialized to the current outer loop position, representing the current candidate for the smallest element in the unsorted portion. The inner loop compares each subsequent element with the element at `min_index`, updating `min_index` whenever a smaller element is discovered. This linear scan ensures that `min_index` points to the actual minimum element in the unsorted region after the inner loop completes.

Once the minimum element is identified, the algorithm uses the `swap()` method to exchange the minimum element with the element at the current target position. This placement ensures that the current position contains the correct element in the final sorted order. The process continues until all positions have been filled with their correct elements, resulting in a fully sorted array.

The algorithm leverages the existing `swap()` method for element exchange, promoting code reuse and maintaining consistency with the class's error handling patterns. The selection sort is stable in terms of implementation correctness and provides predictable performance regardless of input data distribution.

**Time Complexity**: O(n²)

Where n is the current size of the array. The algorithm exhibits quadratic time complexity due to its nested loop structure:

- **Outer loop**: Executes n-1 iterations (positions to fill)
- **Inner loop**: For iteration i, performs n-i-1 comparisons
- **Total comparisons**: Σ(n-i-1) for i from 0 to n-2 = n(n-1)/2 ≈ O(n²)
- **Swap operations**: Exactly n-1 swaps (one per outer loop iteration)

The algorithm's performance is **not input-dependent**—it performs the same number of comparisons whether the array is already sorted, reverse sorted, or randomly ordered. This predictability can be advantageous in real-time systems where consistent performance is more important than optimal average-case behavior.

**Space Complexity**: O(1)

Selection sort is an in-place sorting algorithm that requires only a constant amount of additional memory:

- Loop variables (`i`, `j`): O(1)
- Minimum index tracker (`min_index`): O(1)
- Temporary variables in `swap()`: O(1)

No auxiliary arrays or recursive call stacks are required, making it suitable for memory-constrained environments.

**Algorithm Properties**:

- **Stability**: Not stable—equal elements may change relative order during swapping
- **Adaptive**: Not adaptive—performance doesn't improve for partially sorted inputs
- **Online**: Not online—requires access to the entire dataset
- **In-place**: Yes—sorts without additional memory proportional to input size

**Modification**: This method modifies the original array by rearranging elements in ascending order. The array size remains unchanged, but element positions are altered to achieve sorted order.

**Performance Characteristics**:

- **Best case**: O(n²)—same performance even for already sorted arrays
- **Average case**: O(n²)—consistent performance across all input distributions
- **Worst case**: O(n²)—no degradation for reverse-sorted inputs
- **Number of swaps**: Always n-1, making it optimal for scenarios where write operations are expensive

**Use Cases**: Ideal for small arrays where simplicity is preferred over performance, educational purposes for teaching sorting concepts, situations where minimal memory usage is critical, or when the number of write operations must be minimized (since it performs the minimum possible number of swaps).

---

## Current Limitations

- **Fixed Capacity**: Once created, the array cannot grow beyond its initial capacity. Attempting to append beyond capacity results in an exception rather than automatic resizing.

- **Integer Only**: The current implementation only supports `int` type elements. The design is not templated for generic types.

- **Basic Display**: The display method provides simple console output but doesn't support custom formatting or output to different streams.

_Last Updated: 30th, November 2025_
