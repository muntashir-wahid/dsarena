# Singly Linked List ADT Implementation Documentation

## Overview

This document provides a comprehensive overview of a custom Singly Linked List Abstract Data Type (ADT) implemented in C++ using dynamic node allocation and pointer-based linkage. The implementation demonstrates fundamental concepts of linked data structures, dynamic memory management, and pointer manipulation techniques.

A Singly Linked List ADT is a linear data structure that stores elements in nodes connected through unidirectional pointers, with each node containing data and a reference to the next node in the sequence. Unlike array-based structures that store elements in contiguous memory locations, linked lists provide dynamic memory allocation where nodes can be scattered throughout memory and connected via pointers, enabling efficient insertion and deletion operations without the need for element shifting.

## Design Philosophy

The Singly Linked List ADT is designed with the following principles:

**Node-Based Architecture**: The list employs a separate Node class to encapsulate individual data elements and their linkage information. This separation of concerns promotes modularity, making the code more maintainable and allowing for clear distinction between data storage (Node) and list management (SingleList) responsibilities.

**Head and Tail Pointer Optimization**: The implementation maintains both head and tail pointers to optimize common operations. The head pointer enables O(1) access to the first element and efficient prepend operations, while the tail pointer allows O(1) append operations without requiring traversal to the end of the list, significantly improving performance for list growth scenarios.

**Dynamic Memory Management**: All nodes are allocated dynamically on the heap, providing unlimited growth potential limited only by available system memory. The implementation follows RAII (Resource Acquisition Is Initialization) principles, ensuring proper memory cleanup through destructor-based deallocation that prevents memory leaks.

**Flexible Construction Patterns**: The list supports both empty initialization and single-element initialization, providing users with flexibility in how they begin building their data structures. This dual-constructor approach accommodates different usage patterns while maintaining consistency in the interface.

**Size Tracking Optimization**: The implementation maintains an explicit size counter, enabling O(1) size queries and empty checks without requiring traversal operations. This approach trades minimal memory overhead for significant performance benefits in size-related operations.

## Class Structure

The Singly Linked List implementation consists of two cooperating classes:

### **Node Class Structure:**

- `int data`: The value stored in the node (private)
- `Node* next`: Pointer to the next node in the sequence (private)

### **SingleList Class Structure:**

- `Node* head`: Pointer to the first node in the list
- `Node* tail`: Pointer to the last node in the list
- `int size`: Current number of elements in the list

The Node class provides encapsulated access through getter and setter methods, maintaining data integrity while allowing the SingleList class to manipulate the node structure safely.

## Constructor & Destructor

### Constructor: `SingleList(int val)`

**Purpose**: Initializes a new Singly Linked List with a single element containing the specified value.

**Implementation Details**: The constructor creates the first node using dynamic memory allocation with the provided value and null next pointer. Both head and tail pointers are set to reference this single node, establishing the fundamental invariant that in a single-element list, head and tail point to the same node. The size is initialized to 1, reflecting the presence of the initial element.

This constructor provides immediate utility by creating a functional list with content, eliminating the need for separate creation and insertion steps in scenarios where an initial value is known.

**Time Complexity**: O(1)

The constructor performs a constant number of operations: one memory allocation, three pointer assignments, and one integer assignment, regardless of the initial value provided.

**Memory Allocation**: Allocates `sizeof(Node)` bytes on the heap for the single initial node.

**Invariant Establishment**: Ensures head == tail for single-element list, size reflects actual content, and proper null termination with tail->next == nullptr.

---

### Constructor: `SingleList()`

**Purpose**: Initializes an empty Singly Linked List with no elements, providing a clean slate for dynamic list building.

**Implementation Details**: The default constructor uses modern C++ member initializer list syntax with brace initialization to set all member variables to their empty-list values. Head and tail pointers are set to nullptr, indicating no nodes exist, and size is set to zero. This constructor establishes the empty-list invariant where both head and tail are null and size accurately reflects the absence of elements.

