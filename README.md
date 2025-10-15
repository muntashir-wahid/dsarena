# Data Structures & Algorithms in C++

A comprehensive collection of data structures and algorithms implemented from scratch in C++. This repository serves as both a learning journey and a reference implementation, documenting the theoretical foundations and practical implementations of fundamental computer science concepts.

## Purpose

This repository is designed to:

- **Learn**: Build deep understanding through hands-on implementation
- **Share**: Provide clear, well-documented code for others learning DSA
- **Showcase**: Demonstrate proficiency in C++, memory management, and algorithmic thinking

## Implementation Progress

### Linear Data Structures

| Data Structure        | Status       | Description                                                                                                                                                                    | Documentation                       |
| --------------------- | ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------------- |
| **Array ADT**         | ✅ Completed | A fixed-capacity array implementation supporting comprehensive operations like insert, remove, search, and manipulation. Demonstrates memory management and RAII principles.   | [View Docs](Array/README.md)        |
| **Dynamic Array ADT** | ✅ Completed | An auto-resizing array built through inheritance from Array ADT. Features automatic capacity expansion with amortized O(1) append performance and exponential growth strategy. | [View Docs](DynamicArray/README.md) |

## Legend

- ✅ **Completed**: Fully implemented with comprehensive documentation
- 🚧 **In Progress**: Currently being developed and enhanced
- 📝 **Planned**: Scheduled for future implementation

---

## Technology Stack

- **Language**: C++
- **Compiler**: Standard C++ compiler (C++11 or later)
- **Build System**: Manual compilation (Makefile or build system to be added)

## Repository Structure

```
.
├── main.cpp              # Root level testing/demo file
├── Array/                # Array ADT implementation
│   ├── Array.h          # Header file
│   ├── Array.cpp        # Implementation
│   ├── main.cpp         # Array-specific tests
│   └── README.md        # Array documentation
├── DynamicArray/         # Dynamic Array ADT implementation
│   ├── DynamicArray.h   # Header file
│   ├── DynamicArray.cpp # Implementation
│   ├── main.cpp         # DynamicArray-specific tests
│   └── README.md        # DynamicArray documentation
└── README.md            # This file
```

## Contributing

This is a personal learning project, but suggestions and feedback are welcome!

_Last Updated: 15th, October 2025_
