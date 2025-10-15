# Dynamic Array ADT Implementation Documentation

## Overview

This document provides a comprehensive overview of a custom Dynamic Array Abstract Data Type (ADT) implemented in C++ through inheritance from the Array ADT. The implementation demonstrates advanced concepts of object-oriented programming, inheritance, dynamic memory management, and automatic resizing capabilities.

A Dynamic Array ADT is a linear data structure that stores elements in contiguous memory locations with automatic capacity management. Unlike the fixed-capacity Array ADT, this implementation provides unlimited growth potential by automatically resizing the underlying storage when needed. The dynamic behavior is achieved through inheritance, extending the base Array functionality while maintaining all existing operations and adding dynamic resizing capabilities.

## Design Philosophy

The Dynamic Array ADT is designed with the following principles:

**Inheritance-Based Architecture**: The Dynamic Array extends the Array ADT through public inheritance, leveraging the robust foundation of the base class while adding dynamic capabilities. This approach promotes code reuse, maintains consistency with the base implementation, and provides a natural evolutionary path from fixed to dynamic arrays.

**Automatic Capacity Management**: Unlike the fixed-capacity Array, the Dynamic Array automatically expands its capacity when needed, eliminating the capacity constraint that limits the base Array. The resizing is transparent to the user, maintaining the same interface while providing unlimited growth potential.

**Exponential Growth Strategy**: The implementation employs a capacity doubling strategy for resizing, ensuring amortized O(1) performance for append operations. This approach balances memory efficiency with performance, minimizing the frequency of expensive resize operations while avoiding excessive memory waste.

**Seamless Interface Extension**: The Dynamic Array maintains full compatibility with the Array interface while overriding specific methods to provide dynamic behavior. Inherited methods like `display()`, `get_length()`, and accessor methods work unchanged, ensuring existing code can transition seamlessly from Array to Dynamic Array.

**Protected Member Access**: The inheritance relationship is made possible by the Array class's protected member variables, allowing the Dynamic Array to access and manipulate the underlying data structures while maintaining proper encapsulation principles.

## Class Structure

The Dynamic Array class inherits all member variables from the Array base class:

- `int* data`: Pointer to dynamically allocated array on the heap (inherited)
- `int size`: Current number of elements stored in the array (inherited)
- `int capacity`: Current maximum number of elements the array can hold (inherited, modified during resize)

Additionally, the Dynamic Array introduces:

- `void resize()`: Private method responsible for expanding the array capacity when needed

## Constructor & Destructor

### Constructor: `DynamicArray(int initial_capacity)`

**Purpose**: Initializes a new Dynamic Array object with a specified initial capacity, leveraging the base Array constructor.

**Implementation Details**: The constructor uses member initializer list syntax to delegate construction to the Array base class constructor. This ensures proper initialization of the inherited member variables (`data`, `size`, `capacity`) while maintaining the established initialization patterns from the base class. The initial capacity serves as the starting point for the dynamic array, but unlike the base Array, this capacity is not a permanent limitation.

**Time Complexity**: O(1)

The constructor performs the same constant-time operations as the base Array constructor. Memory allocation for the initial capacity occurs, but no iterative operations or element initialization is performed. The delegation to the base constructor maintains the same efficiency characteristics.

**Memory Allocation**: Initially allocates `initial_capacity * sizeof(int)` bytes on the heap, identical to the base Array behavior.

**Inheritance Mechanism**: Uses constructor delegation (`Array(initial_capacity)`) to ensure proper base class initialization, following C++ best practices for inheritance hierarchies.

---

### Destructor: `~DynamicArray()`

**Purpose**: Cleans up resources when the Dynamic Array object goes out of scope, relying on automatic base class destructor chaining.

**Implementation Details**: The destructor is implemented with an empty body, allowing the C++ automatic destructor chaining mechanism to handle cleanup. When a Dynamic Array object is destroyed, the derived class destructor is called first (performing no additional cleanup), followed automatically by the base Array destructor which properly de-allocates the dynamic memory using `delete[]`. This approach leverages the established RAII pattern from the base class while maintaining proper inheritance semantics.

**Time Complexity**: O(1)

Destruction follows the same constant-time pattern as the base Array destructor. The automatic chaining adds no additional complexity, and memory deallocation remains a constant-time operation handled by the memory manager.

**Inheritance Mechanism**: Relies on automatic base class destructor invocation, ensuring proper cleanup without explicit base class destructor calls, which would be incorrect C++ syntax.