The empty constructor enables list creation without requiring an initial value, supporting use cases where the list will be populated entirely through subsequent append, prepend, or insert operations.

**Time Complexity**: O(1)

Initialization involves only constant-time assignment operations with no memory allocation or traversal required.

**Memory Allocation**: No dynamic memory allocation occurs during empty list construction.

**Invariant Establishment**: Sets up proper empty-list state with head == tail == nullptr and size == 0.

---

### Destructor: `~SingleList()`

**Purpose**: Safely deallocates all nodes in the list when the SingleList object goes out of scope, preventing memory leaks.

**Implementation Details**: The destructor implements a traversal-based cleanup strategy that visits each node in the list exactly once. Starting from the head, it employs a two-pointer technique: saving the current node reference before advancing to the next node, then deleting the saved node. This approach prevents the classic "deleting the node you need to traverse from" problem that would cause undefined behavior.

The algorithm continues until all nodes have been visited and deleted, ensuring complete memory cleanup regardless of list size. The traversal pattern safely handles empty lists (where head is nullptr) and single-element lists, making the destructor robust across all possible list states.

**Time Complexity**: O(n)

Where n is the number of nodes in the list. Each node must be visited exactly once for deletion, resulting in linear time complexity proportional to list size.

**Memory Management**: Systematically deallocates all heap-allocated nodes, ensuring no memory leaks occur when the list is destroyed.

**Safety**: Handles all edge cases including empty lists and single-element lists without undefined behavior.

## Public Methods

### `bool is_empty() const`

**Purpose**: Determines whether the list contains any elements, providing a convenient boolean check for empty state.

**Implementation Details**: The method performs a simple comparison of the size member variable against zero. This approach leverages the maintained size counter for O(1) performance rather than checking pointer states or performing traversal operations. The const qualifier ensures the method doesn't modify the list state, making it safe to call from const contexts and clearly communicating its read-only nature.

**Time Complexity**: O(1)

Direct integer comparison operation with no traversal or complex computation required.

**Return Value**: `true` if the list contains no elements (size == 0), `false` otherwise.

---

### `int get_size() const`

**Purpose**: Returns the current number of elements in the list, enabling size-based algorithms and boundary checking.

**Implementation Details**: The method provides direct access to the size member variable through a simple return statement. This implementation choice prioritizes performance by maintaining an accurate count during list modifications rather than computing size on-demand through traversal. The const qualifier ensures the method is read-only and can be called on const SingleList objects.

**Time Complexity**: O(1)

Simple member variable access with no computation or traversal overhead.

**Return Value**: Integer representing the exact number of elements currently stored in the list.

---

### `void append(int val)`

**Purpose**: Adds a new element to the end of the list, growing the list by one element while maintaining proper linkage.

**Implementation Details**: The method creates a new node with the specified value and null next pointer, then handles two distinct cases based on current list state. For empty lists, both head and tail pointers are set to the new node, establishing the list's first element. For non-empty lists, the current tail's next pointer is updated to reference the new node, and the tail pointer is advanced to the new node, maintaining the invariant that tail always points to the last element.

The size counter is incremented in both cases, ensuring accurate size tracking. The implementation leverages the `is_empty()` method for clear conditional logic and maintains all list invariants throughout the operation.

**Time Complexity**: O(1)

The append operation achieves constant time performance by utilizing the tail pointer, eliminating the need to traverse the entire list to find the insertion point. This is a significant optimization over naive implementations that would require O(n) traversal.

**Memory Allocation**: Allocates `sizeof(Node)` bytes for each new element added to the list.

**Invariant Maintenance**: Properly updates head, tail, and size to maintain list consistency across empty and non-empty list scenarios.

---

### `void prepend(int val)`

**Purpose**: Adds a new element to the beginning of the list, growing the list by one element while maintaining proper linkage and making the new element the first in the sequence.

