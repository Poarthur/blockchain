add_executable(project_tests run_tests.cpp)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

target_link_libraries(project_tests PRIVATE ${CONAN_LIBS} Block merklecpp)
add_test(NAME project_tests COMMAND project_tests)

target_include_directories(project_tests PRIVATE ${CMAKE_SOURCE_DIR}/merklecpp)
target_include_directories(project_tests PRIVATE ${CMAKE_SOURCE_DIR}/Block)