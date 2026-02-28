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

---

### `int find(int val) const`

**Purpose**: Searches the list for the first occurrence of a specified value and returns its zero-based index position, providing a mechanism to locate elements based on their content rather than position.

**Implementation Details**: The method first validates that the list is not empty by checking with the `is_empty()` helper function, immediately returning -1 if the list contains no elements. This early-exit strategy avoids unnecessary initialization and traversal operations when the search space is empty, providing a graceful response rather than throwing an exception.

For non-empty lists, the method employs a sequential search strategy that examines each node in order from head to tail. It initializes a current pointer to the head of the list and an index counter starting at zero. The algorithm then enters a traversal loop that continues until either the target value is found or all nodes have been examined.

During each iteration, the method compares the current node's data value with the search target using the node's getter method. If a match is found, the method immediately returns the current index, implementing an early-exit optimization that avoids unnecessary examination of remaining nodes. If no match is found, the algorithm advances both the current pointer to the next node and increments the index counter, maintaining synchronization between position tracking and traversal progress.

If the traversal completes without finding a match—indicated by the current pointer becoming nullptr after examining the final node—the method returns -1 to signal that the target value does not exist in the list. This sentinel value convention is widely recognized in programming as indicating "not found" and allows the caller to distinguish between finding an element at index 0 (a valid position) and not finding the element at all.

The implementation leverages the `is_empty()` method for consistent empty-list handling and uses `this->` prefix notation to maintain stylistic consistency with all other methods in the class. The const qualifier ensures the method performs read-only operations without modifying any list state, node contents, or linkage relationships.

**Time Complexity**: O(n)