**Implementation Details**: The method creates a new node with the specified value and null next pointer, then handles two distinct cases based on current list state. For empty lists, both head and tail pointers are set to the new node, establishing the list's first element identical to the append operation. For non-empty lists, the new node's next pointer is set to the current head, establishing linkage to the existing list, and the head pointer is updated to reference the new node, making it the new first element while preserving the tail pointer.

The size counter is incremented in both cases, ensuring accurate size tracking. The implementation leverages the `is_empty()` method for clear conditional logic and maintains all list invariants throughout the operation, particularly ensuring that the tail pointer remains unchanged when adding to a non-empty list.

**Time Complexity**: O(1)

The prepend operation achieves constant time performance by directly manipulating the head pointer without requiring any traversal operations. This makes prepend as efficient as append, providing optimal performance for adding elements to either end of the list.

**Memory Allocation**: Allocates `sizeof(Node)` bytes for each new element added to the list.

**Invariant Maintenance**: Properly updates head and size while maintaining tail consistency across empty and non-empty list scenarios.

---

### `int remove_first()`

**Purpose**: Removes and returns the first element from the list, reducing the list size by one while maintaining proper linkage and pointer integrity.

**Implementation Details**: The method first validates that the list is not empty by checking the size, throwing an `out_of_range` exception if removal is attempted on an empty list. For valid operations, it saves a reference to the current head node and extracts its data value before any pointer manipulations. The head pointer is then updated to point to the next node in the sequence (or nullptr if removing the only element).

A critical aspect of the implementation is handling the single-element list case: when `size == 1`, the tail pointer must be set to nullptr to maintain the empty-list invariant. After pointer updates, the size is decremented and the original head node is deleted to prevent memory leaks. The extracted data value is returned to the caller.

**Time Complexity**: O(1)

Removing from the front of a linked list is inherently constant time since it only requires updating the head pointer without any traversal operations. This makes it an optimal operation for implementing stack-like or queue-like behavior.

**Exception Safety**: Throws `std::out_of_range` when attempting to remove from an empty list, providing clear error indication.

**Memory Management**: Properly deallocates the removed node to prevent memory leaks while preserving all remaining list elements.

**Return Value**: The integer value that was stored in the removed first element.

---

### `int remove_last()`

**Purpose**: Removes and returns the last element from the list, reducing the list size by one while maintaining proper linkage throughout the remaining list structure.

**Implementation Details**: The method first validates that the list is not empty by checking the size, throwing an `out_of_range` exception if removal is attempted on an empty list. For valid operations, it extracts the data value from the tail node early to preserve it before any modifications. The implementation handles two distinct cases based on list size.

For single-element lists (`size == 1`), both head and tail pointers are set to nullptr, the size is decremented, and the method returns early with the extracted value. For multi-element lists, the method must traverse to find the second-to-last node since singly linked lists cannot traverse backwards from the tail. Using a precise loop that iterates `size - 2` times, it positions a current pointer at the node that should become the new tail.

After traversal, the original tail is deleted, the size is decremented, the tail pointer is updated to the second-to-last node, and the new tail's next pointer is set to nullptr to properly terminate the list. The extracted data value is returned to the caller.

**Time Complexity**: O(n)

Where n is the number of elements in the list. Unlike `remove_first()`, removing the last element requires traversal to find the second-to-last node, as singly linked lists cannot traverse backwards. This linear complexity is unavoidable for this operation in singly linked list implementations.

**Exception Safety**: Throws `std::out_of_range` when attempting to remove from an empty list, providing clear error indication.

**Memory Management**: Properly deallocates the removed node while maintaining linkage integrity for all remaining elements.

**Return Value**: The integer value that was stored in the removed last element.

**Optimization**: Uses early return for single-element lists to avoid unnecessary traversal when possible.

---

### `void display() const`

**Purpose**: Outputs a formatted representation of the list contents to standard output, providing visual feedback for debugging and verification.

