# Silly Sprites

## How to Build

This project uses CMake. To build the project, run the following commands in the root directory of the repository.

```bash
cmake -B build
cmake --build build
```

### Dependencies

Dependencies are managed with CPM as part of the CMake project. You need internet access to build the project.

The project uses the following dependencies:
* tl::optional
* tl::expected
* spdlog (including libfmt)
* glfw
* glad
* glm
* fmod
* Box2D
* EnTT
* GTest
* magic_enum
* ms-gsl (C++ core guidelines support library)

## Namespaces
All engine code resides in the `sly::` namespace. Bigger systems each get their own sub-namespace (e.g. `sly::gl::` for OpenGL wrapper classes).