Where n is the number of elements in the list. The method implements a linear search algorithm that may need to examine each node sequentially until the target is found or all nodes have been checked. In the worst case (when the element doesn't exist or is located at the end of the list), the algorithm must traverse the entire list structure, visiting every node exactly once, resulting in linear time complexity proportional to list size.

**Best Case Performance**: O(1) when the target value is located in the first node (head position), allowing immediate return after a single comparison without any traversal. This represents the optimal scenario for the search operation.

**Average Case Performance**: O(n/2) when the target value is randomly distributed throughout the list, requiring examination of approximately half the nodes on average. This simplifies to O(n) in asymptotic analysis.

**Worst Case Performance**: O(n) when the target value is located at the tail position or doesn't exist in the list, requiring complete traversal through all n nodes before returning a result.

**Search Strategy**: Implements linear search (also known as sequential search), which is the only viable search strategy for unsorted, linked-based structures. Unlike array-based structures that can leverage binary search on sorted data, singly linked lists lack the O(1) random access capability required for divide-and-conquer search algorithms, making linear search the optimal choice for this data structure.

**Return Value Semantics**: Returns a non-negative integer representing the zero-based index (0 to size-1) of the first occurrence of the target value if found. Returns -1 as a sentinel value if the target value does not exist in the list or if the list is empty. The -1 return value is a widely-adopted convention in programming for indicating "not found" status, allowing callers to easily check for search failure using simple comparison operations.

**First Occurrence Behavior**: When multiple nodes contain the same value, the method returns the index of the first (leftmost) occurrence encountered during head-to-tail traversal. This behavior provides predictable and consistent results, though callers requiring all occurrences or the last occurrence would need to implement alternative search strategies or continue searching beyond the first match.

**Const Correctness**: The method is properly marked const as it performs pure read-only operations, examining node values without modifying any data, pointers, or structural properties of the list. This allows the method to be safely called on const SingleList objects and clearly documents its non-mutating nature in the interface.

**Empty List Handling**: Rather than throwing an exception when called on an empty list, the method gracefully returns -1, treating the empty list as simply a case where no elements can match the target. This design choice prioritizes convenience and reduces exception handling burden on callers, as searching an empty list is a valid operation that should produce a clear "not found" result rather than requiring try-catch blocks.

**Use Cases**: Essential for implementing search functionality in applications such as finding student records by ID number, locating products in inventory systems by SKU, checking membership in unordered collections, validating the presence of elements before performing operations, implementing "contains" predicates by checking if return value is not -1, finding indices for subsequent removal or modification operations, and verifying data integrity by locating expected values. The method is particularly valuable when working with lists where element positions are not known in advance but content values are available for searching.

**Comparison to Alternative Approaches**: For sorted lists, this linear search could be replaced with more sophisticated algorithms, though the lack of random access in linked lists limits optimization potential. For frequent search operations on large lists, alternative data structures like hash tables or binary search trees would provide superior O(1) or O(log n) search performance respectively. However, for small lists or infrequent searches, the simplicity and low overhead of linear search make it entirely appropriate.

**Design Consistency**: The method follows established patterns from the codebase including comprehensive empty-list checks, consistent use of `this->` prefix notation, const correctness for read-only operations, and clear return value semantics. The traversal pattern mirrors other linear operations like `display()`, and the validation approach aligns with other query methods in the interface.

---

### `void insert(int index, int val)`

**Purpose**: Inserts a new element with the specified value at the designated index position, shifting all subsequent elements one position to the right and increasing the list size by one. This operation enables flexible list construction by allowing insertion at any valid position within the list structure.

**Implementation Details**: The method first performs comprehensive bounds checking to ensure the provided index falls within the valid insertion range [0, size], inclusive. Unlike indexed access methods that restrict to [0, size-1], the insert operation allows insertion at position size, which effectively appends to the end of the list. If the index is out of bounds (negative or greater than size), the method throws an `out_of_range` exception to signal invalid operation.

The implementation employs a strategic delegation pattern to handle edge cases efficiently. For insertion at index 0 (beginning of list), the method delegates directly to the existing `prepend()` method, leveraging its optimized O(1) implementation and ensuring consistent behavior for head insertion across all scenarios, including empty lists. Similarly, for insertion at index equal to size (end of list), the method delegates to `append()`, which handles tail insertion efficiently and correctly manages both empty and non-empty list cases. These delegations follow the DRY (Don't Repeat Yourself) principle, avoiding code duplication and centralize edge case handling in specialized methods.

For middle insertions (0 < index < size), the method performs the insertion operation directly. It creates a new node with the specified value and null next pointer, then traverses the list to locate the predecessor node—the node immediately before the insertion position. Using a precise counter-controlled loop that iterates exactly index-1 times, it positions a current pointer at this predecessor node. The insertion is completed through a two-step pointer manipulation: first, the new node's next pointer is set to reference the predecessor's current successor (the node that will follow the new node), then the predecessor's next pointer is updated to reference the new node, effectively splicing the new node into the list structure. Finally, the size counter is incremented to reflect the additional element.

This implementation strategy optimizes memory allocation by only creating new nodes when actually needed—the edge case delegations to `prepend()` and `append()` handle their own allocations, so the middle insertion path allocates only when it will be used. The method maintains all list invariants throughout the operation, ensuring head, tail, and size remain consistent, and all pointer linkages remain valid.

**Time Complexity**: O(n)

Where n is the value of the index parameter. The method must traverse from the head node through the linked structure to reach the insertion point, visiting each intermediate node until positioning at the predecessor location. The traversal cost dominates the operation's time complexity, as pointer manipulation and node creation are constant-time operations.

**Best Case Performance**: O(1) when inserting at index 0, as the operation delegates to `prepend()` which performs head insertion without any traversal. This represents optimal performance for beginning-of-list insertion.

**Worst Case Performance**: O(n) when inserting at index == size, as the operation delegates to `append()` which directly manipulates the tail pointer. While no traversal occurs due to tail pointer optimization, the worst case for a general insertion-at-index operation would be at position size-1, requiring traversal through nearly the entire list to find the predecessor.

**Average Case Performance**: O(n/2) for random insertion positions, requiring traversal through approximately half the list on average. This simplifies to O(n) in asymptotic analysis.

**Exception Safety**: Throws `std::out_of_range` when the provided index falls outside the valid insertion range [0, size]. The exception is thrown before any memory allocation or pointer manipulation occurs, providing strong exception guarantee—if insertion fails, the list remains completely unchanged with no side effects or resource leaks.

**Valid Index Range**: The method accepts indices from 0 to size (inclusive), which is one position beyond the last element's index. This extended range is intentional and standard for insertion operations: index 0 inserts before the first element, index size inserts after the last element, and indices in between insert at their respective positions while shifting subsequent elements rightward. This range differs from `get()` and `set()` which restrict to [0, size-1] as they operate on existing elements only.

**Memory Allocation**: Allocates `sizeof(Node)` bytes for each insertion through dynamic memory allocation on the heap, growing list capacity as needed without predefined limits. The allocation occurs either within the delegated methods (`prepend()` or `append()`) or in the middle insertion path, but only once per insertion operation.

**Pointer Manipulation Safety**: The two-step pointer rewiring process (new node points to successor, then predecessor points to new node) is critical for maintaining list integrity. This order ensures the existing list structure remains intact until the final pointer update, preventing loss of references to subsequent nodes. Reversing this order would break the chain and lose access to all nodes after the insertion point.

**Relationship to Other Methods**: The insert operation provides a generalized interface that encompasses both `prepend()` and `append()` functionality as special cases, while also enabling intermediate insertions that those methods cannot perform. Specifically: `insert(0, val)` is semantically equivalent to `prepend(val)`, `insert(size, val)` is semantically equivalent to `append(val)`, and `insert(k, val)` for 0 < k < size provides unique functionality for middle insertion.

**Comparison to set()**: While both methods accept an index and value, their semantics differ fundamentally. The `set()` method replaces an existing element without changing list size or structure (modification operation), whereas `insert()` adds a new element, increases size, and shifts subsequent elements (structural operation). This distinction is critical: attempting to insert at a position to "replace" an element would result in two elements at that logical position rather than one modified element.

**Use Cases**: Essential for maintaining sorted lists by inserting elements at computed positions, implementing priority queue operations where elements are inserted based on priority values, building lists with specific ordering requirements, inserting elements at user-specified positions in applications like playlist managers or task schedulers, implementing insertion sort algorithms, constructing lists incrementally where insertion position is determined dynamically, and scenarios requiring fine-grained control over element positioning beyond simple append/prepend operations. The method is particularly valuable when list elements must maintain specific ordering or when inserting into the middle of existing sequences.

**Performance Considerations**: For frequent insertions at arbitrary positions, singly linked lists provide superior performance compared to array-based structures. While both have O(n) time complexity for average-case insertion, linked lists avoid the costly element shifting operations that arrays must perform, instead requiring only pointer updates. However, if insertions are predominantly at index 0 or the end, consider using `prepend()` or `append()` directly for clearer intent and guaranteed optimal performance without the overhead of conditional checks.

**Design Consistency**: The method follows established patterns including comprehensive bounds checking with exception throwing for invalid indices, delegation to specialized methods for edge cases (DRY principle), consistent use of `this->` prefix notation, proper size tracking across all code paths (including delegated methods), and clear separation between validation, traversal, and modification phases. The implementation demonstrates advanced design through method reuse rather than duplicating prepend/append logic, making the codebase more maintainable and reducing potential for bugs.

---

### `int remove_at(int index)`

**Purpose**: Removes and returns the element at the specified index position, shifting all subsequent elements one position to the left and decreasing the list size by one. This operation enables flexible list manipulation by allowing removal at any valid position within the list structure while preserving the removed element's value for the caller.

**Implementation Details**: The method first performs comprehensive bounds checking to ensure the provided index falls within the valid removal range [0, size-1], which represents all existing element positions. Unlike the `insert()` method that accepts [0, size] to allow end insertion, removal operations can only target existing elements, making size itself an invalid index. If the index is out of bounds (negative or greater than or equal to size), the method throws an `out_of_range` exception to signal invalid operation, ensuring no attempt is made to remove non-existent elements.

The implementation employs the same strategic delegation pattern as `insert()` to handle edge cases efficiently and maintain code consistency. For removal at index 0 (first element), the method delegates directly to the existing `remove_first()` method, leveraging its optimized O(1) implementation and ensuring consistent behavior for head removal across all scenarios. This delegation also ensures proper tail pointer management when removing the only element in the list. Similarly, for removal at index equal to size-1 (last element), the method delegates to `remove_last()`, which handles tail removal and correctly manages the necessary traversal to find the predecessor node that becomes the new tail.

These delegations follow the DRY (Don't Repeat Yourself) principle, avoiding code duplication and centralizing edge case handling in specialized methods. Both delegated methods return the removed value, which `remove_at()` propagates directly to its caller, maintaining consistent interface semantics across all removal operations.

For middle removals (0 < index < size-1), the method performs the deletion operation directly. It traverses the list to locate the predecessor node—the node immediately before the target position—using a precise counter-controlled loop that iterates exactly index-1 times. This positions a current pointer at the node whose next pointer references the element to be removed.

The removal process employs a careful sequence to prevent memory leaks and maintain list integrity. First, it saves a reference to the target node (the one to be deleted) by accessing the predecessor's next pointer. Second, it extracts the data value from this target node before any structural modifications, preserving the value for return. Third, it updates the predecessor's next pointer to bypass the target node, linking directly to the node that follows the target. This effectively removes the target from the linked chain. Finally, it deletes the target node to free memory, decrements the size counter to reflect the removal, and returns the extracted value to the caller.

This implementation strategy ensures all list invariants are maintained throughout the operation. The head and tail pointers remain valid (updated by delegated methods when necessary), the size accurately reflects element count, and all pointer linkages remain consistent with no dangling references or lost nodes.

**Time Complexity**: O(n)

Where n is the value of the index parameter or the number of elements in the list. The method must traverse from the head node through the linked structure to reach the removal point's predecessor, visiting each intermediate node until positioning correctly. The traversal cost dominates the operation's time complexity, as pointer manipulation, value extraction, and node deletion are constant-time operations.

**Best Case Performance**: O(1) when removing at index 0, as the operation delegates to `remove_first()` which performs head removal without any traversal. This represents optimal performance for beginning-of-list removal.

**Worst Case Performance**: O(n) when removing at index == size-1 (last element), as the operation delegates to `remove_last()` which must traverse the entire list to find the second-to-last node that becomes the new tail. This traversal is unavoidable in singly linked lists due to the unidirectional nature of the next pointers.

**Average Case Performance**: O(n/2) for random removal positions, requiring traversal through approximately half the list on average to reach the predecessor. This simplifies to O(n) in asymptotic analysis.

**Exception Safety**: Throws `std::out_of_range` when the provided index falls outside the valid removal range [0, size-1]. The exception is thrown before any memory access, traversal, or pointer manipulation occurs, providing strong exception guarantee—if removal fails, the list remains completely unchanged with no side effects or resource leaks.

**Valid Index Range**: The method accepts indices from 0 to size-1 (inclusive), representing all existing element positions. This range matches `get()` and `set()` operations as all three methods operate on existing elements. Unlike `insert()` which accepts [0, size] to allow insertion after the last element, removal cannot target a position beyond the last existing element since there is nothing to remove at that position.

**Memory Management**: Deallocates `sizeof(Node)` bytes for each removal through the `delete` operator, returning memory to the heap and preventing memory leaks. The deallocation occurs either within the delegated methods (`remove_first()` or `remove_last()`) or in the middle removal path, but only once per removal operation. The method ensures complete cleanup by holding no references to freed memory after the delete operation.

**Pointer Manipulation Safety**: The removal process carefully sequences operations to prevent undefined behavior. By saving the target node reference before modifying pointer chains, the implementation ensures it can safely access the node for value extraction and eventual deletion. By extracting the data value before deletion, it avoids accessing deallocated memory. By updating the predecessor's next pointer before deleting the target, it maintains list continuity and prevents lost references to subsequent nodes. This ordering is critical for correctness and safety.

**Return Value Semantics**: Returns the integer value that was stored in the removed element, providing the caller with the data content before it is destroyed. This return value enables patterns like "remove and process" where the caller needs to know what was removed, supporting use cases such as undo operations, logging deleted values, or re-inserting removed elements elsewhere. The return value matches the semantics of `remove_first()` and `remove_last()`, maintaining interface consistency across all removal operations.

**Inverse Operation Property**: For any non-empty list configuration and valid index k where 0 ≤ k < size, if `val = list.remove_at(k)` is executed followed by `list.insert(k, val)`, the list is restored to its original state. This inverse relationship demonstrates the methods' complementary nature and supports implementation of operations like "swap with temporary removal" or "extract, modify, and reinsert" patterns.

**Use Cases**: Essential for implementing dynamic list editing in applications where users can delete items at arbitrary positions (task lists, shopping lists), removing elements that match certain criteria after locating them with `find()`, implementing list-based algorithms that require removal at computed positions (removing medians, outliers, or specific ranked elements), building undo/redo functionality where removed elements must be preserved, cleaning up specific positions in data processing pipelines, implementing deletion in sorted lists while maintaining order, removing elements at positions determined by user selection or algorithmic computation, and scenarios requiring fine-grained control over element removal beyond simple first/last removal operations.

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

_Last Updated: 28th February, 2026_
