import re
import sys
from subprocess import call

# Fetch the GLFW key code header from the GLFW repository:
# https://github.com/glfw/glfw/blob/master/include/GLFW/glfw3.h
if len(sys.argv) < 3:
    sys.exit(1)
_,in_file, out_file = sys.argv
with open(in_file, "r") as file:
    glfw_header = file.read()

# Extract all GLFW key code macros
key_macros = re.findall(r"#define\s+GLFW_MOUSE_BUTTON_(\w+)\s+(\d+)", glfw_header)
key_alias = re.findall(r"#define\s+GLFW_MOUSE_BUTTON_(\w+)\s+GLFW_MOUSE_BUTTON_(\w+)", glfw_header)

# Generate the C++ enum and switch case code
enum_code = "enum class MouseButton {"
switch_glfw_key = "\n\n[[nodiscard]] constexpr MouseButton glfw_to_mouse(int const glfw) {switch (glfw) {"
switch_key_glfw = "\n\n[[nodiscard]] constexpr int mouse_to_glfw(MouseButton const key) {switch (key) {"

def to_pascal(word):
    return word.lower().replace("_", " ").title().replace(" ", "")

for key_name, key_code in key_macros:
    lower_key_name = to_pascal(key_name)
    name_prefix = ""
    if lower_key_name[0].isdigit():
        name_prefix = "Button"
    enum_code += f"{name_prefix}{lower_key_name},"
    switch_glfw_key += f"case GLFW_MOUSE_BUTTON_{key_name}: return MouseButton::{name_prefix}{lower_key_name};"
    switch_key_glfw += f"case MouseButton::{name_prefix}{lower_key_name}: return GLFW_MOUSE_BUTTON_{key_name};"

for key_name, key_code in key_alias:
    if (key_name == "LAST"):
        continue
    lower_key_name = to_pascal(key_name)
    enum_code += f"{lower_key_name} = Button{key_code},"

enum_code += "};"
switch_glfw_key += "default: assert(false); throw std::runtime_error(\"invalid glfw mouse define\");}}"
switch_key_glfw += "default: assert(false);  throw std::runtime_error(\"invalid mouse enum\"); }}"

# Write the code to a C++ header file
with open(out_file, "w") as file:
    file.write("#pragma once\n#include <cassert>\n#include <GLFW/glfw3.h>\n#include <stdexcept>\n\n namespace sly::gl {" + enum_code + switch_glfw_key + switch_key_glfw + '}\n')

print("Custom enum and switch case code for GLFW keys generated successfully!")

lc = ["clang-format","-i", path_] 
retcode=call(lc)

print("formatted")
