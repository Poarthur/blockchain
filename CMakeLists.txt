cmake_minimum_required(VERSION 3.14)
project(Blockchain VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(Tests)
add_subdirectory(Block)
add_subdirectory(merklecpp)
list(APPEND MY_LIBS Block)
list(APPEND MY_LIBS merklecpp)

add_executable(blockchain main.cpp menu_functions.cpp menu_functions.h)
target_link_libraries(blockchain PRIVATE ${CONAN_LIBS} ${MY_LIBS})
target_include_directories(blockchain PRIVATE
                          "${PROJECT_BINARY_DIR}"
                          )

# testing
enable_testing()

# does the application run
add_test(NAME Runs COMMAND project_tests)