**Implementation Details**: The method implements a comprehensive display strategy that handles both empty and populated lists with appropriate formatting. For empty lists, it outputs "{empty}" to clearly indicate the absence of elements. For populated lists, it uses a traversal-based approach to visit each node and output its data value.

The formatting uses curly braces to enclose the list contents and arrow notation (" -> ") to visually represent the linkage between consecutive elements. The algorithm employs a look-ahead technique, checking whether the current node has a next pointer to determine whether to append the arrow separator, ensuring clean output without trailing separators.

**Time Complexity**: O(n)

Where n is the number of elements in the list. Each node must be visited exactly once to output its data, resulting in linear time complexity proportional to list size.

**Output Format**: `{empty}` for empty lists, `{data1 -> data2 -> data3}` for populated lists.

**Const Correctness**: The method is marked const as it only reads list data without modification, allowing it to be called on const SingleList objects.

---

### `int get(int index) const`

**Purpose**: Retrieves the value stored at the specified index position in the list, providing zero-based indexed access to list elements without modifying the list structure.

**Implementation Details**: The method first validates that the list is not empty by checking the size, throwing an `out_of_range` exception if access is attempted on an empty list. It then performs comprehensive bounds checking to ensure the provided index falls within the valid range [0, size-1], throwing an exception for both negative indices and indices that exceed the list bounds.

For valid operations, the method employs a linear traversal strategy starting from the head node. Using a counter-controlled loop that iterates exactly `index` times, it advances a current pointer through the linked structure, following the next pointers from node to node. This traversal positions the pointer at the desired index location, after which the method extracts and returns the data value from the target node.

The implementation maintains const correctness as it performs read-only access without modifying any list state, linkage, or node contents. The traversal pattern is straightforward and reliable, visiting exactly the number of nodes necessary to reach the target position.

**Time Complexity**: O(n)

Where n is the value of the index parameter. The method must traverse from the head node through the linked structure, visiting each intermediate node until reaching the target position. In the worst case (accessing the last element at index size-1), the traversal must visit nearly all nodes in the list, resulting in linear time complexity proportional to the index value.

**Best Case Performance**: O(1) when accessing the first element (index 0), as no traversal is required beyond the initial head access.

**Worst Case Performance**: O(n) when accessing the last element, requiring traversal through the entire list structure.

**Exception Safety**: Throws `std::out_of_range` when attempting to access elements from an empty list or when the provided index falls outside the valid bounds [0, size-1], providing clear error indication for boundary violations.

**Return Value**: The integer value stored at the specified index position in the list.

**Index Convention**: Uses zero-based indexing where index 0 represents the first element (head) and index size-1 represents the last element (tail).

**Comparison to Array Access**: Unlike array structures that provide O(1) random access through pointer arithmetic, linked list indexed access requires sequential traversal, making this operation inherently slower for arbitrary position access. This performance characteristic is fundamental to the linked list data structure and represents the trade-off for efficient insertion and deletion operations.

---

### `void set(int index, int val)`

**Purpose**: Modifies the value stored at the specified index position in the list, replacing the existing element with a new value while maintaining the list structure and linkage intact.

**Implementation Details**: The method first validates that the list is not empty by checking the size, throwing an `out_of_range` exception if modification is attempted on an empty list. It then performs comprehensive bounds checking to ensure the provided index falls within the valid range [0, size-1], throwing an exception for both negative indices and indices that exceed the list bounds.

For valid operations, the method employs the same linear traversal strategy as the `get()` method, starting from the head node and using a counter-controlled loop that iterates exactly `index` times to advance through the linked structure. Once the target node is located, the method updates the node's data value using the node's setter method, leaving all pointers and structural properties unchanged.

The implementation follows a read-modify pattern without any memory allocation or deallocation. Unlike insertion or removal operations that restructure the list, `set()` performs a pure in-place modification, updating only the data content of an existing node while preserving all linkage relationships. The size remains unchanged, and no pointer updates are necessary.

**Time Complexity**: O(n)