## Private Helper Methods

### Private Method: `resize()`

**Purpose**: Expands the array capacity when the current capacity is insufficient for new elements, implementing the core dynamic behavior.

**Implementation Details**: The resize method implements a capacity doubling strategy, multiplying the current capacity by 2 to determine the new capacity. This exponential growth approach ensures amortized O(1) performance for insertion operations by reducing the frequency of resize operations as the array grows larger.

The method allocates a new array with the expanded capacity, then performs element-by-element copying from the original array to the new array. The copying loop iterates through exactly `size` elements (not `capacity`), ensuring only valid data is transferred and avoiding copying uninitialized memory regions. After successful copying, the original array memory is deallocated using `delete[]`, and the data pointer is updated to reference the new array.

The resize operation is transparent to users of the Dynamic Array—they only observe that operations that previously would have failed due to capacity constraints now succeed automatically. The method maintains all existing array contents while providing additional space for future elements.

**Time Complexity**: O(n)

Where n is the current size of the array. The resize operation must copy each existing element exactly once from the old array to the new array, resulting in linear time complexity proportional to the number of elements. While this represents a significant cost for individual resize operations, the amortized analysis shows that the doubling strategy distributes this cost effectively across multiple insertions, yielding amortized O(1) performance for sequences of append operations.

Operation breakdown:

- Capacity calculation: O(1)
- New memory allocation: O(1)
- Element copying loop: O(n)
- Each copy operation: O(1)
- Old memory deallocation: O(1)
- Pointer update: O(1)

**Space Complexity**: O(n)

During the resize operation, the method temporarily requires space for both the old and new arrays, effectively doubling the memory footprint momentarily. After copying completes and the old array is deallocated, the space complexity returns to O(n) for the new array alone. This temporary space overhead is inherent to the copying approach and ensures data integrity during the transition.

**Memory Management**: The method carefully manages dynamic memory allocation and deallocation to prevent memory leaks. The old array is only deallocated after successful copying to the new array, ensuring data preservation throughout the operation. The pointer reassignment completes the transition to the new storage.

**Growth Strategy**: The doubling strategy balances memory efficiency with performance. Alternative strategies like fixed increment (capacity += k) would result in O(n²) amortized cost for sequences of insertions, while larger multipliers (capacity \*= 3) would waste more memory for sparse usage patterns.

## Overridden Operations

### `append(int new_element)`

**Purpose**: Adds a new element to the end of the array with automatic capacity expansion when needed.

**Implementation Details**: This method overrides the base Array's `append()` method to provide dynamic behavior. The implementation first checks if capacity is available using the inherited `has_capacity()` helper method. If capacity is sufficient, the method delegates directly to the base class `Array::append()` method, maintaining all the established behavior and error handling of the original implementation.

When capacity is insufficient, the method automatically invokes the private `resize()` method to expand the array capacity before proceeding with the append operation. This automatic expansion eliminates the capacity constraint that would cause the base Array to throw an exception, providing seamless growth capability. After resizing, the method calls `Array::append()` to perform the actual element insertion, ensuring consistency with the base implementation's logic.

The method includes debug output statements that display capacity information before and after resize operations, providing visibility into the dynamic behavior. These statements help users understand when resize operations occur and how the capacity changes in response to growth needs.

**Time Complexity**: Amortized O(1)

While individual append operations may take O(n) time when resize is required, the amortized analysis considers the cost distribution across sequences of operations. The doubling strategy ensures that resize operations become progressively less frequent as the array grows, distributing the O(n) resize cost across approximately n subsequent O(1) append operations. This results in amortized constant time performance for append operations.

Detailed analysis:

- No resize needed: O(1) - direct delegation to base class append
- Resize required: O(n) for copying + O(1) for append
- Amortized across sequence: O(1) due to exponential growth strategy

**Exception Safety**: Inherits the exception safety guarantees from the base Array class for invalid operations, while eliminating capacity-related exceptions through automatic resizing. If resize fails due to memory allocation issues, the original array remains unchanged.

**Memory Behavior**: Capacity grows exponentially (doubles) when expansion is needed, ensuring logarithmic number of resize operations relative to the final array size. This approach balances memory efficiency with performance optimization.

**Output**: Displays capacity information during resize operations for debugging and educational purposes:

- Pre-resize: "Array capacity short: [current_capacity]"
- Post-resize: "Increased capacity: [new_capacity]"

