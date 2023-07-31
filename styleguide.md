# Styleguide

## Language Standard
Use the subset of C++20 that is supported by all toolchains (especially Emscripten).

## Code Formatting
Use the provided .clang-format file.

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
auto count = std::size_t{ 42 };
```

## `[[nodiscard]]`
Functions without side effects must use the `[[nodiscard]]` attribute.

## `noexcept`
Don't use `noexcept`.

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
