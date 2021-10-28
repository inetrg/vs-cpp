cmake_minimum_required(VERSION 3.13.5...3.18 FATAL_ERROR)
project(vs CXX)

include(GNUInstallDirs)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

FetchContent_Declare(
  actor_framework
  GIT_REPOSITORY https://github.com/actor-framework/actor-framework.git
  GIT_TAG        1b29bf10
)
FetchContent_Populate(actor_framework)
set(CAF_ENABLE_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CAF_ENABLE_IO_MODULE ON CACHE BOOL "" FORCE)
set(CAF_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(CAF_ENABLE_TOOLS OFF CACHE BOOL "" FORCE)
set(CAF_ENABLE_OPENSSL_MODULE OFF CACHE BOOL "" FORCE)
set(CAF_SANITIZERS "${CAF_INC_SANITIZERS}" CACHE STRING "" FORCE)
add_subdirectory(${actor_framework_SOURCE_DIR} ${actor_framework_BINARY_DIR})

add_custom_target(all_examples)

# C++ examples.

function(add name)
  add_executable(${name} ${name}.cpp)
  add_dependencies(${name} all_examples)
endfunction()

add(vs01)
add(vs02)
add(vs03)
add(vs04)
add(vs05)
add(vs06)
add(vs07)
add(vs08)
add(vs09)
add(vs10)
add(vs11)
add(vs12)
add(vs13)

# CAF examples.

include_directories(${CAF_INCLUDE_DIRS})
macro(add_caf name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} CAF::core CAF::io)
  add_dependencies(${name} all_examples)
endmacro()
add_caf(vs14)
add_caf(vs15)
add_caf(vs16)
add_caf(vs17)
add_caf(vs18)
add_caf(vs19)
add_caf(vs20)
add_caf(vs21)
add_caf(vs22)