---

### `insert(int index, int new_element)`

**Purpose**: Inserts a new element at a specified position in the array with automatic capacity expansion when needed.

**Implementation Details**: This method overrides the base Array's `insert()` method to provide dynamic behavior while maintaining the same interface and validation logic. The implementation follows the same pattern as the overridden `append()` method: it first checks if capacity is available using the inherited `has_capacity()` helper method, and if capacity is sufficient, delegates directly to the base class `Array::insert()` method.

When capacity is insufficient, the method automatically invokes the private `resize()` method to expand the array capacity before proceeding with the insert operation. This automatic expansion prevents the capacity constraint that would limit insertion operations in the base Array implementation. After resizing, the method calls `Array::insert()` to perform the actual element insertion and shifting operations, ensuring all validation logic, bounds checking, and shifting algorithms remain consistent with the base implementation.

The method includes the same debug output statements as `append()`, providing visibility into capacity changes during insert operations. The position validation and element shifting logic are entirely handled by the base class method, maintaining code reuse and consistency with established behavior patterns.

**Time Complexity**: Amortized O(n)

The insert operation has two components: potential resizing and actual insertion. When no resize is needed, the complexity matches the base Array's O(n) insert operation for element shifting. When resize is required, the operation includes an additional O(n) copying cost, but this cost is amortized across future operations due to the exponential growth strategy.

Detailed analysis:

- No resize needed: O(n) - inherited from base class insert operation
- Resize required: O(n) for copying + O(n) for insertion = O(n)
- Amortized consideration: Resize frequency decreases exponentially

Unlike `append()` which achieves amortized O(1), `insert()` maintains O(n) complexity due to the inherent element shifting requirement, regardless of resize operations. The amortization applies only to the resize cost component.

**Exception Safety**: Inherits position validation and bounds checking from the base Array class, throwing `std::out_of_range` for invalid indices. Eliminates capacity-related limitations through automatic resizing, while maintaining all other safety guarantees.

**Memory Behavior**: Follows the same exponential growth pattern as `append()`, ensuring consistent capacity management across all insertion operations. The resize operation occurs before insertion, guaranteeing sufficient space for the shifting operations performed by the base class method.

**Output**: Displays the same capacity information as `append()` during resize operations:

- Pre-resize: "Array capacity short: [current_capacity]"
- Post-resize: "Increased capacity: [new_capacity]"

## Inherited Operations

The Dynamic Array inherits and provides unchanged access to all methods from the base Array class:

### **Accessor Methods**

- `get_length() const`: Returns current number of elements
- `at(int index) const`: Safe element access with bounds checking
- `first_index_of(int key) const`: Searches for first occurrence of a value

### **Mutator Methods**

- `set(int index, int new_element)`: Updates element at specified index
- `remove(int index)`: Removes and returns element at specified index

### **Display Method**

- `display() const`: Prints array contents in formatted output

### **Analysis Methods**

- `is_sorted(bool ascending = true) const`: Checks if array is sorted

### **Manipulation Methods**

- `reverse()`: Reverses array elements in-place
- `left_shift()`: Shifts elements left, filling rightmost with zero
- `left_rotate()`: Rotates elements left, wrapping first to last
- `right_shift()`: Shifts elements right, filling leftmost with zero
- `right_rotate()`: Rotates elements right, wrapping last to first

### **Advanced Operations**

- `merge(const Array &new_array)`: Merges with another sorted array

All inherited methods maintain their original time complexity, space complexity, and behavioral characteristics as documented in the base Array ADT. The Dynamic Array provides these methods without modification, ensuring complete compatibility and consistent behavior across the inheritance hierarchy.

## Inheritance Benefits

### **Code Reuse**

The Dynamic Array leverages the comprehensive functionality of the base Array class, inheriting over 20 methods without reimplementation. This approach eliminates code duplication and ensures consistent behavior across related data structures.

### **Interface Compatibility**

Existing code written for Array objects can seamlessly work with Dynamic Array objects due to the public inheritance relationship. This enables easy migration from fixed-capacity to dynamic-capacity implementations without code changes.

### **Maintenance Efficiency**

Bug fixes and enhancements to base Array methods automatically benefit the Dynamic Array implementation. This inheritance relationship reduces maintenance overhead and ensures consistency across the class hierarchy.

### **Extensibility**

The inheritance architecture provides a foundation for future extensions, such as specialized dynamic arrays with different growth strategies, shrinking capabilities, or type-specific optimizations.

