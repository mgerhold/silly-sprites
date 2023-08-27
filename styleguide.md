# Styleguide

## Language Standard
Use the subset of C++20 that is supported by all toolchains (especially Emscripten).

## Code Formatting
Use the provided .clang-format file.

## Classes and Structs
Use the `struct` keyword for data types that mainly serve as "data containers". They may provide constructors and
operator overloads, though. Don't use access specifiers (`public`, `private`, `protected`) for such types (i.e. make
everything implicitly public).

```cpp
struct Person {
    std::string name;
    int age;
    
    Person(std::string name, int age) : name{ std::move(name) }, age{ age } { }
    
    [[nodiscard]] friend bool operator==(const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name and lhs.age == rhs.age;
    }
};
```

Use the `class` keyword for "more complex" types (whatever that means exactly). Put data members on top, then special
member functions and overloaded operators and then other member functions. In each section, start with public members (
except for private constructors).

In some cases, you cannot follow these rules (e.g. for type aliases or nested type declarations). Just put those in a
position that works ¯\_(ツ)_/¯

Always use access specifiers, even if the first class members are private.

```cpp
template<typename T>
class Wrapper final {
private: // unnecessary, but make it explicitly private
    using Pointer = T*; // must be declared before use
    
    Pointer m_pointer; // data members first
    
public:
    explicit Wrapper(T&& object) : m_pointer{ new T{ std::forward<T>(object) } } { }
    
    Wrapper(const Wrapper&) = delete;
    Wrapper(Wrapper&&) = delete;
    
    Wrapper& operator=(const Wrapper&) = delete;
    Wrapper& operator=(Wrapper&&) = delete;
    
    ~Wrapper() {
        delete m_pointer;
    }
};
```

Constructors shall be marked `explicit` if they only take one parameter (except for copy and move constructors).
Constructors *may* be marked `explicit` if they take more than one parameter.

Either mark the class as `final` or provide a virtual destructor.
Decide for yourself, which member functions you want to define inside the class and which you want to define in a
separate `*.cpp` file.

## `const`
Use `east const`. `constexpr` all the things. `const` all the things you didn't `constexpr` (also function parameters, but not in a pure declaration).

```cpp
struct Person {
    int age;
    static inline int const max_age = 100;
    static constexpr int min_age = 1;
    
    void set_age(int age);
    [[nodiscard]] int get_age() const;
};

inline void Person::set_age(int const age) {
    this->age = age;
}

[[nodiscard]] inline int get_age() const {
    return age;
} 
```

## Identifiers
| identifier type          | capitalization       |
|--------------------------|----------------------|
| classes, structs, enums  | PascalCase           |
| enum variants            | PascalCase           |
| functions                | snake_case           |
| constants                | snake_case           |
| variables & parameters   | snake_case           |
| macros (don't use them!) | SCREAMING_SNAKE_CASE |


| identifier type                    | prefix |
|------------------------------------|--------|
| static member variables            | s_     |
| private member variables           | m_     |
| global constants                   | -      |
| global variables (don't use them!) | g_     |

Names of `enum class`es shall be written in singular (e.g. `enum class Key` instead of `enum class Keys`).

## `auto`
Use almost always `auto`.

## Type Aliases
Use the following type aliases:
```cpp
using usize = std::size_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
```

## Initialization
Initialization must always use `=`.
```cpp
auto person = Person{ "Claus Kleber", 65 };
auto predicate = true; // bool
auto age = 42; // int
auto count = usize{ 42 };
```

## `[[nodiscard]]`
Functions without side effects must use the `[[nodiscard]]` attribute.

## `noexcept`
Don't use `noexcept` except for move constructors and move assignment operators.

## Error Handling
Exceptions maybe used for error handling when needed. Otherwise, prefer `tl::optional` and `tl::expected`.

## Out-Parameters
Don't use them.

## Logical Operators
Use `and`, `or`, and `not` instead of `&&`, `||`, and `!`.

## Memory Management
Don't use raw `new` and `delete`.

## Pointers
No owning raw pointers.

## Miscellaneous

Use `#pragma once` instead of "classic" header guards. Place an empty line between `#pragma once` and the following
code.

```cpp
#pragma once

#include <iostream>
#include <vector>

// ...
```
