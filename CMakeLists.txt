# This is the project CMakeLists.txt file for the test subproject 
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

add_compile_options(-fdiagnostics-color=always)
set(ENV{GCC_COLORS} "error=01;31:warning=01;33:note=01;36:caret=01;32:locus=01:quote=01")

project(unit_test)