Where n is the value of the index parameter. The method must traverse from the head node through the linked structure, visiting each intermediate node until reaching the target position. In the worst case (modifying the last element at index size-1), the traversal must visit nearly all nodes in the list, resulting in linear time complexity proportional to the index value.

**Best Case Performance**: O(1) when modifying the first element (index 0), though the implementation still performs validation checks before the minimal traversal.

**Worst Case Performance**: O(n) when modifying the last element, requiring traversal through the entire list structure.

**Exception Safety**: Throws `std::out_of_range` when attempting to modify elements in an empty list or when the provided index falls outside the valid bounds [0, size-1]. The method provides strong exception guarantee—if an exception is thrown, the list remains completely unchanged with no side effects.

**Modification Semantics**: This method strictly modifies existing elements and will never add new elements to the list. Attempting to set at `index == size` (one past the last valid index) will throw an exception, as this position does not exist. For adding elements, use the `append()`, `prepend()`, or `insert()` methods instead.

**Const Correctness**: The method is not marked const as it modifies the data content of list nodes, though it preserves the structural integrity of the list.

**Use Cases**: Ideal for updating inventory counts, correcting data entry errors, implementing swap operations in sorting algorithms, replacing placeholder values with computed results, or any scenario requiring in-place modification of list elements without structural changes. The operation is particularly useful when the list structure must remain stable but content needs updating.

**Design Consistency**: The method mirrors the interface and validation logic of `get()`, providing intuitive paired operations for read and write access at indexed positions, maintaining symmetry in the ADT interface.

## Use Cases and Applications

### **When to Use a Singly Linked List**

- **Dynamic size requirements**: When the number of elements cannot be predetermined
- **Frequent insertions/deletions**: Especially at the beginning or end of the sequence
- **Memory efficiency**: When minimizing memory overhead is important
- **Sequential access patterns**: When elements are typically accessed in order
- **Unknown maximum size**: When pre-allocating fixed capacity is impractical

### **When to Use Alternative Structures**

- **Random access requirements**: Use array-based structures for O(1) index access
- **Memory locality critical**: Arrays provide better cache performance
- **Bidirectional traversal needed**: Use doubly linked lists
- **Frequent search operations**: Consider sorted arrays or tree structures
- **Very small datasets**: Array overhead may be more efficient

## Implementation Notes

### **Node Class Integration**

The SingleList relies on a well-designed Node class with proper encapsulation:

- **Private data members**: Ensures data integrity through controlled access
- **Getter/setter methods**: Provide a safe interface for data and pointer manipulation
- **Constructor delegation**: Node class handles its own initialization patterns
- **Memory management**: Node destructor handles individual node cleanup

### **Constructor Overloading Strategy**

The dual-constructor approach serves different initialization patterns:

- **Empty constructor**: Supports incremental list building through append operations
- **Value constructor**: Enables immediate list creation with initial content
- **Consistent interface**: Both constructors establish proper invariants
- **User flexibility**: Accommodates different programming styles and use cases

### **Error Handling Philosophy**

The current implementation focuses on correctness and safety:

- **Null pointer safety**: Proper handling of empty list scenarios
- **Invariant maintenance**: Head, tail, and size always remain consistent
- **Memory leak prevention**: Comprehensive cleanup in destructor
- **Const correctness**: Read-only methods properly marked const

### **Size Tracking Benefits**

Maintaining an explicit size counter provides multiple advantages:

- **O(1) size queries**: Eliminates need for traversal-based counting
- **Efficient bounds checking**: Enables quick validation for future indexing operations
- **Algorithm optimization**: Supports size-based optimizations in complex operations
- **User convenience**: Provides immediate feedback on list size

This Singly Linked List implementation provides a solid foundation for understanding pointer-based data structures while demonstrating professional-quality C++ programming practices. The combination of performance optimization, memory safety, and clear interface design makes it suitable for both educational purposes and practical applications requiring dynamic, efficient list management.

_Last Updated: 23rd, February 2026_