## Performance Characteristics

### **Amortized Analysis**

The Dynamic Array's resize strategy ensures excellent amortized performance:

- **Append Operations**: Amortized O(1) despite occasional O(n) resize costs
- **Memory Efficiency**: Capacity grows exponentially, minimizing resize frequency
- **Space Utilization**: Load factor remains above 50% for efficient memory usage

### **Resize Frequency**

With exponential growth, resize operations occur at exponentially increasing intervals:

- Resize 1: capacity 1 → 2 (after 1 element)
- Resize 2: capacity 2 → 4 (after 2 more elements)
- Resize 3: capacity 4 → 8 (after 4 more elements)
- Resize n: capacity 2^(n-1) → 2^n (after 2^(n-1) more elements)

This pattern ensures logarithmic number of resize operations relative to final array size.

### **Memory Overhead**

The Dynamic Array maintains similar memory characteristics to the base Array:

- **Allocated Space**: Exactly `capacity * sizeof(int)` bytes
- **Utilized Space**: `size * sizeof(int)` bytes of actual data
- **Overhead**: Constant space for object metadata (pointers, size, capacity)
- **Temporary Overhead**: 2x memory during resize operations

## Use Cases and Applications

### **When to Use Dynamic Array**

- **Unknown Size Requirements**: When the number of elements cannot be predetermined
- **Growing Data Sets**: For applications where data accumulates over time
- **User Input Processing**: When processing variable amounts of user data
- **Algorithm Implementation**: For algorithms requiring flexible storage that may grow
- **Legacy Code Migration**: When upgrading from fixed arrays to dynamic storage

### **When to Use Base Array Instead**

- **Known Fixed Size**: When the maximum number of elements is predetermined and constant
- **Memory-Constrained Environments**: When precise memory control is required
- **Performance-Critical Code**: When avoiding any possibility of resize overhead is essential
- **Embedded Systems**: When predictable memory usage patterns are mandatory

## Implementation Notes

### **Protected Member Access**

The Dynamic Array implementation relies on the base Array class exposing its member variables (`data`, `size`, `capacity`) as `protected` rather than `private`. This design decision enables derived classes to access and modify the underlying data structures while maintaining encapsulation principles.

### **Constructor Delegation**

The Dynamic Array constructor uses member initializer list syntax (`Array(initial_capacity)`) to delegate construction to the base class. This approach ensures proper initialization order and maintains consistency with C++ best practices for inheritance hierarchies.

### **Method Override Strategy**

Only methods requiring dynamic behavior (`append` and `insert`) are overridden, while all other functionality is inherited unchanged. This selective override approach minimizes code duplication while extending only the necessary capabilities.

### **Exception Safety**

The Dynamic Array maintains the same exception safety guarantees as the base Array for all inherited operations, while eliminating capacity-related exceptions through automatic resizing. Memory allocation failures during resize operations are the primary remaining exception source.

### **Debug Output**

The current implementation includes debug output statements for resize operations. In production code, these statements could be conditionally compiled, logged to a file, or removed entirely depending on deployment requirements.

## Future Enhancement Opportunities

### **Shrinking Capability**

- Implement automatic capacity reduction when the array becomes sparsely populated
- Add `shrink_to_fit()` method for manual capacity optimization
- Include configurable shrinking thresholds to balance memory efficiency with performance

### **Custom Growth Strategies**

- Allow configurable growth factors (1.5x, 3x, etc.) for different performance profiles
- Implement linear growth options for memory-constrained environments
- Add adaptive growth strategies based on usage patterns

### **Additional Methods**

- `reserve(int new_capacity)`: Pre-allocate capacity to avoid multiple resizes
- `capacity()`: Query current capacity without accessing protected members
- `clear()`: Remove all elements while preserving capacity

### **Memory Optimization**

- Implement move semantics for more efficient resize operations
- Add custom allocator support for specialized memory management
- Include memory pool options for high-frequency allocation scenarios

### **Type Generalization**

- Convert to template class for supporting different data types
- Implement type-safe operations with template specializations
- Add iterator support for STL compatibility

This Dynamic Array implementation demonstrates effective use of inheritance to extend functionality while maintaining code reuse and interface compatibility. The automatic resizing capability transforms the fixed-capacity limitation of the base Array into unlimited growth potential, making it suitable for a wide range of applications requiring flexible data storage.

_Last Updated: 15th, October 2025_
