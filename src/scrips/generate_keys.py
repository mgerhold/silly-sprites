import re
import sys
from subprocess import call

# Fetch the GLFW key code header from the GLFW repository:
# https://github.com/glfw/glfw/blob/master/include/GLFW/glfw3.h
with open("glfw3.h", "r") as file:
    glfw_header = file.read()

# Extract all GLFW key code macros
key_macros = re.findall(r"#define\s+GLFW_KEY_(\w+)\s+(\d+)", glfw_header)

# Generate the C++ enum and switch case code
enum_code = "enum class Keys {"
switch_code = "[[nodiscard]] constexpr Keys glfw_to_key(int glfw) {switch (glfw) {"

def to_pascal(word):
    return word.lower().replace("_", " ").title().replace(" ", "")

for key_name, key_code in key_macros:
    key_name = to_pascal(key_name)
    enum_code += f"Key{key_name},"
    switch_code += f"case GLFW_KEY_{key_name}: return Keys::Key{key_name};"

enum_code += "};"
switch_code += "default: return assert(false);}}"

path_ = "../silly_sprites/opengl/keys.hpp"

# Write the code to a C++ header file
with open(path_, "w") as file:
    file.write("#pragma once\n namespace sly::gl {" + enum_code + switch_code + '}')

print("Custom enum and switch case code for GLFW keys generated successfully!")

lc = ["clang-format","-i", path_] 
retcode=call(lc)

print("formated")

input();
