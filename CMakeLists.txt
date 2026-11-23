cmake_minimum_required(VERSION 3.16)
project(cocoon VERSION 0.1.0 LANGUAGES CXX)

# Generate build/compile_commands.json for clangd and clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.2.1
)
FetchContent_MakeAvailable(cxxopts)

add_executable(cocoon src/main.cpp)

target_include_directories(cocoon PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(cocoon PRIVATE cxxopts::cxxopts)

target_compile_options(cocoon PRIVATE -Wall -Wextra -Wpedantic)
